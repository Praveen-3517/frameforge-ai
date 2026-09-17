"""
╔══════════════════════════════════════════════════════════════╗
║          Bittu AI — Centralized Security Module             ║
╠══════════════════════════════════════════════════════════════╣
║  Provides production-grade security primitives:             ║
║   • Sliding-window rate limiter (per-IP, zero dependencies) ║
║   • File upload validation (size cap + extension allowlist) ║
║   • Mid-stream size enforcement (no OOM on huge uploads)    ║
║   • Filename sanitization (path traversal prevention)       ║
║   • Text input sanitization (null bytes + control chars)    ║
║   • Enum allowlist & numeric clamping                       ║
║   • HTTP security response headers                          ║
╚══════════════════════════════════════════════════════════════╝
"""

from __future__ import annotations

import logging
import re
import time
from collections import defaultdict, deque
from pathlib import Path
from typing import Optional

from fastapi import HTTPException, Request, UploadFile

log = logging.getLogger("bittuai.security")

# ─────────────────────────────────────────────────────────────
# 1.  File Type Allowlists
# ─────────────────────────────────────────────────────────────

ALLOWED_VIDEO_EXTENSIONS: set = {".mp4", ".mov", ".avi", ".mkv", ".webm"}
ALLOWED_AUDIO_EXTENSIONS: set = {".mp3", ".wav", ".ogg", ".m4a", ".aac"}
ALLOWED_IMAGE_EXTENSIONS: set = {".jpg", ".jpeg", ".png", ".webp"}

ALLOWED_MEDIA_EXTENSIONS: set = (
    ALLOWED_VIDEO_EXTENSIONS | ALLOWED_AUDIO_EXTENSIONS | ALLOWED_IMAGE_EXTENSIONS
)

ALLOWED_MIME_TYPES: set = {
    "video/mp4", "video/quicktime", "video/x-msvideo",
    "video/x-matroska", "video/webm",
    "audio/mpeg", "audio/wav", "audio/ogg", "audio/mp4", "audio/aac",
    "image/jpeg", "image/png", "image/webp",
    "application/octet-stream",
}

# ─────────────────────────────────────────────────────────────
# 2.  Hard Limits
# ─────────────────────────────────────────────────────────────

MAX_FILE_SIZE_BYTES: int = 500 * 1024 * 1024   # 500 MB
MAX_TEXT_LENGTH:     int = 5_000
MAX_PROMPT_LENGTH:   int = 500
MAX_TOPIC_LENGTH:    int = 200
MAX_WORD_LENGTH:     int = 30

# ─────────────────────────────────────────────────────────────
# 3.  In-Memory Sliding-Window Rate Limiter
# ─────────────────────────────────────────────────────────────

class _RateLimitStore:
    """Per-IP sliding window backed by deques. GIL-safe under asyncio."""

    def __init__(self) -> None:
        self._windows: dict = defaultdict(deque)

    def is_allowed(self, key: str, max_requests: int, window_sec: int) -> bool:
        now    = time.monotonic()
        window = self._windows[key]
        cutoff = now - window_sec
        while window and window[0] < cutoff:
            window.popleft()
        if len(window) >= max_requests:
            return False
        window.append(now)
        return True


_store = _RateLimitStore()


def _get_client_ip(request: Request) -> str:
    """Extract real client IP honoring Render/Vercel proxy headers."""
    xff = request.headers.get("X-Forwarded-For", "")
    if xff:
        return xff.split(",")[0].strip()
    xri = request.headers.get("X-Real-IP", "")
    if xri:
        return xri.strip()
    return request.client.host if request.client else "unknown"


def rate_limit(request: Request, max_requests: int = 10, window_sec: int = 60) -> None:
    """
    Sliding-window rate limit per (IP, endpoint) pair.
    Raises HTTP 429 with Retry-After header when exceeded.
    """
    ip  = _get_client_ip(request)
    key = f"{ip}:{request.url.path}"
    if not _store.is_allowed(key, max_requests, window_sec):
        log.warning("🚫 Rate-limit exceeded  ip=%-15s  endpoint=%s", ip, request.url.path)
        raise HTTPException(
            status_code=429,
            detail="Too many requests. Please slow down and try again in a minute.",
            headers={"Retry-After": str(window_sec)},
        )


# ─────────────────────────────────────────────────────────────
# 4.  File Upload Validation
# ─────────────────────────────────────────────────────────────

def validate_upload_file(
    file: UploadFile,
    allowed_extensions: Optional[set] = None,
) -> None:
    """
    Validate extension + MIME type BEFORE writing to disk.
    Raises HTTP 400 on disallowed file type.
    """
    if not file or not file.filename:
        raise HTTPException(status_code=400, detail="No file was uploaded.")

    ext     = Path(file.filename).suffix.lower()
    allowed = allowed_extensions if allowed_extensions is not None else ALLOWED_MEDIA_EXTENSIONS

    if ext not in allowed:
        raise HTTPException(
            status_code=400,
            detail=f"File type '{ext}' is not allowed. Accepted: {', '.join(sorted(allowed))}",
        )

    mime = (file.content_type or "").lower().split(";")[0].strip()
    if mime and mime not in ALLOWED_MIME_TYPES:
        log.warning("⚠️  Suspicious MIME  mime=%s  file=%s", mime, file.filename)


async def stream_upload_to_disk(
    file: UploadFile,
    dest_path: Path,
    chunk_size: int = 1024 * 1024,
) -> int:
    """
    Stream upload to disk in 1 MB chunks enforcing the size cap mid-stream.
    Prevents OOM from oversized uploads. Returns total bytes written.
    Raises HTTP 413 if limit exceeded.
    """
    total = 0
    with open(dest_path, "wb") as f:
        while True:
            chunk = await file.read(chunk_size)
            if not chunk:
                break
            total += len(chunk)
            if total > MAX_FILE_SIZE_BYTES:
                f.close()
                try:
                    dest_path.unlink(missing_ok=True)
                except Exception:
                    pass
                raise HTTPException(
                    status_code=413,
                    detail=f"File too large. Maximum allowed size is {MAX_FILE_SIZE_BYTES // (1024*1024)} MB.",
                )
            f.write(chunk)
    return total


# ─────────────────────────────────────────────────────────────
# 5.  Filename Sanitization — Path Traversal Prevention
# ─────────────────────────────────────────────────────────────

_SAFE_FILENAME_RE = re.compile(r"^[a-zA-Z0-9_\-\.]+$")


def sanitize_filename(filename: str) -> str:
    """
    Strip path components and validate against strict alphanumeric allowlist.
    Blocks null bytes, '..', '/', and '\\'.
    Raises HTTP 400 on suspicious input.
    """
    basename = Path(filename).name
    danger   = ("\x00", "..", "/", "\\", "%2e", "%2f", "%5c", "%00")
    for sign in danger:
        if sign.lower() in basename.lower():
            log.error("🚨 Path-traversal attempt  filename=%r", filename)
            raise HTTPException(status_code=400, detail="Invalid filename.")
    if not _SAFE_FILENAME_RE.match(basename):
        raise HTTPException(status_code=400, detail="Filename contains disallowed characters.")
    if len(basename) > 255:
        raise HTTPException(status_code=400, detail="Filename too long.")
    return basename


def safe_output_path(filename: str, allowed_dir: Path) -> Path:
    """
    Resolve filename inside allowed_dir and confirm it doesn't escape via Path.resolve().
    Raises HTTP 400 on traversal.
    """
    safe_name = sanitize_filename(filename)
    resolved  = (allowed_dir / safe_name).resolve()
    allowed   = str(allowed_dir.resolve())

    if not str(resolved).startswith(allowed):
        log.error("🚨 Path-traversal blocked  filename=%r  resolved=%s", filename, resolved)
        raise HTTPException(status_code=400, detail="Invalid file path.")

    return resolved


# ─────────────────────────────────────────────────────────────
# 6.  Text Input Sanitization
# ─────────────────────────────────────────────────────────────

_CONTROL_CHAR_RE  = re.compile(r"[\x00-\x08\x0b\x0c\x0e-\x1f\x7f]")
_SHELL_DANGER     = {";", "|", "&", "`", "$", "{", "}", "<", ">"}


def sanitize_text(text: str, max_length: int = MAX_TEXT_LENGTH, field_name: str = "text") -> str:
    """Strip null bytes and ASCII control chars. Enforce max length."""
    if not isinstance(text, str):
        raise HTTPException(status_code=400, detail=f"'{field_name}' must be a string.")
    cleaned = _CONTROL_CHAR_RE.sub("", text).strip()
    if len(cleaned) > max_length:
        raise HTTPException(
            status_code=400,
            detail=f"'{field_name}' is too long (max {max_length} characters).",
        )
    return cleaned


def sanitize_short_field(value: str, max_length: int, field_name: str) -> str:
    """
    Sanitize a short field (word, topic, key). Strips control chars,
    enforces length, blocks shell metacharacters to prevent FFmpeg injection.
    """
    cleaned = sanitize_text(value, max_length=max_length, field_name=field_name)
    for ch in _SHELL_DANGER:
        if ch in cleaned:
            raise HTTPException(
                status_code=400,
                detail=f"'{field_name}' contains disallowed characters.",
            )
    return cleaned


def sanitize_enum(value: str, allowed: set, field_name: str = "field") -> str:
    """Validate string against an explicit allowlist. Raises HTTP 400 on unknown values."""
    if value not in allowed:
        raise HTTPException(
            status_code=400,
            detail=f"Invalid value for '{field_name}'. Allowed: {', '.join(sorted(allowed))}",
        )
    return value


def clamp(value: float, min_val: float, max_val: float) -> float:
    """Clamp a float to [min_val, max_val]."""
    return max(min_val, min(max_val, value))


# ─────────────────────────────────────────────────────────────
# 7.  HTTP Security Headers
# ─────────────────────────────────────────────────────────────

SECURITY_HEADERS: dict = {
    "X-Content-Type-Options":     "nosniff",
    "X-Frame-Options":            "DENY",
    "X-XSS-Protection":           "1; mode=block",
    "Referrer-Policy":            "strict-origin-when-cross-origin",
    "Permissions-Policy":         "camera=(), microphone=(), geolocation=(), payment=()",
    "Cross-Origin-Opener-Policy": "same-origin-allow-popups",
    # HSTS added conditionally in main.py (only on HTTPS/production)
}

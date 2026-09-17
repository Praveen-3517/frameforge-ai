"""
╔══════════════════════════════════════════════════════════════╗
║          Bittu AI — Email & OTP Verification Service         ║
╠══════════════════════════════════════════════════════════════╣
║  Provides:                                                   ║
║   • Cryptographically secure 6-digit OTP generation          ║
║   • In-memory SHA-256 hashed OTP store with 10-minute TTL    ║
║   • Anti-brute force (5 max attempts lockout)                ║
║   • 60-second resend cooldown per email                      ║
║   • SMTP delivery via Gmail / custom SMTP (STARTTLS/SSL)     ║
║   • Resilient dev fallback when SMTP credentials are unset   ║
╚══════════════════════════════════════════════════════════════╝
"""

from __future__ import annotations

import asyncio
import hashlib
import logging
import os
import re
import secrets
import smtplib
import ssl
import time
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from typing import Dict, Optional, Tuple
from dotenv import load_dotenv

load_dotenv()

log = logging.getLogger("bittuai.email")

# ─────────────────────────────────────────────────────────────
# 1.  Configuration
# ─────────────────────────────────────────────────────────────

def _get_smtp_credentials() -> Tuple[str, int, str, str, str]:
    """Dynamically reads credentials from environment, stripping whitespace from app password."""
    host      = os.getenv("SMTP_HOST", "smtp.gmail.com").strip()
    port      = int(os.getenv("SMTP_PORT", "587"))
    user      = os.getenv("SMTP_USER", "").strip()
    password  = os.getenv("SMTP_PASSWORD", "").strip().replace(" ", "")
    from_name = os.getenv("SMTP_FROM_NAME", "Bittu AI Verification").strip()
    return host, port, user, password, from_name

DEBUG: bool = os.getenv("DEBUG", "false").lower() == "true"

OTP_TTL_SECONDS: int    = 600   # 10 minutes
COOLDOWN_SECONDS: int   = 60    # 1 minute between resends
MAX_ATTEMPTS: int       = 5     # Max failed attempts before lockout

BLOCKED_EMAIL_DOMAINS: set = {
    "mailinator.com", "guerrillamail.com", "tempmail.com", "throwam.com",
    "maildrop.cc", "yopmail.com", "sharklasers.com", "trashmail.com",
    "fakeinbox.com", "dispostable.com", "mailnull.com", "spamgourmet.com",
    "trashmail.net", "discard.email", "spamhereplease.com",
    "spam4.me", "binkmail.com", "safetymail.info", "10minutemail.com",
}

_EMAIL_REGEX = re.compile(r"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,10}$")


def validate_email_address(email: str) -> Optional[str]:
    """
    Validates email format and blocks throwaway domains.
    Returns error message if invalid, None if valid.
    """
    clean = email.strip().lower()
    if not clean:
        return "Email address is required."
    if not _EMAIL_REGEX.match(clean):
        return "Please enter a valid email address."
    domain = clean.split("@")[-1]
    if domain in BLOCKED_EMAIL_DOMAINS:
        return "Disposable or temporary email addresses are not permitted."
    if "." not in domain:
        return "Email domain is invalid."
    return None


# ─────────────────────────────────────────────────────────────
# 2.  In-Memory OTP Store
# ─────────────────────────────────────────────────────────────

# Schema:
# email -> {
#    "hash": str,           # SHA-256(salt + otp)
#    "salt": str,           # 16-char hex
#    "expires_at": float,   # monotonic seconds
#    "attempts": int,
#    "last_sent_at": float,
# }
_OTP_STORE: Dict[str, dict] = {}


def _hash_otp(otp: str, salt: str) -> str:
    """Computes SHA-256 hash with per-OTP salt."""
    return hashlib.sha256(f"{salt}:{otp}".encode("utf-8")).hexdigest()


def _generate_otp() -> str:
    """Generates a cryptographically secure 6-digit numeric string."""
    code = secrets.randbelow(900000) + 100000
    return str(code)


def _cleanup_expired() -> None:
    """Evicts expired OTP records to prevent memory accumulation."""
    now = time.monotonic()
    expired_keys = [k for k, v in _OTP_STORE.items() if now > v.get("expires_at", 0)]
    for k in expired_keys:
        _OTP_STORE.pop(k, None)


# ─────────────────────────────────────────────────────────────
# 3.  HTML Email Template
# ─────────────────────────────────────────────────────────────

def _build_otp_email_html(otp: str, recipient_email: str) -> str:
    """Generates a modern, responsive HTML email template for Bittu AI."""
    return f"""<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Your Bittu AI Verification Code</title>
</head>
<body style="margin: 0; padding: 0; background-color: #0b0714; font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; color: #ffffff;">
  <table role="presentation" width="100%" cellspacing="0" cellpadding="0" style="background-color: #0b0714; padding: 40px 20px;">
    <tr>
      <td align="center">
        <table role="presentation" width="100%" style="max-width: 520px; background: #130d24; border: 1px solid rgba(139, 92, 246, 0.25); border-radius: 20px; overflow: hidden; box-shadow: 0 20px 40px rgba(0,0,0,0.5);">
          <!-- Header Banner -->
          <tr>
            <td style="padding: 32px 32px 20px 32px; background: linear-gradient(135deg, rgba(124, 58, 237, 0.2), rgba(6, 182, 212, 0.1)); text-align: center; border-bottom: 1px solid rgba(139, 92, 246, 0.15);">
              <div style="display: inline-block; width: 48px; height: 48px; line-height: 48px; border-radius: 14px; background: linear-gradient(135deg, #7c3aed, #06b6d4); font-size: 24px; color: #ffffff; text-align: center; font-weight: bold;">
                ⚡
              </div>
              <h1 style="margin: 14px 0 0 0; font-size: 22px; font-weight: 800; letter-spacing: -0.5px; color: #ffffff;">
                Bittu AI
              </h1>
              <p style="margin: 4px 0 0 0; font-size: 13px; color: #a78bfa; font-weight: 500;">
                Next-Gen AI Creation Platform
              </p>
            </td>
          </tr>
          <!-- Body Content -->
          <tr>
            <td style="padding: 32px; text-align: center;">
              <h2 style="margin: 0 0 8px 0; font-size: 18px; font-weight: 700; color: #f1f5f9;">
                Verify Your Email Address
              </h2>
              <p style="margin: 0 0 24px 0; font-size: 13px; color: #94a3b8; line-height: 1.6;">
                Use the 6-digit verification code below to complete your registration.
              </p>

              <!-- OTP Code Display Card -->
              <div style="background: rgba(124, 58, 237, 0.1); border: 2px dashed #8b5cf6; border-radius: 16px; padding: 22px; margin: 0 auto 24px auto; max-width: 320px;">
                <span style="font-family: 'Courier New', Courier, monospace; font-size: 38px; font-weight: 800; letter-spacing: 8px; color: #38bdf8; display: block;">
                  {otp}
                </span>
                <span style="display: block; margin-top: 8px; font-size: 11px; text-transform: uppercase; letter-spacing: 1px; color: #c4b5fd; font-weight: 600;">
                  Valid for 10 minutes
                </span>
              </div>

              <p style="margin: 0 0 16px 0; font-size: 12px; color: #64748b; line-height: 1.5;">
                This code was requested for <strong style="color: #cbd5e1;">{recipient_email}</strong>.<br>
                If you did not make this request, you can safely ignore this email.
              </p>

              <div style="margin-top: 24px; padding-top: 20px; border-top: 1px solid rgba(255,255,255,0.08); font-size: 11px; color: #475569;">
                🔒 Bittu AI Security Team · Never share your verification code with anyone.
              </div>
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
</body>
</html>"""


# ─────────────────────────────────────────────────────────────
# 4.  SMTP Email Dispatcher
# ─────────────────────────────────────────────────────────────

def _send_smtp_sync(to_email: str, subject: str, text_content: str, html_content: str) -> None:
    """Synchronous SMTP email sender designed to run via asyncio.to_thread."""
    host, port, user, password, from_name = _get_smtp_credentials()
    if not user or not password:
        raise ValueError("SMTP credentials (SMTP_USER / SMTP_PASSWORD) are not configured.")

    msg = MIMEMultipart("alternative")
    msg["Subject"] = subject
    msg["From"]    = f"{from_name} <{user}>"
    msg["To"]      = to_email

    msg.attach(MIMEText(text_content, "plain"))
    msg.attach(MIMEText(html_content, "html"))

    if port == 465:
        context = ssl.create_default_context()
        with smtplib.SMTP_SSL(host, port, context=context, timeout=15) as server:
            server.login(user, password)
            server.sendmail(user, [to_email], msg.as_string())
    else:
        with smtplib.SMTP(host, port, timeout=15) as server:
            context = ssl.create_default_context()
            server.ehlo()
            server.starttls(context=context)
            server.ehlo()
            server.login(user, password)
            server.sendmail(user, [to_email], msg.as_string())


# ─────────────────────────────────────────────────────────────
# 5.  Public Service Interface
# ─────────────────────────────────────────────────────────────

async def request_otp(email: str) -> dict:
    """
    Validates cooldown, generates a 6-digit OTP, stores its SHA-256 hash,
    and sends it via SMTP (or prints to terminal in dev mode if SMTP is unconfigured).
    """
    _cleanup_expired()
    normalized_email = email.strip().lower()
    now = time.monotonic()

    # Check 60-second cooldown
    record = _OTP_STORE.get(normalized_email)
    if record:
        elapsed = now - record.get("last_sent_at", 0)
        if elapsed < COOLDOWN_SECONDS:
            remaining = int(COOLDOWN_SECONDS - elapsed)
            return {
                "success": False,
                "error": f"Please wait {remaining}s before requesting a new code.",
                "cooldown_remaining": remaining,
            }

    # Generate and hash OTP
    otp = _generate_otp()
    salt = secrets.token_hex(8)
    otp_hash = _hash_otp(otp, salt)

    _OTP_STORE[normalized_email] = {
        "hash": otp_hash,
        "salt": salt,
        "expires_at": now + OTP_TTL_SECONDS,
        "attempts": 0,
        "last_sent_at": now,
    }

    # Dispatch email
    _, _, user, password, _ = _get_smtp_credentials()
    has_smtp = bool(user and password)
    if has_smtp:
        subject = f"{otp} is your Bittu AI verification code"
        text_body = f"Your Bittu AI verification code is: {otp}\nValid for 10 minutes.\nDo not share this code."
        html_body = _build_otp_email_html(otp, normalized_email)

        try:
            await asyncio.to_thread(_send_smtp_sync, normalized_email, subject, text_body, html_body)
            log.info("✅ Verification OTP successfully sent via SMTP to %s", normalized_email)
            return {
                "success": True,
                "message": f"Verification code sent to {normalized_email}",
                "dev_mode": False,
            }
        except Exception as exc:
            log.error("❌ SMTP send failed for %s: %s", normalized_email, str(exc))
            return {
                "success": False,
                "error": "Failed to send email. Please check server SMTP configuration.",
            }
    else:
        # Dev / Testing fallback: Log prominently in terminal so developers can test immediately
        log.warning(
            "\n" + "═" * 60 + "\n"
            f"📧 [DEV MODE — SMTP NOT SET] Verification OTP for:\n"
            f"   Target: {normalized_email}\n"
            f"   OTP Code: >>> {otp} <<<\n"
            f"   Expires in: {OTP_TTL_SECONDS // 60} minutes\n"
            + "═" * 60
        )
        return {
            "success": True,
            "message": f"Verification code sent to {normalized_email}",
            "dev_mode": True,
            "dev_otp": otp if (DEBUG or not has_smtp) else None,
        }


def verify_otp_code(email: str, user_otp: str) -> dict:
    """
    Validates user-submitted OTP against stored SHA-256 hash.
    Enforces expiration and max 5 attempts lockout.
    """
    _cleanup_expired()
    normalized_email = email.strip().lower()
    cleaned_otp = user_otp.strip()

    record = _OTP_STORE.get(normalized_email)
    if not record:
        return {
            "success": False,
            "error": "No active verification code found for this email. Please request a new one.",
        }

    now = time.monotonic()
    if now > record.get("expires_at", 0):
        _OTP_STORE.pop(normalized_email, None)
        return {
            "success": False,
            "error": "Verification code has expired. Please request a new one.",
        }

    # Increment attempts
    record["attempts"] = record.get("attempts", 0) + 1
    if record["attempts"] > MAX_ATTEMPTS:
        _OTP_STORE.pop(normalized_email, None)
        return {
            "success": False,
            "error": "Too many failed attempts. For security, this code has been revoked. Please request a new code.",
        }

    # Verify constant-time comparison
    expected_hash = record["hash"]
    candidate_hash = _hash_otp(cleaned_otp, record["salt"])

    if not secrets.compare_digest(expected_hash, candidate_hash):
        remaining = MAX_ATTEMPTS - record["attempts"]
        return {
            "success": False,
            "error": f"Invalid verification code. {remaining} attempt{'s' if remaining != 1 else ''} remaining.",
        }

    # Verified! Invalidate immediately to prevent reuse
    _OTP_STORE.pop(normalized_email, None)
    log.info("🎯 OTP verified successfully for %s", normalized_email)
    return {
        "success": True,
        "message": "Email verified successfully.",
    }

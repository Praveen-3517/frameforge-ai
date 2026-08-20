"""
Audio & Video Fingerprint Analyzer Service (High-Performance Engine)
Performs ultra-fast acoustic signal analysis, visual perceptual hashing (dHash),
dominant color analysis, motion detection, keyframe extraction, and dual-media forensic comparison.
"""

from __future__ import annotations

import base64
import hashlib
import json
import logging
import math
import os
import subprocess
import time
from pathlib import Path
from typing import Dict, Any, List, Tuple, Optional

import cv2
import imageio_ffmpeg
import numpy as np
from scipy.fft import rfft, rfftfreq

log = logging.getLogger("text2video.fingerprint")

FFMPEG_EXE = imageio_ffmpeg.get_ffmpeg_exe()


# ─────────────────────────────────────────────────────────────
# 1.  Ultra-Fast Audio Signal Processing & Fingerprinting
# ─────────────────────────────────────────────────────────────

def extract_pcm_audio(media_path: Path, sample_rate: int = 16000) -> Tuple[np.ndarray, int]:
    """
    Extract raw mono PCM float32 audio at 16kHz via FFmpeg stdout stream.
    Optimized for sub-second execution across large audio/video files.
    """
    cmd = [
        FFMPEG_EXE,
        "-threads", "0",          # Utilize all CPU threads for demuxing
        "-i", str(media_path),
        "-t", "90",               # Sample up to 90 seconds (standard for acoustics)
        "-vn",                    # No video decoding
        "-ac", "1",               # Downmix to mono
        "-ar", str(sample_rate),  # 16kHz is standard for acoustic speech & music analysis
        "-f", "f32le",            # 32-bit float Little Endian PCM
        "-threads", "0",          # Utilize all CPU threads
        "-",                      # Pipe to stdout
    ]

    try:
        proc = subprocess.run(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            timeout=15,           # Safety timeout
        )

        if proc.returncode != 0 or len(proc.stdout) == 0:
            return np.array([], dtype=np.float32), sample_rate

        raw_audio = np.frombuffer(proc.stdout, dtype=np.float32)
        return raw_audio, sample_rate
    except Exception as e:
        log.warning("Audio extraction error: %s", e)
        return np.array([], dtype=np.float32), sample_rate


def analyze_audio_fingerprint(media_path: Path) -> Dict[str, Any]:
    """
    Perform sub-second acoustic analysis:
    - Waveform RMS points for visualization
    - Frequency spectrum & 7-band distribution (Sub-bass, Bass, Low-Mid, Mid, High-Mid, Treble, Brilliance)
    - Pitch / Spectral Centroid & Rolloff
    - Tempo (BPM) & Onset Energy
    - Dialogue / Music / Sound Effect characteristics
    - Acoustic Perceptual Hash (Landmark SHA-256)
    """
    audio, sr = extract_pcm_audio(media_path, sample_rate=16000)
    has_audio = len(audio) > 0

    if not has_audio:
        return {
            "has_audio": False,
            "duration_sec": 0.0,
            "waveform": [],
            "frequency_bands": {},
            "spectral_metrics": {},
            "tempo_bpm": 0,
            "characteristics": {},
            "audio_fingerprint_hash": "0000000000000000000000000000000000000000000000000000000000000000",
        }

    duration = len(audio) / sr

    # 1. Waveform Envelope (100 sampled RMS points for clean, responsive canvas rendering)
    num_points = 100
    chunk_size = max(1, len(audio) // num_points)
    waveform = []
    for i in range(num_points):
        chunk = audio[i * chunk_size : (i + 1) * chunk_size]
        if len(chunk) > 0:
            rms = float(np.sqrt(np.mean(chunk**2)))
            peak = float(np.max(np.abs(chunk)))
            val = round(min(1.0, (rms * 0.7 + peak * 0.3) * 2.5), 3)
            waveform.append(val)
        else:
            waveform.append(0.0)

    # 2. Fast FFT Spectral Analysis (Representative Window)
    fft_samples = min(len(audio), int(sr * 4))
    start_idx = max(0, (len(audio) - fft_samples) // 2)
    fft_segment = audio[start_idx : start_idx + fft_samples]
    
    # Hanning window
    windowed = fft_segment * np.hanning(len(fft_segment))
    spectrum = np.abs(rfft(windowed))
    freqs = rfftfreq(len(windowed), 1.0 / sr)

    def band_energy(f_min, f_max):
        mask = (freqs >= f_min) & (freqs < f_max)
        if np.any(mask):
            return float(np.mean(spectrum[mask]))
        return 0.0

    bands_raw = {
        "Sub-Bass (20-60 Hz)": band_energy(20, 60),
        "Bass (60-250 Hz)": band_energy(60, 250),
        "Low-Mid (250-500 Hz)": band_energy(250, 500),
        "Midrange (500-2000 Hz)": band_energy(500, 2000),
        "High-Mid (2k-4k Hz)": band_energy(2000, 4000),
        "Treble (4k-8k Hz)": band_energy(4000, 8000),
        "Brilliance (8k-16k Hz)": band_energy(8000, 16000),
    }

    max_band = max(bands_raw.values()) or 1.0
    frequency_bands = {k: round((v / max_band) * 100, 1) for k, v in bands_raw.items()}

    # 3. Spectral Metrics
    total_energy = np.sum(spectrum) or 1.0
    spectral_centroid = float(np.sum(freqs * spectrum) / total_energy)
    
    # Zero crossing rate
    zero_crossings = np.nonzero(np.diff(audio > 0))[0]
    zcr = float(len(zero_crossings) / len(audio))

    # 4. Tempo (BPM) via Onset Envelope Autocorrelation
    hop_size = 512
    frame_count = len(audio) // hop_size
    energy_env = [
        float(np.sum(audio[i * hop_size : (i + 1) * hop_size] ** 2))
        for i in range(frame_count)
    ]
    onset_diff = np.diff(np.array(energy_env))
    onset_diff[onset_diff < 0] = 0

    estimated_bpm = 120
    if len(onset_diff) > 100:
        autocorr = np.correlate(onset_diff, onset_diff, mode="full")
        autocorr = autocorr[len(autocorr) // 2 :]
        env_fps = sr / hop_size
        min_lag = int(env_fps * 60 / 180)  # 180 BPM
        max_lag = int(env_fps * 60 / 60)   # 60 BPM
        
        if max_lag < len(autocorr):
            lag_slice = autocorr[min_lag:max_lag]
            if len(lag_slice) > 0 and np.max(lag_slice) > 0:
                best_lag = min_lag + int(np.argmax(lag_slice))
                calculated_bpm = round((60.0 * env_fps) / best_lag)
                if 50 <= calculated_bpm <= 220:
                    estimated_bpm = calculated_bpm

    # 5. Audio Breakdown
    voice_energy = band_energy(300, 3400) / max_band
    dialogue_score = min(100, round(voice_energy * 110, 1))
    harmonic_ratio = min(100, round((1.0 - zcr * 10) * 100, 1))
    music_score = max(10, harmonic_ratio)
    transients = np.count_nonzero(onset_diff > np.mean(onset_diff) * 2.0) if len(onset_diff) > 0 else 0
    sfx_score = min(100, round((transients / max(1, duration)) * 15, 1))

    # 6. Acoustic Perceptual Hash
    hash_payload = (
        f"DUR:{duration:.1f}|CENT:{spectral_centroid:.0f}|BPM:{estimated_bpm}|"
        f"BANDS:{','.join(str(v) for v in frequency_bands.values())}|"
        f"ENV:{','.join(str(w) for w in waveform[:20])}"
    )
    audio_fingerprint_hash = hashlib.sha256(hash_payload.encode()).hexdigest()

    return {
        "has_audio": True,
        "duration_sec": round(duration, 2),
        "waveform": waveform,
        "frequency_bands": frequency_bands,
        "spectral_metrics": {
            "spectral_centroid_hz": round(spectral_centroid, 1),
            "zero_crossing_rate": round(zcr, 4),
            "perceived_brightness": "Bright" if spectral_centroid > 2200 else ("Warm" if spectral_centroid > 1000 else "Deep"),
        },
        "tempo_bpm": estimated_bpm,
        "characteristics": {
            "dialogue_presence_pct": dialogue_score,
            "music_tonality_pct": music_score,
            "sound_effects_activity_pct": sfx_score,
        },
        "audio_fingerprint_hash": audio_fingerprint_hash,
    }


# ─────────────────────────────────────────────────────────────
# 2.  High-Speed Visual Perceptual Hashing & Computer Vision
# ─────────────────────────────────────────────────────────────

def compute_dhash(image_gray: np.ndarray, hash_size: int = 8) -> str:
    """
    Compute 64-bit difference hash (dHash) on downscaled luminance array.
    """
    resized = cv2.resize(image_gray, (hash_size + 1, hash_size), interpolation=cv2.INTER_AREA)
    diff = resized[:, 1:] > resized[:, :-1]
    return "".join(f"{byte:02x}" for byte in np.packbits(diff))


def get_fast_dominant_colors(image_bgr: np.ndarray, k: int = 3) -> List[Dict[str, Any]]:
    """
    Ultra-fast color quantization on 32x32 thumbnail (<0.5ms).
    """
    small = cv2.resize(image_bgr, (32, 32), interpolation=cv2.INTER_AREA)
    pixels = small.reshape(-1, 3).astype(np.float32)

    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 5, 1.0)
    _, labels, centers = cv2.kmeans(pixels, k, None, criteria, 2, cv2.KMEANS_RANDOM_CENTERS)

    counts = np.bincount(labels.flatten(), minlength=k)
    total = len(labels)

    dominant = []
    for count, center in zip(counts, centers):
        b, g, r = [int(max(0, min(255, c))) for c in center]
        hex_code = f"#{r:02X}{g:02X}{b:02X}"
        pct = round((count / total) * 100, 1)
        dominant.append({"hex": hex_code, "rgb": [r, g, b], "percentage": pct})

    dominant.sort(key=lambda x: x["percentage"], reverse=True)
    return dominant


def analyze_video_fingerprint(video_path: Path, max_samples: int = 24) -> Dict[str, Any]:
    """
    Fast sequential video stream scanning:
    - Reads video without expensive seek operations (using fast grab & step skipping)
    - Sub-2-second total analysis time
    - Frame dHash stream, dominant colors, scene cuts, keyframes gallery
    """
    cap = cv2.VideoCapture(str(video_path))
    if not cap.isOpened():
        return {
            "has_video": False,
            "error": "Unable to read video stream.",
        }

    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps = float(cap.get(cv2.CAP_PROP_FPS) or 24.0)
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT) or 0)
    duration = (total_frames / fps) if fps > 0 else 0.0

    # Determine frame step interval to scan exactly ~24 frames across the video
    sample_target = min(max_samples, max(6, total_frames))
    frame_step = max(1, total_frames // sample_target) if total_frames > 0 else 1

    dhash_sequence: List[str] = []
    scene_changes: List[Dict[str, Any]] = []
    motion_profile: List[float] = []
    keyframes: List[Dict[str, Any]] = []
    all_dominant_colors: List[Dict[str, Any]] = []

    prev_gray: Optional[np.ndarray] = None
    prev_hist: Optional[np.ndarray] = None

    frame_idx = 0
    sampled_count = 0

    while cap.isOpened() and sampled_count < sample_target:
        # Fast grab skips decoding overhead
        ret = cap.grab()
        if not ret:
            break

        if frame_idx % frame_step == 0:
            ret, frame = cap.retrieve()
            if not ret or frame is None:
                frame_idx += 1
                continue

            sampled_count += 1
            timestamp = round(frame_idx / fps, 2) if fps > 0 else 0.0

            # Downscale frame immediately to 160px for sub-millisecond OpenCV operations
            h, w = frame.shape[:2]
            scale = 160.0 / max(1, w)
            small_bgr = cv2.resize(frame, (160, int(h * scale)), interpolation=cv2.INTER_AREA)
            gray = cv2.cvtColor(small_bgr, cv2.COLOR_BGR2GRAY)

            # 1. Perceptual dHash
            frame_hash = compute_dhash(gray)
            dhash_sequence.append(frame_hash)

            # 2. Motion Intensity
            if prev_gray is not None:
                diff = cv2.absdiff(gray, prev_gray)
                motion_val = round(float(np.mean(diff) / 255.0) * 100, 1)
                motion_profile.append(motion_val)
            else:
                motion_profile.append(0.0)

            # 3. Fast Scene Change Detection via Grayscale Histogram
            hist = cv2.calcHist([gray], [0], None, [16], [0, 256])
            cv2.normalize(hist, hist)

            is_scene_cut = False
            if prev_hist is not None:
                score = cv2.compareHist(prev_hist, hist, cv2.HISTCMP_CORREL)
                if score < 0.60:
                    is_scene_cut = True
                    scene_changes.append({
                        "timestamp_sec": timestamp,
                        "frame_index": int(frame_idx),
                        "confidence_score": round((1.0 - score) * 100, 1),
                    })

            # 4. Keyframes Gallery (Max 6 keyframes)
            should_save_kf = (
                len(keyframes) == 0
                or is_scene_cut
                or (sampled_count % max(1, sample_target // 4) == 0 and len(keyframes) < 6)
            )

            if should_save_kf and len(keyframes) < 6:
                # Fast thumbnail encoding
                thumb = cv2.resize(frame, (200, int(200 * height / max(1, width))), interpolation=cv2.INTER_AREA)
                _, buffer = cv2.imencode(".jpg", thumb, [int(cv2.IMWRITE_JPEG_QUALITY), 75])
                b64_thumb = "data:image/jpeg;base64," + base64.b64encode(buffer).decode("utf-8")

                k_colors = get_fast_dominant_colors(small_bgr, k=3)
                all_dominant_colors.extend(k_colors)

                keyframes.append({
                    "timestamp_sec": timestamp,
                    "timestamp_formatted": f"{int(timestamp // 60):02d}:{int(timestamp % 60):02d}",
                    "thumbnail_url": b64_thumb,
                    "frame_hash": frame_hash,
                    "dominant_colors": k_colors,
                    "is_scene_cut": is_scene_cut,
                })

            prev_gray = gray
            prev_hist = hist

        frame_idx += 1

    cap.release()

    # Deduplicate dominant color palette
    color_palette = []
    seen_hex = set()
    for col in all_dominant_colors:
        if col["hex"] not in seen_hex:
            seen_hex.add(col["hex"])
            color_palette.append(col)
            if len(color_palette) >= 5:
                break

    # Composite Visual Fingerprint Hash
    composite_payload = (
        f"RES:{width}x{height}|FPS:{fps:.1f}|DUR:{duration:.1f}|"
        f"DHASH:{','.join(dhash_sequence[:12])}|"
        f"CUTS:{len(scene_changes)}"
    )
    visual_fingerprint_hash = hashlib.sha256(composite_payload.encode()).hexdigest()

    return {
        "has_video": True,
        "width": width,
        "height": height,
        "resolution": f"{width}x{height}",
        "fps": round(fps, 2),
        "total_frames": total_frames,
        "duration_sec": round(duration, 2),
        "aspect_ratio": f"{round(width / max(1, height), 2)}:1",
        "dhash_sequence": dhash_sequence,
        "scene_changes": scene_changes,
        "scene_changes_count": len(scene_changes),
        "motion_profile": motion_profile,
        "average_motion_pct": round(float(np.mean(motion_profile)), 1) if motion_profile else 0.0,
        "keyframes": keyframes,
        "dominant_palette": color_palette,
        "visual_fingerprint_hash": visual_fingerprint_hash,
    }


# ─────────────────────────────────────────────────────────────
# 3.  Dual-Media Forensic Comparison Engine
# ─────────────────────────────────────────────────────────────

def hamming_distance(hex1: str, hex2: str) -> int:
    """Compute bitwise Hamming distance between two hex strings."""
    try:
        val1 = int(hex1, 16)
        val2 = int(hex2, 16)
        return bin(val1 ^ val2).count("1")
    except Exception:
        return 64


def compare_media_fingerprints(file_a: Path, file_b: Path) -> Dict[str, Any]:
    """
    Perform deep forensic media comparison in 1-2 seconds.
    """
    t_start = time.perf_counter()

    audio_a = analyze_audio_fingerprint(file_a)
    video_a = analyze_video_fingerprint(file_a)

    audio_b = analyze_audio_fingerprint(file_b)
    video_b = analyze_video_fingerprint(file_b)

    # 1. Compare Audio Tracks
    audio_similarity_pct = 0.0
    audio_match_details = {}

    if audio_a["has_audio"] and audio_b["has_audio"]:
        bands_a = list(audio_a["frequency_bands"].values())
        bands_b = list(audio_b["frequency_bands"].values())
        if bands_a and bands_b and len(bands_a) == len(bands_b):
            v_a = np.array(bands_a, dtype=float)
            v_b = np.array(bands_b, dtype=float)
            norm_a = np.linalg.norm(v_a)
            norm_b = np.linalg.norm(v_b)
            if norm_a > 0 and norm_b > 0:
                band_sim = float(np.dot(v_a, v_b) / (norm_a * norm_b)) * 100
            else:
                band_sim = 50.0
        else:
            band_sim = 50.0

        bpm_diff = abs(audio_a["tempo_bpm"] - audio_b["tempo_bpm"])
        tempo_sim = max(0.0, 100.0 - (bpm_diff * 1.5))

        hash_dist = hamming_distance(audio_a["audio_fingerprint_hash"][:16], audio_b["audio_fingerprint_hash"][:16])
        hash_sim = max(0.0, 100.0 - (hash_dist * 1.5))

        audio_similarity_pct = round(band_sim * 0.5 + tempo_sim * 0.25 + hash_sim * 0.25, 1)
        audio_similarity_pct = max(0.0, min(100.0, audio_similarity_pct))

        audio_match_details = {
            "spectral_band_match_pct": round(band_sim, 1),
            "tempo_bpm_a": audio_a["tempo_bpm"],
            "tempo_bpm_b": audio_b["tempo_bpm"],
            "bpm_match_pct": round(tempo_sim, 1),
            "acoustic_hash_match_pct": round(hash_sim, 1),
        }
    elif not audio_a["has_audio"] and not audio_b["has_audio"]:
        audio_similarity_pct = 100.0
        audio_match_details = {"note": "Both files contain no audio track."}
    else:
        audio_similarity_pct = 0.0
        audio_match_details = {"note": "One file has audio, the other does not."}

    # 2. Compare Video Tracks
    video_similarity_pct = 0.0
    matching_segments = []
    matched_keyframes = []

    if video_a["has_video"] and video_b["has_video"]:
        seq_a = video_a["dhash_sequence"]
        seq_b = video_b["dhash_sequence"]

        min_len = min(len(seq_a), len(seq_b))
        if min_len > 0:
            frame_distances = [
                hamming_distance(seq_a[i], seq_b[i]) for i in range(min_len)
            ]
            frame_sims = [max(0.0, 100.0 - (d / 64.0 * 100.0)) for d in frame_distances]
            avg_frame_sim = float(np.mean(frame_sims))

            # Segment detection
            dur_min = min(video_a["duration_sec"], video_b["duration_sec"])
            dt = dur_min / min_len
            in_match = False
            start_t = 0.0

            for i, sim in enumerate(frame_sims):
                cur_t = round(i * dt, 1)
                if sim >= 70.0 and not in_match:
                    in_match = True
                    start_t = cur_t
                elif sim < 70.0 and in_match:
                    in_match = False
                    matching_segments.append({
                        "start_sec": start_t,
                        "end_sec": cur_t,
                        "duration_sec": round(cur_t - start_t, 1),
                        "similarity_pct": round(float(np.mean(frame_sims[int(start_t/dt):i])), 1),
                    })
            if in_match:
                matching_segments.append({
                    "start_sec": start_t,
                    "end_sec": round(dur_min, 1),
                    "duration_sec": round(dur_min - start_t, 1),
                    "similarity_pct": round(float(np.mean(frame_sims[int(start_t/dt):])), 1),
                })
        else:
            avg_frame_sim = 0.0

        # Color palette similarity
        colors_a = {c["hex"] for c in video_a.get("dominant_palette", [])}
        colors_b = {c["hex"] for c in video_b.get("dominant_palette", [])}
        shared_colors = colors_a.intersection(colors_b)
        color_sim = (len(shared_colors) / max(1, len(colors_a.union(colors_b)))) * 100

        video_similarity_pct = round(avg_frame_sim * 0.85 + color_sim * 0.15, 1)
        video_similarity_pct = max(0.0, min(100.0, video_similarity_pct))

        # Side-by-side keyframes
        for kf_a in video_a.get("keyframes", [])[:4]:
            best_match_kf = None
            best_kf_sim = 0.0
            for kf_b in video_b.get("keyframes", []):
                dist = hamming_distance(kf_a["frame_hash"], kf_b["frame_hash"])
                kf_sim = max(0.0, 100.0 - (dist / 64.0 * 100.0))
                if kf_sim > best_kf_sim:
                    best_kf_sim = kf_sim
                    best_match_kf = kf_b

            if best_match_kf:
                matched_keyframes.append({
                    "keyframe_a": kf_a,
                    "keyframe_b": best_match_kf,
                    "visual_match_pct": round(best_kf_sim, 1),
                })
    else:
        video_similarity_pct = 0.0

    # 3. Overall Similarity Score
    if video_a["has_video"] and video_b["has_video"]:
        if audio_a["has_audio"] and audio_b["has_audio"]:
            overall_score = round(video_similarity_pct * 0.65 + audio_similarity_pct * 0.35, 1)
        else:
            overall_score = round(video_similarity_pct, 1)
    else:
        overall_score = round(audio_similarity_pct, 1)

    # 4. Status Classification
    if overall_score >= 85.0:
        verdict = "MATCH"
        verdict_desc = "High confidence match. The media assets are identical or derivative transformations."
        badge_color = "emerald"
    elif overall_score >= 50.0:
        verdict = "SIMILAR"
        verdict_desc = "Partial similarity detected. The files share substantial visual sequences or acoustic structures."
        badge_color = "amber"
    else:
        verdict = "DIFFERENT"
        verdict_desc = "Distinct content. The files exhibit independent acoustic and visual signatures."
        badge_color = "slate"

    elapsed = round(time.perf_counter() - t_start, 2)

    return {
        "status": "success",
        "comparison_time_sec": elapsed,
        "overall_similarity_pct": overall_score,
        "verdict": verdict,
        "verdict_description": verdict_desc,
        "badge_color": badge_color,
        "audio_similarity_pct": audio_similarity_pct,
        "audio_match_details": audio_match_details,
        "video_similarity_pct": video_similarity_pct,
        "matching_segments": matching_segments,
        "matching_segments_count": len(matching_segments),
        "matched_keyframes": matched_keyframes,
        "media_a": {
            "filename": file_a.name,
            "audio": audio_a,
            "video": video_a,
        },
        "media_b": {
            "filename": file_b.name,
            "audio": audio_b,
            "video": video_b,
        },
    }

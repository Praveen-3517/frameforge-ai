"""
Smart Fingerprint Auto-Transform Derivation Engine
Reads a video's fingerprint analysis and auto-derives optimal transformation parameters
including deep visual transforms (zoom+crop, hue shift, film grain) and audio transforms
(pitch shift, time stretch) for legitimate re-purposing of own original content.
"""

from __future__ import annotations

import colorsys
from typing import Dict, Any


def hex_to_hsl(hex_color: str) -> tuple:
    """Convert a hex color like '#RRGGBB' to (H, S, L) in 0-1 range."""
    try:
        hex_color = hex_color.lstrip('#')
        r, g, b = int(hex_color[0:2], 16) / 255.0, int(hex_color[2:4], 16) / 255.0, int(hex_color[4:6], 16) / 255.0
        h, l, s = colorsys.rgb_to_hls(r, g, b)
        return h, s, l
    except Exception:
        return 0.0, 0.0, 0.5


def derive_transform_params(fingerprint: Dict[str, Any]) -> Dict[str, Any]:
    """
    Intelligently derive all transformation parameters from a video's fingerprint.

    Standard transforms:
    - FPS: switch to a different framerate tier
    - Resolution: upscale or change tier
    - Motion intensity: adjust brightness & contrast
    - Spectral bands: shift saturation
    - Scene cuts: adjust gamma
    - Audio normalization

    Deep transforms (for re-purposing own original content):
    - Visual zoom+crop (changes per-frame fingerprint)
    - Hue rotation (shifts color fingerprint)
    - Film grain overlay (changes pixel dHash)
    - Audio pitch shift ±1-2 semitones
    - Audio time stretch ±1-3%
    """
    audio_fp = fingerprint.get("audio_fingerprint") if isinstance(fingerprint.get("audio_fingerprint"), dict) else {}
    video_fp = fingerprint.get("video_fingerprint") if isinstance(fingerprint.get("video_fingerprint"), dict) else {}

    # ── FPS Derivation ──────────────────────────────────────────
    detected_fps = float(video_fp.get("fps") or 30.0)
    if detected_fps >= 50:
        target_fps = "24"
    elif detected_fps >= 28:
        target_fps = "24"
    else:
        target_fps = "30"

    # ── Resolution Derivation ───────────────────────────────────
    detected_width = int(video_fp.get("width") or 1280)
    detected_height = int(video_fp.get("height") or 720)

    if detected_height >= 1080 and detected_width >= 1920:
        target_resolution = "720p"
    elif detected_height >= 720:
        target_resolution = "1080p"
    elif detected_height >= 480:
        target_resolution = "720p"
    else:
        target_resolution = "720p"

    # ── Aspect Ratio / Fit Mode ─────────────────────────────────
    aspect_ratio = detected_width / max(1, detected_height)
    fit_mode = "crop" if aspect_ratio < 0.7 else "fit"

    # ── Motion → Brightness & Contrast ─────────────────────────
    avg_motion = float(video_fp.get("average_motion_pct") or 15.0)
    if avg_motion > 30.0:
        brightness = 0.06
        contrast = 1.12
    elif avg_motion > 15.0:
        brightness = 0.03
        contrast = 1.05
    else:
        brightness = 0.0
        contrast = 1.0

    # ── Spectral Bass → Saturation ──────────────────────────────
    bands = audio_fp.get("frequency_bands") if isinstance(audio_fp.get("frequency_bands"), dict) else {}
    bass_energy = float(bands.get("Bass (60-250 Hz)") or 0.0)
    sub_bass_energy = float(bands.get("Sub-Bass (20-60 Hz)") or 0.0)
    bass_ratio = (bass_energy + sub_bass_energy) / 2.0

    if bass_ratio > 60.0:
        saturation = 1.18
    elif bass_ratio > 35.0:
        saturation = 1.08
    else:
        saturation = 0.95

    # ── Scene Cuts → Gamma ──────────────────────────────────────
    scene_cuts = int(video_fp.get("scene_changes_count") or 0)
    if scene_cuts > 12:
        gamma = 1.08
    elif scene_cuts > 5:
        gamma = 1.04
    else:
        gamma = 1.0

    # ── Deep Visual Transform Derivation ─────────────────────────
    # Always enable for Smart Auto-Transform to maximize fingerprint change
    deep_visual = True

    # Zoom: 2-3% based on motion (high motion = slightly more aggressive crop)
    zoom_pct = 3.0 if avg_motion > 20.0 else 2.0

    # Hue shift: derived from dominant color temperature
    # High bass content → warm shift (+5°), treble-heavy → cool shift (-5°)
    treble_energy = bands.get("Treble (4k-8k Hz)", 0.0)
    if bass_ratio > treble_energy:
        hue_shift_deg = 6.0    # Warm hue shift
    else:
        hue_shift_deg = -6.0   # Cool hue shift

    # Film grain: add if low motion video (static scenes benefit most)
    add_grain = avg_motion < 20.0

    # ── Deep Audio Transform Derivation ─────────────────────────
    # Pitch shift: +1 semitone for bass-heavy, -1 for treble-heavy
    # Keeps content recognizable but shifts acoustic fingerprint
    if bass_ratio > 50.0:
        pitch_shift_semitones = 1.0    # Slightly higher pitch
    elif treble_energy > 50.0:
        pitch_shift_semitones = -1.0   # Slightly lower pitch
    else:
        pitch_shift_semitones = 1.5    # Default mild shift

    # Time stretch: ±1-2% based on BPM
    tempo_bpm = audio_fp.get("tempo_bpm", 120)
    if tempo_bpm > 140:
        time_stretch_pct = -1.5    # Fast content → slight slowdown
    elif tempo_bpm < 80:
        time_stretch_pct = 1.5     # Slow content → slight speedup
    else:
        time_stretch_pct = 2.0     # Medium → slight speedup

    normalize_audio = True
    audio_sample_rate = 48000

    # ── Build Human-Readable Summary ────────────────────────────
    transform_summary = [
        f"FPS: {detected_fps:.0f} -> {target_fps} fps",
        f"Resolution: -> {target_resolution}",
        f"Visual zoom+crop: {zoom_pct:.0f}% (changes frame fingerprint)",
        f"Hue shift: {hue_shift_deg:+.0f} degrees",
        "Film grain overlay" if add_grain else "No grain",
        f"Audio pitch: {pitch_shift_semitones:+.1f} semitones",
        f"Time stretch: {time_stretch_pct:+.1f}%",
        "Audio: Adaptive level normalization",
        "Metadata: stripped + new SHA-256 hash",
    ]
    if brightness != 0.0:
        transform_summary.insert(2, f"Brightness: +{brightness:.2f}")
    if contrast != 1.0:
        transform_summary.insert(3, f"Contrast: {contrast:.2f}x")
    if saturation != 1.0:
        transform_summary.insert(4, f"Saturation: {saturation:.2f}")
    if gamma != 1.0:
        transform_summary.insert(5, f"Gamma: {gamma:.2f}")

    return {
        # Standard transforms
        "resolution": target_resolution,
        "fit_mode": fit_mode,
        "fps": target_fps,
        "quality": "balanced",
        "brightness": round(brightness, 3),
        "contrast": round(contrast, 3),
        "saturation": round(saturation, 3),
        "gamma": round(gamma, 3),
        "normalize_audio": normalize_audio,
        "audio_sample_rate": audio_sample_rate,
        "strip_metadata": True,
        # Deep visual transforms
        "deep_visual": deep_visual,
        "zoom_pct": zoom_pct,
        "hue_shift_deg": hue_shift_deg,
        "add_grain": add_grain,
        # Deep audio transforms
        "pitch_shift_semitones": round(pitch_shift_semitones, 2),
        "time_stretch_pct": round(time_stretch_pct, 2),
        # Summary
        "transform_summary": transform_summary,
        "derived_from": {
            "detected_fps": detected_fps,
            "detected_resolution": f"{detected_width}x{detected_height}",
            "avg_motion_pct": avg_motion,
            "bass_energy_pct": round(bass_ratio, 1),
            "treble_energy_pct": round(treble_energy, 1),
            "scene_cuts": scene_cuts,
            "tempo_bpm": tempo_bpm,
        },
    }

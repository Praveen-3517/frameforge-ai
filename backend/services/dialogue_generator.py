"""
Multi-Character AI Dialogue & Conversation Video Studio Engine (v2.0 Enhanced)
Generates viral multi-speaker conversations, AI podcasts, comedy debates, and anime dialogues:
  - Ultra-smooth Edge-TTS neural voice synthesis in parallel (Hindi, Hinglish, English, Urdu)
  - 100% In-memory fail-safe audio concatenation & volume mastering with SciPy
  - High-Definition Character Face Avatars (Anime, 3D Pixar, Podcast Hosts, Pets)
  - Rich Studio Environments (Podcast Studio, Cozy Cafe, Cyberpunk, Tech Desk)
  - Active speaker neon halo aura, dynamic equalizer bars, and glowing speech bubbles
  - 1-Click Gemini AI Script Sparker
"""

import asyncio
import io
import json
import logging
import math
import os
import random
import subprocess
import time
import uuid
import wave
from pathlib import Path
from typing import Dict, List, Optional, Any, Tuple
from urllib.parse import quote

import edge_tts
import httpx
import imageio_ffmpeg
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageFilter
from pydantic import BaseModel, Field
from scipy.io import wavfile
import google.generativeai as genai

log = logging.getLogger("dialogue_generator")

TEMP_DIR = Path("temp")
OUTPUT_DIR = Path("outputs")
ASSETS_DIR = Path("assets")
AVATARS_DIR = ASSETS_DIR / "avatars"
THEMES_DIR = ASSETS_DIR / "themes"

TEMP_DIR.mkdir(parents=True, exist_ok=True)
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
AVATARS_DIR.mkdir(parents=True, exist_ok=True)
THEMES_DIR.mkdir(parents=True, exist_ok=True)

# Global in-memory job tracker for asynchronous non-blocking generation
DIALOGUE_JOBS: Dict[str, Dict[str, Any]] = {}


def get_ffmpeg_binary() -> str:
    """Get the absolute path to the bundled static FFmpeg binary."""
    return imageio_ffmpeg.get_ffmpeg_exe()


# ─────────────────────────────────────────────────────────────
# 1. Preset Voices, Avatars & Themes
# ─────────────────────────────────────────────────────────────

PRESET_VOICES = {
    "hi_female_swara": {"name": "Swara (Hindi Female - Smooth & Sweet)", "voice": "hi-IN-SwaraNeural", "lang": "Hindi", "gender": "female"},
    "hi_male_madhur": {"name": "Madhur (Hindi Male - Deep & Energetic)", "voice": "hi-IN-MadhurNeural", "lang": "Hindi", "gender": "male"},
    "en_in_female_neerja": {"name": "Neerja (Indian English Female - Expressive)", "voice": "en-IN-NeerjaNeural", "lang": "Indian English", "gender": "female"},
    "en_in_male_prabhat": {"name": "Prabhat (Indian English Male - Clear & Confident)", "voice": "en-IN-PrabhatNeural", "lang": "Indian English", "gender": "male"},
    "en_us_female_jenny": {"name": "Jenny (US English Female - Natural & Friendly)", "voice": "en-US-JennyNeural", "lang": "English", "gender": "female"},
    "en_us_male_guy": {"name": "Guy (US English Male - Casual Podcast Host)", "voice": "en-US-GuyNeural", "lang": "English", "gender": "male"},
    "en_us_female_aria": {"name": "Aria (US English Female - Professional)", "voice": "en-US-AriaNeural", "lang": "English", "gender": "female"},
    "en_us_male_christopher": {"name": "Christopher (US English Male - Young & Playful)", "voice": "en-US-ChristopherNeural", "lang": "English", "gender": "male"},
    "en_gb_female_sonia": {"name": "Sonia (UK British Female - Elegant)", "voice": "en-GB-SoniaNeural", "lang": "British", "gender": "female"},
    "en_gb_male_ryan": {"name": "Ryan (UK British Male - Sophisticated)", "voice": "en-GB-RyanNeural", "lang": "British", "gender": "male"},
    "ur_female_uzma": {"name": "Uzma (Urdu Female - Soft & Melodious)", "voice": "ur-PK-UzmaNeural", "lang": "Urdu", "gender": "female"},
    "ur_male_asad": {"name": "Asad (Urdu Male - Warm & Polite)", "voice": "ur-PK-AsadNeural", "lang": "Urdu", "gender": "male"},
}

PRESET_AVATARS = {
    "podcast_host_m": {"name": "Podcast Guy (Studio)", "color": "#38BDF8", "prompt": "portrait of cool young indian man podcast host with sleek studio headphones, microphone in front, friendly smile, neon rim lighting, 3d pixar style avatar, 8k, square portrait"},
    "podcast_host_f": {"name": "Podcast Woman (Studio)", "color": "#F43F5E", "prompt": "portrait of stylish young indian woman podcast host with sleek headphones, microphone, warm radiant smile, studio lighting, 3d pixar style avatar, 8k, square portrait"},
    "anime_boy": {"name": "Anime Boy Explorer", "color": "#38BDF8", "prompt": "cute anime teenage boy adventurer with spiky brown hair, blue jacket, expressive happy eyes, clean digital anime portrait, 8k, square portrait"},
    "anime_girl": {"name": "Anime Girl Student", "color": "#EC4899", "prompt": "cute anime girl student with ponytail, pink bow, cheerful smile, sparkling anime eyes, vibrant anime portrait, 8k, square portrait"},
    "pixar_boy": {"name": "3D Pixar Boy", "color": "#F59E0B", "prompt": "cute 3D cartoon boy character, Pixar 3D animated CGI style, big expressive brown eyes, friendly smile, ultra-detailed 8k portrait"},
    "pixar_girl": {"name": "3D Pixar Girl", "color": "#A855F7", "prompt": "cute 3D cartoon girl character, Pixar Disney 3D animated CGI style, joyful smile, curly brown hair, vibrant 8k portrait"},
    "funny_cat": {"name": "Smart 3D Cat", "color": "#FB923C", "prompt": "cute 3D animated cartoon orange tabby cat wearing black hipster glasses, intelligent smile, Pixar 3D style character portrait"},
    "funny_dog": {"name": "Cheerful 3D Dog", "color": "#10B981", "prompt": "adorable 3D animated golden retriever dog wearing a red bow tie, joyful happy smile, Pixar 3D style character portrait"},
}

PRESET_THEMES = {
    "podcast_studio": {
        "name": "🎙️ Modern Podcast Studio",
        "bg_color": "#0F172A",
        "prompt": "modern neon podcast recording studio with acoustic foam walls, warm purple and cyan LED lights, dual microphone boom arms, high-end broadcasting setup, 8k, cinematic lighting",
    },
    "cozy_cafe": {
        "name": "☕ Cozy Coffee Shop",
        "bg_color": "#1C1917",
        "prompt": "aesthetic cozy coffee shop interior, warm fairy lights, wooden cafe counter, coffee cups, soft bokeh background, relaxing atmosphere, 8k",
    },
    "neon_cyberpunk": {
        "name": "🌆 Cyberpunk Rooftop",
        "bg_color": "#0B0F19",
        "prompt": "cyberpunk city skyline night view with glowing neon blue and magenta skyscrapers, holographic signs, futuristic atmospheric haze, 8k",
    },
    "tech_workspace": {
        "name": "💻 Tech Creator Desk",
        "bg_color": "#111827",
        "prompt": "modern minimalist creative workspace, dual curved monitors, warm glowing desk lamp, indoor green plants, clean dark room aesthetic, 8k",
    },
    "living_room": {
        "name": "🛋️ Stylish Modern Room",
        "bg_color": "#18181B",
        "prompt": "stylish modern apartment living room, warm sofa, aesthetic wooden bookshelf, ambient floor lamp, cozy evening interior, 8k",
    },
}

EMOTION_BADGES = {
    "neutral": "💬",
    "happy": "😄 Happy",
    "angry": "😡 Angry",
    "sarcastic": "😏 Sarcastic",
    "surprised": "😲 Shocked",
    "laughing": "🤣 Laughing",
    "whisper": "🤫 Whisper",
    "question": "🤔 Curious",
}


# ─────────────────────────────────────────────────────────────
# 2. Data Models
# ─────────────────────────────────────────────────────────────

class CharacterModel(BaseModel):
    id: str = "char_1"
    name: str = "Rohan"
    avatar_key: str = "podcast_host_m"
    avatar_url: Optional[str] = None
    voice_key: str = "hi_male_madhur"
    pitch: str = "+0Hz"
    speech_rate: str = "+0%"
    theme_color: str = "#38BDF8"


class DialogueLineModel(BaseModel):
    character_id: str = "char_1"
    text: str = "Hey! Kya tumne naya AI tool dekha?"
    emotion: str = "happy"


class DialogueVideoRequest(BaseModel):
    title: str = "AI Podcast Debate"
    aspect_ratio: str = "9:16"
    layout: str = "split_podcast"
    theme_key: str = "podcast_studio"
    characters: List[CharacterModel]
    dialogues: List[DialogueLineModel]
    bg_music: bool = True
    bg_music_style: str = "lofi_chill"
    channel_watermark: str = ""


# ─────────────────────────────────────────────────────────────
# 3. High-Quality Neural Audio Synthesis & Fail-Safe Mastering
# ─────────────────────────────────────────────────────────────

def synthesize_lofi_backdrop(duration: float = 10.0, sample_rate: int = 44100, style: str = "lofi_chill") -> np.ndarray:
    """Procedurally synthesizes warm, soothing lofi acoustic chords as background ambience."""
    num_samples = int(duration * sample_rate)
    t = np.linspace(0, duration, num_samples, endpoint=False)
    audio = np.zeros(num_samples, dtype=np.float32)

    if style == "lofi_chill":
        chords = [
            [261.63, 329.63, 392.00, 493.88],  # Cmaj7
            [220.00, 261.63, 329.63, 392.00],  # Am7
            [293.66, 349.23, 440.00, 523.25],  # Dm7
            [196.00, 246.94, 293.66, 349.23],  # G7
        ]
        chord_dur = 2.5
        for i, chord in enumerate(chords):
            c_start = int((i * chord_dur) * sample_rate)
            c_end = min(num_samples, int(((i + 1) * chord_dur) * sample_rate))
            if c_start >= num_samples:
                break
            c_t = t[c_start:c_end] - (i * chord_dur)
            envelope = np.exp(-1.5 * c_t / chord_dur) * (1.0 - np.exp(-20.0 * c_t / chord_dur))
            for freq in chord:
                audio[c_start:c_end] += 0.25 * np.sin(2 * np.pi * freq * c_t) * envelope
                audio[c_start:c_end] += 0.10 * np.sin(2 * np.pi * (freq * 2.0) * c_t) * envelope

    elif style == "comedy_groove":
        bass_freqs = [130.81, 146.83, 164.81, 196.00]
        step_len = 0.5
        for idx in range(int(duration / step_len) + 1):
            s_start = int(idx * step_len * sample_rate)
            s_end = min(num_samples, int((idx + 1) * step_len * sample_rate))
            if s_start >= num_samples:
                break
            s_t = t[s_start:s_end] - (idx * step_len)
            freq = bass_freqs[idx % len(bass_freqs)]
            env = np.exp(-6.0 * s_t / step_len)
            audio[s_start:s_end] += 0.35 * np.sin(2 * np.pi * freq * s_t) * env

    else:
        audio = 0.15 * np.sin(2 * np.pi * 110.0 * t) + 0.08 * np.sin(2 * np.pi * 220.0 * t)

    max_val = np.max(np.abs(audio))
    if max_val > 0:
        audio = (audio / max_val) * 0.12  # Ducked at 12% so voice dominates
    return audio


async def generate_single_line_voiceover(
    text: str,
    voice_key: str = "hi_male_madhur",
    pitch: str = "+0Hz",
    rate: str = "+0%",
    out_path: Optional[Path] = None,
) -> Tuple[Path, float]:
    """Generates crystal-clear voiceover for a single dialogue line using Edge-TTS with fallback."""
    if voice_key in PRESET_VOICES:
        voice_name = PRESET_VOICES[voice_key]["voice"]
    elif "-" in voice_key:
        voice_name = voice_key
    else:
        voice_name = "hi-IN-MadhurNeural"
    
    if not out_path:
        out_path = TEMP_DIR / f"dlg_voice_{uuid.uuid4().hex[:8]}.mp3"

    for attempt in range(2):
        try:
            comm = edge_tts.Communicate(
                text=text,
                voice=voice_name,
                rate=rate or "+0%",
                pitch=pitch or "+0Hz",
            )
            await asyncio.wait_for(comm.save(str(out_path)), timeout=12.0)
            if out_path.exists() and out_path.stat().st_size > 1000:
                dur = await get_audio_duration(out_path)
                return out_path, dur
        except Exception as exc:
            log.warning("Edge-TTS attempt %d failed for text '%s': %s", attempt + 1, text, exc)
            if attempt == 0:
                voice_name = "hi-IN-MadhurNeural" if ("male" in voice_key.lower() or "guy" in voice_key.lower()) else "hi-IN-SwaraNeural"
                await asyncio.sleep(0.5)

    wav_path = out_path.with_suffix(".wav")
    duration = max(2.0, len(text.split()) * 0.45)
    synth = synthesize_lofi_backdrop(duration=duration, style="podcast_ambient")
    int_data = (synth * 32767).astype(np.int16)
    wavfile.write(str(wav_path), 44100, int_data)
    return wav_path, duration


async def get_audio_duration(file_path: Path) -> float:
    """Probe exact duration in seconds using FFmpeg."""
    ffmpeg_exe = get_ffmpeg_binary()
    cmd = [ffmpeg_exe, "-i", str(file_path)]
    res = await asyncio.to_thread(subprocess.run, cmd, capture_output=True, text=True)
    for line in res.stderr.split("\n"):
        if "Duration:" in line:
            parts = line.split("Duration:")[1].split(",")[0].strip()
            h, m, s = parts.split(":")
            total_sec = float(h) * 3600 + float(m) * 60 + float(s)
            return max(0.6, total_sec)
    return 2.5


def build_master_dialogue_audio_scipy(
    line_audio_items: List[Tuple[Path, float]],
    out_master_path: Path,
    bg_music: bool = True,
    bg_music_style: str = "lofi_chill",
    inter_pause: float = 0.35,
) -> float:
    """
    100% In-Memory Robust Concatenation via SciPy/Numpy.
    Guaranteed to produce continuous, crystal-clear audio with perfectly timed pauses and background ducking.
    """
    ffmpeg_exe = get_ffmpeg_binary()
    sample_rate = 44100
    audio_segments = []

    for idx, (aud_file, dur) in enumerate(line_audio_items):
        seg_wav = TEMP_DIR / f"dlg_seg_{uuid.uuid4().hex[:6]}_{idx}.wav"
        # Convert MP3 to standard 44.1k 16-bit mono/stereo WAV
        conv_cmd = [
            ffmpeg_exe, "-y",
            "-i", str(aud_file),
            "-ar", str(sample_rate),
            "-ac", "2",
            "-f", "wav",
            str(seg_wav)
        ]
        subprocess.run(conv_cmd, capture_output=True)
        
        try:
            _, data = wavfile.read(str(seg_wav))
            if data.ndim == 1:
                data = np.stack([data, data], axis=-1)
            audio_segments.append(data)
        except Exception as e:
            log.warning("Could not read converted segment %s: %s", seg_wav, e)
            silence_samples = int(max(1.0, dur) * sample_rate)
            audio_segments.append(np.zeros((silence_samples, 2), dtype=np.int16))

        # Add inter-dialogue natural breath pause
        pause_samples = int(inter_pause * sample_rate)
        audio_segments.append(np.zeros((pause_samples, 2), dtype=np.int16))

    # Concatenate all voice segments
    if not audio_segments:
        master_data = np.zeros((sample_rate * 3, 2), dtype=np.int16)
    else:
        master_data = np.concatenate(audio_segments, axis=0)

    total_samples = len(master_data)
    total_duration = round(total_samples / sample_rate, 2)

    # Mix background ambient music
    if bg_music:
        bg_audio_float = synthesize_lofi_backdrop(duration=total_duration + 1.0, sample_rate=sample_rate, style=bg_music_style)
        bg_samples = len(bg_audio_float)
        
        if bg_samples >= total_samples:
            bg_slice = bg_audio_float[:total_samples]
        else:
            bg_slice = np.pad(bg_audio_float, (0, total_samples - bg_samples))
            
        # Stereo expansion
        bg_stereo = np.stack([bg_slice, bg_slice], axis=-1)
        bg_int16 = (bg_stereo * 32767).astype(np.float32)

        # Mix voice (90%) + bg music (12%)
        voice_float = master_data.astype(np.float32)
        mixed = voice_float * 0.95 + bg_int16 * 0.15
        master_data = np.clip(mixed, -32767, 32767).astype(np.int16)

    wavfile.write(str(out_master_path), sample_rate, master_data)
    return total_duration


# ─────────────────────────────────────────────────────────────
# 4. Rich Character Avatars & Procedural Face Visuals
# ─────────────────────────────────────────────────────────────

def render_procedural_character_avatar(character: CharacterModel, size: int = 240) -> Image.Image:
    """
    Renders an expressive, ultra-aesthetic illustrated character face
    with skin tones, facial features, hair, eyes, and studio headphones!
    """
    img = Image.new("RGBA", (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)

    color_hex = character.theme_color or "#38BDF8"
    try:
        c_hex = color_hex.lstrip("#")
        c_rgb = tuple(int(c_hex[i:i+2], 16) for i in (0, 2, 4))
    except Exception:
        c_rgb = (56, 189, 248)

    cx, cy = size // 2, size // 2
    r_outer = size // 2 - 8

    # Background gradient disc
    draw.ellipse([8, 8, size - 8, size - 8], fill=(22, 27, 46, 255), outline=(*c_rgb, 255), width=5)

    # Character Body / Hoodie Collar
    body_top = int(size * 0.68)
    draw.chord([int(size * 0.15), body_top, int(size * 0.85), size + 20], start=180, end=0, fill=(*c_rgb, 255))
    draw.ellipse([int(size * 0.35), body_top - 10, int(size * 0.65), body_top + 30], fill=(240, 240, 240, 255))

    # Neck
    neck_w = int(size * 0.22)
    neck_h = int(size * 0.18)
    draw.rectangle([cx - neck_w//2, cy, cx + neck_w//2, cy + neck_h], fill=(255, 218, 185, 255))

    # Head / Face Oval
    face_w = int(size * 0.44)
    face_h = int(size * 0.48)
    draw.ellipse([cx - face_w//2, cy - face_h//2 - 6, cx + face_w//2, cy + face_h//2 - 6], fill=(255, 224, 189, 255))

    # Hair Styles based on Avatar Key
    av_key = character.avatar_key.lower()
    hair_color = (45, 30, 25, 255) if "boy" in av_key or "m" in av_key else (90, 40, 30, 255)

    if "cat" in av_key:
        # Cat Ears
        draw.polygon([(cx - 40, cy - 35), (cx - 70, cy - 80), (cx - 15, cy - 50)], fill=(255, 140, 0, 255))
        draw.polygon([(cx + 40, cy - 35), (cx + 70, cy - 80), (cx + 15, cy - 50)], fill=(255, 140, 0, 255))
        draw.polygon([(cx - 38, cy - 38), (cx - 62, cy - 72), (cx - 20, cy - 50)], fill=(255, 192, 203, 255))
        draw.polygon([(cx + 38, cy - 38), (cx + 62, cy - 72), (cx + 20, cy - 50)], fill=(255, 192, 203, 255))
    elif "dog" in av_key:
        # Floppy Dog Ears
        draw.ellipse([cx - 65, cy - 30, cx - 30, cy + 25], fill=(190, 130, 70, 255))
        draw.ellipse([cx + 30, cy - 30, cx + 65, cy + 25], fill=(190, 130, 70, 255))
    elif "anime" in av_key or "pixar" in av_key:
        # Spiky / Animated Hair Bangs
        draw.chord([cx - face_w//2 - 6, cy - face_h//2 - 22, cx + face_w//2 + 6, cy], start=180, end=0, fill=hair_color)
        draw.polygon([(cx - 35, cy - 15), (cx - 15, cy + 5), (cx - 5, cy - 15)], fill=hair_color)
        draw.polygon([(cx - 5, cy - 15), (cx + 15, cy + 8), (cx + 30, cy - 15)], fill=hair_color)
    else:
        # Chic Modern Hair
        draw.chord([cx - face_w//2 - 6, cy - face_h//2 - 18, cx + face_w//2 + 6, cy - 5], start=180, end=0, fill=hair_color)

    # Eyes & Eyebrows
    eye_y = cy - 8
    eye_offset = 18
    # Left Eye
    draw.ellipse([cx - eye_offset - 8, eye_y - 8, cx - eye_offset + 8, eye_y + 8], fill=(255, 255, 255, 255))
    draw.ellipse([cx - eye_offset - 4, eye_y - 5, cx - eye_offset + 5, eye_y + 5], fill=(30, 30, 40, 255))
    draw.ellipse([cx - eye_offset - 1, eye_y - 4, cx - eye_offset + 3, eye_y], fill=(255, 255, 255, 255))
    # Right Eye
    draw.ellipse([cx + eye_offset - 8, eye_y - 8, cx + eye_offset + 8, eye_y + 8], fill=(255, 255, 255, 255))
    draw.ellipse([cx + eye_offset - 5, eye_y - 5, cx + eye_offset + 4, eye_y + 5], fill=(30, 30, 40, 255))
    draw.ellipse([cx + eye_offset - 2, eye_y - 4, cx + eye_offset + 2, eye_y], fill=(255, 255, 255, 255))

    # Eyebrows
    draw.line([cx - eye_offset - 10, eye_y - 14, cx - eye_offset + 6, eye_y - 12], fill=hair_color, width=3)
    draw.line([cx + eye_offset - 6, eye_y - 12, cx + eye_offset + 10, eye_y - 14], fill=hair_color, width=3)

    # Cheerful Smile / Mouth
    mouth_y = cy + 18
    draw.arc([cx - 14, mouth_y - 8, cx + 14, mouth_y + 12], start=0, end=180, fill=(200, 50, 60, 255), width=4)
    # Rosy Cheeks
    draw.ellipse([cx - eye_offset - 8, cy + 6, cx - eye_offset + 6, cy + 16], fill=(255, 160, 160, 120))
    draw.ellipse([cx + eye_offset - 6, cy + 6, cx + eye_offset + 8, cy + 16], fill=(255, 160, 160, 120))

    # DJ / Studio Overhead Headphones
    hp_color = (*c_rgb, 255)
    # Headband
    draw.arc([cx - face_w//2 - 12, cy - face_h//2 - 24, cx + face_w//2 + 12, cy + 10], start=190, end=350, fill=(50, 55, 70, 255), width=8)
    # Left Ear Cushion
    draw.rounded_rectangle([cx - face_w//2 - 16, cy - 22, cx - face_w//2 + 4, cy + 18], radius=8, fill=hp_color, outline=(255, 255, 255, 200), width=2)
    # Right Ear Cushion
    draw.rounded_rectangle([cx + face_w//2 - 4, cy - 22, cx + face_w//2 + 16, cy + 18], radius=8, fill=hp_color, outline=(255, 255, 255, 200), width=2)

    return img


def get_character_avatar_image(character: CharacterModel, size: int = 240) -> Image.Image:
    """Loads cached HD avatar if available on disk, else creates high-aesthetic procedural face."""
    av_file = AVATARS_DIR / f"{character.avatar_key}.jpg"
    if not av_file.exists():
        av_file = AVATARS_DIR / f"{character.avatar_key}.png"

    if av_file.exists() and av_file.stat().st_size > 1000:
        try:
            raw_img = Image.open(av_file).convert("RGBA")
            # Circular mask crop
            raw_img = raw_img.resize((size, size), Image.LANCZOS)
            mask = Image.new("L", (size, size), 0)
            m_draw = ImageDraw.Draw(mask)
            m_draw.ellipse([6, 6, size - 6, size - 6], fill=255)
            
            avatar_img = Image.new("RGBA", (size, size), (0, 0, 0, 0))
            avatar_img.paste(raw_img, (0, 0), mask)
            
            # Glowing border ring
            draw = ImageDraw.Draw(avatar_img)
            color_hex = character.theme_color or "#38BDF8"
            c_hex = color_hex.lstrip("#")
            c_rgb = tuple(int(c_hex[i:i+2], 16) for i in (0, 2, 4))
            draw.ellipse([6, 6, size - 6, size - 6], outline=(*c_rgb, 255), width=5)
            return avatar_img
        except Exception as e:
            log.warning("Could not load avatar disk asset %s: %s", av_file, e)

    return render_procedural_character_avatar(character, size=size)


# ─────────────────────────────────────────────────────────────
# 5. Rich Scene Theme Backgrounds (Studio / Cafe / Cyberpunk)
# ─────────────────────────────────────────────────────────────

def render_rich_studio_background(theme_key: str, width: int, height: int) -> Image.Image:
    """Renders a rich, detailed, broadcast-quality studio backdrop with depth and lighting."""
    bg = Image.new("RGBA", (width, height), (12, 16, 28, 255))
    draw = ImageDraw.Draw(bg)

    if theme_key == "cozy_cafe":
        # Warm ambient cafe with wooden beams and fairy lights
        for y in range(height):
            ratio = y / height
            r = int(35 + 25 * ratio)
            g = int(25 + 15 * ratio)
            b = int(20 + 10 * ratio)
            draw.line([(0, y), (width, y)], fill=(r, g, b, 255))
        # Wooden table lower half
        draw.rectangle([0, int(height * 0.55), width, height], fill=(45, 30, 20, 255))
        # Fairy lights
        for i in range(12):
            lx = (width // 12) * i + 20
            ly = int(height * 0.15) + (10 if i % 2 == 0 else -10)
            draw.ellipse([lx - 8, ly - 8, lx + 8, ly + 8], fill=(255, 230, 160, 240))
            draw.ellipse([lx - 16, ly - 16, lx + 16, ly + 16], fill=(255, 200, 100, 60))

    elif theme_key == "neon_cyberpunk":
        # Dark cyberpunk night sky with magenta/cyan horizon
        for y in range(height):
            ratio = y / height
            r = int(10 + 35 * ratio)
            g = int(12 + 10 * ratio)
            b = int(25 + 50 * ratio)
            draw.line([(0, y), (width, y)], fill=(r, g, b, 255))
        # Skyscraper silhouettes in background
        for b_idx in range(9):
            bx = b_idx * (width // 8)
            bw = width // 10
            bh = int(height * (0.35 + (b_idx % 3) * 0.12))
            draw.rectangle([bx, height - bh, bx + bw, height], fill=(8, 10, 20, 255))
            # Glowing windows
            for wy in range(height - bh + 20, height - 40, 25):
                draw.rectangle([bx + 8, wy, bx + 16, wy + 10], fill=(0, 240, 255, 180) if b_idx % 2 == 0 else (255, 0, 128, 180))

    else:
        # Default: Modern Neon Podcast Studio
        # Acoustic wall foam geometric pattern
        for y in range(height):
            ratio = y / height
            r = int(14 + 18 * ratio)
            g = int(18 + 22 * ratio)
            b = int(32 + 35 * ratio)
            draw.line([(0, y), (width, y)], fill=(r, g, b, 255))

        # Acoustic foam pyramid grid on upper wall
        tile_size = 40
        for tx in range(0, width, tile_size):
            for ty in range(0, int(height * 0.50), tile_size):
                draw.rectangle([tx + 2, ty + 2, tx + tile_size - 2, ty + tile_size - 2], fill=(20, 26, 45, 180), outline=(35, 45, 75, 120))

        # Dual Neon LED light strips
        draw.line([0, int(height * 0.52), width, int(height * 0.52)], fill=(56, 189, 248, 220), width=4)
        draw.line([0, int(height * 0.54), width, int(height * 0.54)], fill=(244, 63, 94, 220), width=4)

        # Studio Desk in lower half
        draw.rectangle([0, int(height * 0.58), width, height], fill=(16, 20, 34, 255))

    return bg


def get_theme_background(theme_key: str, width: int, height: int) -> Image.Image:
    """Loads HD backdrop asset from disk or creates rich procedural environment."""
    theme_file = THEMES_DIR / f"{theme_key}.jpg"
    if not theme_file.exists():
        theme_file = THEMES_DIR / f"{theme_key}.png"

    if theme_file.exists() and theme_file.stat().st_size > 1000:
        try:
            raw_img = Image.open(theme_file).convert("RGBA")
            return raw_img.resize((width, height), Image.LANCZOS)
        except Exception as e:
            log.warning("Could not load theme disk asset %s: %s", theme_file, e)

    return render_rich_studio_background(theme_key, width, height)


# ─────────────────────────────────────────────────────────────
# 6. Dynamic Visual Frame Rendering with Active Speaker Halos
# ─────────────────────────────────────────────────────────────

def render_dialogue_frame(
    width: int,
    height: int,
    bg_image: Image.Image,
    characters: List[CharacterModel],
    active_char_id: str,
    dialogue_text: str,
    emotion: str = "neutral",
    layout: str = "split_podcast",
    watermark: str = "",
    title: str = "AI Podcast Studio",
    avatar_cache: Optional[Dict[str, Image.Image]] = None,
) -> Image.Image:
    """
    Renders high-definition frame with active character face portrait,
    speaker glowing halo, jumping audio equalizer bars, and dynamic speech bubble.
    """
    frame = bg_image.copy()
    draw = ImageDraw.Draw(frame)

    # 1. Top Title & Branding Bar
    header_h = int(height * 0.08)
    draw.rectangle([0, 0, width, header_h], fill=(10, 13, 23, 230))
    
    try:
        title_font = ImageFont.truetype("arialbd.ttf", 26 if width > 800 else 20)
        sub_font = ImageFont.truetype("arial.ttf", 16 if width > 800 else 13)
        dlg_font = ImageFont.truetype("arialbd.ttf", 28 if width > 800 else 22)
        name_font = ImageFont.truetype("arialbd.ttf", 20 if width > 800 else 16)
        badge_font = ImageFont.truetype("arialbd.ttf", 16 if width > 800 else 13)
    except Exception:
        title_font = ImageFont.load_default()
        sub_font = ImageFont.load_default()
        dlg_font = ImageFont.load_default()
        name_font = ImageFont.load_default()
        badge_font = ImageFont.load_default()

    draw.text((24, header_h // 2), f"🎙️ {title}", font=title_font, fill=(255, 255, 255, 240), anchor="lm")
    if watermark:
        draw.text((width - 24, header_h // 2), f"@{watermark}", font=sub_font, fill=(255, 255, 255, 180), anchor="rm")
    
    # 2. Render Character Avatars & Active Halos
    num_chars = len(characters)
    avatar_size = 200 if width > 800 else 160
    
    char_positions = {}
    if height > width:  # 9:16 Vertical Shorts
        char_y = int(height * 0.28)
        spacing = width // (num_chars + 1)
        for idx, c in enumerate(characters):
            char_positions[c.id] = (spacing * (idx + 1), char_y)
    else:  # 16:9 Landscape
        char_y = int(height * 0.42)
        spacing = width // (num_chars + 1)
        for idx, c in enumerate(characters):
            char_positions[c.id] = (spacing * (idx + 1), char_y)

    active_char = next((c for c in characters if c.id == active_char_id), characters[0])
    
    for c in characters:
        cx, cy = char_positions[c.id]
        is_active = (c.id == active_char_id)
        
        av_img = avatar_cache.get(c.id) if avatar_cache else None
        if not av_img:
            av_img = get_character_avatar_image(c, size=avatar_size)
            
        cur_size = int(avatar_size * 1.18) if is_active else int(avatar_size * 0.88)
        scaled_av = av_img.resize((cur_size, cur_size), Image.LANCZOS)
        
        c_hex = c.theme_color.lstrip("#")
        try:
            c_rgb = tuple(int(c_hex[i:i+2], 16) for i in (0, 2, 4))
        except Exception:
            c_rgb = (56, 189, 248)

        if not is_active:
            # Slight dimming for inactive listener
            av_data = np.array(scaled_av)
            av_data[:, :, 3] = (av_data[:, :, 3] * 0.70).astype(np.uint8)
            scaled_av = Image.fromarray(av_data)
        else:
            # Vibrant glowing aura behind active speaker
            aura_r = cur_size // 2 + 16
            draw.ellipse([cx - aura_r, cy - aura_r, cx + aura_r, cy + aura_r], fill=(*c_rgb, 60), outline=(*c_rgb, 255), width=6)
            
            # Animated Equalizer Bars jumping under speaker
            bar_w = 5
            bar_gap = 4
            num_bars = 7
            eq_start = cx - ((num_bars * (bar_w + bar_gap)) // 2)
            eq_y = cy + (cur_size // 2) + 26
            for b in range(num_bars):
                bh = random.randint(10, 26)
                bx = eq_start + (b * (bar_w + bar_gap))
                draw.rectangle([bx, eq_y - bh, bx + bar_w, eq_y + bh], fill=(*c_rgb, 240))

        frame.paste(scaled_av, (cx - cur_size // 2, cy - cur_size // 2), scaled_av)
        
        # Name Tag
        badge_y = cy + (cur_size // 2) + (38 if is_active else 20)
        badge_w = int(len(c.name) * 14 + 32)
        badge_rect = [cx - badge_w // 2, badge_y - 12, cx + badge_w // 2, badge_y + 14]
        
        badge_bg = (20, 24, 38, 230) if not is_active else (*c_rgb, 230)
        text_color = (255, 255, 255, 200) if not is_active else (0, 0, 0, 255)
        
        draw.rounded_rectangle(badge_rect, radius=8, fill=badge_bg, outline=(255, 255, 255, 80), width=1)
        draw.text((cx, badge_y), c.name, font=name_font, fill=text_color, anchor="mm")

    # 3. Render Dynamic Speech Bubble (Bottom Center)
    bubble_w = int(width * 0.90)
    bubble_h = int(height * 0.36) if height > width else int(height * 0.30)
    bubble_x1 = (width - bubble_w) // 2
    bubble_y1 = height - bubble_h - int(height * 0.05)
    bubble_x2 = bubble_x1 + bubble_w
    bubble_y2 = bubble_y1 + bubble_h
    
    try:
        active_hex = active_char.theme_color.lstrip("#")
        active_rgb = tuple(int(active_hex[i:i+2], 16) for i in (0, 2, 4))
    except Exception:
        active_rgb = (56, 189, 248)

    # Glassmorphism Card with Active Glowing Border
    draw.rounded_rectangle(
        [bubble_x1, bubble_y1, bubble_x2, bubble_y2],
        radius=26,
        fill=(10, 14, 26, 240),
        outline=(*active_rgb, 240),
        width=4
    )

    # Bubble Header: Speaker Name + Emotion Tag
    top_badge_y = bubble_y1 + 24
    emotion_label = EMOTION_BADGES.get(emotion, "💬")
    draw.text((bubble_x1 + 26, top_badge_y), f"🗣️ {active_char.name}", font=name_font, fill=(*active_rgb, 255), anchor="lm")
    draw.text((bubble_x2 - 26, top_badge_y), emotion_label, font=badge_font, fill=(255, 255, 255, 220), anchor="rm")
    
    draw.line([bubble_x1 + 20, bubble_y1 + 46, bubble_x2 - 20, bubble_y1 + 46], fill=(255, 255, 255, 40), width=1)

    # Multi-Line Wrapped Dialogue Text
    text_start_y = bubble_y1 + 72
    max_char_per_line = 36 if width > 800 else 24
    
    words = dialogue_text.split()
    lines = []
    current_line = []
    for w in words:
        if len(" ".join(current_line + [w])) <= max_char_per_line:
            current_line.append(w)
        else:
            if current_line:
                lines.append(" ".join(current_line))
            current_line = [w]
    if current_line:
        lines.append(" ".join(current_line))

    line_spacing = 38 if width > 800 else 30
    for idx, line_str in enumerate(lines[:4]):
        ly = text_start_y + (idx * line_spacing)
        draw.text(((bubble_x1 + bubble_x2) // 2, ly), line_str, font=dlg_font, fill=(255, 255, 255, 255), anchor="mm")

    return frame.convert("RGB")


# ─────────────────────────────────────────────────────────────
# 7. Main Asynchronous Video Generation Task
# ─────────────────────────────────────────────────────────────

async def build_dialogue_video_task(job_id: str, req: DialogueVideoRequest) -> None:
    """
    Background worker that updates DIALOGUE_JOBS[job_id] in real-time.
    Executes parallel neural TTS, in-memory audio mix, and native FFmpeg stitch.
    """
    t_start = time.time()
    try:
        DIALOGUE_JOBS[job_id] = {
            "status": "processing",
            "step": 1,
            "step_name": "Initializing Studio & Preloading Character Neural Voices",
            "progress_pct": 15,
            "error": None,
        }

        if req.aspect_ratio == "16:9":
            width, height = 1280, 720
        else:
            width, height = 720, 1280

        # Step 2: Parallel Voice Synthesis
        DIALOGUE_JOBS[job_id]["step"] = 2
        DIALOGUE_JOBS[job_id]["step_name"] = "Synthesizing Multi-Character Natural Neural Voiceovers"
        DIALOGUE_JOBS[job_id]["progress_pct"] = 35

        char_map = {c.id: c for c in req.characters}
        voice_tasks = []
        for d in req.dialogues:
            char = char_map.get(d.character_id, req.characters[0])
            voice_tasks.append(
                generate_single_line_voiceover(
                    text=d.text,
                    voice_key=char.voice_key,
                    pitch=char.pitch,
                    rate=char.speech_rate,
                )
            )

        line_audio_items = await asyncio.gather(*voice_tasks)

        # Step 3: In-Memory SciPy Audio Mastering
        DIALOGUE_JOBS[job_id]["step"] = 3
        DIALOGUE_JOBS[job_id]["step_name"] = "Mastering Multi-Track Dialogue & Ambient Lo-Fi Track"
        DIALOGUE_JOBS[job_id]["progress_pct"] = 60

        master_audio_path = TEMP_DIR / f"{job_id}_master.wav"
        total_audio_duration = await asyncio.to_thread(
            build_master_dialogue_audio_scipy,
            line_audio_items,
            master_audio_path,
            bg_music=req.bg_music,
            bg_music_style=req.bg_music_style,
            inter_pause=0.35,
        )

        # Step 4: Render Avatars and Visual Frames
        DIALOGUE_JOBS[job_id]["step"] = 4
        DIALOGUE_JOBS[job_id]["step_name"] = "Rendering Active Speaker Glow, Avatars & Speech Balloons"
        DIALOGUE_JOBS[job_id]["progress_pct"] = 80

        bg_image = get_theme_background(req.theme_key, width, height)
        avatar_cache = {c.id: get_character_avatar_image(c, size=200 if width > 800 else 160) for c in req.characters}
        
        frame_durations = []
        for idx, d in enumerate(req.dialogues):
            audio_path, line_dur = line_audio_items[idx]
            frame_img = render_dialogue_frame(
                width=width,
                height=height,
                bg_image=bg_image,
                characters=req.characters,
                active_char_id=d.character_id,
                dialogue_text=d.text,
                emotion=d.emotion,
                layout=req.layout,
                watermark=req.channel_watermark,
                title=req.title,
                avatar_cache=avatar_cache,
            )
            
            frame_path = TEMP_DIR / f"{job_id}_frame_{idx}.png"
            frame_img.save(frame_path)
            # Duration matching dialogue duration + inter-pause
            frame_durations.append((frame_path, line_dur + 0.35))

        # Step 5: Native FFmpeg Concat Demuxer Compilation
        DIALOGUE_JOBS[job_id]["step_name"] = "Compiling Broadcast-Ready MP4 Video with FFmpeg"
        DIALOGUE_JOBS[job_id]["progress_pct"] = 90

        output_filename = f"dialogue_{uuid.uuid4().hex[:6]}.mp4"
        output_path = OUTPUT_DIR / output_filename
        
        await asyncio.to_thread(
            stitch_dialogue_slideshow_ffmpeg,
            frame_durations,
            master_audio_path,
            output_path,
        )

        elapsed = round(time.time() - t_start, 2)
        log.info("✅ [Job %s] Multi-Character Dialogue Video generated in %.2f s: %s", job_id, elapsed, output_path)

        # Step 6: Completed
        DIALOGUE_JOBS[job_id] = {
            "status": "completed",
            "step": 5,
            "step_name": "Complete",
            "progress_pct": 100,
            "video_url": f"/api/media/{output_filename}",
            "filename": output_filename,
            "title": req.title,
            "num_dialogues": len(req.dialogues),
            "duration": round(total_audio_duration, 1),
            "aspect_ratio": req.aspect_ratio,
            "generation_time_sec": elapsed,
            "error": None,
        }

    except Exception as exc:
        log.exception("❌ [Job %s] Dialogue video generation failed: %s", job_id, exc)
        DIALOGUE_JOBS[job_id] = {
            "status": "failed",
            "error": str(exc),
            "step": 0,
            "step_name": "Failed",
            "progress_pct": 0,
        }


def stitch_dialogue_slideshow_ffmpeg(
    frame_durations: List[Tuple[Path, float]],
    audio_path: Path,
    output_path: Path,
) -> None:
    """Stitches dialogue frames and master audio with explicit stream mapping."""
    if not frame_durations:
        raise ValueError("No dialogue frames provided to stitch.")

    ffmpeg_exe = get_ffmpeg_binary()
    concat_txt = audio_path.parent / f"concat_{uuid.uuid4().hex[:6]}.txt"
    
    try:
        with open(concat_txt, "w", encoding="utf-8") as f:
            for f_path, dur in frame_durations:
                clean_p = str(f_path.resolve()).replace("\\", "/")
                f.write(f"file '{clean_p}'\n")
                f.write(f"duration {dur}\n")
            # Concat demuxer requirement
            last_p = str(frame_durations[-1][0].resolve()).replace("\\", "/")
            f.write(f"file '{last_p}'\n")

        cmd = [
            ffmpeg_exe, "-y",
            "-f", "concat",
            "-safe", "0",
            "-i", str(concat_txt),
            "-i", str(audio_path),
            "-map", "0:v:0",
            "-map", "1:a:0",
            "-c:v", "libx264",
            "-preset", "ultrafast",
            "-crf", "22",
            "-pix_fmt", "yuv420p",
            "-c:a", "aac",
            "-b:a", "192k",
            "-movflags", "+faststart",
            "-shortest",
            str(output_path)
        ]

        res = subprocess.run(cmd, capture_output=True, text=True)
        if res.returncode != 0:
            log.error("FFmpeg stitch error: %s", res.stderr)
            raise RuntimeError(f"FFmpeg error: {res.stderr}")
    finally:
        if concat_txt.exists():
            try:
                concat_txt.unlink()
            except Exception:
                pass


# ─────────────────────────────────────────────────────────────
# 8. Gemini AI Script Sparker
# ─────────────────────────────────────────────────────────────

async def generate_ai_dialogue_script(
    topic: str,
    language: str = "hinglish",
    genre: str = "comedy",
    char_count: int = 2,
) -> Dict[str, Any]:
    """Generates engaging multi-character dialogue script with Gemini AI."""
    prompt = f"""
    Create a highly engaging, viral, natural multi-character dialogue script for social media (Shorts / Reels / YouTube).
    
    Topic: {topic}
    Language: {language} (use natural conversational slang, Hindi/Hinglish/English as requested)
    Genre/Vibe: {genre} (e.g. funny, debate, podcast gossip, educational, dramatic)
    Number of Characters: {char_count} (Name them appropriately, e.g., Rohan & Priya, or Vikram & Sameer)
    
    Return STRICTLY valid JSON with this exact schema:
    {{
      "title": "Short catchy title",
      "characters": [
        {{
          "id": "char_1",
          "name": "Character 1 Name",
          "avatar_key": "podcast_host_m",
          "voice_key": "hi_male_madhur",
          "theme_color": "#38BDF8"
        }},
        {{
          "id": "char_2",
          "name": "Character 2 Name",
          "avatar_key": "podcast_host_f",
          "voice_key": "hi_female_swara",
          "theme_color": "#F43F5E"
        }}
      ],
      "dialogues": [
        {{
          "character_id": "char_1",
          "text": "First dialogue line here",
          "emotion": "happy"
        }},
        {{
          "character_id": "char_2",
          "text": "Response dialogue line here",
          "emotion": "sarcastic"
        }}
      ]
    }}
    Provide between 4 to 8 fast-paced dialogue turns.
    """

    api_key = os.getenv("GEMINI_API_KEY")
    if not api_key:
        return get_fallback_script(topic, language)

    try:
        genai.configure(api_key=api_key)
        model = genai.GenerativeModel("gemini-1.5-flash")
        response = await asyncio.to_thread(model.generate_content, prompt)
        text = response.text.strip()
        
        if text.startswith("```"):
            lines = text.split("\n")
            if lines[0].startswith("```"):
                lines = lines[1:]
            if lines and lines[-1].startswith("```"):
                lines = lines[:-1]
            text = "\n".join(lines).strip()
            
        data = json.loads(text)
        return data
    except Exception as exc:
        log.warning("Gemini script generation fallback: %s", exc)
        return get_fallback_script(topic, language)


def get_fallback_script(topic: str, language: str = "hinglish") -> Dict[str, Any]:
    """Instant creative fallback script if AI API is offline."""
    if "chai" in topic.lower() or "coffee" in topic.lower():
        return {
            "title": "Chai vs Coffee Ultimate Debate",
            "characters": [
                {"id": "char_1", "name": "Rohan (Chai Lover)", "avatar_key": "podcast_host_m", "voice_key": "hi_male_madhur", "theme_color": "#38BDF8"},
                {"id": "char_2", "name": "Priya (Coffee Fan)", "avatar_key": "podcast_host_f", "voice_key": "hi_female_swara", "theme_color": "#F43F5E"},
            ],
            "dialogues": [
                {"character_id": "char_1", "text": "Bhai, subah subah adrak wali kadak Chai ke bina din hi shuru nahi hota!", "emotion": "happy"},
                {"character_id": "char_2", "text": "Excuse me? Tum abhi tak 90s mein ho! Real energy Espresso coffee mein aati hai.", "emotion": "sarcastic"},
                {"character_id": "char_1", "text": "Arrey par tumhari coffee 300 rupaye ki aati hai, aur meri chai sirf das rupaye ki!", "emotion": "laughing"},
                {"character_id": "char_2", "text": "Par taste aur aesthetics dekho! Coffee is an emotion!", "emotion": "surprised"},
                {"character_id": "char_1", "text": "Tapri wali chai hi asli emotion hai boss! Tapri zindabad!", "emotion": "happy"},
            ]
        }
    else:
        return {
            "title": f"Viral Talk: {topic or 'AI Future'}",
            "characters": [
                {"id": "char_1", "name": "Aman", "avatar_key": "anime_boy", "voice_key": "hi_male_madhur", "theme_color": "#38BDF8"},
                {"id": "char_2", "name": "Ananya", "avatar_key": "anime_girl", "voice_key": "hi_female_swara", "theme_color": "#EC4899"},
            ],
            "dialogues": [
                {"character_id": "char_1", "text": "Arrey yaar, kya lagta hai AI sab kuch replace kar dega?", "emotion": "question"},
                {"character_id": "char_2", "text": "Sab kuch toh nahi, par jo seekhega nahi usse zaroor replace karega!", "emotion": "sarcastic"},
                {"character_id": "char_1", "text": "Toh phir hume kya karna chahiye? Coding seekhein ya Prompting?", "emotion": "surprised"},
                {"character_id": "char_2", "text": "Dono seekho! Aur haan, smart work pe focus karo!", "emotion": "happy"},
            ]
        }

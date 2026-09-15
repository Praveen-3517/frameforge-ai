"""
FrameForge AI — 24/7 Multi-Track YouTube Live Stream Engine
Streams continuous playlist of MP4 videos & MP3 audio tracks in an infinite 24/7 loop to YouTube Live:
  - 100% Free, Native FFmpeg RTMP Engine
  - Auto-scans 'bhajans/' folder for all audio & video tracks
  - For audio files (MP3/WAV), automatically overlays 1080p divine background visual
  - 2-Second GOP Keyframe Sync for perfect YouTube Live stability
  - Real-time live status monitor & auto-reconnect watchdog
"""

import os
import sys
import time
import signal
import subprocess
from pathlib import Path
from typing import List

# Ensure safe UTF-8 terminal printing on Windows
try:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8")
    if hasattr(sys.stderr, "reconfigure"):
        sys.stderr.reconfigure(encoding="utf-8")
except Exception:
    pass

import imageio_ffmpeg
from PIL import Image, ImageDraw, ImageFont

ROOT_DIR = Path(__file__).resolve().parent.parent.parent
BHAJANS_DIR = ROOT_DIR / "bhajans"
ASSETS_DIR = ROOT_DIR / "backend" / "assets"
BG_IMAGE_PATH = ASSETS_DIR / "bhakti_live_bg.jpg"
STREAM_KEY_FILE = ROOT_DIR / ".stream_key"

BHAJANS_DIR.mkdir(parents=True, exist_ok=True)
ASSETS_DIR.mkdir(parents=True, exist_ok=True)


def get_ffmpeg_binary() -> str:
    """Get absolute path to static FFmpeg binary."""
    return imageio_ffmpeg.get_ffmpeg_exe()


def create_divine_background_if_missing(width: int = 1920, height: int = 1080) -> Path:
    """Creates a high-definition 1080p divine glowing temple visual if not already present."""
    if BG_IMAGE_PATH.exists():
        return BG_IMAGE_PATH

    print("🎨 Creating 1080p Divine Live Broadcast Wallpaper...")
    img = Image.new("RGB", (width, height), (15, 10, 25))
    draw = ImageDraw.Draw(img)

    # Deep golden & cosmic royal gradient
    for y in range(height):
        prog = y / height
        r = int(25 + 40 * (1 - prog) + 20 * prog)
        g = int(15 + 25 * (1 - prog) + 10 * prog)
        b = int(45 + 50 * (1 - prog) + 15 * prog)
        draw.line([(0, y), (width, y)], fill=(r, g, b))

    # Glowing golden aura in center
    cx, cy = width // 2, int(height * 0.45)
    for rad in range(350, 0, -10):
        alpha_ratio = 1.0 - (rad / 350.0)
        gr = int(255 * alpha_ratio * 0.4)
        gg = int(180 * alpha_ratio * 0.4)
        draw.ellipse([cx - rad, cy - rad, cx + rad, cy + rad], fill=(r + gr, g + gg, b))

    # Divine Emblem / Symbol
    try:
        font_big = ImageFont.truetype("arialbd.ttf", 90)
        font_title = ImageFont.truetype("arialbd.ttf", 54)
        font_sub = ImageFont.truetype("arial.ttf", 34)
    except Exception:
        font_big = ImageFont.load_default()
        font_title = ImageFont.load_default()
        font_sub = ImageFont.load_default()

    # Draw Om / Sacred Symbol
    draw.text((cx - 60, cy - 80), "ॐ", font=font_big, fill=(255, 215, 0))

    # Live Banner at Bottom
    banner_h = int(height * 0.22)
    draw.rectangle([0, height - banner_h, width, height], fill=(10, 8, 18))
    draw.line([(0, height - banner_h), (width, height - banner_h)], fill=(255, 215, 0), width=4)

    # Live Text
    draw.text((80, height - banner_h + 35), "🔴 24/7 LIVE: JAI SHREE RAM 🙏", font=font_title, fill=(255, 75, 75))
    draw.text((80, height - banner_h + 105), "Peaceful Hanuman Chalisa, Krishna Bhajans, Aarti & Meditation", font=font_sub, fill=(255, 230, 160))

    # Save wallpaper
    img.save(str(BG_IMAGE_PATH), "JPEG", quality=95)
    print("✅ Broadcast Wallpaper saved ->", BG_IMAGE_PATH.name)
    return BG_IMAGE_PATH


def get_media_tracks() -> List[Path]:
    """Scan bhajans/ folder for playable audio & video files."""
    valid_exts = {".mp4", ".mkv", ".mov", ".avi", ".mp3", ".wav", ".m4a", ".aac"}
    files = [f for f in BHAJANS_DIR.iterdir() if f.is_file() and f.suffix.lower() in valid_exts]

    # If empty, check outputs directory as fallback
    if not files:
        outputs_dir = ROOT_DIR / "outputs"
        if outputs_dir.exists():
            files = [f for f in outputs_dir.iterdir() if f.is_file() and f.suffix.lower() in valid_exts]

    return sorted(files)


def stream_single_track(track_path: Path, rtmp_url: str, bg_path: Path, track_idx: int, total_tracks: int):
    """Streams a single audio or video track to the RTMP destination."""
    ffmpeg_exe = get_ffmpeg_binary()
    is_audio = track_path.suffix.lower() in {".mp3", ".wav", ".m4a", ".aac"}

    print("\n" + "=" * 70)
    print(f"  ▶️ NOW STREAMING LIVE [{track_idx}/{total_tracks}]: {track_path.name}")
    print(f"  Type: {'🎵 Audio Track (with 1080p Wallpaper)' if is_audio else '🎬 Video File'}")
    print(f"  Target: YouTube Live RTMP ({rtmp_url[:35]}...)")
    print("=" * 70)

    # 🕉️ Bhakti Zero-Claim Audio Armor: 432Hz Sacred + 1.042x Speed Sync + 7-Stage Formant Notch EQ + Mandir Reverb + Stereo Phase
    af_live_armor = (
        "asetrate=46272,atempo=0.99308,aresample=44100,"
        "equalizer=f=108:t=q:w=2.0:g=+3.5,equalizer=f=80:t=q:w=1.5:g=+2.0,"
        "equalizer=f=380:t=q:w=1.8:g=-3.5,equalizer=f=850:t=q:w=2.0:g=-4.5,"
        "equalizer=f=1250:t=q:w=2.0:g=-4.5,equalizer=f=2150:t=q:w=2.0:g=-4.0,"
        "equalizer=f=2900:t=q:w=1.8:g=-3.5,"
        "aecho=0.75:0.5:60|120:0.22|0.10,extrastereo=m=0.35"
    )

    if is_audio:
        # Loop background image with audio input + live audio armor
        cmd = [
            ffmpeg_exe,
            "-re",                          # Read input at native frame rate (realtime)
            "-loop", "1",
            "-i", str(bg_path),             # Background image
            "-i", str(track_path),          # Audio track
            "-c:v", "libx264",
            "-preset", "veryfast",
            "-tune", "zerolatency",
            "-b:v", "2500k",
            "-maxrate", "2500k",
            "-bufsize", "5000k",
            "-pix_fmt", "yuv420p",
            "-g", "60",                     # 2s Keyframe interval at 30fps
            "-r", "30",
            "-s", "1920x1080",
            "-af", af_live_armor,           # 🕉️ Content ID Protection Shield
            "-c:a", "aac",
            "-b:a", "128k",
            "-ar", "44100",
            "-shortest",                    # Stop when audio ends
            "-f", "flv",
            rtmp_url,
        ]
    else:
        # Stream MP4 video with horizontal mirror + audio armor
        cmd = [
            ffmpeg_exe,
            "-re",                          # Realtime playback rate
            "-i", str(track_path),
            "-vf", "hflip,scale=1920:1080", # Mirror to break video Content ID
            "-c:v", "libx264",
            "-preset", "veryfast",
            "-tune", "zerolatency",
            "-b:v", "2500k",
            "-maxrate", "2500k",
            "-bufsize", "5000k",
            "-pix_fmt", "yuv420p",
            "-g", "60",                     # 2s GOP keyframes for YouTube Live
            "-r", "30",
            "-af", af_live_armor,           # 🕉️ Content ID Protection Shield
            "-c:a", "aac",
            "-b:a", "128k",
            "-ar", "44100",
            "-f", "flv",
            rtmp_url,
        ]

    proc = subprocess.Popen(cmd)
    try:
        proc.wait()
    except KeyboardInterrupt:
        proc.terminate()
        raise


def run_247_live_stream():
    """Main 24/7 infinite streaming orchestrator."""
    print("=" * 70)
    print("      🕉️  FRAMEFORGE AI — 24/7 YOUTUBE LIVE STREAMING ENGINE")
    print("=" * 70)

    # 1. Get / Load YouTube Stream Key
    stream_key = ""
    if STREAM_KEY_FILE.exists():
        saved_key = STREAM_KEY_FILE.read_text(encoding="utf-8").strip()
        if saved_key:
            print(f"🔑 Loaded saved Stream Key: {saved_key[:6]}****{saved_key[-4:] if len(saved_key)>10 else ''}")
            use_saved = input("Use this Stream Key? [Y/n]: ").strip().lower()
            if use_saved != "n":
                stream_key = saved_key

    if not stream_key:
        print("\n👉 How to get your Stream Key:")
        print("   1. Open YouTube Studio (https://studio.youtube.com)")
        print("   2. Click 'Go Live' (Top Right Camera icon)")
        print("   3. Copy your 'Stream Key' (Default stream key)")
        print("-" * 70)
        stream_key = input("Paste your YouTube Stream Key here: ").strip()

        if not stream_key:
            print("❌ Stream key cannot be empty. Exiting.")
            sys.exit(1)

        # Save for next time
        STREAM_KEY_FILE.write_text(stream_key, encoding="utf-8")
        print("💾 Stream key saved to .stream_key for future 1-click runs!")

    rtmp_url = f"rtmp://a.rtmp.youtube.com/live2/{stream_key}"

    # 2. Ensure Background Image
    bg_path = create_divine_background_if_missing()

    # 3. Check Tracks in bhajans/
    tracks = get_media_tracks()
    if not tracks:
        print("\n⚠️ No audio/video files found in 'bhajans/' folder!")
        print(f"👉 Please copy your Hanuman Chalisa, Krishna Bhajans, or MP4 videos into:")
        print(f"   📁 {BHAJANS_DIR.resolve()}")
        print("\nWaiting 10 seconds for you to paste files, or press Ctrl+C...")
        for _ in range(10):
            time.sleep(1)
            tracks = get_media_tracks()
            if tracks:
                break

    if not tracks:
        print("❌ Still no files found in 'bhajans/'. Exiting.")
        sys.exit(1)

    print(f"\n✅ Found {len(tracks)} Track(s) in Playlist Queue:")
    for idx, t in enumerate(tracks, 1):
        print(f"   {idx}. {t.name} ({'Audio' if t.suffix.lower() in {'.mp3','.wav'} else 'Video'})")

    print("\n" + "#" * 70)
    print("  🚀 STARTING 24/7 CONTINUOUS YOUTUBE LIVE BROADCAST")
    print("  Keep this window open in background.")
    print("  Press Ctrl+C anytime to stop stream gracefully.")
    print("#" * 70 + "\n")

    loop_count = 1
    start_time = time.time()

    try:
        while True:
            print(f"\n🔄 === PLAYLIST ROTATION CYCLE #{loop_count} ===")
            for idx, track in enumerate(tracks, 1):
                try:
                    stream_single_track(track, rtmp_url, bg_path, idx, len(tracks))
                except KeyboardInterrupt:
                    raise
                except Exception as e:
                    print(f"⚠️ Track {track.name} stream interrupted: {e}. Moving to next track in 3s...")
                    time.sleep(3)

            loop_count += 1
            elapsed_hours = (time.time() - start_time) / 3600.0
            print(f"\n✨ Completed Loop #{loop_count - 1}! Total Live Uptime: {elapsed_hours:.2f} Hours.")
            print("Restarting playlist from Track #1 for 24/7 non-stop broadcast...")
            time.sleep(1)

    except KeyboardInterrupt:
        print("\n\n🛑 Live Stream stopped by user. Jai Shree Ram! 🙏")


if __name__ == "__main__":
    run_247_live_stream()

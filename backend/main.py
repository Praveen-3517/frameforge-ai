"""
╔══════════════════════════════════════════════════════════════╗
║     Text-to-Video  —  FastAPI Backend (100% FREE Stack)     ║
║                                                              ║
║  Pipeline:                                                   ║
║   1. Gemini 1.5 Flash → 3 cinematic image prompts           ║
║   2. Pollinations.ai  → 3 HD images (FREE, no key needed)   ║
║   3. Edge-TTS         → MP3 voiceover (FREE)                ║
║   4. MoviePy          → Ken Burns effect + stitch + audio   ║
║   5. FastAPI          → Stream final MP4 to client          ║
║                                                              ║
║  ⚡ Generation time: ~30–60 seconds                          ║
║  💰 Cost: $0.00                                              ║
╚══════════════════════════════════════════════════════════════╝
"""

from __future__ import annotations

import asyncio
import json
import logging
import os
import time
import uuid
from pathlib import Path
from typing import List
from urllib.parse import quote

import edge_tts
import google.generativeai as genai
import httpx
import numpy as np
from dotenv import load_dotenv
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse
from moviepy.editor import (
    AudioFileClip,
    ImageClip,
    concatenate_videoclips,
)
from PIL import Image
from pydantic import BaseModel, Field

# ─────────────────────────────────────────────────────────────
# 0.  Bootstrap
# ─────────────────────────────────────────────────────────────

load_dotenv()

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s  %(levelname)-8s  %(name)s — %(message)s",
    datefmt="%H:%M:%S",
)
log = logging.getLogger("text2video")

# ─────────────────────────────────────────────────────────────
# 1.  Configuration
# ─────────────────────────────────────────────────────────────

GEMINI_API_KEY: str  = os.getenv("GEMINI_API_KEY", "")
FRONTEND_ORIGIN: str = os.getenv("FRONTEND_ORIGIN", "http://localhost:5173")

OUTPUT_DIR = Path(os.getenv("OUTPUT_DIR", "outputs"))
TEMP_DIR   = Path(os.getenv("TEMP_DIR",   "temp"))

OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
TEMP_DIR.mkdir(parents=True, exist_ok=True)

if not GEMINI_API_KEY:
    log.warning("GEMINI_API_KEY is not set!")

# Configure Gemini (free)
genai.configure(api_key=GEMINI_API_KEY)

# Pollinations.ai — 100% free, no API key needed
POLLINATIONS_URL = "https://image.pollinations.ai/prompt/{prompt}?width=1280&height=720&nologo=true&enhance=true&model=flux"

# Video settings
CLIP_DURATION_SEC = 6      # seconds per scene
VIDEO_WIDTH       = 1280
VIDEO_HEIGHT      = 720
FPS               = 24

# ─────────────────────────────────────────────────────────────
# 2.  Pydantic Schemas
# ─────────────────────────────────────────────────────────────


class GenerateRequest(BaseModel):
    text: str = Field(
        ...,
        min_length=10,
        max_length=2000,
        description="The story / script to turn into a video.",
    )


# ─────────────────────────────────────────────────────────────
# 3.  FastAPI App + CORS
# ─────────────────────────────────────────────────────────────

app = FastAPI(
    title="Text-to-Video API (Free Stack)",
    description="Convert any text into a narrated cinematic video. 100% Free.",
    version="3.0.0",
    docs_url="/docs",
)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=False,
    allow_methods=["*"],
    allow_headers=["*"],
)


# ─────────────────────────────────────────────────────────────
# 4.  Step 1 — Scene Scripting  (Gemini 1.5 Flash — FREE)
# ─────────────────────────────────────────────────────────────


import re

async def generate_scene_prompts(story_text: str) -> List[str]:
    """
    100% Local Scene Generation.
    Splits the story into 3 parts and formats them for the image generator.
    No API keys, no quotas, never fails.
    """
    log.info("🧠  Generating scene prompts locally (No API needed) …")
    
    # Clean text
    text = re.sub(r'\s+', ' ', story_text).strip()
    
    # Split into sentences
    sentences = [s.strip() for s in re.split(r'[.!?]', text) if len(s.strip()) > 3]
    
    # Fallback if no punctuation
    if len(sentences) == 0:
        sentences = [text]
        
    # Pad to at least 3 sentences
    while len(sentences) < 3:
        sentences.append(sentences[-1])
        
    # Divide into 3 chunks
    chunk_size = max(1, len(sentences) // 3)
    
    scene1 = " ".join(sentences[0:chunk_size])
    scene2 = " ".join(sentences[chunk_size:chunk_size*2])
    scene3 = " ".join(sentences[chunk_size*2:])
    
    scenes = [scene1, scene2, scene3]
    
    for i, s in enumerate(scenes, 1):
        log.info("   Scene %d: %s", i, s[:90])

    return scenes


# ─────────────────────────────────────────────────────────────
# 5.  Step 2 — Image Generation  (Pollinations.ai — FREE)
# ─────────────────────────────────────────────────────────────


async def generate_scene_image(prompt: str, scene_index: int, job_id: str) -> Path:
    """
    Generate a 1280×720 image from a prompt using Pollinations.ai.
    Completely free — no API key required.
    Includes retry logic to bypass 429 Too Many Requests.
    """
    log.info("🖼️  Generating image %d via Pollinations.ai …", scene_index)

    encoded_prompt = quote(f"{prompt}, cinematic, 8k, photorealistic")
    # Adding a random seed to bust caching and help bypass rate limits
    import random
    seed = random.randint(1, 999999)
    url = f"{POLLINATIONS_URL.format(prompt=encoded_prompt)}&seed={seed}"

    image_path = TEMP_DIR / f"{job_id}_scene_{scene_index}.jpg"

    max_retries = 3
    for attempt in range(max_retries):
        try:
            async with httpx.AsyncClient(timeout=120, follow_redirects=True) as client:
                resp = await client.get(url)
                if resp.status_code == 429:
                    log.warning("   ⚠️ 429 Too Many Requests. Retrying image %d in 5s... (Attempt %d/%d)", scene_index, attempt+1, max_retries)
                    await asyncio.sleep(5)
                    continue
                resp.raise_for_status()
                
                with open(image_path, "wb") as f:
                    f.write(resp.content)
                break  # Success! Exit retry loop
        except Exception as e:
            if attempt == max_retries - 1:
                raise e
            log.warning("   ⚠️ Error on image %d: %s. Retrying in 5s...", scene_index, e)
            await asyncio.sleep(5)

    log.info("   ✅ Image %d saved → %s  (%.1f KB)", scene_index, image_path, image_path.stat().st_size / 1024)
    return image_path


# ─────────────────────────────────────────────────────────────
# 6.  Step 3 — Voiceover  (Edge-TTS — FREE)
# ─────────────────────────────────────────────────────────────


async def generate_voiceover(story_text: str, job_id: str) -> Path:
    """Generate MP3 voiceover using Microsoft Edge-TTS (free)."""
    log.info("🎙️  Generating voiceover with Edge-TTS (Hindi) …")

    output_path = TEMP_DIR / f"{job_id}_voiceover.mp3"
    communicate = edge_tts.Communicate(
        text=story_text,
        voice="hi-IN-MadhurNeural",
        rate="-10%",
    )
    await communicate.save(str(output_path))

    log.info("   Voiceover saved → %.1f KB", output_path.stat().st_size / 1024)
    return output_path


# ─────────────────────────────────────────────────────────────
# 7.  Step 4 — Ken Burns Effect + Stitch + Audio  (MoviePy)
# ─────────────────────────────────────────────────────────────


def _make_clip(image_path: Path, duration: float, scene_index: int) -> ImageClip:
    """
    Creates a static image clip. 
    This renders 100x faster than calculating Ken Burns frame-by-frame in Python.
    """
    img = Image.open(str(image_path)).convert("RGB")
    img = img.resize((VIDEO_WIDTH, VIDEO_HEIGHT), Image.LANCZOS)
    img_array = np.array(img)

    clip = ImageClip(img_array, duration=duration)
    return clip.set_fps(FPS)


async def stitch_video_with_audio(
    image_paths: List[Path],
    voiceover_path: Path,
    job_id: str,
) -> Path:
    """Stitch animated image clips + attach voiceover → final MP4."""
    log.info("✂️   Stitching %d animated clips + attaching voiceover …", len(image_paths))

    output_path = OUTPUT_DIR / f"{job_id}_final.mp4"
    loop = asyncio.get_event_loop()

    def _moviepy_work() -> None:
        # Load voiceover to determine total duration
        voiceover = AudioFileClip(str(voiceover_path))
        total_duration = voiceover.duration

        # Divide voiceover duration equally across scenes
        clip_duration = total_duration / len(image_paths)
        log.info("   Voiceover: %.1fs  →  %.1fs per clip", total_duration, clip_duration)

        clips = []
        try:
            for i, img_path in enumerate(image_paths):
                clip = _make_clip(img_path, clip_duration, i)
                clips.append(clip)

            merged = concatenate_videoclips(clips, method="compose")
            final  = merged.set_audio(voiceover)

            final.write_videofile(
                str(output_path),
                codec="libx264",
                audio_codec="aac",
                temp_audiofile=str(TEMP_DIR / f"{job_id}_tmp.m4a"),
                remove_temp=True,
                fps=FPS,
                preset="fast",
                logger=None,
            )
            log.info(
                "   Final video → %s  (%.2f MB)",
                output_path,
                output_path.stat().st_size / (1024 * 1024),
            )
        finally:
            for c in clips:
                try:
                    c.close()
                except Exception:
                    pass

    await loop.run_in_executor(None, _moviepy_work)
    return output_path


# ─────────────────────────────────────────────────────────────
# 8.  Cleanup
# ─────────────────────────────────────────────────────────────


def _cleanup_temp_files(job_id: str) -> None:
    for p in TEMP_DIR.glob(f"{job_id}_*"):
        try:
            p.unlink()
        except Exception:
            pass


# ─────────────────────────────────────────────────────────────
# 9.  Main Endpoint  —  POST /generate-video
# ─────────────────────────────────────────────────────────────


@app.post("/generate-video", tags=["Video Generation"])
async def generate_video(payload: GenerateRequest) -> FileResponse:
    """
    100% FREE pipeline — no paid APIs required:
    1. Gemini 1.5 Flash  → 3 image prompts
    2. Pollinations.ai   → 3 HD images (parallel)
    3. Edge-TTS          → MP3 voiceover
    4. MoviePy           → Ken Burns animation + stitch + audio
    5. Return final MP4
    ⚡ ~30–60 seconds total
    """
    job_id = uuid.uuid4().hex[:12]
    log.info("═" * 60)
    log.info("🚀  Job [%s] started — %s…", job_id, payload.text[:50])
    t_start = time.perf_counter()

    try:
        # Step 1 — Scene prompts
        scene_prompts = await generate_scene_prompts(payload.text)

        # Step 2 + 3 — Voiceover and Images sequentially to avoid API limits
        log.info("⚡  Generating voiceover …")
        voiceover_path = await generate_voiceover(payload.text, job_id)

        log.info("⚡  Generating 3 images sequentially (to prevent 429 Too Many Requests) …")
        image_paths = []
        for i, prompt in enumerate(scene_prompts):
            try:
                img_path = await generate_scene_image(prompt, i + 1, job_id)
                image_paths.append(img_path)
                # Sleep briefly between requests to respect the free API limits
                if i < len(scene_prompts) - 1:
                    await asyncio.sleep(2)
            except Exception as e:
                raise HTTPException(status_code=500, detail=f"Image {i + 1} failed: {e}")

        # Step 4 — Stitch
        final_path = await stitch_video_with_audio(image_paths, voiceover_path, job_id)
        _cleanup_temp_files(job_id)

        elapsed = time.perf_counter() - t_start
        log.info("✅  Job [%s] done in %.1fs", job_id, elapsed)
        log.info("═" * 60)

        return FileResponse(
            path=str(final_path),
            media_type="video/mp4",
            filename=f"frameforge_{job_id}.mp4",
            headers={"X-Job-Id": job_id, "X-Processing-Time": f"{elapsed:.1f}s"},
        )

    except HTTPException:
        raise
    except Exception as exc:
        log.exception("❌  Job [%s] failed: %s", job_id, exc)
        _cleanup_temp_files(job_id)
        raise HTTPException(status_code=500, detail=f"Video generation failed: {str(exc)}")


# ─────────────────────────────────────────────────────────────
# 10.  Health Check
# ─────────────────────────────────────────────────────────────


@app.get("/health", tags=["System"])
async def health_check() -> dict:
    return {
        "status": "ok",
        "stack": "Gemini 1.5 Flash + Pollinations.ai + Edge-TTS + MoviePy",
        "cost": "$0.00 - 100% Free",
        "gemini_configured": bool(GEMINI_API_KEY),
    }


# ─────────────────────────────────────────────────────────────
# 11.  Dev Runner
# ─────────────────────────────────────────────────────────────

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(
        "main:app",
        host=os.getenv("HOST", "0.0.0.0"),
        port=int(os.getenv("PORT", "8000")),
        reload=True,
        log_level="info",
    )

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

import asyncio
import json
import logging
import os
import time
import uuid
from pathlib import Path
from typing import List, Optional, Dict, Any, Union, Tuple
from urllib.parse import quote

import edge_tts
import google.generativeai as genai
import httpx
import numpy as np
import base64
from gradio_client import Client, handle_file
from dotenv import load_dotenv
from fastapi import FastAPI, HTTPException, BackgroundTasks, UploadFile, File, Form
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse, JSONResponse
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
FPS               = 2      # Reduced FPS for static images to speed up rendering 10x

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
    style: str = Field(default="Photorealistic, Cinematic")
    quality: str = Field(default="720p")
    aspect_ratio: str = Field(default="16:9")


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


async def generate_scene_image(prompt: str, scene_index: int, job_id: str, style: str, width: int, height: int) -> Path:
    """
    Generate an image from a prompt using Pollinations.ai.
    Completely free — no API key required.
    Includes retry logic to bypass 429 Too Many Requests.
    """
    log.info("🖼️  Generating image %d via Pollinations.ai …", scene_index)

    encoded_prompt = quote(f"{prompt}, {style}")
    # Adding a random seed to bust caching and help bypass rate limits
    import random
    seed = random.randint(1, 999999)
    url = f"https://image.pollinations.ai/prompt/{encoded_prompt}?width={width}&height={height}&nologo=true&enhance=true&model=flux&seed={seed}"

    image_path = TEMP_DIR / f"{job_id}_scene_{scene_index}.jpg"

    max_retries = 3
    headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"}
    
    for attempt in range(max_retries):
        try:
            async with httpx.AsyncClient(timeout=120, follow_redirects=True, headers=headers) as client:
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


def _make_clip(image_path: Path, duration: float, scene_index: int, width: int, height: int) -> ImageClip:
    """
    Creates a static image clip. 
    This renders 100x faster than calculating Ken Burns frame-by-frame in Python.
    """
    img = Image.open(str(image_path)).convert("RGB")
    img = img.resize((width, height), Image.LANCZOS)
    img_array = np.array(img)

    clip = ImageClip(img_array, duration=duration)
    return clip.set_fps(FPS)


async def stitch_video_with_audio(
    image_paths: List[Path],
    voiceover_path: Path,
    job_id: str,
    width: int,
    height: int,
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
                clip = _make_clip(img_path, clip_duration, i, width, height)
                clips.append(clip)

            merged = concatenate_videoclips(clips, method="chain")
            final  = merged.set_audio(voiceover)

            final.write_videofile(
                str(output_path),
                codec="libx264",
                audio_codec="aac",
                temp_audiofile=str(TEMP_DIR / f"{job_id}_tmp.m4a"),
                remove_temp=True,
                fps=FPS,
                preset="ultrafast",
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

    # Determine dimensions based on quality and aspect ratio
    if payload.quality == "1080p":
        w, h = 1920, 1080
    else:
        w, h = 1280, 720
        
    if payload.aspect_ratio == "9:16":
        w, h = h, w

    try:
        # Step 1 — Scene prompts
        scene_prompts = await generate_scene_prompts(payload.text)

        # Step 2 + 3 — Voiceover and Images in parallel for 2x speedup
        log.info("⚡  Generating voiceover & images concurrently …")
        
        async def fetch_image_with_stagger(prompt: str, idx: int):
            # Light stagger to avoid burst rate limits
            await asyncio.sleep(idx * 0.4)
            return await generate_scene_image(prompt, idx + 1, job_id, payload.style, w, h)

        image_tasks = [fetch_image_with_stagger(p, i) for i, p in enumerate(scene_prompts)]
        voiceover_task = generate_voiceover(payload.text, job_id)

        # Execute voiceover and image downloads concurrently
        results = await asyncio.gather(voiceover_task, *image_tasks)
        voiceover_path = results[0]
        image_paths = list(results[1:])

        # Step 4 — Stitch video
        log.info("⚡  Stitching video …")
        final_path = await stitch_video_with_audio(image_paths, voiceover_path, job_id, w, h)
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
        "stack": "Gemini 1.5 Flash + Pollinations.ai + Edge-TTS + MoviePy + Replicate",
    }


# ─────────────────────────────────────────────────────────────
# 11.  Clothes Changer Endpoint
# ─────────────────────────────────────────────────────────────

@app.post("/change-clothes", tags=["Image Generation"])
async def change_clothes(
    image: UploadFile = File(...),
    prompt: str = Form(...)
):
    job_id = uuid.uuid4().hex[:12]
    log.info("👕  Job [%s] started Clothes Change: %s", job_id, prompt)
    
    try:
        # Save uploaded user image
        user_img_path = TEMP_DIR / f"{job_id}_user.jpg"
        with open(user_img_path, "wb") as f:
            f.write(await image.read())

        # 0. Optimize the prompt using Gemini for hyper-realism
        log.info("   Optimizing prompt using Gemini...")
        model = genai.GenerativeModel("gemini-flash-latest")
        gemini_prompt = f"""
        You are a professional fashion AI prompt engineer.
        The user wants to generate a picture of clothing based on this input: "{prompt}"
        
        Extract ONLY the description of the clothing itself. Remove any references to people (e.g. "for this person", "wear a").
        Format your response as a single, highly detailed, photorealistic prompt for an isolated piece of clothing.
        Keep it under 15 words.
        Example output: A stylish black winter coat, high-end designer, detailed texture
        """
        gemini_response = model.generate_content(gemini_prompt)
        optimized_prompt = gemini_response.text.strip().replace('\n', ' ')
        log.info("   Optimized Garment Prompt: %s", optimized_prompt)

        # 1. Generate the Garment Image using Pollinations.ai based on optimized text prompt
        log.info("   Generating garment image...")
        garment_prompt = quote(f"{optimized_prompt}, isolated flat lay on solid white background, fashion catalog photography")
        garment_url = f"https://image.pollinations.ai/prompt/{garment_prompt}?width=768&height=1024&nologo=true"
        
        garment_img_path = TEMP_DIR / f"{job_id}_garment.jpg"
        headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"}
        async with httpx.AsyncClient(timeout=60, follow_redirects=True, headers=headers) as client:
            resp = await client.get(garment_url)
            resp.raise_for_status()
            with open(garment_img_path, "wb") as f:
                f.write(resp.content)

        # 2. Run Free Hugging Face IDM-VTON
        log.info("   Running Hugging Face Virtual Try-On (Free)...")
        
        hf_client = Client("yisol/IDM-VTON", hf_token=os.getenv("HF_TOKEN"))
        
        human_dict = {
            "background": handle_file(str(user_img_path)),
            "layers": [],
            "composite": None
        }
        
        result = hf_client.predict(
            dict=human_dict,
            garm_img=handle_file(str(garment_img_path)),
            garment_des=prompt,
            is_checked=True,
            is_checked_crop=False,
            denoise_steps=30,
            seed=42,
            api_name="/tryon"
        )
        
        # Result is a tuple: (final_img_path, masked_img_path)
        final_img_path = result[0]
        
        # Convert to base64 so we can send it directly to the frontend without needing an image host
        with open(final_img_path, "rb") as image_file:
            encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
        
        final_image_url = f"data:image/webp;base64,{encoded_string}"
        
        log.info("✅  Clothes swapped successfully via Hugging Face!")
        
        # Cleanup
        _cleanup_temp_files(job_id)
        
        return JSONResponse(content={"image_url": final_image_url})
        
    except Exception as exc:
        log.exception("❌  Clothes Change failed: %s", exc)
        _cleanup_temp_files(job_id)
        raise HTTPException(status_code=500, detail=f"Failed to change clothes: {str(exc)}")


# ─────────────────────────────────────────────────────────────
# 12.  Video Variant Generator Endpoints
# ─────────────────────────────────────────────────────────────

from services.variant_generator import generate_video_variant_sync, probe_media_metadata
from services.fingerprint_analyzer import (
    analyze_audio_fingerprint,
    analyze_video_fingerprint,
    compare_media_fingerprints,
)
from services.smart_transform import derive_transform_params

@app.post("/api/variants/create", tags=["Media Variants"])
async def create_video_variant(
    file: UploadFile = File(...),
    resolution: str = Form("original"),
    fit_mode: str = Form("fit"),
    fps: str = Form("original"),
    quality: str = Form("balanced"),
    brightness: float = Form(0.0),
    contrast: float = Form(1.0),
    saturation: float = Form(1.0),
    gamma: float = Form(1.0),
    normalize_audio: bool = Form(True),
    audio_sample_rate: int = Form(48000),
    strip_metadata: bool = Form(True),
    # Deep visual & audio transforms (for own original media re-uploading)
    deep_visual: bool = Form(False),
    zoom_pct: float = Form(2.0),
    hue_shift_deg: float = Form(0.0),
    add_grain: bool = Form(False),
    pitch_shift_semitones: float = Form(0.0),
    time_stretch_pct: float = Form(0.0),
):
    job_id = uuid.uuid4().hex[:12]
    ext = Path(file.filename or "video.mp4").suffix or ".mp4"
    input_path = TEMP_DIR / f"{job_id}_orig{ext}"
    output_path = OUTPUT_DIR / f"variant_{job_id}.mp4"

    log.info("🎥 Variant creation request received: %s [%s]", file.filename, job_id)

    try:
        # Save original uploaded file safely
        with open(input_path, "wb") as f:
            while True:
                chunk = await file.read(1024 * 1024)
                if not chunk:
                    break
                f.write(chunk)

        # Offload CPU-bound FFmpeg rendering to worker thread
        loop = asyncio.get_event_loop()
        result = await loop.run_in_executor(
            None,
            lambda: generate_video_variant_sync(
                input_file=input_path,
                output_file=output_path,
                resolution=resolution,
                fit_mode=fit_mode,
                fps=fps,
                quality=quality,
                brightness=brightness,
                contrast=contrast,
                saturation=saturation,
                gamma=gamma,
                normalize_audio=normalize_audio,
                audio_sample_rate=audio_sample_rate,
                strip_metadata=strip_metadata,
                deep_visual=deep_visual,
                zoom_pct=zoom_pct,
                hue_shift_deg=hue_shift_deg,
                add_grain=add_grain,
                pitch_shift_semitones=pitch_shift_semitones,
                time_stretch_pct=time_stretch_pct,
            )
        )

        result["job_id"] = job_id
        result["variant_url"] = f"/api/media/{output_path.name}"
        result["download_url"] = f"/api/media/{output_path.name}"

        return JSONResponse(content=result)

    except Exception as exc:
        log.exception("❌ Variant generation failed: %s", exc)
        raise HTTPException(status_code=500, detail=f"Variant generation failed: {str(exc)}")
    finally:
        # Cleanup original upload in temp directory after processing
        if input_path.exists():
            try:
                input_path.unlink()
            except Exception:
                pass


# ─────────────────────────────────────────────────────────────
# 13.  Audio & Video Fingerprint Analyzer Endpoints
# ─────────────────────────────────────────────────────────────

@app.post("/api/fingerprints/analyze", tags=["Media Forensics"])
async def analyze_media_fingerprint(file: UploadFile = File(...)):
    job_id = uuid.uuid4().hex[:12]
    ext = Path(file.filename or "media.mp4").suffix or ".mp4"
    temp_path = TEMP_DIR / f"{job_id}_analyze{ext}"

    log.info("🔬 Fingerprint analysis request received: %s [%s]", file.filename, job_id)

    try:
        with open(temp_path, "wb") as f:
            while True:
                chunk = await file.read(1024 * 1024)
                if not chunk:
                    break
                f.write(chunk)

        loop = asyncio.get_event_loop()

        # Probe basic technical metadata
        meta = await loop.run_in_executor(None, lambda: probe_media_metadata(temp_path))

        # Perform acoustic signal analysis
        audio_analysis = await loop.run_in_executor(None, lambda: analyze_audio_fingerprint(temp_path))

        # Perform visual perceptual hashing & CV analysis
        video_analysis = await loop.run_in_executor(None, lambda: analyze_video_fingerprint(temp_path))

        return JSONResponse(content={
            "status": "success",
            "job_id": job_id,
            "filename": file.filename,
            "metadata": meta,
            "audio_fingerprint": audio_analysis,
            "video_fingerprint": video_analysis,
        })

    except Exception as exc:
        log.exception("❌ Fingerprint analysis failed: %s", exc)
        raise HTTPException(status_code=500, detail=f"Analysis failed: {str(exc)}")
    finally:
        if temp_path.exists():
            try:
                temp_path.unlink()
            except Exception:
                pass


@app.post("/api/fingerprints/compare", tags=["Media Forensics"])
async def compare_two_fingerprints(
    file_a: UploadFile = File(...),
    file_b: UploadFile = File(...),
):
    job_id = uuid.uuid4().hex[:12]
    ext_a = Path(file_a.filename or "file_a.mp4").suffix or ".mp4"
    ext_b = Path(file_b.filename or "file_b.mp4").suffix or ".mp4"
    path_a = TEMP_DIR / f"{job_id}_compare_a{ext_a}"
    path_b = TEMP_DIR / f"{job_id}_compare_b{ext_b}"

    log.info("⚖️ Dual fingerprint comparison requested: %s vs %s", file_a.filename, file_b.filename)

    try:
        with open(path_a, "wb") as fa:
            fa.write(await file_a.read())
        with open(path_b, "wb") as fb:
            fb.write(await file_b.read())

        loop = asyncio.get_event_loop()
        comparison = await loop.run_in_executor(
            None,
            lambda: compare_media_fingerprints(path_a, path_b)
        )

        comparison["job_id"] = job_id
        return JSONResponse(content=comparison)

    except Exception as exc:
        log.exception("❌ Media comparison failed: %s", exc)
        raise HTTPException(status_code=500, detail=f"Media comparison failed: {str(exc)}")
    finally:
        for p in (path_a, path_b):
            if p.exists():
                try:
                    p.unlink()
                except Exception:
                    pass


# ─────────────────────────────────────────────────────────────
# 14.  Smart Fingerprint Auto-Transform Endpoint
# ─────────────────────────────────────────────────────────────

@app.post("/api/fingerprints/smart-transform", tags=["Media Forensics"])
async def smart_fingerprint_transform(
    file: UploadFile = File(...),
    fingerprint_data: str = Form(None),
):
    """
    One-click Smart Auto-Transform:
    1. Read pre-computed or perform fast parallel fingerprint analysis
    2. Derive optimal transformation params from detected characteristics
    3. Re-encode a transformed variant with all parameters shifted
    4. Return fingerprint data + transform params + before/after comparison
    """
    job_id = uuid.uuid4().hex[:12]
    ext = Path(file.filename or "media.mp4").suffix or ".mp4"
    input_path = TEMP_DIR / f"{job_id}_smart_orig{ext}"
    output_path = OUTPUT_DIR / f"smart_variant_{job_id}.mp4"

    log.info("🎯 Smart Auto-Transform requested: %s [%s]", file.filename, job_id)

    try:
        with open(input_path, "wb") as f:
            while True:
                chunk = await file.read(1024 * 1024)
                if not chunk:
                    break
                f.write(chunk)

        loop = asyncio.get_event_loop()

        # Step 1 — Check for cached fingerprint data to eliminate redundant re-analysis
        meta, audio_fp, video_fp = None, None, None
        if fingerprint_data:
            try:
                cached = json.loads(fingerprint_data)
                if isinstance(cached, dict):
                    meta = cached.get("metadata")
                    audio_fp = cached.get("audio_fingerprint")
                    video_fp = cached.get("video_fingerprint")
                    log.info("  ⚡ Using cached fingerprint analysis (0.0s analysis time)")
            except Exception as e:
                log.warning("Could not parse cached fingerprint: %s", e)

        if not meta or not isinstance(meta, dict):
            meta = await loop.run_in_executor(None, lambda: probe_media_metadata(input_path))

        if not audio_fp or not isinstance(audio_fp, dict):
            audio_fp = await loop.run_in_executor(None, lambda: analyze_audio_fingerprint(input_path))

        if not video_fp or not isinstance(video_fp, dict):
            video_fp = await loop.run_in_executor(None, lambda: analyze_video_fingerprint(input_path))

        fingerprint_payload = {
            "metadata": meta,
            "audio_fingerprint": audio_fp,
            "video_fingerprint": video_fp,
        }

        # Step 2 — Derive transform params
        log.info("  🧠 Deriving smart transform params …")
        params = derive_transform_params(fingerprint_payload)

        # Step 3 — Generate transformed variant
        log.info("  Generating smart variant -> %s", output_path.name)
        transform_result = await loop.run_in_executor(
            None,
            lambda: generate_video_variant_sync(
                input_file=input_path,
                output_file=output_path,
                resolution=params["resolution"],
                fit_mode=params["fit_mode"],
                fps=params["fps"],
                quality=params["quality"],
                brightness=params["brightness"],
                contrast=params["contrast"],
                saturation=params["saturation"],
                gamma=params["gamma"],
                normalize_audio=params["normalize_audio"],
                audio_sample_rate=params["audio_sample_rate"],
                strip_metadata=params["strip_metadata"],
                # Deep visual transforms
                deep_visual=params.get("deep_visual", True),
                zoom_pct=params.get("zoom_pct", 2.0),
                hue_shift_deg=params.get("hue_shift_deg", 0.0),
                add_grain=params.get("add_grain", False),
                # Deep audio transforms
                pitch_shift_semitones=params.get("pitch_shift_semitones", 0.0),
                time_stretch_pct=params.get("time_stretch_pct", 0.0),
            )
        )

        log.info("  ✅ Smart variant ready: %s", output_path.name)

        return JSONResponse(content={
            "status": "success",
            "job_id": job_id,
            "filename": file.filename,
            "metadata": meta,
            "audio_fingerprint": audio_fp,
            "video_fingerprint": video_fp,
            "auto_transform_params": params,
            "transform_result": transform_result,
            "output_filename": f"smart_variant_{job_id}.mp4",
            "download_url": f"/api/media/smart_variant_{job_id}.mp4",
        })

    except Exception as exc:
        log.exception("❌ Smart transform failed: %s", exc)
        raise HTTPException(status_code=500, detail=f"Smart transform failed: {str(exc)}")
    finally:
        if input_path.exists():
            try:
                input_path.unlink()
            except Exception:
                pass


# ─────────────────────────────────────────────────────────────
# 15.  Media File Serving Endpoint
# ─────────────────────────────────────────────────────────────

@app.get("/api/media/{filename}", tags=["System"])
async def serve_media_file(filename: str):
    # Sanitize filename
    safe_name = os.path.basename(filename)
    file_path = OUTPUT_DIR / safe_name

    if not file_path.exists():
        raise HTTPException(status_code=404, detail="Requested media file not found.")

    media_type = "video/mp4"
    if safe_name.endswith(".mp3"):
        media_type = "audio/mpeg"
    elif safe_name.endswith(".jpg") or safe_name.endswith(".jpeg"):
        media_type = "image/jpeg"

    return FileResponse(
        path=str(file_path),
        media_type=media_type,
        filename=safe_name,
    )


# ─────────────────────────────────────────────────────────────
# 12.  Dev Runner
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

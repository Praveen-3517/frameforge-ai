# 🎬 FrameForge AI — One-Click AI Tools & Media Forensics Suite

> Multi-modal AI media engine featuring Text-to-Video synthesis, AI Virtual Try-On, Video Variant Generator & Perceptual Forensic Fingerprint Suite. 100% Free-Tier Architecture.

---

## ✨ Tools & Capabilities

1. **Text-to-Video Engine (`/video`)**: Turn any text story into a cinematic, fully narrated MP4 video using Gemini Flash, Pollinations FLUX, Microsoft Edge-TTS, and MoviePy.
2. **AI Virtual Try-On (`/clothes`)**: Swap garments and virtual outfits on full-body photos while preserving pose and lighting via Hugging Face IDM-VTON.
3. **Create New Video Variant (`/variant`)**: Re-encode, re-scale, color grade, normalize (EBU R128), and apply Deep Perceptual Transforms (zoom+crop, hue rotation, film grain, pitch shift, time stretch) for legitimate cross-platform re-purposing of user-owned media.
4. **Audio & Video Fingerprint Analyzer (`/fingerprint`)**: Forensic media analysis extracting PCM waveforms, 7-band FFT spectrums, BPM tempo, perceptual dHash streams, dominant color palettes, scene cuts, and dual-media cross-correlation matching with One-Click Smart Auto-Transform.

---

## 🛠️ Architecture & Free-Tier Tech Stack

| Layer | Technology | Cost |
|---|---|---|
| **Backend** | FastAPI + Uvicorn + Python 3.10+ | Free / Open-Source |
| **Video Scripting** | Deterministic Chunking / Gemini 1.5 Flash | Free Tier |
| **Image Synthesis** | Pollinations.ai (FLUX Model) | 100% Free (No API Key) |
| **Voiceover Synthesis**| Microsoft Edge-TTS (`hi-IN-MadhurNeural`) | 100% Free (No API Key) |
| **Virtual Dressing** | Hugging Face Spaces (`yisol/IDM-VTON`) | Free Public Space |
| **Signal Forensics** | SciPy (FFT) + OpenCV (dHash / K-Means) | Local / Zero Cost |
| **Video Re-encoding**| FFmpeg 7.1 Multi-Threaded Static | Local / Zero Cost |
| **Frontend** | React 18 + Vite 5 + Tailwind CSS v3 | Open-Source |

---

## 🚀 Quick Start (Local Run)

### 1. Backend

```bash
cd backend
python -m venv .venv
.venv\Scripts\activate       # Windows (.venv/bin/activate on Linux/Mac)
pip install -r requirements.txt
python main.py
# Backend live at: http://localhost:8000
# Swagger API docs: http://localhost:8000/docs
```

### 2. Frontend

```bash
cd frontend
npm install
npm run dev
# Frontend live at: http://localhost:5173
```

---

## 🌐 Deploying to Production (Render / Railway / Vercel)

### Backend (Render / Railway):
- **Build Command:** `pip install -r backend/requirements.txt`
- **Start Command:** `uvicorn main:app --host 0.0.0.0 --port $PORT --app-dir backend`
- **Environment Variables:** `OUTPUT_DIR=outputs`, `TEMP_DIR=temp`, `FRONTEND_ORIGIN=*`

### Frontend (Vercel / Netlify):
- **Root Directory:** `frontend`
- **Build Command:** `npm run build`
- **Output Directory:** `dist`
- **Environment Variables:** `VITE_API_URL=<your-deployed-backend-url>`

---

## 🔒 Security & Privacy Notice
- All secrets are managed strictly in `backend/.env` (excluded from git).
- Generated variants and uploads are saved locally/ephemerally and cleaned up automatically.


# 🎬 FrameForge AI — Text to Video Generator

> Transform any text or story into a fully narrated, cinematic MP4 video using AI.

Built with **FastAPI · GPT-4o · OpenAI TTS · Replicate (Wan2.1) · MoviePy · React · Tailwind CSS**

---

## ✨ How It Works

```
Your Text
   │
   ├─ Step 1  GPT-4o        → 3 cinematic scene prompts
   │
   ├─ Step 2  OpenAI TTS    → MP3 voiceover narration       ┐  (parallel)
   ├─ Step 3  Replicate AI  → 3 short video clips (MP4)     ┘
   │
   ├─ Step 4  MoviePy       → Stitch clips + merge audio
   │
   └─ Output               → Final narrated MP4
```

---

## 📁 Project Structure

```
AI tool/
├── backend/
│   ├── main.py              ← FastAPI app (all pipeline logic)
│   ├── requirements.txt     ← Python deps
│   └── .env.example         ← API key template
└── frontend/
    ├── src/
    │   ├── App.jsx           ← Main app shell & state machine
    │   ├── index.css         ← Global design system
    │   ├── main.jsx          ← React entry point
    │   └── components/
    │       ├── Hero.jsx          ← Animated hero section
    │       ├── TextInput.jsx     ← Story textarea + examples
    │       ├── PipelineSteps.jsx ← Live step progress tracker
    │       ├── VideoPlayer.jsx   ← Custom MP4 player + download
    │       ├── ErrorBanner.jsx   ← Error display
    │       └── StarField.jsx     ← Animated star background
    ├── index.html
    ├── package.json
    ├── vite.config.js
    ├── tailwind.config.js
    └── postcss.config.js
```

---

## 🚀 Quick Start

### 1. Backend

```bash
cd backend

# Create & activate virtualenv
python -m venv .venv
.venv\Scripts\activate          # Windows
# source .venv/bin/activate     # macOS/Linux

# Install dependencies
pip install -r requirements.txt

# Set up environment
copy .env.example .env
# → Fill in OPENAI_API_KEY and REPLICATE_API_TOKEN in .env

# Start the server
python main.py
# API live at:   http://localhost:8000
# Swagger docs:  http://localhost:8000/docs
```

### 2. Frontend

```bash
cd frontend

# Install dependencies (already done)
npm install

# Start dev server
npm run dev
# App live at: http://localhost:5173
```

---

## 🔑 API Keys Required

| Key | Where to Get |
|---|---|
| `OPENAI_API_KEY` | [platform.openai.com/api-keys](https://platform.openai.com/api-keys) |
| `REPLICATE_API_TOKEN` | [replicate.com/account/api-tokens](https://replicate.com/account/api-tokens) |

> ⚠️ Never commit your `.env` file. It is already in `.gitignore`.

---

## 📡 API Reference

### `POST /generate-video`

**Request:**
```json
{ "text": "A lone astronaut discovers a glowing artifact on Mars..." }
```

**Response:** Raw MP4 binary stream (`video/mp4`)

**Headers returned:**
- `X-Job-Id` — Unique job identifier
- `X-Processing-Time` — Total server-side time in seconds

### `GET /health`

```json
{
  "status": "ok",
  "openai_configured": true,
  "replicate_configured": true,
  "output_dir": "..."
}
```

---

## ⚙️ Tech Stack

| Layer | Technology |
|---|---|
| Backend Framework | FastAPI + Uvicorn |
| Scene Writing | OpenAI GPT-4o |
| Text-to-Speech | OpenAI TTS (`tts-1-hd`, voice: `onyx`) |
| Video Generation | Replicate — `wan-video/wan2.1-t2v-480p` |
| Video Processing | MoviePy + imageio-ffmpeg |
| Frontend | React 18 + Vite |
| Styling | Tailwind CSS v3 |
| HTTP Client | Axios |
| Icons | Lucide React |

---

## 🎨 UI Features

- 🌌 **Cosmic dark-mode** design with animated star field and ambient orbs
- 🪟 **Glassmorphism** cards with subtle borders and glow effects
- 📊 **Live pipeline tracker** — 4-step progress indicator during generation
- 🎥 **Custom video player** — gradient progress bar, play/pause/mute/fullscreen
- ⬇️ **One-click download** of the final MP4
- 📝 **3 example prompts** to get started instantly
- 📱 **Fully responsive** layout

---

## 🔧 Troubleshooting

| Problem | Fix |
|---|---|
| `OPENAI_API_KEY not set` | Add key to `backend/.env` |
| `REPLICATE_API_TOKEN not set` | Add token to `backend/.env` |
| Timeout error | Replicate can be slow. The 15-min timeout should cover it. |
| `moviepy` error | Ensure `ffmpeg` is installed: `pip install imageio-ffmpeg` |
| CORS error | Check `FRONTEND_ORIGIN` in `.env` matches your Vite port |

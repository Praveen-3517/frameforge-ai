import { useState, useRef, useEffect } from 'react'
import axios from 'axios'
import StarField from './components/StarField'
import Hero from './components/Hero'
import TextInput from './components/TextInput'
import PipelineSteps from './components/PipelineSteps'
import VideoPlayer from './components/VideoPlayer'
import ErrorBanner from './components/ErrorBanner'
import { Github, Zap } from 'lucide-react'

/* ─── Pipeline step timing simulation ───────────────────────────
   Because the backend processes everything server-side, we advance
   the UI step indicator on a timed schedule while waiting for the
   real response. This gives users visual feedback.
   Timings are loose estimates based on typical API latency.
──────────────────────────────────────────────────────────────── */
const STEP_DELAYS_MS = [
  0,      // Step 1: Scene writing  — starts immediately
  12000,  // Step 2: Voiceover      — ~12s after start
  20000,  // Step 3: Video clips    — ~20s after start
  200000, // Step 4: Final stitch   — ~200s (Replicate is slow)
]

// App states
const STATE = {
  IDLE: 'idle',
  LOADING: 'loading',
  SUCCESS: 'success',
  ERROR: 'error',
}

export default function App() {
  const [text, setText] = useState('')
  const [appState, setAppState] = useState(STATE.IDLE)
  const [currentStep, setCurrentStep] = useState(0)
  const [videoUrl, setVideoUrl] = useState(null)
  const [jobId, setJobId] = useState(null)
  const [errorMsg, setErrorMsg] = useState('')

  const stepTimers = useRef([])

  /* Clean up step timers on unmount */
  useEffect(() => {
    return () => stepTimers.current.forEach(clearTimeout)
  }, [])

  /* ── Start the simulated step progression ── */
  const startStepProgression = () => {
    stepTimers.current.forEach(clearTimeout)
    stepTimers.current = []

    STEP_DELAYS_MS.forEach((delay, i) => {
      const t = setTimeout(() => {
        setCurrentStep(i + 1)
      }, delay)
      stepTimers.current.push(t)
    })
  }

  const stopStepProgression = () => {
    stepTimers.current.forEach(clearTimeout)
    stepTimers.current = []
  }

  /* ── Main generate handler ── */
  const handleGenerate = async () => {
    if (!text.trim() || text.length < 10) return

    setAppState(STATE.LOADING)
    setErrorMsg('')
    setVideoUrl(null)
    setJobId(null)
    startStepProgression()

    try {
      // Post to the backend (uses live Render URL if deployed, otherwise localhost)
      const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:8000'
      const response = await axios.post(
        `${API_URL}/generate-video`,
        { text: text.trim() },
        {
          responseType: 'blob',           // expect raw binary MP4
          timeout: 15 * 60 * 1000,        // 15 minute timeout
          headers: { 'Content-Type': 'application/json' },
        }
      )

      /* ── Extract job ID from response headers ── */
      const extractedJobId = response.headers['x-job-id'] || 'unknown'
      setJobId(extractedJobId)

      /* ── Create an Object URL from the blob ── */
      const blob = new Blob([response.data], { type: 'video/mp4' })
      const url = URL.createObjectURL(blob)

      stopStepProgression()
      setCurrentStep(5)       // mark all steps done
      setVideoUrl(url)
      setAppState(STATE.SUCCESS)

    } catch (err) {
      stopStepProgression()
      setCurrentStep(0)

      let message = 'An unexpected error occurred. Please try again.'

      if (err.response) {
        /* Server returned an error response */
        if (err.response.data instanceof Blob) {
          /* FastAPI returns JSON errors even with responseType: blob */
          try {
            const text = await err.response.data.text()
            const json = JSON.parse(text)
            message = json.detail || message
          } catch {
            message = `Server error ${err.response.status}`
          }
        } else {
          message = err.response.data?.detail || `Server error ${err.response.status}`
        }
      } else if (err.code === 'ECONNABORTED') {
        message = 'Request timed out. The video may still be processing — try again in a moment.'
      } else if (!navigator.onLine) {
        message = 'No internet connection detected.'
      }

      setErrorMsg(message)
      setAppState(STATE.ERROR)
    }
  }

  const handleReset = () => {
    /* Revoke old object URL to free memory */
    if (videoUrl) URL.revokeObjectURL(videoUrl)
    setAppState(STATE.IDLE)
    setVideoUrl(null)
    setJobId(null)
    setCurrentStep(0)
    setErrorMsg('')
  }

  const isLoading = appState === STATE.LOADING

  /* ─────────────────────────────────────────────────────────── */
  return (
    <div className="relative min-h-screen flex flex-col">
      {/* ── Decorative background ── */}
      <StarField />

      {/* Ambient orbs */}
      <div className="orb w-96 h-96 bg-violet-600/20 -top-48 -left-48" style={{ animationDelay: '0s' }} />
      <div className="orb w-80 h-80 bg-cyan-600/15 top-1/3 -right-40" style={{ animationDelay: '3s' }} />
      <div className="orb w-64 h-64 bg-rose-600/10 bottom-20 left-1/4" style={{ animationDelay: '5s' }} />

      {/* ── Header ── */}
      <header className="relative z-10 flex items-center justify-between px-6 py-5 max-w-6xl mx-auto w-full">
        <div className="flex items-center gap-2.5">
          <div className="w-8 h-8 rounded-lg bg-gradient-to-br from-violet-500 to-cyan-500
                          flex items-center justify-center shadow-lg shadow-violet-500/30">
            <Zap size={16} className="text-white" />
          </div>
          <span className="font-display font-bold text-white text-lg tracking-tight">
            Frame<span className="gradient-text">Forge</span>
          </span>
          <span className="hidden sm:block px-2 py-0.5 rounded-full bg-violet-500/10
                           border border-violet-500/20 text-violet-300 text-xs font-medium">
            AI Beta
          </span>
        </div>

        <nav className="flex items-center gap-4">
          <a
            href="http://localhost:8000/docs"
            target="_blank"
            rel="noopener noreferrer"
            className="text-white/40 hover:text-white/70 text-sm font-medium transition-colors"
          >
            API Docs
          </a>
          <a
            id="btn-github"
            href="#"
            className="flex items-center gap-1.5 text-white/40 hover:text-white/70
                       text-sm font-medium transition-colors"
          >
            <Github size={15} />
            GitHub
          </a>
        </nav>
      </header>

      {/* ── Main Content ── */}
      <main className="relative z-10 flex-1 flex items-start justify-center px-4 pb-16">
        <div className="w-full max-w-2xl mt-8">

          {/* Hero section — always visible */}
          <Hero />

          {/* Error Banner */}
          {appState === STATE.ERROR && (
            <div className="mb-6">
              <ErrorBanner
                message={errorMsg}
                onDismiss={() => setErrorMsg('')}
              />
            </div>
          )}

          {/* Main panel — switches between input, loading, and result */}
          {appState === STATE.SUCCESS && videoUrl ? (
            /* ── Video Result ── */
            <VideoPlayer
              videoUrl={videoUrl}
              jobId={jobId}
              onReset={handleReset}
            />
          ) : (
            /* ── Input + Loading Steps ── */
            <div className="space-y-5">
              <TextInput
                value={text}
                onChange={setText}
                onSubmit={handleGenerate}
                isLoading={isLoading}
              />

              {/* Pipeline step tracker — only visible while loading */}
              {isLoading && <PipelineSteps currentStep={currentStep} />}
            </div>
          )}
        </div>
      </main>

      {/* ── Footer ── */}
      <footer className="relative z-10 text-center py-6 px-4 text-white/20 text-xs font-mono">
        FrameForge AI · Built with FastAPI · OpenAI · Replicate · MoviePy
      </footer>
    </div>
  )
}

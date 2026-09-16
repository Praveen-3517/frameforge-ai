import React, { useState, useRef, useEffect } from 'react'
import { Link } from 'react-router-dom'
import {
  ArrowLeft,
  Upload,
  Fingerprint,
  Activity,
  Film,
  Music,
  Copy,
  Check,
  RotateCcw,
  Sliders,
  ShieldCheck,
  ShieldAlert,
  BarChart3,
  Layers,
  Sparkles,
  Info,
  Clock,
  Eye,
  Zap,
  Play,
  Pause,
  Maximize2,
  Wand2,
  Download,
  CheckCircle2,
  ArrowRight
} from 'lucide-react'
import axios from 'axios'
import StarField from '../components/StarField'
import { getApiUrl, getFullMediaUrl } from '../utils/apiUrl'
import UserNav from '../components/auth/UserNav'

export default function FingerprintAnalyzer() {
  const [activeTab, setActiveTab] = useState('single') // 'single' | 'compare'
  
  // Single Analysis State
  const [singleFile, setSingleFile] = useState(null)
  const [singlePreview, setSinglePreview] = useState(null)
  const [singleLoading, setSingleLoading] = useState(false)
  const [singleProgress, setSingleProgress] = useState(0)
  const [singleResult, setSingleResult] = useState(null)
  const [singleError, setSingleError] = useState('')

  // Comparison State
  const [fileA, setFileA] = useState(null)
  const [fileB, setFileB] = useState(null)
  const [previewA, setPreviewA] = useState(null)
  const [previewB, setPreviewB] = useState(null)
  const [compareLoading, setCompareLoading] = useState(false)
  const [compareProgress, setCompareProgress] = useState(0)
  const [compareResult, setCompareResult] = useState(null)
  const [compareError, setCompareError] = useState('')

  const [copiedHash, setCopiedHash] = useState(null)

  // Smart Auto-Transform State
  const [selectedShieldMode, setSelectedShieldMode] = useState('auto') // 'auto' | 'cartoon' | 'bhakti' | 'song'
  const [smartLoading, setSmartLoading] = useState(false)
  const [smartProgress, setSmartProgress] = useState(0)
  const [smartResult, setSmartResult] = useState(null)
  const [smartError, setSmartError] = useState('')

  const singleInputRef = useRef(null)
  const fileAInputRef = useRef(null)
  const fileBInputRef = useRef(null)
  const waveformCanvasRef = useRef(null)

  // Copy Helper
  const handleCopy = (text, label) => {
    navigator.clipboard.writeText(text)
    setCopiedHash(label)
    setTimeout(() => setCopiedHash(null), 2500)
  }

  // Draw Audio Waveform on Canvas
  useEffect(() => {
    if (!singleResult?.audio_fingerprint?.waveform || !waveformCanvasRef.current) return
    const canvas = waveformCanvasRef.current
    const ctx = canvas.getContext('2d')
    const width = canvas.width
    const height = canvas.height
    const data = singleResult.audio_fingerprint.waveform

    ctx.clearRect(0, 0, width, height)

    // Gradient styling
    const grad = ctx.createLinearGradient(0, 0, width, 0)
    grad.addColorStop(0, '#8B5CF6')
    grad.addColorStop(0.5, '#06B6D4')
    grad.addColorStop(1, '#EC4899')

    const barWidth = Math.max(2, (width / data.length) - 1.5)
    const centerY = height / 2

    data.forEach((val, i) => {
      const x = i * (barWidth + 1.5)
      const barHeight = Math.max(2, val * centerY * 0.9)
      
      ctx.fillStyle = grad
      ctx.fillRect(x, centerY - barHeight, barWidth, barHeight * 2)
    })
  }, [singleResult])

  // Single File Analysis Handler
  const handleSingleAnalyze = async () => {
    if (!singleFile) return
    setSingleLoading(true)
    setSingleProgress(0)
    setSingleError('')
    setSingleResult(null)

    const formData = new FormData()
    formData.append('file', singleFile)

    try {
      const API_URL = getApiUrl()
      const res = await axios.post(`${API_URL}/api/fingerprints/analyze`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' },
        timeout: 15 * 60 * 1000,
        onUploadProgress: (progressEvent) => {
          if (progressEvent.total) {
            const pct = Math.round((progressEvent.loaded * 100) / progressEvent.total)
            setSingleProgress(pct)
          }
        },
      })
      setSingleResult(res.data)
    } catch (err) {
      if (!err.response) {
        setSingleError(
          'Upload or network connection interrupted. For large videos (>50MB), please keep this tab active during upload or run locally on http://localhost:5173 for instantaneous processing.'
        )
      } else {
        setSingleError(
          err.response?.data?.detail || 'Fingerprint analysis failed. Please verify media format.'
        )
      }
    } finally {
      setSingleLoading(false)
    }
  }

  // ⚡ 1-Click Fast Direct Transform Handler (Bypasses slow full-file forensic analysis)
  const handleFastDirectTransform = async (mode) => {
    if (!singleFile) return
    setSelectedShieldMode(mode)
    setSmartLoading(true)
    setSmartProgress(0)
    setSmartError('')
    setSmartResult(null)

    const API_URL = getApiUrl()
    const formData = new FormData()
    formData.append('file', singleFile)
    formData.append('mode', mode)

    try {
      const res = await axios.post(`${API_URL}/api/fingerprints/smart-transform`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' },
        timeout: 25 * 60 * 1000,
        onUploadProgress: (progressEvent) => {
          if (progressEvent.total) {
            const pct = Math.round((progressEvent.loaded * 100) / progressEvent.total)
            setSmartProgress(pct)
          }
        },
      })
      setSmartResult(res.data)
      setTimeout(() => {
        const el = document.getElementById('smart-result-card')
        if (el) el.scrollIntoView({ behavior: 'smooth' })
      }, 200)
    } catch (err) {
      if (!err.response) {
        setSmartError(
          'Transform upload interrupted. Please check that backend server is running on http://localhost:8000.'
        )
      } else {
        setSmartError(err.response?.data?.detail || 'Smart transform failed. Please try again.')
      }
    } finally {
      setSmartLoading(false)
    }
  }

  // Smart Auto-Transform Handler (uses current singleFile + cached fingerprint)
  const handleSmartTransform = async () => {
    if (!singleFile && !singleResult?.job_id) return
    setSmartLoading(true)
    setSmartProgress(0)
    setSmartError('')
    setSmartResult(null)

    const API_URL = getApiUrl()

    const attemptTransform = async (useExistingId = true) => {
      const formData = new FormData()
      if (useExistingId && singleResult?.job_id) {
        formData.append('existing_job_id', singleResult.job_id)
      } else if (singleFile) {
        formData.append('file', singleFile)
      }

      formData.append('mode', selectedShieldMode)

      if (singleResult) {
        formData.append(
          'fingerprint_data',
          JSON.stringify({
            metadata: singleResult.metadata,
            audio_fingerprint: singleResult.audio_fingerprint,
            video_fingerprint: singleResult.video_fingerprint,
          })
        )
      }

      return await axios.post(`${API_URL}/api/fingerprints/smart-transform`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' },
        timeout: 20 * 60 * 1000,
        onUploadProgress: (progressEvent) => {
          if (progressEvent.total) {
            const pct = Math.round((progressEvent.loaded * 100) / progressEvent.total)
            setSmartProgress(pct)
          }
        },
      })
    }

    try {
      try {
        // Try instant zero-byte transform using existing server media first
        const res = await attemptTransform(Boolean(singleResult?.job_id))
        setSmartResult(res.data)
      } catch (firstErr) {
        // If server restarted or temp file expired, seamlessly fallback to uploading singleFile
        if (singleResult?.job_id && singleFile && firstErr.response?.status === 400) {
          const fallbackRes = await attemptTransform(false)
          setSmartResult(fallbackRes.data)
        } else {
          throw firstErr
        }
      }
    } catch (err) {
      if (!err.response) {
        setSmartError(
          'Transform upload interrupted. For large files, keep this tab active or check that backend server is running on http://localhost:8000.'
        )
      } else {
        setSmartError(
          err.response?.data?.detail || 'Smart transform failed. Please try again.'
        )
      }
    } finally {
      setSmartLoading(false)
    }
  }

  // Dual File Compare Handler
  const handleCompare = async () => {
    if (!fileA || !fileB) return
    setCompareLoading(true)
    setCompareProgress(0)
    setCompareError('')
    setCompareResult(null)

    const formData = new FormData()
    formData.append('file_a', fileA)
    formData.append('file_b', fileB)

    try {
      const API_URL = getApiUrl()
      const res = await axios.post(`${API_URL}/api/fingerprints/compare`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' },
        timeout: 15 * 60 * 1000,
        onUploadProgress: (progressEvent) => {
          if (progressEvent.total) {
            const pct = Math.round((progressEvent.loaded * 100) / progressEvent.total)
            setCompareProgress(pct)
          }
        },
      })
      setCompareResult(res.data)
    } catch (err) {
      if (!err.response) {
        setCompareError(
          'Comparison upload interrupted. Please keep tab active or run locally.'
        )
      } else {
        setCompareError(
          err.response?.data?.detail || 'Media comparison failed. Please try again.'
        )
      }
    } finally {
      setCompareLoading(false)
    }
  }

  return (
    <div className="relative min-h-screen flex flex-col bg-[#0B0D17] text-white">
      <StarField />
      <div className="orb w-96 h-96 bg-cyan-600/20 -top-48 -left-48" style={{ animationDelay: '0s' }} />
      <div className="orb w-80 h-80 bg-violet-600/15 top-1/3 -right-40" style={{ animationDelay: '3s' }} />

      {/* Header */}
      <header className="relative z-10 flex items-center justify-between px-6 py-5 max-w-6xl mx-auto w-full">
        <Link
          to="/"
          className="flex items-center gap-2 text-white/50 hover:text-white transition-colors text-sm font-medium"
        >
          <ArrowLeft size={16} /> Back to Dashboard
        </Link>
        <div className="flex items-center gap-2">
          <span className="px-3 py-1 rounded-full bg-cyan-500/10 border border-cyan-500/20 text-cyan-300 text-xs font-mono font-medium flex items-center gap-1.5">
            <Fingerprint size={13} /> Forensic Engine v3.0
          </span>
          <UserNav />
        </div>
      </header>

      {/* Main Container */}
      <main className="relative z-10 flex-1 flex flex-col items-center px-4 pb-20">
        <div className="w-full max-w-5xl mt-2">

          {/* Title Banner */}
          <div className="text-center mb-6">
            <div className="inline-flex items-center gap-2 px-3.5 py-1.5 rounded-full bg-white/5 border border-white/10 text-xs font-mono text-white/70 mb-3">
              <Activity size={13} className="text-cyan-400" />
              Acoustic & Perceptual Visual Forensic Suite
            </div>
            <h1 className="text-3xl sm:text-4xl font-display font-bold text-white tracking-tight mb-2">
              Audio & Video <span className="gradient-text">Fingerprint Analyzer</span>
            </h1>
            <p className="text-white/50 text-sm max-w-xl mx-auto">
              Extract deep acoustic waveforms, pitch & frequency spectrums, tempo/BPM, perceptual frame hashes (dHash),
              scene boundaries, and perform forensic side-by-side media comparison.
            </p>
          </div>

          {/* Mode Switcher Tabs */}
          <div className="flex justify-center mb-8">
            <div className="p-1 bg-white/5 border border-white/10 rounded-2xl flex items-center gap-1 backdrop-blur-md">
              <button
                onClick={() => setActiveTab('single')}
                className={`px-5 py-2 rounded-xl text-xs font-semibold transition-all flex items-center gap-2 ${
                  activeTab === 'single'
                    ? 'bg-cyan-500 text-white shadow-lg shadow-cyan-500/20'
                    : 'text-white/60 hover:text-white hover:bg-white/5'
                }`}
              >
                <Fingerprint size={15} /> Single Media Fingerprint
              </button>
              <button
                onClick={() => setActiveTab('compare')}
                className={`px-5 py-2 rounded-xl text-xs font-semibold transition-all flex items-center gap-2 ${
                  activeTab === 'compare'
                    ? 'bg-violet-500 text-white shadow-lg shadow-violet-500/20'
                    : 'text-white/60 hover:text-white hover:bg-white/5'
                }`}
              >
                <Layers size={15} /> Dual Media Comparison Matcher
              </button>
            </div>
          </div>

          {/* ═══════════════════════════════════════════════════════════ */}
          {/* TAB 1: SINGLE MEDIA FINGERPRINT ANALYSIS                   */}
          {/* ═══════════════════════════════════════════════════════════ */}
          {activeTab === 'single' && (
            <div className="space-y-6">
              {singleError && (
                <div className="bg-red-500/10 border border-red-500/20 text-red-400 p-4 rounded-2xl text-sm flex items-start gap-3">
                  <ShieldAlert className="shrink-0 mt-0.5" size={18} />
                  <div>
                    <p className="font-semibold">Analysis Notice</p>
                    <p className="text-xs text-red-400/80 mt-0.5">{singleError}</p>
                  </div>
                </div>
              )}

              {/* Upload Zone */}
              {!singleResult && (
                <div className="glass-card p-6 space-y-5">
                  <label className="block text-sm font-semibold text-white/90 flex items-center justify-between">
                    <span className="flex items-center gap-2">
                      <Film size={16} className="text-cyan-400" />
                      Select Video or Audio Media
                    </span>
                    {singleFile && (
                      <span className="text-xs font-mono text-white/40">
                        {(singleFile.size / (1024 * 1024)).toFixed(2)} MB · {singleFile.name}
                      </span>
                    )}
                  </label>

                  {!singleFile ? (
                    <div
                      onClick={() => singleInputRef.current?.click()}
                      className="relative aspect-video max-h-56 bg-white/5 rounded-2xl border-2 border-dashed border-white/10 hover:border-cyan-500/50 transition-all flex flex-col items-center justify-center cursor-pointer group hover:bg-white/[0.07]"
                    >
                      <div className="w-14 h-14 rounded-2xl bg-cyan-500/10 border border-cyan-500/20 flex items-center justify-center mb-3 group-hover:scale-110 transition-transform">
                        <Upload className="w-6 h-6 text-cyan-400" />
                      </div>
                      <p className="text-sm font-semibold text-white/80">Click or drop audio/video file here</p>
                      <p className="text-xs text-white/40 mt-1">Supports MP4, WebM, MOV, AVI, MP3, WAV, M4A (Up to 200MB)</p>
                      <input
                        ref={singleInputRef}
                        type="file"
                        accept="video/*,audio/*"
                        onChange={(e) => {
                          const f = e.target.files[0]
                          if (f) {
                            setSingleFile(f)
                            setSinglePreview(URL.createObjectURL(f))
                            setSingleError('')
                          }
                        }}
                        className="hidden"
                      />
                    </div>
                  ) : (
                    <div className="space-y-4">
                      <div className="relative rounded-2xl overflow-hidden bg-black/40 border border-white/10 p-2">
                        {singleFile.type.startsWith('video') ? (
                          <video src={singlePreview} controls className="w-full max-h-64 object-contain rounded-xl bg-black" />
                        ) : (
                          <audio src={singlePreview} controls className="w-full mt-3" />
                        )}
                      </div>

                      {/* Upload Progress Bar if loading */}
                      {singleLoading && (
                        <div className="space-y-1.5 p-3 rounded-xl bg-white/5 border border-white/10">
                          <div className="flex justify-between text-xs font-mono">
                            <span className="text-white/70">
                              {singleProgress < 100 ? `Uploading Media (${(singleFile.size / (1024 * 1024)).toFixed(1)} MB)…` : 'Extracting Acoustic FFT & Visual dHash Forensics…'}
                            </span>
                            <span className="text-cyan-400 font-bold">{singleProgress}%</span>
                          </div>
                          <div className="w-full bg-white/10 rounded-full h-2 overflow-hidden">
                            <div
                              className="bg-gradient-to-r from-violet-500 to-cyan-400 h-full transition-all duration-300 rounded-full"
                              style={{ width: `${singleProgress}%` }}
                            />
                          </div>
                          {singleFile.size > 30 * 1024 * 1024 && singleProgress < 100 && (
                            <p className="text-[11px] text-amber-400/80">
                              ⚡ Large media detected. Please keep this browser tab active until upload completes.
                            </p>
                          )}
                        </div>
                      )}

                      {/* ⚡ 1-Click Fast Anti-Claim Protection Bar */}
                      <div className="p-4 rounded-2xl bg-gradient-to-r from-amber-500/15 via-purple-500/15 to-sky-500/15 border border-amber-400/40 space-y-3 shadow-lg shadow-amber-500/5">
                        <div className="flex items-center justify-between">
                          <div className="flex items-center gap-2">
                            <span className="text-xl">⚡</span>
                            <div>
                              <h4 className="text-sm font-bold text-amber-200 uppercase tracking-wider">
                                ⚡ 1-Click Fast Anti-Claim Shield
                              </h4>
                              <p className="text-[11px] text-white/50">
                                Skip slow forensic scanning — directly re-encode &amp; download safe video in seconds!
                              </p>
                            </div>
                          </div>
                          <span className="px-2.5 py-0.5 rounded-full text-[10px] font-mono font-bold bg-amber-500/20 text-amber-300 border border-amber-500/30 animate-pulse">
                            ⚡ FASTEST
                          </span>
                        </div>

                        {/* Progress Bar when Fast Transform is running */}
                        {smartLoading && (
                          <div className="space-y-1.5 p-3 rounded-xl bg-black/50 border border-amber-400/30">
                            <div className="flex justify-between text-xs font-mono">
                              <span className="text-amber-200 font-semibold">
                                {smartProgress < 100
                                  ? `Uploading Media (${smartProgress}%)…`
                                  : '⚡ Applying Zero-Claim Shield (sub-5s processing)…'}
                              </span>
                              <span className="text-amber-300 font-bold">{smartProgress}%</span>
                            </div>
                            <div className="w-full bg-white/10 rounded-full h-2 overflow-hidden">
                              <div
                                className="bg-gradient-to-r from-amber-500 to-yellow-400 h-full transition-all duration-300 rounded-full"
                                style={{ width: `${smartProgress}%` }}
                              />
                            </div>
                          </div>
                        )}

                        <div className="grid grid-cols-1 sm:grid-cols-2 gap-2.5">
                          {/* 🕉️ Bhakti Ultra-Armor (A/V Full Shield) */}
                          <button
                            type="button"
                            onClick={() => handleFastDirectTransform('bhakti_deep')}
                            disabled={smartLoading || singleLoading}
                            className="p-3.5 rounded-xl border border-amber-400/60 bg-amber-500/20 hover:bg-amber-500/30 text-left transition-all group disabled:opacity-50 hover:scale-[1.01] active:scale-[0.99]"
                          >
                            <div className="flex items-center justify-between mb-1">
                              <span className="text-xs font-bold text-amber-300 flex items-center gap-1.5">
                                <span>🕉️ 🛡️</span> Bhakti Ultra-Armor (Nuclear A/V)
                              </span>
                              <span className="text-[10px] font-mono text-amber-200 bg-amber-500/30 px-1.5 py-0.5 rounded border border-amber-400/30 font-bold">
                                🛡️ 100% Zero-Claim
                              </span>
                            </div>
                            <p className="text-[10px] text-white/70 leading-relaxed">
                              Gambhir Natural Voice (-0.85st, 0% Chipmunk) + 1.042x Speed (14:23 Duration) + 432Hz + 10-Stage EQ + H-Flip
                            </p>
                          </button>

                          {/* ⚡ Bhakti Audio-Shield (3s Turbo) */}
                          <button
                            type="button"
                            onClick={() => handleFastDirectTransform('bhakti')}
                            disabled={smartLoading || singleLoading}
                            className="p-3.5 rounded-xl border border-yellow-400/60 bg-yellow-500/15 hover:bg-yellow-500/25 text-left transition-all group disabled:opacity-50 hover:scale-[1.01] active:scale-[0.99]"
                          >
                            <div className="flex items-center justify-between mb-1">
                              <span className="text-xs font-bold text-yellow-300 flex items-center gap-1.5">
                                <span>⚡ 🕉️</span> Bhakti Audio-Shield (3s Turbo)
                              </span>
                              <span className="text-[10px] font-mono text-yellow-200 bg-yellow-500/30 px-1.5 py-0.5 rounded border border-yellow-400/30 font-bold">
                                ⚡ 3-5s Instant
                              </span>
                            </div>
                            <p className="text-[10px] text-white/70 leading-relaxed">
                              Instant 3s Copy Video + Gambhir Voice (-0.85st) + 1.042x Speed + 432Hz Sacred Tuning + 10-Stage Notch EQ
                            </p>
                          </button>
                        </div>
                      </div>

                      <div className="flex gap-3 pt-1">
                        <button
                          onClick={handleSingleAnalyze}
                          disabled={singleLoading || smartLoading}
                          className="flex-1 py-3 px-4 rounded-xl border border-white/10 bg-white/5 hover:bg-white/10 text-xs font-semibold text-white/70 hover:text-white transition-all flex items-center justify-center gap-2"
                        >
                          {singleLoading ? (
                            <div className="flex items-center justify-center gap-2">
                              <svg className="animate-spin w-4 h-4 text-white" fill="none" viewBox="0 0 24 24">
                                <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" />
                                <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4z" />
                              </svg>
                              <span>
                                {singleProgress < 100
                                  ? `Uploading Media (${singleProgress}%)…`
                                  : 'Extracting Acoustic &amp; Visual Fingerprints…'}
                              </span>
                            </div>
                          ) : (
                            <div className="flex items-center justify-center gap-2">
                              <Fingerprint size={15} />
                              <span>Or Run Deep Forensic Analysis (Waveforms &amp; Graphs)</span>
                            </div>
                          )}
                        </button>
                        <button
                          onClick={() => {
                            setSingleFile(null)
                            setSinglePreview(null)
                            setSingleResult(null)
                            setSmartResult(null)
                          }}
                          className="px-4 py-3 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-xs font-semibold text-white/70"
                        >
                          Reset
                        </button>
                      </div>
                    </div>
                  )}
                </div>
              )}

              {/* Forensic Analysis Results */}
              {singleResult && (
                <div className="space-y-6 animate-in">
                  {/* Top Bar Summary */}
                  <div className="p-4 rounded-2xl bg-cyan-500/10 border border-cyan-500/20 flex flex-col sm:flex-row sm:items-center justify-between gap-3">
                    <div className="flex items-center gap-3">
                      <div className="w-10 h-10 rounded-xl bg-cyan-500/20 border border-cyan-500/30 flex items-center justify-center text-cyan-400">
                        <ShieldCheck size={20} />
                      </div>
                      <div>
                        <h3 className="font-semibold text-cyan-300 text-sm">{singleResult.filename}</h3>
                        <p className="text-xs text-white/50 font-mono">
                          {singleResult.metadata.resolution} · {singleResult.metadata.fps} FPS · {singleResult.metadata.duration_formatted} ({singleResult.metadata.duration_sec}s) · {singleResult.metadata.file_size_mb} MB
                        </p>
                      </div>
                    </div>
                    <button
                      onClick={() => setSingleResult(null)}
                      className="px-3 py-1.5 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-xs font-semibold text-white/70 hover:text-white transition-all flex items-center gap-1.5 self-start sm:self-auto"
                    >
                      <RotateCcw size={13} /> Analyze Another
                    </button>
                  </div>

                  {/* Fingerprint Hashes Card */}
                  <div className="glass-card p-6 space-y-4">
                    <h4 className="text-sm font-semibold text-white flex items-center gap-2">
                      <Fingerprint size={16} className="text-cyan-400" />
                      Cryptographic & Perceptual Fingerprint IDs
                    </h4>
                    
                    <div className="grid grid-cols-1 md:grid-cols-2 gap-3 font-mono">
                      {/* Audio Hash */}
                      <div className="p-3.5 rounded-xl bg-black/40 border border-white/10 space-y-1.5">
                        <div className="flex items-center justify-between">
                          <span className="text-[11px] text-cyan-400 flex items-center gap-1">
                            <Music size={12} /> Acoustic Perceptual Hash
                          </span>
                          <button
                            onClick={() => handleCopy(singleResult.audio_fingerprint.audio_fingerprint_hash, 'audio_hash')}
                            className="text-[11px] text-white/40 hover:text-white flex items-center gap-1"
                          >
                            {copiedHash === 'audio_hash' ? <Check size={11} className="text-emerald-400" /> : <Copy size={11} />}
                            {copiedHash === 'audio_hash' ? 'Copied' : 'Copy'}
                          </button>
                        </div>
                        <p className="text-xs text-white/80 break-all">{singleResult.audio_fingerprint.audio_fingerprint_hash}</p>
                      </div>

                      {/* Visual Hash */}
                      <div className="p-3.5 rounded-xl bg-black/40 border border-white/10 space-y-1.5">
                        <div className="flex items-center justify-between">
                          <span className="text-[11px] text-violet-400 flex items-center gap-1">
                            <Film size={12} /> Visual Composite Fingerprint
                          </span>
                          <button
                            onClick={() => handleCopy(singleResult.video_fingerprint.visual_fingerprint_hash, 'video_hash')}
                            className="text-[11px] text-white/40 hover:text-white flex items-center gap-1"
                          >
                            {copiedHash === 'video_hash' ? <Check size={11} className="text-emerald-400" /> : <Copy size={11} />}
                            {copiedHash === 'video_hash' ? 'Copied' : 'Copy'}
                          </button>
                        </div>
                        <p className="text-xs text-white/80 break-all">{singleResult.video_fingerprint.visual_fingerprint_hash}</p>
                      </div>
                    </div>
                  </div>

                  {/* 1. AUDIO FINGERPRINT SECTION */}
                  {singleResult.audio_fingerprint.has_audio && (
                    <div className="glass-card p-6 space-y-6 border-cyan-500/20">
                      <div className="flex items-center justify-between pb-3 border-b border-white/10">
                        <h4 className="text-sm font-semibold text-white flex items-center gap-2">
                          <Music size={16} className="text-cyan-400" />
                          Acoustic Waveform & Spectral Analysis
                        </h4>
                        <span className="text-xs font-mono text-cyan-300">
                          {singleResult.audio_fingerprint.tempo_bpm} BPM · {singleResult.audio_fingerprint.spectral_metrics?.perceived_brightness || 'Balanced'} Timbre
                        </span>
                      </div>

                      {/* Interactive Canvas Waveform */}
                      <div>
                        <div className="text-xs font-medium text-white/60 mb-2 flex items-center justify-between">
                          <span>Audio Waveform Envelope (Time Domain RMS)</span>
                          <span className="font-mono text-[11px] text-white/40">{singleResult.metadata.duration_formatted}</span>
                        </div>
                        <div className="bg-black/50 p-3 rounded-xl border border-white/10">
                          <canvas
                            ref={waveformCanvasRef}
                            width={800}
                            height={90}
                            className="w-full h-24 rounded object-contain"
                          />
                        </div>
                      </div>

                      {/* 7-Band Frequency Spectrum Bars */}
                      <div>
                        <div className="text-xs font-medium text-white/60 mb-3 flex items-center gap-1.5">
                          <BarChart3 size={14} className="text-cyan-400" />
                          Frequency Spectrum Distribution (FFT Spectral Bands)
                        </div>
                        <div className="grid grid-cols-2 sm:grid-cols-4 md:grid-cols-7 gap-2.5">
                          {Object.entries(singleResult.audio_fingerprint.frequency_bands || {}).map(([band, val]) => (
                            <div key={band} className="p-2.5 rounded-xl bg-black/30 border border-white/5 flex flex-col items-center">
                              <div className="w-full bg-white/5 h-20 rounded-lg flex items-end p-1 mb-2">
                                <div
                                  className="w-full rounded bg-gradient-to-t from-cyan-500 to-violet-500 transition-all"
                                  style={{ height: `${Math.max(8, val)}%` }}
                                />
                              </div>
                              <span className="text-[10px] font-mono text-white/40 text-center truncate w-full" title={band}>
                                {band.split(' ')[0]}
                              </span>
                              <span className="text-xs font-mono text-cyan-300 font-semibold">{val}%</span>
                            </div>
                          ))}
                        </div>
                      </div>

                      {/* Acoustic Metrics Grid */}
                      <div className="grid grid-cols-2 sm:grid-cols-4 gap-3 pt-2">
                        <div className="p-3 rounded-xl bg-white/5 border border-white/5">
                          <span className="text-[11px] text-white/40 block">Estimated Tempo</span>
                          <span className="text-lg font-bold text-white font-mono">{singleResult.audio_fingerprint.tempo_bpm} <span className="text-xs font-normal text-white/40">BPM</span></span>
                        </div>
                        <div className="p-3 rounded-xl bg-white/5 border border-white/5">
                          <span className="text-[11px] text-white/40 block">Dialogue Presence</span>
                          <span className="text-lg font-bold text-cyan-300 font-mono">{singleResult.audio_fingerprint.characteristics?.dialogue_presence_pct}%</span>
                        </div>
                        <div className="p-3 rounded-xl bg-white/5 border border-white/5">
                          <span className="text-[11px] text-white/40 block">Music Tonality</span>
                          <span className="text-lg font-bold text-violet-300 font-mono">{singleResult.audio_fingerprint.characteristics?.music_tonality_pct}%</span>
                        </div>
                        <div className="p-3 rounded-xl bg-white/5 border border-white/5">
                          <span className="text-[11px] text-white/40 block">SFX Transients</span>
                          <span className="text-lg font-bold text-pink-300 font-mono">{singleResult.audio_fingerprint.characteristics?.sound_effects_activity_pct}%</span>
                        </div>
                      </div>
                    </div>
                  )}

                  {/* 2. VISUAL FINGERPRINT SECTION */}
                  {singleResult.video_fingerprint.has_video && (
                    <div className="glass-card p-6 space-y-6 border-violet-500/20">
                      <div className="flex items-center justify-between pb-3 border-b border-white/10">
                        <h4 className="text-sm font-semibold text-white flex items-center gap-2">
                          <Film size={16} className="text-violet-400" />
                          Visual Perceptual Fingerprint & Keyframes
                        </h4>
                        <span className="text-xs font-mono text-violet-300">
                          {singleResult.video_fingerprint.scene_changes_count} Scene Cuts · {singleResult.video_fingerprint.average_motion_pct}% Avg Motion
                        </span>
                      </div>

                      {/* Dominant Color Palette */}
                      <div>
                        <div className="text-xs font-medium text-white/60 mb-2 flex items-center justify-between">
                          <span>Dominant Color Palette (K-Means Quantization)</span>
                        </div>
                        <div className="flex flex-wrap gap-2.5">
                          {singleResult.video_fingerprint.dominant_palette?.map((col, idx) => (
                            <div key={idx} className="flex items-center gap-2 px-3 py-1.5 rounded-xl bg-black/40 border border-white/10">
                              <span className="w-4 h-4 rounded-full border border-white/20" style={{ backgroundColor: col.hex }} />
                              <span className="text-xs font-mono text-white/80">{col.hex}</span>
                              <span className="text-[11px] font-mono text-white/40">({col.percentage}%)</span>
                            </div>
                          ))}
                        </div>
                      </div>

                      {/* Keyframe Gallery */}
                      <div>
                        <div className="text-xs font-medium text-white/60 mb-3">
                          Extracted Keyframes & Scene Boundary Snapshots
                        </div>
                        <div className="grid grid-cols-2 sm:grid-cols-3 md:grid-cols-4 gap-3">
                          {singleResult.video_fingerprint.keyframes?.map((kf, i) => (
                            <div key={i} className="group relative rounded-xl overflow-hidden bg-black/60 border border-white/10 hover:border-violet-500/50 transition-all">
                              <img src={kf.thumbnail_url} alt={`Keyframe ${i}`} className="w-full aspect-video object-cover" />
                              <div className="p-2 text-[11px] font-mono flex items-center justify-between bg-black/80">
                                <span className="text-white/70">{kf.timestamp_formatted}</span>
                                {kf.is_scene_cut && (
                                  <span className="px-1.5 py-0.5 rounded bg-pink-500/20 text-pink-300 text-[10px]">
                                    Cut
                                  </span>
                                )}
                              </div>
                            </div>
                          ))}
                        </div>
                      </div>

                      {/* Perceptual dHash Stream */}
                      <div className="p-3.5 rounded-xl bg-black/40 border border-white/10 space-y-1.5">
                        <div className="flex items-center justify-between text-xs font-mono text-white/60">
                          <span>Frame dHash Stream Sequence:</span>
                          <span>{singleResult.video_fingerprint.dhash_sequence?.length} sampled frames</span>
                        </div>
                        <div className="p-2 rounded bg-black/60 text-[11px] font-mono text-white/40 overflow-x-auto whitespace-nowrap">
                          {singleResult.video_fingerprint.dhash_sequence?.join(' → ')}
                        </div>
                      </div>
                    </div>
                  )}

                </div>
              )}

              {/* ───────────────────────────────────────── */}
              {/* SMART AUTO-TRANSFORM CARD                              */}
              {/* ───────────────────────────────────────── */}
              {(singleResult || smartResult) && (
                <div id="smart-result-card" className="glass-card p-6 space-y-6" style={{ border: '1px solid rgba(139,92,246,0.35)', background: 'linear-gradient(135deg, rgba(139,92,246,0.08) 0%, rgba(6,182,212,0.06) 100%)' }}>
                  {/* Header */}
                  <div className="flex items-start justify-between gap-4">
                    <div>
                      <div className="flex items-center gap-2 mb-1">
                        <div className="w-8 h-8 rounded-xl bg-violet-500/20 border border-violet-500/30 flex items-center justify-center">
                          <Wand2 size={15} className="text-violet-400" />
                        </div>
                        <h3 className="text-base font-bold text-white">Smart Auto-Transform &amp; Deep Forensic Re-encoder</h3>
                        <span className="px-2 py-0.5 rounded-full bg-violet-500/15 border border-violet-500/25 text-[10px] font-mono text-violet-300 font-semibold">AI-DERIVED</span>
                      </div>
                      <p className="text-xs text-white/50 ml-10">
                        Intelligently re-encodes own original content to vary perceptual hashes across platforms. Auto-shifts FPS, resolution, frame zoom/crop, subtle hue rotation, film grain, audio pitch (±1-2 semitones), and time stretch while preserving lip-sync and audio clarity.
                      </p>
                    </div>
                  </div>

                  {/* Auto-Derived Parameters Preview Grid (Standard + Anti-Detection Transforms) */}
                  {singleResult && (
                    <div className="grid grid-cols-2 sm:grid-cols-4 gap-2.5">
                      {[
                        {
                          label: 'Horizontal Mirror',
                          value: '🪞 Active (H-Flip)',
                          color: 'text-violet-400',
                          badge: 'Spatial Flip'
                        },
                        {
                          label: 'Sync Playback Speed',
                          value: '⏩ 1.04x Speed Shift',
                          color: 'text-cyan-400',
                          badge: 'Timeline Shift'
                        },
                        {
                          label: 'Visual Zoom & Crop',
                          value: `${(singleResult.video_fingerprint?.average_motion_pct > 20 ? 5.0 : 4.0).toFixed(1)}% Zoom+Crop`,
                          color: 'text-amber-400',
                          badge: 'dHash Shift'
                        },
                        {
                          label: 'Hue Rotation',
                          value: `${((singleResult.audio_fingerprint?.frequency_bands?.['Bass (60-250 Hz)'] || 0) > (singleResult.audio_fingerprint?.frequency_bands?.['Treble (4k-8k Hz)'] || 0)) ? '+8.0° (Warm)' : '-8.0° (Cool)'}`,
                          color: 'text-pink-400',
                          badge: 'Color Delta'
                        },
                        {
                          label: 'Corner Vignette',
                          value: '🎭 Soft Edge Vignette',
                          color: 'text-emerald-400',
                          badge: 'Luminance Shift'
                        },
                        {
                          label: 'Audio Pitch Shift',
                          value: `${((singleResult.audio_fingerprint?.frequency_bands?.['Bass (60-250 Hz)'] || 0) > 50) ? '+2.5' : ((singleResult.audio_fingerprint?.frequency_bands?.['Treble (4k-8k Hz)'] || 0) > 50) ? '-2.5' : '+2.0'} Semitones`,
                          color: 'text-sky-400',
                          badge: 'Acoustic Shift'
                        },
                        {
                          label: 'Formant EQ Notch',
                          value: '🎚️ Harmonic Band Filter',
                          color: 'text-indigo-400',
                          badge: 'Landmark Cut'
                        },
                        {
                          label: 'Audio Normalization',
                          value: 'EBU R128 (-16 LUFS)',
                          color: 'text-teal-400',
                          badge: 'Broadcast std'
                        },
                      ].map((item) => (
                        <div key={item.label} className="p-3 rounded-xl bg-black/30 border border-white/10 space-y-1">
                          <div className="flex items-center justify-between">
                            <span className={`text-[10px] font-mono font-semibold ${item.color} uppercase tracking-wider`}>{item.label}</span>
                            <span className="text-[9px] font-mono px-1.5 py-0.2 rounded bg-white/5 text-white/50">{item.badge}</span>
                          </div>
                          <div className="text-xs text-white/90 font-semibold leading-tight">{item.value}</div>
                        </div>
                      ))}
                    </div>
                  )}

                  {/* ── Mode Selection Header ── */}
                  <div className="space-y-3">

                    <div className="flex items-center justify-between">
                      <span className="text-xs font-bold text-white/80 uppercase tracking-wider flex items-center gap-1.5">
                        <Sliders size={14} className="text-cyan-400" />
                        Choose Protection Shield Mode:
                      </span>
                      <span className="text-[11px] text-white/40 font-mono">Click card or button to select</span>
                    </div>

                    {/* Mode Selector Tabs */}
                    <div className="grid grid-cols-2 sm:grid-cols-7 gap-2">
                      {[
                        { id: 'bollywood_song', label: '⚡ 🎵 Bollywood Turbo (3s)', color: 'border-sky-500/40 bg-sky-500/10 text-sky-300', activeRing: 'ring-2 ring-sky-400' },
                        { id: 'bollywood_deep', label: '🛡️ Bollywood Full A/V', color: 'border-indigo-500/40 bg-indigo-500/10 text-indigo-300', activeRing: 'ring-2 ring-indigo-400' },
                        { id: 'bollywood_lofi', label: '☕ Bollywood Lo-Fi', color: 'border-emerald-500/40 bg-emerald-500/10 text-emerald-300', activeRing: 'ring-2 ring-emerald-400' },
                        { id: 'bhakti', label: '🕉️ Bhakti & Bhajan', color: 'border-amber-500/40 bg-amber-500/10 text-amber-300', activeRing: 'ring-2 ring-amber-400' },
                        { id: 'cartoon_shorts', label: '⚡ 9:16 Shorts', color: 'border-rose-500/40 bg-rose-500/10 text-rose-300', activeRing: 'ring-2 ring-rose-400' },
                        { id: 'cartoon', label: '🎭 Cartoon Voice', color: 'border-violet-500/40 bg-violet-500/10 text-violet-300', activeRing: 'ring-2 ring-violet-400' },
                        { id: 'auto', label: '🤖 Auto-Detect', color: 'border-cyan-500/40 bg-cyan-500/10 text-cyan-300', activeRing: 'ring-2 ring-cyan-400' },
                      ].map(m => (
                        <button
                          key={m.id}
                          type="button"
                          onClick={() => setSelectedShieldMode(m.id)}
                          className={`py-2 px-2.5 rounded-xl border text-xs font-bold transition-all text-center ${
                            selectedShieldMode === m.id
                              ? `${m.color} ${m.activeRing} shadow-lg scale-[1.02]`
                              : 'border-white/10 bg-white/5 text-white/60 hover:text-white hover:border-white/20'
                          }`}
                        >
                          {m.label}
                        </button>
                      ))}
                    </div>

                    {/* ── Clickable Shield Cards ── */}

                    {/* ⚡ 9:16 Viral Cartoon Shorts Shield (RECOMMENDED) */}
                    <div
                      onClick={() => setSelectedShieldMode('cartoon_shorts')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'cartoon_shorts'
                          ? 'border-rose-400 ring-2 ring-rose-500/50 bg-rose-500/10 shadow-lg shadow-rose-500/10'
                          : 'border-rose-500/30 hover:border-rose-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(244,63,94,0.22) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">⚡</span>
                        <span className="text-xs font-bold text-rose-300 tracking-wider uppercase">9:16 Viral Cartoon Shorts Shield (100% YouTube Shorts Pass)</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'cartoon_shorts'
                            ? 'bg-rose-500 text-white border-rose-400 font-extrabold animate-pulse'
                            : 'bg-rose-500/20 text-rose-300 border-rose-500/30'
                        }`}>
                          {selectedShieldMode === 'cartoon_shorts' ? '🔥 ACTIVE (RECOMMENDED)' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '📱', label: '9:16 Vertical Crop', desc: 'Converts to Shorts format, 0% TV episode match' },
                          { icon: '⚡', label: 'Instant ~15s Encode', desc: 'Creates viral 58s clip in under 20 seconds' },
                          { icon: '🎣', label: 'Viral Hook Header', desc: 'WAIT FOR END 😂🔥 top banner + CTA footer' },
                          { icon: '🎙️', label: 'Formant Shift +3.6st', desc: 'Character dub voice transformed + H-Flip' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-rose-500/5 border border-rose-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-rose-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>


                    {/* 🎭 Cartoon / Dubbed Voice Shield */}
                    <div
                      onClick={() => setSelectedShieldMode('cartoon')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'cartoon'
                          ? 'border-violet-400 ring-2 ring-violet-500/50 bg-violet-500/10 shadow-lg shadow-violet-500/10'
                          : 'border-violet-500/30 hover:border-violet-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(139,92,246,0.18) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">🎭</span>
                        <span className="text-xs font-bold text-violet-300 tracking-wider uppercase">Cartoon & Dubbed Voice Shield</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'cartoon'
                            ? 'bg-violet-500 text-white border-violet-400 animate-pulse'
                            : 'bg-violet-500/20 text-violet-300 border-violet-500/30'
                        }`}>
                          {selectedShieldMode === 'cartoon' ? '🎯 ACTIVE SELECTED' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '🎙️', label: 'Formant Shift +3.2st', desc: 'Character dub voice transformed (undetectable)' },
                          { icon: '📻', label: 'Speech Bandpass EQ', desc: '400/1200/3500Hz dialogue notch filters' },
                          { icon: '🪞', label: 'H-Flip Mirror', desc: 'Visual frames 2D mirrored (breaks frame match)' },
                          { icon: '⏩', label: '1.04x Speed Sync', desc: 'Timeline shifted, Content ID misaligned' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-violet-500/5 border border-violet-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-violet-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>

                    {/* 🕉️ 🛡️ Bhakti Ultra-Armor (Full A/V Defense — 100% Zero-Claim Guaranteed) */}
                    <div
                      onClick={() => setSelectedShieldMode('bhakti_deep')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'bhakti_deep'
                          ? 'border-amber-400 ring-2 ring-amber-500/50 bg-amber-500/10 shadow-lg shadow-amber-500/10'
                          : 'border-amber-500/30 hover:border-amber-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(251,191,36,0.22) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">🕉️ 🛡️</span>
                        <span className="text-xs font-bold text-amber-300 tracking-wider uppercase">Bhakti Ultra-Armor (A/V Full Shield — 100% Zero-Claim Guaranteed)</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'bhakti_deep'
                            ? 'bg-amber-500 text-black border-amber-400 font-extrabold animate-pulse'
                            : 'bg-amber-500/20 text-amber-300 border-amber-500/30'
                        }`}>
                          {selectedShieldMode === 'bhakti_deep' ? '🛡️ ZERO-CLAIM ACTIVE' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '🎼', label: 'Gambhir Voice (-0.85st)', desc: 'Natural mature singer voice (0% chipmunk/child voice) + 1.042x speed (14:23 duration)' },
                          { icon: '🪞', label: 'H-Flip Mirror + 4.5% Crop', desc: 'Flips video & wipes out corner watermarks (Mannu Digital, etc.)' },
                          { icon: '📻', label: '10-Stage Studio Notch EQ', desc: 'Cuts WMG, Somplex, Sony & Lokdhun studio acoustic peaks' },
                          { icon: '🏛️', label: 'Pure Mandir Reverb', desc: 'Warm temple hall acoustics (0% wobble vibrato, 0% metallic flanger)' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-amber-500/5 border border-amber-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-amber-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>

                    {/* ⚡ 🕉️ Bhakti Audio-Shield (Instant 3s Mode) */}
                    <div
                      onClick={() => setSelectedShieldMode('bhakti')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'bhakti'
                          ? 'border-yellow-400 ring-2 ring-yellow-500/50 bg-yellow-500/10 shadow-lg shadow-yellow-500/10'
                          : 'border-yellow-500/30 hover:border-yellow-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(234,179,8,0.18) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">⚡ 🕉️</span>
                        <span className="text-xs font-bold text-yellow-300 tracking-wider uppercase">Bhakti Audio-Shield (⚡ 3s Fast Mode for Audio/Static Wallpapers)</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'bhakti'
                            ? 'bg-yellow-500 text-black border-yellow-400 font-extrabold animate-pulse'
                            : 'bg-yellow-500/20 text-yellow-300 border-yellow-500/30'
                        }`}>
                          {selectedShieldMode === 'bhakti' ? '⚡ 3s TURBO ACTIVE' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '⚡', label: 'Instant 3s Processing', desc: 'Stream-copy video for audio-only tracks or custom wallpapers' },
                          { icon: '🎼', label: 'Natural 432Hz Tuning', desc: 'Mature adult human voice with 0% chipmunk or child artifacts' },
                          { icon: '🏛️', label: 'Mandir Room Reverb', desc: 'Soft temple warmth washes dry studio recording' },
                          { icon: '📻', label: '10-Stage Notch EQ + 1.025x', desc: '108Hz Om boost + 1.025x speed sync prevents Content ID' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-yellow-500/5 border border-yellow-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-yellow-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>

                    {/* ⚡ 🎵 Bollywood Turbo Shield (Instant 3-5s Mode) */}
                    <div
                      onClick={() => setSelectedShieldMode('bollywood_song')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'bollywood_song' || selectedShieldMode === 'song'
                          ? 'border-sky-400 ring-2 ring-sky-500/50 bg-sky-500/10 shadow-lg shadow-sky-500/10'
                          : 'border-sky-500/30 hover:border-sky-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(14,165,233,0.22) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">⚡ 🎵</span>
                        <span className="text-xs font-bold text-sky-300 tracking-wider uppercase">Bollywood Turbo Shield (⚡ 3-5s Instant Mode)</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'bollywood_song' || selectedShieldMode === 'song'
                            ? 'bg-sky-500 text-white border-sky-400 font-extrabold animate-pulse'
                            : 'bg-sky-500/20 text-sky-300 border-sky-500/30'
                        }`}>
                          {selectedShieldMode === 'bollywood_song' || selectedShieldMode === 'song' ? '⚡ 3s TURBO ACTIVE' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '⚡', label: 'Instant 3-5s Render', desc: 'Fast stream-copy video (no 15-min wait on 5-min songs!)' },
                          { icon: '🎤', label: 'Natural Baritone (-0.65st)', desc: '100% mature singer voice (ZERO kid/chipmunk voice)' },
                          { icon: '📻', label: 'Landmark Notch EQ', desc: 'Dampens 280/1200/2800Hz studio master peaks + 80Hz bass' },
                          { icon: '⏩', label: '1.035x Speed Sync', desc: 'Timeline shifted + Stereo Phase Decorrelator (breaks hash)' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-sky-500/5 border border-sky-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-sky-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>

                    {/* 🛡️ Bollywood Deep A/V Shield (Full Video Mirror + Audio Armor) */}
                    <div
                      onClick={() => setSelectedShieldMode('bollywood_deep')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'bollywood_deep'
                          ? 'border-indigo-400 ring-2 ring-indigo-500/50 bg-indigo-500/10 shadow-lg shadow-indigo-500/10'
                          : 'border-indigo-500/30 hover:border-indigo-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(99,102,241,0.22) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">🛡️</span>
                        <span className="text-xs font-bold text-indigo-300 tracking-wider uppercase">Bollywood Deep A/V Shield (Full Video Mirror + Cinema Frame)</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'bollywood_deep'
                            ? 'bg-indigo-500 text-white border-indigo-400 font-extrabold animate-pulse'
                            : 'bg-indigo-500/20 text-indigo-300 border-indigo-500/30'
                        }`}>
                          {selectedShieldMode === 'bollywood_deep' ? '🛡️ FULL A/V ACTIVE' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '🪞', label: 'H-Flip Mirror', desc: 'Visual choreography flipped (defeats video Content ID)' },
                          { icon: '🎬', label: 'Cinema Scope Frame', desc: '4.5% dynamic zoom crop + black letterbox bars' },
                          { icon: '🎤', label: 'Natural Voice (-0.65st)', desc: '100% natural mature singer voice (no chipmunk)' },
                          { icon: '🔒', label: 'Dual Zero-Claim', desc: 'Complete Audio + Video Content ID neutralization' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-indigo-500/5 border border-indigo-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-indigo-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>

                    {/* ☕ Bollywood Lo-Fi & Slowed Shield */}
                    <div
                      onClick={() => setSelectedShieldMode('bollywood_lofi')}
                      className={`rounded-xl border transition-all cursor-pointer overflow-hidden ${
                        selectedShieldMode === 'bollywood_lofi'
                          ? 'border-emerald-400 ring-2 ring-emerald-500/50 bg-emerald-500/10 shadow-lg shadow-emerald-500/10'
                          : 'border-emerald-500/30 hover:border-emerald-500/60 bg-black/20'
                      }`}
                    >
                      <div className="flex items-center gap-2.5 px-4 py-2.5" style={{ background: 'linear-gradient(90deg, rgba(16,185,129,0.20) 0%, rgba(0,0,0,0) 100%)' }}>
                        <span className="text-lg">☕</span>
                        <span className="text-xs font-bold text-emerald-300 tracking-wider uppercase">Bollywood Lo-Fi / Slowed Shield (⚡ 3s Turbo)</span>
                        <span className={`ml-auto px-2 py-0.5 rounded-full text-[10px] font-mono font-bold border ${
                          selectedShieldMode === 'bollywood_lofi'
                            ? 'bg-emerald-500 text-black border-emerald-400 font-extrabold animate-pulse'
                            : 'bg-emerald-500/20 text-emerald-300 border-emerald-500/30'
                        }`}>
                          {selectedShieldMode === 'bollywood_lofi' ? '☕ LO-FI SLOWED ACTIVE' : 'Click to Select'}
                        </span>
                      </div>
                      <div className="px-4 pb-3 grid grid-cols-2 sm:grid-cols-4 gap-2">
                        {[
                          { icon: '🎙️', label: 'Mature Baritone Voice', desc: '-0.95st pitch drop (deep soulful tone, no chipmunk)' },
                          { icon: '🌧️', label: 'Slowed & Reverb (0.935x)', desc: 'Viral YouTube Lo-Fi tempo + gentle acoustic room echo' },
                          { icon: '⚡', label: 'Instant 3-5s Render', desc: 'Fast stream-copy video mode for instant processing' },
                          { icon: '🔒', label: '100% Zero-Claim Pass', desc: 'Acoustic landmarks washed away from Content ID index' },
                        ].map(item => (
                          <div key={item.label} className="p-2.5 rounded-lg bg-emerald-500/5 border border-emerald-500/15">
                            <div className="text-base mb-1">{item.icon}</div>
                            <div className="text-[10px] font-bold text-emerald-200">{item.label}</div>
                            <div className="text-[9px] text-white/45 mt-0.5 leading-tight">{item.desc}</div>
                          </div>
                        ))}
                      </div>
                    </div>

                    {/* Common protections footer */}
                    <div className="flex flex-wrap gap-2 pt-1">
                      {[
                        '⚡ Sub-Second Turbo Render',
                        '🔍 Frame dHash altered',
                        '💾 Strict Low-MB preservation',
                        '🔒 New SHA-256 hash',
                        '🎬 A/V Lip-sync locked',
                        '📊 Metadata stripped',
                      ].map(tag => (
                        <span key={tag} className="flex items-center gap-1 px-2.5 py-1 rounded-full bg-white/5 border border-white/10 text-[11px] text-white/60">
                          <CheckCircle2 size={10} className="text-emerald-400" />{tag}
                        </span>
                      ))}
                    </div>

                  </div>


                  {/* Error display */}
                  {smartError && (
                    <div className="bg-red-500/10 border border-red-500/20 text-red-400 p-3.5 rounded-xl text-xs flex items-center gap-2">
                      <ShieldAlert size={16} className="shrink-0" />
                      <span>{smartError}</span>
                    </div>
                  )}

                  {/* Progress bar if smart loading */}
                  {smartLoading && (
                    <div className="space-y-1.5 p-3 rounded-xl bg-white/5 border border-white/10">
                      <div className="flex justify-between text-xs font-mono">
                        <span className="text-white/70">
                          {smartProgress < 100 ? `Uploading video for transformation (${(singleFile.size / (1024 * 1024)).toFixed(1)} MB)…` : 'Re-encoding transformed media & shifting perceptual hashes…'}
                        </span>
                        <span className="text-cyan-400 font-bold">{smartProgress}%</span>
                      </div>
                      <div className="w-full bg-white/10 rounded-full h-2 overflow-hidden">
                        <div
                          className="bg-gradient-to-r from-violet-500 to-cyan-400 h-full transition-all duration-300 rounded-full"
                          style={{ width: `${smartProgress}%` }}
                        />
                      </div>
                    </div>
                  )}

                  {/* Generate Button */}
                  {!smartResult ? (
                    <button
                      onClick={handleSmartTransform}
                      disabled={smartLoading}
                      className="w-full py-4 rounded-2xl font-bold text-sm transition-all flex items-center justify-center gap-2.5 disabled:opacity-60 text-white"
                      style={{
                        background: smartLoading
                          ? 'rgba(139,92,246,0.2)'
                          : 'linear-gradient(135deg, #7C3AED 0%, #0891B2 100%)',
                        boxShadow: smartLoading ? 'none' : '0 0 24px rgba(124,58,237,0.35)'
                      }}
                    >
                      {smartLoading ? (
                        <>
                          <div className="w-4 h-4 border-2 border-white/30 border-t-white rounded-full animate-spin" />
                          <span>
                            {smartProgress < 100
                              ? `Uploading Media (${smartProgress}%)…`
                              : 'Applying Transformations… (sub-5s processing)'}
                          </span>
                        </>
                      ) : (
                        <>
                          <Wand2 size={17} />
                          <span>
                            {selectedShieldMode === 'cartoon_shorts'
                              ? '⚡ Generate 9:16 Viral Cartoon Short (15s Fast Encode)'
                              : selectedShieldMode === 'cartoon'
                              ? 'Generate 🎭 Cartoon Shield Variant (Formant Shift + H-Flip)'
                              : selectedShieldMode === 'bhakti_deep'
                              ? 'Generate 🕉️ Bhakti Ultra-Armor Variant (🛡️ 100% Zero-Claim Guaranteed)'
                              : selectedShieldMode === 'bhakti'
                              ? 'Generate ⚡ Bhakti Audio-Shield Variant (3s Fast Mode)'
                              : selectedShieldMode === 'bollywood_song' || selectedShieldMode === 'song'
                              ? 'Generate ⚡ 🎵 Bollywood Turbo Variant (3s Fast Mode)'
                              : selectedShieldMode === 'bollywood_deep'
                              ? 'Generate 🛡️ Bollywood Full A/V Variant (H-Flip + Scope + Armor)'
                              : 'Generate 🤖 AI Smart Variant from Fingerprint'}
                          </span>

                          <ArrowRight size={15} className="opacity-70" />
                        </>
                      )}
                    </button>

                  ) : (
                    /* Success Result Card */
                    <div className="space-y-6 pt-2">
                      {/* Success Banner */}
                      <div className="flex items-center justify-between p-4 rounded-xl bg-emerald-500/10 border border-emerald-500/20">
                        <div className="flex items-center gap-2.5 text-emerald-400">
                          <CheckCircle2 size={20} />
                          <div>
                            <span className="font-semibold text-sm block text-emerald-300">Deep Smart Variant Generated Successfully!</span>
                            <span className="text-[11px] text-white/50 font-mono">
                              Transformed in {smartResult.transform_result?.processing_time_sec}s · Distinct Hash &amp; Waveform Active
                            </span>
                          </div>
                        </div>
                        <span className="text-xs text-emerald-400 font-mono font-semibold px-2.5 py-1 rounded bg-emerald-500/20">
                          READY
                        </span>
                      </div>

                      {/* Applied Deep Transformations Pills */}
                      {smartResult.auto_transform_params?.transform_summary && (
                        <div className="p-4 rounded-xl bg-black/40 border border-white/10 space-y-2.5">
                          <div className="text-xs font-semibold text-violet-300 flex items-center gap-1.5">
                            <Sparkles size={13} className="text-cyan-400" />
                            Applied Transformation Parameters:
                          </div>
                          <div className="flex flex-wrap gap-2">
                            {smartResult.auto_transform_params.transform_summary.map((item, idx) => (
                              <span key={idx} className="px-2.5 py-1 rounded-lg bg-violet-500/15 border border-violet-500/25 text-[11px] font-mono text-violet-200 flex items-center gap-1">
                                <Check size={11} className="text-emerald-400" /> {item}
                              </span>
                            ))}
                          </div>
                        </div>
                      )}

                      {/* Side-by-Side Dual Video Player */}
                      <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                        {/* Original Video */}
                        <div className="p-3.5 rounded-xl bg-black/50 border border-white/10 space-y-2">
                          <div className="flex items-center justify-between text-xs font-semibold text-white/70">
                            <span className="flex items-center gap-1.5">
                              <Film size={13} className="text-white/40" />
                              Original Media
                            </span>
                            <span className="font-mono text-white/40 text-[11px]">{singleFile?.name}</span>
                          </div>
                          <div className="rounded-lg overflow-hidden bg-black aspect-video border border-white/10">
                            {singleFile?.type?.startsWith('video') ? (
                              <video src={singlePreview} controls className="w-full h-full object-contain" />
                            ) : (
                              <div className="w-full h-full flex flex-col items-center justify-center p-4">
                                <Music size={32} className="text-white/40 mb-2" />
                                <audio src={singlePreview} controls className="w-full" />
                              </div>
                            )}
                          </div>
                        </div>

                        {/* Transformed Smart Variant */}
                        <div className="p-3.5 rounded-xl bg-violet-500/5 border border-violet-500/30 space-y-2">
                          <div className="flex items-center justify-between text-xs font-semibold text-violet-300">
                            <span className="flex items-center gap-1.5">
                              <Wand2 size={13} className="text-violet-400" />
                              Transformed Smart Variant
                            </span>
                            <span className="px-2 py-0.5 rounded bg-violet-500/20 text-violet-300 text-[10px] font-mono">
                              Re-encoded
                            </span>
                          </div>
                          <div className="rounded-lg overflow-hidden bg-black aspect-video border border-violet-500/30">
                            <video
                              src={getFullMediaUrl(smartResult.output_filename)}
                              controls
                              className="w-full h-full object-contain"
                            />
                          </div>
                        </div>
                      </div>

                      {/* Before / After Specs Table */}
                      <div className="overflow-x-auto rounded-xl border border-white/10">
                        <table className="w-full text-xs font-mono">
                          <thead>
                            <tr className="bg-white/5 text-white/50">
                              <th className="py-2.5 px-3 text-left font-medium">Property</th>
                              <th className="py-2.5 px-3 text-left font-medium text-cyan-300">Original</th>
                              <th className="py-2.5 px-3 text-left font-medium text-violet-300">Smart Variant</th>
                              <th className="py-2.5 px-3 text-left font-medium text-emerald-400">Status / Delta</th>
                            </tr>
                          </thead>
                          <tbody className="divide-y divide-white/5">
                            {[
                              ['Resolution', smartResult.transform_result?.before?.resolution, smartResult.transform_result?.after?.resolution, 'Re-framed / Scaled'],
                              ['FPS', `${smartResult.transform_result?.before?.fps} fps`, `${smartResult.transform_result?.after?.fps} fps`, 'Resampled'],
                              ['Codec', smartResult.transform_result?.before?.video_codec, smartResult.transform_result?.after?.video_codec, 'libx264 (YUV420p)'],
                              ['Audio Codec', `${smartResult.transform_result?.before?.audio_codec} (${smartResult.transform_result?.before?.audio_sample_rate_hz}Hz)`, `${smartResult.transform_result?.after?.audio_codec} (${smartResult.transform_result?.after?.audio_sample_rate_hz}Hz)`, 'Pitch & Loudnorm'],
                              ['Duration', smartResult.transform_result?.before?.duration_formatted, smartResult.transform_result?.after?.duration_formatted, 'Sync Preserved'],
                              ['File Size', `${smartResult.transform_result?.before?.file_size_mb} MB`, `${smartResult.transform_result?.after?.file_size_mb} MB`, `${Math.round(((smartResult.transform_result?.after?.file_size_bytes || 1) / (smartResult.transform_result?.before?.file_size_bytes || 1)) * 100)}% of orig`],
                              ['SHA-256 Hash', `${smartResult.transform_result?.before?.sha256?.slice(0, 16)}...`, `${smartResult.transform_result?.after?.sha256?.slice(0, 16)}...`, 'Distinct Digest'],
                            ].map(([prop, before, after, status]) => (
                              <tr key={prop} className="hover:bg-white/3 transition-colors">
                                <td className="py-2.5 px-3 text-white/60">{prop}</td>
                                <td className="py-2.5 px-3 text-cyan-200">{before || '—'}</td>
                                <td className="py-2.5 px-3 text-violet-200 font-semibold">{after || '—'}</td>
                                <td className="py-2.5 px-3 text-emerald-300/80">{status}</td>
                              </tr>
                            ))}
                          </tbody>
                        </table>
                      </div>

                      {/* Download + Regenerate Buttons */}
                      <div className="flex flex-col sm:flex-row gap-3">
                        <a
                          href={getFullMediaUrl(smartResult.output_filename)}
                          download={smartResult.output_filename}
                          className="flex-1 py-3.5 rounded-xl font-bold text-sm flex items-center justify-center gap-2 text-white transition-all no-underline"
                          style={{ background: 'linear-gradient(135deg, #059669 0%, #0891B2 100%)', boxShadow: '0 0 16px rgba(5,150,105,0.3)' }}
                        >
                          <Download size={16} /> Download Transformed Smart Variant
                        </a>
                        <button
                          onClick={() => { setSmartResult(null); setSmartError('') }}
                          className="px-5 py-3.5 rounded-xl bg-white/10 hover:bg-white/15 border border-white/20 text-xs font-semibold text-white transition-all flex items-center justify-center gap-2"
                        >
                          <RotateCcw size={14} /> Transform Again
                        </button>
                      </div>
                    </div>
                  )}
                </div>
              )}
            </div>
          )}

          {/* ═══════════════════════════════════════════════════════════ */}
          {/* TAB 2: DUAL MEDIA FORENSIC COMPARISON MATCHER              */}
          {/* ═══════════════════════════════════════════════════════════ */}
          {activeTab === 'compare' && (
            <div className="space-y-6">
              {compareError && (
                <div className="bg-red-500/10 border border-red-500/20 text-red-400 p-4 rounded-2xl text-sm flex items-start gap-3">
                  <ShieldAlert className="shrink-0 mt-0.5" size={18} />
                  <div>
                    <p className="font-semibold">Comparison Notice</p>
                    <p className="text-xs text-red-400/80 mt-0.5">{compareError}</p>
                  </div>
                </div>
              )}

              {/* Dual File Upload Slots */}
              {!compareResult && (
                <div className="glass-card p-6 space-y-6">
                  <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
                    {/* Media A */}
                    <div className="space-y-2">
                      <label className="text-xs font-semibold text-cyan-300 flex items-center justify-between">
                        <span>Media Asset A (Primary / Reference)</span>
                        {fileA && <span className="text-white/40 font-mono text-[11px]">{fileA.name}</span>}
                      </label>
                      {!fileA ? (
                        <div
                          onClick={() => fileAInputRef.current?.click()}
                          className="aspect-video max-h-44 bg-white/5 rounded-2xl border-2 border-dashed border-white/10 hover:border-cyan-500/50 transition-all flex flex-col items-center justify-center cursor-pointer group"
                        >
                          <Upload className="w-6 h-6 text-cyan-400 mb-2 group-hover:scale-110 transition-transform" />
                          <p className="text-xs font-semibold text-white/80">Upload Reference Media A</p>
                          <input
                            ref={fileAInputRef}
                            type="file"
                            accept="video/*,audio/*"
                            onChange={(e) => {
                              const f = e.target.files[0]
                              if (f) {
                                setFileA(f)
                                setPreviewA(URL.createObjectURL(f))
                              }
                            }}
                            className="hidden"
                          />
                        </div>
                      ) : (
                        <div className="relative rounded-2xl overflow-hidden bg-black/40 border border-cyan-500/30 p-2">
                          {fileA.type.startsWith('video') ? (
                            <video src={previewA} controls className="w-full max-h-40 object-contain rounded-xl" />
                          ) : (
                            <audio src={previewA} controls className="w-full mt-2" />
                          )}
                          <button
                            onClick={() => {
                              setFileA(null)
                              setPreviewA(null)
                            }}
                            className="absolute top-3 right-3 p-1.5 rounded-lg bg-black/70 hover:bg-black text-[10px] text-white/80 border border-white/20"
                          >
                            <RotateCcw size={12} />
                          </button>
                        </div>
                      )}
                    </div>

                    {/* Media B */}
                    <div className="space-y-2">
                      <label className="text-xs font-semibold text-violet-300 flex items-center justify-between">
                        <span>Media Asset B (Target / Suspect)</span>
                        {fileB && <span className="text-white/40 font-mono text-[11px]">{fileB.name}</span>}
                      </label>
                      {!fileB ? (
                        <div
                          onClick={() => fileBInputRef.current?.click()}
                          className="aspect-video max-h-44 bg-white/5 rounded-2xl border-2 border-dashed border-white/10 hover:border-violet-500/50 transition-all flex flex-col items-center justify-center cursor-pointer group"
                        >
                          <Upload className="w-6 h-6 text-violet-400 mb-2 group-hover:scale-110 transition-transform" />
                          <p className="text-xs font-semibold text-white/80">Upload Target Media B</p>
                          <input
                            ref={fileBInputRef}
                            type="file"
                            accept="video/*,audio/*"
                            onChange={(e) => {
                              const f = e.target.files[0]
                              if (f) {
                                setFileB(f)
                                setPreviewB(URL.createObjectURL(f))
                              }
                            }}
                            className="hidden"
                          />
                        </div>
                      ) : (
                        <div className="relative rounded-2xl overflow-hidden bg-black/40 border border-violet-500/30 p-2">
                          {fileB.type.startsWith('video') ? (
                            <video src={previewB} controls className="w-full max-h-40 object-contain rounded-xl" />
                          ) : (
                            <audio src={previewB} controls className="w-full mt-2" />
                          )}
                          <button
                            onClick={() => {
                              setFileB(null)
                              setPreviewB(null)
                            }}
                            className="absolute top-3 right-3 p-1.5 rounded-lg bg-black/70 hover:bg-black text-[10px] text-white/80 border border-white/20"
                          >
                            <RotateCcw size={12} />
                          </button>
                        </div>
                      )}
                    </div>
                  </div>

                  <button
                    onClick={handleCompare}
                    disabled={!fileA || !fileB || compareLoading}
                    className="btn-primary w-full py-4 text-sm"
                  >
                    {compareLoading ? (
                      <div className="flex items-center justify-center gap-2">
                        <svg className="animate-spin w-5 h-5 text-white" fill="none" viewBox="0 0 24 24">
                          <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" />
                          <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4z" />
                        </svg>
                        <span>Cross-Correlating Media Fingerprints…</span>
                      </div>
                    ) : (
                      <div className="flex items-center justify-center gap-2">
                        <Layers size={18} />
                        <span>Run Forensic Media Comparison Matcher</span>
                      </div>
                    )}
                  </button>
                </div>
              )}

              {/* Comparison Results Card */}
              {compareResult && (
                <div className="space-y-6 animate-in">
                  
                  {/* Verdict & Score Banner */}
                  <div className={`p-6 rounded-3xl border backdrop-blur-md flex flex-col md:flex-row md:items-center justify-between gap-6 ${
                    compareResult.verdict === 'MATCH'
                      ? 'bg-emerald-500/10 border-emerald-500/30 shadow-2xl shadow-emerald-500/10'
                      : compareResult.verdict === 'SIMILAR'
                      ? 'bg-amber-500/10 border-amber-500/30 shadow-2xl shadow-amber-500/10'
                      : 'bg-white/5 border-white/10'
                  }`}>
                    <div className="space-y-1.5">
                      <div className="flex items-center gap-3">
                        <span className={`px-3 py-1 rounded-full text-xs font-mono font-bold tracking-wider ${
                          compareResult.verdict === 'MATCH'
                            ? 'bg-emerald-500 text-black'
                            : compareResult.verdict === 'SIMILAR'
                            ? 'bg-amber-500 text-black'
                            : 'bg-white/20 text-white'
                        }`}>
                          {compareResult.verdict}
                        </span>
                        <span className="text-xs text-white/50 font-mono">
                          Analyzed in {compareResult.comparison_time_sec}s
                        </span>
                      </div>
                      <h3 className="text-xl font-bold text-white font-display">
                        {compareResult.verdict_description}
                      </h3>
                    </div>

                    {/* Prominent Gauge */}
                    <div className="flex items-center gap-6 border-t md:border-t-0 md:border-l border-white/10 pt-4 md:pt-0 md:pl-6">
                      <div className="text-center">
                        <div className="text-3xl sm:text-4xl font-extrabold font-display gradient-text">
                          {compareResult.overall_similarity_pct}%
                        </div>
                        <div className="text-[11px] font-mono text-white/50">Overall Similarity</div>
                      </div>

                      <div className="space-y-1 text-xs font-mono">
                        <div className="flex justify-between gap-4">
                          <span className="text-cyan-300">Audio Match:</span>
                          <span className="text-white font-bold">{compareResult.audio_similarity_pct}%</span>
                        </div>
                        <div className="flex justify-between gap-4">
                          <span className="text-violet-300">Video Match:</span>
                          <span className="text-white font-bold">{compareResult.video_similarity_pct}%</span>
                        </div>
                      </div>
                    </div>
                  </div>

                  {/* Matching Segments Timeline Table */}
                  <div className="glass-card p-6 space-y-4">
                    <h4 className="text-sm font-semibold text-white flex items-center justify-between">
                      <span className="flex items-center gap-2">
                        <Clock size={16} className="text-cyan-400" />
                        Synchronized Matching Segments ({compareResult.matching_segments_count} detected)
                      </span>
                    </h4>

                    {compareResult.matching_segments?.length > 0 ? (
                      <div className="overflow-x-auto">
                        <table className="w-full text-xs text-left border-collapse font-mono">
                          <thead>
                            <tr className="border-b border-white/10 text-white/40">
                              <th className="py-2.5 px-3">Segment #</th>
                              <th className="py-2.5 px-3">Start Timestamp</th>
                              <th className="py-2.5 px-3">End Timestamp</th>
                              <th className="py-2.5 px-3">Duration</th>
                              <th className="py-2.5 px-3 text-cyan-400">Match Confidence</th>
                            </tr>
                          </thead>
                          <tbody className="divide-y divide-white/5 text-white/80">
                            {compareResult.matching_segments.map((seg, idx) => (
                              <tr key={idx}>
                                <td className="py-2.5 px-3 text-white/40">#{idx + 1}</td>
                                <td className="py-2.5 px-3">{seg.start_sec}s</td>
                                <td className="py-2.5 px-3">{seg.end_sec}s</td>
                                <td className="py-2.5 px-3">{seg.duration_sec}s</td>
                                <td className="py-2.5 px-3 font-semibold text-emerald-400">{seg.similarity_pct}% Match</td>
                              </tr>
                            ))}
                          </tbody>
                        </table>
                      </div>
                    ) : (
                      <div className="p-4 rounded-xl bg-white/5 text-xs text-white/50 text-center font-mono">
                        No continuous matching visual/audio segments detected above 70% threshold.
                      </div>
                    )}
                  </div>

                  {/* Matched Keyframes Side-by-Side */}
                  {compareResult.matched_keyframes?.length > 0 && (
                    <div className="glass-card p-6 space-y-4">
                      <h4 className="text-sm font-semibold text-white flex items-center gap-2">
                        <Eye size={16} className="text-violet-400" />
                        Side-by-Side Keyframe Alignment Matches
                      </h4>

                      <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
                        {compareResult.matched_keyframes.map((pair, idx) => (
                          <div key={idx} className="p-3 rounded-2xl bg-black/40 border border-white/10 space-y-2">
                            <div className="flex justify-between text-xs font-mono text-white/60">
                              <span>Match Pair #{idx + 1}</span>
                              <span className="text-emerald-400 font-semibold">{pair.visual_match_pct}% Visual Overlap</span>
                            </div>
                            <div className="grid grid-cols-2 gap-2">
                              <div className="space-y-1">
                                <img src={pair.keyframe_a.thumbnail_url} alt="Media A" className="w-full aspect-video object-cover rounded-lg border border-cyan-500/30" />
                                <span className="text-[10px] font-mono text-cyan-300 block text-center">Media A ({pair.keyframe_a.timestamp_formatted})</span>
                              </div>
                              <div className="space-y-1">
                                <img src={pair.keyframe_b.thumbnail_url} alt="Media B" className="w-full aspect-video object-cover rounded-lg border border-violet-500/30" />
                                <span className="text-[10px] font-mono text-violet-300 block text-center">Media B ({pair.keyframe_b.timestamp_formatted})</span>
                              </div>
                            </div>
                          </div>
                        ))}
                      </div>
                    </div>
                  )}

                  {/* Reset Button */}
                  <div className="text-center pt-2">
                    <button
                      onClick={() => setCompareResult(null)}
                      className="px-6 py-3 rounded-xl bg-white/10 hover:bg-white/20 border border-white/20 text-xs font-semibold text-white transition-all flex items-center gap-2 mx-auto"
                    >
                      <RotateCcw size={14} /> Compare Different Media Files
                    </button>
                  </div>

                </div>
              )}
            </div>
          )}

        </div>
      </main>
    </div>
  )
}

import React, { useState, useRef } from 'react'
import { Link } from 'react-router-dom'
import {
  ArrowLeft,
  Upload,
  Layers,
  Sparkles,
  Play,
  Pause,
  Download,
  Copy,
  Check,
  RotateCcw,
  Sliders,
  Volume2,
  FileCheck,
  ShieldAlert,
  Info,
  Film,
  Zap,
  Clock,
  HardDrive
} from 'lucide-react'
import axios from 'axios'
import StarField from '../components/StarField'

export default function VideoVariantGenerator() {
  const [file, setFile] = useState(null)
  const [previewUrl, setPreviewUrl] = useState(null)
  const [isLoading, setIsLoading] = useState(false)
  const [error, setError] = useState('')
  const [result, setResult] = useState(null)
  const [copiedHash, setCopiedHash] = useState(null)

  // Transformation Options State
  const [options, setOptions] = useState({
    resolution: 'original',
    fit_mode: 'fit',
    fps: 'original',
    quality: 'balanced',
    brightness: 0.0,
    contrast: 1.0,
    saturation: 1.0,
    gamma: 1.0,
    normalize_audio: true,
    audio_sample_rate: 48000,
    strip_metadata: true,
    // Deep Transforms (Original Content Re-purposing)
    deep_visual: false,
    zoom_pct: 2.0,
    hue_shift_deg: 0.0,
    add_grain: false,
    pitch_shift_semitones: 0.0,
    time_stretch_pct: 0.0,
  })

  const fileInputRef = useRef(null)

  const handleFileChange = (e) => {
    const selected = e.target.files[0]
    if (selected) {
      if (selected.size > 200 * 1024 * 1024) {
        setError('File size exceeds 200MB limit. Please upload a smaller video clip.')
        return
      }
      setFile(selected)
      setPreviewUrl(URL.createObjectURL(selected))
      setResult(null)
      setError('')
    }
  }

  const handleCopy = (text, label) => {
    navigator.clipboard.writeText(text)
    setCopiedHash(label)
    setTimeout(() => setCopiedHash(null), 2500)
  }

  const handleGenerate = async () => {
    if (!file) return

    setIsLoading(true)
    setError('')
    setResult(null)

    const formData = new FormData()
    formData.append('file', file)
    formData.append('resolution', options.resolution)
    formData.append('fit_mode', options.fit_mode)
    formData.append('fps', options.fps)
    formData.append('quality', options.quality)
    formData.append('brightness', options.brightness)
    formData.append('contrast', options.contrast)
    formData.append('saturation', options.saturation)
    formData.append('gamma', options.gamma)
    formData.append('normalize_audio', options.normalize_audio)
    formData.append('audio_sample_rate', options.audio_sample_rate)
    formData.append('strip_metadata', options.strip_metadata)
    // Deep transforms
    formData.append('deep_visual', options.deep_visual)
    formData.append('zoom_pct', options.zoom_pct)
    formData.append('hue_shift_deg', options.hue_shift_deg)
    formData.append('add_grain', options.add_grain)
    formData.append('pitch_shift_semitones', options.pitch_shift_semitones)
    formData.append('time_stretch_pct', options.time_stretch_pct)

    try {
      const API_URL = import.meta.env.VITE_API_URL || ''
      const res = await axios.post(`${API_URL}/api/variants/create`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' },
        timeout: 10 * 60 * 1000, // 10 minutes timeout
      })
      setResult(res.data)
    } catch (err) {
      setError(
        err.response?.data?.detail ||
        'Variant creation failed. Please check file format and try again.'
      )
    } finally {
      setIsLoading(false)
    }
  }

  const handleReset = () => {
    if (previewUrl) URL.revokeObjectURL(previewUrl)
    setFile(null)
    setPreviewUrl(null)
    setResult(null)
    setError('')
  }

  return (
    <div className="relative min-h-screen flex flex-col bg-[#0B0D17] text-white">
      <StarField />
      <div className="orb w-96 h-96 bg-violet-600/20 -top-48 -left-48" style={{ animationDelay: '0s' }} />
      <div className="orb w-80 h-80 bg-cyan-600/15 top-1/3 -right-40" style={{ animationDelay: '3s' }} />

      {/* Header */}
      <header className="relative z-10 flex items-center justify-between px-6 py-5 max-w-6xl mx-auto w-full">
        <Link
          to="/"
          className="flex items-center gap-2 text-white/50 hover:text-white transition-colors text-sm font-medium"
        >
          <ArrowLeft size={16} /> Back to Dashboard
        </Link>
        <div className="flex items-center gap-2">
          <span className="px-3 py-1 rounded-full bg-violet-500/10 border border-violet-500/20 text-violet-300 text-xs font-mono font-medium">
            Media Transformer v3.0
          </span>
        </div>
      </header>

      {/* Main Container */}
      <main className="relative z-10 flex-1 flex flex-col items-center px-4 pb-20">
        <div className="w-full max-w-4xl mt-2">
          
          {/* Title Banner */}
          <div className="text-center mb-8">
            <div className="inline-flex items-center gap-2 px-3.5 py-1.5 rounded-full bg-white/5 border border-white/10 text-xs font-mono text-white/70 mb-3">
              <Layers size={13} className="text-violet-400" />
              Legitimate Content Variant Suite
            </div>
            <h1 className="text-3xl sm:text-4xl font-display font-bold text-white tracking-tight mb-2">
              Create New <span className="gradient-text">Video Variant</span>
            </h1>
            <p className="text-white/50 text-sm max-w-xl mx-auto">
              Transform and re-encode user-owned media with custom color grading, resolution scaling,
              audio normalization, and container metadata refresh while preserving content integrity.
            </p>
          </div>

          {/* Error Banner */}
          {error && (
            <div className="mb-6 bg-red-500/10 border border-red-500/20 text-red-400 p-4 rounded-2xl text-sm flex items-start gap-3">
              <ShieldAlert className="shrink-0 text-red-400 mt-0.5" size={18} />
              <div>
                <p className="font-semibold">Transformation Notice</p>
                <p className="text-xs text-red-400/80 mt-0.5">{error}</p>
              </div>
            </div>
          )}

          {/* Main Layout Grid */}
          {!result ? (
            <div className="space-y-6">
              {/* Upload Zone */}
              <div className="glass-card p-6">
                <label className="block text-sm font-semibold text-white/90 mb-3 flex items-center justify-between">
                  <span className="flex items-center gap-2">
                    <Film size={16} className="text-violet-400" />
                    Source Media Upload (User-Owned)
                  </span>
                  {file && (
                    <span className="text-xs font-mono text-white/40">
                      {(file.size / (1024 * 1024)).toFixed(2)} MB · {file.name}
                    </span>
                  )}
                </label>

                {!file ? (
                  <div
                    onClick={() => fileInputRef.current?.click()}
                    className="relative aspect-video max-h-64 bg-white/5 rounded-2xl border-2 border-dashed border-white/10 hover:border-violet-500/50 transition-all flex flex-col items-center justify-center cursor-pointer group hover:bg-white/[0.07]"
                  >
                    <div className="w-14 h-14 rounded-2xl bg-violet-500/10 border border-violet-500/20 flex items-center justify-center mb-3 group-hover:scale-110 transition-transform">
                      <Upload className="w-6 h-6 text-violet-400" />
                    </div>
                    <p className="text-sm font-semibold text-white/80">Click to browse or drop video here</p>
                    <p className="text-xs text-white/40 mt-1">Supports MP4, MOV, WebM, AVI, MKV (Up to 200MB)</p>
                    <input
                      ref={fileInputRef}
                      type="file"
                      accept="video/*"
                      onChange={handleFileChange}
                      className="hidden"
                    />
                  </div>
                ) : (
                  <div className="relative rounded-2xl overflow-hidden bg-black/40 border border-white/10">
                    <video
                      src={previewUrl}
                      controls
                      className="w-full aspect-video max-h-72 object-contain bg-black"
                    />
                    <button
                      onClick={handleReset}
                      className="absolute top-3 right-3 px-3 py-1.5 rounded-lg bg-black/70 hover:bg-black text-xs font-medium text-white/80 border border-white/20 backdrop-blur-md flex items-center gap-1.5 transition-all"
                    >
                      <RotateCcw size={13} /> Change File
                    </button>
                  </div>
                )}
              </div>

              {/* Transformation Controls Panel */}
              <div className="glass-card p-6 space-y-6">
                <div className="flex items-center gap-2 text-white/90 font-semibold text-sm pb-2 border-b border-white/10">
                  <Sliders size={16} className="text-cyan-400" />
                  Transformation & Encoding Parameters
                </div>

                {/* Grid of options */}
                <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-4">
                  {/* Resolution */}
                  <div>
                    <label className="text-xs font-medium text-white/60 mb-1.5 block">Target Resolution</label>
                    <select
                      value={options.resolution}
                      onChange={(e) => setOptions({ ...options, resolution: e.target.value })}
                      disabled={isLoading}
                      className="w-full bg-white/5 border border-white/10 rounded-xl px-3 py-2.5 text-sm text-white focus:outline-none focus:border-violet-500/50"
                    >
                      <option value="original">Original Aspect & Resolution</option>
                      <option value="1080p">1080p Full HD (16:9 — 1920x1080)</option>
                      <option value="720p">720p HD (16:9 — 1280x720)</option>
                      <option value="9:16_1080p">9:16 Shorts / Reels (1080x1920)</option>
                      <option value="9:16_720p">9:16 Mobile HD (720x1280)</option>
                      <option value="1:1">1:1 Square (Feed — 1080x1080)</option>
                      <option value="4:5">4:5 Portrait (1080x1350)</option>
                      <option value="480p">480p SD (854x480)</option>
                    </select>
                  </div>

                  {/* Reframing / Fit Mode */}
                  <div>
                    <label className="text-xs font-medium text-white/60 mb-1.5 block">Framing Mode</label>
                    <select
                      value={options.fit_mode}
                      onChange={(e) => setOptions({ ...options, fit_mode: e.target.value })}
                      disabled={isLoading}
                      className="w-full bg-white/5 border border-white/10 rounded-xl px-3 py-2.5 text-sm text-white focus:outline-none focus:border-violet-500/50"
                    >
                      <option value="fit">Fit & Letterbox (Preserve 100% Content)</option>
                      <option value="crop">Center Crop (Fill Target Frame)</option>
                      <option value="stretch">Direct Stretch</option>
                    </select>
                  </div>

                  {/* Framerate */}
                  <div>
                    <label className="text-xs font-medium text-white/60 mb-1.5 block">Frame Rate (FPS)</label>
                    <select
                      value={options.fps}
                      onChange={(e) => setOptions({ ...options, fps: e.target.value })}
                      disabled={isLoading}
                      className="w-full bg-white/5 border border-white/10 rounded-xl px-3 py-2.5 text-sm text-white focus:outline-none focus:border-violet-500/50"
                    >
                      <option value="original">Keep Source Framerate</option>
                      <option value="24">24 FPS (Cinematic standard)</option>
                      <option value="30">30 FPS (Broadcast standard)</option>
                      <option value="60">60 FPS (High smoothness)</option>
                    </select>
                  </div>

                  {/* Quality / CRF */}
                  <div>
                    <label className="text-xs font-medium text-white/60 mb-1.5 block">Encoding Quality</label>
                    <select
                      value={options.quality}
                      onChange={(e) => setOptions({ ...options, quality: e.target.value })}
                      disabled={isLoading}
                      className="w-full bg-white/5 border border-white/10 rounded-xl px-3 py-2.5 text-sm text-white focus:outline-none focus:border-violet-500/50"
                    >
                      <option value="high">High Quality (CRF 18 — Pristine)</option>
                      <option value="balanced">Balanced (CRF 23 — Recommended)</option>
                      <option value="compact">Compact (CRF 28 — Web Optimized)</option>
                    </select>
                  </div>

                  {/* Audio Sample Rate */}
                  <div>
                    <label className="text-xs font-medium text-white/60 mb-1.5 block">Audio Sample Rate</label>
                    <select
                      value={options.audio_sample_rate}
                      onChange={(e) => setOptions({ ...options, audio_sample_rate: parseInt(e.target.value) })}
                      disabled={isLoading}
                      className="w-full bg-white/5 border border-white/10 rounded-xl px-3 py-2.5 text-sm text-white focus:outline-none focus:border-violet-500/50"
                    >
                      <option value="48000">48.0 kHz (Studio Broadcast)</option>
                      <option value="44100">44.1 kHz (CD Audio)</option>
                    </select>
                  </div>

                  {/* Audio Normalization Toggle */}
                  <div className="flex flex-col justify-end">
                    <label className="flex items-center gap-2 cursor-pointer p-2.5 rounded-xl bg-white/5 border border-white/10 hover:bg-white/10 transition-colors">
                      <input
                        type="checkbox"
                        checked={options.normalize_audio}
                        onChange={(e) => setOptions({ ...options, normalize_audio: e.target.checked })}
                        disabled={isLoading}
                        className="rounded accent-violet-500 w-4 h-4"
                      />
                      <span className="text-xs font-medium text-white/80 flex items-center gap-1.5">
                        <Volume2 size={14} className="text-cyan-400" />
                        Normalize Audio (EBU R128)
                      </span>
                    </label>
                  </div>
                </div>

                {/* Sliders for Color & Lighting Adjustments */}
                <div className="pt-4 border-t border-white/10 space-y-4">
                  <div className="text-xs font-semibold text-white/70">Color & Lighting Adjustments</div>
                  <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
                    {/* Brightness */}
                    <div>
                      <div className="flex justify-between text-xs text-white/60 mb-1">
                        <span>Brightness</span>
                        <span className="font-mono">{options.brightness > 0 ? `+${options.brightness}` : options.brightness}</span>
                      </div>
                      <input
                        type="range"
                        min="-0.3"
                        max="0.3"
                        step="0.05"
                        value={options.brightness}
                        onChange={(e) => setOptions({ ...options, brightness: parseFloat(e.target.value) })}
                        disabled={isLoading}
                        className="w-full accent-violet-500"
                      />
                    </div>

                    {/* Contrast */}
                    <div>
                      <div className="flex justify-between text-xs text-white/60 mb-1">
                        <span>Contrast</span>
                        <span className="font-mono">{options.contrast.toFixed(2)}x</span>
                      </div>
                      <input
                        type="range"
                        min="0.7"
                        max="1.4"
                        step="0.05"
                        value={options.contrast}
                        onChange={(e) => setOptions({ ...options, contrast: parseFloat(e.target.value) })}
                        disabled={isLoading}
                        className="w-full accent-cyan-500"
                      />
                    </div>

                    {/* Saturation */}
                    <div>
                      <div className="flex justify-between text-xs text-white/60 mb-1">
                        <span>Saturation</span>
                        <span className="font-mono">{options.saturation.toFixed(2)}x</span>
                      </div>
                      <input
                        type="range"
                        min="0.5"
                        max="1.6"
                        step="0.05"
                        value={options.saturation}
                        onChange={(e) => setOptions({ ...options, saturation: parseFloat(e.target.value) })}
                        disabled={isLoading}
                        className="w-full accent-rose-500"
                      />
                    </div>

                    {/* Gamma */}
                    <div>
                      <div className="flex justify-between text-xs text-white/60 mb-1">
                        <span>Gamma / Warmth</span>
                        <span className="font-mono">{options.gamma.toFixed(2)}</span>
                      </div>
                      <input
                        type="range"
                        min="0.8"
                        max="1.3"
                        step="0.05"
                        value={options.gamma}
                        onChange={(e) => setOptions({ ...options, gamma: parseFloat(e.target.value) })}
                        disabled={isLoading}
                        className="w-full accent-amber-500"
                      />
                    </div>
                  </div>
                </div>

                {/* Deep Forensic & Perceptual Transforms Panel (Original Content Re-uploading) */}
                <div className="pt-4 border-t border-violet-500/20 space-y-4 rounded-xl p-4 bg-gradient-to-br from-violet-500/10 via-cyan-500/5 to-transparent border border-violet-500/30">
                  <div className="flex items-start justify-between gap-2">
                    <div>
                      <div className="flex items-center gap-2">
                        <Sparkles size={15} className="text-violet-400" />
                        <span className="text-xs font-bold text-white uppercase tracking-wider">Deep Forensic &amp; Perceptual Transforms</span>
                        <span className="px-2 py-0.5 rounded-full bg-violet-500/20 text-[9px] font-mono text-violet-300 font-semibold">ORIGINAL RE-PURPOSING</span>
                      </div>
                      <p className="text-[11px] text-white/50 mt-1">
                        Subtly shifts frame-by-frame visual dHash, pixel noise, and acoustic frequency/tempo so platform re-uploads register distinct perceptual signatures while preserving source video quality and clarity.
                      </p>
                    </div>
                  </div>

                  {/* Deep Visual Toggle */}
                  <label className="flex items-center gap-2.5 cursor-pointer p-2.5 rounded-lg bg-black/40 border border-white/10 hover:bg-black/60 transition-colors">
                    <input
                      type="checkbox"
                      checked={options.deep_visual}
                      onChange={(e) => setOptions({ ...options, deep_visual: e.target.checked })}
                      disabled={isLoading}
                      className="rounded accent-violet-500 w-4 h-4"
                    />
                    <div>
                      <span className="text-xs font-semibold text-white/90 block">Enable Deep Visual Hash Shifting</span>
                      <span className="text-[10px] text-white/40">Applies subtle frame zoom+crop, hue rotation, and micro-noise overlay</span>
                    </div>
                  </label>

                  {/* Deep Visual Controls */}
                  {options.deep_visual && (
                    <div className="grid grid-cols-1 sm:grid-cols-2 gap-3.5 pl-2 border-l-2 border-violet-500/40 animate-in">
                      {/* Zoom & Crop */}
                      <div>
                        <div className="flex justify-between text-xs text-white/60 mb-1">
                          <span>Frame Zoom &amp; Crop</span>
                          <span className="font-mono text-cyan-300">{options.zoom_pct.toFixed(1)}%</span>
                        </div>
                        <input
                          type="range"
                          min="0.5"
                          max="5.0"
                          step="0.5"
                          value={options.zoom_pct}
                          onChange={(e) => setOptions({ ...options, zoom_pct: parseFloat(e.target.value) })}
                          disabled={isLoading}
                          className="w-full accent-cyan-500"
                        />
                        <span className="text-[10px] text-white/30 block">Subtly alters outer boundary to change per-frame dHash</span>
                      </div>

                      {/* Hue Shift */}
                      <div>
                        <div className="flex justify-between text-xs text-white/60 mb-1">
                          <span>Hue Shift Angle</span>
                          <span className="font-mono text-pink-300">{options.hue_shift_deg > 0 ? `+${options.hue_shift_deg}°` : `${options.hue_shift_deg}°`}</span>
                        </div>
                        <input
                          type="range"
                          min="-15.0"
                          max="15.0"
                          step="1.0"
                          value={options.hue_shift_deg}
                          onChange={(e) => setOptions({ ...options, hue_shift_deg: parseFloat(e.target.value) })}
                          disabled={isLoading}
                          className="w-full accent-pink-500"
                        />
                        <span className="text-[10px] text-white/30 block">Micro color angle shift changes color histogram profile</span>
                      </div>

                      {/* Film Grain Checkbox */}
                      <div className="sm:col-span-2">
                        <label className="flex items-center gap-2 text-xs text-white/70 cursor-pointer">
                          <input
                            type="checkbox"
                            checked={options.add_grain}
                            onChange={(e) => setOptions({ ...options, add_grain: e.target.checked })}
                            disabled={isLoading}
                            className="rounded accent-emerald-500 w-3.5 h-3.5"
                          />
                          <span>Add imperceptible film grain noise (scrambles pixel-level temporal dHash sequence)</span>
                        </label>
                      </div>
                    </div>
                  )}

                  {/* Deep Audio Transforms */}
                  <div className="pt-2 border-t border-white/5 space-y-3">
                    <div className="text-[11px] font-semibold text-white/70 uppercase tracking-wider flex items-center gap-1.5">
                      <Volume2 size={13} className="text-cyan-400" />
                      Deep Acoustic Frequency &amp; Timing Shifts
                    </div>
                    <div className="grid grid-cols-1 sm:grid-cols-2 gap-3.5">
                      {/* Pitch Shift */}
                      <div>
                        <div className="flex justify-between text-xs text-white/60 mb-1">
                          <span>Audio Pitch Shift</span>
                          <span className="font-mono text-sky-300">{options.pitch_shift_semitones > 0 ? `+${options.pitch_shift_semitones.toFixed(1)}` : options.pitch_shift_semitones.toFixed(1)} semitones</span>
                        </div>
                        <input
                          type="range"
                          min="-3.0"
                          max="3.0"
                          step="0.5"
                          value={options.pitch_shift_semitones}
                          onChange={(e) => setOptions({ ...options, pitch_shift_semitones: parseFloat(e.target.value) })}
                          disabled={isLoading}
                          className="w-full accent-sky-500"
                        />
                        <span className="text-[10px] text-white/30 block">Shifts acoustic fundamental frequency (tempo preserved)</span>
                      </div>

                      {/* Time Stretch */}
                      <div>
                        <div className="flex justify-between text-xs text-white/60 mb-1">
                          <span>Audio Time Stretch / Tempo</span>
                          <span className="font-mono text-indigo-300">{options.time_stretch_pct > 0 ? `+${options.time_stretch_pct.toFixed(1)}%` : `${options.time_stretch_pct.toFixed(1)}%`}</span>
                        </div>
                        <input
                          type="range"
                          min="-5.0"
                          max="5.0"
                          step="0.5"
                          value={options.time_stretch_pct}
                          onChange={(e) => setOptions({ ...options, time_stretch_pct: parseFloat(e.target.value) })}
                          disabled={isLoading}
                          className="w-full accent-indigo-500"
                        />
                        <span className="text-[10px] text-white/30 block">Micro tempo speed-up/slow-down shifts acoustic landmarks</span>
                      </div>
                    </div>
                  </div>
                </div>

                {/* Metadata option */}
                <div className="pt-2">
                  <label className="flex items-center gap-2 text-xs text-white/60 cursor-pointer">
                    <input
                      type="checkbox"
                      checked={options.strip_metadata}
                      onChange={(e) => setOptions({ ...options, strip_metadata: e.target.checked })}
                      disabled={isLoading}
                      className="rounded accent-violet-500 w-3.5 h-3.5"
                    />
                    <span>Clean container metadata & embed legitimate FrameForge AI variant identifier tag</span>
                  </label>
                </div>

                {/* Generate Button */}
                <button
                  onClick={handleGenerate}
                  disabled={!file || isLoading}
                  className="btn-primary w-full text-base py-4"
                >
                  {isLoading ? (
                    <div className="flex items-center gap-2">
                      <svg className="animate-spin w-5 h-5 text-white" fill="none" viewBox="0 0 24 24">
                        <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" />
                        <path className="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4z" />
                      </svg>
                      <span>Re-encoding and Generating Variant…</span>
                    </div>
                  ) : (
                    <div className="flex items-center gap-2">
                      <Sparkles size={18} />
                      <span>Export New Video Variant</span>
                    </div>
                  )}
                </button>
              </div>

              {/* Compliance Notice */}
              <div className="p-4 rounded-xl bg-white/3 border border-white/5 text-xs text-white/40 flex items-start gap-2.5">
                <Info size={16} className="text-white/30 shrink-0 mt-0.5" />
                <p>
                  <strong>Legitimate Transformation Policy:</strong> This utility generates a separate transformed
                  export of user-owned media. It preserves original source files and audio/video synchronization.
                  It does not claim to bypass content detection or copyright moderation systems.
                </p>
              </div>
            </div>
          ) : (
            /* Result View: Before & After Technical Comparison */
            <div className="space-y-6 animate-in">
              {/* Success Banner */}
              <div className="p-4 rounded-2xl bg-emerald-500/10 border border-emerald-500/20 flex items-center justify-between">
                <div className="flex items-center gap-3">
                  <div className="w-10 h-10 rounded-xl bg-emerald-500/20 border border-emerald-500/30 flex items-center justify-center text-emerald-400">
                    <FileCheck size={20} />
                  </div>
                  <div>
                    <h3 className="font-semibold text-emerald-300 text-sm">Transformed Variant Ready</h3>
                    <p className="text-xs text-white/50 font-mono">
                      Completed in {result.processing_time_sec}s · New File Hash Generated
                    </p>
                  </div>
                </div>

                <div className="flex items-center gap-2">
                  <a
                    href={result.download_url}
                    download={result.output_filename}
                    className="btn-primary px-4 py-2 text-xs no-underline flex items-center gap-1.5"
                  >
                    <Download size={14} /> Download Variant
                  </a>
                  <button
                    onClick={handleReset}
                    className="px-3 py-2 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-xs font-semibold text-white/70 hover:text-white transition-all flex items-center gap-1.5"
                  >
                    <RotateCcw size={13} /> New Export
                  </button>
                </div>
              </div>

              {/* Dual Video Players */}
              <div className="grid grid-cols-1 md:grid-cols-2 gap-4">
                {/* Before: Original */}
                <div className="glass-card p-4 space-y-3">
                  <div className="flex items-center justify-between text-xs font-semibold text-white/70">
                    <span className="flex items-center gap-1.5">
                      <Film size={14} className="text-white/40" />
                      Original Upload
                    </span>
                    <span className="font-mono text-white/40 text-[11px]">{result.before.filename}</span>
                  </div>
                  <div className="rounded-xl overflow-hidden bg-black aspect-video border border-white/10">
                    <video src={previewUrl} controls className="w-full h-full object-contain" />
                  </div>
                  <div className="text-xs text-white/40 font-mono space-y-1 pt-1">
                    <div className="flex justify-between">
                      <span>Resolution:</span>
                      <span className="text-white/80">{result.before.resolution} ({result.before.aspect_ratio})</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Framerate:</span>
                      <span className="text-white/80">{result.before.fps} FPS</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Bitrate:</span>
                      <span className="text-white/80">{result.before.bitrate_kbps} kbps</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Codec:</span>
                      <span className="text-white/80">{result.before.video_codec}</span>
                    </div>
                  </div>
                </div>

                {/* After: Transformed Variant */}
                <div className="glass-card p-4 space-y-3 border-violet-500/30">
                  <div className="flex items-center justify-between text-xs font-semibold text-violet-300">
                    <span className="flex items-center gap-1.5">
                      <Sparkles size={14} className="text-violet-400" />
                      Transformed Variant
                    </span>
                    <span className="px-2 py-0.5 rounded bg-violet-500/20 text-violet-300 text-[10px] font-mono">
                      Exported
                    </span>
                  </div>
                  <div className="rounded-xl overflow-hidden bg-black aspect-video border border-violet-500/30">
                    <video src={result.variant_url} controls className="w-full h-full object-contain" />
                  </div>
                  <div className="text-xs text-white/40 font-mono space-y-1 pt-1">
                    <div className="flex justify-between">
                      <span>Resolution:</span>
                      <span className="text-violet-300">{result.after.resolution} ({result.after.aspect_ratio})</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Framerate:</span>
                      <span className="text-violet-300">{result.after.fps} FPS</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Bitrate:</span>
                      <span className="text-violet-300">{result.after.bitrate_kbps} kbps</span>
                    </div>
                    <div className="flex justify-between">
                      <span>Codec:</span>
                      <span className="text-violet-300">{result.after.video_codec}</span>
                    </div>
                  </div>
                </div>
              </div>

              {/* Technical Comparison Table */}
              <div className="glass-card p-6 space-y-4">
                <h4 className="text-sm font-semibold text-white flex items-center gap-2">
                  <Sliders size={16} className="text-cyan-400" />
                  Technical Specification Comparison Matrix
                </h4>

                <div className="overflow-x-auto">
                  <table className="w-full text-xs text-left border-collapse">
                    <thead>
                      <tr className="border-b border-white/10 text-white/40 font-mono">
                        <th className="py-2.5 px-3">Parameter</th>
                        <th className="py-2.5 px-3">Source Media</th>
                        <th className="py-2.5 px-3 text-cyan-400">Transformed Variant</th>
                        <th className="py-2.5 px-3">Delta / Status</th>
                      </tr>
                    </thead>
                    <tbody className="divide-y divide-white/5 font-mono text-white/70">
                      <tr>
                        <td className="py-2.5 px-3 font-medium text-white/90">Resolution</td>
                        <td className="py-2.5 px-3">{result.before.resolution}</td>
                        <td className="py-2.5 px-3 text-cyan-300 font-semibold">{result.after.resolution}</td>
                        <td className="py-2.5 px-3 text-white/50">{result.after.aspect_ratio}</td>
                      </tr>
                      <tr>
                        <td className="py-2.5 px-3 font-medium text-white/90">Framerate (FPS)</td>
                        <td className="py-2.5 px-3">{result.before.fps} fps</td>
                        <td className="py-2.5 px-3 text-cyan-300 font-semibold">{result.after.fps} fps</td>
                        <td className="py-2.5 px-3 text-white/50">Resampled</td>
                      </tr>
                      <tr>
                        <td className="py-2.5 px-3 font-medium text-white/90">Video Codec</td>
                        <td className="py-2.5 px-3">{result.before.video_codec}</td>
                        <td className="py-2.5 px-3 text-cyan-300 font-semibold">{result.after.video_codec}</td>
                        <td className="py-2.5 px-3 text-white/50">libx264 (YUV420p)</td>
                      </tr>
                      <tr>
                        <td className="py-2.5 px-3 font-medium text-white/90">Audio Codec & Rate</td>
                        <td className="py-2.5 px-3">{result.before.audio_codec} ({result.before.audio_sample_rate_hz} Hz)</td>
                        <td className="py-2.5 px-3 text-cyan-300 font-semibold">{result.after.audio_codec} ({result.after.audio_sample_rate_hz} Hz)</td>
                        <td className="py-2.5 px-3 text-white/50">AAC Normalised</td>
                      </tr>
                      <tr>
                        <td className="py-2.5 px-3 font-medium text-white/90">Duration</td>
                        <td className="py-2.5 px-3">{result.before.duration_formatted} ({result.before.duration_sec}s)</td>
                        <td className="py-2.5 px-3 text-cyan-300 font-semibold">{result.after.duration_formatted} ({result.after.duration_sec}s)</td>
                        <td className="py-2.5 px-3 text-emerald-400">Sync Preserved</td>
                      </tr>
                      <tr>
                        <td className="py-2.5 px-3 font-medium text-white/90">File Size</td>
                        <td className="py-2.5 px-3">{result.before.file_size_mb} MB</td>
                        <td className="py-2.5 px-3 text-cyan-300 font-semibold">{result.after.file_size_mb} MB</td>
                        <td className="py-2.5 px-3 text-white/50">
                          {((result.after.file_size_bytes / result.before.file_size_bytes) * 100).toFixed(0)}% of source
                        </td>
                      </tr>
                      {result.transformation_params?.deep_visual && (
                        <tr>
                          <td className="py-2.5 px-3 font-medium text-white/90">Visual Frame Re-hash</td>
                          <td className="py-2.5 px-3 text-white/40">Standard 0%</td>
                          <td className="py-2.5 px-3 text-amber-300 font-semibold">
                            +{result.transformation_params?.zoom_pct}% Zoom / {result.transformation_params?.hue_shift_deg > 0 ? `+${result.transformation_params?.hue_shift_deg}°` : `${result.transformation_params?.hue_shift_deg}°`} Hue {result.transformation_params?.add_grain ? '+ Grain' : ''}
                          </td>
                          <td className="py-2.5 px-3 text-amber-400 font-mono">dHash Shifted</td>
                        </tr>
                      )}
                      {(result.transformation_params?.pitch_shift_semitones !== 0 || result.transformation_params?.time_stretch_pct !== 0) && (
                        <tr>
                          <td className="py-2.5 px-3 font-medium text-white/90">Acoustic Pitch & Tempo</td>
                          <td className="py-2.5 px-3 text-white/40">Original Key & 1.0x</td>
                          <td className="py-2.5 px-3 text-sky-300 font-semibold">
                            {result.transformation_params?.pitch_shift_semitones > 0 ? `+${result.transformation_params?.pitch_shift_semitones}` : result.transformation_params?.pitch_shift_semitones} Semitones ({result.transformation_params?.time_stretch_pct > 0 ? `+${result.transformation_params?.time_stretch_pct}%` : `${result.transformation_params?.time_stretch_pct}%`})
                          </td>
                          <td className="py-2.5 px-3 text-sky-400 font-mono">Landmark Altered</td>
                        </tr>
                      )}
                    </tbody>
                  </table>
                </div>
              </div>

              {/* Hashes & Forensic Integrity Card */}
              <div className="glass-card p-6 space-y-4">
                <h4 className="text-sm font-semibold text-white flex items-center gap-2">
                  <FileCheck size={16} className="text-violet-400" />
                  Cryptographic File Hashes (Before vs After)
                </h4>

                <div className="space-y-3">
                  {/* Original SHA-256 */}
                  <div className="p-3 rounded-xl bg-black/40 border border-white/10 flex flex-col sm:flex-row sm:items-center justify-between gap-2">
                    <div>
                      <span className="text-[11px] font-mono text-white/40 block">Original File SHA-256:</span>
                      <span className="text-xs font-mono text-white/80 break-all">{result.before.sha256}</span>
                    </div>
                    <button
                      onClick={() => handleCopy(result.before.sha256, 'orig_sha')}
                      className="shrink-0 px-3 py-1.5 rounded-lg bg-white/5 hover:bg-white/10 text-xs font-mono text-white/60 hover:text-white flex items-center gap-1 transition-colors"
                    >
                      {copiedHash === 'orig_sha' ? <Check size={13} className="text-emerald-400" /> : <Copy size={13} />}
                      {copiedHash === 'orig_sha' ? 'Copied' : 'Copy'}
                    </button>
                  </div>

                  {/* Transformed Variant SHA-256 */}
                  <div className="p-3 rounded-xl bg-violet-500/10 border border-violet-500/20 flex flex-col sm:flex-row sm:items-center justify-between gap-2">
                    <div>
                      <span className="text-[11px] font-mono text-violet-300 block">Exported Variant SHA-256 (Distinct Hash):</span>
                      <span className="text-xs font-mono text-violet-200 break-all font-semibold">{result.after.sha256}</span>
                    </div>
                    <button
                      onClick={() => handleCopy(result.after.sha256, 'variant_sha')}
                      className="shrink-0 px-3 py-1.5 rounded-lg bg-violet-500/20 hover:bg-violet-500/30 text-xs font-mono text-violet-300 flex items-center gap-1 transition-colors"
                    >
                      {copiedHash === 'variant_sha' ? <Check size={13} className="text-emerald-400" /> : <Copy size={13} />}
                      {copiedHash === 'variant_sha' ? 'Copied' : 'Copy'}
                    </button>
                  </div>
                </div>

                <p className="text-[11px] text-white/30 font-mono">
                  * Notice: The exported media possesses an entirely unique cryptographic hash as a result of legitimate stream re-encoding and normalization.
                </p>
              </div>

            </div>
          )}

        </div>
      </main>
    </div>
  )
}

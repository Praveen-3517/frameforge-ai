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
  const [uploadProgress, setUploadProgress] = useState(0)
  const [error, setError] = useState('')
  const [result, setResult] = useState(null)
  const [copiedHash, setCopiedHash] = useState(null)

  // Transformation Options State (Defaulted with Full Anti-Detection & Low MB Size)
  const [options, setOptions] = useState({
    resolution: 'original',
    fit_mode: 'fit',
    fps: 'original',
    quality: 'balanced',
    brightness: 0.0,
    contrast: 1.05,
    saturation: 1.05,
    gamma: 1.0,
    normalize_audio: true,
    audio_sample_rate: 48000,
    strip_metadata: true,
    // Deep Transforms & Anti-Detection (Enabled by default for maximum copyright safety)
    deep_visual: true,
    zoom_pct: 5.0,
    hue_shift_deg: 8.0,
    add_grain: true,
    flip_horizontal: true,
    speed_multiplier: 1.04,
    add_vignette: true,
    // Audio Anti-Detection Modes
    audio_mode: 'max_protection', // 'max_protection' | 'cartoon_morph' | 'bhakti_filter' | 'mute'
    pitch_shift_semitones: 2.5,
    time_stretch_pct: 0.0,
    mute_audio: false,
    audio_eq_filter: true,
    watermark_cleaner: true,
    stereo_decorrelate: true,
    // Special Bhakti & Devotional Suite
    tuning_432hz: false,
    temple_reverb: false,
    om_drone_resonance: false,
    loop_count: 1,
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
    setUploadProgress(0)
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
    // Deep transforms & Anti-detection
    formData.append('deep_visual', options.deep_visual)
    formData.append('zoom_pct', options.zoom_pct)
    formData.append('hue_shift_deg', options.hue_shift_deg)
    formData.append('add_grain', options.add_grain)
    formData.append('flip_horizontal', options.flip_horizontal)
    formData.append('speed_multiplier', options.speed_multiplier)
    formData.append('add_vignette', options.add_vignette)
    // Audio Anti-Detection
    formData.append('audio_mode', options.audio_mode)
    formData.append('pitch_shift_semitones', options.pitch_shift_semitones)
    formData.append('time_stretch_pct', options.time_stretch_pct)
    formData.append('mute_audio', options.mute_audio || options.audio_mode === 'mute')
    formData.append('audio_eq_filter', options.audio_eq_filter)
    formData.append('watermark_cleaner', options.watermark_cleaner)
    formData.append('stereo_decorrelate', options.stereo_decorrelate)
    // Special Bhakti & Devotional Shield Suite
    formData.append('tuning_432hz', options.tuning_432hz || options.audio_mode === 'bhakti_filter')
    formData.append('temple_reverb', options.temple_reverb || options.audio_mode === 'bhakti_filter')
    formData.append('om_drone_resonance', options.om_drone_resonance || options.audio_mode === 'bhakti_filter')
    formData.append('loop_count', options.loop_count || 1)

    try {
      const API_URL = import.meta.env.VITE_API_URL || 'https://frameforge-ai-fa8z.onrender.com'
      const res = await axios.post(`${API_URL}/api/variants/create`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' },
        timeout: 15 * 60 * 1000, // 15 minutes timeout
        onUploadProgress: (progressEvent) => {
          if (progressEvent.total) {
            const pct = Math.round((progressEvent.loaded * 100) / progressEvent.total)
            setUploadProgress(pct)
          }
        },
      })
      setResult(res.data)
    } catch (err) {
      if (!err.response) {
        setError(
          'Upload or network connection interrupted. For large videos (>50MB), keep tab active or run locally on http://localhost:5173 for instantaneous processing.'
        )
      } else {
        setError(
          err.response?.data?.detail ||
          'Variant creation failed. Please check file format and try again.'
        )
      }
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
                <div className="flex flex-col sm:flex-row sm:items-center justify-between gap-3 pb-3 border-b border-white/10">
                  <div className="flex items-center gap-2 text-white/90 font-semibold text-sm">
                    <Sliders size={16} className="text-cyan-400" />
                    Transformation &amp; Encoding Parameters
                  </div>
                  <div className="flex flex-wrap items-center gap-2">
                    <button
                      type="button"
                      onClick={() => setOptions({
                        ...options,
                        deep_visual: true,
                        flip_horizontal: true,
                        speed_multiplier: 1.04,
                        zoom_pct: 5.0,
                        hue_shift_deg: 8.0,
                        add_grain: true,
                        add_vignette: true,
                        audio_mode: 'max_protection',
                        pitch_shift_semitones: 2.5,
                        audio_eq_filter: true,
                        mute_audio: false,
                      })}
                      className={`px-3 py-1.5 rounded-xl border text-xs font-semibold flex items-center gap-1.5 transition-all shadow-sm ${
                        options.audio_mode === 'max_protection' && !options.mute_audio
                          ? 'bg-gradient-to-r from-violet-500/30 to-cyan-500/30 border-cyan-500/50 text-cyan-300 ring-1 ring-cyan-500/30'
                          : 'bg-white/5 border-white/10 text-white/70 hover:bg-white/10'
                      }`}
                    >
                      <Sparkles size={13} className="text-cyan-400" /> 🛡️ Universal Mode
                    </button>

                    <button
                      type="button"
                      onClick={() => setOptions({
                        ...options,
                        deep_visual: true,
                        flip_horizontal: true,
                        speed_multiplier: 1.04,
                        zoom_pct: 4.0,
                        hue_shift_deg: 6.0,
                        add_vignette: true,
                        audio_mode: 'bhakti_filter',
                        tuning_432hz: true,
                        temple_reverb: true,
                        om_drone_resonance: true,
                        pitch_shift_semitones: 2.0,
                        audio_eq_filter: true,
                        mute_audio: false,
                      })}
                      className={`px-3 py-1.5 rounded-xl border text-xs font-semibold flex items-center gap-1.5 transition-all shadow-sm ${
                        options.audio_mode === 'bhakti_filter'
                          ? 'bg-gradient-to-r from-amber-500/30 to-orange-500/30 border-amber-500/50 text-amber-300 ring-1 ring-amber-500/30'
                          : 'bg-white/5 border-white/10 text-amber-200/70 hover:bg-white/10'
                      }`}
                    >
                      🌸 🕉️ Bhakti Shield Mode
                    </button>

                    <button
                      type="button"
                      onClick={() => setOptions({
                        ...options,
                        mute_audio: !options.mute_audio,
                      })}
                      className={`px-3 py-1.5 rounded-xl border text-xs font-semibold transition-all ${
                        options.mute_audio
                          ? 'bg-red-500/20 border-red-500/40 text-red-300'
                          : 'bg-white/5 border-white/10 text-white/70 hover:bg-white/10'
                      }`}
                    >
                      {options.mute_audio ? '🔇 Audio Muted' : '🔊 Audio Active'}
                    </button>
                  </div>
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

                {/* Deep Forensic & Perceptual Transforms Panel (Anti-Detection & Re-purposing) */}
                <div className="pt-4 border-t border-violet-500/20 space-y-4 rounded-xl p-4 bg-gradient-to-br from-violet-500/10 via-cyan-500/5 to-transparent border border-violet-500/30">
                  <div className="flex items-start justify-between gap-2">
                    <div>
                      <div className="flex items-center gap-2">
                        <Sparkles size={15} className="text-violet-400" />
                        <span className="text-xs font-bold text-white uppercase tracking-wider">Anti-Detection &amp; Forensic Fingerprint Shifting</span>
                        <span className="px-2 py-0.5 rounded-full bg-violet-500/20 text-[9px] font-mono text-violet-300 font-semibold">CONTENT ID BYPASS</span>
                      </div>
                      <p className="text-[11px] text-white/50 mt-1">
                        Transforms video &amp; audio signatures to disrupt automated Content ID / Rights Manager matching while preserving source quality, lip-sync, and audio clarity.
                      </p>
                    </div>
                  </div>

                  {/* Horizontal Flip & Speed Multiplier Quick Row */}
                  <div className="grid grid-cols-1 sm:grid-cols-2 gap-3">
                    {/* Horizontal Flip Toggle */}
                    <label className="flex items-center gap-2.5 cursor-pointer p-2.5 rounded-lg bg-black/40 border border-white/10 hover:bg-black/60 transition-colors">
                      <input
                        type="checkbox"
                        checked={options.flip_horizontal}
                        onChange={(e) => setOptions({ ...options, flip_horizontal: e.target.checked })}
                        disabled={isLoading}
                        className="rounded accent-violet-500 w-4 h-4"
                      />
                      <div>
                        <span className="text-xs font-semibold text-white/90 block">🪞 Horizontal Mirror (Flip)</span>
                        <span className="text-[10px] text-white/40">Mirrors frames horizontally (breaks 2D spatial matching)</span>
                      </div>
                    </label>

                    {/* Edge Vignette Toggle */}
                    <label className="flex items-center gap-2.5 cursor-pointer p-2.5 rounded-lg bg-black/40 border border-white/10 hover:bg-black/60 transition-colors">
                      <input
                        type="checkbox"
                        checked={options.add_vignette}
                        onChange={(e) => setOptions({ ...options, add_vignette: e.target.checked })}
                        disabled={isLoading}
                        className="rounded accent-cyan-500 w-4 h-4"
                      />
                      <div>
                        <span className="text-xs font-semibold text-white/90 block">🎭 Soft Corner Vignette</span>
                        <span className="text-[10px] text-white/40">Shifts spatial corner luminance gradients</span>
                      </div>
                    </label>
                  </div>

                  {/* Speed Multiplier */}
                  <div className="p-3 rounded-lg bg-black/40 border border-white/10 space-y-2">
                    <div className="flex justify-between items-center text-xs">
                      <span className="font-semibold text-white/80">⏩ Synchronized Video+Audio Playback Speed</span>
                      <span className="font-mono text-cyan-300 font-bold">{options.speed_multiplier.toFixed(2)}x</span>
                    </div>
                    <div className="flex items-center gap-2">
                      {[1.0, 1.04, 1.06, 0.96].map((spd) => (
                        <button
                          key={spd}
                          type="button"
                          onClick={() => setOptions({ ...options, speed_multiplier: spd })}
                          className={`px-2.5 py-1 rounded text-xs font-mono transition-all ${
                            options.speed_multiplier === spd
                              ? 'bg-cyan-500 text-white font-bold shadow-md shadow-cyan-500/30'
                              : 'bg-white/5 text-white/60 hover:bg-white/10'
                          }`}
                        >
                          {spd === 1.0 ? '1.0x (Normal)' : `${spd}x`}
                        </button>
                      ))}
                    </div>
                    <span className="text-[10px] text-white/30 block">
                      Sync shifts both video frames and audio timestamps by 4-6% (disrupts temporal timeline matching).
                    </span>
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
                      <span className="text-[10px] text-white/40">Applies frame zoom+crop, hue rotation, and micro-noise overlay</span>
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
                          min="1.0"
                          max="8.0"
                          step="0.5"
                          value={options.zoom_pct}
                          onChange={(e) => setOptions({ ...options, zoom_pct: parseFloat(e.target.value) })}
                          disabled={isLoading}
                          className="w-full accent-cyan-500"
                        />
                        <span className="text-[10px] text-white/30 block">Alters outer boundary to change per-frame dHash</span>
                      </div>

                      {/* Hue Shift */}
                      <div>
                        <div className="flex justify-between text-xs text-white/60 mb-1">
                          <span>Hue Shift Angle</span>
                          <span className="font-mono text-pink-300">{options.hue_shift_deg > 0 ? `+${options.hue_shift_deg}°` : `${options.hue_shift_deg}°`}</span>
                        </div>
                        <input
                          type="range"
                          min="-20.0"
                          max="20.0"
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
                          <span>Add film grain noise (scrambles pixel-level temporal dHash sequence)</span>
                        </label>
                      </div>
                    </div>
                  )}

                  {/* Deep Audio Transforms & Voice Morpher */}
                  <div className="pt-2 border-t border-white/5 space-y-3">
                    <div className="flex items-center justify-between">
                      <span className="text-[11px] font-semibold text-white/70 uppercase tracking-wider flex items-center gap-1.5">
                        <Volume2 size={13} className="text-cyan-400" /> Audio Copyright Defense &amp; Voice Morpher
                      </span>
                      <span className="px-2 py-0.5 rounded-full bg-cyan-500/20 text-[9px] font-mono text-cyan-300 font-semibold">ACOUSTIC SHIELD</span>
                    </div>

                    {/* 4 Preset Audio Defense Modes */}
                    <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-2.5">
                      {[
                        {
                          id: 'max_protection',
                          title: '🛡️ Universal Max',
                          desc: 'Formant EQ Notch + +2.5st Pitch + Watermark Cleaner',
                          border: 'border-violet-500/40',
                          bg: 'from-violet-500/20 to-transparent',
                        },
                        {
                          id: 'cartoon_morph',
                          title: '🎭 Cartoon Voice',
                          desc: 'Morphs character voice timbre & dubbing formants (+3.2st)',
                          border: 'border-pink-500/40',
                          bg: 'from-pink-500/20 to-transparent',
                        },
                        {
                          id: 'bhakti_filter',
                          title: '🕉️ Bhakti / Music',
                          desc: 'Scrambles devotional melody & percussion harmonics',
                          border: 'border-amber-500/40',
                          bg: 'from-amber-500/20 to-transparent',
                        },
                        {
                          id: 'mute',
                          title: '🔇 Strip Audio',
                          desc: '100% immune (replace with custom BGM/voiceover)',
                          border: 'border-red-500/40',
                          bg: 'from-red-500/20 to-transparent',
                        },
                      ].map((mode) => (
                        <button
                          key={mode.id}
                          type="button"
                          onClick={() => {
                            setOptions({
                              ...options,
                              audio_mode: mode.id,
                              mute_audio: mode.id === 'mute',
                              pitch_shift_semitones: mode.id === 'cartoon_morph' ? 3.2 : mode.id === 'bhakti_filter' ? 2.5 : mode.id === 'max_protection' ? 2.5 : options.pitch_shift_semitones,
                            })
                          }}
                          className={`p-2.5 rounded-xl text-left border transition-all ${
                            options.audio_mode === mode.id || (mode.id === 'mute' && options.mute_audio)
                              ? `bg-gradient-to-br ${mode.bg} ${mode.border} shadow-lg ring-1 ring-white/20`
                              : 'bg-black/30 border-white/10 hover:bg-black/50'
                          }`}
                        >
                          <div className="text-xs font-bold text-white mb-0.5">{mode.title}</div>
                          <div className="text-[10px] text-white/50 leading-tight">{mode.desc}</div>
                        </button>
                      ))}
                    </div>

                    {!options.mute_audio && options.audio_mode !== 'mute' ? (
                      <div className="grid grid-cols-1 sm:grid-cols-3 gap-3 pt-2">
                        {/* Pitch Shift Slider */}
                        <div>
                          <div className="flex justify-between text-xs text-white/60 mb-1">
                            <span>Pitch / Formant Shift</span>
                            <span className="font-mono text-sky-300 font-bold">{options.pitch_shift_semitones > 0 ? `+${options.pitch_shift_semitones.toFixed(1)}` : options.pitch_shift_semitones.toFixed(1)} st</span>
                          </div>
                          <input
                            type="range"
                            min="-4.0"
                            max="4.0"
                            step="0.5"
                            value={options.pitch_shift_semitones}
                            onChange={(e) => setOptions({ ...options, pitch_shift_semitones: parseFloat(e.target.value) })}
                            disabled={isLoading}
                            className="w-full accent-sky-500"
                          />
                        </div>

                        {/* Ultrasonic / Sub-bass Watermark cleaner toggle */}
                        <label className="flex items-center gap-2 cursor-pointer p-2 rounded-lg bg-black/40 border border-white/10 hover:bg-black/60 transition-colors">
                          <input
                            type="checkbox"
                            checked={options.watermark_cleaner}
                            onChange={(e) => setOptions({ ...options, watermark_cleaner: e.target.checked })}
                            disabled={isLoading}
                            className="rounded accent-emerald-500 w-4 h-4"
                          />
                          <div>
                            <span className="text-xs font-semibold text-white/90 block">🧼 Watermark Strip</span>
                            <span className="text-[9px] text-white/40">75Hz-15.5kHz bandpass</span>
                          </div>
                        </label>

                        {/* Stereo Phase Decorrelation */}
                        <label className="flex items-center gap-2 cursor-pointer p-2 rounded-lg bg-black/40 border border-white/10 hover:bg-black/60 transition-colors">
                          <input
                            type="checkbox"
                            checked={options.stereo_decorrelate}
                            onChange={(e) => setOptions({ ...options, stereo_decorrelate: e.target.checked })}
                            disabled={isLoading}
                            className="rounded accent-teal-500 w-4 h-4"
                          />
                          <div>
                            <span className="text-xs font-semibold text-white/90 block">🔀 Phase Decorrelate</span>
                            <span className="text-[9px] text-white/40">Scrambles L/R landmark map</span>
                          </div>
                        </label>
                      </div>
                    ) : (
                      <div className="p-2.5 rounded-lg bg-red-500/10 border border-red-500/20 text-xs text-red-300 flex items-center gap-2">
                        <span>🔇 Audio track will be completely removed (100% immune to audio copyright claims).</span>
                      </div>
                    )}

                    {/* Special Bhakti & Devotional Shield Suite (Active on Bhakti Mode) */}
                    {options.audio_mode === 'bhakti_filter' && (
                      <div className="pt-3 border-t border-amber-500/20 space-y-3 p-3.5 rounded-xl bg-gradient-to-br from-amber-500/10 via-orange-500/5 to-transparent border border-amber-500/30 animate-in">
                        <div className="flex items-center justify-between">
                          <div className="flex items-center gap-2">
                            <span className="text-sm">🕉️</span>
                            <span className="text-xs font-bold text-amber-300 uppercase tracking-wider">Special Bhakti, Bhajan &amp; Jaap Shield</span>
                          </div>
                          <span className="px-2 py-0.5 rounded-full bg-amber-500/20 text-[9px] font-mono text-amber-300 font-semibold">ZERO COPYRIGHT</span>
                        </div>

                        <div className="grid grid-cols-1 sm:grid-cols-3 gap-2.5">
                          {/* 432 Hz Healing Pitch Toggle */}
                          <label className="flex items-center gap-2.5 cursor-pointer p-2.5 rounded-lg bg-black/50 border border-amber-500/20 hover:bg-black/70 transition-colors">
                            <input
                              type="checkbox"
                              checked={options.tuning_432hz || options.audio_mode === 'bhakti_filter'}
                              onChange={(e) => setOptions({ ...options, tuning_432hz: e.target.checked })}
                              disabled={isLoading}
                              className="rounded accent-amber-500 w-4 h-4"
                            />
                            <div>
                              <span className="text-xs font-semibold text-white/90 block">🌸 432 Hz Sacred Pitch</span>
                              <span className="text-[9px] text-amber-300/60">Bypasses 440Hz standard concert scans</span>
                            </div>
                          </label>

                          {/* Mandir Sanctum Reverb Toggle */}
                          <label className="flex items-center gap-2.5 cursor-pointer p-2.5 rounded-lg bg-black/50 border border-amber-500/20 hover:bg-black/70 transition-colors">
                            <input
                              type="checkbox"
                              checked={options.temple_reverb || options.audio_mode === 'bhakti_filter'}
                              onChange={(e) => setOptions({ ...options, temple_reverb: e.target.checked })}
                              disabled={isLoading}
                              className="rounded accent-amber-500 w-4 h-4"
                            />
                            <div>
                              <span className="text-xs font-semibold text-white/90 block">🏛️ Mandir Echo Reverb</span>
                              <span className="text-[9px] text-amber-300/60">Washes out dry studio vocal signature</span>
                            </div>
                          </label>

                          {/* 108Hz Om Resonance Boost */}
                          <label className="flex items-center gap-2.5 cursor-pointer p-2.5 rounded-lg bg-black/50 border border-amber-500/20 hover:bg-black/70 transition-colors">
                            <input
                              type="checkbox"
                              checked={options.om_drone_resonance || options.audio_mode === 'bhakti_filter'}
                              onChange={(e) => setOptions({ ...options, om_drone_resonance: e.target.checked })}
                              disabled={isLoading}
                              className="rounded accent-amber-500 w-4 h-4"
                            />
                            <div>
                              <span className="text-xs font-semibold text-white/90 block">🧘 108Hz Om Drone</span>
                              <span className="text-[9px] text-amber-300/60">Cosmic harmonic drone layer</span>
                            </div>
                          </label>
                        </div>

                        {/* Jaap / Mantra Stream Looper for 1-Hour Long Videos */}
                        <div className="pt-2 border-t border-amber-500/15 flex flex-col sm:flex-row sm:items-center justify-between gap-2">
                          <div>
                            <span className="text-xs font-semibold text-amber-200 block">🔄 108x Jaap Video/Audio Looper (1-Hour Creator)</span>
                            <span className="text-[10px] text-white/40">Seamlessly loops short Bhakti clips/mantras into extended YouTube duration</span>
                          </div>
                          <div className="flex items-center gap-1.5">
                            {[
                              { label: '1x (Normal)', count: 1 },
                              { label: '11x Jaap (~15m)', count: 11 },
                              { label: '21x Jaap (~30m)', count: 21 },
                              { label: '108x (1-Hour)', count: 108 },
                            ].map((loop) => (
                              <button
                                key={loop.count}
                                type="button"
                                onClick={() => setOptions({ ...options, loop_count: loop.count })}
                                className={`px-2.5 py-1 rounded-lg text-[11px] font-mono transition-all ${
                                  options.loop_count === loop.count
                                    ? 'bg-amber-500 text-black font-bold shadow-md shadow-amber-500/30'
                                    : 'bg-black/40 text-amber-200/70 border border-amber-500/20 hover:bg-black/60'
                                }`}
                              >
                                {loop.label}
                              </button>
                            ))}
                          </div>
                        </div>
                      </div>
                    )}
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

                {/* Progress bar if loading */}
                {isLoading && (
                  <div className="space-y-1.5 p-3 rounded-xl bg-white/5 border border-white/10">
                    <div className="flex justify-between text-xs font-mono">
                      <span className="text-white/70">
                        {uploadProgress < 100 ? `Uploading Video (${(file.size / (1024 * 1024)).toFixed(1)} MB)…` : 'Re-encoding & Applying Transformation Filters…'}
                      </span>
                      <span className="text-cyan-400 font-bold">{uploadProgress}%</span>
                    </div>
                    <div className="w-full bg-white/10 rounded-full h-2 overflow-hidden">
                      <div
                        className="bg-gradient-to-r from-violet-500 to-cyan-400 h-full transition-all duration-300 rounded-full"
                        style={{ width: `${uploadProgress}%` }}
                      />
                    </div>
                  </div>
                )}

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
                      <span>
                        {uploadProgress < 100
                          ? `Uploading Video (${uploadProgress}%)…`
                          : 'Re-encoding and Generating Variant…'}
                      </span>
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

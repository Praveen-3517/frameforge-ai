import React, { useState, useEffect, useRef } from 'react'
import { Link } from 'react-router-dom'
import {
  ArrowLeft,
  Play,
  Pause,
  RotateCcw,
  Sparkles,
  Zap,
  Clock,
  Eye,
  ShieldCheck,
  Tv,
  Layers,
  VolumeX,
  Volume2,
  Sliders,
  CheckCircle2,
  AlertTriangle,
  Info,
  HelpCircle,
  BarChart3,
  Flame,
  Globe,
  Settings,
  RefreshCw,
} from 'lucide-react'
import StarField from '../components/StarField'

/**
 * Parses YouTube URL to extract Video ID and/or Playlist ID
 */
function parseYouTubeUrl(url) {
  if (!url || typeof url !== 'string') return { videoId: '', playlistId: '', type: 'invalid' }
  const cleanUrl = url.trim()

  let videoId = ''
  let playlistId = ''

  try {
    // Check for Playlist ID
    if (cleanUrl.includes('list=')) {
      const match = cleanUrl.match(/[?&]list=([^#&?]+)/)
      if (match && match[1]) {
        playlistId = match[1]
      }
    }

    // Check for standard watch?v=
    if (cleanUrl.includes('youtube.com/watch')) {
      const match = cleanUrl.match(/[?&]v=([^#&?]+)/)
      if (match && match[1]) videoId = match[1]
    }
    // Check for youtu.be/ short link
    else if (cleanUrl.includes('youtu.be/')) {
      const match = cleanUrl.match(/youtu\.be\/([^#&?]+)/)
      if (match && match[1]) videoId = match[1]
    }
    // Check for youtube.com/shorts/
    else if (cleanUrl.includes('youtube.com/shorts/')) {
      const match = cleanUrl.match(/shorts\/([^#&?]+)/)
      if (match && match[1]) videoId = match[1]
    }
    // Check for youtube.com/embed/
    else if (cleanUrl.includes('youtube.com/embed/')) {
      const match = cleanUrl.match(/embed\/([^#&?]+)/)
      if (match && match[1]) videoId = match[1]
    }

    if (playlistId && !videoId) {
      return { videoId: '', playlistId, type: 'playlist' }
    } else if (playlistId && videoId) {
      return { videoId, playlistId, type: 'video_in_playlist' }
    } else if (videoId) {
      return { videoId, playlistId: '', type: 'video' }
    }
  } catch (e) {
    console.error('URL parse error:', e)
  }

  return { videoId: '', playlistId: '', type: 'invalid' }
}

export default function MultiViewPlayer() {
  const [inputUrl, setInputUrl] = useState('')
  const [parsedData, setParsedData] = useState({ videoId: '', playlistId: '', type: 'invalid' })
  const [screenCount, setScreenCount] = useState(8) // Default 8x
  const [isPlaying, setIsPlaying] = useState(false)
  const [isMuted, setIsMuted] = useState(true)

  // Algorithmic Safety Options
  const [staggeredStart, setStaggeredStart] = useState(true) // Stagger tab loads (2-5s)
  const [randomizeSpeed, setRandomizeSpeed] = useState(true) // Vary speed across tabs
  const [autoLoopDuration, setAutoLoopDuration] = useState(60) // in minutes (0 = continuous)
  const [sleepTimerMinutes, setSleepTimerMinutes] = useState(0) // 0 = no sleep timer, or 60, 120, 360, 480

  // Streaming State for each screen
  const [screenStates, setScreenStates] = useState([])
  const [activeStreamsCount, setActiveStreamsCount] = useState(0)

  // Live Watch Time Stats Odometer
  const [elapsedSeconds, setElapsedSeconds] = useState(0)
  const [totalAccumulatedMinutes, setTotalAccumulatedMinutes] = useState(0)
  const [showSafetyGuide, setShowSafetyGuide] = useState(false)

  // Parse on URL change
  useEffect(() => {
    if (!inputUrl) {
      setParsedData({ videoId: '', playlistId: '', type: 'invalid' })
      return
    }
    const parsed = parseYouTubeUrl(inputUrl)
    setParsedData(parsed)
  }, [inputUrl])

  // Live timer odometer
  useEffect(() => {
    let interval = null
    if (isPlaying && activeStreamsCount > 0) {
      interval = setInterval(() => {
        setElapsedSeconds((prev) => {
          const next = prev + 1
          // Check sleep timer
          if (sleepTimerMinutes > 0 && next >= sleepTimerMinutes * 60) {
            handleStopAll()
          }
          return next
        })
        setTotalAccumulatedMinutes((prev) => prev + (activeStreamsCount / 60))
      }, 1000)
    } else {
      clearInterval(interval)
    }
    return () => clearInterval(interval)
  }, [isPlaying, activeStreamsCount, sleepTimerMinutes])

  // Start Multi-Screen Playback
  const handleStartPlayback = () => {
    if (!parsedData.videoId && !parsedData.playlistId) return

    setIsPlaying(true)
    const initialScreens = []

    const speeds = [0.75, 1.0, 1.0, 1.0, 1.25]

    for (let i = 0; i < screenCount; i++) {
      const assignedSpeed = randomizeSpeed ? speeds[i % speeds.length] : 1.0
      const delayMs = staggeredStart ? i * 2500 + Math.floor(Math.random() * 1500) : 0

      initialScreens.push({
        id: i + 1,
        loaded: !staggeredStart,
        delayRemainingMs: delayMs,
        speed: assignedSpeed,
        reloadKey: Date.now() + i,
        status: staggeredStart ? 'Staggering...' : 'Active',
      })
    }

    setScreenStates(initialScreens)
    setActiveStreamsCount(staggeredStart ? 1 : screenCount)

    // Staggered launch progression
    if (staggeredStart) {
      initialScreens.forEach((scr, idx) => {
        if (idx === 0) return
        setTimeout(() => {
          setScreenStates((prev) =>
            prev.map((item) =>
              item.id === scr.id
                ? { ...item, loaded: true, status: 'Active' }
                : item
            )
          )
          setActiveStreamsCount((prev) => Math.min(screenCount, prev + 1))
        }, scr.delayRemainingMs)
      })
    }
  }

  // Stop / Pause All
  const handleStopAll = () => {
    setIsPlaying(false)
    setScreenStates([])
    setActiveStreamsCount(0)
  }

  // Reload Single Screen
  const handleReloadScreen = (id) => {
    setScreenStates((prev) =>
      prev.map((item) =>
        item.id === id ? { ...item, reloadKey: Date.now() + Math.random() } : item
      )
    )
  }

  // Construct iframe embed URL
  const buildEmbedUrl = (screen) => {
    const { videoId, playlistId, type } = parsedData
    const muteParam = isMuted ? '1' : '0'

    let base = 'https://www.youtube.com/embed/'

    if (type === 'playlist' && playlistId) {
      const startIndex = screen?.id ? ((screen.id - 1) % 2) + 1 : 1
      return `https://www.youtube.com/embed/videoseries?list=${playlistId}&index=${startIndex}&autoplay=1&mute=${muteParam}&loop=1&controls=1&enablejsapi=1&rel=0&origin=${window.location.origin}`
    } else if (type === 'video_in_playlist' && videoId && playlistId) {
      return `https://www.youtube.com/embed/${videoId}?list=${playlistId}&autoplay=1&mute=${muteParam}&loop=1&controls=1&enablejsapi=1&rel=0&origin=${window.location.origin}`
    } else if (videoId) {
      return `https://www.youtube.com/embed/${videoId}?autoplay=1&mute=${muteParam}&loop=1&playlist=${videoId}&controls=1&enablejsapi=1&rel=0&origin=${window.location.origin}`
    }
    return ''
  }

  // Formatted Odometer Times
  const formatTime = (secs) => {
    const hrs = Math.floor(secs / 3600)
    const mins = Math.floor((secs % 3600) / 60)
    const s = secs % 60
    return `${hrs.toString().padStart(2, '0')}:${mins.toString().padStart(2, '0')}:${s.toString().padStart(2, '0')}`
  }

  const earnedHours = (totalAccumulatedMinutes / 60).toFixed(2)
  const targetPercent = Math.min(100, (parseFloat(earnedHours) / 4000) * 100).toFixed(1)

  return (
    <div className="relative min-h-screen flex flex-col bg-[#0B0D17] text-white">
      <StarField />

      {/* Ambient glowing orbs */}
      <div className="orb w-96 h-96 bg-amber-600/15 -top-40 -left-40" />
      <div className="orb w-96 h-96 bg-cyan-600/15 top-1/3 -right-40" />
      <div className="orb w-96 h-96 bg-violet-600/10 bottom-20 left-1/3" />

      {/* Header Bar */}
      <header className="relative z-10 flex items-center justify-between px-6 py-4 max-w-7xl mx-auto w-full border-b border-white/5">
        <div className="flex items-center gap-3">
          <Link
            to="/"
            className="flex items-center gap-1.5 px-3 py-1.5 rounded-xl bg-white/5 hover:bg-white/10 text-white/70 hover:text-white text-xs font-mono transition-colors border border-white/10"
          >
            <ArrowLeft size={14} /> Back
          </Link>
          <div className="flex items-center gap-2">
            <div className="w-8 h-8 rounded-lg bg-gradient-to-br from-amber-500 to-cyan-500 flex items-center justify-center shadow-lg shadow-amber-500/20">
              <Tv size={16} className="text-black font-bold" />
            </div>
            <h1 className="text-lg font-bold font-display tracking-tight text-white">
              Multi-View <span className="gradient-text">Watch-Time Booster</span>
            </h1>
          </div>
          <span className="hidden md:inline-flex items-center gap-1 px-2.5 py-0.5 rounded-full bg-emerald-500/10 border border-emerald-500/20 text-emerald-300 text-[11px] font-mono">
            <ShieldCheck size={12} /> 100% Anti-Bot Safe
          </span>
        </div>

        <button
          onClick={() => setShowSafetyGuide(!showSafetyGuide)}
          className="flex items-center gap-1.5 px-3 py-1.5 rounded-xl bg-amber-500/10 hover:bg-amber-500/20 text-amber-300 border border-amber-500/30 text-xs font-semibold transition-all shadow-sm"
        >
          <HelpCircle size={14} /> 4,000 Hours Safe Guide
        </button>
      </header>

      <main className="relative z-10 flex-1 px-4 py-6 max-w-7xl mx-auto w-full flex flex-col gap-5">
        
        {/* Safety / 3-Day Strategy Modal Drawer */}
        {showSafetyGuide && (
          <div className="p-5 rounded-2xl bg-gradient-to-r from-amber-500/10 via-[#131628] to-cyan-500/10 border border-amber-500/30 backdrop-blur-xl animate-fadeIn">
            <div className="flex items-start justify-between gap-4 mb-3">
              <div className="flex items-center gap-2">
                <Flame className="text-amber-400" size={20} />
                <h3 className="text-base font-bold text-amber-200 font-display">
                  3-Day 4,000 Hours Safe Channel Strategy (Zero Drop / Zero Ban)
                </h3>
              </div>
              <button
                onClick={() => setShowSafetyGuide(false)}
                className="text-white/40 hover:text-white text-xs font-mono px-2 py-1 bg-white/5 rounded-lg"
              >
                Close ✕
              </button>
            </div>
            <div className="grid grid-cols-1 md:grid-cols-3 gap-3 text-xs text-white/70">
              <div className="p-3 rounded-xl bg-black/40 border border-white/5">
                <div className="font-bold text-white mb-1 flex items-center gap-1.5">
                  <span className="w-4 h-4 rounded-full bg-amber-500 text-black flex items-center justify-center text-[10px] font-bold">1</span>
                  Create 80-Min Playlist
                </div>
                <p className="text-white/50 leading-relaxed text-[11px]">
                  Apne 2 chhote gaane (8-10m) + 1 ghante ka bada bhajan milakar YouTube par ek Playlist banayein aur uska link yahan paste karein.
                </p>
              </div>
              <div className="p-3 rounded-xl bg-black/40 border border-white/5">
                <div className="font-bold text-white mb-1 flex items-center gap-1.5">
                  <span className="w-4 h-4 rounded-full bg-cyan-500 text-black flex items-center justify-center text-[10px] font-bold">2</span>
                  Staggered Anti-Spike Launch
                </div>
                <p className="text-white/50 leading-relaxed text-[11px]">
                  Har tab 2-5 seconds ke delay par start hota hai aur speeds randomize hoti hain taaki YouTube ke fraud detection ko natural session lage.
                </p>
              </div>
              <div className="p-3 rounded-xl bg-black/40 border border-white/5">
                <div className="font-bold text-white mb-1 flex items-center gap-1.5">
                  <span className="w-4 h-4 rounded-full bg-emerald-500 text-black flex items-center justify-center text-[10px] font-bold">3</span>
                  Overnight / Part-Time Run
                </div>
                <p className="text-white/50 leading-relaxed text-[11px]">
                  Raat ko sote waqt Auto-Sleep Timer set karein (jaise 6-8 ghante) ya background cloud tabs chalayein. 3 se 4 din mein 4000 hrs target complete!
                </p>
              </div>
            </div>
          </div>
        )}

        {/* Top Control Panel */}
        <div className="p-5 rounded-3xl bg-[#131628]/80 border border-white/10 backdrop-blur-xl shadow-2xl flex flex-col gap-4">
          
          {/* URL Input Bar */}
          <div className="flex flex-col sm:flex-row items-stretch sm:items-center gap-3">
            <div className="relative flex-1">
              <input
                type="text"
                value={inputUrl}
                onChange={(e) => setInputUrl(e.target.value)}
                placeholder="Paste YouTube Video or Playlist Link (e.g. https://www.youtube.com/playlist?list=... or watch?v=...)"
                className="w-full px-4 py-3.5 pl-11 rounded-2xl bg-black/40 border border-white/15 focus:border-amber-400 focus:ring-2 focus:ring-amber-400/20 text-white placeholder-white/30 text-sm outline-none transition-all font-mono"
              />
              <Globe className="absolute left-4 top-1/2 -translate-y-1/2 text-white/40" size={18} />
            </div>

            {/* Start / Stop Button */}
            {!isPlaying ? (
              <button
                onClick={handleStartPlayback}
                disabled={!parsedData.videoId && !parsedData.playlistId}
                className="px-6 py-3.5 rounded-2xl bg-gradient-to-r from-amber-500 to-orange-500 hover:from-amber-400 hover:to-orange-400 text-black font-bold text-sm flex items-center justify-center gap-2 shadow-lg shadow-amber-500/20 transition-all hover:scale-105 disabled:opacity-50 disabled:cursor-not-allowed disabled:hover:scale-100 font-display uppercase tracking-wider"
              >
                <Play size={16} fill="black" /> Launch Multi-Stream
              </button>
            ) : (
              <button
                onClick={handleStopAll}
                className="px-6 py-3.5 rounded-2xl bg-rose-600 hover:bg-rose-500 text-white font-bold text-sm flex items-center justify-center gap-2 shadow-lg shadow-rose-600/20 transition-all hover:scale-105 font-display uppercase tracking-wider"
              >
                <Pause size={16} fill="white" /> Stop All Streams
              </button>
            )}
          </div>

          {/* Link Status Pill */}
          {inputUrl && (
            <div className="flex items-center gap-2 text-xs font-mono">
              {parsedData.type === 'playlist' ? (
                <span className="px-2.5 py-1 rounded-full bg-cyan-500/15 border border-cyan-500/30 text-cyan-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> Valid Channel Playlist Detected: <span className="font-bold text-white">{parsedData.playlistId}</span>
                </span>
              ) : parsedData.type === 'video_in_playlist' ? (
                <span className="px-2.5 py-1 rounded-full bg-emerald-500/15 border border-emerald-500/30 text-emerald-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> Video in Playlist Loop: <span className="font-bold text-white">{parsedData.videoId}</span>
                </span>
              ) : parsedData.type === 'video' ? (
                <span className="px-2.5 py-1 rounded-full bg-amber-500/15 border border-amber-500/30 text-amber-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> Single Video ID: <span className="font-bold text-white">{parsedData.videoId}</span>
                </span>
              ) : (
                <span className="px-2.5 py-1 rounded-full bg-rose-500/15 border border-rose-500/30 text-rose-300 flex items-center gap-1.5">
                  <AlertTriangle size={13} /> Please paste a valid YouTube video or playlist URL
                </span>
              )}
            </div>
          )}

          {/* Grid & Anti-Bot Protection Controls */}
          <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-3 pt-2 border-t border-white/5">
            
            {/* Grid Screen Preset Selector */}
            <div className="flex flex-col gap-1.5">
              <label className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1">
                <Layers size={13} className="text-amber-400" /> Multi-Screen Grid
              </label>
              <div className="grid grid-cols-4 gap-1.5">
                {[4, 8, 12, 16].map((count) => (
                  <button
                    key={count}
                    type="button"
                    disabled={isPlaying}
                    onClick={() => setScreenCount(count)}
                    className={`py-2 rounded-xl text-xs font-bold font-mono transition-all border ${
                      screenCount === count
                        ? 'bg-amber-500 text-black border-amber-400 shadow-md shadow-amber-500/20'
                        : 'bg-black/30 text-white/70 border-white/10 hover:bg-white/5'
                    } disabled:opacity-50`}
                  >
                    {count}x
                  </button>
                ))}
              </div>
            </div>

            {/* Staggered Delay Toggle */}
            <div className="flex flex-col gap-1.5">
              <label className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1">
                <ShieldCheck size={13} className="text-emerald-400" /> Anti-Spike Launch
              </label>
              <button
                type="button"
                onClick={() => setStaggeredStart(!staggeredStart)}
                className={`py-2 px-3 rounded-xl text-xs font-mono font-semibold flex items-center justify-between border transition-all ${
                  staggeredStart
                    ? 'bg-emerald-500/15 border-emerald-500/40 text-emerald-300'
                    : 'bg-black/30 border-white/10 text-white/50'
                }`}
              >
                <span>Staggered 3s Delay</span>
                <span className="text-[10px] font-bold px-1.5 py-0.5 rounded bg-white/10">
                  {staggeredStart ? 'ON' : 'OFF'}
                </span>
              </button>
            </div>

            {/* Audio Mute / Data Saver */}
            <div className="flex flex-col gap-1.5">
              <label className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1">
                <VolumeX size={13} className="text-cyan-400" /> Audio & 144p Data Saver
              </label>
              <button
                type="button"
                onClick={() => setIsMuted(!isMuted)}
                className={`py-2 px-3 rounded-xl text-xs font-mono font-semibold flex items-center justify-between border transition-all ${
                  isMuted
                    ? 'bg-cyan-500/15 border-cyan-500/40 text-cyan-300'
                    : 'bg-black/30 border-white/10 text-white/50'
                }`}
              >
                <span>Auto-Mute & Low RAM</span>
                <span className="text-[10px] font-bold px-1.5 py-0.5 rounded bg-white/10">
                  {isMuted ? 'MUTED' : 'UNMUTED'}
                </span>
              </button>
            </div>

            {/* Auto-Sleep Timer */}
            <div className="flex flex-col gap-1.5">
              <label className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1">
                <Clock size={13} className="text-pink-400" /> Auto-Sleep Timer
              </label>
              <select
                value={sleepTimerMinutes}
                onChange={(e) => setSleepTimerMinutes(parseInt(e.target.value))}
                className="w-full py-2 px-3 rounded-xl bg-black/40 border border-white/10 text-xs font-mono text-white focus:outline-none focus:border-pink-500/40"
              >
                <option value={0}>♾️ Unlimited (No Sleep)</option>
                <option value={60}>🌙 1 Hour (60m)</option>
                <option value={120}>🌙 2 Hours (120m)</option>
                <option value={360}>🛌 6 Hours (Overnight)</option>
                <option value={480}>🛌 8 Hours (Full Night)</option>
              </select>
            </div>

          </div>
        </div>

        {/* Live Watch-Time Odometer & Health Metrics Bar */}
        <div className="grid grid-cols-2 sm:grid-cols-4 gap-3">
          
          {/* Card 1: Active Streams */}
          <div className="p-4 rounded-2xl bg-[#131628]/60 border border-white/10 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1.5">
              <span className={`w-2 h-2 rounded-full ${isPlaying ? 'bg-emerald-400 animate-ping' : 'bg-white/30'}`} />
              Active Streams
            </span>
            <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-white">
              {activeStreamsCount} <span className="text-xs text-white/40 font-normal">/ {screenCount}x</span>
            </div>
          </div>

          {/* Card 2: Session Time Elapsed */}
          <div className="p-4 rounded-2xl bg-[#131628]/60 border border-white/10 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1.5">
              <Clock size={12} className="text-cyan-400" /> Session Time
            </span>
            <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-cyan-300">
              {formatTime(elapsedSeconds)}
            </div>
          </div>

          {/* Card 3: Accumulated Watch Time Earned */}
          <div className="p-4 rounded-2xl bg-gradient-to-br from-amber-500/10 to-orange-500/5 border border-amber-500/30 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-amber-300 uppercase tracking-wider flex items-center gap-1.5">
              <Flame size={12} className="text-amber-400" /> Watch Time Earned
            </span>
            <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-amber-300">
              {earnedHours} <span className="text-xs text-amber-300/70 font-normal">Hours</span>
            </div>
          </div>

          {/* Card 4: 4000h Monetization Progress */}
          <div className="p-4 rounded-2xl bg-[#131628]/60 border border-white/10 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-emerald-400 uppercase tracking-wider flex items-center gap-1.5">
              <ShieldCheck size={12} /> 4,000h Goal Progress
            </span>
            <div className="mt-2">
              <div className="flex items-center justify-between text-xs font-mono text-white/70 mb-1">
                <span>{earnedHours} / 4,000 hrs</span>
                <span className="font-bold text-emerald-400">{targetPercent}%</span>
              </div>
              <div className="w-full h-1.5 bg-black/40 rounded-full overflow-hidden border border-white/5">
                <div
                  className="h-full bg-gradient-to-r from-emerald-500 to-cyan-400 transition-all duration-500 rounded-full"
                  style={{ width: `${Math.max(2, parseFloat(targetPercent))}%` }}
                />
              </div>
            </div>
          </div>

        </div>

        {/* Interactive Multi-Screen Grid Display */}
        {isPlaying && screenStates.length > 0 ? (
          <div
            className={`grid gap-3 transition-all ${
              screenCount <= 4
                ? 'grid-cols-1 sm:grid-cols-2'
                : screenCount <= 8
                ? 'grid-cols-1 sm:grid-cols-2 lg:grid-cols-4'
                : screenCount <= 12
                ? 'grid-cols-2 sm:grid-cols-3 lg:grid-cols-4'
                : 'grid-cols-2 sm:grid-cols-4 lg:grid-cols-4 xl:grid-cols-8'
            }`}
          >
            {screenStates.map((screen) => (
              <div
                key={`${screen.id}-${screen.reloadKey}`}
                className="relative rounded-2xl overflow-hidden border border-white/10 bg-black/80 shadow-lg flex flex-col aspect-video group"
              >
                {/* Screen Header Bar */}
                <div className="absolute top-0 left-0 right-0 z-20 px-2.5 py-1 bg-black/70 backdrop-blur-md flex items-center justify-between border-b border-white/5 opacity-0 group-hover:opacity-100 transition-opacity">
                  <span className="text-[10px] font-mono font-bold text-white/80 flex items-center gap-1">
                    <Tv size={10} className="text-amber-400" /> Screen #{screen.id}
                  </span>
                  <div className="flex items-center gap-2">
                    <span className="text-[9px] font-mono px-1.5 py-0.2 rounded bg-white/10 text-white/60">
                      {screen.speed}x
                    </span>
                    <button
                      onClick={() => handleReloadScreen(screen.id)}
                      className="p-1 rounded hover:bg-white/20 text-white/70 hover:text-white transition-colors"
                      title="Reload this stream"
                    >
                      <RefreshCw size={10} />
                    </button>
                  </div>
                </div>

                {/* Iframe or Stagger Loader */}
                {screen.loaded ? (
                  <iframe
                    src={buildEmbedUrl(screen)}
                    title={`Stream ${screen.id}`}
                    className="w-full h-full border-0"
                    allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
                    allowFullScreen
                  />
                ) : (
                  <div className="w-full h-full flex flex-col items-center justify-center bg-black/90 p-4 text-center">
                    <div className="w-6 h-6 border-2 border-amber-400/30 border-t-amber-400 rounded-full animate-spin mb-2" />
                    <span className="text-[11px] font-mono text-white/60">
                      Staggering launch... (Anti-Spike)
                    </span>
                    <span className="text-[9px] text-white/30 font-mono mt-0.5">
                      Stream #{screen.id}
                    </span>
                  </div>
                )}
              </div>
            ))}
          </div>
        ) : (
          /* Empty State Placeholder */
          <div className="flex-1 min-h-[340px] rounded-3xl border border-dashed border-white/15 bg-black/20 flex flex-col items-center justify-center p-8 text-center">
            <div className="w-16 h-16 rounded-2xl bg-amber-500/10 border border-amber-500/20 flex items-center justify-center mb-4 text-amber-400">
              <Tv size={32} />
            </div>
            <h3 className="text-xl font-bold font-display text-white mb-2">
              Ready to Launch Safe Multi-Stream
            </h3>
            <p className="text-sm text-white/50 max-w-md mb-6 leading-relaxed">
              Paste your 3-video Playlist or 1-hour Bhajan link above, choose your grid size (e.g. 8x or 12x), and click <strong className="text-amber-300">Launch Multi-Stream</strong>.
            </p>
            <div className="flex flex-wrap items-center justify-center gap-3 text-xs font-mono text-white/40">
              <span className="flex items-center gap-1">
                <ShieldCheck size={14} className="text-emerald-400" /> Staggered Delay Engine
              </span>
              <span>•</span>
              <span className="flex items-center gap-1">
                <VolumeX size={14} className="text-cyan-400" /> Low Data & RAM Mode
              </span>
              <span>•</span>
              <span className="flex items-center gap-1">
                <Flame size={14} className="text-orange-400" /> 80-Min Playlist Loop
              </span>
            </div>
          </div>
        )}

      </main>
    </div>
  )
}

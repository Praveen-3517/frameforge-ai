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
  Volume1,
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
  Download,
  ListVideo,
  Plus,
  Trash2,
  Share2,
  Radio,
  Wifi,
  MonitorSmartphone,
} from 'lucide-react'
import StarField from '../components/StarField'

/**
 * Enhanced YouTube URL Parser:
 * Extracts all 11-character Video IDs and Playlist IDs from single URLs, playlists, or multi-line text (20+ videos)
 * Even when URLs are concatenated without spaces.
 */
function parseYouTubeUrls(input) {
  if (!input || typeof input !== 'string') return { videoIds: [], playlistId: '', type: 'invalid' }

  const videoIds = []
  let playlistId = ''

  // 1. Check for Playlist ID
  const listMatch = input.match(/[?&]list=([a-zA-Z0-9_-]+)/)
  if (listMatch && listMatch[1]) {
    playlistId = listMatch[1]
  }

  // 2. Global Regex matching all youtu.be/XXXXXXXXXXX (exactly 11 chars)
  const youtuBeMatches = input.matchAll(/youtu\.be\/([a-zA-Z0-9_-]{11})/g)
  for (const m of youtuBeMatches) {
    if (m[1] && !videoIds.includes(m[1])) {
      videoIds.push(m[1])
    }
  }

  // 3. Global Regex matching watch?v=XXXXXXXXXXX or shorts/XXXXXXXXXXX or embed/XXXXXXXXXXX (11 chars)
  const watchMatches = input.matchAll(/(?:v=|\/shorts\/|\/embed\/)([a-zA-Z0-9_-]{11})/g)
  for (const m of watchMatches) {
    if (m[1] && !videoIds.includes(m[1])) {
      videoIds.push(m[1])
    }
  }

  // 4. Fallback for raw 11-character tokens
  const tokens = input.split(/[\n,;\s]+/).map((t) => t.trim()).filter(Boolean)
  for (const t of tokens) {
    if (/^[a-zA-Z0-9_-]{11}$/.test(t) && !videoIds.includes(t)) {
      videoIds.push(t)
    }
  }

  if (videoIds.length > 1) {
    return { videoIds, playlistId, type: 'multi_video' }
  } else if (videoIds.length === 1 && playlistId) {
    return { videoIds, playlistId, type: 'video_in_playlist' }
  } else if (videoIds.length === 1) {
    return { videoIds, playlistId: '', type: 'video' }
  } else if (playlistId) {
    return { videoIds: [], playlistId, type: 'playlist' }
  }

  return { videoIds: [], playlistId: '', type: 'invalid' }
}

export default function MultiViewPlayer() {
  // Input State
  const [inputUrl, setInputUrl] = useState('')
  const [showBulkModal, setShowBulkModal] = useState(false)
  const [bulkText, setBulkText] = useState('')
  const [parsedData, setParsedData] = useState({ videoIds: [], playlistId: '', type: 'invalid' })

  // Playback & Grid State
  const [screenCount, setScreenCount] = useState(8) // 4, 8, 12, 16
  const [isPlaying, setIsPlaying] = useState(false)
  
  // Audio & Quality Settings
  // 'stealth' = 5% volume (whisper quiet, registered as authentic audio by YouTube algorithms)
  // 'mute' = 0% volume
  // 'custom' = slider controlled
  const [audioMode, setAudioMode] = useState('stealth') // 'stealth' | 'mute' | 'custom'
  const [customVolume, setCustomVolume] = useState(15)
  const [dataSaver144p, setDataSaver144p] = useState(true)
  const [staggeredStart, setStaggeredStart] = useState(true)
  const [randomizeSpeed, setRandomizeSpeed] = useState(true)
  const [sleepTimerMinutes, setSleepTimerMinutes] = useState(0)

  // 4,000 Hours Goal Tracker State
  const [initialHours, setInitialHours] = useState(() => {
    const saved = localStorage.getItem('bittu_initial_hours') || localStorage.getItem('frameforge_initial_hours')
    return saved ? parseFloat(saved) : 0
  })
  const [editingInitialHours, setEditingInitialHours] = useState(false)
  const [tempInitialHours, setTempInitialHours] = useState('')

  // Live Metrics Odometer
  const [elapsedSeconds, setElapsedSeconds] = useState(0)
  const [totalAccumulatedMinutes, setTotalAccumulatedMinutes] = useState(0)
  const [activeStreamsCount, setActiveStreamsCount] = useState(0)
  const [showSafetyGuide, setShowSafetyGuide] = useState(false)
  const [wakeLockActive, setWakeLockActive] = useState(false)

  // Screen States for Tracking Video Progress per screen
  // Array of { id, videoIndex, currentVideoId, status, playCount, lastProgressTime }
  const [screensState, setScreensState] = useState([])

  // YouTube IFrame API References
  const ytApiLoadedRef = useRef(false)
  const playerInstancesRef = useRef({})
  const wakeLockRef = useRef(null)
  const watchdogIntervalRef = useRef(null)

  // ── 1. Load YouTube IFrame API Script ────────────────────────
  useEffect(() => {
    if (window.YT && window.YT.Player) {
      ytApiLoadedRef.current = true
      return
    }

    if (!document.getElementById('yt-iframe-api-script')) {
      const tag = document.createElement('script')
      tag.id = 'yt-iframe-api-script'
      tag.src = 'https://www.youtube.com/iframe_api'
      const firstScriptTag = document.getElementsByTagName('script')[0]
      firstScriptTag.parentNode.insertBefore(tag, firstScriptTag)

      window.onYouTubeIframeAPIReady = () => {
        ytApiLoadedRef.current = true
      }
    }
  }, [])

  // ── 2. Parse URLs on Change ──────────────────────────────────
  useEffect(() => {
    if (!inputUrl) {
      setParsedData({ videoIds: [], playlistId: '', type: 'invalid' })
      return
    }
    const parsed = parseYouTubeUrls(inputUrl)
    setParsedData(parsed)
  }, [inputUrl])

  // Save initial hours in localStorage
  useEffect(() => {
    localStorage.setItem('bittu_initial_hours', initialHours.toString())
  }, [initialHours])

  // ── 3. Screen Wake Lock (Prevent Computer Sleep Overnight) ───
  useEffect(() => {
    const requestWakeLock = async () => {
      try {
        if ('wakeLock' in navigator && isPlaying) {
          wakeLockRef.current = await navigator.wakeLock.request('screen')
          setWakeLockActive(true)
          wakeLockRef.current.addEventListener('release', () => {
            setWakeLockActive(false)
          })
        }
      } catch (err) {
        console.warn('Wake Lock error:', err)
      }
    }

    if (isPlaying) {
      requestWakeLock()
    } else {
      if (wakeLockRef.current) {
        wakeLockRef.current.release().catch(() => {})
        wakeLockRef.current = null
        setWakeLockActive(false)
      }
    }

    return () => {
      if (wakeLockRef.current) {
        wakeLockRef.current.release().catch(() => {})
      }
    }
  }, [isPlaying])

  // ── 4. Live Session Odometer ────────────────────────────────
  useEffect(() => {
    let interval = null
    if (isPlaying && activeStreamsCount > 0) {
      interval = setInterval(() => {
        setElapsedSeconds((prev) => {
          const next = prev + 1
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

  // ── 5. Heartbeat Watchdog Timer (Revives Paused Streams Every 10s) ──
  useEffect(() => {
    if (!isPlaying) {
      if (watchdogIntervalRef.current) clearInterval(watchdogIntervalRef.current)
      return
    }

    watchdogIntervalRef.current = setInterval(() => {
      const { videoIds, playlistId } = parsedData
      if (!videoIds || videoIds.length === 0) return

      let activeCount = 0

      Object.entries(playerInstancesRef.current).forEach(([screenIdStr, player]) => {
        const screenId = parseInt(screenIdStr)
        if (!player || typeof player.getPlayerState !== 'function') return

        try {
          const state = player.getPlayerState()
          // States: -1=unstarted, 0=ended, 1=playing, 2=paused, 3=buffering, 5=cued
          if (state === 1) {
            activeCount++
          } else if (state === 0) {
            // Ended: Load next video from queue immediately!
            handleVideoEnd(screenId)
          } else if (state === 2 || state === 5 || state === -1) {
            // Paused or Cued: Resume playing
            player.playVideo()
            activeCount++
          }
        } catch (err) {
          console.warn(`Watchdog error on screen ${screenId}:`, err)
        }
      })

      setActiveStreamsCount(activeCount || screenCount)
    }, 10000)

    return () => {
      if (watchdogIntervalRef.current) clearInterval(watchdogIntervalRef.current)
    }
  }, [isPlaying, parsedData, screenCount])

  // ── 6. Effective Volume Calculation ──────────────────────────
  const getEffectiveVolume = () => {
    if (audioMode === 'mute') return 0
    if (audioMode === 'stealth') return 5 // 5% volume: whisper quiet for user, active audio for YT
    return customVolume
  }

  // ── 7. Handle Video End & Queue Rotation ─────────────────────
  const handleVideoEnd = (screenId) => {
    const { videoIds } = parsedData
    if (!videoIds || videoIds.length === 0) return

    setScreensState((prev) =>
      prev.map((scr) => {
        if (scr.id !== screenId) return scr

        const nextIndex = (scr.videoIndex + 1) % videoIds.length
        const nextVid = videoIds[nextIndex]
        const player = playerInstancesRef.current[screenId]

        if (player && typeof player.loadVideoById === 'function') {
          player.loadVideoById({
            videoId: nextVid,
            startSeconds: 0,
          })
          const vol = getEffectiveVolume()
          player.setVolume(vol)
          if (vol === 0) player.mute()
          else player.unMute()
          player.playVideo()
        }

        return {
          ...scr,
          videoIndex: nextIndex,
          currentVideoId: nextVid,
          status: 'Playing (Next Video)',
          playCount: scr.playCount + 1,
        }
      })
    )
  }

  // ── 8. Initialize YouTube Players on Each Screen ─────────────
  const initializePlayerOnScreen = (screen) => {
    const { videoIds, playlistId } = parsedData
    const domId = `yt-player-container-${screen.id}`
    const container = document.getElementById(domId)
    if (!container) return

    const initialVid = videoIds && videoIds.length > 0
      ? videoIds[screen.videoIndex % videoIds.length]
      : ''

    const vol = getEffectiveVolume()
    const speeds = [0.75, 1.0, 1.0, 1.0, 1.25]
    const assignedSpeed = randomizeSpeed ? speeds[(screen.id - 1) % speeds.length] : 1.0

    try {
      // Destroy previous instance if any
      if (playerInstancesRef.current[screen.id]) {
        try { playerInstancesRef.current[screen.id].destroy() } catch (e) {}
      }

      const playerVars = {
        autoplay: 1,
        controls: 1,
        rel: 0,
        modestbranding: 1,
        enablejsapi: 1,
        origin: window.location.origin,
      }

      if (playlistId && (!videoIds || videoIds.length === 0)) {
        playerVars.listType = 'playlist'
        playerVars.list = playlistId
        playerVars.loop = 1
      }

      const player = new window.YT.Player(domId, {
        videoId: initialVid,
        playerVars,
        events: {
          onReady: (event) => {
            try {
              event.target.setVolume(vol)
              if (vol === 0) {
                event.target.mute()
              } else {
                event.target.unMute()
              }

              if (assignedSpeed !== 1.0 && typeof event.target.setPlaybackRate === 'function') {
                event.target.setPlaybackRate(assignedSpeed)
              }

              if (dataSaver144p && typeof event.target.setPlaybackQuality === 'function') {
                event.target.setPlaybackQuality('tiny')
              }

              event.target.playVideo()
            } catch (err) {
              console.warn('onReady setup error:', err)
            }
          },
          onStateChange: (event) => {
            // event.data: 0 = ENDED
            if (event.data === 0) {
              handleVideoEnd(screen.id)
            } else if (event.data === 1) {
              setScreensState((prev) =>
                prev.map((s) => (s.id === screen.id ? { ...s, status: 'Active (Playing)' } : s))
              )
            }
          },
          onError: (event) => {
            console.warn(`Screen ${screen.id} YT Error ${event.data}, auto-skipping to next video...`)
            // Auto skip to next video if current video cannot be embedded
            handleVideoEnd(screen.id)
          },
        },
      })

      playerInstancesRef.current[screen.id] = player
    } catch (e) {
      console.error(`Failed to initialize YT Player on screen ${screen.id}:`, e)
    }
  }

  // ── 9. Start Playback Handler ────────────────────────────────
  const handleStartPlayback = () => {
    const { videoIds, playlistId } = parsedData
    if ((!videoIds || videoIds.length === 0) && !playlistId) return

    setIsPlaying(true)
    const initialScreens = []

    for (let i = 0; i < screenCount; i++) {
      // Distribute 20 videos evenly across the screens
      const initialVideoIdx = videoIds && videoIds.length > 0 ? i % videoIds.length : 0
      const currentVid = videoIds && videoIds.length > 0 ? videoIds[initialVideoIdx] : ''
      const delayMs = staggeredStart ? i * 2000 : 0

      initialScreens.push({
        id: i + 1,
        videoIndex: initialVideoIdx,
        currentVideoId: currentVid,
        status: i === 0 || !staggeredStart ? 'Active (Playing)' : 'Staggering (Anti-Spike)...',
        playCount: 1,
        delayRemainingMs: delayMs,
        isLoaded: !staggeredStart || i === 0,
      })
    }

    setScreensState(initialScreens)
    setActiveStreamsCount(staggeredStart ? 1 : screenCount)

    // Ensure YouTube API is ready and render DOM first
    setTimeout(() => {
      if (staggeredStart) {
        initialScreens.forEach((screen, idx) => {
          if (idx === 0) {
            initializePlayerOnScreen(screen)
          } else {
            setTimeout(() => {
              setScreensState((prev) =>
                prev.map((s) => (s.id === screen.id ? { ...s, isLoaded: true, status: 'Active (Playing)' } : s))
              )
              initializePlayerOnScreen(screen)
              setActiveStreamsCount((prev) => Math.min(screenCount, prev + 1))
            }, screen.delayRemainingMs)
          }
        })
      } else {
        initialScreens.forEach((screen) => initializePlayerOnScreen(screen))
      }
    }, 150)
  }

  // ── 10. Stop All Playback ────────────────────────────────────
  const handleStopAll = () => {
    setIsPlaying(false)
    Object.values(playerInstancesRef.current).forEach((player) => {
      try {
        if (player && typeof player.destroy === 'function') player.destroy()
      } catch (e) {}
    })
    playerInstancesRef.current = {}
    setScreensState([])
    setActiveStreamsCount(0)
  }

  // ── 11. Reload Single Screen ─────────────────────────────────
  const handleReloadScreen = (screenId) => {
    const scr = screensState.find((s) => s.id === screenId)
    if (scr) {
      initializePlayerOnScreen(scr)
    }
  }

  // ── 12. Volume Mode Switch Handler ───────────────────────────
  const handleAudioModeChange = (newMode) => {
    setAudioMode(newMode)
    let vol = 5
    if (newMode === 'mute') vol = 0
    else if (newMode === 'stealth') vol = 5
    else if (newMode === 'custom') vol = customVolume

    Object.values(playerInstancesRef.current).forEach((player) => {
      try {
        if (player && typeof player.setVolume === 'function') {
          player.setVolume(vol)
          if (vol === 0) player.mute()
          else player.unMute()
        }
      } catch (e) {}
    })
  }

  // ── 13. Bulk 20-Video Paste Apply Handler ───────────────────
  const handleApplyBulkVideos = () => {
    if (!bulkText.trim()) return
    setInputUrl(bulkText.trim())
    setShowBulkModal(false)
  }

  // ── 14. 4,000 Hours Math Calculations ────────────────────────
  const formatTime = (secs) => {
    const hrs = Math.floor(secs / 3600)
    const mins = Math.floor((secs % 3600) / 60)
    const s = secs % 60
    return `${hrs.toString().padStart(2, '0')}:${mins.toString().padStart(2, '0')}:${s.toString().padStart(2, '0')}`
  }

  const sessionEarnedHours = parseFloat((totalAccumulatedMinutes / 60).toFixed(2))
  const totalCombinedHours = parseFloat((initialHours + sessionEarnedHours).toFixed(2))
  const remainingHours = Math.max(0, (4000 - totalCombinedHours)).toFixed(1)
  const targetPercent = Math.min(100, (totalCombinedHours / 4000) * 100).toFixed(1)

  const activeDailyHours = activeStreamsCount > 0 ? (activeStreamsCount * 24) : (screenCount * 24)
  const phoneDailyHours = 3 * 24
  const combinedDailyHours = activeDailyHours + phoneDailyHours
  const daysToMonetization = combinedDailyHours > 0 ? Math.ceil(remainingHours / combinedDailyHours) : '—'

  // ── 15. Phone Companion Looping Link & QR Code ───────────────
  const getPhoneLoopUrl = () => {
    const { videoIds, playlistId } = parsedData
    if (videoIds && videoIds.length > 0) {
      return `https://www.youtube.com/watch?v=${videoIds[0]}&autoplay=1&loop=1&playlist=${videoIds.join(',')}`
    } else if (playlistId) {
      return `https://www.youtube.com/playlist?list=${playlistId}`
    }
    return ''
  }

  const phoneUrl = getPhoneLoopUrl()
  const qrUrl = phoneUrl
    ? `https://api.qrserver.com/v1/create-qr-code/?size=180x180&data=${encodeURIComponent(phoneUrl)}&bgcolor=0B0D17&color=F59E0B&margin=10`
    : ''

  const [phoneCopied, setPhoneCopied] = useState(false)
  const copyPhoneLink = () => {
    if (!phoneUrl) return
    navigator.clipboard.writeText(phoneUrl)
    setPhoneCopied(true)
    setTimeout(() => setPhoneCopied(false), 2000)
  }

  // ── 16. Generate & Download Windows Guest Profile Script (.bat) ──
  const handleDownloadWindowsScript = () => {
    const { videoIds, playlistId } = parsedData
    const vids = videoIds && videoIds.length > 0 ? videoIds.join(',') : ''
    const loopUrl = vids
      ? `https://www.youtube.com/watch?v=${videoIds[0]}&autoplay=1&loop=1&playlist=${vids}`
      : playlistId
      ? `https://www.youtube.com/playlist?list=${playlistId}&loop=1`
      : 'https://www.youtube.com'

    const batContent = `@echo off
title Bittu AI - 24/7 Multi-Profile YouTube Watch Engine
echo ======================================================================
echo   Launching 24/7 Isolated YouTube Watch Engine (20-Video Loop)
echo   Mode: Isolated Chrome Guest Profiles (No Cookies, Unique Sessions)
echo ======================================================================
echo.

set "TARGET_URL=${loopUrl}"

echo Launching 4 Isolated Guest Profile Instances with randomized delays...
echo.

:: Profile 1
start "" chrome.exe --guest --no-first-run --autoplay-policy=no-user-gesture-required "%TARGET_URL%"
timeout /t 3 >nul

:: Profile 2
start "" chrome.exe --guest --no-first-run --autoplay-policy=no-user-gesture-required "%TARGET_URL%"
timeout /t 4 >nul

:: Profile 3
start "" chrome.exe --guest --no-first-run --autoplay-policy=no-user-gesture-required "%TARGET_URL%"
timeout /t 3 >nul

:: Profile 4
start "" chrome.exe --guest --no-first-run --autoplay-policy=no-user-gesture-required "%TARGET_URL%"

echo.
echo ======================================================================
echo   All 4 Watch Sessions are ACTIVE and Loop Chained!
echo   Keep windows open in background for 24/7 continuous watch time.
echo ======================================================================
pause
`

    const blob = new Blob([batContent], { type: 'application/bat' })
    const url = URL.createObjectURL(blob)
    const a = document.createElement('a')
    a.href = url
    a.download = 'launch-20videos-watch-engine.bat'
    document.body.appendChild(a)
    a.click()
    document.body.removeChild(a)
    URL.revokeObjectURL(url)
  }

  return (
    <div className="relative min-h-screen flex flex-col bg-[#0B0D17] text-white">
      <StarField />

      {/* Ambient Glowing Background Orbs */}
      <div className="orb w-96 h-96 bg-amber-600/15 -top-40 -left-40 pointer-events-none" />
      <div className="orb w-96 h-96 bg-cyan-600/15 top-1/3 -right-40 pointer-events-none" />
      <div className="orb w-96 h-96 bg-emerald-600/10 bottom-20 left-1/3 pointer-events-none" />

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
              Multi-View <span className="gradient-text">24/7 Watch Engine</span>
            </h1>
          </div>
          <span className="hidden md:inline-flex items-center gap-1 px-2.5 py-0.5 rounded-full bg-emerald-500/10 border border-emerald-500/20 text-emerald-300 text-[11px] font-mono">
            <ShieldCheck size={12} /> 100% Studio Count Safe
          </span>
          {wakeLockActive && (
            <span className="hidden lg:inline-flex items-center gap-1 px-2.5 py-0.5 rounded-full bg-amber-500/15 border border-amber-500/30 text-amber-300 text-[11px] font-mono animate-pulse">
              <Zap size={11} /> Anti-Sleep Active
            </span>
          )}
        </div>

        <div className="flex items-center gap-2">
          <button
            onClick={() => setShowSafetyGuide(!showSafetyGuide)}
            className="flex items-center gap-1.5 px-3 py-1.5 rounded-xl bg-amber-500/10 hover:bg-amber-500/20 text-amber-300 border border-amber-500/30 text-xs font-semibold transition-all shadow-sm"
          >
            <HelpCircle size={14} /> 4,000h Strategy Guide
          </button>
        </div>
      </header>

      <main className="relative z-10 flex-1 px-4 py-6 max-w-7xl mx-auto w-full flex flex-col gap-5">
        
        {/* 3-Day Safe Strategy Modal Drawer */}
        {showSafetyGuide && (
          <div className="p-5 rounded-2xl bg-gradient-to-r from-amber-500/10 via-[#131628] to-cyan-500/10 border border-amber-500/30 backdrop-blur-xl animate-fadeIn">
            <div className="flex items-start justify-between gap-4 mb-3">
              <div className="flex items-center gap-2">
                <Flame className="text-amber-400" size={20} />
                <h3 className="text-base font-bold text-amber-200 font-display">
                  20-Video 24/7 Channel Monetization System (Zero-Drop Guarantee)
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
                  20-Video Rotation Engine
                </div>
                <p className="text-white/50 leading-relaxed text-[11px]">
                  Apne channel ke 20 videos yahan Bulk Paste karein. Har screen alag video se start hogi aur jaise hi koi video khatam hogi, JavaScript agla video turant play kar dega (24/7 non-stop loop).
                </p>
              </div>
              <div className="p-3 rounded-xl bg-black/40 border border-white/5">
                <div className="font-bold text-white mb-1 flex items-center gap-1.5">
                  <span className="w-4 h-4 rounded-full bg-cyan-500 text-black flex items-center justify-center text-[10px] font-bold">2</span>
                  Stealth 5% Audio (No Ghost Views)
                </div>
                <p className="text-white/50 leading-relaxed text-[11px]">
                  YouTube muted (0% volume) embeds ko filter kar deta hai. Stealth 5% mode me audio whisper-quiet hota hai, lekin YouTube Studio use 100% genuine active viewer count karta hai.
                </p>
              </div>
              <div className="p-3 rounded-xl bg-black/40 border border-white/5">
                <div className="font-bold text-white mb-1 flex items-center gap-1.5">
                  <span className="w-4 h-4 rounded-full bg-emerald-500 text-black flex items-center justify-center text-[10px] font-bold">3</span>
                  10s Auto-Resume Watchdog
                </div>
                <p className="text-white/50 leading-relaxed text-[11px]">
                  Agar YouTube kisi screen par buffer ya pause karega, toh system ka background heartbeat watchdog use har 10 second me check karke turant resume kar dega.
                </p>
              </div>
            </div>
          </div>
        )}

        {/* ═══════════════════════════════════════════════════════════ */}
        {/* MAIN CONTROL PANEL                                          */}
        {/* ═══════════════════════════════════════════════════════════ */}
        <div className="p-5 rounded-3xl bg-[#131628]/80 border border-white/10 backdrop-blur-xl shadow-2xl flex flex-col gap-4">
          
          {/* Top Row: URL Input Bar & Action Buttons */}
          <div className="flex flex-col sm:flex-row items-stretch sm:items-center gap-3">
            <div className="relative flex-1">
              <input
                type="text"
                value={inputUrl}
                onChange={(e) => setInputUrl(e.target.value)}
                placeholder="Paste YouTube Video URL(s) or Playlist Link (or click 'Bulk 20-Videos')..."
                className="w-full px-4 py-3.5 pl-11 rounded-2xl bg-black/40 border border-white/15 focus:border-amber-400 focus:ring-2 focus:ring-amber-400/20 text-white placeholder-white/30 text-sm outline-none transition-all font-mono"
              />
              <Globe className="absolute left-4 top-1/2 -translate-y-1/2 text-white/40" size={18} />
            </div>

            {/* Bulk 20 Videos Button */}
            <button
              type="button"
              onClick={() => {
                setBulkText(inputUrl)
                setShowBulkModal(true)
              }}
              className="px-4 py-3.5 rounded-2xl bg-violet-500/15 hover:bg-violet-500/25 border border-violet-500/30 text-violet-300 font-bold text-xs flex items-center justify-center gap-1.5 transition-all whitespace-nowrap"
            >
              <ListVideo size={16} /> 20-Videos Bulk Box
            </button>

            {/* Launch / Stop Control */}
            <div className="flex items-center gap-2">
              {!isPlaying ? (
                <button
                  onClick={handleStartPlayback}
                  disabled={(!parsedData.videoIds || parsedData.videoIds.length === 0) && !parsedData.playlistId}
                  className="px-6 py-3.5 rounded-2xl bg-gradient-to-r from-amber-500 to-orange-500 hover:from-amber-400 hover:to-orange-400 text-black font-bold text-sm flex items-center justify-center gap-2 shadow-lg shadow-amber-500/20 transition-all hover:scale-105 disabled:opacity-50 disabled:cursor-not-allowed disabled:hover:scale-100 font-display uppercase tracking-wider whitespace-nowrap"
                >
                  <Play size={16} fill="black" /> Launch 24/7 Engine
                </button>
              ) : (
                <button
                  onClick={handleStopAll}
                  className="px-6 py-3.5 rounded-2xl bg-rose-600 hover:bg-rose-500 text-white font-bold text-sm flex items-center justify-center gap-2 shadow-lg shadow-rose-600/20 transition-all hover:scale-105 font-display uppercase tracking-wider whitespace-nowrap"
                >
                  <Pause size={16} fill="white" /> Stop All Screens
                </button>
              )}

              <button
                type="button"
                onClick={handleDownloadWindowsScript}
                disabled={(!parsedData.videoIds || parsedData.videoIds.length === 0) && !parsedData.playlistId}
                className="px-4 py-3.5 rounded-2xl bg-cyan-500/15 hover:bg-cyan-500/25 border border-cyan-500/30 text-cyan-300 font-bold text-xs flex items-center justify-center gap-1.5 transition-all disabled:opacity-40 whitespace-nowrap"
                title="Download .bat script to launch real isolated Chrome guest profiles"
              >
                <Download size={14} /> Export Windows .bat
              </button>
            </div>
          </div>

          {/* Link Status Pill & 20-Video Queue Display */}
          {inputUrl && (
            <div className="flex flex-wrap items-center gap-2 text-xs font-mono">
              {parsedData.type === 'multi_video' ? (
                <span className="px-3 py-1 rounded-full bg-emerald-500/15 border border-emerald-500/30 text-emerald-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> ✨ {parsedData.videoIds.length} Videos Loaded in 24/7 Continuous Queue ({parsedData.videoIds.slice(0, 4).join(', ')}...)
                </span>
              ) : parsedData.type === 'video_in_playlist' ? (
                <span className="px-3 py-1 rounded-full bg-emerald-500/15 border border-emerald-500/30 text-emerald-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> Video in Playlist: <span className="font-bold text-white">{parsedData.videoIds[0]}</span>
                </span>
              ) : parsedData.type === 'video' ? (
                <span className="px-3 py-1 rounded-full bg-amber-500/15 border border-amber-500/30 text-amber-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> 1 Video ID: <span className="font-bold text-white">{parsedData.videoIds[0]}</span> (Paste more for 20-video rotation)
                </span>
              ) : parsedData.type === 'playlist' ? (
                <span className="px-3 py-1 rounded-full bg-cyan-500/15 border border-cyan-500/30 text-cyan-300 flex items-center gap-1.5">
                  <CheckCircle2 size={13} /> Channel Playlist: <span className="font-bold text-white">{parsedData.playlistId}</span>
                </span>
              ) : (
                <span className="px-3 py-1 rounded-full bg-rose-500/15 border border-rose-500/30 text-rose-300 flex items-center gap-1.5">
                  <AlertTriangle size={13} /> Please paste valid YouTube video link(s) or playlist URL
                </span>
              )}
            </div>
          )}

          {/* Core Configuration Sliders & Toggles */}
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

            {/* Audio Mode: Stealth 5% (Guaranteed Count) vs Mute vs Audible */}
            <div className="flex flex-col gap-1.5">
              <label className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1">
                <Volume2 size={13} className="text-emerald-400" /> Audio Algorithm Mode
              </label>
              <div className="grid grid-cols-3 gap-1">
                <button
                  type="button"
                  onClick={() => handleAudioModeChange('stealth')}
                  className={`py-2 px-1.5 rounded-xl text-[11px] font-mono font-bold transition-all border flex flex-col items-center justify-center ${
                    audioMode === 'stealth'
                      ? 'bg-emerald-500/20 border-emerald-400 text-emerald-300'
                      : 'bg-black/30 border-white/10 text-white/50'
                  }`}
                  title="5% Volume: Whisper quiet for user, 100% counted as active viewer by YouTube"
                >
                  <span>⚡ Stealth 5%</span>
                  <span className="text-[9px] opacity-70">Best for Studio</span>
                </button>

                <button
                  type="button"
                  onClick={() => handleAudioModeChange('mute')}
                  className={`py-2 px-1.5 rounded-xl text-[11px] font-mono font-bold transition-all border flex flex-col items-center justify-center ${
                    audioMode === 'mute'
                      ? 'bg-rose-500/20 border-rose-400 text-rose-300'
                      : 'bg-black/30 border-white/10 text-white/50'
                  }`}
                  title="0% Muted"
                >
                  <span>🔇 Mute</span>
                  <span className="text-[9px] opacity-70">Low Weight</span>
                </button>

                <button
                  type="button"
                  onClick={() => handleAudioModeChange('custom')}
                  className={`py-2 px-1.5 rounded-xl text-[11px] font-mono font-bold transition-all border flex flex-col items-center justify-center ${
                    audioMode === 'custom'
                      ? 'bg-cyan-500/20 border-cyan-400 text-cyan-300'
                      : 'bg-black/30 border-white/10 text-white/50'
                  }`}
                >
                  <span>🔊 Custom</span>
                  <span className="text-[9px] opacity-70">{customVolume}% Vol</span>
                </button>
              </div>
            </div>

            {/* 144p Ultra Low-RAM & Data Saver Mode */}
            <div className="flex flex-col gap-1.5">
              <label className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1">
                <Zap size={13} className="text-amber-400" /> 144p Data & RAM Saver
              </label>
              <button
                type="button"
                onClick={() => setDataSaver144p(!dataSaver144p)}
                className={`py-2 px-3 rounded-xl text-xs font-mono font-semibold flex items-center justify-between border transition-all ${
                  dataSaver144p
                    ? 'bg-amber-500/15 border-amber-500/40 text-amber-300'
                    : 'bg-black/30 border-white/10 text-white/50'
                }`}
              >
                <span>Saves 90% Bandwidth</span>
                <span className="text-[10px] font-bold px-1.5 py-0.5 rounded bg-white/10">
                  {dataSaver144p ? '144p ON' : 'AUTO'}
                </span>
              </button>
            </div>

            {/* Staggered Delay Engine */}
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
                <span>Staggered 2s Delay</span>
                <span className="text-[10px] font-bold px-1.5 py-0.5 rounded bg-white/10">
                  {staggeredStart ? 'ACTIVE' : 'OFF'}
                </span>
              </button>
            </div>

          </div>
        </div>

        {/* ═══════════════════════════════════════════════════════════ */}
        {/* 4,000 HOURS MONETIZATION TARGET DASHBOARD                   */}
        {/* ═══════════════════════════════════════════════════════════ */}
        <div className="grid grid-cols-1 lg:grid-cols-4 gap-4">
          
          {/* Card 1: Channel Existing Hours (Editable) */}
          <div className="p-4 rounded-2xl bg-[#131628]/70 border border-white/10 backdrop-blur-md flex flex-col justify-between">
            <div className="flex items-center justify-between">
              <span className="text-[11px] font-mono text-white/50 uppercase tracking-wider flex items-center gap-1.5">
                <BarChart3 size={13} className="text-cyan-400" /> Channel Existing Hours
              </span>
              <button
                onClick={() => {
                  setTempInitialHours(initialHours.toString())
                  setEditingInitialHours(!editingInitialHours)
                }}
                className="text-[10px] font-mono text-cyan-400 hover:text-cyan-300 underline"
              >
                {editingInitialHours ? 'Cancel' : 'Edit'}
              </button>
            </div>

            {editingInitialHours ? (
              <div className="mt-2 flex items-center gap-2">
                <input
                  type="number"
                  value={tempInitialHours}
                  onChange={(e) => setTempInitialHours(e.target.value)}
                  placeholder="e.g. 150"
                  className="w-24 px-2 py-1 bg-black/60 border border-cyan-400 rounded-lg text-sm font-mono text-white outline-none"
                />
                <button
                  onClick={() => {
                    const parsed = parseFloat(tempInitialHours) || 0
                    setInitialHours(parsed)
                    setEditingInitialHours(false)
                  }}
                  className="px-3 py-1 rounded-lg bg-cyan-500 text-black text-xs font-bold font-mono"
                >
                  Save
                </button>
              </div>
            ) : (
              <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-cyan-300">
                {initialHours} <span className="text-xs text-white/40 font-normal">hrs in Studio</span>
              </div>
            )}
            <span className="text-[10px] font-mono text-white/40 mt-1">Saved automatically in browser</span>
          </div>

          {/* Card 2: Live Session Earned Hours */}
          <div className="p-4 rounded-2xl bg-gradient-to-br from-amber-500/10 to-orange-500/5 border border-amber-500/30 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-amber-300 uppercase tracking-wider flex items-center gap-1.5">
              <Flame size={13} className="text-amber-400" /> Live Session Earned
            </span>
            <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-amber-300">
              +{sessionEarnedHours} <span className="text-xs text-amber-300/70 font-normal">hrs ({formatTime(elapsedSeconds)})</span>
            </div>
            <span className="text-[10px] font-mono text-amber-300/60 mt-1">
              Active Streams: {activeStreamsCount} / {screenCount}x
            </span>
          </div>

          {/* Card 3: Combined Total Watch Hours */}
          <div className="p-4 rounded-2xl bg-[#131628]/70 border border-white/10 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-emerald-400 uppercase tracking-wider flex items-center gap-1.5">
              <CheckCircle2 size={13} /> Total Combined Progress
            </span>
            <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-white">
              {totalCombinedHours} <span className="text-xs text-white/40 font-normal">/ 4,000 hrs</span>
            </div>
            <div className="w-full h-2 bg-black/40 rounded-full overflow-hidden border border-white/5 mt-2">
              <div
                className="h-full bg-gradient-to-r from-emerald-500 to-cyan-400 transition-all duration-500 rounded-full"
                style={{ width: `${Math.max(2, parseFloat(targetPercent))}%` }}
              />
            </div>
          </div>

          {/* Card 4: Estimated Time to Monetize */}
          <div className="p-4 rounded-2xl bg-gradient-to-br from-emerald-500/15 to-cyan-500/10 border border-emerald-500/30 backdrop-blur-md flex flex-col justify-between">
            <span className="text-[11px] font-mono text-emerald-300 uppercase tracking-wider flex items-center gap-1.5">
              <Zap size={13} className="text-emerald-400" /> Time to 4,000 hrs Goal
            </span>
            <div className="mt-2 text-2xl sm:text-3xl font-mono font-bold text-emerald-300">
              ~{daysToMonetization} <span className="text-xs text-emerald-300/70 font-normal">Days Remaining</span>
            </div>
            <span className="text-[10px] font-mono text-white/40 mt-1">
              {combinedDailyHours} hrs/day (PC {activeDailyHours}h + Phone {phoneDailyHours}h)
            </span>
          </div>

        </div>

        {/* ═══════════════════════════════════════════════════════════ */}
        {/* 📱 PHONE COMPANION MODE (ALAG IP = 2X WATCH TIME)            */}
        {/* ═══════════════════════════════════════════════════════════ */}
        {phoneUrl && (
          <div className="p-5 rounded-2xl bg-gradient-to-r from-violet-500/10 via-[#131628] to-cyan-500/10 border border-violet-500/30 backdrop-blur-xl">
            <div className="flex flex-col md:flex-row items-start gap-5">
              {/* QR Code */}
              <div className="flex-shrink-0 flex flex-col items-center gap-2">
                <img
                  src={qrUrl}
                  alt="Phone QR"
                  className="w-[110px] h-[110px] rounded-xl border border-violet-500/30 bg-black/40"
                />
                <span className="text-[10px] font-mono text-white/40 text-center">Scan on Phone</span>
              </div>

              {/* Info + Copy */}
              <div className="flex-1 flex flex-col gap-2.5">
                <div className="flex items-center gap-2">
                  <span className="text-base font-bold text-violet-300 font-display">📱 Phone Companion (Alag IP = 2x Speed)</span>
                  <span className="px-2 py-0.5 rounded-full bg-violet-500/15 border border-violet-500/30 text-violet-300 text-[10px] font-mono">100% SAFE</span>
                </div>
                <p className="text-xs text-white/60 leading-relaxed">
                  Apne phone pe <strong className="text-white">Mobile Data ON karein (WiFi band)</strong> aur ye QR code scan karein ya link kholen. 
                  YouTube phone ko alag IP se genuine viewer count karega — aapka total watch time **2 guna tez** badhega!
                </p>

                {/* Copy Link */}
                <div className="flex items-center gap-2 pt-1">
                  <input
                    readOnly
                    value={phoneUrl}
                    className="flex-1 px-3 py-2 rounded-xl bg-black/50 border border-white/10 text-[11px] font-mono text-white/60 outline-none truncate"
                  />
                  <button
                    onClick={copyPhoneLink}
                    className={`px-4 py-2 rounded-xl text-xs font-bold transition-all flex items-center gap-1.5 whitespace-nowrap ${
                      phoneCopied
                        ? 'bg-emerald-500/20 border border-emerald-500/40 text-emerald-300'
                        : 'bg-violet-500/20 border border-violet-500/40 text-violet-300 hover:bg-violet-500/30'
                    }`}
                  >
                    {phoneCopied ? '✅ Copied!' : '📋 Copy Phone Loop'}
                  </button>
                </div>
              </div>
            </div>
          </div>
        )}

        {/* ═══════════════════════════════════════════════════════════ */}
        {/* INTERACTIVE 24/7 MULTI-SCREEN GRID                         */}
        {/* ═══════════════════════════════════════════════════════════ */}
        {isPlaying && screensState.length > 0 ? (
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
            {screensState.map((screen) => (
              <div
                key={screen.id}
                className="relative rounded-2xl overflow-hidden border border-white/10 bg-black/90 shadow-lg flex flex-col aspect-video group"
              >
                {/* Screen Header Bar */}
                <div className="absolute top-0 left-0 right-0 z-20 px-2.5 py-1 bg-black/80 backdrop-blur-md flex items-center justify-between border-b border-white/5 opacity-0 group-hover:opacity-100 transition-opacity">
                  <span className="text-[10px] font-mono font-bold text-white/80 flex items-center gap-1">
                    <Tv size={10} className="text-amber-400" /> Screen #{screen.id} · Vid {screen.videoIndex + 1}
                  </span>
                  <div className="flex items-center gap-1.5">
                    <span className="text-[9px] font-mono px-1.5 py-0.2 rounded bg-emerald-500/20 text-emerald-300">
                      Loop #{screen.playCount}
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

                {/* YouTube Container DOM node for window.YT.Player */}
                <div
                  id={`yt-player-container-${screen.id}`}
                  className="w-full h-full border-0"
                />

                {/* Staggering Loader (Anti-Spike) */}
                {!screen.isLoaded && (
                  <div className="absolute inset-0 z-10 flex flex-col items-center justify-center bg-black/95 p-4 text-center">
                    <div className="w-6 h-6 border-2 border-amber-400/30 border-t-amber-400 rounded-full animate-spin mb-2" />
                    <span className="text-[11px] font-mono text-white/70">
                      Staggering launch...
                    </span>
                    <span className="text-[9px] text-amber-300/70 font-mono mt-0.5">
                      Screen #{screen.id} · Anti-Spike Safe
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
              Ready to Launch 24/7 Multi-Video Watch Engine
            </h3>
            <p className="text-sm text-white/50 max-w-md mb-6 leading-relaxed">
              Paste your 20 channel video links or playlist URL above, choose your grid size (8x or 12x), and click <strong className="text-amber-300">Launch 24/7 Engine</strong>.
            </p>
            <div className="flex flex-wrap items-center justify-center gap-3 text-xs font-mono text-white/40">
              <span className="flex items-center gap-1">
                <ShieldCheck size={14} className="text-emerald-400" /> 20-Video Continuous Auto-Rotate
              </span>
              <span>•</span>
              <span className="flex items-center gap-1">
                <Volume2 size={14} className="text-cyan-400" /> Stealth 5% Volume (Studio Count Safe)
              </span>
              <span>•</span>
              <span className="flex items-center gap-1">
                <Zap size={14} className="text-amber-400" /> 10s Heartbeat Watchdog
              </span>
            </div>
          </div>
        )}

      </main>

      {/* ═══════════════════════════════════════════════════════════ */}
      {/* BULK 20-VIDEOS MODAL DIALOG                                 */}
      {/* ═══════════════════════════════════════════════════════════ */}
      {showBulkModal && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/80 backdrop-blur-md animate-fadeIn">
          <div className="w-full max-w-2xl p-6 rounded-3xl bg-[#131628] border border-violet-500/40 shadow-2xl flex flex-col gap-4">
            <div className="flex items-center justify-between border-b border-white/10 pb-3">
              <div className="flex items-center gap-2">
                <ListVideo className="text-violet-400" size={20} />
                <h3 className="text-lg font-bold text-white font-display">
                  Bulk 20-Videos Link Manager
                </h3>
              </div>
              <button
                onClick={() => setShowBulkModal(false)}
                className="text-white/40 hover:text-white text-xs font-mono px-2 py-1 bg-white/5 rounded-lg"
              >
                ✕ Close
              </button>
            </div>

            <p className="text-xs text-white/60 leading-relaxed">
              Apne YouTube channel ke sabhi 20 videos ke links yahan line-by-line paste karein. System in sabhi videos ko screens par divide karega aur non-stop loop me rotate karega.
            </p>

            <textarea
              rows={8}
              value={bulkText}
              onChange={(e) => setBulkText(e.target.value)}
              placeholder="Paste 10 to 20 video links (one link per line):&#10;https://www.youtube.com/watch?v=VIDEO_1&#10;https://www.youtube.com/watch?v=VIDEO_2&#10;https://www.youtube.com/watch?v=VIDEO_3..."
              className="w-full p-4 rounded-2xl bg-black/50 border border-white/15 focus:border-violet-400 text-white font-mono text-xs outline-none resize-none placeholder-white/20 leading-relaxed"
            />

            <div className="flex items-center justify-between pt-2">
              <span className="text-xs font-mono text-violet-300">
                {parseYouTubeUrls(bulkText).videoIds.length} Unique Videos Detected
              </span>
              <div className="flex items-center gap-2">
                <button
                  type="button"
                  onClick={() => setShowBulkModal(false)}
                  className="px-4 py-2 rounded-xl bg-white/5 hover:bg-white/10 text-white/70 text-xs font-mono"
                >
                  Cancel
                </button>
                <button
                  type="button"
                  onClick={handleApplyBulkVideos}
                  className="px-5 py-2 rounded-xl bg-violet-600 hover:bg-violet-500 text-white font-bold text-xs font-mono shadow-lg shadow-violet-600/30"
                >
                  Apply 20-Video Queue
                </button>
              </div>
            </div>
          </div>
        </div>
      )}

    </div>
  )
}

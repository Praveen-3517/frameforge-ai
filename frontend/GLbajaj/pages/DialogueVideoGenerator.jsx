import React, { useState, useEffect, useRef } from 'react'
import { Link } from 'react-router-dom'
import axios from 'axios'
import {
  Sparkles,
  ArrowLeft,
  Play,
  Pause,
  Download,
  RotateCcw,
  Volume2,
  Tv,
  Wand2,
  CheckCircle2,
  Copy,
  Check,
  Film,
  Zap,
  Flame,
  Plus,
  Trash2,
  MessageSquare,
  Users,
  Mic,
  Smile,
  Radio,
  Sliders,
  ChevronUp,
  ChevronDown,
  RefreshCw,
} from 'lucide-react'
import StarField from '../components/StarField'
import { getApiUrl, getFullMediaUrl } from '../utils/apiUrl'
import { useAuth } from '../context/AuthContext'
import UserNav from '../components/auth/UserNav'
import TokenBadge from '../components/TokenBadge'
import { fetchUserTokens } from '../utils/tokenUsage'

const DEFAULT_CHARACTERS = [
  {
    id: 'char_1',
    name: 'Rohan',
    avatar_key: 'podcast_host_m',
    voice_key: 'hi_male_madhur',
    pitch: '+0Hz',
    speech_rate: '+0%',
    theme_color: '#38BDF8',
  },
  {
    id: 'char_2',
    name: 'Priya',
    avatar_key: 'podcast_host_f',
    voice_key: 'hi_female_swara',
    pitch: '+0Hz',
    speech_rate: '+0%',
    theme_color: '#F43F5E',
  },
]

const DEFAULT_DIALOGUES = [
  {
    character_id: 'char_1',
    text: 'Bhai, subah subah adrak wali kadak Chai ke bina din hi shuru nahi hota!',
    emotion: 'happy',
  },
  {
    character_id: 'char_2',
    text: 'Excuse me? Tum abhi tak 90s mein ho! Real energy Espresso coffee mein aati hai.',
    emotion: 'sarcastic',
  },
  {
    character_id: 'char_1',
    text: 'Arrey par tumhari coffee 300 rupaye ki aati hai, aur meri chai sirf das rupaye ki!',
    emotion: 'laughing',
  },
  {
    character_id: 'char_2',
    text: 'Par taste aur aesthetic dekho! Coffee is an emotion!',
    emotion: 'surprised',
  },
  {
    character_id: 'char_1',
    text: 'Tapri wali chai hi asli emotion hai boss! Tapri zindabad!',
    emotion: 'happy',
  },
]

const QUICK_TEMPLATES = [
  {
    id: 'chai_coffee',
    name: '☕ Chai vs Coffee Debate',
    desc: 'Funny & heated Indian tea vs coffee argument',
    topic: 'Chai vs Coffee Debate',
  },
  {
    id: 'ai_future',
    name: '🤖 AI vs Human Jobs',
    desc: 'Tech podcast discussion on whether AI will take jobs',
    topic: 'Will AI replace software developers?',
  },
  {
    id: 'late_excuse',
    name: '🏫 Late to Class Excuse',
    desc: 'Funny teacher vs student conversation',
    topic: 'Hilarious excuse for being late to college class',
  },
  {
    id: 'anime_clash',
    name: '⚔️ Anime Rival Banter',
    desc: 'Intense anime battle monologue and banter',
    topic: 'Two powerful anime rivals meeting before final battle',
  },
]

const EMOTION_OPTIONS = [
  { id: 'happy', label: '😄 Happy' },
  { id: 'sarcastic', label: '😏 Sarcastic' },
  { id: 'angry', label: '😡 Angry' },
  { id: 'surprised', label: '😲 Shocked' },
  { id: 'laughing', label: '🤣 Laughing' },
  { id: 'whisper', label: '🤫 Whisper' },
  { id: 'question', label: '🤔 Question' },
  { id: 'neutral', label: '💬 Neutral' },
]

const COLOR_PALETTE = [
  '#38BDF8', // Sky Cyan
  '#F43F5E', // Rose Pink
  '#10B981', // Emerald
  '#A855F7', // Purple
  '#F59E0B', // Amber
  '#06B6D4', // Cyan
  '#EC4899', // Hot Pink
  '#8B5CF6', // Violet
]

export default function DialogueVideoGenerator() {
  const { user, openAuthModal } = useAuth()
  const [title, setTitle] = useState('Chai vs Coffee Ultimate Debate')
  const [aspectRatio, setAspectRatio] = useState('9:16')
  const [layout, setLayout] = useState('split_podcast')
  const [themeKey, setThemeKey] = useState('podcast_studio')
  const [bgMusic, setBgMusic] = useState(true)
  const [bgMusicStyle, setBgMusicStyle] = useState('lofi_chill')
  const [watermark, setWatermark] = useState('')

  const [characters, setCharacters] = useState(DEFAULT_CHARACTERS)
  const [dialogues, setDialogues] = useState(DEFAULT_DIALOGUES)

  // AI Script Sparker State
  const [aiTopic, setAiTopic] = useState('')
  const [aiLang, setAiLang] = useState('hinglish')
  const [aiGenre, setAiGenre] = useState('comedy')
  const [isGeneratingScript, setIsGeneratingScript] = useState(false)

  // Presets from backend
  const [presetVoices, setPresetVoices] = useState({})
  const [presetAvatars, setPresetAvatars] = useState({})
  const [presetThemes, setPresetThemes] = useState({})

  // Generation & Status state
  const [isGenerating, setIsGenerating] = useState(false)
  const [generationStep, setGenerationStep] = useState(0)
  const [generationLogs, setGenerationLogs] = useState([])
  const [resultVideo, setResultVideo] = useState(null)
  const [error, setError] = useState(null)

  // Player & UI state
  const [isPlaying, setIsPlaying] = useState(false)
  const [copied, setCopied] = useState(false)
  const [activePreviewTurn, setActivePreviewTurn] = useState(0)
  const videoRef = useRef(null)

  const stepsList = [
    { title: 'Initializing Studio & Voices', desc: 'Validating character roster and neural voice profiles' },
    { title: 'Synthesizing Neural Voiceovers', desc: 'Generating multi-character speech lines with Edge-TTS' },
    { title: 'Mixing Soundstage & Lofi Ambience', desc: 'Assembling audio track with natural breathing pauses' },
    { title: 'Rendering Active Speaker Glow & Bubbles', desc: 'Composing visual frames with speaker halo & subtitles' },
    { title: 'Compiling Final MP4 Video', desc: 'Hardware-accelerated FFmpeg concat demuxer encoding' },
  ]

  // Load presets on component mount & enforce dark cosmic mode
  useEffect(() => {
    document.documentElement.classList.add('dark')
    document.documentElement.classList.remove('light')
    async function loadPresets() {
      try {
        const base = getApiUrl()
        const res = await axios.get(`${base}/api/dialogue/presets`)
        if (res.data && res.data.status === 'success') {
          if (res.data.voices) setPresetVoices(res.data.voices)
          if (res.data.avatars) setPresetAvatars(res.data.avatars)
          if (res.data.themes) setPresetThemes(res.data.themes)
        }
      } catch (err) {
        console.warn('Could not fetch dialogue presets:', err)
      }
    }
    loadPresets()
  }, [])

  // Character Management
  const handleAddCharacter = () => {
    if (characters.length >= 4) {
      alert('Maximum 4 characters allowed for optimal layout.')
      return
    }
    const newIdx = characters.length + 1
    const newChar = {
      id: `char_${Date.now().toString(36)}`,
      name: `Character ${newIdx}`,
      avatar_key: newIdx % 2 === 0 ? 'podcast_host_f' : 'anime_boy',
      voice_key: newIdx % 2 === 0 ? 'hi_female_swara' : 'hi_male_madhur',
      pitch: '+0Hz',
      speech_rate: '+0%',
      theme_color: COLOR_PALETTE[newIdx % COLOR_PALETTE.length],
    }
    setCharacters([...characters, newChar])
  }

  const handleUpdateCharacter = (id, field, value) => {
    setCharacters((prev) =>
      prev.map((c) => (c.id === id ? { ...c, [field]: value } : c))
    )
  }

  const handleDeleteCharacter = (id) => {
    if (characters.length <= 2) {
      alert('Minimum 2 characters required for conversation.')
      return
    }
    const filtered = characters.filter((c) => c.id !== id)
    setCharacters(filtered)
    // Update dialogues pointing to deleted character
    setDialogues((prev) =>
      prev.map((d) =>
        d.character_id === id ? { ...d, character_id: filtered[0].id } : d
      )
    )
  }

  // Dialogue Management
  const handleAddDialogue = () => {
    const lastCharId = dialogues[dialogues.length - 1]?.character_id
    const nextChar =
      characters.find((c) => c.id !== lastCharId) || characters[0]

    setDialogues([
      ...dialogues,
      {
        character_id: nextChar.id,
        text: '',
        emotion: 'happy',
      },
    ])
  }

  const handleUpdateDialogue = (idx, field, value) => {
    setDialogues((prev) => {
      const copy = [...prev]
      copy[idx] = { ...copy[idx], [field]: value }
      return copy
    })
  }

  const handleDeleteDialogue = (idx) => {
    if (dialogues.length <= 1) {
      alert('At least 1 dialogue line is required.')
      return
    }
    setDialogues((prev) => prev.filter((_, i) => i !== idx))
  }

  const handleMoveDialogue = (idx, direction) => {
    if (
      (direction === 'up' && idx === 0) ||
      (direction === 'down' && idx === dialogues.length - 1)
    )
      return
    const targetIdx = direction === 'up' ? idx - 1 : idx + 1
    setDialogues((prev) => {
      const copy = [...prev]
      const temp = copy[idx]
      copy[idx] = copy[targetIdx]
      copy[targetIdx] = temp
      return copy
    })
  }

  // 1-Click AI Script Generator (Gemini)
  const handleGenerateAiScript = async (customTopic) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    const topicToUse = (customTopic || aiTopic || 'Funny friendship debate').trim()
    setIsGeneratingScript(true)
    setError(null)

    try {
      const base = getApiUrl()
      const res = await axios.post(`${base}/api/dialogue/ai-script`, {
        topic: topicToUse,
        language: aiLang,
        genre: aiGenre,
        char_count: characters.length,
      })

      if (res.data && res.data.script) {
        const script = res.data.script
        if (script.title) setTitle(script.title)
        if (script.characters && script.characters.length >= 2) {
          setCharacters(script.characters)
        }
        if (script.dialogues && script.dialogues.length > 0) {
          setDialogues(script.dialogues)
        }
      }
    } catch (err) {
      console.error('AI script generation error:', err)
      setError('Could not generate AI script. Please check your network.')
    } finally {
      setIsGeneratingScript(false)
    }
  }

  // Handle Video Generation with Real-Time Polling
  const handleGenerateVideo = async () => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    // Validate dialogues
    const emptyLine = dialogues.find((d) => !d.text.trim())
    if (emptyLine) {
      setError('Please fill in all dialogue lines before generating.')
      return
    }

    setIsGenerating(true)
    setError(null)
    setResultVideo(null)
    setGenerationStep(0)
    setGenerationLogs(['🚀 Initializing Multi-Character Studio pipeline...'])

    try {
      const base = getApiUrl()
      const payload = {
        title: title.trim() || 'AI Podcast Conversation',
        aspect_ratio: aspectRatio,
        layout,
        theme_key: themeKey,
        characters,
        dialogues: dialogues.map((d) => ({
          character_id: d.character_id,
          text: d.text.trim(),
          emotion: d.emotion || 'neutral',
        })),
        bg_music: bgMusic,
        bg_music_style: bgMusicStyle,
        channel_watermark: watermark.trim(),
      }

      const userEmail = user?.email || localStorage.getItem('user_email') || ''
      const res = await axios.post(`${base}/api/dialogue/generate`, payload, {
        headers: {
          'X-User-Email': userEmail
        },
        timeout: 20000,
      })

      if (res.data && res.data.job_id) {
        if (userEmail) fetchUserTokens(userEmail)
        const jobId = res.data.job_id
        setGenerationLogs((l) => [
          ...l,
          `📋 Job queued (ID: ${jobId}). Synthesizing neural dialogue audio...`,
        ])

        let isDone = false
        const maxPolls = 150

        for (let i = 0; i < maxPolls; i++) {
          await new Promise((r) => setTimeout(r, 800))

          try {
            const statusRes = await axios.get(
              `${base}/api/dialogue/status/${jobId}`,
              { timeout: 10000 }
            )
            const jobData = statusRes.data

            if (jobData.step !== undefined) {
              setGenerationStep(Math.max(0, jobData.step - 1))
            }

            if (jobData.step_name) {
              const logMsg = `⚡ ${jobData.step_name} (${
                jobData.progress_pct || 0
              }%)`
              setGenerationLogs((prev) =>
                !prev.includes(logMsg) ? [...prev, logMsg] : prev
              )
            }

            if (jobData.status === 'completed') {
              isDone = true
              setGenerationStep(5)
              setResultVideo(jobData)
              setGenerationLogs((l) => [
                ...l,
                `✅ Video complete! Saved as ${jobData.filename} (${jobData.duration}s)`,
              ])
              break
            } else if (jobData.status === 'failed') {
              throw new Error(
                jobData.error || 'Video generation failed on backend.'
              )
            }
          } catch (pollErr) {
            if (pollErr.message && !pollErr.message.includes('timeout')) {
              throw pollErr
            }
          }
        }

        if (!isDone) {
          throw new Error('Video generation timed out while waiting for output.')
        }
      } else {
        throw new Error('Server returned unexpected queue response.')
      }
    } catch (err) {
      console.error('Dialogue video generation failed:', err)
      let errorText = ''
      if (err.code === 'ECONNABORTED' || err.message?.includes('timeout')) {
        errorText =
          'Request timed out. Please ensure the Python backend server is running on http://localhost:8000 (run `start-app.bat`).'
      } else if (err.code === 'ERR_NETWORK' || !err.response) {
        errorText =
          'Cannot connect to backend server. Make sure Python backend is active on http://localhost:8000 (run `start-app.bat`).'
      } else {
        errorText =
          err.response?.data?.detail ||
          err.message ||
          'Video synthesis encountered an error.'
      }
      setError(errorText)
    } finally {
      setIsGenerating(false)
    }
  }

  const togglePlay = () => {
    if (!videoRef.current) return
    if (isPlaying) {
      videoRef.current.pause()
      setIsPlaying(false)
    } else {
      videoRef.current.play()
      setIsPlaying(true)
    }
  }

  const handleCopyLink = (url) => {
    navigator.clipboard.writeText(url)
    setCopied(true)
    setTimeout(() => setCopied(false), 2000)
  }

  // Active dialogue line for live visual simulator
  const activeLine = dialogues[activePreviewTurn] || dialogues[0] || {}
  const activeChar =
    characters.find((c) => c.id === activeLine.character_id) || characters[0]

  return (
    <div className="relative min-h-screen flex flex-col bg-[#070913] text-white font-sans selection:bg-cyan-500/30 selection:text-cyan-200">
      <StarField />

      {/* Ambient Neon Orbs */}
      <div
        className="orb w-96 h-96 bg-cyan-600/15 -top-48 -left-48"
        style={{ animationDelay: '0s' }}
      />
      <div
        className="orb w-96 h-96 bg-rose-600/15 top-1/3 -right-48"
        style={{ animationDelay: '2.5s' }}
      />
      <div
        className="orb w-80 h-80 bg-purple-600/10 bottom-10 left-1/4"
        style={{ animationDelay: '4.5s' }}
      />

      {/* Header */}
      <header className="relative z-40 flex items-center justify-between px-6 py-4 max-w-7xl mx-auto w-full border-b border-white/5 backdrop-blur-md">
        <Link
          to="/"
          className="flex items-center gap-2 text-white/50 hover:text-white transition-colors text-sm font-medium"
        >
          <ArrowLeft size={16} /> Back to Dashboard
        </Link>
        <div className="flex items-center gap-3">
          <TokenBadge userEmail={user?.email} />
          <span className="hidden sm:flex items-center gap-1.5 px-3 py-1 rounded-full bg-cyan-500/10 border border-cyan-500/30 text-cyan-300 text-xs font-mono font-medium">
            <Radio size={12} className="text-cyan-400 animate-pulse" /> AI Multi-Voice Studio v4.0
          </span>
          <UserNav />
        </div>
      </header>

      {/* Main Studio Container */}
      <main className="relative z-10 flex-1 max-w-7xl mx-auto w-full px-4 sm:px-6 py-6 pb-24">
        {/* Title & One-Click Templates */}
        <div className="flex flex-col md:flex-row md:items-end justify-between gap-4 mb-6">
          <div>
            <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-white/5 border border-white/10 text-xs font-mono text-cyan-300 mb-2">
              <Sparkles size={12} className="text-cyan-400" /> Multi-Character AI Dialogue & Podcast Studio
            </div>
            <h1 className="text-3xl sm:text-4xl font-display font-extrabold text-white tracking-tight">
              Create <span className="bg-gradient-to-r from-cyan-400 via-rose-400 to-purple-400 bg-clip-text text-transparent">Multi-Character Video</span> Conversations
            </h1>
            <p className="text-white/50 text-sm mt-1">
              Add dialogues, pick ultra-smooth neural voices for each speaker, or let Gemini AI auto-write the script.
            </p>
          </div>

          {/* Quick Preset Buttons */}
          <div className="flex items-center gap-2 overflow-x-auto pb-1 max-w-full">
            {QUICK_TEMPLATES.map((tmpl) => (
              <button
                key={tmpl.id}
                onClick={() => {
                  setAiTopic(tmpl.topic)
                  handleGenerateAiScript(tmpl.topic)
                }}
                disabled={isGeneratingScript}
                className="px-3 py-1.5 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-xs font-medium text-white/80 hover:text-white whitespace-nowrap transition-all flex items-center gap-1.5 cursor-pointer disabled:opacity-50"
              >
                <span>{tmpl.name}</span>
              </button>
            ))}
          </div>
        </div>

        {/* 2-Column Grid Layout */}
        <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 items-start">
          
          {/* Left Column: Controls, Characters & Dialogue Script (7 cols) */}
          <div className="lg:col-span-7 flex flex-col gap-6">

            {/* AI 1-Click Script Sparker Card */}
            <div className="bg-gradient-to-br from-cyan-950/40 via-white/5 to-purple-950/40 border border-cyan-500/30 rounded-2xl p-5 backdrop-blur-md shadow-xl">
              <div className="flex items-center justify-between mb-3">
                <div className="flex items-center gap-2">
                  <div className="w-7 h-7 rounded-lg bg-cyan-500/20 border border-cyan-500/40 flex items-center justify-center text-cyan-300">
                    <Wand2 size={15} />
                  </div>
                  <span className="text-sm font-display font-bold text-white">
                    1-Click Gemini AI Script Sparker
                  </span>
                </div>
                <span className="text-[10px] font-mono px-2 py-0.5 rounded-full bg-cyan-500/10 text-cyan-300 border border-cyan-500/20">
                  AI Auto-Write
                </span>
              </div>

              <div className="flex flex-col sm:flex-row gap-2.5">
                <input
                  type="text"
                  value={aiTopic}
                  onChange={(e) => setAiTopic(e.target.value)}
                  placeholder="Enter any topic (e.g. Chai vs Coffee, AI vs Developers, Funny Late Excuse...)"
                  className="flex-1 bg-black/40 border border-white/15 focus:border-cyan-400 rounded-xl px-3.5 py-2.5 text-xs text-white placeholder:text-white/30 focus:outline-none transition-colors"
                />
                <select
                  value={aiLang}
                  onChange={(e) => setAiLang(e.target.value)}
                  className="bg-black/60 border border-white/15 focus:border-cyan-400 rounded-xl px-3 py-2.5 text-xs text-white focus:outline-none"
                >
                  <option value="hinglish">Hinglish</option>
                  <option value="hindi">Hindi</option>
                  <option value="english">English</option>
                </select>
                <select
                  value={aiGenre}
                  onChange={(e) => setAiGenre(e.target.value)}
                  className="bg-black/60 border border-white/15 focus:border-cyan-400 rounded-xl px-3 py-2.5 text-xs text-white focus:outline-none"
                >
                  <option value="comedy">Comedy & Fun</option>
                  <option value="debate">Heated Debate</option>
                  <option value="podcast">Podcast Gossip</option>
                  <option value="drama">Drama / Story</option>
                </select>
                <button
                  onClick={() => handleGenerateAiScript()}
                  disabled={isGeneratingScript}
                  className="px-4 py-2.5 rounded-xl bg-gradient-to-r from-cyan-500 to-blue-500 hover:opacity-90 active:scale-95 text-black font-display font-bold text-xs flex items-center justify-center gap-1.5 shadow-md shadow-cyan-500/20 transition-all disabled:opacity-50 cursor-pointer whitespace-nowrap"
                >
                  {isGeneratingScript ? (
                    <>
                      <Sparkles size={14} className="animate-spin" /> Writing...
                    </>
                  ) : (
                    <>
                      <Sparkles size={14} /> Auto-Write Script
                    </>
                  )}
                </button>
              </div>
            </div>

            {/* Video Settings: Title, Layout, Aspect Ratio, Theme */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4">
              <div className="flex items-center justify-between">
                <span className="text-xs font-mono text-cyan-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                  <Sliders size={14} /> Video Settings & Scene Layout
                </span>
              </div>

              {/* Title Input */}
              <div>
                <label className="text-xs text-white/70 font-medium mb-1 block">Video Title:</label>
                <input
                  type="text"
                  value={title}
                  onChange={(e) => setTitle(e.target.value)}
                  placeholder="e.g. Chai vs Coffee Ultimate Debate"
                  className="w-full bg-black/40 border border-white/15 focus:border-cyan-400 rounded-xl px-3.5 py-2 text-xs text-white focus:outline-none"
                />
              </div>

              {/* Grid: Layout, Aspect Ratio, Theme */}
              <div className="grid grid-cols-1 sm:grid-cols-3 gap-3">
                {/* Aspect Ratio */}
                <div>
                  <label className="text-xs text-white/70 font-medium mb-1 block">Format:</label>
                  <div className="grid grid-cols-2 gap-1.5">
                    <button
                      type="button"
                      onClick={() => setAspectRatio('9:16')}
                      className={`p-2 rounded-xl border text-center text-xs font-mono font-bold transition-all ${
                        aspectRatio === '9:16'
                          ? 'bg-rose-500/20 border-rose-400 text-rose-300'
                          : 'bg-black/30 border-white/10 text-white/60'
                      }`}
                    >
                      📱 9:16 Shorts
                    </button>
                    <button
                      type="button"
                      onClick={() => setAspectRatio('16:9')}
                      className={`p-2 rounded-xl border text-center text-xs font-mono font-bold transition-all ${
                        aspectRatio === '16:9'
                          ? 'bg-cyan-500/20 border-cyan-400 text-cyan-300'
                          : 'bg-black/30 border-white/10 text-white/60'
                      }`}
                    >
                      🖥️ 16:9 YouTube
                    </button>
                  </div>
                </div>

                {/* Theme Scene */}
                <div>
                  <label className="text-xs text-white/70 font-medium mb-1 block">Scene Theme:</label>
                  <select
                    value={themeKey}
                    onChange={(e) => setThemeKey(e.target.value)}
                    className="w-full bg-black/50 border border-white/15 focus:border-cyan-400 rounded-xl p-2 text-xs text-white focus:outline-none"
                  >
                    <option value="podcast_studio">🎙️ Podcast Studio</option>
                    <option value="cozy_cafe">☕ Cozy Coffee Shop</option>
                    <option value="neon_cyberpunk">🌆 Cyberpunk Rooftop</option>
                    <option value="tech_workspace">💻 Tech Creator Desk</option>
                    <option value="living_room">🛋️ Stylish Modern Room</option>
                  </select>
                </div>

                {/* Background Music */}
                <div>
                  <label className="text-xs text-white/70 font-medium mb-1 block">Background Ambience:</label>
                  <div className="flex gap-1.5">
                    <button
                      type="button"
                      onClick={() => setBgMusic(!bgMusic)}
                      className={`p-2 rounded-xl border text-xs font-mono font-bold flex-1 transition-all ${
                        bgMusic
                          ? 'bg-emerald-500/20 border-emerald-400 text-emerald-300'
                          : 'bg-black/30 border-white/10 text-white/40'
                      }`}
                    >
                      {bgMusic ? '🎵 Music: ON' : '🔇 Music: OFF'}
                    </button>
                    {bgMusic && (
                      <select
                        value={bgMusicStyle}
                        onChange={(e) => setBgMusicStyle(e.target.value)}
                        className="bg-black/50 border border-white/15 focus:border-cyan-400 rounded-xl px-2 text-xs text-white focus:outline-none"
                      >
                        <option value="lofi_chill">Lo-Fi Chill</option>
                        <option value="comedy_groove">Comedy Funk</option>
                        <option value="podcast_ambient">Ambient</option>
                      </select>
                    )}
                  </div>
                </div>
              </div>

              {/* Watermark Branding */}
              <div>
                <label className="text-xs text-white/70 font-medium mb-1 block">Channel Watermark (Optional):</label>
                <input
                  type="text"
                  value={watermark}
                  onChange={(e) => setWatermark(e.target.value)}
                  placeholder="e.g. AIStudio, TechDebates, GossipHub"
                  className="w-full bg-black/40 border border-white/15 focus:border-cyan-400 rounded-xl px-3 py-1.5 text-xs text-white placeholder:text-white/30 focus:outline-none font-mono"
                />
              </div>
            </div>

            {/* Character Roster Studio */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4">
              <div className="flex items-center justify-between">
                <span className="text-xs font-mono text-rose-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                  <Users size={14} /> Character Roster & Smooth Neural Voices ({characters.length})
                </span>
                {characters.length < 4 && (
                  <button
                    onClick={handleAddCharacter}
                    className="px-2.5 py-1 rounded-lg bg-white/10 hover:bg-white/15 text-xs font-mono text-white flex items-center gap-1 transition-colors"
                  >
                    <Plus size={12} /> Add Character
                  </button>
                )}
              </div>

              <div className="grid grid-cols-1 sm:grid-cols-2 gap-3.5">
                {characters.map((char, cIdx) => (
                  <div
                    key={char.id}
                    style={{ borderColor: `${char.theme_color}40` }}
                    className="bg-black/30 border rounded-2xl p-4 flex flex-col gap-3 relative group"
                  >
                    {/* Header: Name & Color */}
                    <div className="flex items-center justify-between gap-2">
                      <div className="flex items-center gap-2 flex-1">
                        <div
                          style={{ backgroundColor: char.theme_color }}
                          className="w-4 h-4 rounded-full shadow-md"
                        />
                        <input
                          type="text"
                          value={char.name}
                          onChange={(e) =>
                            handleUpdateCharacter(char.id, 'name', e.target.value)
                          }
                          className="bg-transparent border-b border-white/15 focus:border-white text-xs font-bold text-white focus:outline-none w-full"
                          placeholder="Character Name"
                        />
                      </div>

                      {characters.length > 2 && (
                        <button
                          onClick={() => handleDeleteCharacter(char.id)}
                          className="text-white/30 hover:text-rose-400 p-1 transition-colors"
                          title="Remove character"
                        >
                          <Trash2 size={13} />
                        </button>
                      )}
                    </div>

                    {/* Avatar Style & Color */}
                    <div className="grid grid-cols-2 gap-2">
                      <div>
                        <label className="text-[10px] text-white/50 block mb-0.5">Avatar Style:</label>
                        <select
                          value={char.avatar_key}
                          onChange={(e) =>
                            handleUpdateCharacter(char.id, 'avatar_key', e.target.value)
                          }
                          className="w-full bg-black/60 border border-white/15 rounded-lg p-1.5 text-[11px] text-white focus:outline-none"
                        >
                          <option value="podcast_host_m">🎙️ Podcast Guy</option>
                          <option value="podcast_host_f">🎙️ Podcast Woman</option>
                          <option value="anime_boy">⚡ Anime Boy</option>
                          <option value="anime_girl">🌸 Anime Girl</option>
                          <option value="pixar_boy">🧸 3D Pixar Boy</option>
                          <option value="pixar_girl">✨ 3D Pixar Girl</option>
                          <option value="funny_cat">🐱 Smart Cat</option>
                          <option value="funny_dog">🐶 Cheerful Dog</option>
                        </select>
                      </div>

                      <div>
                        <label className="text-[10px] text-white/50 block mb-0.5">Theme Color:</label>
                        <div className="flex items-center gap-1.5 pt-1">
                          {COLOR_PALETTE.slice(0, 5).map((clr) => (
                            <button
                              key={clr}
                              type="button"
                              onClick={() => handleUpdateCharacter(char.id, 'theme_color', clr)}
                              style={{ backgroundColor: clr }}
                              className={`w-5 h-5 rounded-full border transition-transform ${
                                char.theme_color === clr ? 'scale-125 border-white' : 'border-transparent opacity-60 hover:opacity-100'
                              }`}
                            />
                          ))}
                        </div>
                      </div>
                    </div>

                    {/* Voice Selection */}
                    <div>
                      <label className="text-[10px] text-white/50 block mb-0.5">Neural Voice:</label>
                      <select
                        value={char.voice_key}
                        onChange={(e) =>
                          handleUpdateCharacter(char.id, 'voice_key', e.target.value)
                        }
                        className="w-full bg-black/60 border border-white/15 rounded-lg p-1.5 text-[11px] text-white focus:outline-none"
                      >
                        <optgroup label="🇮🇳 Hindi / Hinglish Voices">
                          <option value="hi_female_swara">Swara (Hindi Female - Smooth & Sweet)</option>
                          <option value="hi_male_madhur">Madhur (Hindi Male - Deep & Energetic)</option>
                          <option value="en_in_female_neerja">Neerja (Indian English Female - Expressive)</option>
                          <option value="en_in_male_prabhat">Prabhat (Indian English Male - Confident)</option>
                        </optgroup>
                        <optgroup label="🇺🇸 US & 🇬🇧 UK English Voices">
                          <option value="en_us_female_jenny">Jenny (US English Female - Natural)</option>
                          <option value="en_us_male_guy">Guy (US English Male - Casual Podcast)</option>
                          <option value="en_us_female_aria">Aria (US English Female - Clear)</option>
                          <option value="en_us_male_christopher">Christopher (US Male - Young)</option>
                          <option value="en_gb_female_sonia">Sonia (UK British Female - Elegant)</option>
                          <option value="en_gb_male_ryan">Ryan (UK British Male - Sophisticated)</option>
                        </optgroup>
                        <optgroup label="🇵🇰 Urdu Voices">
                          <option value="ur_female_uzma">Uzma (Urdu Female - Melodious)</option>
                          <option value="ur_male_asad">Asad (Urdu Male - Warm)</option>
                        </optgroup>
                      </select>
                    </div>
                  </div>
                ))}
              </div>
            </div>

            {/* Turn-by-Turn Dialogue Script Editor */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4">
              <div className="flex items-center justify-between">
                <span className="text-xs font-mono text-purple-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                  <MessageSquare size={14} /> Dialogue Script Timeline ({dialogues.length} Turns)
                </span>
                <button
                  onClick={handleAddDialogue}
                  className="px-3 py-1.5 rounded-xl bg-gradient-to-r from-purple-500 to-pink-500 hover:opacity-90 text-white text-xs font-bold font-display flex items-center gap-1 transition-all shadow-md shadow-purple-500/20"
                >
                  <Plus size={13} /> Add Turn
                </button>
              </div>

              {/* Dialogue Line Cards */}
              <div className="flex flex-col gap-3">
                {dialogues.map((dlg, idx) => {
                  const speaker =
                    characters.find((c) => c.id === dlg.character_id) ||
                    characters[0]

                  return (
                    <div
                      key={idx}
                      onClick={() => setActivePreviewTurn(idx)}
                      style={{
                        borderColor:
                          activePreviewTurn === idx
                            ? speaker.theme_color
                            : 'rgba(255,255,255,0.08)',
                      }}
                      className={`bg-black/40 border rounded-2xl p-3.5 flex flex-col gap-2 transition-all cursor-pointer ${
                        activePreviewTurn === idx
                          ? 'ring-1 ring-white/20 bg-white/5'
                          : 'hover:border-white/20'
                      }`}
                    >
                      <div className="flex items-center justify-between gap-2">
                        {/* Speaker Selector */}
                        <div className="flex items-center gap-2">
                          <span className="text-[10px] font-mono px-1.5 py-0.5 rounded bg-white/10 text-white/50">
                            #{idx + 1}
                          </span>
                          <select
                            value={dlg.character_id}
                            onChange={(e) =>
                              handleUpdateDialogue(idx, 'character_id', e.target.value)
                            }
                            onClick={(e) => e.stopPropagation()}
                            style={{ color: speaker.theme_color }}
                            className="bg-black/60 border border-white/15 rounded-lg px-2.5 py-1 text-xs font-bold focus:outline-none"
                          >
                            {characters.map((c) => (
                              <option key={c.id} value={c.id}>
                                🗣️ {c.name}
                              </option>
                            ))}
                          </select>
                        </div>

                        {/* Emotion & Controls */}
                        <div className="flex items-center gap-1.5" onClick={(e) => e.stopPropagation()}>
                          <select
                            value={dlg.emotion}
                            onChange={(e) =>
                              handleUpdateDialogue(idx, 'emotion', e.target.value)
                            }
                            className="bg-black/60 border border-white/15 rounded-lg px-2 py-1 text-[11px] text-white/80 focus:outline-none"
                          >
                            {EMOTION_OPTIONS.map((emo) => (
                              <option key={emo.id} value={emo.id}>
                                {emo.label}
                              </option>
                            ))}
                          </select>

                          {/* Reorder up/down */}
                          <button
                            onClick={() => handleMoveDialogue(idx, 'up')}
                            disabled={idx === 0}
                            className="p-1 text-white/40 hover:text-white disabled:opacity-20 transition-colors"
                          >
                            <ChevronUp size={14} />
                          </button>
                          <button
                            onClick={() => handleMoveDialogue(idx, 'down')}
                            disabled={idx === dialogues.length - 1}
                            className="p-1 text-white/40 hover:text-white disabled:opacity-20 transition-colors"
                          >
                            <ChevronDown size={14} />
                          </button>

                          {/* Delete line */}
                          {dialogues.length > 1 && (
                            <button
                              onClick={() => handleDeleteDialogue(idx)}
                              className="p-1 text-white/30 hover:text-rose-400 transition-colors"
                            >
                              <Trash2 size={13} />
                            </button>
                          )}
                        </div>
                      </div>

                      {/* Dialogue Text Input */}
                      <textarea
                        value={dlg.text}
                        onChange={(e) =>
                          handleUpdateDialogue(idx, 'text', e.target.value)
                        }
                        onClick={(e) => e.stopPropagation()}
                        rows={2}
                        placeholder={`What does ${speaker.name} say?`}
                        className="w-full bg-black/50 border border-white/10 focus:border-cyan-400 rounded-xl p-2.5 text-xs text-white placeholder:text-white/20 focus:outline-none resize-none transition-colors"
                      />
                    </div>
                  )
                })}
              </div>

              <button
                onClick={handleAddDialogue}
                className="w-full py-2.5 rounded-xl border border-dashed border-white/20 hover:border-white/40 text-xs font-mono text-white/60 hover:text-white flex items-center justify-center gap-1.5 transition-colors cursor-pointer"
              >
                <Plus size={14} /> Add Another Turn
              </button>
            </div>

            {/* Error Banner */}
            {error && (
              <div className="p-4 rounded-xl bg-red-500/10 border border-red-500/30 text-red-300 text-xs font-mono">
                ⚠️ {error}
              </div>
            )}

            {/* Main Action Button */}
            <button
              onClick={handleGenerateVideo}
              disabled={isGenerating}
              className="w-full py-4 rounded-2xl bg-gradient-to-r from-cyan-400 via-rose-400 to-purple-400 hover:opacity-95 active:scale-[0.99] text-black font-display font-black text-lg tracking-wide shadow-xl shadow-cyan-500/25 transition-all flex items-center justify-center gap-2 disabled:opacity-50 cursor-pointer"
            >
              {isGenerating ? (
                <>
                  <Sparkles size={20} className="animate-spin text-black" />
                  Generating Multi-Voice Video...
                </>
              ) : !user ? (
                <>
                  <Sparkles size={22} className="text-amber-300 animate-pulse" />
                  <span>⚡ Sign Up to Generate Video (100% Free)</span>
                </>
              ) : (
                <>
                  <Zap size={22} className="fill-black text-black" />
                  Generate Multi-Character Video (HD MP4)
                </>
              )}
            </button>

          </div>

          {/* Right Column: Live Scene Preview & Video Output (5 cols) */}
          <div className="lg:col-span-5 flex flex-col gap-5 sticky top-6">

            {/* Live Interactive Scene Simulator */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col items-center">
              <div className="w-full flex items-center justify-between mb-4">
                <span className="text-xs font-mono text-cyan-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                  <Film size={14} /> Live Scene & Bubble Preview
                </span>
                <span className="text-[10px] font-mono px-2 py-0.5 rounded-full bg-cyan-500/20 text-cyan-300 border border-cyan-500/30">
                  Turn #{activePreviewTurn + 1} / {dialogues.length}
                </span>
              </div>

              {/* Simulated Screen */}
              <div
                style={{
                  aspectRatio: aspectRatio === '9:16' ? '9/16' : '16/9',
                  maxWidth: aspectRatio === '9:16' ? '280px' : '100%',
                }}
                className="relative w-full rounded-2xl overflow-hidden border-2 border-cyan-500/30 shadow-2xl shadow-cyan-500/20 bg-gradient-to-b from-slate-900 via-[#0E1528] to-slate-950 flex flex-col justify-between p-3.5"
              >
                {/* Header Title */}
                <div className="w-full flex items-center justify-between text-[10px] font-mono text-white/70 border-b border-white/10 pb-1.5 z-10">
                  <span className="truncate max-w-[140px] font-bold">🎙️ {title || 'AI Podcast'}</span>
                  <span>{watermark ? `@${watermark}` : '✨ Studio'}</span>
                </div>

                {/* Character Avatars Row */}
                <div className="flex items-center justify-around w-full my-auto z-10 py-2">
                  {characters.map((c) => {
                    const isTurnActive = c.id === activeChar.id
                    return (
                      <div
                        key={c.id}
                        className={`flex flex-col items-center gap-1.5 transition-all ${
                          isTurnActive ? 'scale-110' : 'opacity-60 scale-90'
                        }`}
                      >
                        {/* Avatar Circle with Glow */}
                        <div
                          style={{
                            borderColor: isTurnActive ? c.theme_color : 'rgba(255,255,255,0.2)',
                            boxShadow: isTurnActive ? `0 0 20px ${c.theme_color}60` : 'none',
                          }}
                          className="w-16 h-16 rounded-full border-2 bg-black/60 flex items-center justify-center text-xl font-bold text-white relative"
                        >
                          <span style={{ color: c.theme_color }}>
                            {c.name.slice(0, 2).toUpperCase()}
                          </span>

                          {/* Equalizer dots on active */}
                          {isTurnActive && (
                            <div className="absolute -bottom-2 flex gap-0.5">
                              <div className="w-1 h-3 bg-cyan-400 rounded-full animate-bounce" />
                              <div className="w-1 h-4 bg-cyan-400 rounded-full animate-bounce [animation-delay:0.2s]" />
                              <div className="w-1 h-2 bg-cyan-400 rounded-full animate-bounce [animation-delay:0.4s]" />
                            </div>
                          )}
                        </div>

                        {/* Name Tag */}
                        <span
                          style={{
                            backgroundColor: isTurnActive ? c.theme_color : 'rgba(0,0,0,0.5)',
                            color: isTurnActive ? '#000' : '#fff',
                          }}
                          className="text-[10px] font-bold px-2 py-0.5 rounded-full font-display shadow-md"
                        >
                          {c.name}
                        </span>
                      </div>
                    )
                  })}
                </div>

                {/* Dynamic Speech Bubble */}
                <div
                  style={{
                    borderColor: `${activeChar.theme_color}90`,
                  }}
                  className="w-full bg-slate-950/90 border-2 rounded-xl p-3 z-10 flex flex-col gap-1 shadow-lg"
                >
                  <div className="flex items-center justify-between text-[10px] border-b border-white/10 pb-1">
                    <span style={{ color: activeChar.theme_color }} className="font-bold">
                      🗣️ {activeChar.name}
                    </span>
                    <span className="text-white/60">
                      {EMOTION_OPTIONS.find((e) => e.id === activeLine.emotion)?.label || '💬'}
                    </span>
                  </div>
                  <p className="text-xs text-white font-medium leading-snug line-clamp-3 pt-0.5">
                    "{activeLine.text || 'Dialogue text preview will appear here...'}"
                  </p>
                </div>
              </div>

              {/* Turn Selector Mini Bar */}
              <div className="flex items-center gap-1.5 mt-3 overflow-x-auto max-w-full pb-1">
                {dialogues.map((_, idx) => (
                  <button
                    key={idx}
                    onClick={() => setActivePreviewTurn(idx)}
                    className={`w-6 h-6 rounded-full text-[10px] font-mono font-bold transition-all ${
                      activePreviewTurn === idx
                        ? 'bg-cyan-400 text-black scale-110'
                        : 'bg-white/10 text-white/60 hover:bg-white/20'
                    }`}
                  >
                    {idx + 1}
                  </button>
                ))}
              </div>
            </div>

            {/* Live Progress Card */}
            {isGenerating && (
              <div className="bg-white/5 border border-cyan-500/40 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4 animate-pulse">
                <div className="flex items-center justify-between">
                  <span className="text-xs font-mono text-cyan-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                    <Sparkles size={14} className="animate-spin" /> Synthesizing Dialogue Video...
                  </span>
                  <span className="text-xs font-mono text-white/50">{generationStep + 1} / 5</span>
                </div>

                <div className="flex flex-col gap-2.5">
                  {stepsList.map((s, idx) => {
                    const isDone = generationStep > idx
                    const isCurrent = generationStep === idx
                    return (
                      <div
                        key={idx}
                        className={`flex items-start gap-2.5 p-2 rounded-xl border transition-all ${
                          isCurrent
                            ? 'bg-cyan-500/20 border-cyan-500/50 text-white'
                            : isDone
                            ? 'bg-emerald-500/10 border-emerald-500/20 text-white/60'
                            : 'bg-black/20 border-white/5 text-white/30'
                        }`}
                      >
                        <div className="mt-0.5">
                          {isDone ? (
                            <CheckCircle2 size={14} className="text-emerald-400" />
                          ) : (
                            <div
                              className={`w-3.5 h-3.5 rounded-full border ${
                                isCurrent
                                  ? 'border-cyan-400 border-t-transparent animate-spin'
                                  : 'border-white/20'
                              }`}
                            />
                          )}
                        </div>
                        <div>
                          <p className={`text-xs font-bold ${isCurrent ? 'text-cyan-300' : ''}`}>{s.title}</p>
                          <p className="text-[10px] text-white/40">{s.desc}</p>
                        </div>
                      </div>
                    )
                  })}
                </div>
              </div>
            )}

            {/* Video Player Output Card */}
            {resultVideo && (
              <div className="bg-gradient-to-b from-white/10 to-white/5 border border-emerald-500/40 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4 shadow-2xl shadow-emerald-500/10">
                <div className="flex items-center justify-between">
                  <span className="text-xs font-mono text-emerald-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                    <CheckCircle2 size={14} /> Video Ready for Download!
                  </span>
                  <span className="text-[11px] font-mono px-2 py-0.5 rounded bg-emerald-500/20 text-emerald-300">
                    {resultVideo.duration}s • HD MP4
                  </span>
                </div>

                {/* HTML5 Video Player */}
                <div
                  style={{
                    aspectRatio: resultVideo.aspect_ratio === '9:16' ? '9/16' : '16/9',
                    maxWidth: resultVideo.aspect_ratio === '9:16' ? '280px' : '100%',
                  }}
                  className="relative w-full mx-auto rounded-2xl overflow-hidden bg-black border border-white/20 shadow-xl"
                >
                  <video
                    ref={videoRef}
                    src={getFullMediaUrl(resultVideo.video_url)}
                    className="w-full h-full object-cover"
                    loop
                    playsInline
                    controls
                    onPlay={() => setIsPlaying(true)}
                    onPause={() => setIsPlaying(false)}
                  />

                  <button
                    onClick={togglePlay}
                    className="absolute inset-0 flex items-center justify-center bg-black/20 hover:bg-black/40 transition-colors group cursor-pointer"
                  >
                    {!isPlaying && (
                      <div className="w-14 h-14 rounded-full bg-cyan-500/90 text-black flex items-center justify-center shadow-lg shadow-cyan-500/40 group-hover:scale-110 transition-transform">
                        <Play size={24} className="ml-1" />
                      </div>
                    )}
                  </button>
                </div>

                {/* Action Buttons */}
                <div className="flex flex-col gap-2 pt-2">
                  <a
                    href={getFullMediaUrl(resultVideo.video_url)}
                    download={resultVideo.filename}
                    className="w-full py-3 rounded-xl bg-gradient-to-r from-emerald-500 to-teal-400 hover:opacity-95 text-black font-display font-bold text-sm flex items-center justify-center gap-2 shadow-lg shadow-emerald-500/20 transition-all"
                  >
                    <Download size={16} /> Download MP4 (Ready to Post)
                  </a>

                  <button
                    onClick={() => handleCopyLink(getFullMediaUrl(resultVideo.video_url))}
                    className="w-full py-2.5 px-3 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-xs font-mono text-white/80 flex items-center justify-center gap-1.5 transition-colors cursor-pointer"
                  >
                    {copied ? <Check size={14} className="text-emerald-400" /> : <Copy size={14} />}
                    {copied ? 'Copied URL!' : 'Copy URL'}
                  </button>
                </div>
              </div>
            )}

          </div>

        </div>

      </main>
    </div>
  )
}

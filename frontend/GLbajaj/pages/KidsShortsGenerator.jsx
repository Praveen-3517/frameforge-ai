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
  Layers,
  Wand2,
  CheckCircle2,
  Copy,
  Check,
  Film,
  Zap,
  Flame,
  HelpCircle,
  Smile,
  ShieldCheck,
  Send,
} from 'lucide-react'
import StarField from '../components/StarField'
import { getApiUrl, getFullMediaUrl } from '../utils/apiUrl'
import { useAuth } from '../context/AuthContext'
import UserNav from '../components/auth/UserNav'

export default function KidsShortsGenerator() {
  const { user, openAuthModal } = useAuth()
  const [variety, setVariety] = useState('spelling_rush')
  const [word, setWord] = useState('CHUM')
  const [category, setCategory] = useState('custom')
  const [characterKey, setCharacterKey] = useState('anime_boy_explorer')
  const [themeKey, setThemeKey] = useState('green_hills')
  const [letterStyle, setLetterStyle] = useState('donut_sprinkles')
  const [voiceKey, setVoiceKey] = useState('hindi_cute_girl')
  const [speechRate, setSpeechRate] = useState('+5%')
  const [aspectRatio, setAspectRatio] = useState('9:16')
  const [watermark, setWatermark] = useState('')
  const [storyScript, setStoryScript] = useState('')

  // Presets & AI Ideas state
  const [presets, setPresets] = useState(null)
  const [aiIdeas, setAiIdeas] = useState([])
  const [loadingIdeas, setLoadingIdeas] = useState(false)

  // Generation status
  const [isGenerating, setIsGenerating] = useState(false)
  const [generationStep, setGenerationStep] = useState(0)
  const [generationLogs, setGenerationLogs] = useState([])
  const [resultVideo, setResultVideo] = useState(null)
  const [error, setError] = useState(null)
  const [copied, setCopied] = useState(false)

  const videoRef = useRef(null)
  const [isPlaying, setIsPlaying] = useState(false)

  // Step names for progress tracking
  const stepsList = [
    { title: 'Crafting Phonics Script & Letter Stack', desc: 'Analyzing syllables, phonetics and 3D bounce timing' },
    { title: 'Synthesizing Kids Voiceover', desc: 'Generating cheerful Edge-TTS kids audio with high pitch' },
    { title: 'Rendering 3D Pixar Visuals', desc: 'Generating 3D cartoon world & character mascot via FLUX' },
    { title: 'Building 3D Candy Letter Layers', desc: 'Extruding donut sugar frosting, sprinkles & tick badges' },
    { title: 'Stitching 9:16 Short & Sound FX', desc: 'Mixing boing pops, correct ding chimes & final MP4 encode' }
  ]

  // Fetch presets on load
  useEffect(() => {
    async function loadPresets() {
      try {
        const base = getApiUrl()
        const res = await axios.get(`${base}/api/kids/presets`)
        if (res.data && res.data.status === 'success') {
          setPresets(res.data)
        }
      } catch (err) {
        console.warn('Could not fetch remote presets:', err)
      }
    }
    loadPresets()
  }, [])

  // 1-Click AI Sparker
  const handleFetchAiIdeas = async (cat = category) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    setLoadingIdeas(true)
    setError(null)
    try {
      const base = getApiUrl()
      const res = await axios.post(`${base}/api/kids/ai-ideas`, {
        category: cat === 'custom' ? 'animals' : cat,
        language: voiceKey.startsWith('hindi') ? 'hindi' : 'english'
      })
      if (res.data && res.data.ideas) {
        setAiIdeas(res.data.ideas)
      }
    } catch (err) {
      console.error('AI ideas fetch failed:', err)
    } finally {
      setLoadingIdeas(false)
    }
  }

  // Handle Generate
  const handleGenerate = async () => {
    if (!user) {
      openAuthModal('signup')
      return
    }

    if (!word.trim()) {
      setError('Please enter a word or phrase!')
      return
    }

    setIsGenerating(true)
    setError(null)
    setResultVideo(null)
    setGenerationStep(0)
    setGenerationLogs(['🚀 Initializing Kids 3D video generation pipeline...'])

    try {
      const base = getApiUrl()
      const payload = {
        variety,
        word: word.toUpperCase().trim(),
        category,
        character_key: characterKey,
        theme_key: themeKey,
        letter_style: letterStyle,
        voice_key: voiceKey,
        speech_rate: speechRate,
        aspect_ratio: aspectRatio,
        story_script: storyScript,
        channel_watermark: watermark.trim(),
      }

      const res = await axios.post(`${base}/api/kids/generate`, payload, { timeout: 20000 })

      if (res.data && res.data.job_id) {
        const jobId = res.data.job_id
        setGenerationLogs(l => [...l, `📋 Job queued (ID: ${jobId}). Synthesizing 3D animation...`])
        
        let isDone = false
        const maxPolls = 120

        for (let i = 0; i < maxPolls; i++) {
          await new Promise((r) => setTimeout(r, 800))

          try {
            const statusRes = await axios.get(`${base}/api/kids/status/${jobId}`, { timeout: 10000 })
            const jobData = statusRes.data

            if (jobData.step !== undefined) {
              setGenerationStep(Math.max(0, jobData.step - 1))
            }

            if (jobData.step_name) {
              const logMsg = `⚡ ${jobData.step_name} (${jobData.progress_pct || 0}%)`
              setGenerationLogs((prev) => (!prev.includes(logMsg) ? [...prev, logMsg] : prev))
            }

            if (jobData.status === 'completed') {
              isDone = true
              setGenerationStep(5)
              setResultVideo(jobData)
              setGenerationLogs(l => [...l, `✅ Video complete! Saved as ${jobData.filename} (${jobData.duration}s)`])
              break
            } else if (jobData.status === 'failed') {
              throw new Error(jobData.error || 'Video generation failed on backend.')
            }
          } catch (pollErr) {
            if (pollErr.message && !pollErr.message.includes('timeout')) {
              throw pollErr
            }
          }
        }

        if (!isDone) {
          throw new Error('Video generation timed out. The server might still be working.')
        }

      } else if (res.data && res.data.status === 'success') {
        setGenerationStep(5)
        setResultVideo(res.data)
        setGenerationLogs(l => [...l, `✅ Video complete! Saved as ${res.data.filename}`])
      } else {
        throw new Error('Video generation returned unexpected format')
      }
    } catch (err) {
      console.error('Kids short generation failed:', err)
      let errorText = ''
      if (err.code === 'ECONNABORTED' || err.message?.includes('timeout')) {
        errorText = 'Request timed out. Please ensure the Python backend server is running on http://localhost:8000 (run `start-app.bat`).'
      } else if (err.code === 'ERR_NETWORK' || !err.response) {
        errorText = 'Cannot connect to backend server. Make sure Python backend is active on http://localhost:8000 (run `start-app.bat` or `uvicorn main:app`).'
      } else {
        errorText = err.response?.data?.detail || err.message || 'Video synthesis encountered an error.'
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

  // Predefined Categories
  const categoriesList = [
    { id: 'animals', label: '🐾 Animals', sample: 'LION' },
    { id: 'fruits', label: '🍎 Fruits', sample: 'APPLE' },
    { id: 'colors', label: '🎨 Colors', sample: 'PINK' },
    { id: 'toys', label: '🧸 Toys & Fun', sample: 'ROBOT' },
    { id: 'space', label: '🚀 Space', sample: 'MOON' },
    { id: 'numbers', label: '🔢 Numbers', sample: 'FIVE' },
  ]

  const varietiesList = [
    { id: 'spelling_rush', emoji: '🍩', title: '3D Candy Spelling Rush', desc: 'Character jumps on stacked donut letters' },
    { id: 'missing_quiz', emoji: '❓', title: 'Kids Phonics Quiz', desc: 'Missing letter challenge with chime & tick' },
    { id: 'animal_morph', emoji: '🦁', title: 'Animal Guess & Morph', desc: 'Mystery reveal with roaring sounds & facts' },
    { id: 'number_hop', emoji: '🔢', title: 'Color & Number Hop', desc: 'Stepping stone jelly blocks with counting' },
    { id: 'which_slide', emoji: '🚪', title: 'Which Slide / Door?', desc: 'Pick-one slide adventure with funny whoosh' },
    { id: 'moral_story', emoji: '📖', title: '3D Mini Moral Story', desc: 'Narrated 3D fairy tale with cute scenes' },
  ]

  // Donut colors for the live letter visualizer
  const donutColors = [
    { bg: '#FF69B4', icing: '#FFB6C1', shadow: '#C71585' },
    { bg: '#1E90FF', icing: '#87CEEB', shadow: '#00008B' },
    { bg: '#FFA500', icing: '#FFE4B5', shadow: '#CD6600' },
    { bg: '#9370DB', icing: '#DDA0DD', shadow: '#4B0082' },
    { bg: '#32CD32', icing: '#98FB98', shadow: '#006400' },
    { bg: '#FF4500', icing: '#FFA07A', shadow: '#8B0000' },
  ]

  const cleanLetters = word.toUpperCase().replace(/[^A-Z0-9]/g, '').split('').slice(0, 6)

  return (
    <div className="relative min-h-screen flex flex-col bg-[#080A12] text-white selection:bg-pink-500 selection:text-white">
      <StarField />

      {/* Playful Ambient Orbs */}
      <div className="orb w-96 h-96 bg-pink-500/20 -top-40 -left-40 blur-3xl" />
      <div className="orb w-96 h-96 bg-amber-500/15 top-1/2 -right-40 blur-3xl" />
      <div className="orb w-80 h-80 bg-cyan-500/15 bottom-10 left-1/3 blur-3xl" />

      {/* Header */}
      <header className="relative z-40 flex items-center justify-between px-6 py-4 max-w-7xl mx-auto w-full border-b border-white/10">
        <div className="flex items-center gap-3">
          <Link
            to="/"
            className="flex items-center gap-1.5 px-3 py-1.5 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-white/70 hover:text-white text-xs font-mono transition-colors"
          >
            <ArrowLeft size={14} /> Back
          </Link>
          <div className="h-4 w-px bg-white/20" />
          <div className="w-9 h-9 rounded-xl bg-gradient-to-tr from-pink-500 via-amber-400 to-cyan-400 flex items-center justify-center shadow-lg shadow-pink-500/30">
            <Sparkles size={18} className="text-white" />
          </div>
          <div>
            <div className="flex items-center gap-2">
              <span className="font-display font-bold text-white text-lg tracking-tight">
                Kids <span className="bg-gradient-to-r from-pink-400 via-yellow-300 to-cyan-400 bg-clip-text text-transparent">3D Shorts</span> & Phonics
              </span>
              <span className="px-2 py-0.5 rounded-full bg-pink-500/20 border border-pink-500/30 text-pink-300 text-[10px] font-bold uppercase tracking-wider">
                Krishna VFX Style
              </span>
            </div>
            <p className="text-[11px] text-white/40 font-mono">100% Monetizable • 0% Copyright Risk • Automated 9:16</p>
          </div>
        </div>

        <div className="flex items-center gap-3">
          <div className="hidden sm:flex items-center gap-1.5 px-3 py-1 rounded-full bg-emerald-500/10 border border-emerald-500/20 text-emerald-400 text-xs font-mono">
            <ShieldCheck size={14} /> YouTube Kids Ready
          </div>
          <UserNav />
        </div>
      </header>

      {/* Main Container */}
      <main className="relative z-10 flex-1 max-w-7xl mx-auto w-full px-4 sm:px-6 py-6 flex flex-col gap-6">

        {/* Variety Selector Carousel */}
        <div className="bg-white/5 border border-white/10 rounded-2xl p-4 backdrop-blur-md">
          <div className="flex items-center justify-between mb-3">
            <label className="text-xs font-mono text-pink-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
              <Flame size={14} className="text-pink-400" /> Select Content Variety / Viral Format
            </label>
            <span className="text-[11px] text-white/40 font-mono">6 AI Formats Supported</span>
          </div>

          <div className="grid grid-cols-2 sm:grid-cols-3 lg:grid-cols-6 gap-2.5">
            {varietiesList.map((v) => {
              const active = variety === v.id
              return (
                <button
                  key={v.id}
                  onClick={() => setVariety(v.id)}
                  className={`flex flex-col text-left p-3 rounded-xl border transition-all ${
                    active
                      ? 'bg-gradient-to-b from-pink-500/25 to-purple-600/25 border-pink-500 shadow-lg shadow-pink-500/20 scale-[1.02]'
                      : 'bg-white/5 border-white/10 hover:bg-white/10 hover:border-white/20'
                  }`}
                >
                  <span className="text-2xl mb-1.5">{v.emoji}</span>
                  <span className={`text-xs font-bold font-display ${active ? 'text-pink-300' : 'text-white'}`}>
                    {v.title}
                  </span>
                  <span className="text-[10px] text-white/50 leading-tight mt-0.5">{v.desc}</span>
                </button>
              )
            })}
          </div>
        </div>

        {/* Two Column Layout: Editor vs Preview/Player */}
        <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 items-start">
          
          {/* Left Column: Creator Controls (7 cols) */}
          <div className="lg:col-span-7 flex flex-col gap-5">
            
            {/* Word Input & AI Idea Sparker */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4">
              
              <div className="flex items-center justify-between">
                <label className="text-xs font-mono text-cyan-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                  <Wand2 size={14} /> 1. Word / Learning Target
                </label>

                <button
                  onClick={() => handleFetchAiIdeas()}
                  disabled={loadingIdeas}
                  className="flex items-center gap-1 px-3 py-1 rounded-lg bg-gradient-to-r from-amber-500/20 to-pink-500/20 border border-amber-500/30 hover:border-amber-400 text-amber-300 text-xs font-mono font-medium transition-all"
                >
                  <Sparkles size={12} className={loadingIdeas ? 'animate-spin' : ''} />
                  {loadingIdeas ? 'Thinking...' : '⚡ AI Idea Sparker'}
                </button>
              </div>

              {/* Main Word Input */}
              <div className="relative">
                <input
                  type="text"
                  value={word}
                  onChange={(e) => setWord(e.target.value.toUpperCase().slice(0, 8))}
                  placeholder="e.g. CHUM, APPLE, LION, ROBOT..."
                  className="w-full bg-black/40 border border-pink-500/40 focus:border-pink-400 rounded-xl px-4 py-3.5 text-2xl font-black font-display tracking-widest text-pink-300 placeholder:text-white/20 focus:outline-none focus:ring-2 focus:ring-pink-500/30"
                />
                <div className="absolute right-3 top-1/2 -translate-y-1/2 flex items-center gap-2">
                  <span className="text-[11px] font-mono px-2 py-0.5 rounded bg-white/10 text-white/60">
                    {cleanLetters.length} Letters
                  </span>
                </div>
              </div>

              {/* Quick Category Chips */}
              <div className="flex flex-wrap items-center gap-1.5 pt-1">
                <span className="text-[11px] text-white/40 font-mono mr-1">Quick Picks:</span>
                {categoriesList.map((c) => (
                  <button
                    key={c.id}
                    onClick={() => {
                      setCategory(c.id)
                      setWord(c.sample)
                      handleFetchAiIdeas(c.id)
                    }}
                    className={`px-2.5 py-1 rounded-lg text-xs font-mono transition-colors border ${
                      category === c.id
                        ? 'bg-pink-500/20 border-pink-500/50 text-pink-300'
                        : 'bg-white/5 border-white/10 hover:bg-white/10 text-white/70'
                    }`}
                  >
                    {c.label}
                  </button>
                ))}
              </div>

              {/* AI Ideas Drawer */}
              {aiIdeas.length > 0 && (
                <div className="mt-2 p-3 rounded-xl bg-pink-950/30 border border-pink-500/30 flex flex-col gap-2">
                  <span className="text-[11px] font-mono text-pink-300 flex items-center gap-1">
                    <Sparkles size={11} /> Viral AI Suggestions for {category.toUpperCase()}:
                  </span>
                  <div className="grid grid-cols-1 sm:grid-cols-2 gap-2">
                    {aiIdeas.map((idea, idx) => (
                      <button
                        key={idx}
                        onClick={() => {
                          setWord(idea.word)
                          if (idea.variety) setVariety(idea.variety)
                        }}
                        className="flex items-center justify-between p-2 rounded-lg bg-black/40 hover:bg-pink-500/20 border border-white/10 hover:border-pink-500/40 text-left transition-colors"
                      >
                        <div>
                          <p className="text-xs font-bold text-white">{idea.title || idea.word}</p>
                          <p className="text-[10px] text-white/50 truncate max-w-[180px]">{idea.clue || `Spell ${idea.word}`}</p>
                        </div>
                        <span className="text-xs font-black text-pink-400 font-mono px-2 py-0.5 rounded bg-pink-500/10">
                          {idea.word}
                        </span>
                      </button>
                    ))}
                  </div>
                </div>
              )}
            </div>

            {/* Customization Grid: Characters, Worlds, Styles */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4">
              <label className="text-xs font-mono text-amber-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                <Smile size={14} /> 2. Mascot, World & 3D Textures
              </label>

              {/* Character Mascot Selector */}
              <div>
                <span className="text-xs text-white/70 font-medium mb-2 block">3D Animated Character Mascot:</span>
                <div className="grid grid-cols-2 sm:grid-cols-3 gap-2">
                  {[
                    { id: 'anime_boy_explorer', name: '👦 3D Boy Explorer', desc: 'Krishna VFX Style' },
                    { id: 'chibi_panda', name: '🐼 Baby Panda', desc: 'Cute cape mascot' },
                    { id: 'superhero_kid', name: '🦸 Mini Superhero', desc: 'Red cape & star' },
                    { id: 'baby_dino', name: '🦖 Baby Dinosaur', desc: 'Friendly green dino' },
                    { id: 'cute_kitty', name: '🐱 Fluffy Kitty', desc: 'Pink bow tie kitten' },
                  ].map((c) => (
                    <button
                      key={c.id}
                      onClick={() => setCharacterKey(c.id)}
                      className={`p-2.5 rounded-xl border text-left transition-all ${
                        characterKey === c.id
                          ? 'bg-amber-500/20 border-amber-400 text-amber-300 font-bold shadow-md shadow-amber-500/10'
                          : 'bg-black/30 border-white/10 hover:border-white/20 text-white/80'
                      }`}
                    >
                      <div className="text-xs">{c.name}</div>
                      <div className="text-[10px] text-white/40">{c.desc}</div>
                    </button>
                  ))}
                </div>
              </div>

              {/* Background Theme Selector */}
              <div>
                <span className="text-xs text-white/70 font-medium mb-2 block">3D World Environment:</span>
                <div className="grid grid-cols-2 sm:grid-cols-3 gap-2">
                  {[
                    { id: 'green_hills', name: '🏞️ Sunny Green Hills', desc: 'Windows Bliss Style' },
                    { id: 'candy_land', name: '🍭 Candy Wonderland', desc: 'Lollipop trees & icing' },
                    { id: 'magic_forest', name: '🌲 Magic Forest', desc: 'Glowing mushrooms' },
                    { id: 'space_galaxy', name: '🌌 Space Galaxy', desc: 'Neon nebula & stars' },
                    { id: 'toy_castle', name: '🏰 Giant Toy Castle', desc: 'Toy brick kingdom' },
                  ].map((t) => (
                    <button
                      key={t.id}
                      onClick={() => setThemeKey(t.id)}
                      className={`p-2.5 rounded-xl border text-left transition-all ${
                        themeKey === t.id
                          ? 'bg-cyan-500/20 border-cyan-400 text-cyan-300 font-bold shadow-md shadow-cyan-500/10'
                          : 'bg-black/30 border-white/10 hover:border-white/20 text-white/80'
                      }`}
                    >
                      <div className="text-xs">{t.name}</div>
                      <div className="text-[10px] text-white/40">{t.desc}</div>
                    </button>
                  ))}
                </div>
              </div>

              {/* Letter Texture Style */}
              <div>
                <span className="text-xs text-white/70 font-medium mb-2 block">3D Letter Texture / Material:</span>
                <div className="grid grid-cols-2 sm:grid-cols-3 gap-2">
                  {[
                    { id: 'donut_sprinkles', name: '🍩 Donut & Sprinkles', desc: 'Glazed pink icing' },
                    { id: 'glossy_balloon', name: '🎈 Shiny Balloons', desc: 'Glossy metallic vinyl' },
                    { id: 'gummy_jelly', name: '🍬 Gummy Fruit Jelly', desc: 'Translucent glow' },
                    { id: 'gold_sparkle', name: '⭐ 3D Gold & Diamond', desc: 'Treasure sparkle' },
                    { id: 'clay_plasticine', name: '🎨 3D Clay Claymation', desc: 'Plasticine toy look' },
                  ].map((s) => (
                    <button
                      key={s.id}
                      onClick={() => setLetterStyle(s.id)}
                      className={`p-2.5 rounded-xl border text-left transition-all ${
                        letterStyle === s.id
                          ? 'bg-pink-500/20 border-pink-400 text-pink-300 font-bold shadow-md shadow-pink-500/10'
                          : 'bg-black/30 border-white/10 hover:border-white/20 text-white/80'
                      }`}
                    >
                      <div className="text-xs">{s.name}</div>
                      <div className="text-[10px] text-white/40">{s.desc}</div>
                    </button>
                  ))}
                </div>
              </div>
            </div>

            {/* Audio, Voice & Branding */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4">
              <label className="text-xs font-mono text-emerald-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                <Volume2 size={14} /> 3. Phonics Voice & Channel Branding
              </label>

              <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
                {/* Voice Selection */}
                <div>
                  <span className="text-xs text-white/70 font-medium mb-1.5 block">Phonics Voiceover (Edge-TTS):</span>
                  <select
                    value={voiceKey}
                    onChange={(e) => setVoiceKey(e.target.value)}
                    className="w-full bg-black/40 border border-white/15 focus:border-emerald-400 rounded-xl px-3 py-2.5 text-xs text-white focus:outline-none font-mono"
                  >
                    <option value="hindi_cute_girl">👧 Hindi Cute Voice (Swara)</option>
                    <option value="hindi_energetic_boy">👦 Hindi Energetic Boy (Madhur)</option>
                    <option value="english_kid_girl">🇬🇧 English Kid Phonics (Ana)</option>
                    <option value="english_kid_boy">🇺🇸 English Energetic Kid (Christopher)</option>
                    <option value="english_nursery_female">🎶 British Nursery Rhyme (Sonia)</option>
                  </select>
                </div>

                {/* Aspect Ratio */}
                <div>
                  <span className="text-xs text-white/70 font-medium mb-1.5 block">Format & Aspect Ratio:</span>
                  <div className="grid grid-cols-2 gap-2">
                    <button
                      type="button"
                      onClick={() => setAspectRatio('9:16')}
                      className={`p-2.5 rounded-xl border text-center text-xs font-mono font-bold transition-all ${
                        aspectRatio === '9:16'
                          ? 'bg-pink-500/20 border-pink-400 text-pink-300'
                          : 'bg-black/30 border-white/10 text-white/60'
                      }`}
                    >
                      📱 9:16 Shorts/Reels
                    </button>
                    <button
                      type="button"
                      onClick={() => setAspectRatio('16:9')}
                      className={`p-2.5 rounded-xl border text-center text-xs font-mono font-bold transition-all ${
                        aspectRatio === '16:9'
                          ? 'bg-cyan-500/20 border-cyan-400 text-cyan-300'
                          : 'bg-black/30 border-white/10 text-white/60'
                      }`}
                    >
                      🖥️ 16:9 YouTube
                    </button>
                  </div>
                </div>
              </div>

              {/* Watermark Branding */}
              <div>
                <span className="text-xs text-white/70 font-medium mb-1.5 block">Channel Watermark (Optional):</span>
                <input
                  type="text"
                  value={watermark}
                  onChange={(e) => setWatermark(e.target.value)}
                  placeholder="e.g. KrishnaVFX, KidsWorld, PhonicsKids"
                  className="w-full bg-black/40 border border-white/15 focus:border-emerald-400 rounded-xl px-3 py-2 text-xs font-mono text-white placeholder:text-white/30 focus:outline-none"
                />
              </div>
            </div>

            {/* Error Banner */}
            {error && (
              <div className="p-4 rounded-xl bg-red-500/10 border border-red-500/30 text-red-300 text-xs font-mono">
                ⚠️ {error}
              </div>
            )}

            {/* Massive Generate Button */}
            <button
              onClick={handleGenerate}
              disabled={isGenerating}
              className="w-full py-4 rounded-2xl bg-gradient-to-r from-pink-500 via-amber-400 to-cyan-400 hover:opacity-95 active:scale-[0.99] text-black font-display font-black text-lg tracking-wide shadow-xl shadow-pink-500/25 transition-all flex items-center justify-center gap-2 disabled:opacity-50 cursor-pointer"
            >
              {isGenerating ? (
                <>
                  <Sparkles size={20} className="animate-spin text-black" />
                  Generating 3D Kids Video...
                </>
              ) : !user ? (
                <>
                  <Sparkles size={22} className="text-amber-300 animate-pulse" />
                  <span>⚡ Sign Up to Generate Video (100% Free)</span>
                </>
              ) : (
                <>
                  <Zap size={22} className="fill-black text-black" />
                  Generate 3D Kids Short Video
                </>
              )}
            </button>

          </div>

          {/* Right Column: Live Donut Visualizer & Video Output Studio (5 cols) */}
          <div className="lg:col-span-5 flex flex-col gap-5">
            
            {/* Live Interactive 3D Donut Stack Simulator */}
            <div className="bg-white/5 border border-white/10 rounded-2xl p-5 backdrop-blur-md flex flex-col items-center">
              <div className="w-full flex items-center justify-between mb-4">
                <span className="text-xs font-mono text-pink-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                  <Film size={14} /> Live 3D Donut Stack Preview
                </span>
                <span className="text-[10px] font-mono px-2 py-0.5 rounded-full bg-emerald-500/20 text-emerald-300 border border-emerald-500/30">
                  Real-Time Engine
                </span>
              </div>

              {/* Visual Simulated 9:16 Canvas */}
              <div className="relative w-full max-w-[280px] aspect-[9/16] rounded-2xl overflow-hidden border-2 border-pink-500/30 shadow-2xl shadow-pink-500/20 bg-gradient-to-b from-sky-400 via-sky-300 to-emerald-400 flex flex-col items-center justify-between p-4">
                
                {/* Sun & Clouds */}
                <div className="w-full flex items-center justify-between relative z-10">
                  <div className="w-10 h-10 rounded-full bg-yellow-300 shadow-lg shadow-yellow-300/50" />
                  <div className="text-[10px] font-mono bg-white/80 text-black px-2 py-0.5 rounded-full font-bold">
                    {watermark ? `@${watermark}` : '✨ 3D Phonics'}
                  </div>
                </div>

                {/* Vertical Stacked Donut Letters */}
                <div className="flex flex-col items-center justify-center gap-2 my-auto relative z-10">
                  {cleanLetters.map((char, idx) => {
                    const color = donutColors[idx % donutColors.length]
                    return (
                      <div
                        key={idx}
                        style={{
                          backgroundColor: color.bg,
                          boxShadow: `0 8px 0 ${color.shadow}, 0 12px 20px rgba(0,0,0,0.35)`,
                        }}
                        className="w-16 h-16 rounded-2xl flex items-center justify-center text-3xl font-black text-white font-display border-2 border-white/50 transform hover:scale-110 transition-transform relative group cursor-pointer"
                      >
                        {/* Sugar Frosting Top Glow */}
                        <div
                          style={{ backgroundColor: color.icing }}
                          className="absolute inset-x-1 top-1 h-3 rounded-t-xl opacity-80"
                        />
                        {/* Letter Text */}
                        <span className="relative z-10 drop-shadow-md">{char}</span>

                        {/* Little Checkmark on active */}
                        {idx === 0 && (
                          <div className="absolute -right-3 -top-2 w-6 h-6 rounded-full bg-emerald-500 border-2 border-white flex items-center justify-center text-white text-xs font-black shadow-md">
                            ✓
                          </div>
                        )}
                      </div>
                    )
                  })}
                </div>

                {/* Character Mascot Badge & Bottom Banner */}
                <div className="w-full relative z-10 flex flex-col items-center gap-2">
                  <div className="px-4 py-1.5 rounded-xl bg-white/90 shadow-lg border border-pink-400 text-center w-full">
                    <span className="text-xs font-black text-pink-600 font-display">
                      ✨ {word || 'CHUM'}! ✨
                    </span>
                  </div>
                </div>

                {/* Rolling Green Hills Background Cutout */}
                <div className="absolute inset-x-0 bottom-0 h-1/3 bg-gradient-to-t from-emerald-600 to-emerald-400 rounded-t-[40px] border-t-2 border-emerald-300/40" />
              </div>
            </div>

            {/* Live Generation Progress Card */}
            {isGenerating && (
              <div className="bg-white/5 border border-pink-500/40 rounded-2xl p-5 backdrop-blur-md flex flex-col gap-4 animate-pulse">
                <div className="flex items-center justify-between">
                  <span className="text-xs font-mono text-pink-300 font-bold uppercase tracking-wider flex items-center gap-1.5">
                    <Sparkles size={14} className="animate-spin" /> Rendering in Progress...
                  </span>
                  <span className="text-xs font-mono text-white/50">{generationStep + 1} / 5</span>
                </div>

                {/* Step List */}
                <div className="flex flex-col gap-2.5">
                  {stepsList.map((s, idx) => {
                    const isDone = generationStep > idx
                    const isCurrent = generationStep === idx
                    return (
                      <div
                        key={idx}
                        className={`flex items-start gap-2.5 p-2 rounded-xl border transition-all ${
                          isCurrent
                            ? 'bg-pink-500/20 border-pink-500/50 text-white'
                            : isDone
                            ? 'bg-emerald-500/10 border-emerald-500/20 text-white/60'
                            : 'bg-black/20 border-white/5 text-white/30'
                        }`}
                      >
                        <div className="mt-0.5">
                          {isDone ? (
                            <CheckCircle2 size={14} className="text-emerald-400" />
                          ) : (
                            <div className={`w-3.5 h-3.5 rounded-full border ${isCurrent ? 'border-pink-400 border-t-transparent animate-spin' : 'border-white/20'}`} />
                          )}
                        </div>
                        <div>
                          <p className={`text-xs font-bold ${isCurrent ? 'text-pink-300' : ''}`}>{s.title}</p>
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
                <div className="relative w-full aspect-[9/16] max-w-[280px] mx-auto rounded-2xl overflow-hidden bg-black border border-white/20 shadow-xl">
                  <video
                    ref={videoRef}
                    src={getFullMediaUrl(resultVideo.video_url)}
                    className="w-full h-full object-cover"
                    loop
                    playsInline
                    onPlay={() => setIsPlaying(true)}
                    onPause={() => setIsPlaying(false)}
                  />

                  {/* Play / Pause Overlay Button */}
                  <button
                    onClick={togglePlay}
                    className="absolute inset-0 flex items-center justify-center bg-black/20 hover:bg-black/40 transition-colors group cursor-pointer"
                  >
                    {!isPlaying && (
                      <div className="w-14 h-14 rounded-full bg-pink-500/90 text-white flex items-center justify-center shadow-lg shadow-pink-500/40 group-hover:scale-110 transition-transform">
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
                    <Download size={16} /> Download 9:16 MP4 (Shorts Ready)
                  </a>

                  <div className="grid grid-cols-2 gap-2">
                    <button
                      onClick={() => handleCopyLink(getFullMediaUrl(resultVideo.video_url))}
                      className="py-2.5 px-3 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-xs font-mono text-white/80 flex items-center justify-center gap-1.5 transition-colors"
                    >
                      {copied ? <Check size={14} className="text-emerald-400" /> : <Copy size={14} />}
                      {copied ? 'Copied URL!' : 'Copy URL'}
                    </button>

                    <Link
                      to="/variant"
                      className="py-2.5 px-3 rounded-xl bg-gradient-to-r from-violet-500/20 to-pink-500/20 hover:bg-violet-500/30 border border-violet-500/30 text-xs font-mono text-violet-300 flex items-center justify-center gap-1.5 transition-colors"
                    >
                      <Layers size={14} /> Multi-Variant
                    </Link>
                  </div>
                </div>

              </div>
            )}

          </div>

        </div>

      </main>
    </div>
  )
}

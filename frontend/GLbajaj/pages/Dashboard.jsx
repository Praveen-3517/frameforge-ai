import React, { useState, useEffect } from 'react'
import { Link } from 'react-router-dom'
import {
  Video, Shirt, Layers, Fingerprint, Tv,
  MessageSquare, Sparkles, Code2, Zap, Github,
  ChevronRight, BrainCircuit, Crown, Sun, Moon,
  Trophy, ArrowRightLeft, Timer, Flame, CheckCircle2,
  Terminal, BookOpen, ArrowRight, Coffee, Clock
} from 'lucide-react'
import StarField from '../components/StarField'
import { getApiUrl } from '../utils/apiUrl'
import UserNav from '../components/auth/UserNav'

const PREMIUM_TOOLS = [
  {
    to: '/dialogue',
    icon: <MessageSquare size={22} />,
    iconBg: 'from-cyan-500 to-rose-500',
    glow: 'hover:shadow-cyan-500/20',
    borderDark: 'hover:border-amber-400/60 border-amber-500/20',
    borderLight: 'hover:border-amber-400 border-amber-200/80',
    label: 'AI Dialogue Studio',
    desc: 'Multi-character AI conversations, podcasts & debates with neural voices',
    badge: 'Hindi · English · Urdu',
  },
  {
    to: '/kids',
    icon: <Sparkles size={22} />,
    iconBg: 'from-pink-500 to-amber-400',
    glow: 'hover:shadow-pink-500/20',
    borderDark: 'hover:border-amber-400/60 border-amber-500/20',
    borderLight: 'hover:border-amber-400 border-amber-200/80',
    label: 'Kids 3D Shorts',
    desc: '3D candy letter spelling rush, phonics quiz & mini moral stories',
    badge: '9:16 Shorts',
  },
  {
    to: '/multiview',
    icon: <Tv size={22} />,
    iconBg: 'from-amber-500 to-orange-500',
    glow: 'hover:shadow-amber-500/20',
    borderDark: 'hover:border-amber-400/60 border-amber-500/20',
    borderLight: 'hover:border-amber-400 border-amber-200/80',
    label: 'Watch-Time Booster',
    desc: '4x/8x/16x multi-screen YouTube player for 4,000-hour monetization',
    badge: '4,000 Hr Engine',
  },
  {
    to: '/variant',
    icon: <Layers size={22} />,
    iconBg: 'from-cyan-500 to-teal-600',
    glow: 'hover:shadow-cyan-500/20',
    borderDark: 'hover:border-amber-400/60 border-amber-500/20',
    borderLight: 'hover:border-amber-400 border-amber-200/80',
    label: 'Video Variant Generator',
    desc: 'Re-encode videos with color grading, FPS resampling & audio normalization',
    badge: 'Transformer',
  },
]

const STANDARD_TOOLS = [
  {
    to: '/video',
    icon: <Video size={22} />,
    iconBg: 'from-violet-500 to-violet-700',
    glow: 'hover:shadow-violet-500/20',
    borderDark: 'hover:border-violet-500/50 border-white/8',
    borderLight: 'hover:border-violet-400 border-slate-200/80',
    label: 'Text to Video',
    desc: 'Convert any story into a fully narrated cinematic video in one click',
    badge: '100% Free',
  },
  {
    to: '/clothes',
    icon: <Shirt size={22} />,
    iconBg: 'from-pink-500 to-fuchsia-600',
    glow: 'hover:shadow-pink-500/20',
    borderDark: 'hover:border-pink-500/50 border-white/8',
    borderLight: 'hover:border-pink-400 border-slate-200/80',
    label: 'AI Clothes Changer',
    desc: 'Upload a photo and instantly try on new outfits with AI',
    badge: 'Virtual Try-On',
  },
  {
    to: '/fingerprint',
    icon: <Fingerprint size={22} />,
    iconBg: 'from-emerald-500 to-green-600',
    glow: 'hover:shadow-emerald-500/20',
    borderDark: 'hover:border-emerald-500/50 border-white/8',
    borderLight: 'hover:border-emerald-400 border-slate-200/80',
    label: 'Fingerprint Analyzer',
    desc: 'Analyze audio waveforms, FFT spectrum, BPM & compare dual media files',
    badge: 'Forensics',
  },
]

export default function Dashboard() {
  const [theme, setTheme] = useState(() => {
    return localStorage.getItem('dsa_theme') || 'dark'
  })

  useEffect(() => {
    localStorage.setItem('dsa_theme', theme)
    if (theme === 'light') {
      document.documentElement.classList.add('light')
    } else {
      document.documentElement.classList.remove('light')
    }
  }, [theme])

  const isLight = theme === 'light'

  return (
    <div className={`relative min-h-screen flex flex-col transition-colors duration-300 ${
      isLight ? 'bg-[#F4F6FB] text-slate-900' : 'bg-[#0B0D17] text-white'
    }`}>
      {!isLight && <StarField />}

      {/* Ambient orbs */}
      <div
        className={`orb w-96 h-96 ${isLight ? 'bg-violet-400/10' : 'bg-violet-600/20'} -top-48 -left-48`}
        style={{ animationDelay: '0s' }}
      />
      <div
        className={`orb w-80 h-80 ${isLight ? 'bg-cyan-400/10' : 'bg-cyan-600/15'} top-1/3 -right-40`}
        style={{ animationDelay: '3s' }}
      />
      <div
        className={`orb w-72 h-72 ${isLight ? 'bg-pink-400/10' : 'bg-pink-600/10'} bottom-10 left-1/3`}
        style={{ animationDelay: '5s' }}
      />

      {/* Header */}
      <header className="relative z-10 flex items-center justify-between px-6 py-4 max-w-5xl mx-auto w-full">
        <div className="flex items-center gap-2.5">
          <div className="w-8 h-8 rounded-lg bg-gradient-to-br from-violet-500 to-cyan-500 flex items-center justify-center shadow-lg shadow-violet-500/30">
            <Zap size={16} className="text-white" />
          </div>
          <span className={`font-bold text-base tracking-tight ${isLight ? 'text-slate-900' : 'text-white'}`}>
            Bittu <span className="bg-gradient-to-r from-violet-500 to-cyan-500 bg-clip-text text-transparent">AI Tools</span>
          </span>
          <span className={`hidden sm:inline-block px-2 py-0.5 rounded-full border text-[10px] font-mono ${
            isLight ? 'bg-slate-200/80 border-slate-300 text-slate-600' : 'bg-white/5 border-white/10 text-white/40'
          }`}>
            v4.4.0
          </span>
        </div>

        <nav className="flex items-center gap-3">
          {/* User Sign In / Profile Nav */}
          <UserNav isLight={isLight} />

          {/* Quick Header Theme Switcher */}
          <div className={`flex items-center p-0.5 rounded-lg border text-xs font-medium ${
            isLight ? 'bg-slate-200 border-slate-300' : 'bg-white/5 border-white/10'
          }`}>
            <button
              onClick={() => setTheme('light')}
              title="Switch to Light Theme"
              className={`flex items-center gap-1 px-2 py-1 rounded-md transition-all ${
                isLight
                  ? 'bg-white text-amber-600 font-bold shadow-sm'
                  : 'text-white/40 hover:text-white'
              }`}
            >
              <Sun size={13} />
              <span className="hidden sm:inline text-[11px]">Light</span>
            </button>
            <button
              onClick={() => setTheme('dark')}
              title="Switch to Dark Theme"
              className={`flex items-center gap-1 px-2 py-1 rounded-md transition-all ${
                !isLight
                  ? 'bg-violet-600 text-white font-bold shadow-sm'
                  : 'text-slate-500 hover:text-slate-800'
              }`}
            >
              <Moon size={13} />
              <span className="hidden sm:inline text-[11px]">Dark</span>
            </button>
          </div>

          <a
            href={`${getApiUrl()}/docs`}
            target="_blank"
            rel="noopener noreferrer"
            className={`text-xs font-mono transition-colors ${
              isLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/35 hover:text-white/65'
            }`}
          >
            API Docs
          </a>
          <a
            href="#"
            className={`flex items-center gap-1.5 text-sm transition-colors ${
              isLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/35 hover:text-white/65'
            }`}
          >
            <Github size={14} /> GitHub
          </a>
        </nav>
      </header>

      <main className="relative z-10 flex-1 flex flex-col items-center px-4 py-6 max-w-5xl mx-auto w-full">

        {/* Hero */}
        <div className="text-center mb-8">
          <h1 className={`text-3xl sm:text-4xl font-bold tracking-tight mb-2 ${
            isLight ? 'text-slate-900' : 'text-white'
          }`}>
            Select an <span className="bg-gradient-to-r from-violet-500 to-cyan-500 bg-clip-text text-transparent">AI Tool</span>
          </h1>
          <p className={`text-sm ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
            Powerful tools — media creation, forensics, DSA practice & premium features
          </p>
        </div>

        {/* ── DSA Platform — Comprehensive Featured Showcase Card ── */}
        <div className={`w-full mb-6 rounded-2xl border transition-all duration-300 backdrop-blur-sm overflow-hidden ${
          isLight
            ? 'bg-gradient-to-br from-violet-100/90 via-white to-cyan-100/90 border-violet-300/80 shadow-xl shadow-violet-200/40'
            : 'bg-gradient-to-br from-violet-950/40 via-[#0d0722] to-cyan-950/30 border-violet-500/30 hover:border-violet-400/60 shadow-xl shadow-violet-500/10'
        }`}>
          {/* Top Header Bar */}
          <div className={`p-5 sm:p-6 pb-4 flex flex-col md:flex-row md:items-center justify-between gap-4 border-b ${
            isLight ? 'border-violet-200/80' : 'border-white/8'
          }`}>
            <Link to="/dsa" className="flex items-start sm:items-center gap-3.5 group flex-1">
              <div className="w-12 h-12 rounded-xl bg-gradient-to-br from-violet-600 to-cyan-600 flex items-center justify-center shadow-lg shadow-violet-500/30 group-hover:scale-110 transition-transform shrink-0">
                <Code2 size={24} className="text-white" />
              </div>
              <div>
                <div className="flex flex-wrap items-center gap-2 mb-1">
                  <h2 className={`text-lg font-bold tracking-tight transition-colors ${
                    isLight ? 'text-slate-950 group-hover:text-violet-600' : 'text-white group-hover:text-violet-300'
                  }`}>
                    DSA Practice & Competitive Platform
                  </h2>
                  <span className={`px-2.5 py-0.5 rounded-full border text-[11px] font-mono font-bold flex items-center gap-1 ${
                    isLight
                      ? 'bg-emerald-100 border-emerald-300 text-emerald-800'
                      : 'bg-emerald-500/15 border-emerald-500/30 text-emerald-300'
                  }`}>
                    🔥 1,800 Problems
                  </span>
                  <span className={`px-2 py-0.5 rounded-full border text-[10px] font-mono font-bold ${
                    isLight
                      ? 'bg-violet-100 border-violet-300 text-violet-800'
                      : 'bg-violet-500/20 border-violet-500/30 text-violet-300'
                  }`}>
                    15 Topics · Easy to Hard
                  </span>
                  <span className={`hidden sm:inline-flex items-center gap-1 px-2 py-0.5 rounded-full border text-[10px] font-mono font-bold ${
                    isLight
                      ? 'bg-amber-100 border-amber-300 text-amber-800'
                      : 'bg-amber-500/15 border-amber-500/30 text-amber-300'
                  }`}>
                    English & हिंदी
                  </span>
                </div>
                <p className={`text-xs sm:text-sm leading-relaxed ${isLight ? 'text-slate-600 font-medium' : 'text-white/60'}`}>
                  Full in-browser algorithmic practice and FAANG technical interview prep suite with real Python 3.11 WASM.
                </p>
              </div>
            </Link>

            {/* Actions: Theme Toggle & Launch Button */}
            <div className="flex items-center gap-2.5 shrink-0 self-end md:self-center">
              <div className={`flex items-center p-1 rounded-xl border shadow-sm ${
                isLight ? 'bg-white border-slate-300' : 'bg-black/50 border-white/10'
              }`}>
                <button
                  type="button"
                  onClick={() => setTheme('light')}
                  className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-xs font-bold transition-all ${
                    isLight
                      ? 'bg-gradient-to-r from-amber-400 to-amber-500 text-slate-950 shadow-sm'
                      : 'text-white/50 hover:text-white'
                  }`}
                  title="Light Mode"
                >
                  <Sun size={12} />
                  <span>Light</span>
                </button>
                <button
                  type="button"
                  onClick={() => setTheme('dark')}
                  className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-xs font-bold transition-all ${
                    !isLight
                      ? 'bg-violet-600 text-white shadow-sm'
                      : 'text-slate-600 hover:text-slate-900'
                  }`}
                  title="Dark Mode"
                >
                  <Moon size={12} />
                  <span>Dark</span>
                </button>
              </div>

              <Link
                to="/dsa"
                className="flex items-center gap-1.5 px-4 py-2 rounded-xl text-xs font-bold bg-gradient-to-r from-violet-600 to-cyan-600 text-white shadow-md shadow-violet-500/25 hover:opacity-95 transition-all active:scale-95"
              >
                <span>Launch Hub</span>
                <ArrowRight size={14} />
              </Link>
            </div>
          </div>

          {/* Feature Highlights Grid (4 Pillars) */}
          <div className="p-5 sm:p-6 grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-4 gap-3.5">
            {/* Feature 1 */}
            <div className={`p-3.5 rounded-xl border transition-all ${
              isLight
                ? 'bg-white/80 border-violet-200/80 shadow-sm text-slate-800'
                : 'bg-white/[0.02] border-white/8 text-white'
            }`}>
              <div className="flex items-center gap-2 mb-1.5">
                <div className={`p-1.5 rounded-lg ${isLight ? 'bg-cyan-100 text-cyan-800' : 'bg-cyan-500/15 text-cyan-300'}`}>
                  <Terminal size={14} />
                </div>
                <h3 className={`text-xs font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>
                  Python 3.11 WASM Engine
                </h3>
              </div>
              <p className={`text-[11px] leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/50'}`}>
                Zero install. Real Python executes directly in your browser with automated test validation and output console.
              </p>
            </div>

            {/* Feature 2 */}
            <div className={`p-3.5 rounded-xl border transition-all ${
              isLight
                ? 'bg-white/80 border-violet-200/80 shadow-sm text-slate-800'
                : 'bg-white/[0.02] border-white/8 text-white'
            }`}>
              <div className="flex items-center gap-2 mb-1.5">
                <div className={`p-1.5 rounded-lg ${isLight ? 'bg-violet-100 text-violet-800' : 'bg-violet-500/15 text-violet-300'}`}>
                  <ArrowRightLeft size={14} />
                </div>
                <h3 className={`text-xs font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>
                  Visual Code Diff Viewer
                </h3>
              </div>
              <p className={`text-[11px] leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/50'}`}>
                Compare your workspace code side-by-side against FAANG optimal solutions with delta counts and 1-click load to editor.
              </p>
            </div>

            {/* Feature 3 */}
            <div className={`p-3.5 rounded-xl border transition-all ${
              isLight
                ? 'bg-white/80 border-violet-200/80 shadow-sm text-slate-800'
                : 'bg-white/[0.02] border-white/8 text-white'
            }`}>
              <div className="flex items-center gap-2 mb-1.5">
                <div className={`p-1.5 rounded-lg ${isLight ? 'bg-amber-100 text-amber-800' : 'bg-amber-500/15 text-amber-300'}`}>
                  <Trophy size={14} />
                </div>
                <h3 className={`text-xs font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>
                  Leaderboard & Contests
                </h3>
              </div>
              <p className={`text-[11px] leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/50'}`}>
                Compete with 24,000+ coders across India, climb tiers from Contender to Grandmaster, and simulate Weekly Algorithmic Clashes.
              </p>
            </div>

            {/* Feature 4 */}
            <div className={`p-3.5 rounded-xl border transition-all ${
              isLight
                ? 'bg-white/80 border-violet-200/80 shadow-sm text-slate-800'
                : 'bg-white/[0.02] border-white/8 text-white'
            }`}>
              <div className="flex items-center gap-2 mb-1.5">
                <div className={`p-1.5 rounded-lg ${isLight ? 'bg-rose-100 text-rose-800' : 'bg-rose-500/15 text-rose-300'}`}>
                  <Timer size={14} />
                </div>
                <h3 className={`text-xs font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>
                  FAANG Mock Interview Mode
                </h3>
              </div>
              <p className={`text-[11px] leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/50'}`}>
                Simulate real technical rounds with countdown timers, locked external hints, company tags, and bilingual (English & हिंदी) questions.
              </p>
            </div>
          </div>

          {/* Curriculum & Topics Footer Strip */}
          <div className={`px-5 sm:px-6 py-3 border-t flex flex-wrap items-center justify-between gap-2 text-[11px] font-mono ${
            isLight ? 'bg-slate-50/80 border-violet-200/60 text-slate-700' : 'bg-black/30 border-white/5 text-white/40'
          }`}>
            <div className="flex items-center gap-2 flex-wrap">
              <span className={`font-bold uppercase tracking-wider ${isLight ? 'text-violet-800' : 'text-violet-300'}`}>
                Curriculum:
              </span>
              <span>
                1,800 Curated Problems · 15 Topics (Arrays, Strings, Linked Lists, Stack, Hashing, Binary Search, Trees, Graphs, Heap, DP, Bit Manipulation, Sorting, Greedy, Recursion)
              </span>
            </div>
            <span className={`font-bold shrink-0 ${isLight ? 'text-emerald-700' : 'text-emerald-400'}`}>
              ✓ 100% Free · In-Browser Execution
            </span>
          </div>
        </div>

        {/* ── DSA With Java — Coming Soon Box (Placeholder / Under Development) ── */}
        <div className={`w-full mb-6 rounded-2xl border transition-all duration-300 backdrop-blur-sm relative overflow-hidden ${
          isLight
            ? 'bg-gradient-to-r from-amber-50/70 via-white to-orange-50/60 border-amber-200/90 shadow-lg shadow-amber-100/40'
            : 'bg-gradient-to-r from-orange-950/25 via-[#0e0918] to-amber-950/20 border-orange-500/20 shadow-md shadow-orange-950/10'
        }`}>
          {/* Top subtle highlight line */}
          <div className="absolute top-0 left-0 right-0 h-[2px] bg-gradient-to-r from-transparent via-amber-500 to-transparent opacity-70" />

          <div className="p-5 sm:p-6 flex flex-col sm:flex-row items-start sm:items-center justify-between gap-4">
            <div className="flex items-start sm:items-center gap-4 flex-1">
              {/* Java Coffee Cup Icon Badge */}
              <div className="w-12 h-12 rounded-xl bg-gradient-to-br from-amber-500 via-orange-600 to-red-600 flex items-center justify-center shadow-lg shadow-orange-500/25 text-white shrink-0">
                <Coffee size={24} />
              </div>

              <div>
                <div className="flex flex-wrap items-center gap-2 mb-1">
                  <h2 className={`text-base sm:text-lg font-bold tracking-tight ${
                    isLight ? 'text-slate-950' : 'text-white'
                  }`}>
                    DSA with Java
                  </h2>
                  <span className={`px-2.5 py-0.5 rounded-full border text-[10px] font-mono font-bold tracking-wider flex items-center gap-1.5 ${
                    isLight
                      ? 'bg-amber-100 border-amber-300 text-amber-900 shadow-sm'
                      : 'bg-amber-400/15 border-amber-400/30 text-amber-300'
                  }`}>
                    <Clock size={11} />
                    COMING SOON
                  </span>
                  <span className={`hidden sm:inline-flex items-center gap-1 px-2 py-0.5 rounded-full border text-[10px] font-mono ${
                    isLight
                      ? 'bg-orange-100 border-orange-200 text-orange-800'
                      : 'bg-orange-500/10 border-orange-500/20 text-orange-300/80'
                  }`}>
                    Java 21 · Collections Framework · LeetCode
                  </span>
                </div>

                <p className={`text-xs sm:text-sm leading-relaxed ${isLight ? 'text-slate-600 font-medium' : 'text-white/50'}`}>
                  DSA in Java is currently in active development. Stay tuned for LeetCode Java solutions, Collections Framework, and OOP design patterns.
                </p>
              </div>
            </div>

            {/* In Development Badge */}
            <div className="shrink-0 self-start sm:self-center">
              <span className={`inline-flex items-center gap-2 px-3.5 py-1.5 rounded-xl border text-xs font-semibold ${
                isLight
                  ? 'bg-amber-50 border-amber-200 text-amber-900 shadow-sm'
                  : 'bg-white/5 border-white/10 text-white/40'
              }`}>
                <span className="w-2 h-2 rounded-full bg-amber-500 animate-pulse" />
                Under Development
              </span>
            </div>
          </div>
        </div>

        {/* ── Premium Features Box ── */}
        <div className={`w-full mb-6 rounded-2xl border p-5 backdrop-blur-sm relative overflow-hidden transition-all duration-300 ${
          isLight
            ? 'bg-gradient-to-b from-amber-100/70 via-amber-50/40 to-white border-amber-300 shadow-xl shadow-amber-200/30'
            : 'bg-gradient-to-b from-amber-500/[0.08] via-amber-500/[0.02] to-transparent border-amber-500/30 shadow-lg shadow-amber-500/5'
        }`}>
          {/* Subtle top glow bar */}
          <div className="absolute top-0 left-0 right-0 h-[2px] bg-gradient-to-r from-transparent via-amber-400 to-transparent" />
          
          <div className="flex items-center justify-between mb-4">
            <div className="flex items-center gap-2.5">
              <div className="w-7 h-7 rounded-lg bg-gradient-to-br from-amber-400 to-amber-600 flex items-center justify-center shadow-md shadow-amber-500/30 text-slate-950">
                <Crown size={15} className="stroke-[2.5]" />
              </div>
              <div>
                <div className="flex items-center gap-2">
                  <h2 className={`text-base font-bold tracking-wide ${isLight ? 'text-amber-900' : 'text-amber-200'}`}>
                    Premium Features
                  </h2>
                  <span className={`px-2 py-0.5 rounded-full border text-[10px] font-mono font-bold tracking-wider ${
                    isLight
                      ? 'bg-amber-100 border-amber-300 text-amber-800'
                      : 'bg-amber-400/20 border-amber-400/40 text-amber-300'
                  }`}>
                    PRO
                  </span>
                </div>
                <p className={`text-xs ${isLight ? 'text-amber-800/70' : 'text-amber-300/50'}`}>
                  Specialized AI tools for content creators and high-engagement videos
                </p>
              </div>
            </div>
            <span className={`text-[11px] font-mono hidden sm:inline-block px-2.5 py-1 rounded-full border ${
              isLight
                ? 'bg-amber-100 border-amber-300 text-amber-800'
                : 'bg-amber-500/10 border-amber-500/20 text-amber-300/60'
            }`}>
              4 Tools Included
            </span>
          </div>

          <div className="grid grid-cols-1 sm:grid-cols-2 gap-3">
            {PREMIUM_TOOLS.map((tool) => (
              <Link
                key={tool.to}
                to={tool.to}
                className={`group block rounded-xl p-4 transition-all hover:-translate-y-0.5 hover:shadow-lg ${tool.glow} backdrop-blur-sm border ${
                  isLight
                    ? `bg-white/95 ${tool.borderLight} text-slate-800 shadow-sm`
                    : `bg-black/40 ${tool.borderDark} text-white`
                }`}
              >
                <div className="flex items-start gap-3">
                  <div className={`w-10 h-10 rounded-lg bg-gradient-to-br ${tool.iconBg} flex items-center justify-center shrink-0 group-hover:scale-110 transition-transform shadow-md`}>
                    <span className="text-white">{tool.icon}</span>
                  </div>
                  <div className="flex-1 min-w-0">
                    <div className="flex items-center justify-between gap-2 mb-1">
                      <h3 className={`text-sm font-semibold truncate ${
                        isLight ? 'text-slate-900 group-hover:text-amber-700' : 'text-white'
                      }`}>
                        {tool.label}
                      </h3>
                      <span className={`shrink-0 text-[9px] px-1.5 py-0.5 rounded font-mono whitespace-nowrap border ${
                        isLight
                          ? 'bg-amber-100 border-amber-300 text-amber-800'
                          : 'bg-amber-400/10 border-amber-400/20 text-amber-300/80'
                      }`}>
                        {tool.badge}
                      </span>
                    </div>
                    <p className={`text-xs leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/40'}`}>
                      {tool.desc}
                    </p>
                  </div>
                </div>
              </Link>
            ))}
          </div>
        </div>

        {/* ── Standard AI Tools Section ── */}
        <div className="w-full">
          <h2 className={`text-xs font-semibold uppercase tracking-widest mb-3 px-1 ${
            isLight ? 'text-slate-500' : 'text-white/30'
          }`}>
            Standard AI Tools
          </h2>
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-3">
            {STANDARD_TOOLS.map((tool) => (
              <Link
                key={tool.to}
                to={tool.to}
                className={`group block rounded-xl p-4 transition-all hover:-translate-y-0.5 hover:shadow-lg ${tool.glow} backdrop-blur-sm border ${
                  isLight
                    ? `bg-white/90 ${tool.borderLight} text-slate-800 shadow-sm`
                    : `bg-white/[0.03] ${tool.borderDark} text-white`
                }`}
              >
                <div className="flex items-start gap-3">
                  <div className={`w-10 h-10 rounded-lg bg-gradient-to-br ${tool.iconBg} flex items-center justify-center shrink-0 group-hover:scale-110 transition-transform shadow-md`}>
                    <span className="text-white">{tool.icon}</span>
                  </div>
                  <div className="flex-1 min-w-0">
                    <div className="flex items-center justify-between gap-2 mb-1">
                      <h3 className={`text-sm font-semibold truncate ${
                        isLight ? 'text-slate-900 group-hover:text-violet-600' : 'text-white'
                      }`}>
                        {tool.label}
                      </h3>
                      <span className={`shrink-0 text-[9px] px-1.5 py-0.5 rounded font-mono whitespace-nowrap border ${
                        isLight
                          ? 'bg-slate-100 border-slate-200 text-slate-600'
                          : 'bg-white/5 border-white/10 text-white/35'
                      }`}>
                        {tool.badge}
                      </span>
                    </div>
                    <p className={`text-xs leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/40'}`}>
                      {tool.desc}
                    </p>
                  </div>
                </div>
              </Link>
            ))}
          </div>
        </div>

      </main>
    </div>
  )
}

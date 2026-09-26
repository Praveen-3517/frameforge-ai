import React, { useState, useEffect } from 'react'
import { Link } from 'react-router-dom'
import {
  Video, Shirt, Fingerprint, Tv,
  MessageSquare, MessageSquarePlus, Sparkles, Code2, Zap, Github,
  ChevronRight, BrainCircuit, Crown, Sun, Moon,
  Trophy, ArrowRightLeft, Timer, Flame, CheckCircle2,
  Terminal, BookOpen, ArrowRight, Coffee, Clock
} from 'lucide-react'
import StarField from '../components/StarField'
import { getApiUrl } from '../utils/apiUrl'
import UserNav from '../components/auth/UserNav'
import TrustFooter from '../components/TrustFooter'

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
    to: '/dialogue',
    icon: <MessageSquare size={22} />,
    iconBg: 'from-cyan-500 to-rose-500',
    glow: 'hover:shadow-cyan-500/20',
    borderDark: 'hover:border-cyan-500/50 border-white/8',
    borderLight: 'hover:border-cyan-400 border-slate-200/80',
    label: 'AI Dialogue Studio',
    desc: 'Multi-character AI conversations, podcasts & debates with neural voices',
    badge: 'Hindi · English · Urdu',
  },
  {
    to: '/kids',
    icon: <Sparkles size={22} />,
    iconBg: 'from-pink-500 to-amber-400',
    glow: 'hover:shadow-pink-500/20',
    borderDark: 'hover:border-pink-500/50 border-white/8',
    borderLight: 'hover:border-pink-400 border-slate-200/80',
    label: 'Kids 3D Shorts',
    desc: '3D candy letter spelling rush, phonics quiz & mini moral stories',
    badge: '9:16 Shorts',
  },
  // HIDDEN: Watch-Time Booster card (uncomment to restore)
  // {
  //   to: '/multiview',
  //   icon: <Tv size={22} />,
  //   iconBg: 'from-amber-500 to-orange-500',
  //   glow: 'hover:shadow-amber-500/20',
  //   borderDark: 'hover:border-amber-500/50 border-white/8',
  //   borderLight: 'hover:border-amber-400 border-slate-200/80',
  //   label: 'Watch-Time Booster',
  //   desc: '4x/8x/16x multi-screen YouTube player for 4,000-hour monetization',
  //   badge: '4,000 Hr Engine',
  // },
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
    // Website always opens in light dashboard by default
    return sessionStorage.getItem('dashboard_theme') || 'light'
  })

  useEffect(() => {
    sessionStorage.setItem('dashboard_theme', theme)
    localStorage.setItem('dsa_theme', theme)
    if (theme === 'light') {
      document.documentElement.classList.add('light')
      document.documentElement.classList.remove('dark')
    } else {
      document.documentElement.classList.remove('light')
      document.documentElement.classList.add('dark')
    }
  }, [theme])

  const isLight = theme === 'light'

  return (
    <div className={`relative min-h-screen flex flex-col transition-colors duration-300 w-full max-w-[100vw] overflow-x-hidden ${
      isLight ? 'bg-[#F4F6FB] text-slate-900' : 'bg-[#0B0D17] text-white'
    }`}>
      {!isLight && <StarField />}

      {/* Ambient orbs — strictly clipped so they never stretch the mobile viewport */}
      <div className="absolute inset-0 overflow-hidden pointer-events-none">
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
      </div>

      {/* Header */}
      <header className="relative z-40 flex items-center justify-between px-3.5 sm:px-6 py-3 sm:py-4 max-w-5xl mx-auto w-full">
        <div className="flex items-center gap-2.5 shrink-0">
          <img
            src="/bittu-logo.jpg"
            alt="Bittu AI Logo"
            className="w-8 h-8 sm:w-9 sm:h-9 rounded-xl object-cover shadow-lg shadow-violet-500/25 border border-white/15 hover:scale-105 transition-transform"
          />
          <span className={`font-black text-sm sm:text-base tracking-tight ${isLight ? 'text-slate-900' : 'text-white'}`}>
            Bittu <span className="bg-gradient-to-r from-violet-500 to-cyan-500 bg-clip-text text-transparent">AI Tools</span>
          </span>
          <span className={`hidden md:inline-block px-2 py-0.5 rounded-full border text-[10px] font-mono ${
            isLight ? 'bg-slate-200/80 border-slate-300 text-slate-600' : 'bg-white/5 border-white/10 text-white/40'
          }`}>
            v4.4.0
          </span>
        </div>

        <nav className="flex items-center gap-1.5 sm:gap-2.5">
          {/* Quick Header Theme Switcher */}
          <div className={`flex items-center p-0.5 rounded-lg border text-xs font-medium ${
            isLight ? 'bg-slate-200 border-slate-300' : 'bg-white/5 border-white/10'
          }`}>
            <button
              onClick={() => setTheme('light')}
              title="Switch to Light Theme"
              className={`flex items-center gap-1 px-1.5 sm:px-2 py-1 rounded-md transition-all ${
                isLight
                  ? 'bg-white text-amber-600 font-bold shadow-sm'
                  : 'text-white/40 hover:text-white'
              }`}
            >
              <Sun size={12} />
              <span className="hidden sm:inline text-[11px]">Light</span>
            </button>
            <button
              onClick={() => setTheme('dark')}
              title="Switch to Dark Theme"
              className={`flex items-center gap-1 px-1.5 sm:px-2 py-1 rounded-md transition-all ${
                !isLight
                  ? 'bg-violet-600 text-white font-bold shadow-sm'
                  : 'text-slate-500 hover:text-slate-800'
              }`}
            >
              <Moon size={12} />
              <span className="hidden sm:inline text-[11px]">Dark</span>
            </button>
          </div>

          {/* Feedback Trigger Button */}
          <button
            onClick={() => window.dispatchEvent(new CustomEvent('open-feedback'))}
            className={`flex items-center gap-1.5 text-xs font-semibold px-2 sm:px-2.5 py-1 sm:py-1.5 rounded-xl border transition-all ${
              isLight
                ? 'bg-white border-slate-200 text-slate-700 hover:text-violet-700 shadow-sm'
                : 'bg-white/5 border-white/10 text-white/70 hover:text-white hover:bg-white/10'
            }`}
            title="Give feedback"
          >
            <MessageSquarePlus size={13} className={isLight ? 'text-violet-600' : 'text-violet-400'} />
            <span className="hidden sm:inline">Feedback</span>
          </button>

          {/* API Docs — hidden on small phones to prevent header blowout */}
          <a
            href={`${getApiUrl()}/docs`}
            target="_blank"
            rel="noopener noreferrer"
            className={`hidden md:inline-block text-xs font-mono transition-colors ${
              isLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/35 hover:text-white/65'
            }`}
          >
            API Docs
          </a>

          {/* GitHub — hidden on small phones */}
          <a
            href="#"
            className={`hidden md:flex items-center gap-1.5 text-sm transition-colors ${
              isLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/35 hover:text-white/65'
            }`}
          >
            <Github size={14} /> GitHub
          </a>

          {/* User Sign In / Profile Nav — positioned at far right */}
          <UserNav isLight={isLight} />
        </nav>
      </header>

      <main className="relative z-10 flex-1 flex flex-col items-center px-4 py-6 max-w-5xl mx-auto w-full">

        {/* Hero */}
        <div className="text-center mb-6">
          <h1 className={`text-3xl sm:text-4xl font-bold tracking-tight mb-2 ${
            isLight ? 'text-slate-900' : 'text-white'
          }`}>
            Select an <span className="bg-gradient-to-r from-violet-500 to-cyan-500 bg-clip-text text-transparent">AI Tool</span>
          </h1>
          <p className={`text-sm ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
            Powerful tools — media creation, forensics, DSA practice & premium features
          </p>
        </div>

        {/* ── Early Bird Promo Banner ── */}
        <button
          onClick={() => window.dispatchEvent(new CustomEvent('open-early-bird'))}
          className={`w-full mb-6 p-3 sm:p-3.5 rounded-2xl border transition-all hover:scale-[1.01] active:scale-[0.99] flex flex-col sm:flex-row sm:items-center justify-between gap-3 text-left group shadow-lg ${
            isLight
              ? 'bg-gradient-to-r from-amber-100 via-orange-50 to-amber-100 border-amber-300 text-amber-950 shadow-amber-200/40'
              : 'bg-gradient-to-r from-amber-500/15 via-orange-500/10 to-violet-500/15 border-amber-500/30 text-white shadow-amber-500/5'
          }`}
        >
          <div className="flex items-center gap-3">
            <span className="w-9 h-9 rounded-xl bg-amber-500 text-slate-950 flex items-center justify-center font-bold text-base shadow-md shrink-0">
              🎁
            </span>
            <div>
              <div className="flex flex-wrap items-center gap-2 mb-0.5">
                <span className="font-black text-xs sm:text-sm">
                  Special Offer: पहले 100 लोगों के लिए 100% Free Lifetime DSA Access!
                </span>
                <span className={`px-2 py-0.2 rounded-full border text-[10px] font-mono font-bold ${
                  isLight ? 'bg-amber-200 border-amber-400 text-amber-900' : 'bg-amber-400/20 border-amber-400/40 text-amber-300'
                }`}>
                  🔥 13 Passes Left
                </span>
              </div>
              <p className={`text-[11px] ${isLight ? 'text-amber-900/80 font-medium' : 'text-white/60'}`}>
                1,800 Problems, Python WASM, Visual Diff & Weekly Contests. Click to claim your free pass now!
              </p>
            </div>
          </div>

          <span className={`px-3 py-1.5 rounded-xl text-xs font-bold transition-all flex items-center gap-1.5 shrink-0 self-end sm:self-center ${
            isLight ? 'bg-amber-500 text-slate-950 shadow-sm group-hover:bg-amber-400' : 'bg-white/10 group-hover:bg-amber-500 group-hover:text-slate-950 text-amber-300'
          }`}>
            Claim Free Pass →
          </span>
        </button>

        {/* ── 1. Learning Tools Section (FIRST on Dashboard) ── */}
        <div className="w-full mb-8">
          <div className="flex items-center justify-between mb-3 px-1">
            <div className="flex items-center gap-2.5">
              <div className="w-8 h-8 rounded-xl bg-gradient-to-br from-violet-600 to-cyan-600 flex items-center justify-center shadow-md shadow-violet-500/25 text-white">
                <BookOpen size={16} />
              </div>
              <div>
                <div className="flex items-center gap-2">
                  <h2 className={`text-base sm:text-lg font-bold tracking-tight ${isLight ? 'text-slate-900' : 'text-white'}`}>
                    Learning Tools
                  </h2>
                  <span className={`px-2 py-0.5 rounded-full border text-[10px] font-mono font-bold ${
                    isLight ? 'bg-violet-100 border-violet-300 text-violet-800' : 'bg-violet-500/20 border-violet-500/30 text-violet-300'
                  }`}>
                    DSA & CODING
                  </span>
                </div>
                <p className={`text-xs ${isLight ? 'text-slate-500' : 'text-white/50'}`}>
                  In-browser algorithmic practice, interview prep & programming tracks
                </p>
              </div>
            </div>

            <Link
              to="/dsa"
              className="hidden sm:flex items-center gap-1.5 px-3 py-1.5 rounded-xl text-xs font-bold text-violet-600 dark:text-violet-400 hover:underline"
            >
              <span>View All 1,800 Problems</span>
              <ArrowRight size={13} />
            </Link>
          </div>

          {/* DSA Platform — Comprehensive Featured Showcase Card */}
          <div className={`w-full mb-4 rounded-2xl border transition-all duration-300 backdrop-blur-sm overflow-hidden ${
            isLight
              ? 'bg-gradient-to-br from-violet-100/90 via-white to-cyan-100/90 border-violet-300/80 shadow-xl shadow-violet-200/40'
              : 'bg-gradient-to-br from-violet-950/40 via-[#0d0722] to-cyan-950/30 border-violet-500/30 hover:border-violet-400/60 shadow-xl shadow-violet-500/10'
          }`}>
            {/* Top Header Bar */}
            <div className={`p-5 sm:p-6 flex flex-col md:flex-row md:items-center justify-between gap-4 border-b ${
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

            {/* Top Interview 150 Sub-Card Banner */}
            <div className={`p-4 sm:p-5 flex flex-col sm:flex-row sm:items-center justify-between gap-3 border-b ${
              isLight ? 'bg-violet-50/60 border-violet-200/70' : 'bg-white/[0.02] border-white/5'
            }`}>
              <div className="flex items-center gap-3">
                <div className="w-10 h-10 rounded-xl bg-gradient-to-br from-cyan-500 to-blue-600 text-white font-black text-xs flex flex-col items-center justify-center shrink-0 shadow-md shadow-cyan-500/20">
                  <span>TOP</span>
                  <span className="text-[9px] -mt-1 font-mono">150</span>
                </div>
                <div>
                  <div className="flex items-center gap-2">
                    <h3 className={`text-xs sm:text-sm font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>
                      LeetCode Top Interview 150 Study Plan
                    </h3>
                    <span className={`px-2 py-0.2 rounded-full border text-[9px] font-mono font-bold ${
                      isLight ? 'bg-amber-100 border-amber-300 text-amber-800' : 'bg-amber-400/15 border-amber-400/30 text-amber-300'
                    }`}>
                      FAANG Curated
                    </span>
                  </div>
                  <p className={`text-[11px] ${isLight ? 'text-slate-600' : 'text-white/50'}`}>
                    23 Core interview categories with optimal Python solutions, complexity analysis & company tags.
                  </p>
                </div>
              </div>
              <Link
                to="/dsa/top-interview-150"
                className="flex items-center gap-1.5 px-3.5 py-1.5 rounded-xl text-xs font-bold bg-gradient-to-r from-cyan-600 to-blue-600 text-white shadow-sm hover:opacity-90 transition-all self-start sm:self-center shrink-0"
              >
                <span>Open Top 150</span>
                <ArrowRight size={13} />
              </Link>
            </div>

            {/* Curriculum & Topics Footer Strip */}
            <div className={`px-5 sm:px-6 py-3 flex flex-wrap items-center justify-between gap-2 text-[11px] font-mono ${
              isLight ? 'bg-slate-50/80 text-slate-700' : 'bg-black/30 text-white/40'
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

          {/* ── Language Tracks Grid: DSA with Java & DSA with C (Side-by-Side) ── */}
          <div className="grid grid-cols-1 md:grid-cols-2 gap-3.5">
            {/* Box 1: DSA with Java — LIVE */}
            <div className={`rounded-2xl border transition-all duration-300 backdrop-blur-sm relative overflow-hidden p-4 sm:p-5 hover:-translate-y-0.5 hover:shadow-lg hover:shadow-amber-500/10 ${
              isLight
                ? 'bg-gradient-to-br from-amber-50/70 via-white to-orange-50/60 border-amber-300/90 shadow-sm'
                : 'bg-gradient-to-br from-orange-950/30 via-[#0e0918] to-amber-950/20 border-amber-500/30 shadow-md shadow-orange-950/10'
            }`}>
              <div className="absolute top-0 left-0 right-0 h-[2px] bg-gradient-to-r from-transparent via-amber-500 to-transparent opacity-90" />
              <div className="flex items-start gap-3.5">
                <div className="w-11 h-11 rounded-xl bg-gradient-to-br from-amber-500 via-orange-600 to-red-600 flex items-center justify-center shadow-lg shadow-orange-500/30 text-white shrink-0">
                  <Coffee size={22} />
                </div>
                <div className="flex-1 min-w-0">
                  <div className="flex flex-wrap items-center gap-2 mb-1">
                    <h3 className={`text-sm sm:text-base font-bold tracking-tight ${isLight ? 'text-slate-950' : 'text-white'}`}>
                      DSA with Java
                    </h3>
                    <span className={`px-2 py-0.5 rounded-full border text-[9px] font-mono font-bold tracking-wider flex items-center gap-1 ${
                      isLight ? 'bg-emerald-100 border-emerald-300 text-emerald-800' : 'bg-emerald-400/15 border-emerald-400/40 text-emerald-300'
                    }`}>
                      <span className="w-1.5 h-1.5 rounded-full bg-emerald-500 animate-pulse" />
                      LIVE
                    </span>
                  </div>
                  <p className={`text-[11px] leading-relaxed mb-2.5 ${isLight ? 'text-slate-600' : 'text-white/55'}`}>
                    20 topics · 554 problems — Arrays, Strings, OOP, Trees, Graphs, DP, Bit Manipulation, Sliding Window &amp; more. Full LeetCode solutions with complexity analysis &amp; company tags.
                  </p>
                  <div className="flex flex-wrap items-center gap-2">
                    <Link
                      to="/dsa?lang=java"
                      className="inline-flex items-center gap-1.5 px-3 py-1.5 rounded-xl text-[11px] font-bold bg-gradient-to-r from-amber-500 via-orange-500 to-red-500 text-white shadow-sm hover:opacity-90 transition-all"
                    >
                      <span>Open Java DSA</span>
                      <ArrowRight size={12} />
                    </Link>
                    <span className={`inline-flex items-center gap-1 px-2 py-1 rounded-lg border text-[10px] font-mono font-semibold ${
                      isLight ? 'bg-amber-50 border-amber-200 text-amber-800' : 'bg-amber-400/10 border-amber-400/20 text-amber-300'
                    }`}>
                      Easy · Medium · Hard
                    </span>
                  </div>
                </div>
              </div>
            </div>

            {/* Box 2: DSA with C — LIVE */}
            <div className={`rounded-2xl border transition-all duration-300 backdrop-blur-sm relative overflow-hidden p-4 sm:p-5 hover:-translate-y-0.5 hover:shadow-lg hover:shadow-cyan-500/10 ${
              isLight
                ? 'bg-gradient-to-br from-cyan-50/70 via-white to-blue-50/60 border-cyan-300/90 shadow-sm'
                : 'bg-gradient-to-br from-cyan-950/30 via-[#080d1a] to-blue-950/20 border-cyan-500/30 shadow-md shadow-cyan-950/10'
            }`}>
              <div className="absolute top-0 left-0 right-0 h-[2px] bg-gradient-to-r from-transparent via-cyan-500 to-transparent opacity-90" />
              <div className="flex items-start gap-3.5">
                <div className="w-11 h-11 rounded-xl bg-gradient-to-br from-cyan-500 via-blue-600 to-indigo-600 flex items-center justify-center shadow-lg shadow-cyan-500/30 text-white shrink-0 font-black text-lg font-mono">
                  C
                </div>
                <div className="flex-1 min-w-0">
                  <div className="flex flex-wrap items-center gap-2 mb-1">
                    <h3 className={`text-sm sm:text-base font-bold tracking-tight ${isLight ? 'text-slate-950' : 'text-white'}`}>
                      DSA with C
                    </h3>
                    <span className={`px-2 py-0.5 rounded-full border text-[9px] font-mono font-bold tracking-wider flex items-center gap-1 ${
                      isLight ? 'bg-emerald-100 border-emerald-300 text-emerald-800' : 'bg-emerald-400/15 border-emerald-400/40 text-emerald-300'
                    }`}>
                      <span className="w-1.5 h-1.5 rounded-full bg-emerald-500 animate-pulse" />
                      LIVE
                    </span>
                  </div>
                  <p className={`text-[11px] leading-relaxed mb-2.5 ${isLight ? 'text-slate-600' : 'text-white/55'}`}>
                    20 topics · 554 problems — Pointers, Dynamic Memory, Structs, Linked Lists, Trees, Graphs, DP &amp; Bit Twiddling. Production-grade low-level systems solutions.
                  </p>
                  <div className="flex flex-wrap items-center gap-2">
                    <Link
                      to="/dsa?lang=c"
                      className="inline-flex items-center gap-1.5 px-3 py-1.5 rounded-xl text-[11px] font-bold bg-gradient-to-r from-cyan-500 via-blue-600 to-indigo-600 text-white shadow-sm hover:opacity-90 transition-all"
                    >
                      <span>Open C DSA</span>
                      <ArrowRight size={12} />
                    </Link>
                    <span className={`inline-flex items-center gap-1 px-2 py-1 rounded-lg border text-[10px] font-mono font-semibold ${
                      isLight ? 'bg-cyan-50 border-cyan-200 text-cyan-800' : 'bg-cyan-400/10 border-cyan-400/20 text-cyan-300'
                    }`}>
                      Easy · Medium · Hard
                    </span>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>

        {/* ── 2. Standard AI Tools Section (All 7 AI Media Tools) ── */}
        <div className="w-full">
          <div className="flex items-center justify-between mb-3 px-1">
            <div className="flex items-center gap-2.5">
              <div className="w-8 h-8 rounded-xl bg-gradient-to-br from-pink-500 to-violet-600 flex items-center justify-center shadow-md shadow-pink-500/25 text-white">
                <Sparkles size={16} />
              </div>
              <div>
                <div className="flex items-center gap-2">
                  <h2 className={`text-base sm:text-lg font-bold tracking-tight ${isLight ? 'text-slate-900' : 'text-white'}`}>
                    Standard AI Tools
                  </h2>
                  <span className={`px-2 py-0.5 rounded-full border text-[10px] font-mono font-bold ${
                    isLight ? 'bg-slate-200 border-slate-300 text-slate-700' : 'bg-white/10 border-white/15 text-white/70'
                  }`}>
                    7 AI TOOLS
                  </span>
                </div>
                <p className={`text-xs ${isLight ? 'text-slate-500' : 'text-white/50'}`}>
                  Generative media synthesis, virtual styling, multi-speaker dialogue & forensics
                </p>
              </div>
            </div>
          </div>

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

      {/* Trust, Legal Disclaimer & Developer Attribution Footer */}
      <TrustFooter isLight={isLight} />
    </div>
  )
}

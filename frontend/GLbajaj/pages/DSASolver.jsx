import React, { useState, useEffect, useCallback, useMemo } from 'react'
import { Link, useParams, useNavigate, useSearchParams } from 'react-router-dom'
import {
  ArrowLeft, ChevronLeft, ChevronRight, Code2, BookOpen,
  Lightbulb, CheckCircle2, Circle, Bookmark, BookmarkCheck,
  RotateCcw, Tag, Clock, Play, Trophy, Zap, Share2, Check,
  Sun, Moon, Unlock, Building2, Sparkles, HelpCircle, Languages,
  ArrowRightLeft, Coffee, Terminal, Lock, Crown
} from 'lucide-react'
import CodeEditor from '../components/dsa/CodeEditor'
import TestRunner from '../components/dsa/TestRunner'
import HintPanel from '../components/dsa/HintPanel'
import SolutionPanel from '../components/dsa/SolutionPanel'
import CodeDiffViewer from '../components/dsa/CodeDiffViewer'
import InterviewTimer from '../components/dsa/InterviewTimer'
import ProPaymentModal from '../components/dsa/ProPaymentModal'
import { getCachedProStatus, fetchRemoteProStatus } from '../utils/proSubscription'
import { dsaProblems } from '../data/dsaProblems'
import { onProblemSolved, XP_MAP } from '../utils/dsaStats'
import { getProblemInterviewData } from '../data/dsaInterviewSolutions'
import { getCSolution, getCSolutionApproaches } from '../data/dsaCSolutions'
import { useAuth } from '../context/AuthContext'
import UserNav from '../components/auth/UserNav'

const difficultyConfig = {
  Easy:   { color: 'text-emerald-400', bg: 'bg-emerald-500/10', border: 'border-emerald-500/25', dot: 'bg-emerald-400' },
  Medium: { color: 'text-amber-400',   bg: 'bg-amber-500/10',   border: 'border-amber-500/25',   dot: 'bg-amber-400' },
  Hard:   { color: 'text-red-400',     bg: 'bg-red-500/10',     border: 'border-red-500/25',     dot: 'bg-red-400' },
}

function useProblemStorage(problemId, selectedLang, defaultStarterCode) {
  const { user, openAuthModal } = useAuth()
  const [code, setCode] = useState('')
  const [solved, setSolved] = useState([])
  const [bookmarks, setBookmarks] = useState([])
  const [hintsRevealed, setHintsRevealed] = useState(0)

  useEffect(() => {
    try {
      const storageKey = `dsa_code_${selectedLang}_${problemId}`
      const savedCode      = localStorage.getItem(storageKey)
      const savedSolved    = JSON.parse(localStorage.getItem('dsa_solved') || '[]')
      const savedBookmarks = JSON.parse(localStorage.getItem('dsa_bookmarks') || '[]')
      const savedHints     = parseInt(localStorage.getItem(`dsa_hints_${problemId}`) || '0')

      setSolved(savedSolved)
      setBookmarks(savedBookmarks)
      setHintsRevealed(savedHints)

      setCode(savedCode || defaultStarterCode)
    } catch {}
  }, [problemId, selectedLang, defaultStarterCode])

  const updateCode = useCallback((val) => {
    setCode(val)
    localStorage.setItem(`dsa_code_${selectedLang}_${problemId}`, val)
  }, [problemId, selectedLang])

  const markSolved = useCallback((id) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    const next = solved.includes(id) ? solved.filter(x => x !== id) : [...solved, id]
    setSolved(next)
    localStorage.setItem('dsa_solved', JSON.stringify(next))
  }, [solved, user, openAuthModal])

  const toggleBookmark = useCallback((id) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    const next = bookmarks.includes(id) ? bookmarks.filter(x => x !== id) : [...bookmarks, id]
    setBookmarks(next)
    localStorage.setItem('dsa_bookmarks', JSON.stringify(next))
  }, [bookmarks, user, openAuthModal])

  const revealHint = useCallback((level) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    setHintsRevealed(level)
    localStorage.setItem(`dsa_hints_${problemId}`, level.toString())
  }, [problemId, user, openAuthModal])

  const resetCode = useCallback(() => {
    setCode(defaultStarterCode)
    localStorage.removeItem(`dsa_code_${selectedLang}_${problemId}`)
  }, [problemId, selectedLang, defaultStarterCode])

  return { code, updateCode, solved, markSolved, bookmarks, toggleBookmark, hintsRevealed, revealHint, resetCode }
}

function MarkdownRenderer({ text, isLight = false }) {
  if (!text) return null
  const parts = text.split(/(`[^`]+`|\*\*[^*]+\*\*)/g)
  return (
    <span>
      {parts.map((part, i) => {
        if (part.startsWith('`') && part.endsWith('`'))
          return (
            <code key={i} className={`px-1.5 py-0.5 rounded text-[13px] font-mono border ${
              isLight ? 'bg-violet-100 border-violet-200 text-violet-800 font-semibold' : 'bg-violet-500/15 border-violet-500/20 text-violet-300'
            }`}>
              {part.slice(1, -1)}
            </code>
          )
        if (part.startsWith('**') && part.endsWith('**'))
          return <strong key={i} className={isLight ? 'text-slate-900 font-bold' : 'text-white font-semibold'}>{part.slice(2, -2)}</strong>
        return <span key={i}>{part}</span>
      })}
    </span>
  )
}

export default function DSASolver() {
  const { id } = useParams()
  const navigate = useNavigate()
  const [searchParams, setSearchParams] = useSearchParams()
  const { user, openAuthModal } = useAuth()
  const problemId = parseInt(id)

  const initialLang = searchParams.get('lang') || localStorage.getItem('dsa_lang') || 'c'
  const [selectedLang, setSelectedLang] = useState(initialLang)

  const problem      = dsaProblems.find(p => p.id === problemId)
  const problemIndex = dsaProblems.findIndex(p => p.id === problemId)
  const prevProblem  = problemIndex > 0 ? dsaProblems[problemIndex - 1] : null
  const nextProblem  = problemIndex < dsaProblems.length - 1 ? dsaProblems[problemIndex + 1] : null

  const interviewData = useMemo(() => getProblemInterviewData(problem), [problem])

  const defaultStarterCode = useMemo(() => {
    if (selectedLang === 'c') {
      return interviewData?.solution?.cStarterCode || getCSolution(problem)?.starterCode || getCSolution(problem)?.code || ''
    }
    if (selectedLang === 'java') {
      return interviewData?.solution?.javaStarterCode || interviewData?.solution?.javaCode || ''
    }
    return problem?.starterCode || ''
  }, [selectedLang, interviewData, problem])

  const { code, updateCode, solved, markSolved, bookmarks, toggleBookmark, hintsRevealed, revealHint, resetCode } = useProblemStorage(id, selectedLang, defaultStarterCode)

  const [activeTab, setActiveTab]       = useState('description')
  const [mobileTab, setMobileTab]       = useState('problem') // 'problem' | 'editor'
  const [questionLang, setQuestionLang] = useState('en') // 'en' | 'hi'
  const [editorHeight, setEditorHeight] = useState(60)
  const [justSolved, setJustSolved]     = useState(false)
  const [xpGained, setXpGained]         = useState(null)
  const [copied, setCopied]             = useState(false)
  const [solutionToast, setSolutionToast] = useState(false)
  const [theme, setTheme]               = useState(() => localStorage.getItem('dsa_theme') || 'dark')
  const [interviewMode, setInterviewMode] = useState(false)
  const [isPro, setIsPro]               = useState(() => getCachedProStatus(user?.email).isPro)
  const [showProModal, setShowProModal] = useState(false)
  const [activeApproachId, setActiveApproachId] = useState(null)
  const [approachToast, setApproachToast] = useState(null)

  const cApproaches = useMemo(() => {
    return getCSolutionApproaches(problem)
  }, [problem])

  const handleSelectApproach = (appr) => {
    setActiveApproachId(appr.id)
    updateCode(appr.code)
    setApproachToast(`Loaded ${appr.name} into Editor!`)
    setTimeout(() => setApproachToast(null), 2500)
  }

  const isFreeTier = problemId <= 6
  const isLocked = !isFreeTier && !isPro

  // Sync remote Pro subscription status
  useEffect(() => {
    if (user?.email) {
      fetchRemoteProStatus(user.email).then(status => {
        if (status?.isPro) setIsPro(true)
      })
    }
    const handleProUpdate = (e) => {
      if (e.detail?.isPro) setIsPro(true)
    }
    window.addEventListener('bittu_pro_updated', handleProUpdate)
    return () => window.removeEventListener('bittu_pro_updated', handleProUpdate)
  }, [user])

  const handleLanguageChange = (newLang) => {
    setSelectedLang(newLang)
    localStorage.setItem('dsa_lang', newLang)
    setSearchParams({ lang: newLang })
  }

  useEffect(() => {
    localStorage.setItem('dsa_theme', theme)
    if (theme === 'light') {
      document.documentElement.classList.add('light')
    } else {
      document.documentElement.classList.remove('light')
    }
  }, [theme])

  const isLight = theme === 'light'
  const isSolved    = solved.includes(problemId)
  const isBookmarked= bookmarks.includes(problemId)
  const diff        = problem ? (difficultyConfig[problem.difficulty] || difficultyConfig.Easy) : difficultyConfig.Easy

  const handleSuccess = useCallback(() => {
    if (!isSolved) {
      markSolved(problemId)
      const result = onProblemSolved(problem.difficulty)
      setXpGained(result.gained)
      setJustSolved(true)
      setTimeout(() => { setJustSolved(false); setXpGained(null) }, 3500)
    }
  }, [isSolved, markSolved, problemId, problem])

  const handleShare = useCallback(() => {
    const url = window.location.href
    navigator.clipboard.writeText(url).then(() => {
      setCopied(true)
      setTimeout(() => setCopied(false), 2000)
    }).catch(() => {
      // Fallback
      const el = document.createElement('input')
      el.value = url
      document.body.appendChild(el)
      el.select()
      document.execCommand('copy')
      document.body.removeChild(el)
      setCopied(true)
      setTimeout(() => setCopied(false), 2000)
    })
  }, [])

  const handleLoadCode = useCallback((solCode, codeLang) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    if (codeLang && codeLang !== selectedLang) {
      setSelectedLang(codeLang)
      localStorage.setItem('dsa_lang', codeLang)
    }
    updateCode(solCode)
    setSolutionToast(true)
    setTimeout(() => setSolutionToast(false), 3000)
    if (typeof window !== 'undefined' && window.innerWidth < 1024) {
      setMobileTab('editor')
    }
  }, [updateCode, user, openAuthModal, selectedLang])

  if (!problem) {
    return (
      <div className={`min-h-screen flex items-center justify-center ${isLight ? 'bg-[#F4F6FB] text-slate-900' : 'bg-[#020008] text-white'}`}>
        <div className="text-center">
          <Code2 size={40} className={`${isLight ? 'text-slate-300' : 'text-white/20'} mx-auto mb-4`} />
          <h2 className="text-xl font-bold mb-2">Problem not found</h2>
          <Link to="/dsa" className="text-violet-500 hover:text-violet-600 text-sm">← Back to problems</Link>
        </div>
      </div>
    )
  }

  return (
    <div className={`flex flex-col h-screen overflow-hidden transition-colors duration-300 ${
      isLight ? 'bg-[#F4F6FB] text-slate-900' : 'bg-[#020008] text-white'
    }`}>
      {/* ── Preview Mode Banner for Unauthenticated Users ── */}
      {!user && (
        <div className="bg-gradient-to-r from-violet-600 via-fuchsia-600 to-cyan-600 text-white px-4 py-2 flex items-center justify-between text-xs font-semibold shrink-0 shadow-md">
          <div className="flex items-center gap-2">
            <span className="bg-white/20 px-2 py-0.5 rounded text-[10px] font-mono font-bold uppercase tracking-wider">🔒 Preview Mode</span>
            <span>Sign up free to execute code, unlock interview hints, and save progress!</span>
          </div>
          <button
            onClick={() => openAuthModal('signup')}
            className="bg-white text-slate-950 hover:bg-white/90 px-3 py-1 rounded-lg text-xs font-bold shadow-sm transition-transform active:scale-95 cursor-pointer whitespace-nowrap"
          >
            Sign Up Free
          </button>
        </div>
      )}

      {/* ── Lifetime Pass Required Banner for Question #7+ ── */}
      {user && isLocked && (
        <div className="bg-gradient-to-r from-amber-600 via-orange-600 to-amber-700 text-white px-4 py-2 flex items-center justify-between text-xs font-semibold shrink-0 shadow-md">
          <div className="flex items-center gap-2 flex-wrap">
            <span className="bg-white/20 px-2 py-0.5 rounded text-[10px] font-mono font-bold uppercase tracking-wider">🔒 Q#{problem.id} Pro Tier</span>
            <span>Questions #1–6 are 100% Free! Unlock full Java & C tracks (554+ problems) with the ₹149 Lifetime Pass.</span>
          </div>
          <button
            onClick={() => setShowProModal(true)}
            className="bg-white text-slate-950 hover:bg-white/90 px-3 py-1 rounded-lg text-xs font-black uppercase tracking-wider shadow-sm transition-transform active:scale-95 cursor-pointer whitespace-nowrap flex items-center gap-1.5"
          >
            <Crown size={12} className="text-amber-600 fill-amber-600/20" />
            <span>Unlock (₹149)</span>
          </button>
        </div>
      )}

      {/* ── Top Bar ── */}
      <div className={`flex items-center justify-between gap-2 px-3 sm:px-4 py-2 sm:py-2.5 border-b shrink-0 ${
        isLight ? 'border-slate-200 bg-white/80' : 'border-white/8 bg-white/[0.02]'
      }`}>
        <div className="flex items-center gap-2 sm:gap-3 min-w-0 flex-1">
          <Link to="/dsa" className={`flex items-center gap-1 sm:gap-1.5 transition-colors text-xs sm:text-sm shrink-0 ${
            isLight ? 'text-slate-600 hover:text-slate-900 font-semibold' : 'text-white/40 hover:text-white/80'
          }`}>
            <ArrowLeft size={15} />
            <span className="hidden sm:inline">Problems</span>
          </Link>

          <span className={`hidden sm:inline ${isLight ? 'text-slate-300' : 'text-white/15'}`}>|</span>

          {/* Problem title & difficulty */}
          <div className="flex items-center gap-1.5 sm:gap-2 min-w-0">
            <span className={`text-xs sm:text-sm font-mono shrink-0 ${isLight ? 'text-slate-500 font-bold' : 'text-white/40'}`}>#{problem.id}</span>
            <h1 className={`text-xs sm:text-sm font-bold truncate max-w-[120px] sm:max-w-none ${isLight ? 'text-slate-950 font-black' : 'text-white/90'}`}>
              {problem.title}
            </h1>
            <span className={`hidden sm:inline-flex items-center gap-1 px-2 py-0.5 rounded-full text-[10px] font-bold border ${diff.bg} ${diff.border} ${diff.color} shrink-0`}>
              <span className={`w-1.5 h-1.5 rounded-full ${diff.dot}`} />
              {problem.difficulty}
            </span>
            <span className={`hidden md:inline-flex items-center gap-1 px-2 py-0.5 rounded-full text-[10px] border shrink-0 ${
              isLight ? 'bg-slate-100 border-slate-200 text-slate-600 font-medium' : 'bg-white/4 border-white/8 text-white/35'
            }`}>
              <Tag size={9} />
              {problem.pattern}
            </span>
          </div>
        </div>

        {/* ── Actions ── */}
        <div className="flex items-center gap-1 sm:gap-1.5 shrink-0 overflow-x-auto scrollbar-none py-0.5">

          {/* Language Selector: C / Java / Python */}
          <div className={`flex items-center p-0.5 rounded-lg border text-xs font-bold shrink-0 ${
            isLight ? 'bg-slate-100 border-slate-300' : 'bg-white/5 border-white/10'
          }`}>
            <button
              onClick={() => handleLanguageChange('c')}
              title="Switch to C Track (C11/C17/C23 Standard)"
              className={`flex items-center gap-1 px-2.5 py-1 rounded-md transition-all ${
                selectedLang === 'c'
                  ? 'bg-gradient-to-r from-cyan-500 to-blue-600 text-white shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
              }`}
            >
              <Terminal size={12} />
              <span>C</span>
            </button>
            <button
              onClick={() => handleLanguageChange('java')}
              title="Switch to Java 21 Track"
              className={`flex items-center gap-1 px-2.5 py-1 rounded-md transition-all ${
                selectedLang === 'java'
                  ? 'bg-gradient-to-r from-amber-500 to-orange-600 text-white shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
              }`}
            >
              <Coffee size={12} />
              <span>Java</span>
            </button>
            <button
              onClick={() => handleLanguageChange('python')}
              title="Switch to Python 3.11 Track"
              className={`flex items-center gap-1 px-2.5 py-1 rounded-md transition-all ${
                selectedLang === 'python'
                  ? 'bg-gradient-to-r from-emerald-500 to-teal-600 text-white shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
              }`}
            >
              <span>Python</span>
            </button>
          </div>

          {/* Theme Toggle Button */}
          <button
            onClick={() => setTheme(isLight ? 'dark' : 'light')}
            title={isLight ? "Switch to Dark Mode" : "Switch to Light Mode"}
            className={`flex items-center gap-1 px-2 py-1.5 rounded-lg border text-xs font-bold transition-all shrink-0 ${
              isLight
                ? 'bg-amber-50 border-amber-300 text-amber-900 hover:bg-amber-100 shadow-sm'
                : 'bg-white/5 border-white/10 text-white/70 hover:text-white'
            }`}
          >
            {isLight ? <Sun size={13} className="text-amber-600" /> : <Moon size={13} className="text-violet-400" />}
            <span className="hidden sm:inline text-[10px]">{isLight ? 'Light' : 'Dark'}</span>
          </button>

          {/* Interview Timer */}
          <InterviewTimer difficulty={problem.difficulty} isLight={isLight} />

          {/* Interview Mode Toggle */}
          <button
            onClick={() => {
              if (!user) {
                openAuthModal('signup')
                return
              }
              setInterviewMode(m => !m)
            }}
            title={interviewMode ? "Exit Interview Simulation" : "Start FAANG Interview Simulation"}
            className={`flex items-center gap-1.5 px-2 sm:px-2.5 py-1.5 rounded-lg border text-xs font-semibold transition-all ${
              interviewMode
                ? 'bg-amber-500/20 border-amber-500/40 text-amber-400 shadow-sm'
                : isLight
                ? 'bg-white border-slate-200 text-slate-600 hover:text-slate-900'
                : 'bg-white/4 border-white/10 text-white/50 hover:border-amber-500/30 hover:text-amber-300'
            }`}
          >
            <Building2 size={13} />
            <span className="hidden md:inline">{interviewMode ? 'Interview Mode' : 'Mock Mode'}</span>
          </button>

          {/* Mark Solved */}
          <button
            onClick={() => markSolved(problemId)}
            title={isSolved ? 'Mark as unsolved' : 'Mark as solved'}
            className={`flex items-center gap-1 sm:gap-1.5 px-2 sm:px-2.5 py-1.5 rounded-lg border text-xs font-medium transition-all ${
              isSolved
                ? 'bg-emerald-500/15 border-emerald-500/30 text-emerald-400 hover:bg-emerald-500/25'
                : isLight ? 'bg-white border-slate-200 text-slate-500 hover:text-emerald-600' : 'bg-white/4 border-white/10 text-white/40 hover:border-emerald-500/30 hover:text-emerald-400/70'
            }`}
          >
            {isSolved ? <CheckCircle2 size={13} /> : <Circle size={13} />}
            <span className="hidden sm:inline">{isSolved ? 'Solved' : 'Mark Solved'}</span>
          </button>

          {/* Share */}
          <button
            onClick={handleShare}
            title="Copy problem link"
            className={`p-1.5 rounded-lg border transition-all ${
              copied
                ? 'bg-emerald-500/15 border-emerald-500/30 text-emerald-400'
                : isLight ? 'bg-white border-slate-200 text-slate-500 hover:text-slate-800' : 'bg-white/4 border-white/10 text-white/30 hover:border-violet-500/30 hover:text-violet-400'
            }`}
          >
            {copied ? <Check size={14} /> : <Share2 size={14} />}
          </button>

          {/* Bookmark */}
          <button
            onClick={() => toggleBookmark(problemId)}
            title={isBookmarked ? "Remove Bookmark" : "Save Problem"}
            className={`p-1.5 rounded-lg border transition-all ${
              isBookmarked
                ? 'bg-violet-500/15 border-violet-500/30 text-violet-400'
                : isLight ? 'bg-white border-slate-200 text-slate-500 hover:text-slate-800' : 'bg-white/4 border-white/10 text-white/30 hover:border-violet-500/30'
            }`}
          >
            {isBookmarked ? <BookmarkCheck size={14} /> : <Bookmark size={14} />}
          </button>

          {/* Reset */}
          <button
            onClick={resetCode}
            title="Reset to starter code"
            className={`p-1.5 rounded-lg border transition-all ${
              isLight ? 'bg-white border-slate-200 text-slate-500 hover:text-slate-800' : 'bg-white/4 border-white/10 text-white/30 hover:text-white/60 hover:border-white/20'
            }`}
          >
            <RotateCcw size={14} />
          </button>

          {/* Prev / Next */}
          <div className={`flex items-center border rounded-lg overflow-hidden ${
            isLight ? 'border-slate-200 bg-white' : 'border-white/8'
          }`}>
            <button
              onClick={() => prevProblem && navigate(`/dsa/${prevProblem.id}?lang=${selectedLang}`)}
              disabled={!prevProblem}
              title="Previous Problem"
              className={`p-1.5 border-r transition-all disabled:opacity-20 disabled:cursor-not-allowed ${
                isLight ? 'text-slate-500 hover:text-slate-900 border-slate-200' : 'text-white/30 hover:text-white/60 hover:bg-white/5 border-white/8'
              }`}
            >
              <ChevronLeft size={15} />
            </button>
            <button
              onClick={() => nextProblem && navigate(`/dsa/${nextProblem.id}?lang=${selectedLang}`)}
              disabled={!nextProblem}
              title="Next Problem"
              className={`p-1.5 transition-all disabled:opacity-20 disabled:cursor-not-allowed ${
                isLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/30 hover:text-white/60 hover:bg-white/5'
              }`}
            >
              <ChevronRight size={15} />
            </button>
          </div>

          {/* Lifetime Pass Button */}
          {!isPro ? (
            <button
              onClick={() => setShowProModal(true)}
              className="flex items-center gap-1.5 px-2.5 py-1.5 rounded-lg text-xs font-bold bg-gradient-to-r from-amber-500 via-orange-500 to-amber-600 text-white shadow-sm hover:opacity-95 active:scale-95 transition-all shrink-0 cursor-pointer"
              title="Unlock All 554+ Java & C DSA Problems for ₹149 Lifetime"
            >
              <Crown size={12} className="fill-white/20" />
              <span className="hidden sm:inline">Pass (₹149)</span>
            </button>
          ) : (
            <div className="flex items-center gap-1 px-2.5 py-1 rounded-lg text-xs font-bold bg-amber-500/15 border border-amber-400/30 text-amber-500 shrink-0">
              <Crown size={12} className="text-amber-500 fill-amber-500/20" />
              <span className="hidden sm:inline text-[11px]">PRO</span>
            </div>
          )}

          {/* User Nav */}
          <UserNav isLight={isLight} />
        </div>
      </div>

      {/* ── Solved / XP Banner ── */}
      {justSolved && (
        <div className="shrink-0 bg-gradient-to-r from-emerald-500/20 via-emerald-500/15 to-violet-500/20 border-b border-emerald-500/25 px-4 py-2.5 flex items-center gap-3 animate-fadeIn">
          <Trophy size={16} className="text-yellow-400" />
          <p className="text-emerald-300 text-sm font-medium flex-1">
            🎉 Excellent! Problem solved!
          </p>
          {xpGained && (
            <span className="flex items-center gap-1 px-3 py-1 rounded-full bg-violet-500/20 border border-violet-500/30 text-violet-300 text-xs font-bold">
              <Zap size={12} className="text-violet-400" />
              +{xpGained} XP
            </span>
          )}
        </div>
      )}

      {/* ── Copied Toast ── */}
      {copied && (
        <div className="shrink-0 bg-violet-500/15 border-b border-violet-500/25 px-4 py-2 flex items-center gap-2 animate-fadeIn">
          <Check size={13} className="text-emerald-400" />
          <p className="text-white/70 text-xs">Problem link copied to clipboard!</p>
        </div>
      )}

      {/* ── Solution Code Loaded Toast ── */}
      {solutionToast && (
        <div className="shrink-0 bg-emerald-500/15 border-b border-emerald-500/30 px-4 py-2 flex items-center gap-2 animate-fadeIn">
          <CheckCircle2 size={14} className="text-emerald-500" />
          <p className={`text-xs font-semibold ${isLight ? 'text-emerald-900' : 'text-emerald-300'}`}>
            Official solution code has been loaded into the editor!
          </p>
        </div>
      )}

      {/* ── Mobile View Switcher (Visible on < lg screens) ── */}
      <div className={`lg:hidden flex border-b shrink-0 ${
        isLight ? 'bg-slate-100 border-slate-200' : 'bg-[#080214] border-white/8'
      }`}>
        <button
          onClick={() => setMobileTab('problem')}
          className={`flex-1 flex items-center justify-center gap-2 py-2.5 text-xs font-bold border-b-2 transition-all ${
            mobileTab === 'problem'
              ? isLight
                ? 'border-violet-600 text-violet-700 bg-white shadow-sm'
                : 'border-violet-500 text-violet-300 bg-violet-500/10'
              : isLight
              ? 'border-transparent text-slate-500 hover:text-slate-800'
              : 'border-transparent text-white/40 hover:text-white'
          }`}
        >
          <BookOpen size={14} />
          <span>Problem & Solution</span>
          {isSolved && <span className="w-1.5 h-1.5 rounded-full bg-emerald-500" />}
        </button>

        <button
          onClick={() => setMobileTab('editor')}
          className={`flex-1 flex items-center justify-center gap-2 py-2.5 text-xs font-bold border-b-2 transition-all ${
            mobileTab === 'editor'
              ? isLight
                ? 'border-cyan-600 text-cyan-700 bg-white shadow-sm'
                : 'border-cyan-500 text-cyan-300 bg-cyan-500/10'
              : isLight
              ? 'border-transparent text-slate-500 hover:text-slate-800'
              : 'border-transparent text-white/40 hover:text-white'
          }`}
        >
          <Code2 size={14} />
          <span>Code & Console</span>
          <span className="text-[10px] font-mono px-1.5 py-0.2 rounded bg-violet-500/20 text-violet-300">
            Python
          </span>
        </button>
      </div>

      {/* ── Main Split Layout ── */}
      <div className="flex flex-1 min-h-0 overflow-hidden">

        {/* LEFT: Problem Description & Solutions */}
        <div className={`${
          mobileTab === 'problem' ? 'flex' : 'hidden'
        } lg:flex w-full lg:w-[45%] xl:w-[42%] flex-col border-r min-h-0 overflow-hidden ${
          isLight ? 'border-slate-200 bg-white' : 'border-white/8 bg-[#020008]'
        }`}>
          {/* Tabs */}
          <div className={`flex border-b shrink-0 items-center justify-between px-2 overflow-x-auto scrollbar-none ${
            isLight ? 'border-slate-200 bg-slate-50' : 'border-white/8 bg-white/[0.015]'
          }`}>
            <div className="flex items-center shrink-0">
              {[
                { id: 'description', icon: <BookOpen size={12} />, label: 'Problem / प्रश्न' },
                { id: 'hints',       icon: <Lightbulb size={12} />, label: `Hints (${problem.hints?.length || 0})` },
                { id: 'solution',    icon: <Unlock size={12} />, label: 'Solution / समाधान' },
                { id: 'diff',        icon: <ArrowRightLeft size={12} />, label: 'Code Diff / तुलना' },
              ].map(tab => (
                <button
                  key={tab.id}
                  onClick={() => setActiveTab(tab.id)}
                  className={`flex items-center gap-1.5 px-3 sm:px-3.5 py-2.5 text-xs font-semibold border-b-2 whitespace-nowrap transition-all ${
                    activeTab === tab.id
                      ? isLight
                        ? 'border-violet-600 text-violet-700 bg-white shadow-sm'
                        : 'border-violet-500 text-violet-300 bg-violet-500/5'
                      : isLight
                      ? 'border-transparent text-slate-500 hover:text-slate-900'
                      : 'border-transparent text-white/40 hover:text-white/70'
                  }`}
                >
                  {tab.icon}
                  {tab.label}
                </button>
              ))}
            </div>

            {/* Bilingual English / Hindi Switcher for Question */}
            {activeTab === 'description' && (
              <div className={`flex items-center p-0.5 rounded-lg border text-[11px] font-semibold ${
                isLight ? 'bg-white border-slate-300' : 'bg-white/5 border-white/10'
              }`}>
                <button
                  onClick={() => setQuestionLang('en')}
                  className={`px-2 py-0.5 rounded transition-all ${
                    questionLang === 'en'
                      ? 'bg-violet-600 text-white font-bold shadow-sm'
                      : isLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/40 hover:text-white'
                  }`}
                >
                  English
                </button>
                <button
                  onClick={() => setQuestionLang('hi')}
                  className={`px-2 py-0.5 rounded transition-all ${
                    questionLang === 'hi'
                      ? 'bg-amber-500 text-slate-950 font-bold shadow-sm'
                      : isLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/40 hover:text-white'
                  }`}
                >
                  हिंदी
                </button>
              </div>
            )}
          </div>

          {/* Tab Content */}
          <div className="flex-1 overflow-y-auto px-5 py-4">
            {activeTab === 'description' && (
              <div className="space-y-4">

                {/* ── Problem Title & Exam/Interview Header ── */}
                <div className={`p-4 rounded-xl border ${
                  isLight
                    ? 'bg-gradient-to-br from-violet-50 via-white to-cyan-50 border-violet-200/80 shadow-sm'
                    : 'bg-gradient-to-br from-violet-950/20 via-black/40 to-cyan-950/20 border-violet-500/25'
                }`}>
                  <div className="flex items-center gap-2 mb-1.5 flex-wrap">
                    <span className={`px-2 py-0.5 rounded text-[11px] font-mono font-bold border ${
                      isLight ? 'bg-violet-100 border-violet-200 text-violet-800' : 'bg-violet-500/20 border-violet-500/30 text-violet-300'
                    }`}>
                      Question #{problem.id}
                    </span>
                    <span className={`px-2 py-0.5 rounded text-[11px] font-bold border ${diff.bg} ${diff.border} ${diff.color}`}>
                      {problem.difficulty}
                    </span>
                    <span className={`px-2 py-0.5 rounded text-[11px] font-medium border ${
                      isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/5 border-white/10 text-white/50'
                    }`}>
                      {problem.topic}
                    </span>
                  </div>

                  <h2 className={`text-lg font-bold tracking-tight mb-2 ${
                    isLight ? 'text-slate-950' : 'text-white'
                  }`}>
                    {questionLang === 'hi' ? interviewData?.hi?.title || problem.title : problem.title}
                  </h2>

                  {/* Real Interview & Exam Context */}
                  <div className={`p-2.5 rounded-lg border text-xs flex flex-col gap-1 ${
                    isLight
                      ? 'bg-amber-50/70 border-amber-200 text-amber-950'
                      : 'bg-amber-500/5 border-amber-500/20 text-amber-300/90'
                  }`}>
                    <div className="flex items-center gap-1.5 font-bold">
                      <Building2 size={13} className="text-amber-500 shrink-0" />
                      <span>Asked in Top Tech Interviews:</span>
                      <span className="font-mono font-semibold">
                        {interviewData?.companies?.join(', ')}
                      </span>
                    </div>
                    <p className={`text-[11px] leading-relaxed ${isLight ? 'text-amber-900/80' : 'text-amber-300/70'}`}>
                      {questionLang === 'hi'
                        ? '💡 Interview Tip: Code likhne se pehle interviewer se constraints aur edge cases zaroor confirm karein.'
                        : '💡 Interview Tip: Always discuss the brute force first, then explain why the optimal approach saves time.'
                      }
                    </p>
                  </div>
                </div>

                {/* ── Problem Statement (English or Hindi) ── */}
                <div className={`p-4 rounded-xl border ${
                  isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.02] border-white/8'
                }`}>
                  <h3 className={`text-xs font-bold uppercase tracking-wider mb-2.5 ${
                    isLight ? 'text-violet-700' : 'text-violet-400'
                  }`}>
                    {questionLang === 'hi' ? '📝 प्रश्न विवरण (Problem Statement)' : '📝 Problem Statement'}
                  </h3>

                  {questionLang === 'hi' ? (
                    <div className={`text-sm leading-relaxed space-y-3 ${isLight ? 'text-slate-800' : 'text-white/80'}`}>
                      <p className="whitespace-pre-wrap">{interviewData?.hi?.statement}</p>
                      {interviewData?.hi?.objective && (
                        <div className={`p-2.5 rounded-lg border text-xs ${
                          isLight ? 'bg-slate-50 border-slate-200 text-slate-700' : 'bg-white/4 border-white/8 text-white/70'
                        }`}>
                          <span className="font-bold text-violet-600 dark:text-violet-400">🎯 लक्ष्य (Objective): </span>
                          <span>{interviewData?.hi?.objective}</span>
                        </div>
                      )}
                    </div>
                  ) : (
                    <div className={`text-sm leading-relaxed whitespace-pre-wrap ${
                      isLight ? 'text-slate-800' : 'text-white/75'
                    }`}>
                      {problem.description.split('\n').map((line, i) => (
                        <React.Fragment key={i}>
                          <MarkdownRenderer text={line} isLight={isLight} />
                          {i < problem.description.split('\n').length - 1 && <br />}
                        </React.Fragment>
                      ))}
                    </div>
                  )}
                </div>

                {problem.examples?.length > 0 && (
                  <div>
                    <h3 className={`text-xs font-bold uppercase tracking-wider mb-2.5 ${
                      isLight ? 'text-slate-700' : 'text-white/50'
                    }`}>
                      {questionLang === 'hi' ? 'उदहारण (Examples)' : 'Examples'}
                    </h3>
                    <div className="space-y-3">
                      {problem.examples.map((ex, i) => (
                        <div key={i} className={`border rounded-xl p-3.5 font-mono text-xs ${
                          isLight ? 'bg-slate-50/80 border-slate-200 text-slate-800 shadow-sm' : 'bg-white/3 border-white/8 text-white'
                        }`}>
                          <div className="space-y-1.5">
                            <div><span className={isLight ? 'text-slate-500 font-semibold' : 'text-white/30'}>Input: </span><span className={isLight ? 'text-cyan-700 font-bold' : 'text-cyan-300'}>{ex.input}</span></div>
                            <div><span className={isLight ? 'text-slate-500 font-semibold' : 'text-white/30'}>Output: </span><span className={isLight ? 'text-emerald-700 font-bold' : 'text-emerald-300'}>{ex.output}</span></div>
                            {ex.explanation && <div><span className={isLight ? 'text-slate-500 font-semibold' : 'text-white/30'}>Explanation: </span><span className={isLight ? 'text-slate-600' : 'text-white/55'}>{ex.explanation}</span></div>}
                          </div>
                        </div>
                      ))}
                    </div>
                  </div>
                )}

                {problem.constraints?.length > 0 && (
                  <div>
                    <h3 className={`text-xs font-bold uppercase tracking-wider mb-2.5 ${
                      isLight ? 'text-slate-700' : 'text-white/50'
                    }`}>
                      {questionLang === 'hi' ? 'प्रतिबंध (Constraints)' : 'Constraints'}
                    </h3>
                    <ul className="space-y-1.5">
                      {problem.constraints.map((c, i) => (
                        <li key={i} className={`flex items-start gap-2 text-xs font-mono ${
                          isLight ? 'text-slate-700 font-medium' : 'text-white/50'
                        }`}>
                          <span className="text-violet-500 mt-0.5 shrink-0 font-bold">•</span>{c}
                        </li>
                      ))}
                    </ul>
                  </div>
                )}

                <div className={`flex flex-wrap gap-2 pt-2 border-t ${
                  isLight ? 'border-slate-200' : 'border-white/5'
                }`}>
                  <span className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-[11px] font-medium border ${
                    isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/4 border-white/8 text-white/40'
                  }`}>
                    <Tag size={10} className={isLight ? 'text-violet-600' : 'text-violet-400'} />{problem.pattern}
                  </span>
                  <span className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-[11px] font-medium border ${
                    isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/4 border-white/8 text-white/40'
                  }`}>
                    <Code2 size={10} className={isLight ? 'text-cyan-600' : 'text-cyan-400'} />{problem.topic}
                  </span>
                  {problem.timeComplexity && (
                    <span className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-[11px] font-mono font-medium border ${
                      isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/4 border-white/8 text-white/40'
                    }`}>
                      <Clock size={10} className={isLight ? 'text-amber-600' : 'text-amber-400'} />{problem.timeComplexity}
                    </span>
                  )}
                  <span className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-[11px] font-mono font-bold border ${
                    isLight ? 'bg-violet-100 border-violet-200 text-violet-800' : 'bg-violet-500/10 border-violet-500/20 text-violet-300'
                  }`}>
                    <Zap size={10} className={isLight ? 'text-violet-600' : 'text-violet-400'} />
                    +{XP_MAP[problem.difficulty] || 10} XP
                  </span>
                </div>

                {/* Mobile Quick Action to Switch to Editor */}
                <div className="lg:hidden pt-3 pb-1">
                  <button
                    onClick={() => setMobileTab('editor')}
                    className="w-full py-2.5 px-4 rounded-xl font-bold text-xs bg-gradient-to-r from-violet-600 to-cyan-600 text-white shadow-lg shadow-violet-500/25 flex items-center justify-center gap-2 active:scale-[0.98] transition-all"
                  >
                    <Code2 size={15} />
                    <span>Open Code Editor & Run Tests</span>
                    <ChevronRight size={15} />
                  </button>
                </div>
              </div>
            )}

            {interviewMode && activeTab !== 'description' ? (
              <div className={`p-8 rounded-2xl border text-center transition-all ${
                isLight ? 'bg-amber-50/70 border-amber-200 text-slate-800' : 'bg-amber-500/5 border-amber-500/20 text-white'
              }`}>
                <div className={`w-14 h-14 rounded-2xl mx-auto mb-4 flex items-center justify-center border shadow-lg ${
                  isLight ? 'bg-amber-100 border-amber-300 text-amber-600' : 'bg-amber-500/20 border-amber-500/30 text-amber-400'
                }`}>
                  <Building2 size={26} />
                </div>
                <h3 className="text-base font-bold mb-2">
                  Technical Interview Simulation Active
                </h3>
                <p className={`text-xs leading-relaxed max-w-md mx-auto mb-6 ${
                  isLight ? 'text-slate-600' : 'text-white/60'
                }`}>
                  In a real technical interview round at Google / Amazon / Microsoft, external hints, solutions, and diff tools are strictly unavailable. Rely on your algorithmic reasoning, write code, and run test cases on the right!
                </p>
                <button
                  onClick={() => setInterviewMode(false)}
                  className="px-4 py-2 rounded-xl text-xs font-bold bg-amber-500 text-slate-950 hover:bg-amber-400 transition-all shadow-md shadow-amber-500/20"
                >
                  Exit Interview Simulation Mode
                </button>
              </div>
            ) : isLocked && activeTab !== 'description' ? (
              <div className={`p-6 sm:p-8 rounded-2xl border text-center transition-all ${
                isLight ? 'bg-amber-50/70 border-amber-200 text-slate-800' : 'bg-amber-500/5 border-amber-500/20 text-white'
              }`}>
                <div className={`w-14 h-14 rounded-2xl mx-auto mb-4 flex items-center justify-center border shadow-lg ${
                  isLight ? 'bg-amber-100 border-amber-300 text-amber-600' : 'bg-amber-500/20 border-amber-500/30 text-amber-400'
                }`}>
                  <Lock size={26} />
                </div>
                <div className="inline-flex items-center gap-1 px-2.5 py-0.5 rounded-full text-[11px] font-bold bg-amber-500/15 text-amber-600 dark:text-amber-400 border border-amber-500/30 mb-2">
                  Questions #1 to #6 are Free · Q#{problem.id} is Locked
                </div>
                <h3 className="text-base font-extrabold mb-2 text-slate-900 dark:text-white">
                  Unlock Official Editorial & Optimal Solutions
                </h3>
                <p className={`text-xs leading-relaxed max-w-md mx-auto mb-6 ${
                  isLight ? 'text-slate-600' : 'text-white/60'
                }`}>
                  Get lifetime access to complete Java & C optimal solutions, Hindi explanations, visual code diffs, and interview walkthroughs for all 554+ problems.
                </p>
                <button
                  type="button"
                  onClick={() => setShowProModal(true)}
                  className="px-6 py-2.5 rounded-xl text-xs font-black uppercase tracking-wider bg-gradient-to-r from-amber-500 via-orange-500 to-amber-600 text-white shadow-lg shadow-amber-500/30 hover:opacity-95 active:scale-95 transition-all inline-flex items-center gap-2 cursor-pointer"
                >
                  <Crown size={15} className="fill-white/20" />
                  <span>Unlock Both Tracks for ₹149 (Lifetime)</span>
                </button>
              </div>
            ) : (
              <>
                {activeTab === 'hints' && (
                  <HintPanel
                    problem={problem}
                    hintsRevealed={hintsRevealed}
                    onRevealHint={revealHint}
                    isLight={isLight}
                  />
                )}

                {activeTab === 'solution' && (
                  <SolutionPanel
                    problem={problem}
                    interviewData={interviewData}
                    isLight={isLight}
                    onLoadCodeIntoEditor={handleLoadCode}
                    userCode={code}
                    activeLang={selectedLang}
                  />
                )}

                {activeTab === 'diff' && (
                  <div className="space-y-4">
                    <div className={`p-3.5 rounded-xl border flex items-center justify-between ${
                      isLight
                        ? 'bg-gradient-to-r from-violet-50 to-cyan-50 border-violet-200 shadow-sm'
                        : 'bg-gradient-to-r from-violet-500/10 to-cyan-500/10 border-violet-500/20'
                    }`}>
                      <div className="flex items-center gap-2.5">
                        <div className={`p-2 rounded-lg ${
                          isLight ? 'bg-violet-100 text-violet-800' : 'bg-violet-500/20 text-violet-300'
                        }`}>
                          <ArrowRightLeft size={16} />
                        </div>
                        <div>
                          <h4 className={`text-xs font-bold ${isLight ? 'text-violet-950' : 'text-violet-200'}`}>
                            Visual Code Diff Viewer (अंतर तुलना)
                          </h4>
                          <p className={`text-[11px] ${isLight ? 'text-violet-700' : 'text-violet-300/70'}`}>
                            Comparing your workspace code against the optimal {problem.pattern} solution
                          </p>
                        </div>
                      </div>
                    </div>

                    <CodeDiffViewer
                      original={code}
                      modified={interviewData?.solution?.code || problem.starterCode}
                      isLight={isLight}
                      onLoadCodeIntoEditor={handleLoadCode}
                    />
                  </div>
                )}
              </>
            )}
          </div>
        </div>

        {/* RIGHT: Editor + Console */}
        <div className={`${
          mobileTab === 'editor' ? 'flex' : 'hidden'
        } lg:flex flex-1 flex-col min-h-0 overflow-hidden`}>
          {/* Editor header */}
          <div className="relative flex items-center justify-between px-3 md:px-4 py-2 border-b border-white/8 bg-white/[0.015] shrink-0 gap-2">
            <div className="flex items-center gap-2 shrink-0">
              <div className="flex gap-1.5">
                <span className="w-3 h-3 rounded-full bg-red-500/60" />
                <span className="w-3 h-3 rounded-full bg-yellow-500/60" />
                <span className="w-3 h-3 rounded-full bg-emerald-500/60" />
              </div>
              <span className={`text-xs font-mono font-semibold ml-1 flex items-center gap-1 ${
                selectedLang === 'c' ? 'text-cyan-400' : (selectedLang === 'java' ? 'text-amber-400' : 'text-emerald-400')
              }`}>
                {selectedLang === 'java' ? <Coffee size={12} /> : (selectedLang === 'c' ? <Terminal size={12} /> : null)}
                {selectedLang === 'c' ? 'solution.c' : (selectedLang === 'java' ? 'Solution.java' : 'solution.py')}
              </span>
            </div>

            {/* Middle: Multiple Solution Ways Buttons */}
            {selectedLang === 'c' && cApproaches.length > 0 && (
              <div className="flex items-center gap-1.5 overflow-x-auto no-scrollbar py-0.5 max-w-full">
                <span className="text-[11px] font-semibold text-white/40 hidden xl:inline-flex items-center gap-1 mr-0.5 shrink-0">
                  <Sparkles size={11} className="text-cyan-400" />
                  Ways:
                </span>
                {cApproaches.map((appr, idx) => {
                  const isActive = activeApproachId === appr.id
                  return (
                    <button
                      key={appr.id || idx}
                      onClick={() => handleSelectApproach(appr)}
                      title={`Click to load ${appr.name}: ${appr.description} (${appr.timeComplexity})`}
                      className={`group flex items-center gap-1.5 px-2.5 py-1 rounded-lg text-xs font-semibold transition-all shrink-0 border ${
                        isActive
                          ? 'bg-gradient-to-r from-cyan-500/30 to-blue-600/30 text-cyan-300 border-cyan-400/60 shadow-sm shadow-cyan-500/25 ring-1 ring-cyan-400/30'
                          : isLight
                          ? 'bg-white hover:bg-slate-100 text-slate-700 border-slate-300 hover:border-slate-400'
                          : 'bg-white/[0.04] hover:bg-white/[0.09] text-white/75 hover:text-white border-white/10 hover:border-white/20'
                      }`}
                    >
                      <span className="font-mono text-[11px]">{appr.name}</span>
                      <span className={`text-[9px] px-1.5 py-0.2 rounded font-sans uppercase tracking-wider font-bold ${
                        isActive ? 'bg-cyan-400/25 text-cyan-200' : 'bg-white/10 text-white/50'
                      }`}>
                        {appr.badge || appr.timeComplexity}
                      </span>
                    </button>
                  )
                })}
              </div>
            )}

            <div className="flex items-center gap-2 shrink-0">
              <span className="text-white/40 text-xs font-mono font-medium hidden sm:inline">
                {selectedLang === 'c' ? '⚡ C11 / C17 · GCC Ready' : (selectedLang === 'java' ? '☕ Java 21 · SE' : '🐍 Python 3.11 · Pyodide')}
              </span>
            </div>

            {/* Quick Toast when Approach is loaded */}
            {approachToast && (
              <div className="absolute top-11 left-1/2 -translate-x-1/2 z-30 flex items-center gap-2 px-3 py-1.5 bg-cyan-950/95 text-cyan-200 border border-cyan-400/50 rounded-lg text-xs shadow-xl backdrop-blur-md animate-fadeIn">
                <Check size={13} className="text-cyan-400" />
                <span className="font-semibold">{approachToast}</span>
              </div>
            )}
          </div>

          {/* Editor */}
          <div className="flex-1 min-h-0" style={{ flex: editorHeight }}>
            <CodeEditor language={selectedLang} value={code} onChange={updateCode} isLight={isLight} />
          </div>

          {/* Drag handle */}
          <div
            className={`h-1 cursor-row-resize transition-colors shrink-0 flex items-center justify-center ${
              isLight ? 'bg-slate-200 hover:bg-violet-200 border-y border-slate-300' : 'bg-white/5 border-y border-white/8 hover:bg-violet-500/20'
            }`}
            onMouseDown={(e) => {
              const startY = e.clientY
              const startH = editorHeight
              const onMove = (me) => {
                const delta = me.clientY - startY
                setEditorHeight(Math.max(20, Math.min(85, startH + delta * 0.1)))
              }
              const onUp = () => {
                window.removeEventListener('mousemove', onMove)
                window.removeEventListener('mouseup', onUp)
              }
              window.addEventListener('mousemove', onMove)
              window.addEventListener('mouseup', onUp)
            }}
          >
            <div className="flex gap-1"><span className={`w-6 h-0.5 rounded-full ${isLight ? 'bg-slate-400' : 'bg-white/20'}`} /></div>
          </div>

          {/* Console / Test Runner */}
          <div className="min-h-0" style={{ flex: 100 - editorHeight }}>
            <TestRunner language={selectedLang} problem={problem} code={code} onSuccess={handleSuccess} isLight={isLight} />
          </div>
        </div>
      </div>

      {/* ── ₹149 DSA Master Lifetime Pass Modal ── */}
      <ProPaymentModal
        isOpen={showProModal}
        onClose={() => setShowProModal(false)}
        onSuccess={() => setIsPro(true)}
        isLight={isLight}
      />
    </div>
  )
}

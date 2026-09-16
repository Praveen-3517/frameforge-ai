import React, { useState, useEffect, useCallback, useMemo } from 'react'
import { Link, useParams, useNavigate } from 'react-router-dom'
import {
  ArrowLeft, ChevronLeft, ChevronRight, Code2, BookOpen,
  Lightbulb, CheckCircle2, Circle, Bookmark, BookmarkCheck,
  RotateCcw, Tag, Clock, Play, Trophy, Zap, Share2, Check,
  Sun, Moon, Unlock, Building2, Sparkles, HelpCircle, Languages,
  ArrowRightLeft
} from 'lucide-react'
import CodeEditor from '../components/dsa/CodeEditor'
import TestRunner from '../components/dsa/TestRunner'
import HintPanel from '../components/dsa/HintPanel'
import SolutionPanel from '../components/dsa/SolutionPanel'
import CodeDiffViewer from '../components/dsa/CodeDiffViewer'
import InterviewTimer from '../components/dsa/InterviewTimer'
import { dsaProblems } from '../data/dsaProblems'
import { onProblemSolved, XP_MAP } from '../utils/dsaStats'
import { getProblemInterviewData } from '../data/dsaInterviewSolutions'

const difficultyConfig = {
  Easy:   { color: 'text-emerald-400', bg: 'bg-emerald-500/10', border: 'border-emerald-500/25', dot: 'bg-emerald-400' },
  Medium: { color: 'text-amber-400',   bg: 'bg-amber-500/10',   border: 'border-amber-500/25',   dot: 'bg-amber-400' },
  Hard:   { color: 'text-red-400',     bg: 'bg-red-500/10',     border: 'border-red-500/25',     dot: 'bg-red-400' },
}

function useProblemStorage(problemId) {
  const [code, setCode] = useState('')
  const [solved, setSolved] = useState([])
  const [bookmarks, setBookmarks] = useState([])
  const [hintsRevealed, setHintsRevealed] = useState(0)

  useEffect(() => {
    try {
      const savedCode      = localStorage.getItem(`dsa_code_${problemId}`)
      const savedSolved    = JSON.parse(localStorage.getItem('dsa_solved') || '[]')
      const savedBookmarks = JSON.parse(localStorage.getItem('dsa_bookmarks') || '[]')
      const savedHints     = parseInt(localStorage.getItem(`dsa_hints_${problemId}`) || '0')

      setSolved(savedSolved)
      setBookmarks(savedBookmarks)
      setHintsRevealed(savedHints)

      const problem = dsaProblems.find(p => p.id === parseInt(problemId))
      if (problem) setCode(savedCode || problem.starterCode)
    } catch {}
  }, [problemId])

  const updateCode = useCallback((val) => {
    setCode(val)
    localStorage.setItem(`dsa_code_${problemId}`, val)
  }, [problemId])

  const markSolved = useCallback((id) => {
    const next = solved.includes(id) ? solved.filter(x => x !== id) : [...solved, id]
    setSolved(next)
    localStorage.setItem('dsa_solved', JSON.stringify(next))
  }, [solved])

  const toggleBookmark = useCallback((id) => {
    const next = bookmarks.includes(id) ? bookmarks.filter(x => x !== id) : [...bookmarks, id]
    setBookmarks(next)
    localStorage.setItem('dsa_bookmarks', JSON.stringify(next))
  }, [bookmarks])

  const revealHint = useCallback((level) => {
    setHintsRevealed(level)
    localStorage.setItem(`dsa_hints_${problemId}`, level.toString())
  }, [problemId])

  const resetCode = useCallback(() => {
    const problem = dsaProblems.find(p => p.id === parseInt(problemId))
    if (problem) {
      setCode(problem.starterCode)
      localStorage.removeItem(`dsa_code_${problemId}`)
    }
  }, [problemId])

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
  const problemId = parseInt(id)

  const problem      = dsaProblems.find(p => p.id === problemId)
  const problemIndex = dsaProblems.findIndex(p => p.id === problemId)
  const prevProblem  = problemIndex > 0 ? dsaProblems[problemIndex - 1] : null
  const nextProblem  = problemIndex < dsaProblems.length - 1 ? dsaProblems[problemIndex + 1] : null

  const { code, updateCode, solved, markSolved, bookmarks, toggleBookmark, hintsRevealed, revealHint, resetCode } = useProblemStorage(id)

  const [activeTab, setActiveTab]       = useState('description')
  const [questionLang, setQuestionLang] = useState('en') // 'en' | 'hi'
  const [editorHeight, setEditorHeight] = useState(60)
  const [justSolved, setJustSolved]     = useState(false)
  const [xpGained, setXpGained]         = useState(null)
  const [copied, setCopied]             = useState(false)
  const [solutionToast, setSolutionToast] = useState(false)
  const [theme, setTheme]               = useState(() => localStorage.getItem('dsa_theme') || 'dark')
  const [interviewMode, setInterviewMode] = useState(false)

  const interviewData = useMemo(() => getProblemInterviewData(problem), [problem])

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

  const handleLoadCode = useCallback((solCode) => {
    updateCode(solCode)
    setSolutionToast(true)
    setTimeout(() => setSolutionToast(false), 3000)
  }, [updateCode])

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

      {/* ── Top Bar ── */}
      <div className={`flex items-center gap-3 px-4 py-2.5 border-b shrink-0 ${
        isLight ? 'border-slate-200 bg-white/80' : 'border-white/8 bg-white/[0.02]'
      }`}>
        <Link to="/dsa" className={`flex items-center gap-1.5 transition-colors text-sm ${
          isLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/40 hover:text-white/80'
        }`}>
          <ArrowLeft size={15} />
          <span className="hidden sm:inline">Problems</span>
        </Link>

        <span className={isLight ? 'text-slate-300' : 'text-white/15'}>|</span>

        {/* Problem title & difficulty */}
        <div className="flex items-center gap-2 flex-1 min-w-0">
          <span className={`text-sm font-mono shrink-0 ${isLight ? 'text-slate-400' : 'text-white/40'}`}>#{problem.id}</span>
          <h1 className={`text-sm font-semibold truncate ${isLight ? 'text-slate-900' : 'text-white/90'}`}>{problem.title}</h1>
          <span className={`hidden sm:inline-flex items-center gap-1 px-2 py-0.5 rounded-full text-[10px] font-bold border ${diff.bg} ${diff.border} ${diff.color} shrink-0`}>
            <span className={`w-1.5 h-1.5 rounded-full ${diff.dot}`} />
            {problem.difficulty}
          </span>
          <span className={`hidden md:inline-flex items-center gap-1 px-2 py-0.5 rounded-full text-[10px] border shrink-0 ${
            isLight ? 'bg-slate-100 border-slate-200 text-slate-500' : 'bg-white/4 border-white/8 text-white/35'
          }`}>
            <Tag size={9} />
            {problem.pattern}
          </span>
        </div>

        {/* ── Actions ── */}
        <div className="flex items-center gap-1.5 shrink-0">

          {/* Theme Selector */}
          <div className={`flex items-center p-0.5 rounded-lg border text-xs font-medium mr-1 ${
            isLight ? 'bg-slate-200 border-slate-300' : 'bg-white/5 border-white/10'
          }`}>
            <button
              onClick={() => setTheme('light')}
              title="Light Mode"
              className={`flex items-center gap-1 px-2 py-1 rounded-md transition-all ${
                isLight ? 'bg-white text-amber-600 font-bold shadow-sm' : 'text-white/40 hover:text-white'
              }`}
            >
              <Sun size={12} />
              <span className="hidden sm:inline text-[10px]">Light</span>
            </button>
            <button
              onClick={() => setTheme('dark')}
              title="Dark Mode"
              className={`flex items-center gap-1 px-2 py-1 rounded-md transition-all ${
                !isLight ? 'bg-violet-600 text-white font-bold shadow-sm' : 'text-slate-500 hover:text-slate-800'
              }`}
            >
              <Moon size={12} />
              <span className="hidden sm:inline text-[10px]">Dark</span>
            </button>
          </div>

          {/* Interview Timer */}
          <InterviewTimer difficulty={problem.difficulty} />

          {/* Interview Mode Toggle */}
          <button
            onClick={() => setInterviewMode(m => !m)}
            title={interviewMode ? "Exit Interview Simulation" : "Start FAANG Interview Simulation"}
            className={`flex items-center gap-1.5 px-2.5 py-1.5 rounded-lg border text-xs font-semibold transition-all ${
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
            className={`flex items-center gap-1.5 px-2.5 py-1.5 rounded-lg border text-xs font-medium transition-all ${
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
              onClick={() => prevProblem && navigate(`/dsa/${prevProblem.id}`)}
              disabled={!prevProblem}
              className={`p-1.5 border-r transition-all disabled:opacity-20 disabled:cursor-not-allowed ${
                isLight ? 'text-slate-500 hover:text-slate-900 border-slate-200' : 'text-white/30 hover:text-white/60 hover:bg-white/5 border-white/8'
              }`}
            >
              <ChevronLeft size={15} />
            </button>
            <button
              onClick={() => nextProblem && navigate(`/dsa/${nextProblem.id}`)}
              disabled={!nextProblem}
              className={`p-1.5 transition-all disabled:opacity-20 disabled:cursor-not-allowed ${
                isLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/30 hover:text-white/60 hover:bg-white/5'
              }`}
            >
              <ChevronRight size={15} />
            </button>
          </div>
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

      {/* ── Main Split Layout ── */}
      <div className="flex flex-1 min-h-0">

        {/* LEFT: Problem Description & Solutions */}
        <div className={`w-full lg:w-[45%] xl:w-[42%] flex flex-col border-r min-h-0 overflow-hidden ${
          isLight ? 'border-slate-200 bg-white' : 'border-white/8 bg-[#020008]'
        }`}>
          {/* Tabs */}
          <div className={`flex border-b shrink-0 items-center justify-between px-2 ${
            isLight ? 'border-slate-200 bg-slate-50' : 'border-white/8 bg-white/[0.015]'
          }`}>
            <div className="flex items-center">
              {[
                { id: 'description', icon: <BookOpen size={12} />, label: 'Problem / प्रश्न' },
                { id: 'hints',       icon: <Lightbulb size={12} />, label: `Hints (${problem.hints?.length || 0})` },
                { id: 'solution',    icon: <Unlock size={12} />, label: 'Solution / समाधान' },
                { id: 'diff',        icon: <ArrowRightLeft size={12} />, label: 'Code Diff / तुलना' },
              ].map(tab => (
                <button
                  key={tab.id}
                  onClick={() => setActiveTab(tab.id)}
                  className={`flex items-center gap-1.5 px-3.5 py-2.5 text-xs font-semibold border-b-2 transition-all ${
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
            ) : (
              <>
                {activeTab === 'hints' && (
                  <HintPanel
                    problem={problem}
                    hintsRevealed={hintsRevealed}
                    onRevealHint={revealHint}
                  />
                )}

                {activeTab === 'solution' && (
                  <SolutionPanel
                    problem={problem}
                    interviewData={interviewData}
                    isLight={isLight}
                    onLoadCodeIntoEditor={handleLoadCode}
                    userCode={code}
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
        <div className="flex-1 flex flex-col min-h-0 overflow-hidden">
          {/* Editor header */}
          <div className="flex items-center justify-between px-4 py-2 border-b border-white/8 bg-white/[0.015] shrink-0">
            <div className="flex items-center gap-2">
              <div className="flex gap-1.5">
                <span className="w-3 h-3 rounded-full bg-red-500/60" />
                <span className="w-3 h-3 rounded-full bg-yellow-500/60" />
                <span className="w-3 h-3 rounded-full bg-emerald-500/60" />
              </div>
              <span className="text-white/30 text-xs font-mono ml-1">solution.py</span>
            </div>
            <span className="text-white/20 text-xs font-mono">Python 3.11 · Pyodide</span>
          </div>

          {/* Editor */}
          <div className="flex-1 min-h-0" style={{ flex: editorHeight }}>
            <CodeEditor value={code} onChange={updateCode} />
          </div>

          {/* Drag handle */}
          <div
            className="h-1 bg-white/5 border-y border-white/8 cursor-row-resize hover:bg-violet-500/20 transition-colors shrink-0 flex items-center justify-center"
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
            <div className="flex gap-1"><span className="w-6 h-0.5 rounded-full bg-white/20" /></div>
          </div>

          {/* Console / Test Runner */}
          <div className="min-h-0" style={{ flex: 100 - editorHeight }}>
            <TestRunner problem={problem} code={code} onSuccess={handleSuccess} />
          </div>
        </div>
      </div>
    </div>
  )
}

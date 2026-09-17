import React, { useState, useMemo, useEffect } from 'react'
import { Link, useNavigate } from 'react-router-dom'
import {
  ArrowLeft, CheckCircle2, Circle, FileText,
  Search, Sparkles, Trophy, Lock, Crown,
  ExternalLink, Copy, Check, X, ChevronDown, ChevronUp,
  Tag, Code2, ArrowRight, Zap
} from 'lucide-react'
import { TOP_INTERVIEW_150, TOP_INTERVIEW_CATEGORIES } from '../data/topInterview150Data'
import { getCachedProStatus, fetchRemoteProStatus } from '../utils/proSubscription'
import { useAuth } from '../context/AuthContext'
import ProPaymentModal from '../components/dsa/ProPaymentModal'

export default function TopInterview150() {
  const navigate = useNavigate()
  const { user } = useAuth()

  // Pro Subscription State
  const [isPro, setIsPro] = useState(() => getCachedProStatus(user?.email).isPro)
  const [showProModal, setShowProModal] = useState(false)

  // Local storage for solved interview questions
  const [solvedIds, setSolvedIds] = useState(() => {
    try {
      return JSON.parse(localStorage.getItem('dsa_solved_interview_150') || '[]')
    } catch {
      return []
    }
  })

  // UI States
  const [showTags, setShowTags] = useState(true)
  const [searchQuery, setSearchQuery] = useState('')
  const [selectedCategory, setSelectedCategory] = useState('All')
  const [activeSolutionModal, setActiveSolutionModal] = useState(null)
  const [copied, setCopied] = useState(false)
  const [collapsedCategories, setCollapsedCategories] = useState({})

  // Theme from session / local
  const [theme] = useState(() => sessionStorage.getItem('dsa_theme') || 'light')
  const isLight = theme === 'light'

  // Sync and Listen for Pro status updates
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

  // Guarded Solution opener: Only Pro subscribers can open solutions or problem details!
  const handleOpenSolution = (problem) => {
    if (!isPro) {
      setShowProModal(true)
      return
    }
    setActiveSolutionModal(problem)
  }

  // Toggle problem solved
  const toggleSolved = (id, e) => {
    e.stopPropagation()
    const next = solvedIds.includes(id)
      ? solvedIds.filter(x => x !== id)
      : [...solvedIds, id]
    setSolvedIds(next)
    localStorage.setItem('dsa_solved_interview_150', JSON.stringify(next))
  }

  // Toggle category collapse
  const toggleCategory = (cat) => {
    setCollapsedCategories(prev => ({
      ...prev,
      [cat]: !prev[cat]
    }))
  }

  // Copy code to clipboard
  const handleCopy = (code) => {
    navigator.clipboard.writeText(code)
    setCopied(true)
    setTimeout(() => setCopied(false), 2000)
  }

  // Filtered problems
  const filteredProblems = useMemo(() => {
    return TOP_INTERVIEW_150.filter(p => {
      const matchSearch = p.title.toLowerCase().includes(searchQuery.toLowerCase()) ||
        p.category.toLowerCase().includes(searchQuery.toLowerCase()) ||
        p.companies.some(c => c.toLowerCase().includes(searchQuery.toLowerCase()))
      const matchCat = selectedCategory === 'All' || p.category === selectedCategory
      return matchSearch && matchCat
    })
  }, [searchQuery, selectedCategory])

  // Group by category
  const groupedProblems = useMemo(() => {
    const groups = {}
    filteredProblems.forEach(p => {
      if (!groups[p.category]) groups[p.category] = []
      groups[p.category].push(p)
    })
    return groups
  }, [filteredProblems])

  const totalQuestions = TOP_INTERVIEW_150.length
  const solvedCount = solvedIds.length
  const progressPercent = Math.round((solvedCount / totalQuestions) * 100)

  return (
    <div className={`min-h-screen transition-colors duration-300 ${
      isLight ? 'bg-[#FAFAFA] text-slate-900' : 'bg-[#05020c] text-white'
    }`}>

      {/* ── Sub-header Navigation ── */}
      <div className={`sticky top-0 z-40 border-b backdrop-blur-md transition-colors ${
        isLight ? 'bg-white/90 border-slate-200 shadow-sm' : 'bg-[#0a0518]/90 border-white/10'
      }`}>
        <div className="max-w-6xl mx-auto px-4 py-3 flex items-center justify-between">
          <div className="flex items-center gap-3">
            <Link
              to="/dsa"
              className={`p-2 rounded-xl border transition-all flex items-center gap-1.5 text-xs font-semibold ${
                isLight
                  ? 'bg-slate-50 border-slate-200 text-slate-700 hover:bg-slate-100'
                  : 'bg-white/5 border-white/10 text-white/70 hover:bg-white/10 hover:text-white'
              }`}
            >
              <ArrowLeft size={15} />
              <span>Back to DSA Hub</span>
            </Link>
            <div className="h-5 w-px bg-slate-200 dark:bg-white/10 hidden sm:block" />
            <Link to="/" className="flex items-center gap-2 group">
              <img
                src="/bittu-logo.jpg"
                alt="Bittu AI"
                className="w-6 h-6 rounded-lg object-cover shadow-sm border border-violet-400/30 group-hover:scale-105 transition-transform"
              />
              <span className="text-xs font-bold uppercase tracking-wider text-violet-600 hidden sm:inline">
                Bittu AI Study Plan
              </span>
            </Link>
          </div>

          <div className="flex items-center gap-2">
            {!isPro ? (
              <button
                type="button"
                onClick={() => setShowProModal(true)}
                className="flex items-center gap-1.5 px-3 py-1.5 rounded-xl text-xs font-bold bg-gradient-to-r from-amber-500 via-yellow-500 to-amber-600 text-white shadow-md shadow-amber-500/25 hover:opacity-95 active:scale-95 transition-all cursor-pointer"
              >
                <Crown size={13} className="text-white fill-white/30" />
                <span>Get Pro Pass (₹99)</span>
              </button>
            ) : (
              <div className="flex items-center gap-1.5 px-3 py-1.5 rounded-xl text-xs font-bold bg-gradient-to-r from-amber-500/15 to-yellow-500/15 border border-amber-400/40 text-amber-500">
                <Crown size={13} className="text-amber-500 fill-amber-500/20" />
                <span>PRO MEMBER</span>
              </div>
            )}
          </div>
        </div>
      </div>

      <div className="max-w-6xl mx-auto px-4 py-8">

        {/* ── Banner matching LeetCode Top Interview 150 Screenshot ── */}
        <div className={`relative overflow-hidden rounded-3xl border p-6 sm:p-8 mb-8 transition-all ${
          isLight
            ? 'bg-white border-slate-200/90 shadow-sm'
            : 'bg-gradient-to-br from-[#0e0a1f] to-[#080413] border-violet-500/20 shadow-violet-950/20'
        }`}>
          {/* Subtle grid background pattern */}
          <div className="absolute inset-0 opacity-[0.03] pointer-events-none" style={{
            backgroundImage: 'radial-gradient(#000 1px, transparent 1px)',
            backgroundSize: '16px 16px'
          }} />

          <div className="relative z-10 flex flex-col sm:flex-row sm:items-center justify-between gap-6">
            
            {/* Left Graphic + Title */}
            <div className="flex items-start gap-4 sm:gap-6">
              {/* LeetCode-style 3D Cyan/Blue "TOP" Bubble Icon */}
              <div className="relative w-20 h-20 sm:w-24 sm:h-24 shrink-0 rounded-2xl bg-gradient-to-br from-cyan-400 via-sky-500 to-blue-600 p-0.5 shadow-xl shadow-cyan-500/20 flex items-center justify-center">
                <div className="w-full h-full rounded-2xl bg-white dark:bg-slate-950 flex flex-col items-center justify-center relative overflow-hidden">
                  <span className="text-xl sm:text-2xl font-black tracking-tight bg-gradient-to-r from-cyan-500 to-blue-600 bg-clip-text text-transparent">
                    TOP
                  </span>
                  <span className="text-[10px] font-extrabold uppercase tracking-widest text-slate-400">
                    150
                  </span>
                  <div className="absolute -bottom-2 -right-2 w-8 h-8 rounded-full bg-cyan-400/20 blur-sm" />
                </div>
              </div>

              <div>
                <div className="flex items-center gap-2 mb-1">
                  <span className="text-xs font-semibold text-slate-500 dark:text-slate-400 flex items-center gap-1">
                    <Sparkles size={12} className="text-cyan-500" />
                    Must-do List for Interview Prep
                  </span>
                </div>
                <h1 className="text-2xl sm:text-3xl font-black tracking-tight mb-2">
                  Top Interview 150
                </h1>
                <p className={`text-xs sm:text-sm max-w-xl leading-relaxed ${
                  isLight ? 'text-slate-600' : 'text-slate-400'
                }`}>
                  Curated essential interview questions covering 23 core topics. Practice real questions asked at <strong>Google, Amazon, Meta, Microsoft, and TCS</strong> with complete Python 3 editorial solutions.
                </p>
              </div>
            </div>

            {/* Right Progress Counter + Tag Toggle */}
            <div className="sm:text-right shrink-0">
              <div className="flex items-center sm:justify-end gap-2 mb-2">
                <span className="text-sm font-mono font-bold">
                  <span className="text-lg font-black text-violet-600">{solvedCount}</span> / {totalQuestions}
                </span>
                <div className="w-6 h-6 rounded-lg bg-amber-500/15 text-amber-500 flex items-center justify-center text-xs">
                  <Trophy size={13} />
                </div>
              </div>

              {/* Progress Bar */}
              <div className={`w-48 sm:w-56 h-2 rounded-full mb-3 overflow-hidden ${
                isLight ? 'bg-slate-200' : 'bg-white/10'
              }`}>
                <div
                  className="h-full rounded-full bg-gradient-to-r from-cyan-500 via-blue-500 to-violet-600 transition-all duration-500"
                  style={{ width: `${progressPercent}%` }}
                />
              </div>

              {/* "Show tags" Checkbox matching LeetCode */}
              <label className="inline-flex items-center gap-2 cursor-pointer select-none text-xs font-semibold text-slate-600 dark:text-slate-300">
                <input
                  type="checkbox"
                  checked={showTags}
                  onChange={(e) => setShowTags(e.target.checked)}
                  className="w-3.5 h-3.5 rounded border-slate-300 text-violet-600 focus:ring-violet-500 cursor-pointer"
                />
                <span>Show company tags</span>
              </label>
            </div>
          </div>
        </div>

        {/* ── Locked Pro Notice Banner (If not subscribed) ── */}
        {!isPro && (
          <div className={`relative overflow-hidden rounded-3xl border p-5 sm:p-6 mb-8 transition-all ${
            isLight
              ? 'bg-gradient-to-r from-amber-500/10 via-yellow-500/10 to-amber-600/10 border-amber-300 shadow-sm'
              : 'bg-gradient-to-r from-amber-950/40 via-yellow-950/25 to-amber-900/30 border-amber-500/30 shadow-lg shadow-amber-950/30'
          }`}>
            <div className="flex flex-col sm:flex-row items-start sm:items-center justify-between gap-5 relative z-10">
              <div className="flex items-start gap-4">
                <div className="w-12 h-12 rounded-2xl bg-gradient-to-br from-amber-500 to-yellow-600 text-white flex items-center justify-center shrink-0 shadow-lg shadow-amber-500/30">
                  <Lock size={22} className="text-white" />
                </div>
                <div>
                  <div className="flex items-center gap-2 flex-wrap mb-1">
                    <h2 className="text-base sm:text-lg font-black tracking-tight text-slate-900 dark:text-white">
                      Top Interview 150 Questions & Solutions are Locked 🔒
                    </h2>
                    <span className="text-[10px] font-black uppercase tracking-wider px-2.5 py-0.5 rounded-full bg-amber-500 text-slate-950 shadow-sm">
                      Pro Pass Required
                    </span>
                  </div>
                  <p className={`text-xs sm:text-sm leading-relaxed max-w-2xl ${
                    isLight ? 'text-slate-600' : 'text-slate-300'
                  }`}>
                    All 150 company-tagged questions, optimal Python 3 solutions, step-by-step intuition, and time/space complexity breakdowns require a Bittu AI Pro Pass. Get unlimited instant access for just <strong>₹99/month</strong>.
                  </p>
                </div>
              </div>
              <button
                type="button"
                onClick={() => setShowProModal(true)}
                className="shrink-0 w-full sm:w-auto px-6 py-3 rounded-2xl text-xs sm:text-sm font-black uppercase tracking-wider bg-gradient-to-r from-amber-500 via-yellow-500 to-amber-600 text-slate-950 shadow-xl shadow-amber-500/30 hover:brightness-110 active:scale-95 transition-all flex items-center justify-center gap-2 cursor-pointer"
              >
                <Crown size={16} className="fill-slate-950" />
                <span>Unlock All 150 (₹99)</span>
              </button>
            </div>
          </div>
        )}

        {/* ── Search & Filter Controls ── */}
        <div className="flex flex-col sm:flex-row gap-3 items-center justify-between mb-6">
          {/* Search Box */}
          <div className={`relative w-full sm:w-80 rounded-xl border flex items-center px-3 py-2 transition-all ${
            isLight
              ? 'bg-white border-slate-200 text-slate-900 shadow-sm'
              : 'bg-white/5 border-white/10 text-white'
          }`}>
            <Search size={15} className="text-slate-400 shrink-0 mr-2" />
            <input
              type="text"
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              placeholder="Search 150 questions or companies..."
              className="bg-transparent text-xs w-full outline-none placeholder:text-slate-400"
            />
            {searchQuery && (
              <button onClick={() => setSearchQuery('')} className="text-slate-400 hover:text-slate-600">
                <X size={13} />
              </button>
            )}
          </div>

          {/* Quick Category Filter Pill Dropdown */}
          <div className="flex items-center gap-2 overflow-x-auto w-full sm:w-auto pb-1 scrollbar-hide">
            <span className="text-[11px] font-bold text-slate-500 shrink-0">Topic:</span>
            <select
              value={selectedCategory}
              onChange={(e) => setSelectedCategory(e.target.value)}
              className={`px-3 py-1.5 rounded-xl border text-xs font-semibold outline-none cursor-pointer ${
                isLight ? 'bg-white border-slate-200 text-slate-700' : 'bg-white/5 border-white/10 text-white'
              }`}
            >
              <option value="All">All 23 Categories</option>
              {TOP_INTERVIEW_CATEGORIES.map(cat => (
                <option key={cat} value={cat}>{cat}</option>
              ))}
            </select>
          </div>
        </div>

        {/* ── Grouped Question List matching Screenshot ── */}
        <div className="space-y-6">
          {Object.entries(groupedProblems).map(([category, problems]) => {
            const isCollapsed = !!collapsedCategories[category]
            const categorySolved = problems.filter(p => solvedIds.includes(p.id)).length

            return (
              <div
                key={category}
                className={`rounded-2xl border overflow-hidden transition-all ${
                  isLight
                    ? 'bg-white border-slate-200/90 shadow-sm'
                    : 'bg-[#0d091a] border-white/8 shadow-md'
                }`}
              >
                {/* Category Header */}
                <button
                  type="button"
                  onClick={() => toggleCategory(category)}
                  className={`w-full px-5 py-3.5 flex items-center justify-between text-left transition-colors cursor-pointer ${
                    isLight
                      ? 'bg-slate-50/90 hover:bg-slate-100/90 border-b border-slate-200'
                      : 'bg-white/[0.03] hover:bg-white/[0.06] border-b border-white/5'
                  }`}
                >
                  <div className="flex items-center gap-2.5">
                    <span className="text-sm font-extrabold tracking-tight">
                      {category}
                    </span>
                    <span className={`text-[11px] font-mono px-2 py-0.5 rounded-full ${
                      isLight ? 'bg-slate-200/70 text-slate-700' : 'bg-white/10 text-white/70'
                    }`}>
                      {categorySolved} / {problems.length}
                    </span>
                  </div>
                  <div className="flex items-center gap-1.5 text-xs text-slate-500 font-semibold">
                    <span>{isCollapsed ? 'Expand' : 'Collapse'}</span>
                    {isCollapsed ? <ChevronDown size={15} /> : <ChevronUp size={15} />}
                  </div>
                </button>

                {/* Problem Rows */}
                {!isCollapsed && (
                  <div className="divide-y divide-slate-100 dark:divide-white/5">
                    {problems.map((problem) => {
                      const isSolved = solvedIds.includes(problem.id)

                      return (
                        <div
                          key={problem.id}
                          className={`px-4 sm:px-6 py-3.5 flex flex-col sm:flex-row sm:items-center justify-between gap-3 hover:bg-violet-500/[0.03] transition-colors`}
                        >
                          {/* Left: Solved radio + Title + Tags */}
                          <div className="flex items-start gap-3 min-w-0">
                            {/* Solved toggle circle */}
                            <button
                              type="button"
                              onClick={(e) => toggleSolved(problem.id, e)}
                              className="mt-0.5 text-slate-400 hover:text-emerald-500 transition-colors shrink-0 cursor-pointer"
                              title={isSolved ? 'Mark as unsolved' : 'Mark as solved'}
                            >
                              {isSolved ? (
                                <CheckCircle2 size={18} className="text-emerald-500 fill-emerald-500/20" />
                              ) : (
                                <Circle size={18} className="text-slate-300 dark:text-white/20 hover:text-emerald-500" />
                              )}
                            </button>

                            <div className="min-w-0">
                              <div className="flex items-baseline gap-2 flex-wrap">
                                <button
                                  type="button"
                                  onClick={() => handleOpenSolution(problem)}
                                  className={`text-left text-sm font-semibold tracking-tight hover:underline flex items-center gap-2 group/title cursor-pointer ${
                                    isSolved
                                      ? isLight ? 'text-slate-500 line-through' : 'text-white/50 line-through'
                                      : isLight ? 'text-slate-900 hover:text-violet-600' : 'text-white hover:text-cyan-300'
                                  }`}
                                >
                                  <span>{problem.title}</span>
                                  {!isPro && (
                                    <span className="inline-flex items-center gap-1 text-[10px] font-bold px-1.5 py-0.2 rounded bg-amber-500/15 border border-amber-500/30 text-amber-500 no-underline">
                                      <Lock size={10} /> Pro
                                    </span>
                                  )}
                                </button>
                              </div>

                              {/* Company tags when "Show tags" is checked */}
                              {showTags && problem.companies && problem.companies.length > 0 && (
                                <div className="flex items-center gap-1.5 flex-wrap mt-1">
                                  {problem.companies.map(comp => (
                                    <span
                                      key={comp}
                                      className={`text-[10px] font-mono px-2 py-0.2 rounded-md border ${
                                        isLight
                                          ? 'bg-slate-100 border-slate-200 text-slate-600'
                                          : 'bg-white/5 border-white/10 text-white/50'
                                      }`}
                                    >
                                      {comp}
                                    </span>
                                  ))}
                                </div>
                              )}
                            </div>
                          </div>

                          {/* Right: Solution button + Difficulty badge */}
                          <div className="flex items-center gap-3 shrink-0 self-end sm:self-center">
                            {/* [Solution] Editorial Button matching LeetCode screenshot */}
                            <button
                              type="button"
                              onClick={() => handleOpenSolution(problem)}
                              className={`flex items-center gap-1.5 px-3 py-1.5 rounded-xl text-xs font-semibold border transition-all cursor-pointer ${
                                !isPro
                                  ? 'bg-amber-500/10 border-amber-500/30 text-amber-500 hover:bg-amber-500/20 hover:border-amber-500/50 shadow-sm shadow-amber-500/10'
                                  : isLight
                                  ? 'bg-slate-50 border-slate-200 text-slate-700 hover:bg-violet-50 hover:border-violet-300 hover:text-violet-700 shadow-sm'
                                  : 'bg-white/5 border-white/10 text-white/70 hover:bg-white/10 hover:text-white'
                              }`}
                              title={!isPro ? 'Pro Subscription Required (₹99/mo)' : 'View Editorial Solution'}
                            >
                              {!isPro ? (
                                <>
                                  <Lock size={12} className="text-amber-500" />
                                  <span className="font-bold">Solution (Pro)</span>
                                </>
                              ) : (
                                <>
                                  <FileText size={13} className="text-violet-500" />
                                  <span>Solution</span>
                                </>
                              )}
                            </button>

                            {/* Difficulty Tag */}
                            <span className={`text-xs font-bold min-w-[54px] text-right ${
                              problem.difficulty === 'Easy'
                                ? 'text-emerald-500'
                                : problem.difficulty === 'Medium'
                                ? 'text-amber-500'
                                : 'text-rose-500'
                            }`}>
                              {problem.difficulty}
                            </span>
                          </div>
                        </div>
                      )
                    })}
                  </div>
                )}
              </div>
            )
          })}
        </div>
      </div>

      {/* ── EDITORIAL SOLUTION MODAL / DRAWER ── */}
      {activeSolutionModal && isPro && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-3 sm:p-4 bg-black/80 backdrop-blur-md animate-fadeIn">
          <div className={`relative w-full max-w-3xl max-h-[90vh] flex flex-col rounded-3xl border shadow-2xl overflow-hidden transition-all ${
            isLight
              ? 'bg-white border-slate-200 text-slate-900 shadow-slate-300/60'
              : 'bg-[#0f0a1c] border-violet-500/30 text-white shadow-violet-950/50'
          }`}>
            {/* Modal Header */}
            <div className={`px-6 py-4 border-b flex items-center justify-between shrink-0 ${
              isLight ? 'bg-slate-50/90 border-slate-200' : 'bg-white/[0.03] border-white/10'
            }`}>
              <div className="flex items-center gap-3">
                <div className="w-9 h-9 rounded-xl bg-violet-600 text-white flex items-center justify-center shadow-md shadow-violet-600/30">
                  <FileText size={18} />
                </div>
                <div>
                  <div className="flex items-center gap-2">
                    <h3 className="text-base font-extrabold tracking-tight">
                      {activeSolutionModal.title}
                    </h3>
                    <span className={`text-[10px] font-bold px-2 py-0.5 rounded-full ${
                      activeSolutionModal.difficulty === 'Easy'
                        ? 'bg-emerald-500/15 text-emerald-500'
                        : activeSolutionModal.difficulty === 'Medium'
                        ? 'bg-amber-500/15 text-amber-500'
                        : 'bg-rose-500/15 text-rose-500'
                    }`}>
                      {activeSolutionModal.difficulty}
                    </span>
                  </div>
                  <p className="text-xs text-slate-500">
                    Category: {activeSolutionModal.category}
                  </p>
                </div>
              </div>

              <button
                onClick={() => setActiveSolutionModal(null)}
                className={`p-2 rounded-full transition-colors ${
                  isLight ? 'hover:bg-slate-200 text-slate-500' : 'hover:bg-white/10 text-white/50 hover:text-white'
                }`}
              >
                <X size={18} />
              </button>
            </div>

            {/* Modal Body */}
            <div className="p-6 overflow-y-auto space-y-5 flex-1">
              
              {/* Problem Description */}
              <div>
                <h4 className="text-xs font-bold uppercase tracking-wider text-slate-400 mb-1.5">
                  Problem Summary
                </h4>
                <p className={`text-xs sm:text-sm leading-relaxed whitespace-pre-line ${
                  isLight ? 'text-slate-700' : 'text-slate-300'
                }`}>
                  {activeSolutionModal.description}
                </p>
              </div>

              {/* Approach & Intuition */}
              <div className={`p-4 rounded-2xl border ${
                isLight ? 'bg-violet-50/60 border-violet-200/80 text-violet-950' : 'bg-violet-950/20 border-violet-500/30 text-violet-200'
              }`}>
                <h4 className="text-xs font-bold uppercase tracking-wider mb-1 flex items-center gap-1.5">
                  <Sparkles size={13} className="text-violet-500" />
                  Optimal Intuition & Approach
                </h4>
                <p className="text-xs sm:text-sm leading-relaxed">
                  {activeSolutionModal.approach}
                </p>
              </div>

              {/* Python Code Solution */}
              <div>
                <div className="flex items-center justify-between mb-2">
                  <div className="flex items-center gap-2">
                    <Code2 size={15} className="text-violet-500" />
                    <span className="text-xs font-bold uppercase tracking-wider">
                      Python 3 Solution (Accepted O(1)/O(n))
                    </span>
                  </div>
                  <button
                    type="button"
                    onClick={() => handleCopy(activeSolutionModal.code)}
                    className={`flex items-center gap-1 px-2.5 py-1 rounded-lg text-xs font-semibold transition-all border ${
                      isLight
                        ? 'bg-slate-100 hover:bg-slate-200 border-slate-200 text-slate-700'
                        : 'bg-white/5 hover:bg-white/10 border-white/10 text-white/70'
                    }`}
                  >
                    {copied ? (
                      <>
                        <Check size={13} className="text-emerald-500" />
                        <span className="text-emerald-500">Copied!</span>
                      </>
                    ) : (
                      <>
                        <Copy size={13} />
                        <span>Copy Code</span>
                      </>
                    )}
                  </button>
                </div>

                <div className="rounded-2xl overflow-hidden border border-slate-800 bg-[#0c0915] p-4 text-xs font-mono leading-relaxed text-slate-100">
                  <pre className="overflow-x-auto scrollbar-thin">
                    <code>{activeSolutionModal.code}</code>
                  </pre>
                </div>
              </div>

              {/* Complexity Analysis */}
              <div className="grid grid-cols-1 sm:grid-cols-2 gap-3">
                <div className={`p-3.5 rounded-2xl border ${
                  isLight ? 'bg-slate-50 border-slate-200' : 'bg-white/5 border-white/10'
                }`}>
                  <span className="text-[11px] font-bold text-slate-400 block mb-0.5">Time Complexity</span>
                  <span className="text-xs sm:text-sm font-mono font-bold text-emerald-500">
                    {activeSolutionModal.timeComplexity}
                  </span>
                </div>
                <div className={`p-3.5 rounded-2xl border ${
                  isLight ? 'bg-slate-50 border-slate-200' : 'bg-white/5 border-white/10'
                }`}>
                  <span className="text-[11px] font-bold text-slate-400 block mb-0.5">Space Complexity</span>
                  <span className="text-xs sm:text-sm font-mono font-bold text-cyan-500">
                    {activeSolutionModal.spaceComplexity}
                  </span>
                </div>
              </div>

              {/* Asked in Companies */}
              {activeSolutionModal.companies && (
                <div>
                  <span className="text-[11px] font-bold uppercase tracking-wider text-slate-400 block mb-1.5">
                    Frequently Asked At:
                  </span>
                  <div className="flex items-center gap-1.5 flex-wrap">
                    {activeSolutionModal.companies.map(c => (
                      <span
                        key={c}
                        className={`text-xs font-semibold px-2.5 py-1 rounded-xl border ${
                          isLight ? 'bg-slate-100 border-slate-200 text-slate-800' : 'bg-white/5 border-white/10 text-white/80'
                        }`}
                      >
                        {c}
                      </span>
                    ))}
                  </div>
                </div>
              )}
            </div>

            {/* Modal Footer */}
            <div className={`px-6 py-3.5 border-t flex items-center justify-between ${
              isLight ? 'bg-slate-50 border-slate-200' : 'bg-white/[0.03] border-white/10'
            }`}>
              <a
                href={activeSolutionModal.editorialUrl}
                target="_blank"
                rel="noreferrer"
                className="text-xs font-semibold text-violet-600 hover:text-violet-700 flex items-center gap-1"
              >
                <span>Official LeetCode Editorial</span>
                <ExternalLink size={12} />
              </a>

              <button
                type="button"
                onClick={() => {
                  const id = activeSolutionModal.id
                  setActiveSolutionModal(null)
                  // Mark as solved and notify
                  if (!solvedIds.includes(id)) {
                    const next = [...solvedIds, id]
                    setSolvedIds(next)
                    localStorage.setItem('dsa_solved_interview_150', JSON.stringify(next))
                  }
                }}
                className="px-4 py-2 rounded-xl text-xs font-bold bg-gradient-to-r from-violet-600 to-cyan-600 text-white shadow-md shadow-violet-600/30 hover:opacity-95 active:scale-95 transition-all cursor-pointer"
              >
                Mark as Solved ✓
              </button>
            </div>
          </div>
        </div>
      )}

      {/* ── ₹99 DSA Pro Pass Payment Modal ── */}
      <ProPaymentModal
        isOpen={showProModal}
        onClose={() => setShowProModal(false)}
        onSuccess={() => setIsPro(true)}
        isLight={isLight}
      />
    </div>
  )
}

import React, { useState, useMemo, useEffect } from 'react'
import { Link } from 'react-router-dom'
import {
  Code2, Search, Trophy, Zap, BookOpen,
  BarChart3, Sparkles, ArrowLeft,
  Target, Flame, Star, CheckCircle2, X, Sun, Moon,
  ChevronLeft, ChevronRight
} from 'lucide-react'
import ProblemCard from '../components/dsa/ProblemCard'
import StatsPanel from '../components/dsa/StatsPanel'
import LeaderboardModal from '../components/dsa/LeaderboardModal'
import { dsaProblems, filterProblems } from '../data/dsaProblems'
import StarField from '../components/StarField'
import { getLevel, getStreak, updateStreak, LEVELS } from '../utils/dsaStats'
import UserNav from '../components/auth/UserNav'
import { useAuth } from '../context/AuthContext'
import { syncProgressOnLogin, saveProgressToCloud } from '../utils/dsaSync'

const TOPICS = [
  'All', 'Arrays', 'Strings', 'Linked List', 'Stack',
  'Hashing', 'Binary Search', 'Backtracking',
  'Trees', 'Graphs', 'Heap', 'Dynamic Programming',
  'Bit Manipulation', 'Sorting', 'Greedy', 'Recursion'
]
const DIFFICULTIES = ['All', 'Easy', 'Medium', 'Hard']
const PHASES = ['All', 'Basic', 'Intermediate', 'Advanced']

function useDSAStorage() {
  const { user } = useAuth()
  const [solved, setSolved] = useState(() => {
    try { return JSON.parse(localStorage.getItem('dsa_solved') || '[]') } catch { return [] }
  })
  const [bookmarks, setBookmarks] = useState(() => {
    try { return JSON.parse(localStorage.getItem('dsa_bookmarks') || '[]') } catch { return [] }
  })

  // Sync with cloud on login
  useEffect(() => {
    if (user?.id) {
      syncProgressOnLogin(user.id).then(res => {
        if (res) {
          setSolved(res.solved)
          setBookmarks(res.bookmarks)
        }
      })
    }
  }, [user?.id])

  const markSolved = (id) => {
    const next = solved.includes(id) ? solved.filter(x => x !== id) : [...solved, id]
    setSolved(next)
    localStorage.setItem('dsa_solved', JSON.stringify(next))
    if (user?.id) saveProgressToCloud(user.id, next, bookmarks)
  }

  const toggleBookmark = (id) => {
    const next = bookmarks.includes(id) ? bookmarks.filter(x => x !== id) : [...bookmarks, id]
    setBookmarks(next)
    localStorage.setItem('dsa_bookmarks', JSON.stringify(next))
    if (user?.id) saveProgressToCloud(user.id, solved, next)
  }

  return { solved, bookmarks, markSolved, toggleBookmark }
}

// XP from solved list
function computeXP(solvedIds) {
  const XP_MAP = { Easy: 10, Medium: 25, Hard: 50 }
  return solvedIds.reduce((acc, id) => {
    const p = dsaProblems.find(x => x.id === id)
    return acc + (p ? (XP_MAP[p.difficulty] || 10) : 10)
  }, 0)
}

export default function DSAHub() {
  const [search, setSearch] = useState('')
  const [topic, setTopic] = useState('All')
  const [difficulty, setDifficulty] = useState('All')
  const [phase, setPhase] = useState('All')
  const [showBookmarks, setShowBookmarks] = useState(false)
  const [showStats, setShowStats] = useState(false)
  const [showLeaderboard, setShowLeaderboard] = useState(false)
  const [theme, setTheme] = useState(() => localStorage.getItem('dsa_theme') || 'dark')
  const [currentPage, setCurrentPage] = useState(1)
  const PAGE_SIZE = 30

  const { solved, bookmarks, markSolved, toggleBookmark } = useDSAStorage()

  // Reset page when filters change
  useEffect(() => {
    setCurrentPage(1)
  }, [search, topic, difficulty, phase, showBookmarks])

  // Update streak on mount
  useEffect(() => { updateStreak() }, [])

  useEffect(() => {
    localStorage.setItem('dsa_theme', theme)
    if (theme === 'light') {
      document.documentElement.classList.add('light')
    } else {
      document.documentElement.classList.remove('light')
    }
  }, [theme])

  const isLight = theme === 'light'
  const streak = getStreak()
  const xp = useMemo(() => computeXP(solved), [solved])
  const level = useMemo(() => getLevel(xp), [xp])

  const phaseMap = { 'Basic': 1, 'Intermediate': 2, 'Advanced': 3 }

  const filtered = useMemo(() => {
    let problems = filterProblems(topic, difficulty, search)
    if (phase !== 'All') problems = problems.filter(p => p.phase === phaseMap[phase])
    if (showBookmarks) problems = problems.filter(p => bookmarks.includes(p.id))
    return problems
  }, [topic, difficulty, search, phase, showBookmarks, bookmarks])

  const totalPages = Math.max(1, Math.ceil(filtered.length / PAGE_SIZE))
  const paginatedProblems = useMemo(() => {
    const start = (currentPage - 1) * PAGE_SIZE
    return filtered.slice(start, start + PAGE_SIZE)
  }, [filtered, currentPage])

  const total = dsaProblems.length
  const solvedCount = solved.length
  const easyTotal   = dsaProblems.filter(p => p.difficulty === 'Easy').length
  const mediumTotal = dsaProblems.filter(p => p.difficulty === 'Medium').length
  const hardTotal   = dsaProblems.filter(p => p.difficulty === 'Hard').length

  const easySolved   = solved.filter(id => dsaProblems.find(p => p.id === id)?.difficulty === 'Easy').length
  const mediumSolved = solved.filter(id => dsaProblems.find(p => p.id === id)?.difficulty === 'Medium').length
  const hardSolved   = solved.filter(id => dsaProblems.find(p => p.id === id)?.difficulty === 'Hard').length

  return (
    <div className={`relative min-h-screen transition-colors duration-300 ${
      isLight ? 'bg-[#F4F6FB] text-slate-900' : 'bg-[#020008] text-white'
    }`}>
      {!isLight && <StarField />}
      <div className={`fixed w-96 h-96 rounded-full ${isLight ? 'bg-violet-400/10' : 'bg-violet-600/10'} -top-48 -left-48 blur-3xl pointer-events-none`} />
      <div className={`fixed w-80 h-80 rounded-full ${isLight ? 'bg-cyan-400/10' : 'bg-cyan-600/8'} top-1/3 -right-40 blur-3xl pointer-events-none`} />

      <div className="relative z-10 max-w-7xl mx-auto px-4 py-5">

        {/* ── Header ── */}
        <div className="flex items-center justify-between mb-5">
          <div className="flex items-center gap-3">
            <Link to="/" className={`p-2 rounded-lg border transition-all ${
              isLight ? 'bg-white border-slate-200 text-slate-700 hover:bg-slate-100' : 'bg-white/5 hover:bg-white/10 border-white/8 text-white/60'
            }`}>
              <ArrowLeft size={15} />
            </Link>
            <div className="flex items-center gap-2.5">
              <div className="w-9 h-9 rounded-xl bg-gradient-to-br from-violet-600 to-cyan-600 flex items-center justify-center shadow-lg shadow-violet-500/30">
                <Code2 size={18} className="text-white" />
              </div>
              <div>
                <h1 className={`text-lg font-bold tracking-tight ${isLight ? 'text-slate-900' : 'text-white'}`}>
                  DSA <span className="bg-gradient-to-r from-violet-400 to-cyan-400 bg-clip-text text-transparent">Practice</span>
                </h1>
                <p className={`text-[10px] ${isLight ? 'text-slate-500' : 'text-white/30'}`}>Python · {total} Problems · Basic to Advanced</p>
              </div>
            </div>
          </div>

          <div className="flex items-center gap-2">
            {/* User Profile / Auth Nav */}
            <UserNav isLight={isLight} />

            {/* Theme Toggle Feature */}
            <div className={`flex items-center p-0.5 rounded-lg border text-xs font-medium ${
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

            <button
              onClick={() => setShowLeaderboard(true)}
              className={`flex items-center gap-1.5 px-3 py-1.5 rounded-lg border text-xs font-semibold transition-all ${
                showLeaderboard
                  ? 'bg-amber-500/20 border-amber-500/40 text-amber-300 shadow-sm'
                  : isLight
                  ? 'bg-white border-amber-200 text-amber-700 hover:bg-amber-50'
                  : 'bg-amber-500/10 border-amber-500/25 text-amber-300 hover:bg-amber-500/20 hover:border-amber-500/40'
              }`}
            >
              <Trophy size={13} className="text-amber-400" />
              <span>Leaderboard</span>
            </button>

            <button
              onClick={() => setShowBookmarks(b => !b)}
              className={`flex items-center gap-1.5 px-3 py-1.5 rounded-lg border text-xs font-medium transition-all ${
                showBookmarks
                  ? 'bg-violet-500/20 border-violet-500/40 text-violet-300'
                  : isLight ? 'bg-white border-slate-200 text-slate-600 hover:border-slate-300' : 'bg-white/4 border-white/10 text-white/50 hover:border-white/20'
              }`}
            >
              <Star size={12} />
              Saved {bookmarks.length > 0 && `(${bookmarks.length})`}
            </button>
            <button
              onClick={() => setShowStats(s => !s)}
              className={`flex items-center gap-1.5 px-3 py-1.5 rounded-lg border text-xs font-medium transition-all ${
                showStats
                  ? 'bg-cyan-500/20 border-cyan-500/40 text-cyan-300'
                  : isLight ? 'bg-white border-slate-200 text-slate-600 hover:border-slate-300' : 'bg-white/4 border-white/10 text-white/50 hover:border-white/20'
              }`}
            >
              <BarChart3 size={12} />
              Stats
            </button>
          </div>
        </div>

        {/* ── Gamification Bar ── */}
        <div className={`flex flex-wrap items-center gap-3 mb-5 p-3.5 border rounded-xl transition-colors ${
          isLight
            ? 'bg-white border-slate-200/90 shadow-sm text-slate-800'
            : 'bg-white/[0.025] border-white/8 text-white'
        }`}>
          {/* Streak */}
          <div className="flex items-center gap-2">
            <div className={`w-8 h-8 rounded-lg border flex items-center justify-center ${
              isLight ? 'bg-amber-100 border-amber-300 text-amber-600' : 'bg-amber-500/15 border-amber-500/25 text-amber-400'
            }`}>
              <Flame size={16} />
            </div>
            <div>
              <p className={`font-bold text-sm leading-none ${isLight ? 'text-slate-900' : 'text-white'}`}>
                {streak} <span className="text-amber-500">🔥</span>
              </p>
              <p className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/30'}`}>Day Streak</p>
            </div>
          </div>

          <div className={`w-px h-8 ${isLight ? 'bg-slate-200' : 'bg-white/8'}`} />

          {/* Level + XP */}
          <div className="flex items-center gap-2 flex-1 min-w-0">
            <span className="text-xl">{level.icon}</span>
            <div className="flex-1 min-w-0">
              <div className="flex items-center gap-2 mb-1">
                <span className={`text-xs font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>{level.name}</span>
                <span className={`text-[10px] font-mono font-semibold px-1.5 py-0.2 rounded ${
                  isLight ? 'bg-violet-100 text-violet-700 border border-violet-200' : 'text-violet-300'
                }`}>
                  {xp} XP
                </span>
                {level.nextLevel && (
                  <span className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/25'}`}>
                    → {level.nextLevel.icon} {level.nextLevel.name}
                  </span>
                )}
              </div>
              <div className={`w-full rounded-full h-1.5 max-w-xs ${isLight ? 'bg-slate-200' : 'bg-white/5'}`}>
                <div
                  className="h-1.5 rounded-full bg-gradient-to-r from-violet-500 to-cyan-500 transition-all duration-700"
                  style={{ width: `${level.progressInLevel}%` }}
                />
              </div>
            </div>
          </div>

          <div className={`w-px h-8 hidden sm:block ${isLight ? 'bg-slate-200' : 'bg-white/8'}`} />

          {/* Solved count */}
          <div className="hidden sm:flex items-center gap-1.5">
            <Trophy size={14} className={isLight ? 'text-emerald-600' : 'text-emerald-400'} />
            <span className={`text-sm font-bold ${isLight ? 'text-slate-900' : 'text-white'}`}>{solvedCount}</span>
            <span className={`text-xs ${isLight ? 'text-slate-500 font-medium' : 'text-white/30'}`}>/ {total} solved</span>
          </div>
        </div>

        {/* ── Stats Cards ── */}
        <div className="grid grid-cols-2 sm:grid-cols-4 gap-3 mb-5">
          {[
            {
              label: 'Solved',
              value: solvedCount,
              total,
              color: isLight ? 'bg-violet-50/90' : 'bg-gradient-to-br from-violet-500/20 to-violet-600/15',
              border: isLight ? 'border-violet-200 shadow-sm' : 'border-violet-500/20',
              textTitle: isLight ? 'text-violet-800' : 'text-violet-300',
              textVal: isLight ? 'text-violet-950 font-black' : 'text-violet-300 font-bold',
              textSub: isLight ? 'text-slate-500 font-semibold' : 'text-white/25',
              trackBg: isLight ? 'bg-violet-200/80' : 'bg-white/5',
              barBg: 'bg-violet-600',
              icon: <CheckCircle2 size={13} />
            },
            {
              label: 'Easy',
              value: easySolved,
              total: easyTotal,
              color: isLight ? 'bg-emerald-50/90' : 'bg-gradient-to-br from-emerald-500/15 to-emerald-600/10',
              border: isLight ? 'border-emerald-200 shadow-sm' : 'border-emerald-500/20',
              textTitle: isLight ? 'text-emerald-800' : 'text-emerald-300',
              textVal: isLight ? 'text-emerald-950 font-black' : 'text-emerald-300 font-bold',
              textSub: isLight ? 'text-slate-500 font-semibold' : 'text-white/25',
              trackBg: isLight ? 'bg-emerald-200/80' : 'bg-white/5',
              barBg: 'bg-emerald-600',
              icon: <Zap size={13} />
            },
            {
              label: 'Medium',
              value: mediumSolved,
              total: mediumTotal,
              color: isLight ? 'bg-amber-50/90' : 'bg-gradient-to-br from-amber-500/15 to-amber-600/10',
              border: isLight ? 'border-amber-200 shadow-sm' : 'border-amber-500/20',
              textTitle: isLight ? 'text-amber-900' : 'text-amber-300',
              textVal: isLight ? 'text-amber-950 font-black' : 'text-amber-300 font-bold',
              textSub: isLight ? 'text-slate-500 font-semibold' : 'text-white/25',
              trackBg: isLight ? 'bg-amber-200/80' : 'bg-white/5',
              barBg: 'bg-amber-500',
              icon: <Flame size={13} />
            },
            {
              label: 'Hard',
              value: hardSolved,
              total: hardTotal,
              color: isLight ? 'bg-rose-50/90' : 'bg-gradient-to-br from-red-500/15 to-red-600/10',
              border: isLight ? 'border-rose-200 shadow-sm' : 'border-red-500/20',
              textTitle: isLight ? 'text-rose-900' : 'text-red-300',
              textVal: isLight ? 'text-rose-950 font-black' : 'text-red-300 font-bold',
              textSub: isLight ? 'text-slate-500 font-semibold' : 'text-white/25',
              trackBg: isLight ? 'bg-rose-200/80' : 'bg-white/5',
              barBg: 'bg-rose-600',
              icon: <Target size={13} />
            },
          ].map(stat => (
            <div key={stat.label} className={`${stat.color} border ${stat.border} rounded-xl p-3.5`}>
              <div className={`flex items-center gap-1.5 ${stat.textTitle} mb-1`}>
                {stat.icon}
                <span className="text-xs font-bold">{stat.label}</span>
              </div>
              <div className="flex items-baseline gap-1">
                <span className={`text-2xl ${stat.textVal}`}>{stat.value}</span>
                <span className={`text-sm ${stat.textSub}`}>/ {stat.total}</span>
              </div>
              <div className={`mt-2 w-full rounded-full h-1 ${stat.trackBg}`}>
                <div
                  className={`h-1 rounded-full ${stat.barBg} transition-all duration-700`}
                  style={{ width: `${stat.total > 0 ? (stat.value / stat.total) * 100 : 0}%` }}
                />
              </div>
            </div>
          ))}
        </div>

        <div className="flex gap-4">
          {/* ── Main Content ── */}
          <div className="flex-1 min-w-0">

            {/* Search */}
            <div className="relative mb-3">
              <Search size={14} className={`absolute left-3 top-1/2 -translate-y-1/2 ${
                isLight ? 'text-slate-500' : 'text-white/30'
              }`} />
              <input
                type="text"
                placeholder="Search problems, patterns, topics..."
                value={search}
                onChange={e => setSearch(e.target.value)}
                className={`w-full rounded-xl pl-9 pr-4 py-2.5 text-sm transition-all focus:outline-none ${
                  isLight
                    ? 'bg-white border border-slate-300 text-slate-900 placeholder-slate-400 focus:border-violet-500 focus:ring-2 focus:ring-violet-100 shadow-sm'
                    : 'bg-white/4 border border-white/8 text-white placeholder-white/25 focus:border-violet-500/40 focus:bg-white/6'
                }`}
              />
              {search && (
                <button
                  onClick={() => setSearch('')}
                  className={`absolute right-3 top-1/2 -translate-y-1/2 ${
                    isLight ? 'text-slate-400 hover:text-slate-700' : 'text-white/25 hover:text-white/60'
                  }`}
                >
                  <X size={14} />
                </button>
              )}
            </div>

            {/* Filters */}
            <div className="flex flex-wrap gap-2 mb-3">
              <div className={`flex items-center gap-1 rounded-lg p-1 border ${
                isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
              }`}>
                {DIFFICULTIES.map(d => (
                  <button
                    key={d}
                    onClick={() => setDifficulty(d)}
                    className={`px-2.5 py-1 rounded-md text-xs font-semibold transition-all ${
                      difficulty === d
                        ? d === 'Easy'
                          ? isLight ? 'bg-emerald-600 text-white shadow-sm' : 'bg-emerald-500/20 text-emerald-300 border border-emerald-500/30'
                          : d === 'Medium'
                          ? isLight ? 'bg-amber-500 text-slate-950 shadow-sm font-bold' : 'bg-amber-500/20 text-amber-300 border border-amber-500/30'
                          : d === 'Hard'
                          ? isLight ? 'bg-rose-600 text-white shadow-sm' : 'bg-red-500/20 text-red-300 border border-red-500/30'
                          : isLight ? 'bg-violet-600 text-white shadow-sm' : 'bg-violet-500/20 text-violet-300 border border-violet-500/30'
                        : isLight
                        ? 'text-slate-600 hover:text-slate-900 hover:bg-slate-100'
                        : 'text-white/40 hover:text-white/70'
                    }`}
                  >
                    {d}
                  </button>
                ))}
              </div>

              <div className={`flex items-center gap-1 rounded-lg p-1 border ${
                isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
              }`}>
                {PHASES.map(p => (
                  <button
                    key={p}
                    onClick={() => setPhase(p)}
                    className={`px-2.5 py-1 rounded-md text-xs font-semibold transition-all ${
                      phase === p
                        ? isLight
                          ? 'bg-violet-600 text-white shadow-sm'
                          : 'bg-violet-500/20 text-violet-300 border border-violet-500/30'
                        : isLight
                        ? 'text-slate-600 hover:text-slate-900 hover:bg-slate-100'
                        : 'text-white/40 hover:text-white/70'
                    }`}
                  >
                    {p}
                  </button>
                ))}
              </div>
            </div>

            {/* Topic pills */}
            <div className="flex flex-wrap gap-1.5 mb-4">
              {TOPICS.filter(t => t === 'All' || dsaProblems.some(p => p.topic === t)).map(t => (
                <button
                  key={t}
                  onClick={() => setTopic(t)}
                  className={`px-2.5 py-1 rounded-full text-xs font-medium border transition-all ${
                    topic === t
                      ? isLight
                        ? 'bg-violet-600 border-violet-600 text-white font-bold shadow-md shadow-violet-600/20'
                        : 'bg-violet-500/25 border-violet-500/50 text-violet-300'
                      : isLight
                      ? 'bg-white border-slate-200 text-slate-700 hover:bg-slate-100 hover:border-slate-300 shadow-sm font-semibold'
                      : 'bg-white/3 border-white/8 text-white/40 hover:text-white/70 hover:border-white/20'
                  }`}
                >
                  {t}
                </button>
              ))}
            </div>

            {/* Problem Count */}
            <div className="flex items-center justify-between mb-3">
              <p className={`text-xs ${isLight ? 'text-slate-600' : 'text-white/35'}`}>
                Showing <span className={`font-bold ${isLight ? 'text-slate-900' : 'text-white/80'}`}>
                  {filtered.length === 0 ? 0 : (currentPage - 1) * PAGE_SIZE + 1}–{Math.min(currentPage * PAGE_SIZE, filtered.length)}
                </span> of <span className={`font-bold ${isLight ? 'text-slate-900' : 'text-white/80'}`}>{filtered.length}</span> problems
                {search && <span> for "<span className={isLight ? 'text-violet-700 font-bold' : 'text-violet-300'}>{search}</span>"</span>}
              </p>
              <div className="flex items-center gap-2">
                {showBookmarks && (
                  <span className={`text-xs px-2 py-0.5 rounded-full border ${
                    isLight
                      ? 'bg-violet-100 border-violet-300 text-violet-800 font-semibold'
                      : 'text-violet-400 bg-violet-500/10 border-violet-500/20'
                  }`}>
                    Bookmarks only
                  </span>
                )}
                {totalPages > 1 && (
                  <span className={`text-xs px-2 py-0.5 rounded-lg border font-mono ${
                    isLight ? 'bg-slate-100 border-slate-200 text-slate-600' : 'bg-white/5 border-white/10 text-white/50'
                  }`}>
                    Page {currentPage} / {totalPages}
                  </span>
                )}
              </div>
            </div>

            {/* Problem List */}
            <div className="space-y-2">
              {filtered.length === 0 ? (
                <div className="text-center py-16">
                  <Code2 size={32} className={`mx-auto mb-3 ${isLight ? 'text-slate-300' : 'text-white/10'}`} />
                  <p className={`text-sm ${isLight ? 'text-slate-500' : 'text-white/30'}`}>No problems found</p>
                  <p className={`text-xs mt-1 ${isLight ? 'text-slate-400' : 'text-white/15'}`}>Try adjusting your filters</p>
                </div>
              ) : (
                paginatedProblems.map(problem => (
                  <ProblemCard
                    key={problem.id}
                    problem={problem}
                    isSolved={solved.includes(problem.id)}
                    isBookmarked={bookmarks.includes(problem.id)}
                    onBookmark={toggleBookmark}
                    isLight={isLight}
                  />
                ))
              )}
            </div>

            {/* Pagination Controls */}
            {totalPages > 1 && (
              <div className={`flex flex-wrap items-center justify-between gap-3 mt-6 p-3 rounded-xl border ${
                isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.02] border-white/8'
              }`}>
                <div className="flex items-center gap-1.5">
                  <button
                    onClick={() => {
                      setCurrentPage(p => Math.max(1, p - 1))
                      window.scrollTo({ top: 300, behavior: 'smooth' })
                    }}
                    disabled={currentPage === 1}
                    className={`flex items-center gap-1 px-3 py-1.5 rounded-lg text-xs font-semibold border transition-all ${
                      currentPage === 1
                        ? 'opacity-40 cursor-not-allowed border-transparent'
                        : isLight
                        ? 'bg-slate-100 border-slate-200 text-slate-700 hover:bg-slate-200 hover:text-slate-900'
                        : 'bg-white/5 border-white/10 text-white/70 hover:bg-white/10 hover:text-white'
                    }`}
                  >
                    <ChevronLeft size={14} />
                    <span>Previous</span>
                  </button>

                  <button
                    onClick={() => {
                      setCurrentPage(p => Math.min(totalPages, p + 1))
                      window.scrollTo({ top: 300, behavior: 'smooth' })
                    }}
                    disabled={currentPage === totalPages}
                    className={`flex items-center gap-1 px-3 py-1.5 rounded-lg text-xs font-semibold border transition-all ${
                      currentPage === totalPages
                        ? 'opacity-40 cursor-not-allowed border-transparent'
                        : isLight
                        ? 'bg-slate-100 border-slate-200 text-slate-700 hover:bg-slate-200 hover:text-slate-900'
                        : 'bg-white/5 border-white/10 text-white/70 hover:bg-white/10 hover:text-white'
                    }`}
                  >
                    <span>Next</span>
                    <ChevronRight size={14} />
                  </button>
                </div>

                {/* Page Number Quick Buttons */}
                <div className="flex items-center gap-1">
                  {Array.from({ length: Math.min(7, totalPages) }, (_, idx) => {
                    let pageNum = idx + 1
                    if (totalPages > 7) {
                      if (currentPage > 4 && currentPage < totalPages - 3) {
                        pageNum = currentPage - 3 + idx
                      } else if (currentPage >= totalPages - 3) {
                        pageNum = totalPages - 6 + idx
                      }
                    }
                    return (
                      <button
                        key={pageNum}
                        onClick={() => {
                          setCurrentPage(pageNum)
                          window.scrollTo({ top: 300, behavior: 'smooth' })
                        }}
                        className={`w-7 h-7 rounded-lg text-xs font-mono font-bold transition-all ${
                          currentPage === pageNum
                            ? isLight
                              ? 'bg-violet-600 text-white shadow-md shadow-violet-600/30'
                              : 'bg-violet-500 text-white shadow-lg shadow-violet-500/30'
                            : isLight
                            ? 'text-slate-600 hover:bg-slate-100'
                            : 'text-white/40 hover:bg-white/5 hover:text-white'
                        }`}
                      >
                        {pageNum}
                      </button>
                    )
                  })}
                </div>

                <div className={`text-xs font-mono ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
                  Page {currentPage} of {totalPages}
                </div>
              </div>
            )}
          </div>

          {/* ── Right Sidebar — Stats Panel ── */}
          {showStats && (
            <div className="w-64 shrink-0 hidden lg:block">
              <div className="sticky top-6">
                <StatsPanel solved={solved} isLight={isLight} />
              </div>
            </div>
          )}
        </div>
      </div>

      {/* ── Leaderboard & Contest Modal ── */}
      <LeaderboardModal
        isOpen={showLeaderboard}
        onClose={() => setShowLeaderboard(false)}
        userStats={{
          xp,
          streak,
          solvedCount,
          easySolved,
          medSolved,
          hardSolved
        }}
        isLight={isLight}
      />
    </div>
  )
}

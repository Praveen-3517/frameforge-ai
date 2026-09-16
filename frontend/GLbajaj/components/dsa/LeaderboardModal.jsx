import React, { useState, useMemo } from 'react'
import { Link, useNavigate } from 'react-router-dom'
import {
  Trophy, Flame, Zap, Award, Star, X, Medal, Crown,
  Clock, CheckCircle2, ChevronRight, Users, Target, Shield,
  TrendingUp, Sparkles, AlertCircle, ArrowUpRight
} from 'lucide-react'

// Simulated Global Competitive Coder Database
const GLOBAL_LEADERS = [
  { rank: 1, name: 'Aarav Sharma', handle: '@aarav_codes', avatar: '👨‍💻', college: 'IIT Delhi', xp: 4850, solved: 142, easy: 50, med: 62, hard: 30, streak: 38, tier: 'Grandmaster' },
  { rank: 2, name: 'Priya Patel', handle: '@priya_algo', avatar: '👩‍💻', college: 'BITS Pilani', xp: 4420, solved: 128, easy: 45, med: 58, hard: 25, streak: 45, tier: 'Grandmaster' },
  { rank: 3, name: 'Dev Rishi', handle: '@dev_matrix', avatar: '🚀', college: 'IIIT Hyderabad', xp: 4180, solved: 119, easy: 40, med: 55, hard: 24, streak: 29, tier: 'Grandmaster' },
  { rank: 4, name: 'Vikramaditya S.', handle: '@vikram_cpp', avatar: '⚡', college: 'NIT Trichy', xp: 3720, solved: 104, easy: 38, med: 50, hard: 16, streak: 21, tier: 'Master' },
  { rank: 5, name: 'Neha Gupta', handle: '@neha_coder', avatar: '✨', college: 'DTU Delhi', xp: 3410, solved: 96, easy: 35, med: 48, hard: 13, streak: 33, tier: 'Master' },
  { rank: 6, name: 'Arjun Verma', handle: '@arjun_v', avatar: '🎯', college: 'IIT Bombay', xp: 3150, solved: 88, easy: 32, med: 44, hard: 12, streak: 18, tier: 'Master' },
  { rank: 7, name: 'Ananya Krishnan', handle: '@ananya_k', avatar: '🌸', college: 'IIT Madras', xp: 2890, solved: 81, easy: 30, med: 42, hard: 9, streak: 24, tier: 'Specialist' },
  { rank: 8, name: 'Rohan Mehra', handle: '@rohan_py', avatar: '🐍', college: 'NSUT Delhi', xp: 2640, solved: 74, easy: 28, med: 38, hard: 8, streak: 15, tier: 'Specialist' },
  { rank: 9, name: 'Sneha Roy', handle: '@sneha_dev', avatar: '💡', college: 'Jadavpur Univ', xp: 2380, solved: 67, easy: 26, med: 35, hard: 6, streak: 19, tier: 'Specialist' },
  { rank: 10, name: 'Kunal Singhania', handle: '@kunal_dsa', avatar: '🔥', college: 'IIT Roorkee', xp: 2150, solved: 61, easy: 25, med: 31, hard: 5, streak: 12, tier: 'Specialist' },
  { rank: 11, name: 'Tanvi Joshi', handle: '@tanvi_j', avatar: '🌟', college: 'COEP Pune', xp: 1920, solved: 55, easy: 22, med: 28, hard: 5, streak: 14, tier: 'Specialist' },
  { rank: 12, name: 'Aditya Nair', handle: '@aditya_n', avatar: '☕', college: 'NIT Surathkal', xp: 1740, solved: 49, easy: 20, med: 26, hard: 3, streak: 9, tier: 'Contender' },
]

const TIER_CONFIG = {
  Grandmaster: { label: 'Grandmaster', icon: '👑', color: 'text-amber-400', bg: 'bg-amber-500/15', border: 'border-amber-500/30' },
  Master:      { label: 'Master',      icon: '💎', color: 'text-violet-400', bg: 'bg-violet-500/15', border: 'border-violet-500/30' },
  Specialist:  { label: 'Specialist',  icon: '⚡', color: 'text-cyan-400',   bg: 'bg-cyan-500/15',   border: 'border-cyan-500/30' },
  Contender:   { label: 'Contender',   icon: '🎯', color: 'text-emerald-400',bg: 'bg-emerald-500/15',border: 'border-emerald-500/30' },
}

export default function LeaderboardModal({
  isOpen,
  onClose,
  userStats = { xp: 0, streak: 0, solvedCount: 0, easySolved: 0, medSolved: 0, hardSolved: 0 },
  isLight = false
}) {
  const navigate = useNavigate()
  const [activeTab, setActiveTab] = useState('leaderboard') // 'leaderboard' | 'contest'
  const [filter, setFilter]       = useState('xp') // 'xp' | 'solved' | 'streak'

  // Calculate dynamic rank for current user
  const { userRank, sortedLeaders } = useMemo(() => {
    const list = [...GLOBAL_LEADERS]
    if (filter === 'solved') {
      list.sort((a, b) => b.solved - a.solved)
    } else if (filter === 'streak') {
      list.sort((a, b) => b.streak - a.streak)
    } else {
      list.sort((a, b) => b.xp - a.xp)
    }

    // Determine where user falls
    let rank = 1
    for (const item of list) {
      const metric = filter === 'solved' ? item.solved : filter === 'streak' ? item.streak : item.xp
      const userMetric = filter === 'solved' ? userStats.solvedCount : filter === 'streak' ? userStats.streak : userStats.xp
      if (userMetric < metric) rank++
    }

    return { userRank: rank, sortedLeaders: list }
  }, [filter, userStats])

  if (!isOpen) return null

  const getUserTier = (xp) => {
    if (xp >= 4000) return 'Grandmaster'
    if (xp >= 2800) return 'Master'
    if (xp >= 1500) return 'Specialist'
    return 'Contender'
  }

  const userTier = getUserTier(userStats.xp)
  const userTierInfo = TIER_CONFIG[userTier]

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center p-3 sm:p-4 bg-black/70 backdrop-blur-md animate-fadeIn">
      <div className={`relative w-full max-w-4xl max-h-[92vh] flex flex-col rounded-2xl border shadow-2xl overflow-hidden transition-all ${
        isLight
          ? 'bg-[#F9FAFC] border-slate-200 text-slate-900 shadow-slate-300/50'
          : 'bg-[#0a0218] border-violet-500/25 text-white shadow-violet-900/30'
      }`}>

        {/* ── Modal Header ── */}
        <div className={`flex items-center justify-between px-6 py-4 border-b shrink-0 ${
          isLight ? 'bg-white border-slate-200' : 'bg-white/[0.02] border-white/8'
        }`}>
          <div className="flex items-center gap-3">
            <div className="w-10 h-10 rounded-xl bg-gradient-to-br from-amber-500 via-violet-600 to-cyan-500 flex items-center justify-center shadow-lg shadow-violet-500/30 text-white">
              <Trophy size={20} />
            </div>
            <div>
              <div className="flex items-center gap-2">
                <h2 className="text-base font-bold tracking-tight">
                  DSA Champions League & Contests
                </h2>
                <span className="px-2 py-0.5 rounded-full text-[10px] font-bold bg-amber-500/20 border border-amber-500/30 text-amber-400">
                  Season 2026
                </span>
              </div>
              <p className={`text-xs ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
                Compete with 24,000+ engineers across India and track your placement readiness
              </p>
            </div>
          </div>

          <button
            onClick={onClose}
            className={`p-2 rounded-xl border transition-all ${
              isLight ? 'bg-slate-100 hover:bg-slate-200 border-slate-200 text-slate-600' : 'bg-white/5 hover:bg-white/10 border-white/10 text-white/60'
            }`}
          >
            <X size={16} />
          </button>
        </div>

        {/* ── Tabs Navigation ── */}
        <div className={`flex items-center justify-between px-6 border-b shrink-0 ${
          isLight ? 'bg-slate-50 border-slate-200' : 'bg-black/30 border-white/5'
        }`}>
          <div className="flex gap-1">
            <button
              onClick={() => setActiveTab('leaderboard')}
              className={`flex items-center gap-2 py-3 px-4 font-semibold text-xs border-b-2 transition-all ${
                activeTab === 'leaderboard'
                  ? 'border-violet-500 text-violet-400'
                  : isLight ? 'border-transparent text-slate-500 hover:text-slate-900' : 'border-transparent text-white/40 hover:text-white/70'
              }`}
            >
              <Trophy size={14} />
              <span>Global Rankings</span>
            </button>
            <button
              onClick={() => setActiveTab('contest')}
              className={`flex items-center gap-2 py-3 px-4 font-semibold text-xs border-b-2 transition-all ${
                activeTab === 'contest'
                  ? 'border-amber-500 text-amber-400'
                  : isLight ? 'border-transparent text-slate-500 hover:text-slate-900' : 'border-transparent text-white/40 hover:text-white/70'
              }`}
            >
              <Flame size={14} />
              <span>Weekly Contest #48</span>
              <span className="w-2 h-2 rounded-full bg-emerald-500 animate-ping" />
            </button>
          </div>

          {/* Leaderboard Filters */}
          {activeTab === 'leaderboard' && (
            <div className={`flex items-center p-0.5 rounded-lg border text-[11px] font-medium my-2 overflow-x-auto scrollbar-none shrink-0 ${
              isLight ? 'bg-white border-slate-200' : 'bg-white/5 border-white/10'
            }`}>
              {[
                { id: 'xp', label: 'Top XP' },
                { id: 'solved', label: 'Most Solved' },
                { id: 'streak', label: 'Streaks' }
              ].map(f => (
                <button
                  key={f.id}
                  onClick={() => setFilter(f.id)}
                  className={`px-2.5 py-1 rounded-md transition-all ${
                    filter === f.id
                      ? 'bg-violet-600 text-white font-bold shadow-sm'
                      : isLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/40 hover:text-white'
                  }`}
                >
                  {f.label}
                </button>
              ))}
            </div>
          )}
        </div>

        {/* ── Modal Body Content ── */}
        <div className="flex-1 overflow-y-auto px-6 py-5 space-y-6">

          {/* ================= TAB 1: GLOBAL LEADERBOARD ================= */}
          {activeTab === 'leaderboard' && (
            <div className="space-y-6">

              {/* ── User's Personal Live Rank Sticky Banner ── */}
              <div className={`p-4 rounded-xl border flex flex-wrap items-center justify-between gap-4 shadow-lg ${
                isLight
                  ? 'bg-gradient-to-r from-violet-50 via-white to-amber-50 border-violet-200 text-slate-800'
                  : 'bg-gradient-to-r from-violet-950/40 via-black/40 to-amber-950/30 border-violet-500/30 text-white'
              }`}>
                <div className="flex items-center gap-3.5">
                  <div className="w-11 h-11 rounded-xl bg-gradient-to-br from-violet-600 to-cyan-500 flex items-center justify-center font-bold text-sm shadow-md text-white">
                    #{userRank}
                  </div>
                  <div>
                    <div className="flex items-center gap-2">
                      <span className="font-bold text-sm">Your Standing (You)</span>
                      <span className={`px-2 py-0.2 rounded-full text-[10px] font-semibold border ${userTierInfo.bg} ${userTierInfo.border} ${userTierInfo.color}`}>
                        {userTierInfo.icon} {userTierInfo.label}
                      </span>
                    </div>
                    <p className={`text-xs ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
                      Rank #{userRank} among active participants in this session
                    </p>
                  </div>
                </div>

                <div className="flex items-center gap-4 sm:gap-6 font-mono text-xs">
                  <div>
                    <span className={`text-[10px] block font-sans ${isLight ? 'text-slate-400' : 'text-white/30'}`}>Total XP</span>
                    <span className="font-bold text-violet-400 text-sm">{userStats.xp} XP</span>
                  </div>
                  <div>
                    <span className={`text-[10px] block font-sans ${isLight ? 'text-slate-400' : 'text-white/30'}`}>Solved</span>
                    <span className="font-bold text-emerald-400 text-sm">{userStats.solvedCount}</span>
                  </div>
                  <div>
                    <span className={`text-[10px] block font-sans ${isLight ? 'text-slate-400' : 'text-white/30'}`}>Streak</span>
                    <span className="font-bold text-amber-400 text-sm">{userStats.streak} 🔥</span>
                  </div>
                </div>
              </div>

              {/* ── Top 3 Podium Cards ── */}
              <div className="grid grid-cols-1 sm:grid-cols-3 gap-3">
                {sortedLeaders.slice(0, 3).map((leader, i) => {
                  const placeColors = [
                    { medal: '🥇', border: 'border-amber-500/40', glow: 'from-amber-500/20 to-transparent', ring: 'border-amber-400' },
                    { medal: '🥈', border: 'border-slate-400/30', glow: 'from-slate-400/15 to-transparent', ring: 'border-slate-300' },
                    { medal: '🥉', border: 'border-amber-700/30', glow: 'from-amber-700/15 to-transparent', ring: 'border-amber-600' },
                  ]
                  const cfg = placeColors[i]

                  return (
                    <div
                      key={leader.rank}
                      className={`relative p-4 rounded-xl border bg-gradient-to-b ${cfg.glow} ${cfg.border} flex flex-col items-center text-center transition-all hover:scale-[1.02] ${
                        isLight ? 'bg-white shadow-sm' : 'bg-white/[0.02]'
                      }`}
                    >
                      <span className="absolute top-2.5 right-3 text-xl">{cfg.medal}</span>
                      <div className={`w-12 h-12 rounded-full border-2 ${cfg.ring} flex items-center justify-center text-2xl mb-2 bg-black/20 shadow-lg`}>
                        {leader.avatar}
                      </div>

                      <h4 className="font-bold text-sm tracking-tight">{leader.name}</h4>
                      <p className={`text-[10px] mb-2 font-mono ${isLight ? 'text-slate-500' : 'text-white/40'}`}>{leader.college}</p>

                      <div className="flex items-center gap-2 mb-3">
                        <span className="px-2 py-0.5 rounded text-[10px] font-bold bg-amber-500/15 text-amber-400 border border-amber-500/20">
                          {leader.xp} XP
                        </span>
                        <span className="px-2 py-0.5 rounded text-[10px] font-bold bg-emerald-500/15 text-emerald-400 border border-emerald-500/20">
                          {leader.solved} Solved
                        </span>
                      </div>

                      <div className={`w-full pt-2 border-t flex justify-between text-[10px] font-mono ${
                        isLight ? 'border-slate-200 text-slate-500' : 'border-white/8 text-white/40'
                      }`}>
                        <span>Streak: {leader.streak}d 🔥</span>
                        <span>{leader.tier}</span>
                      </div>
                    </div>
                  )
                })}
              </div>

              {/* ── Full Rankings Table ── */}
              <div className={`rounded-xl border overflow-hidden ${
                isLight ? 'border-slate-200 bg-white shadow-sm' : 'border-white/8 bg-white/[0.015]'
              }`}>
                <div className={`grid grid-cols-12 px-4 py-2.5 border-b text-[11px] font-semibold uppercase tracking-wider ${
                  isLight ? 'bg-slate-100 border-slate-200 text-slate-600' : 'bg-white/5 border-white/8 text-white/40'
                }`}>
                  <span className="col-span-1 text-center">#</span>
                  <span className="col-span-5">Engineer & Campus</span>
                  <span className="col-span-2 text-center">Tier</span>
                  <span className="col-span-2 text-center">Solved</span>
                  <span className="col-span-2 text-right">XP Points</span>
                </div>

                <div className="divide-y divide-white/5 text-xs">
                  {sortedLeaders.map((item) => {
                    const tier = TIER_CONFIG[item.tier] || TIER_CONFIG.Contender

                    return (
                      <div
                        key={item.rank}
                        className={`grid grid-cols-12 px-4 py-3 items-center transition-colors ${
                          isLight ? 'hover:bg-slate-50' : 'hover:bg-white/[0.025]'
                        }`}
                      >
                        <span className="col-span-1 text-center font-mono font-bold text-white/50">
                          {item.rank <= 3 ? (item.rank === 1 ? '🥇' : item.rank === 2 ? '🥈' : '🥉') : `#${item.rank}`}
                        </span>

                        <div className="col-span-5 flex items-center gap-2.5 min-w-0">
                          <span className="text-base shrink-0">{item.avatar}</span>
                          <div className="min-w-0">
                            <p className="font-semibold truncate leading-tight">{item.name}</p>
                            <p className={`text-[10px] truncate ${isLight ? 'text-slate-400' : 'text-white/35'}`}>
                              {item.college} · {item.handle}
                            </p>
                          </div>
                        </div>

                        <div className="col-span-2 text-center">
                          <span className={`inline-flex items-center gap-1 px-2 py-0.5 rounded text-[10px] font-semibold border ${tier.bg} ${tier.border} ${tier.color}`}>
                            {tier.icon} {tier.label}
                          </span>
                        </div>

                        <div className="col-span-2 text-center font-mono font-semibold">
                          <span className="text-emerald-400">{item.solved}</span>
                          <span className={`text-[10px] ml-1 font-sans ${isLight ? 'text-slate-400' : 'text-white/30'}`}>
                            ({item.streak}d 🔥)
                          </span>
                        </div>

                        <div className="col-span-2 text-right font-mono font-bold text-violet-400">
                          {item.xp}
                        </div>
                      </div>
                    )
                  })}
                </div>
              </div>
            </div>
          )}

          {/* ================= TAB 2: WEEKLY CONTEST ================= */}
          {activeTab === 'contest' && (
            <div className="space-y-5">
              {/* Contest Hero Banner */}
              <div className={`p-6 rounded-2xl border relative overflow-hidden ${
                isLight
                  ? 'bg-gradient-to-r from-amber-50 via-white to-violet-50 border-amber-200 text-slate-800'
                  : 'bg-gradient-to-r from-amber-950/30 via-violet-950/30 to-black border-amber-500/30 text-white'
              }`}>
                <div className="flex flex-col md:flex-row items-start md:items-center justify-between gap-4">
                  <div>
                    <div className="flex items-center gap-2 mb-2">
                      <span className="px-2.5 py-0.5 rounded-full text-xs font-bold bg-red-500/20 border border-red-500/30 text-red-400 flex items-center gap-1">
                        <span className="w-1.5 h-1.5 rounded-full bg-red-400 animate-ping" />
                        LIVE ROUND
                      </span>
                      <span className="text-xs text-amber-400 font-mono font-bold">
                        Weekly Algorithmic Clash #48
                      </span>
                    </div>

                    <h3 className="text-lg font-bold mb-1">
                      FAANG & Unicorn Mock Assessment Sprint
                    </h3>
                    <p className={`text-xs max-w-lg leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/60'}`}>
                      Solve 3 algorithmic problems under 90 minutes with zero hints. Pass all edge-cases to climb the national leaderboard and earn contest badges!
                    </p>
                  </div>

                  <div className="shrink-0 flex flex-col items-center sm:items-end gap-2">
                    <div className="flex items-center gap-1.5 text-xs font-mono bg-black/30 px-3 py-1.5 rounded-lg border border-white/10">
                      <Clock size={13} className="text-amber-400" />
                      <span>Closes in: 01h : 28m : 14s</span>
                    </div>

                    <button
                      onClick={() => {
                        onClose()
                        navigate('/dsa/1')
                      }}
                      className="px-5 py-2.5 rounded-xl font-bold text-xs bg-gradient-to-r from-amber-500 via-orange-500 to-amber-600 text-slate-950 shadow-lg shadow-amber-500/25 hover:scale-105 active:scale-95 transition-all flex items-center gap-2"
                    >
                      <Zap size={14} />
                      <span>Enter Live Contest</span>
                      <ArrowUpRight size={13} />
                    </button>
                  </div>
                </div>
              </div>

              {/* 3 Contest Problems List */}
              <div className="space-y-2.5">
                <h4 className="text-xs font-bold uppercase tracking-wider text-white/50 flex items-center gap-2">
                  <Target size={14} />
                  Contest Problem Set (3 Challenges · 850 Max Points)
                </h4>

                {[
                  { id: 1, title: 'Two Sum & Complement Hashing', diff: 'Easy', pts: 100, topic: 'Arrays', solvedPct: '78%' },
                  { id: 3, title: 'Longest Substring Without Repeating Characters', diff: 'Medium', pts: 250, topic: 'Strings', solvedPct: '42%' },
                  { id: 10, title: 'Median of Two Sorted Arrays', diff: 'Hard', pts: 500, topic: 'Binary Search', solvedPct: '16%' },
                ].map((q, idx) => (
                  <div
                    key={q.id}
                    onClick={() => {
                      onClose()
                      navigate(`/dsa/${q.id}`)
                    }}
                    className={`p-3.5 rounded-xl border flex items-center justify-between gap-3 cursor-pointer transition-all hover:translate-x-1 ${
                      isLight ? 'bg-white border-slate-200 hover:border-violet-300' : 'bg-white/[0.025] border-white/8 hover:border-violet-500/30'
                    }`}
                  >
                    <div className="flex items-center gap-3 min-w-0">
                      <span className="w-6 h-6 rounded-full bg-white/5 border border-white/10 flex items-center justify-center text-xs font-mono font-bold shrink-0">
                        Q{idx + 1}
                      </span>
                      <div>
                        <h5 className="font-semibold text-xs truncate hover:text-violet-400">{q.title}</h5>
                        <p className={`text-[10px] ${isLight ? 'text-slate-400' : 'text-white/40'}`}>
                          {q.topic} · Pass rate: {q.solvedPct}
                        </p>
                      </div>
                    </div>

                    <div className="flex items-center gap-3 shrink-0">
                      <span className={`px-2 py-0.5 rounded text-[10px] font-bold ${
                        q.diff === 'Easy' ? 'text-emerald-400 bg-emerald-500/10' : q.diff === 'Medium' ? 'text-amber-400 bg-amber-500/10' : 'text-red-400 bg-red-500/10'
                      }`}>
                        {q.diff}
                      </span>
                      <span className="font-mono text-xs font-bold text-amber-400">
                        +{q.pts} pts
                      </span>
                      <ChevronRight size={14} className="text-white/30" />
                    </div>
                  </div>
                ))}
              </div>

              {/* Contest Rules & Scorecard Info */}
              <div className={`p-4 rounded-xl border text-xs leading-relaxed ${
                isLight ? 'bg-slate-50 border-slate-200 text-slate-700' : 'bg-black/30 border-white/8 text-white/70'
              }`}>
                <h5 className="font-bold mb-2 flex items-center gap-1.5 text-amber-400">
                  <Shield size={13} />
                  Contest Scoring & Fair Play Rules:
                </h5>
                <ul className="list-disc list-inside space-y-1 text-[11px]">
                  <li>Score is determined by total points earned + time taken to solve.</li>
                  <li>Penalty: Each failed code execution adds <strong>10 penalty minutes</strong> to your submission timestamp.</li>
                  <li>In-browser Python 3.11 Pyodide sandbox ensures 100% deterministic test-case validation.</li>
                </ul>
              </div>
            </div>
          )}
        </div>
      </div>
    </div>
  )
}

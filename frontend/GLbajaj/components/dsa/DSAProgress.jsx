import React from 'react'
import { CheckCircle2, Circle, Zap, Trophy, Target, TrendingUp } from 'lucide-react'
import { dsaProblems } from '../../data/dsaProblems'

function ProgressRing({ value, max, size = 56, strokeWidth = 5, color = '#7c3aed' }) {
  const radius = (size - strokeWidth) / 2
  const circumference = radius * 2 * Math.PI
  const progress = max > 0 ? (value / max) : 0
  const strokeDashoffset = circumference - progress * circumference

  return (
    <svg width={size} height={size} className="-rotate-90">
      <circle
        cx={size / 2}
        cy={size / 2}
        r={radius}
        strokeWidth={strokeWidth}
        stroke="rgba(255,255,255,0.06)"
        fill="transparent"
      />
      <circle
        cx={size / 2}
        cy={size / 2}
        r={radius}
        strokeWidth={strokeWidth}
        stroke={color}
        fill="transparent"
        strokeDasharray={circumference}
        strokeDashoffset={strokeDashoffset}
        strokeLinecap="round"
        style={{ transition: 'stroke-dashoffset 0.6s ease' }}
      />
    </svg>
  )
}

export default function DSAProgress({ solved = [], attempted = [] }) {
  const total = dsaProblems.length
  const easy = dsaProblems.filter(p => p.difficulty === 'Easy')
  const medium = dsaProblems.filter(p => p.difficulty === 'Medium')
  const hard = dsaProblems.filter(p => p.difficulty === 'Hard')

  const solvedSet = new Set(solved)

  const solvedEasy = easy.filter(p => solvedSet.has(p.id)).length
  const solvedMedium = medium.filter(p => solvedSet.has(p.id)).length
  const solvedHard = hard.filter(p => solvedSet.has(p.id)).length
  const totalSolved = solved.length

  // Topic breakdown
  const topics = [...new Set(dsaProblems.map(p => p.topic))]
  const topicStats = topics.map(t => {
    const topicProblems = dsaProblems.filter(p => p.topic === t)
    const topicSolved = topicProblems.filter(p => solvedSet.has(p.id)).length
    return { topic: t, total: topicProblems.length, solved: topicSolved }
  }).filter(t => t.total > 0)

  return (
    <div className="space-y-4">
      {/* Overall Progress */}
      <div className="bg-white/3 border border-white/8 rounded-xl p-4">
        <div className="flex items-center justify-between mb-3">
          <h3 className="text-white/70 text-xs font-semibold uppercase tracking-wider">Overall Progress</h3>
          <div className="flex items-center gap-1.5">
            <Trophy size={13} className="text-yellow-400" />
            <span className="text-white font-bold text-sm">{totalSolved}</span>
            <span className="text-white/30 text-xs">/ {total}</span>
          </div>
        </div>

        <div className="w-full bg-white/5 rounded-full h-1.5 mb-3">
          <div
            className="h-1.5 rounded-full bg-gradient-to-r from-violet-500 to-cyan-500 transition-all duration-700"
            style={{ width: `${total > 0 ? (totalSolved / total) * 100 : 0}%` }}
          />
        </div>

        <div className="grid grid-cols-3 gap-2">
          {/* Easy */}
          <div className="flex flex-col items-center gap-1.5 relative">
            <div className="relative">
              <ProgressRing value={solvedEasy} max={easy.length} size={52} color="#10b981" />
              <div className="absolute inset-0 flex items-center justify-center">
                <span className="text-emerald-400 text-xs font-bold">{solvedEasy}</span>
              </div>
            </div>
            <div className="text-center">
              <p className="text-emerald-400 text-xs font-semibold">Easy</p>
              <p className="text-white/30 text-[10px]">{easy.length} total</p>
            </div>
          </div>

          {/* Medium */}
          <div className="flex flex-col items-center gap-1.5">
            <div className="relative">
              <ProgressRing value={solvedMedium} max={medium.length} size={52} color="#f59e0b" />
              <div className="absolute inset-0 flex items-center justify-center">
                <span className="text-amber-400 text-xs font-bold">{solvedMedium}</span>
              </div>
            </div>
            <div className="text-center">
              <p className="text-amber-400 text-xs font-semibold">Medium</p>
              <p className="text-white/30 text-[10px]">{medium.length} total</p>
            </div>
          </div>

          {/* Hard */}
          <div className="flex flex-col items-center gap-1.5">
            <div className="relative">
              <ProgressRing value={solvedHard} max={hard.length} size={52} color="#ef4444" />
              <div className="absolute inset-0 flex items-center justify-center">
                <span className="text-red-400 text-xs font-bold">{solvedHard}</span>
              </div>
            </div>
            <div className="text-center">
              <p className="text-red-400 text-xs font-semibold">Hard</p>
              <p className="text-white/30 text-[10px]">{hard.length} total</p>
            </div>
          </div>
        </div>
      </div>

      {/* Topic Breakdown */}
      <div className="bg-white/3 border border-white/8 rounded-xl p-4">
        <h3 className="text-white/70 text-xs font-semibold uppercase tracking-wider mb-3 flex items-center gap-2">
          <Target size={12} className="text-cyan-400" />
          By Topic
        </h3>
        <div className="space-y-2">
          {topicStats.map(({ topic, total: t, solved: s }) => (
            <div key={topic}>
              <div className="flex items-center justify-between mb-0.5">
                <span className="text-white/60 text-xs">{topic}</span>
                <span className="text-white/40 text-xs font-mono">{s}/{t}</span>
              </div>
              <div className="w-full bg-white/5 rounded-full h-1">
                <div
                  className="h-1 rounded-full bg-gradient-to-r from-violet-500/70 to-cyan-500/70 transition-all duration-500"
                  style={{ width: `${t > 0 ? (s / t) * 100 : 0}%` }}
                />
              </div>
            </div>
          ))}
        </div>
      </div>
    </div>
  )
}

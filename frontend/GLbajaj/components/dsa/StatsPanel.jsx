import React, { useMemo } from 'react'
import { BarChart3, Trophy, Flame, Zap, Target, TrendingUp, Calendar } from 'lucide-react'
import { dsaProblems } from '../../data/dsaProblems'
import { getLevel, getStreak, getRecentActivity, getTopicStats, LEVELS } from '../../utils/dsaStats'

// Mini bar for topic
function TopicBar({ topic, solved, total, isLight }) {
  const pct = total > 0 ? Math.round((solved / total) * 100) : 0
  return (
    <div className="flex items-center gap-2">
      <span className={`text-[11px] w-28 truncate shrink-0 ${isLight ? 'text-slate-600 font-medium' : 'text-white/40'}`}>{topic}</span>
      <div className={`flex-1 rounded-full h-1.5 relative ${isLight ? 'bg-slate-200' : 'bg-white/5'}`}>
        <div
          className="h-1.5 rounded-full bg-gradient-to-r from-violet-500 to-cyan-500 transition-all duration-700"
          style={{ width: `${pct}%` }}
        />
      </div>
      <span className={`text-[10px] font-mono w-10 text-right shrink-0 ${isLight ? 'text-slate-500 font-semibold' : 'text-white/30'}`}>{solved}/{total}</span>
    </div>
  )
}

// Activity calendar (30 days)
function ActivityCalendar({ activity, isLight }) {
  const intensity = (count) => {
    if (count === 0) return isLight ? 'bg-slate-200' : 'bg-white/5'
    if (count === 1) return 'bg-violet-400'
    if (count === 2) return 'bg-violet-600'
    return 'bg-violet-700'
  }

  return (
    <div className="flex flex-wrap gap-1">
      {activity.map((day, i) => (
        <div
          key={i}
          title={`${day.date}: ${day.count} solved`}
          className={`w-3.5 h-3.5 rounded-sm ${intensity(day.count)} transition-colors`}
        />
      ))}
    </div>
  )
}

export default function StatsPanel({ solved = [], isLight = false }) {
  const xp = useMemo(() => {
    // Compute XP from solved problems
    const XP_MAP = { Easy: 10, Medium: 25, Hard: 50 }
    return solved.reduce((acc, id) => {
      const p = dsaProblems.find(x => x.id === id)
      return acc + (p ? (XP_MAP[p.difficulty] || 10) : 10)
    }, 0)
  }, [solved])

  const level = useMemo(() => getLevel(xp), [xp])
  const streak = getStreak()
  const activity = getRecentActivity(30)
  const topicStats = useMemo(() => getTopicStats(solved, dsaProblems), [solved])

  const nextLevelXP = level.nextLevel ? level.nextLevel.min - level.min : 0
  const currentLevelXP = xp - level.min
  const progressPct = level.progressInLevel

  const easyS = solved.filter(id => dsaProblems.find(p => p.id === id)?.difficulty === 'Easy').length
  const medS  = solved.filter(id => dsaProblems.find(p => p.id === id)?.difficulty === 'Medium').length
  const hardS = solved.filter(id => dsaProblems.find(p => p.id === id)?.difficulty === 'Hard').length

  return (
    <div className="space-y-4">

      {/* Level Card */}
      <div className={`border rounded-xl p-4 transition-colors ${
        isLight
          ? 'bg-white border-slate-200/90 shadow-sm text-slate-800'
          : 'bg-gradient-to-br from-violet-600/10 to-cyan-600/10 border-violet-500/20 text-white'
      }`}>
        <div className="flex items-center justify-between mb-3">
          <div className="flex items-center gap-2">
            <span className="text-xl">{level.icon}</span>
            <div>
              <p className={`text-sm font-bold ${isLight ? 'text-slate-900' : 'text-white/90'}`}>{level.name}</p>
              <p className={`text-[10px] font-mono ${isLight ? 'text-slate-500' : 'text-white/35'}`}>{xp} XP total</p>
            </div>
          </div>
          <div className="text-right">
            <p className={`text-xs font-mono font-bold ${isLight ? 'text-violet-700 bg-violet-50 px-2 py-0.5 rounded border border-violet-200' : 'text-violet-300'}`}>
              Lv. {LEVELS.indexOf(level) + 1}
            </p>
          </div>
        </div>
        {/* XP Bar */}
        <div className={`w-full rounded-full h-1.5 mb-1 ${isLight ? 'bg-slate-200' : 'bg-white/5'}`}>
          <div
            className="h-1.5 rounded-full bg-gradient-to-r from-violet-500 to-cyan-500 transition-all duration-700"
            style={{ width: `${progressPct}%` }}
          />
        </div>
        {level.nextLevel ? (
          <p className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/25'}`}>
            {currentLevelXP} / {nextLevelXP} XP to {level.nextLevel.icon} {level.nextLevel.name}
          </p>
        ) : (
          <p className="text-amber-500 text-[10px] font-bold">👑 Max level reached!</p>
        )}
      </div>

      {/* Quick Stats */}
      <div className="grid grid-cols-2 gap-2">
        <div className={`border rounded-xl p-3 text-center ${
          isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
        }`}>
          <Flame size={16} className="text-amber-500 mx-auto mb-1" />
          <p className={`font-bold text-lg ${isLight ? 'text-slate-900' : 'text-white'}`}>{streak}</p>
          <p className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/35'}`}>Day Streak</p>
        </div>
        <div className={`border rounded-xl p-3 text-center ${
          isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
        }`}>
          <Zap size={16} className="text-violet-600 mx-auto mb-1" />
          <p className={`font-bold text-lg ${isLight ? 'text-slate-900' : 'text-white'}`}>{xp}</p>
          <p className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/35'}`}>Total XP</p>
        </div>
        <div className={`border rounded-xl p-3 text-center ${
          isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
        }`}>
          <Trophy size={16} className="text-emerald-600 mx-auto mb-1" />
          <p className={`font-bold text-lg ${isLight ? 'text-slate-900' : 'text-white'}`}>{solved.length}</p>
          <p className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/35'}`}>Solved</p>
        </div>
        <div className={`border rounded-xl p-3 text-center ${
          isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
        }`}>
          <Target size={16} className="text-rose-600 mx-auto mb-1" />
          <p className={`font-bold text-lg ${isLight ? 'text-slate-900' : 'text-white'}`}>{hardS}</p>
          <p className={`text-[10px] ${isLight ? 'text-slate-500 font-medium' : 'text-white/35'}`}>Hard Solved</p>
        </div>
      </div>

      {/* Difficulty Breakdown */}
      <div className={`border rounded-xl p-3.5 ${
        isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
      }`}>
        <p className={`text-[10px] font-bold uppercase tracking-wider mb-3 ${
          isLight ? 'text-slate-700' : 'text-white/40'
        }`}>
          Difficulty Breakdown
        </p>
        <div className="space-y-2">
          {[
            { label: 'Easy', solved: easyS, total: dsaProblems.filter(p => p.difficulty === 'Easy').length, color: 'from-emerald-500 to-emerald-400' },
            { label: 'Medium', solved: medS, total: dsaProblems.filter(p => p.difficulty === 'Medium').length, color: 'from-amber-500 to-amber-400' },
            { label: 'Hard', solved: hardS, total: dsaProblems.filter(p => p.difficulty === 'Hard').length, color: 'from-red-500 to-red-400' },
          ].map(d => (
            <div key={d.label} className="flex items-center gap-2">
              <span className={`text-[11px] w-12 shrink-0 ${isLight ? 'text-slate-600 font-medium' : 'text-white/40'}`}>{d.label}</span>
              <div className={`flex-1 rounded-full h-1.5 ${isLight ? 'bg-slate-200' : 'bg-white/5'}`}>
                <div
                  className={`h-1.5 rounded-full bg-gradient-to-r ${d.color} transition-all duration-700`}
                  style={{ width: `${d.total > 0 ? (d.solved / d.total) * 100 : 0}%` }}
                />
              </div>
              <span className={`text-[10px] font-mono w-10 text-right shrink-0 ${isLight ? 'text-slate-500 font-semibold' : 'text-white/30'}`}>{d.solved}/{d.total}</span>
            </div>
          ))}
        </div>
      </div>

      {/* Topic Progress */}
      <div className={`border rounded-xl p-3.5 ${
        isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
      }`}>
        <div className="flex items-center gap-1.5 mb-3">
          <TrendingUp size={12} className={isLight ? 'text-violet-600' : 'text-violet-400'} />
          <p className={`text-[10px] font-bold uppercase tracking-wider ${isLight ? 'text-slate-700' : 'text-white/40'}`}>Topic Progress</p>
        </div>
        <div className="space-y-2">
          {topicStats.slice(0, 8).map(t => (
            <TopicBar key={t.topic} topic={t.topic} solved={t.solved} total={t.total} isLight={isLight} />
          ))}
        </div>
      </div>

      {/* Activity Calendar */}
      <div className={`border rounded-xl p-3.5 ${
        isLight ? 'bg-white border-slate-200/90 shadow-sm' : 'bg-white/3 border-white/8'
      }`}>
        <div className="flex items-center gap-1.5 mb-3">
          <Calendar size={12} className={isLight ? 'text-cyan-600' : 'text-cyan-400'} />
          <p className={`text-[10px] font-bold uppercase tracking-wider ${isLight ? 'text-slate-700' : 'text-white/40'}`}>Last 30 Days</p>
        </div>
        <ActivityCalendar activity={activity} isLight={isLight} />
        <div className="flex items-center gap-2 mt-2">
          <span className={`text-[10px] ${isLight ? 'text-slate-400' : 'text-white/20'}`}>Less</span>
          {[
            isLight ? 'bg-slate-200' : 'bg-white/5',
            'bg-violet-400',
            'bg-violet-600',
            'bg-violet-700'
          ].map((c, i) => (
            <div key={i} className={`w-3 h-3 rounded-sm ${c}`} />
          ))}
          <span className={`text-[10px] ${isLight ? 'text-slate-400' : 'text-white/20'}`}>More</span>
        </div>
      </div>

    </div>
  )
}

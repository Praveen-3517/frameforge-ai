import React from 'react'
import { Link } from 'react-router-dom'
import { CheckCircle2, Circle, Bookmark, BookmarkCheck, ChevronRight, Tag, Zap } from 'lucide-react'

export default function ProblemCard({ problem, isSolved, isBookmarked, onBookmark, isLight = false }) {
  // Difficulty styling
  const diffConfig = {
    Easy: {
      label: 'Easy',
      badge: isLight
        ? 'bg-emerald-100 border-emerald-300 text-emerald-800'
        : 'bg-emerald-500/10 border-emerald-500/20 text-emerald-400',
      dot: isLight ? 'bg-emerald-600' : 'bg-emerald-400',
    },
    Medium: {
      label: 'Medium',
      badge: isLight
        ? 'bg-amber-100 border-amber-300 text-amber-900'
        : 'bg-amber-500/10 border-amber-500/20 text-amber-400',
      dot: isLight ? 'bg-amber-600' : 'bg-amber-400',
    },
    Hard: {
      label: 'Hard',
      badge: isLight
        ? 'bg-rose-100 border-rose-300 text-rose-800'
        : 'bg-red-500/10 border-red-500/20 text-red-400',
      dot: isLight ? 'bg-rose-600' : 'bg-red-400',
    },
  }

  const phaseConfig = {
    1: {
      label: 'Basic',
      badge: isLight
        ? 'bg-sky-100 border-sky-300 text-sky-800'
        : 'bg-sky-500/10 border-sky-500/20 text-sky-400',
    },
    2: {
      label: 'Intermediate',
      badge: isLight
        ? 'bg-violet-100 border-violet-300 text-violet-800'
        : 'bg-violet-500/10 border-violet-500/20 text-violet-400',
    },
    3: {
      label: 'Advanced',
      badge: isLight
        ? 'bg-pink-100 border-pink-300 text-pink-800'
        : 'bg-pink-500/10 border-pink-500/20 text-pink-400',
    },
  }

  const diff = diffConfig[problem.difficulty] || diffConfig.Easy
  const phase = phaseConfig[problem.phase] || phaseConfig[1]

  return (
    <div
      className={`group relative flex items-center gap-3 px-4 py-3.5 rounded-xl border transition-all duration-200 cursor-pointer ${
        isLight
          ? isSolved
            ? 'bg-emerald-50/70 border-emerald-300 shadow-sm'
            : 'bg-white border-slate-200/90 hover:border-violet-400 hover:shadow-md shadow-sm'
          : isSolved
            ? 'bg-emerald-500/5 border-emerald-500/15 hover:border-emerald-500/30'
            : 'bg-white/2 border-white/8 hover:bg-white/4 hover:border-violet-500/30'
      }`}
    >
      {/* Solved indicator */}
      <div className="shrink-0">
        {isSolved ? (
          <CheckCircle2 size={18} className={isLight ? 'text-emerald-600' : 'text-emerald-400'} />
        ) : (
          <Circle size={18} className={`${isLight ? 'text-slate-300 group-hover:text-slate-400' : 'text-white/15 group-hover:text-white/30'} transition-colors`} />
        )}
      </div>

      {/* Main content */}
      <Link
        to={`/dsa/${problem.id}`}
        className="flex-1 min-w-0 flex flex-col gap-1.5"
      >
        <div className="flex items-center gap-2 flex-wrap">
          <span className={`text-sm font-semibold transition-colors ${
            isLight
              ? isSolved ? 'text-slate-500 line-through' : 'text-slate-900 group-hover:text-violet-700 font-bold'
              : isSolved ? 'text-white/60' : 'text-white/90 group-hover:text-white'
          }`}>
            {problem.id}. {problem.title}
          </span>
        </div>

        <div className="flex items-center gap-2 flex-wrap">
          {/* Difficulty badge */}
          <span className={`inline-flex items-center gap-1 px-2 py-0.5 rounded-full text-[10px] font-semibold border ${diff.badge}`}>
            <span className={`w-1.5 h-1.5 rounded-full ${diff.dot}`} />
            {diff.label}
          </span>

          {/* Phase badge */}
          <span className={`px-2 py-0.5 rounded-full text-[10px] font-semibold border ${phase.badge}`}>
            {phase.label}
          </span>

          {/* Topic badge */}
          <span className={`px-2 py-0.5 rounded-full text-[10px] font-medium border ${
            isLight
              ? 'bg-slate-100 border-slate-300 text-slate-700'
              : 'bg-white/5 border-white/8 text-white/40'
          }`}>
            {problem.topic}
          </span>

          {/* Pattern tag */}
          <span className={`hidden sm:inline-flex items-center gap-1 text-[10px] font-medium ${
            isLight ? 'text-slate-500' : 'text-white/35'
          }`}>
            <Tag size={9} />
            {problem.pattern}
          </span>
        </div>
      </Link>

      {/* Bookmark */}
      <button
        onClick={(e) => { e.preventDefault(); onBookmark(problem.id) }}
        className={`shrink-0 p-1.5 rounded-lg transition-all opacity-0 group-hover:opacity-100 ${
          isLight ? 'hover:bg-slate-100 text-slate-400 hover:text-slate-700' : 'hover:bg-white/8 text-white/30'
        }`}
        title={isBookmarked ? 'Remove bookmark' : 'Bookmark'}
      >
        {isBookmarked ? (
          <BookmarkCheck size={15} className={isLight ? 'text-violet-600' : 'text-violet-400'} />
        ) : (
          <Bookmark size={15} />
        )}
      </button>

      {/* Arrow */}
      <Link to={`/dsa/${problem.id}`} className="shrink-0">
        <ChevronRight
          size={18}
          className={`${
            isLight
              ? 'text-slate-400 group-hover:text-violet-600 group-hover:translate-x-0.5'
              : 'text-white/15 group-hover:text-violet-400 group-hover:translate-x-0.5'
          } transition-all duration-200`}
        />
      </Link>
    </div>
  )
}

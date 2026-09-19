import React from 'react'
import { Lightbulb, ChevronRight, Code2, Clock, Database, Lock } from 'lucide-react'
import { useAuth } from '../../context/AuthContext'

export default function HintPanel({ problem, hintsRevealed, onRevealHint, isLight = false }) {
  const { user, openAuthModal } = useAuth()
  const totalHints = problem.hints?.length || 0

  const handleUnlockHint = (idx) => {
    if (!user) {
      openAuthModal('signup')
      return
    }
    onRevealHint(idx + 1)
  }

  return (
    <div className="space-y-4">
      {/* Hints Section */}
      <div>
        <h3 className={`text-xs font-bold uppercase tracking-wider mb-2.5 flex items-center gap-2 ${
          isLight ? 'text-slate-800' : 'text-white/70'
        }`}>
          <Lightbulb size={14} className={isLight ? 'text-amber-500' : 'text-yellow-400'} />
          <span>Progressive Hints ({hintsRevealed}/{totalHints})</span>
        </h3>

        <div className="space-y-2.5">
          {problem.hints?.map((hint, idx) => (
            <div key={idx}>
              {hintsRevealed > idx ? (
                <div className={`rounded-xl p-3.5 border transition-all animate-fadeIn ${
                  isLight
                    ? 'bg-amber-50/90 border-amber-300 shadow-sm text-slate-900'
                    : 'bg-yellow-500/10 border-yellow-500/25 text-white'
                }`}>
                  <div className="flex items-start gap-2.5">
                    <span className={`px-2 py-0.5 rounded text-xs font-black shrink-0 mt-0.5 ${
                      isLight
                        ? 'bg-amber-500 text-slate-950 shadow-sm'
                        : 'bg-yellow-400/20 text-yellow-300 border border-yellow-400/30'
                    }`}>
                      #{idx + 1}
                    </span>
                    <p className={`text-sm leading-relaxed font-medium ${
                      isLight ? 'text-slate-900' : 'text-yellow-100/90'
                    }`}>
                      {hint}
                    </p>
                  </div>
                </div>
              ) : (
                <button
                  onClick={() => handleUnlockHint(idx)}
                  disabled={user ? hintsRevealed < idx : false}
                  className={`w-full text-left px-3.5 py-3 rounded-xl border text-xs font-bold transition-all duration-200 flex items-center gap-2.5 cursor-pointer ${
                    !user
                      ? isLight
                        ? 'border-amber-400 bg-amber-50 text-amber-950 hover:bg-amber-100 shadow-sm'
                        : 'border-yellow-500/40 text-yellow-300 bg-yellow-500/15 hover:bg-yellow-500/25'
                      : hintsRevealed < idx
                      ? isLight
                        ? 'border-slate-200 text-slate-400 bg-slate-100/70 cursor-not-allowed'
                        : 'border-white/5 text-white/20 cursor-not-allowed bg-white/2'
                      : isLight
                      ? 'border-amber-400 bg-amber-100/70 text-amber-950 hover:bg-amber-100 hover:border-amber-500 shadow-sm active:scale-[0.99]'
                      : 'border-yellow-500/30 text-yellow-300 bg-yellow-500/10 hover:bg-yellow-500/20 hover:border-yellow-500/50'
                  }`}
                >
                  <Lightbulb size={14} className={hintsRevealed === idx || !user ? (isLight ? 'text-amber-600' : 'text-yellow-400') : 'opacity-40'} />
                  <span className="flex-1">
                    {!user ? `🔒 Sign Up to Unlock Hint #${idx + 1}` : hintsRevealed < idx ? `Hint #${idx + 1} (Unlock Hint #${idx} first)` : `Unlock Hint #${idx + 1}`}
                  </span>
                  {(hintsRevealed === idx || !user) && <ChevronRight size={14} className="ml-auto" />}
                </button>
              )}
            </div>
          ))}
        </div>
      </div>

      {/* Approach Section */}
      {hintsRevealed >= totalHints && problem.approach && (
        <div className={`rounded-xl p-4 border transition-all animate-fadeIn ${
          isLight
            ? 'bg-violet-50 border-violet-300 shadow-sm'
            : 'bg-violet-500/10 border-violet-500/25'
        }`}>
          <h4 className={`text-xs font-bold uppercase tracking-wider mb-2 flex items-center gap-1.5 ${
            isLight ? 'text-violet-900' : 'text-violet-300'
          }`}>
            <Code2 size={13} className={isLight ? 'text-violet-600' : 'text-violet-400'} />
            Solution Approach (दृष्टिकोण)
          </h4>
          <p className={`text-sm leading-relaxed font-medium ${
            isLight ? 'text-slate-900' : 'text-violet-100/90'
          }`}>
            {problem.approach}
          </p>
        </div>
      )}

      {/* Complexity */}
      {(problem.timeComplexity || problem.spaceComplexity) && (
        <div className="grid grid-cols-2 gap-2.5 pt-1">
          {problem.timeComplexity && (
            <div className={`rounded-xl p-3 border transition-all ${
              isLight
                ? 'bg-cyan-50/90 border-cyan-300 shadow-sm'
                : 'bg-white/3 border-white/8'
            }`}>
              <div className="flex items-center gap-1.5 mb-1">
                <Clock size={12} className={isLight ? 'text-cyan-700 font-bold' : 'text-cyan-400'} />
                <span className={`text-[11px] font-bold uppercase tracking-wider ${
                  isLight ? 'text-cyan-900' : 'text-white/40'
                }`}>
                  Time Complexity
                </span>
              </div>
              <p className={`text-sm font-mono font-black ${
                isLight ? 'text-cyan-950' : 'text-cyan-300'
              }`}>
                {problem.timeComplexity}
              </p>
            </div>
          )}

          {problem.spaceComplexity && (
            <div className={`rounded-xl p-3 border transition-all ${
              isLight
                ? 'bg-pink-50/90 border-pink-300 shadow-sm'
                : 'bg-white/3 border-white/8'
            }`}>
              <div className="flex items-center gap-1.5 mb-1">
                <Database size={12} className={isLight ? 'text-pink-700 font-bold' : 'text-pink-400'} />
                <span className={`text-[11px] font-bold uppercase tracking-wider ${
                  isLight ? 'text-pink-900' : 'text-white/40'
                }`}>
                  Space Complexity
                </span>
              </div>
              <p className={`text-sm font-mono font-black ${
                isLight ? 'text-pink-950' : 'text-pink-300'
              }`}>
                {problem.spaceComplexity}
              </p>
            </div>
          )}
        </div>
      )}
    </div>
  )
}

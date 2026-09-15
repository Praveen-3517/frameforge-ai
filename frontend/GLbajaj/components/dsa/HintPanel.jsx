import React from 'react'
import { Lightbulb, ChevronRight, Code2, Clock, Database } from 'lucide-react'

export default function HintPanel({ problem, hintsRevealed, onRevealHint }) {
  const totalHints = problem.hints?.length || 0

  return (
    <div className="space-y-3">
      {/* Hints Section */}
      <div>
        <h3 className="text-sm font-semibold text-white/70 uppercase tracking-wider mb-2 flex items-center gap-2">
          <Lightbulb size={14} className="text-yellow-400" />
          Hints
        </h3>

        <div className="space-y-2">
          {problem.hints?.map((hint, idx) => (
            <div key={idx}>
              {hintsRevealed > idx ? (
                <div className="bg-yellow-500/10 border border-yellow-500/20 rounded-lg p-3 animate-fadeIn">
                  <div className="flex items-start gap-2">
                    <span className="text-yellow-400 text-xs font-bold mt-0.5">#{idx + 1}</span>
                    <p className="text-yellow-200/80 text-sm leading-relaxed">{hint}</p>
                  </div>
                </div>
              ) : (
                <button
                  onClick={() => onRevealHint(idx + 1)}
                  disabled={hintsRevealed < idx}
                  className={`w-full text-left px-3 py-2.5 rounded-lg border text-sm font-medium transition-all duration-200 flex items-center gap-2 ${
                    hintsRevealed < idx
                      ? 'border-white/5 text-white/20 cursor-not-allowed bg-white/2'
                      : 'border-yellow-500/30 text-yellow-400 hover:bg-yellow-500/10 hover:border-yellow-500/50 cursor-pointer'
                  }`}
                >
                  <Lightbulb size={13} />
                  {hintsRevealed < idx ? `Hint ${idx + 1} (unlock hint ${idx} first)` : `Reveal Hint ${idx + 1}`}
                  {hintsRevealed === idx && <ChevronRight size={13} className="ml-auto" />}
                </button>
              )}
            </div>
          ))}
        </div>
      </div>

      {/* Approach Section */}
      {hintsRevealed >= totalHints && problem.approach && (
        <div className="bg-violet-500/10 border border-violet-500/25 rounded-lg p-3 animate-fadeIn">
          <h4 className="text-violet-300 text-xs font-semibold uppercase tracking-wider mb-2 flex items-center gap-1.5">
            <Code2 size={12} />
            Solution Approach
          </h4>
          <p className="text-violet-200/80 text-sm leading-relaxed">{problem.approach}</p>
        </div>
      )}

      {/* Complexity */}
      {(problem.timeComplexity || problem.spaceComplexity) && (
        <div className="grid grid-cols-2 gap-2 mt-3">
          {problem.timeComplexity && (
            <div className="bg-white/3 border border-white/8 rounded-lg p-2.5">
              <div className="flex items-center gap-1.5 mb-1">
                <Clock size={11} className="text-cyan-400" />
                <span className="text-white/40 text-xs uppercase tracking-wider">Time</span>
              </div>
              <p className="text-cyan-300 text-sm font-mono font-medium">{problem.timeComplexity}</p>
            </div>
          )}
          {problem.spaceComplexity && (
            <div className="bg-white/3 border border-white/8 rounded-lg p-2.5">
              <div className="flex items-center gap-1.5 mb-1">
                <Database size={11} className="text-pink-400" />
                <span className="text-white/40 text-xs uppercase tracking-wider">Space</span>
              </div>
              <p className="text-pink-300 text-sm font-mono font-medium">{problem.spaceComplexity}</p>
            </div>
          )}
        </div>
      )}
    </div>
  )
}

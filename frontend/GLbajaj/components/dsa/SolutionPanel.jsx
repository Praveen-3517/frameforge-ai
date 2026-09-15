import React, { useState } from 'react'
import {
  Lock, Unlock, Copy, Check, Play, BookOpen,
  Code2, Clock, Database, Sparkles, CheckCircle2,
  HelpCircle, ChevronRight, Languages
} from 'lucide-react'

export default function SolutionPanel({
  problem,
  interviewData,
  isLight = false,
  onLoadCodeIntoEditor
}) {
  const [unlocked, setUnlocked] = useState(false)
  const [solutionLang, setSolutionLang] = useState('en') // 'en' | 'hi'
  const [copied, setCopied] = useState(false)

  const solution = interviewData?.solution
  const isHindi = solutionLang === 'hi'
  const text = isHindi ? solution?.hi : solution?.en

  const handleCopy = () => {
    if (!solution?.code) return
    navigator.clipboard.writeText(solution.code).then(() => {
      setCopied(true)
      setTimeout(() => setCopied(false), 2000)
    })
  }

  // If user hasn't clicked "Unlock Solution" yet
  if (!unlocked) {
    return (
      <div className={`p-6 rounded-2xl border text-center transition-all ${
        isLight
          ? 'bg-gradient-to-b from-violet-50/70 via-white to-white border-violet-200 shadow-sm'
          : 'bg-gradient-to-b from-violet-500/[0.08] via-transparent to-transparent border-violet-500/20'
      }`}>
        <div className={`w-14 h-14 rounded-2xl mx-auto mb-4 flex items-center justify-center border shadow-lg ${
          isLight
            ? 'bg-violet-100 border-violet-300 text-violet-700 shadow-violet-200'
            : 'bg-violet-500/15 border-violet-500/30 text-violet-400 shadow-violet-500/20'
        }`}>
          <Lock size={26} />
        </div>

        <h3 className={`text-base font-bold mb-2 ${
          isLight ? 'text-slate-900' : 'text-white'
        }`}>
          Solution & Logic Locked (समाधान सुरक्षित)
        </h3>

        <p className={`text-xs leading-relaxed max-w-md mx-auto mb-5 ${
          isLight ? 'text-slate-600' : 'text-white/60'
        }`}>
          Real interviews me pehle khud try karna sabse zaroori hota hai.
          Agar aap 10-15 minute try kar chuke hain ya question ka logic samajh nahi aa raha, tabhi solution dekhein!
        </p>

        <div className="flex flex-col sm:flex-row items-center justify-center gap-3">
          <button
            onClick={() => setUnlocked(true)}
            className="w-full sm:w-auto px-6 py-2.5 rounded-xl font-bold text-xs flex items-center justify-center gap-2 bg-gradient-to-r from-violet-600 to-cyan-600 text-white shadow-lg shadow-violet-600/30 hover:scale-105 active:scale-95 transition-all"
          >
            <Unlock size={14} />
            <span>Reveal Solution & Logic / पूरा समाधान देखें</span>
          </button>
        </div>

        <p className={`text-[10px] mt-4 ${
          isLight ? 'text-slate-400' : 'text-white/30'
        }`}>
          Includes: Step-by-Step Intuition · Algorithm · Python Code · Time & Space Complexity (English & Hindi)
        </p>
      </div>
    )
  }

  // Once unlocked: Show full solution with English/Hindi toggle
  return (
    <div className="space-y-5 animate-fadeIn">
      {/* Header bar of Solution */}
      <div className={`flex items-center justify-between p-3 rounded-xl border ${
        isLight ? 'bg-violet-50/80 border-violet-200' : 'bg-violet-500/10 border-violet-500/20'
      }`}>
        <div className="flex items-center gap-2">
          <div className={`p-1.5 rounded-lg ${isLight ? 'bg-violet-200/80 text-violet-800' : 'bg-violet-500/20 text-violet-300'}`}>
            <Unlock size={14} />
          </div>
          <div>
            <h4 className={`text-xs font-bold ${isLight ? 'text-violet-950' : 'text-violet-200'}`}>
              Official Solution & Intuition
            </h4>
            <p className={`text-[10px] ${isLight ? 'text-violet-700' : 'text-violet-300/70'}`}>
              Optimal {problem.pattern} Approach
            </p>
          </div>
        </div>

        {/* English / Hindi Selector for Solution */}
        <div className={`flex items-center p-0.5 rounded-lg border text-xs font-semibold ${
          isLight ? 'bg-white border-slate-300' : 'bg-black/40 border-white/10'
        }`}>
          <button
            onClick={() => setSolutionLang('en')}
            className={`px-2 py-1 rounded-md transition-all ${
              !isHindi
                ? 'bg-violet-600 text-white shadow-sm'
                : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
            }`}
          >
            English
          </button>
          <button
            onClick={() => setSolutionLang('hi')}
            className={`px-2 py-1 rounded-md transition-all ${
              isHindi
                ? 'bg-amber-500 text-slate-950 font-bold shadow-sm'
                : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
            }`}
          >
            हिंदी
          </button>
        </div>
      </div>

      {/* 1. Intuition & Core Concept */}
      <div className={`p-4 rounded-xl border ${
        isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.025] border-white/8'
      }`}>
        <h4 className={`text-xs font-bold uppercase tracking-wider mb-2 flex items-center gap-1.5 ${
          isLight ? 'text-violet-700' : 'text-violet-300'
        }`}>
          <Sparkles size={13} />
          {isHindi ? 'सोचने का तरीका (Intuition & Thought Process)' : 'Intuition & Key Insight'}
        </h4>
        <p className={`text-sm leading-relaxed ${isLight ? 'text-slate-700' : 'text-white/80'}`}>
          {text?.intuition || problem.approach}
        </p>
      </div>

      {/* 2. Step-by-Step Algorithm */}
      {text?.steps && text.steps.length > 0 && (
        <div className={`p-4 rounded-xl border ${
          isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.025] border-white/8'
        }`}>
          <h4 className={`text-xs font-bold uppercase tracking-wider mb-3 flex items-center gap-1.5 ${
            isLight ? 'text-cyan-700' : 'text-cyan-300'
          }`}>
            <CheckCircle2 size={13} />
            {isHindi ? 'कदम-दर-कदम एल्गोरिदम (Step-by-Step Algorithm)' : 'Step-by-Step Algorithm'}
          </h4>
          <div className="space-y-2.5">
            {text.steps.map((step, idx) => (
              <div key={idx} className="flex items-start gap-2.5 text-xs">
                <span className={`w-5 h-5 rounded-full flex items-center justify-center font-mono font-bold shrink-0 text-[10px] mt-0.5 ${
                  isLight ? 'bg-cyan-100 text-cyan-800' : 'bg-cyan-500/20 text-cyan-300'
                }`}>
                  {idx + 1}
                </span>
                <p className={`leading-relaxed ${isLight ? 'text-slate-700' : 'text-white/80'}`}>
                  {step}
                </p>
              </div>
            ))}
          </div>
        </div>
      )}

      {/* 3. Optimal Python Code */}
      <div className={`rounded-xl border overflow-hidden ${
        isLight ? 'border-slate-200 shadow-sm bg-white' : 'border-white/10 bg-[#070312]'
      }`}>
        <div className={`flex items-center justify-between px-4 py-2 border-b text-xs font-mono ${
          isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/5 border-white/8 text-white/60'
        }`}>
          <div className="flex items-center gap-2">
            <Code2 size={13} className="text-emerald-500" />
            <span className="font-semibold">solution.py (Optimal Python 3)</span>
          </div>

          <div className="flex items-center gap-2">
            <button
              onClick={handleCopy}
              className={`flex items-center gap-1 px-2.5 py-1 rounded border text-[11px] font-sans font-medium transition-all ${
                copied
                  ? 'bg-emerald-500/20 border-emerald-500/30 text-emerald-600'
                  : isLight ? 'bg-white border-slate-300 text-slate-700 hover:bg-slate-50' : 'bg-white/5 border-white/10 text-white/70 hover:text-white'
              }`}
            >
              {copied ? <Check size={12} /> : <Copy size={12} />}
              <span>{copied ? 'Copied!' : 'Copy Code'}</span>
            </button>

            {onLoadCodeIntoEditor && (
              <button
                onClick={() => onLoadCodeIntoEditor(solution.code)}
                className="flex items-center gap-1 px-2.5 py-1 rounded bg-gradient-to-r from-violet-600 to-cyan-600 text-white font-sans text-[11px] font-semibold hover:opacity-95 active:scale-95 transition-all shadow-sm"
                title="Copy code directly into Monaco editor on the right"
              >
                <Play size={11} />
                <span>{isHindi ? 'एडिटर में लोड करें' : 'Load into Editor'}</span>
              </button>
            )}
          </div>
        </div>

        <pre className={`p-4 text-xs font-mono overflow-x-auto leading-relaxed ${
          isLight ? 'bg-slate-900 text-slate-100' : 'bg-[#0a0218] text-slate-200'
        }`}>
          <code>{solution?.code}</code>
        </pre>
      </div>

      {/* 4. Complexity Analysis */}
      <div className={`p-4 rounded-xl border ${
        isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.025] border-white/8'
      }`}>
        <h4 className={`text-xs font-bold uppercase tracking-wider mb-3 ${
          isLight ? 'text-slate-800' : 'text-white/70'
        }`}>
          {isHindi ? 'जटिलता विश्लेषण (Complexity Analysis)' : 'Complexity Analysis'}
        </h4>
        <div className="grid grid-cols-1 sm:grid-cols-2 gap-3 text-xs">
          <div className={`p-3 rounded-lg border ${
            isLight ? 'bg-violet-50/60 border-violet-200 text-slate-800' : 'bg-violet-500/5 border-violet-500/15 text-white/80'
          }`}>
            <div className="flex items-center gap-1.5 font-bold mb-1 text-violet-600 dark:text-violet-400">
              <Clock size={13} />
              <span>{isHindi ? 'समय जटिलता (Time Complexity)' : 'Time Complexity'}</span>
            </div>
            <p className="leading-relaxed">
              {text?.timeComplexity || problem.timeComplexity}
            </p>
          </div>

          <div className={`p-3 rounded-lg border ${
            isLight ? 'bg-cyan-50/60 border-cyan-200 text-slate-800' : 'bg-cyan-500/5 border-cyan-500/15 text-white/80'
          }`}>
            <div className="flex items-center gap-1.5 font-bold mb-1 text-cyan-600 dark:text-cyan-400">
              <Database size={13} />
              <span>{isHindi ? 'स्थान जटिलता (Space Complexity)' : 'Space Complexity'}</span>
            </div>
            <p className="leading-relaxed">
              {text?.spaceComplexity || problem.spaceComplexity}
            </p>
          </div>
        </div>
      </div>
    </div>
  )
}

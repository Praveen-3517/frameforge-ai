import React, { useState } from 'react'
import {
  Copy, Check, Play,
  Code2, Clock, Database, Sparkles, CheckCircle2,
  ArrowRightLeft, Eye, Coffee, Terminal
} from 'lucide-react'
import { useAuth } from '../../context/AuthContext'
import CodeDiffViewer from './CodeDiffViewer'
import { getJavaSolution } from '../../data/dsaJavaSolutions'
import { getCSolution } from '../../data/dsaCSolutions'

export default function SolutionPanel({
  problem,
  interviewData,
  isLight = false,
  onLoadCodeIntoEditor,
  userCode = '',
  activeLang = 'c'
}) {
  const { user, openAuthModal } = useAuth()
  const [solutionLang, setSolutionLang] = useState('en') // 'en' | 'hi'
  const [codeLang, setCodeLang] = useState(activeLang || 'c')
  const [copied, setCopied] = useState(false)
  const [showDiff, setShowDiff] = useState(false)

  // Keep in sync if parent activeLang changes
  React.useEffect(() => {
    if (activeLang) setCodeLang(activeLang)
  }, [activeLang])

  const solution = interviewData?.solution
  const isHindi = solutionLang === 'hi'
  const text = isHindi ? solution?.hi : solution?.en

  // Guarantee clean code matching selected language
  const cCode = solution?.cCode || getCSolution(problem)?.code || ''
  const javaCode = solution?.javaCode || getJavaSolution(problem)?.code || ''
  const pythonCode = solution?.code || ''

  const activeSolutionCode = codeLang === 'c' ? cCode : (codeLang === 'java' ? javaCode : pythonCode)
  const activeFileName = codeLang === 'c' 
    ? 'solution.c (Optimal C11 / C17)' 
    : (codeLang === 'java' ? 'Solution.java (Optimal Java 21 / SE)' : 'solution.py (Optimal Python 3)')

  const handleCopy = () => {
    if (!activeSolutionCode) return
    navigator.clipboard.writeText(activeSolutionCode).then(() => {
      setCopied(true)
      setTimeout(() => setCopied(false), 2000)
    })
  }

  return (
    <div className="space-y-4 animate-fadeIn">
      {/* ── 1. Top Section: Direct Answer Code First ── */}
      <div className="space-y-2">
        {/* Language Tabs + Action Bar */}
        <div className="flex flex-wrap items-center justify-between gap-2">
          {/* Language Selector: C / Java / Python */}
          <div className={`flex items-center p-0.5 rounded-xl border text-xs font-bold ${
            isLight ? 'bg-slate-100 border-slate-300' : 'bg-black/30 border-white/10'
          }`}>
            <button
              onClick={() => setCodeLang('c')}
              className={`flex items-center gap-1 px-3 py-1.5 rounded-lg transition-all ${
                codeLang === 'c'
                  ? 'bg-gradient-to-r from-cyan-500 to-blue-600 text-white shadow-md'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/60 hover:text-white'
              }`}
            >
              <Terminal size={13} />
              <span>C Solution</span>
            </button>
            <button
              onClick={() => setCodeLang('java')}
              className={`flex items-center gap-1 px-3 py-1.5 rounded-lg transition-all ${
                codeLang === 'java'
                  ? 'bg-gradient-to-r from-amber-500 to-orange-600 text-white shadow-md'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/60 hover:text-white'
              }`}
            >
              <Coffee size={13} />
              <span>Java Solution</span>
            </button>
            <button
              onClick={() => setCodeLang('python')}
              className={`flex items-center gap-1 px-3 py-1.5 rounded-lg transition-all ${
                codeLang === 'python'
                  ? 'bg-gradient-to-r from-emerald-500 to-teal-600 text-white shadow-md'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/60 hover:text-white'
              }`}
            >
              <span>Python Solution</span>
            </button>
          </div>

          <div className="flex items-center gap-2">
            <button
              onClick={() => setShowDiff(d => !d)}
              className={`flex items-center gap-1 px-2.5 py-1.5 rounded-lg border text-xs font-semibold transition-all ${
                showDiff
                  ? 'bg-violet-600 text-white border-violet-500 shadow-md shadow-violet-600/30'
                  : isLight
                  ? 'bg-white border-violet-200 text-violet-700 hover:bg-violet-50'
                  : 'bg-violet-500/10 border-violet-500/25 text-violet-300 hover:bg-violet-500/20'
              }`}
            >
              {showDiff ? <Eye size={12} /> : <ArrowRightLeft size={12} />}
              <span>{showDiff ? 'Code View' : 'Compare Diff'}</span>
            </button>
          </div>
        </div>

        {/* Code Box */}
        {showDiff ? (
          <CodeDiffViewer
            original={userCode}
            modified={activeSolutionCode || ''}
            isLight={isLight}
            onLoadCodeIntoEditor={(c) => onLoadCodeIntoEditor && onLoadCodeIntoEditor(c, codeLang)}
          />
        ) : (
          <div className={`rounded-xl border overflow-hidden ${
            isLight ? 'border-slate-200 shadow-sm bg-white' : 'border-white/10 bg-[#070312]'
          }`}>
            <div className={`flex items-center justify-between px-4 py-2 border-b text-xs font-mono ${
              isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/5 border-white/8 text-white/60'
            }`}>
              <div className="flex items-center gap-2">
                <Code2 size={13} className={codeLang === 'java' ? 'text-amber-500' : 'text-cyan-400'} />
                <span className="font-bold">{activeFileName}</span>
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
                    onClick={() => onLoadCodeIntoEditor(activeSolutionCode, codeLang)}
                    className="flex items-center gap-1 px-3 py-1 rounded bg-gradient-to-r from-violet-600 to-cyan-600 text-white font-sans text-[11px] font-bold hover:opacity-95 active:scale-95 transition-all shadow-sm"
                    title={`Load ${codeLang.toUpperCase()} solution directly into Monaco editor`}
                  >
                    <Play size={11} />
                    <span>Load into Editor</span>
                  </button>
                )}
              </div>
            </div>

            <pre className={`p-4 text-xs font-mono overflow-x-auto leading-relaxed max-h-[420px] ${
              isLight ? 'bg-slate-900 text-slate-100' : 'bg-[#0a0218] text-slate-200'
            }`}>
              <code>{activeSolutionCode}</code>
            </pre>
          </div>
        )}
      </div>

      {/* ── 2. Bottom Section: Explanation Underneath Code ── */}
      <div className={`p-4 rounded-xl border ${
        isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.025] border-white/8'
      }`}>
        <div className="flex items-center justify-between mb-3">
          <h4 className={`text-xs font-bold uppercase tracking-wider flex items-center gap-1.5 ${
            isLight ? 'text-violet-700' : 'text-violet-300'
          }`}>
            <Sparkles size={13} />
            <span>{isHindi ? 'विस्तृत समाधान व व्याख्या (Explanation)' : 'Detailed Logic & Explanation'}</span>
          </h4>

          {/* English / Hindi Toggle */}
          <div className={`flex items-center p-0.5 rounded-lg border text-xs font-semibold ${
            isLight ? 'bg-slate-100 border-slate-300' : 'bg-black/40 border-white/10'
          }`}>
            <button
              onClick={() => setSolutionLang('en')}
              className={`px-2 py-0.5 rounded transition-all text-[11px] ${
                !isHindi
                  ? 'bg-violet-600 text-white shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
              }`}
            >
              English
            </button>
            <button
              onClick={() => setSolutionLang('hi')}
              className={`px-2 py-0.5 rounded transition-all text-[11px] ${
                isHindi
                  ? 'bg-amber-500 text-slate-950 font-bold shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/50 hover:text-white'
              }`}
            >
              हिंदी
            </button>
          </div>
        </div>

        {/* Intuition text */}
        <p className={`text-xs leading-relaxed mb-3 ${isLight ? 'text-slate-700' : 'text-white/80'}`}>
          {text?.intuition || problem.approach}
        </p>

        {/* Steps */}
        {text?.steps && text.steps.length > 0 && (
          <div className="space-y-1.5 mt-3 pt-3 border-t border-white/5">
            <h5 className={`text-[11px] font-bold uppercase tracking-wider ${isLight ? 'text-cyan-800' : 'text-cyan-400'}`}>
              {isHindi ? 'कदम-दर-कदम एल्गोरिदम:' : 'Algorithm Steps:'}
            </h5>
            {text.steps.map((step, idx) => (
              <div key={idx} className="flex items-start gap-2 text-xs">
                <span className={`w-4 h-4 rounded-full flex items-center justify-center font-mono font-bold shrink-0 text-[10px] mt-0.5 ${
                  isLight ? 'bg-cyan-100 text-cyan-800' : 'bg-cyan-500/20 text-cyan-300'
                }`}>
                  {idx + 1}
                </span>
                <span className={isLight ? 'text-slate-600' : 'text-white/70'}>{step}</span>
              </div>
            ))}
          </div>
        )}
      </div>

      {/* ── 3. Complexity Analysis ── */}
      <div className={`p-4 rounded-xl border ${
        isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/[0.025] border-white/8'
      }`}>
        <h4 className={`text-xs font-bold uppercase tracking-wider mb-3 ${
          isLight ? 'text-slate-500' : 'text-white/40'
        }`}>
          Complexity Analysis
        </h4>

        <div className="grid grid-cols-1 sm:grid-cols-2 gap-3">
          <div className={`p-3 rounded-lg border ${
            isLight ? 'bg-violet-50/50 border-violet-200 text-violet-950' : 'bg-violet-500/5 border-violet-500/15'
          }`}>
            <div className="flex items-center gap-1.5 text-violet-600 dark:text-violet-400 font-bold text-xs mb-1">
              <Clock size={12} />
              <span>Time Complexity</span>
            </div>
            <p className={`text-xs ${isLight ? 'text-slate-700' : 'text-white/70'}`}>
              {text?.timeComplexity || problem.timeComplexity || 'O(N)'}
            </p>
          </div>

          <div className={`p-3 rounded-lg border ${
            isLight ? 'bg-cyan-50/50 border-cyan-200 text-cyan-950' : 'bg-cyan-500/5 border-cyan-500/15'
          }`}>
            <div className="flex items-center gap-1.5 text-cyan-600 dark:text-cyan-400 font-bold text-xs mb-1">
              <Database size={12} />
              <span>Space Complexity</span>
            </div>
            <p className={`text-xs ${isLight ? 'text-slate-700' : 'text-white/70'}`}>
              {text?.spaceComplexity || problem.spaceComplexity || 'O(1)'}
            </p>
          </div>
        </div>
      </div>
    </div>
  )
}

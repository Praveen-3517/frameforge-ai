import React, { useState, useRef } from 'react'
import { DiffEditor } from '@monaco-editor/react'
import {
  Columns, AlignJustify, Play, Copy, Check,
  Sparkles, Code2, ArrowRightLeft, CheckCircle2
} from 'lucide-react'

export default function CodeDiffViewer({
  original = '',
  modified = '',
  isLight = false,
}) {
  const [sideBySide, setSideBySide] = useState(() => {
    return typeof window !== 'undefined' ? window.innerWidth >= 768 : true
  })
  const [copied, setCopied] = useState(false)
  const [loaded, setLoaded] = useState(false)
  const diffEditorRef = useRef(null)

  function handleDiffMount(editor, monaco) {
    diffEditorRef.current = editor

    // Define custom dark theme if not already defined
    try {
      monaco.editor.defineTheme('dsa-diff-dark', {
        base: 'vs-dark',
        inherit: true,
        rules: [
          { token: 'keyword', foreground: 'a78bfa' },
          { token: 'string', foreground: '34d399' },
          { token: 'number', foreground: 'fb923c' },
          { token: 'comment', foreground: '6b7280', fontStyle: 'italic' },
          { token: 'function', foreground: '60a5fa' },
        ],
        colors: {
          'editor.background': '#070212',
          'editor.foreground': '#e2e8f0',
          'diffEditor.insertedTextBackground': '#10b98125',
          'diffEditor.removedTextBackground': '#f43f5e25',
          'diffEditor.insertedLineBackground': '#10b98115',
          'diffEditor.removedLineBackground': '#f43f5e15',
          'scrollbarSlider.background': '#7c3aed30',
        }
      })
    } catch {}

    monaco.editor.setTheme(isLight ? 'vs' : 'dsa-diff-dark')
  }

  const handleCopyOptimal = () => {
    if (!modified) return
    navigator.clipboard.writeText(modified).then(() => {
      setCopied(true)
      setTimeout(() => setCopied(false), 2000)
    })
  }

  const handleApplyOptimal = () => {
    if (onLoadCodeIntoEditor && modified) {
      onLoadCodeIntoEditor(modified)
      setLoaded(true)
      setTimeout(() => setLoaded(false), 2500)
    }
  }

  // Basic line delta counts
  const origLines = (original || '').trim().split('\n').length
  const modLines = (modified || '').trim().split('\n').length

  return (
    <div className={`rounded-xl border overflow-hidden flex flex-col transition-all ${
      isLight ? 'border-slate-200 bg-white shadow-sm' : 'border-violet-500/25 bg-[#070212]'
    }`}>
      {/* ── Toolbar ── */}
      <div className={`flex flex-wrap items-center justify-between gap-2 px-3.5 py-2.5 border-b text-xs ${
        isLight ? 'bg-slate-100 border-slate-200 text-slate-700' : 'bg-white/[0.03] border-white/8 text-white/70'
      }`}>
        {/* Left: Indicator & Stats */}
        <div className="flex items-center gap-2">
          <div className="flex items-center gap-1.5 font-bold text-violet-500">
            <ArrowRightLeft size={13} />
            <span className="text-xs">Diff Comparison</span>
          </div>

          <span className={`text-[10px] px-2 py-0.5 rounded font-mono font-medium border ${
            isLight ? 'bg-slate-200 border-slate-300 text-slate-700' : 'bg-white/5 border-white/10 text-white/50'
          }`}>
            Your Code: {origLines}L ↔ Optimal: {modLines}L
          </span>
        </div>

        {/* Right: Actions */}
        <div className="flex items-center gap-1.5">
          {/* Side-by-side vs Inline toggle */}
          <div className={`flex items-center p-0.5 rounded-lg border ${
            isLight ? 'bg-white border-slate-300' : 'bg-black/30 border-white/10'
          }`}>
            <button
              onClick={() => setSideBySide(true)}
              title="Side by side comparison"
              className={`flex items-center gap-1 px-2 py-1 rounded text-[10px] font-semibold transition-all ${
                sideBySide
                  ? 'bg-violet-600 text-white shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/40 hover:text-white'
              }`}
            >
              <Columns size={11} />
              <span className="hidden sm:inline">Split</span>
            </button>
            <button
              onClick={() => setSideBySide(false)}
              title="Inline unified diff"
              className={`flex items-center gap-1 px-2 py-1 rounded text-[10px] font-semibold transition-all ${
                !sideBySide
                  ? 'bg-violet-600 text-white shadow-sm'
                  : isLight ? 'text-slate-600 hover:text-slate-900' : 'text-white/40 hover:text-white'
              }`}
            >
              <AlignJustify size={11} />
              <span className="hidden sm:inline">Unified</span>
            </button>
          </div>

          {/* Copy optimal */}
          <button
            onClick={handleCopyOptimal}
            className={`flex items-center gap-1 px-2.5 py-1 rounded border text-[11px] font-medium transition-all ${
              copied
                ? 'bg-emerald-500/20 border-emerald-500/30 text-emerald-600'
                : isLight ? 'bg-white border-slate-300 text-slate-700 hover:bg-slate-50' : 'bg-white/5 border-white/10 text-white/70 hover:text-white'
            }`}
          >
            {copied ? <Check size={11} /> : <Copy size={11} />}
            <span>{copied ? 'Copied' : 'Copy'}</span>
          </button>

          {/* Load into editor */}
          {onLoadCodeIntoEditor && (
            <button
              onClick={handleApplyOptimal}
              className={`flex items-center gap-1 px-2.5 py-1 rounded text-[11px] font-semibold transition-all shadow-sm ${
                loaded
                  ? 'bg-emerald-600 text-white'
                  : 'bg-gradient-to-r from-violet-600 to-cyan-600 text-white hover:opacity-95 active:scale-95'
              }`}
            >
              {loaded ? <CheckCircle2 size={11} /> : <Play size={11} />}
              <span>{loaded ? 'Loaded!' : 'Load to Editor'}</span>
            </button>
          )}
        </div>
      </div>

      {/* ── Header Legend ── */}
      <div className={`flex items-center justify-between px-3.5 py-1 border-b text-[10px] font-mono ${
        isLight ? 'bg-slate-50 border-slate-200 text-slate-500' : 'bg-black/20 border-white/5 text-white/40'
      }`}>
        <div className="flex items-center gap-1.5">
          <span className="w-2 h-2 rounded-full bg-rose-500/80" />
          <span>Left: Your Current Solution</span>
        </div>
        <div className="flex items-center gap-1.5">
          <span className="w-2 h-2 rounded-full bg-emerald-500/80" />
          <span>Right: Official Optimal Solution</span>
        </div>
      </div>

      {/* ── Monaco Diff Editor ── */}
      <div className="h-[380px] w-full">
        <DiffEditor
          height="100%"
          language="python"
          original={original}
          modified={modified}
          onMount={handleDiffMount}
          theme={isLight ? 'vs' : 'dsa-diff-dark'}
          options={{
            renderSideBySide: sideBySide,
            readOnly: true,
            fontSize: 12.5,
            fontFamily: '"JetBrains Mono", "Fira Code", monospace',
            minimap: { enabled: false },
            scrollBeyondLastLine: false,
            wordWrap: 'on',
            lineNumbers: 'on',
            automaticLayout: true,
            padding: { top: 10, bottom: 10 },
            scrollbar: {
              verticalScrollbarSize: 6,
              horizontalScrollbarSize: 6,
            }
          }}
          loading={
            <div className={`flex items-center justify-center h-full ${isLight ? 'bg-slate-100' : 'bg-[#070212]'}`}>
              <div className="flex flex-col items-center gap-2">
                <div className="w-6 h-6 border-2 border-violet-500 border-t-transparent rounded-full animate-spin" />
                <span className="text-violet-400 text-xs font-mono">Loading diff engine...</span>
              </div>
            </div>
          }
        />
      </div>
    </div>
  )
}

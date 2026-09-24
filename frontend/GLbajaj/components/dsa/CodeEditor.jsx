import React, { useRef, useEffect, useState } from 'react'
import Editor, { loader } from '@monaco-editor/react'

// Configure ultra-reliable CDN for Monaco Editor assets
try {
  loader.config({
    paths: {
      vs: 'https://cdnjs.cloudflare.com/ajax/libs/monaco-editor/0.45.0/min/vs'
    }
  })
} catch {}

function FallbackCodeEditor({ value, onChange, readOnly, isLight, language }) {
  const lineCount = (value || '').split('\n').length
  const lineNumbers = Array.from({ length: Math.max(lineCount, 12) }, (_, i) => i + 1)

  const handleKeyDown = (e) => {
    if (e.key === 'Tab') {
      e.preventDefault()
      const start = e.target.selectionStart
      const end = e.target.selectionEnd
      const nextVal = (value || '').substring(0, start) + '    ' + (value || '').substring(end)
      onChange(nextVal)
      setTimeout(() => {
        e.target.selectionStart = e.target.selectionEnd = start + 4
      }, 0)
    }
  }

  return (
    <div className={`h-full w-full flex font-mono text-sm overflow-auto ${
      isLight ? 'bg-white text-slate-800' : 'bg-[#0a0118] text-slate-200'
    }`}>
      {/* Line Numbers */}
      <div className={`select-none py-4 px-3 text-right border-r font-mono text-xs ${
        isLight ? 'bg-slate-50 border-slate-200 text-slate-400' : 'bg-[#060010] border-white/5 text-white/20'
      }`}>
        {lineNumbers.map(n => (
          <div key={n} className="leading-6">{n}</div>
        ))}
      </div>

      {/* Editor Textarea */}
      <textarea
        value={value || ''}
        onChange={(e) => onChange(e.target.value)}
        onKeyDown={handleKeyDown}
        readOnly={readOnly}
        spellCheck="false"
        autoCapitalize="off"
        autoComplete="off"
        className={`flex-1 h-full p-4 bg-transparent resize-none outline-none leading-6 font-mono text-sm whitespace-pre ${
          isLight ? 'text-slate-900 caret-violet-600' : 'text-slate-100 caret-cyan-400'
        }`}
      />
    </div>
  )
}

export default function CodeEditor({ value, onChange, readOnly = false, isLight = false, language = 'c' }) {
  const editorRef = useRef(null)
  const monacoRef = useRef(null)
  const [monacoFailed, setMonacoFailed] = useState(false)

  // If Monaco takes longer than 2.5s, fall back to lightweight native code editor
  useEffect(() => {
    const timer = setTimeout(() => {
      if (!editorRef.current) {
        setMonacoFailed(true)
      }
    }, 2500)
    return () => clearTimeout(timer)
  }, [])

  function handleEditorDidMount(editor, monaco) {
    editorRef.current = editor
    monacoRef.current = monaco
    setMonacoFailed(false)

    // Custom dark theme matching the app
    try {
      monaco.editor.defineTheme('dsa-dark', {
        base: 'vs-dark',
        inherit: true,
        rules: [
          { token: 'keyword', foreground: 'a78bfa' },
          { token: 'string', foreground: '34d399' },
          { token: 'number', foreground: 'fb923c' },
          { token: 'comment', foreground: '6b7280', fontStyle: 'italic' },
          { token: 'function', foreground: '60a5fa' },
          { token: 'type', foreground: 'f472b6' },
        ],
        colors: {
          'editor.background': '#0a0118',
          'editor.foreground': '#e2e8f0',
          'editor.lineHighlightBackground': '#1e1040',
          'editor.selectionBackground': '#7c3aed50',
          'editorCursor.foreground': '#a78bfa',
          'editorLineNumber.foreground': '#4b5563',
          'editorLineNumber.activeForeground': '#a78bfa',
          'editor.inactiveSelectionBackground': '#7c3aed30',
          'scrollbarSlider.background': '#7c3aed30',
          'scrollbarSlider.hoverBackground': '#7c3aed60',
          'scrollbarSlider.activeBackground': '#7c3aed80',
          'editorWidget.background': '#0f0620',
          'editorSuggestWidget.background': '#0f0620',
          'editorSuggestWidget.border': '#7c3aed40',
          'editorSuggestWidget.selectedBackground': '#7c3aed40',
        }
      })
    } catch {}

    monaco.editor.setTheme(isLight ? 'vs' : 'dsa-dark')
    editor.focus()
  }

  useEffect(() => {
    if (monacoRef.current) {
      monacoRef.current.editor.setTheme(isLight ? 'vs' : 'dsa-dark')
    }
  }, [isLight])

  if (monacoFailed) {
    return (
      <div className={`h-full w-full rounded-lg overflow-hidden border transition-colors ${
        isLight ? 'border-slate-300 shadow-sm bg-white' : 'border-violet-500/20 bg-[#0a0118]'
      }`}>
        <FallbackCodeEditor
          value={value}
          onChange={onChange}
          readOnly={readOnly}
          isLight={isLight}
          language={language}
        />
      </div>
    )
  }

  return (
    <div className={`h-full w-full rounded-lg overflow-hidden border transition-colors ${
      isLight ? 'border-slate-300 shadow-sm bg-white' : 'border-violet-500/20 bg-[#0a0118]'
    }`}>
      <Editor
        height="100%"
        language={language === 'c' ? 'c' : (language === 'java' ? 'java' : 'python')}
        defaultLanguage={language === 'c' ? 'c' : (language === 'java' ? 'java' : 'python')}
        value={value}
        onChange={onChange}
        onMount={handleEditorDidMount}
        options={{
          fontSize: 14,
          fontFamily: '"JetBrains Mono", "Fira Code", "Cascadia Code", monospace',
          fontLigatures: true,
          minimap: { enabled: false },
          scrollBeyondLastLine: false,
          lineNumbers: 'on',
          renderLineHighlight: 'all',
          automaticLayout: true,
          tabSize: 4,
          wordWrap: 'on',
          readOnly,
          padding: { top: 16, bottom: 16 },
          smoothScrolling: true,
          cursorBlinking: 'smooth',
          cursorSmoothCaretAnimation: 'on',
          bracketPairColorization: { enabled: true },
          guides: { bracketPairs: true },
          formatOnPaste: true,
          suggest: { showKeywords: true },
          quickSuggestions: true,
          scrollbar: {
            verticalScrollbarSize: 6,
            horizontalScrollbarSize: 6,
          }
        }}
        theme={isLight ? 'vs' : 'dsa-dark'}
        loading={
          <div className={`flex items-center justify-center h-full ${
            isLight ? 'bg-white' : 'bg-[#0a0118]'
          }`}>
            <div className="flex flex-col items-center gap-3">
              <div className="w-8 h-8 border-2 border-cyan-500 border-t-transparent rounded-full animate-spin" />
              <span className={`text-sm font-mono ${
                isLight ? 'text-slate-700' : 'text-cyan-400'
              }`}>
                Loading editor...
              </span>
            </div>
          </div>
        }
      />
    </div>
  )
}

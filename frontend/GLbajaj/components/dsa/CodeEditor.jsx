import React, { useRef, useEffect } from 'react'
import Editor from '@monaco-editor/react'

export default function CodeEditor({ value, onChange, readOnly = false }) {
  const editorRef = useRef(null)

  function handleEditorDidMount(editor, monaco) {
    editorRef.current = editor

    // Custom dark theme matching the app
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
    monaco.editor.setTheme('dsa-dark')

    // Python-specific settings
    monaco.languages.setLanguageConfiguration('python', {
      indentationRules: {
        increaseIndentPattern: /^.*:\s*$/,
        decreaseIndentPattern: /^\s*(else|elif|except|finally)\b.*:\s*$/
      }
    })

    editor.focus()
  }

  return (
    <div className="h-full w-full rounded-lg overflow-hidden border border-violet-500/20">
      <Editor
        height="100%"
        defaultLanguage="python"
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
        theme="dsa-dark"
        loading={
          <div className="flex items-center justify-center h-full bg-[#0a0118]">
            <div className="flex flex-col items-center gap-3">
              <div className="w-8 h-8 border-2 border-violet-500 border-t-transparent rounded-full animate-spin" />
              <span className="text-violet-400 text-sm font-mono">Loading editor...</span>
            </div>
          </div>
        }
      />
    </div>
  )
}

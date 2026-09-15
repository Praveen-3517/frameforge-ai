import React, { useState, useRef, useEffect } from 'react'
import { Play, RotateCcw, CheckCircle2, XCircle, Loader2, Terminal, AlertTriangle } from 'lucide-react'

let pyodideInstance = null
let pyodideLoading = false
let pyodideReady = false

async function getPyodide() {
  if (pyodideReady && pyodideInstance) return pyodideInstance
  if (pyodideLoading) {
    // Wait for it to finish loading
    return new Promise((resolve) => {
      const check = setInterval(() => {
        if (pyodideReady && pyodideInstance) {
          clearInterval(check)
          resolve(pyodideInstance)
        }
      }, 200)
    })
  }
  pyodideLoading = true
  const pyodide = await window.loadPyodide({
    indexURL: 'https://cdn.jsdelivr.net/pyodide/v0.25.0/full/'
  })
  pyodideInstance = pyodide
  pyodideReady = true
  pyodideLoading = false
  return pyodide
}

export default function TestRunner({ problem, code, onSuccess }) {
  const [status, setStatus] = useState('idle') // idle | loading-pyodide | running | passed | failed | error
  const [output, setOutput] = useState('')
  const [testResults, setTestResults] = useState([])
  const [pyodideStatus, setPyodideStatus] = useState('unloaded') // unloaded | loading | ready
  const outputRef = useRef(null)

  // Load Pyodide script on mount
  useEffect(() => {
    if (!document.getElementById('pyodide-script')) {
      setPyodideStatus('loading')
      const script = document.createElement('script')
      script.id = 'pyodide-script'
      script.src = 'https://cdn.jsdelivr.net/pyodide/v0.25.0/full/pyodide.js'
      script.onload = async () => {
        try {
          await getPyodide()
          setPyodideStatus('ready')
        } catch (e) {
          setPyodideStatus('error')
        }
      }
      script.onerror = () => setPyodideStatus('error')
      document.head.appendChild(script)
    } else if (pyodideReady) {
      setPyodideStatus('ready')
    } else {
      setPyodideStatus('loading')
      const checkInterval = setInterval(() => {
        if (pyodideReady) {
          setPyodideStatus('ready')
          clearInterval(checkInterval)
        }
      }, 300)
      return () => clearInterval(checkInterval)
    }
  }, [])

  useEffect(() => {
    if (outputRef.current) {
      outputRef.current.scrollTop = outputRef.current.scrollHeight
    }
  }, [output])

  const runCode = async () => {
    if (!pyodideReady) {
      setStatus('loading-pyodide')
      setOutput('⏳ Loading Python engine (Pyodide)...\nThis may take a moment on first load.')
      try {
        await getPyodide()
        setPyodideStatus('ready')
      } catch (e) {
        setStatus('error')
        setOutput('❌ Failed to load Python engine. Please check your internet connection.')
        return
      }
    }

    setStatus('running')
    setOutput('')
    setTestResults([])

    try {
      const pyodide = await getPyodide()

      // Capture stdout
      let captured = ''
      pyodide.setStdout({ batched: (text) => { captured += text + '\n' } })
      pyodide.setStderr({ batched: (text) => { captured += '⚠️ ' + text + '\n' } })

      // Run user's code
      await pyodide.runPythonAsync(code)

      setOutput(captured.trim() || '(No output)')

      // Run test cases if any
      if (problem.testCases && problem.testCases.length > 0) {
        const results = []
        let allPassed = true

        for (const tc of problem.testCases) {
          try {
            // Extract function name from starter code
            const fnMatch = problem.starterCode.match(/def (\w+)\s*\(/)
            const fnName = fnMatch ? fnMatch[1] : 'solution'

            // Run test
            const testCode = `
import json
try:
    _result = ${fnName}${tc.input}
    print(repr(_result))
except Exception as e:
    print(f"ERROR: {e}")
`
            let testOut = ''
            pyodide.setStdout({ batched: (t) => { testOut += t } })
            await pyodide.runPythonAsync(code + '\n' + testCode)

            const actual = testOut.trim()
            const passed = actual === tc.expected ||
              actual.replace(/\s/g, '') === tc.expected.replace(/\s/g, '')

            if (!passed) allPassed = false
            results.push({
              input: tc.input,
              expected: tc.expected,
              actual,
              passed,
            })
          } catch (e) {
            allPassed = false
            results.push({
              input: tc.input,
              expected: tc.expected,
              actual: `Error: ${e.message}`,
              passed: false,
            })
          }
        }

        setTestResults(results)
        setStatus(allPassed ? 'passed' : 'failed')
        if (allPassed) onSuccess?.()
      } else {
        setStatus('passed')
        if (captured.trim()) onSuccess?.()
      }
    } catch (err) {
      setStatus('error')
      setOutput(`❌ Error:\n${err.message || err.toString()}`)
    }
  }

  const reset = () => {
    setStatus('idle')
    setOutput('')
    setTestResults([])
  }

  const statusConfig = {
    idle: { color: 'text-white/40', label: 'Ready to run' },
    'loading-pyodide': { color: 'text-yellow-400', label: 'Loading Python...' },
    running: { color: 'text-blue-400', label: 'Running...' },
    passed: { color: 'text-emerald-400', label: '✓ All tests passed!' },
    failed: { color: 'text-red-400', label: '✗ Some tests failed' },
    error: { color: 'text-orange-400', label: '⚠ Runtime error' },
  }

  return (
    <div className="flex flex-col h-full">
      {/* Toolbar */}
      <div className="flex items-center justify-between px-4 py-2.5 border-b border-white/8 bg-white/2">
        <div className="flex items-center gap-2">
          <Terminal size={14} className="text-violet-400" />
          <span className="text-white/50 text-xs font-mono">Output Console</span>
          {pyodideStatus === 'loading' && (
            <span className="text-yellow-400/70 text-xs flex items-center gap-1">
              <Loader2 size={10} className="animate-spin" />
              Loading Python engine...
            </span>
          )}
          {pyodideStatus === 'ready' && (
            <span className="text-emerald-400/60 text-xs">● Python Ready</span>
          )}
        </div>

        <div className="flex items-center gap-2">
          <span className={`text-xs font-medium ${statusConfig[status]?.color}`}>
            {statusConfig[status]?.label}
          </span>

          <button
            onClick={reset}
            className="p-1.5 rounded hover:bg-white/8 text-white/30 hover:text-white/70 transition-all"
            title="Clear output"
          >
            <RotateCcw size={13} />
          </button>

          <button
            onClick={runCode}
            disabled={status === 'running' || status === 'loading-pyodide'}
            className={`flex items-center gap-2 px-4 py-1.5 rounded-lg text-sm font-medium transition-all duration-200 ${
              status === 'running' || status === 'loading-pyodide'
                ? 'bg-violet-600/30 text-violet-400/50 cursor-not-allowed'
                : 'bg-gradient-to-r from-violet-600 to-cyan-600 hover:from-violet-500 hover:to-cyan-500 text-white shadow-lg shadow-violet-500/20 hover:shadow-violet-500/40 hover:scale-105'
            }`}
          >
            {status === 'running' || status === 'loading-pyodide' ? (
              <Loader2 size={14} className="animate-spin" />
            ) : (
              <Play size={14} />
            )}
            Run Code
          </button>
        </div>
      </div>

      {/* Test Results */}
      {testResults.length > 0 && (
        <div className="px-4 py-3 border-b border-white/8 space-y-2">
          <p className="text-white/40 text-xs font-mono uppercase tracking-wider mb-2">Test Cases</p>
          {testResults.map((r, i) => (
            <div
              key={i}
              className={`flex items-start gap-3 p-2.5 rounded-lg text-xs border ${
                r.passed
                  ? 'bg-emerald-500/8 border-emerald-500/20'
                  : 'bg-red-500/8 border-red-500/20'
              }`}
            >
              {r.passed ? (
                <CheckCircle2 size={14} className="text-emerald-400 mt-0.5 shrink-0" />
              ) : (
                <XCircle size={14} className="text-red-400 mt-0.5 shrink-0" />
              )}
              <div className="flex-1 min-w-0">
                <div className="flex flex-wrap gap-x-4 gap-y-0.5">
                  <span className="text-white/40">Input: <span className="text-white/70 font-mono">{r.input}</span></span>
                  <span className="text-white/40">Expected: <span className="text-emerald-300/80 font-mono">{r.expected}</span></span>
                  {!r.passed && (
                    <span className="text-white/40">Got: <span className="text-red-300/80 font-mono">{r.actual}</span></span>
                  )}
                </div>
              </div>
            </div>
          ))}
        </div>
      )}

      {/* Output area */}
      <div
        ref={outputRef}
        className="flex-1 p-4 font-mono text-sm overflow-auto bg-[#050010]"
        style={{ minHeight: '80px' }}
      >
        {status === 'idle' && !output ? (
          <div className="flex flex-col items-center justify-center h-full text-center py-6">
            <Play size={24} className="text-white/10 mb-2" />
            <p className="text-white/20 text-xs">Press Run Code to execute your Python solution</p>
          </div>
        ) : (
          <pre className={`whitespace-pre-wrap break-words leading-relaxed ${
            status === 'error' ? 'text-orange-300' :
            status === 'passed' ? 'text-emerald-300' :
            'text-slate-300'
          }`}>
            {output}
          </pre>
        )}
      </div>
    </div>
  )
}

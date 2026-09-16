import React, { useState, useRef, useEffect } from 'react'
import { Play, RotateCcw, CheckCircle2, XCircle, Loader2, Terminal } from 'lucide-react'
import { useAuth } from '../../context/AuthContext'

let pyodideInstance = null
let pyodideLoading = false
let pyodideReady = false

async function getPyodide() {
  if (pyodideReady && pyodideInstance) return pyodideInstance
  if (pyodideLoading) {
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

export default function TestRunner({ problem, code, onSuccess, isLight = false }) {
  const { user, openAuthModal } = useAuth()
  const [status, setStatus] = useState('idle') // idle | loading-pyodide | running | passed | failed | error
  const [output, setOutput] = useState('')
  const [testResults, setTestResults] = useState([])
  const [pyodideStatus, setPyodideStatus] = useState('unloaded')
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
    if (!user) {
      openAuthModal('signup')
      return
    }

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
            const fnMatch = problem.starterCode.match(/def (\w+)\s*\(/)
            const fnName = fnMatch ? fnMatch[1] : 'solution'

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
    idle: {
      color: isLight ? 'text-slate-500' : 'text-white/40',
      label: 'Ready to run'
    },
    'loading-pyodide': {
      color: isLight ? 'text-amber-700 font-bold' : 'text-yellow-400',
      label: 'Loading Python...'
    },
    running: {
      color: isLight ? 'text-blue-700 font-bold' : 'text-blue-400',
      label: 'Running...'
    },
    passed: {
      color: isLight ? 'text-emerald-700 font-bold' : 'text-emerald-400',
      label: '✓ All tests passed!'
    },
    failed: {
      color: isLight ? 'text-red-700 font-bold' : 'text-red-400',
      label: '✗ Some tests failed'
    },
    error: {
      color: isLight ? 'text-orange-700 font-bold' : 'text-orange-400',
      label: '⚠ Runtime error'
    },
  }

  return (
    <div className="flex flex-col h-full">
      {/* Toolbar */}
      <div className={`flex items-center justify-between px-4 py-2.5 border-b transition-colors ${
        isLight ? 'bg-slate-100 border-slate-200 text-slate-800' : 'border-white/8 bg-white/2 text-white'
      }`}>
        <div className="flex items-center gap-2">
          <Terminal size={14} className={isLight ? 'text-violet-600' : 'text-violet-400'} />
          <span className={`text-xs font-mono font-bold ${isLight ? 'text-slate-900' : 'text-white/50'}`}>
            Output Console
          </span>
          {pyodideStatus === 'loading' && (
            <span className={`text-xs flex items-center gap-1 ${isLight ? 'text-amber-700 font-medium' : 'text-yellow-400/70'}`}>
              <Loader2 size={10} className="animate-spin" />
              Loading Python engine...
            </span>
          )}
          {pyodideStatus === 'ready' && (
            <span className={`text-xs font-medium ${isLight ? 'text-emerald-700' : 'text-emerald-400/60'}`}>
              ● Python Ready
            </span>
          )}
        </div>

        <div className="flex items-center gap-2">
          <span className={`text-xs font-medium ${statusConfig[status]?.color}`}>
            {statusConfig[status]?.label}
          </span>

          <button
            onClick={reset}
            className={`p-1.5 rounded transition-all ${
              isLight
                ? 'text-slate-500 hover:text-slate-900 hover:bg-slate-200'
                : 'hover:bg-white/8 text-white/30 hover:text-white/70'
            }`}
            title="Clear output"
          >
            <RotateCcw size={13} />
          </button>

          <button
            onClick={runCode}
            disabled={status === 'running' || status === 'loading-pyodide'}
            className={`flex items-center gap-2 px-4 py-1.5 rounded-lg text-sm font-bold transition-all duration-200 ${
              status === 'running' || status === 'loading-pyodide'
                ? 'bg-violet-600/30 text-violet-400/50 cursor-not-allowed'
                : 'bg-gradient-to-r from-violet-600 to-cyan-600 hover:from-violet-500 hover:to-cyan-500 text-white shadow-lg shadow-violet-500/20 active:scale-95'
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
        <div className={`px-4 py-3 border-b space-y-2 ${
          isLight ? 'border-slate-200 bg-slate-50/90' : 'border-white/8 bg-black/20'
        }`}>
          <p className={`text-xs font-mono font-bold uppercase tracking-wider mb-2 ${
            isLight ? 'text-slate-700' : 'text-white/40'
          }`}>
            Test Case Results
          </p>
          {testResults.map((r, i) => (
            <div
              key={i}
              className={`flex items-start gap-3 p-2.5 rounded-xl text-xs border ${
                r.passed
                  ? isLight
                    ? 'bg-emerald-50 border-emerald-300 text-emerald-950 shadow-sm'
                    : 'bg-emerald-500/8 border-emerald-500/20 text-emerald-200'
                  : isLight
                    ? 'bg-red-50 border-red-300 text-red-950 shadow-sm'
                    : 'bg-red-500/8 border-red-500/20 text-red-200'
              }`}
            >
              {r.passed ? (
                <CheckCircle2 size={15} className="text-emerald-600 mt-0.5 shrink-0" />
              ) : (
                <XCircle size={15} className="text-red-600 mt-0.5 shrink-0" />
              )}
              <div className="flex-1 min-w-0">
                <div className="flex flex-wrap gap-x-4 gap-y-1">
                  <span>
                    <span className={isLight ? 'text-slate-600 font-semibold' : 'text-white/40'}>Input: </span>
                    <span className={`font-mono font-bold ${isLight ? 'text-slate-900' : 'text-white/80'}`}>{r.input}</span>
                  </span>
                  <span>
                    <span className={isLight ? 'text-slate-600 font-semibold' : 'text-white/40'}>Expected: </span>
                    <span className={`font-mono font-bold ${isLight ? 'text-emerald-800' : 'text-emerald-300/80'}`}>{r.expected}</span>
                  </span>
                  {!r.passed && (
                    <span>
                      <span className={isLight ? 'text-red-700 font-semibold' : 'text-white/40'}>Got: </span>
                      <span className={`font-mono font-bold ${isLight ? 'text-red-800' : 'text-red-300/80'}`}>{r.actual}</span>
                    </span>
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
        className={`flex-1 p-4 font-mono text-sm overflow-auto ${
          isLight ? 'bg-[#0f172a] text-slate-100' : 'bg-[#050010] text-slate-300'
        }`}
        style={{ minHeight: '80px' }}
      >
        {status === 'idle' && !output ? (
          <div className="flex flex-col items-center justify-center h-full text-center py-6">
            <Play size={24} className="text-white/10 mb-2" />
            <p className="text-white/30 text-xs">Press Run Code to execute your Python solution</p>
          </div>
        ) : (
          <pre className={`whitespace-pre-wrap break-words leading-relaxed ${
            status === 'error' ? 'text-rose-400 font-semibold' :
            status === 'passed' ? 'text-emerald-400 font-semibold' :
            'text-slate-200'
          }`}>
            {output}
          </pre>
        )}
      </div>
    </div>
  )
}

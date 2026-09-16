import React, { useState, useEffect, useRef, useCallback } from 'react'
import { Timer, Play, Pause, RotateCcw, AlertTriangle } from 'lucide-react'

// Default time per difficulty (seconds)
const DEFAULT_TIME = { Easy: 20 * 60, Medium: 30 * 60, Hard: 45 * 60 }

export default function InterviewTimer({ difficulty = 'Medium', isLight = false }) {
  const defaultSecs = DEFAULT_TIME[difficulty] || 30 * 60
  const [total, setTotal] = useState(defaultSecs)
  const [remaining, setRemaining] = useState(defaultSecs)
  const [running, setRunning] = useState(false)
  const [finished, setFinished] = useState(false)
  const intervalRef = useRef(null)

  // Reset when difficulty changes
  useEffect(() => {
    const t = DEFAULT_TIME[difficulty] || 30 * 60
    setTotal(t)
    setRemaining(t)
    setRunning(false)
    setFinished(false)
  }, [difficulty])

  useEffect(() => {
    if (running) {
      intervalRef.current = setInterval(() => {
        setRemaining(r => {
          if (r <= 1) {
            clearInterval(intervalRef.current)
            setRunning(false)
            setFinished(true)
            return 0
          }
          return r - 1
        })
      }, 1000)
    } else {
      clearInterval(intervalRef.current)
    }
    return () => clearInterval(intervalRef.current)
  }, [running])

  const reset = useCallback(() => {
    clearInterval(intervalRef.current)
    setRemaining(total)
    setRunning(false)
    setFinished(false)
  }, [total])

  const toggle = useCallback(() => {
    if (finished) return
    setRunning(r => !r)
  }, [finished])

  const mins = Math.floor(remaining / 60)
  const secs = remaining % 60
  const pct = total > 0 ? (remaining / total) * 100 : 0

  const isWarning = remaining <= 5 * 60 && remaining > 0
  const isDanger  = remaining <= 2 * 60 && remaining > 0

  const colorClass = finished
    ? (isLight ? 'text-red-600 font-black' : 'text-red-400')
    : isDanger
    ? (isLight ? 'text-red-600 font-black' : 'text-red-400')
    : isWarning
    ? (isLight ? 'text-amber-700 font-black' : 'text-amber-400')
    : running
    ? (isLight ? 'text-emerald-700 font-black' : 'text-emerald-400')
    : (isLight ? 'text-slate-800 font-bold' : 'text-white/60')

  const trackColor = finished
    ? '#dc2626'
    : isDanger
    ? '#e11d48'
    : isWarning
    ? '#d97706'
    : running
    ? '#16a34a'
    : (isLight ? '#7c3aed' : '#8b5cf6')

  return (
    <div className={`flex items-center gap-2 px-2.5 sm:px-3 py-1.5 rounded-xl border transition-all ${
      finished
        ? (isLight ? 'bg-red-50 border-red-300 shadow-sm' : 'bg-red-500/10 border-red-500/30')
        : isDanger
        ? (isLight ? 'bg-red-50 border-red-200' : 'bg-red-500/8 border-red-500/20')
        : isWarning
        ? (isLight ? 'bg-amber-50 border-amber-200' : 'bg-amber-500/8 border-amber-500/20')
        : running
        ? (isLight ? 'bg-emerald-50 border-emerald-300 shadow-sm' : 'bg-emerald-500/5 border-emerald-500/15')
        : (isLight ? 'bg-white border-slate-200 shadow-sm' : 'bg-white/4 border-white/8')
    }`}>

      {/* Circular mini-progress */}
      <div className="relative w-6 sm:w-7 h-6 sm:h-7 shrink-0">
        <svg viewBox="0 0 28 28" className="w-full h-full -rotate-90">
          <circle
            cx="14" cy="14" r="11" fill="none"
            stroke={isLight ? '#e2e8f0' : 'rgba(255,255,255,0.08)'}
            strokeWidth="2.5"
          />
          <circle
            cx="14" cy="14" r="11" fill="none"
            stroke={trackColor}
            strokeWidth="2.5"
            strokeLinecap="round"
            strokeDasharray={`${2 * Math.PI * 11}`}
            strokeDashoffset={`${2 * Math.PI * 11 * (1 - pct / 100)}`}
            style={{ transition: 'stroke-dashoffset 1s linear, stroke 0.3s' }}
          />
        </svg>
        <div className="absolute inset-0 flex items-center justify-center">
          {finished
            ? <AlertTriangle size={10} className="text-red-500" />
            : <Timer size={10} className={colorClass} />
          }
        </div>
      </div>

      {/* Time display */}
      <span className={`font-mono text-xs sm:text-sm tabular-nums ${colorClass} ${isDanger && running ? 'animate-pulse' : ''}`}>
        {String(mins).padStart(2, '0')}:{String(secs).padStart(2, '0')}
      </span>

      {finished && (
        <span className="text-red-600 text-xs font-bold animate-pulse">Over!</span>
      )}

      {/* Controls */}
      <div className="flex items-center gap-1">
        <button
          onClick={toggle}
          disabled={finished}
          title={running ? 'Pause' : 'Start timer'}
          className={`p-1 rounded-lg border transition-all disabled:opacity-30 ${
            running
              ? isLight
                ? 'bg-amber-100 border-amber-300 text-amber-900 hover:bg-amber-200'
                : 'bg-amber-500/15 border-amber-500/30 text-amber-400 hover:bg-amber-500/25'
              : isLight
              ? 'bg-violet-100 border-violet-300 text-violet-800 hover:bg-violet-200 shadow-sm'
              : 'bg-violet-500/15 border-violet-500/30 text-violet-400 hover:bg-violet-500/25'
          }`}
        >
          {running ? <Pause size={11} /> : <Play size={11} />}
        </button>
        <button
          onClick={reset}
          title="Reset timer"
          className={`p-1 rounded-lg border transition-all ${
            isLight
              ? 'bg-slate-100 border-slate-200 text-slate-600 hover:text-slate-900 hover:bg-slate-200'
              : 'bg-white/4 border-white/10 text-white/30 hover:text-white/60 hover:border-white/20'
          }`}
        >
          <RotateCcw size={11} />
        </button>
      </div>
    </div>
  )
}

import React, { useState, useEffect, useRef, useCallback } from 'react'
import { Timer, Play, Pause, RotateCcw, AlertTriangle } from 'lucide-react'

// Default time per difficulty (seconds)
const DEFAULT_TIME = { Easy: 20 * 60, Medium: 30 * 60, Hard: 45 * 60 }

export default function InterviewTimer({ difficulty = 'Medium' }) {
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
    ? 'text-red-400'
    : isDanger
    ? 'text-red-400'
    : isWarning
    ? 'text-amber-400'
    : running
    ? 'text-emerald-400'
    : 'text-white/50'

  const trackColor = finished
    ? '#f43f5e'
    : isDanger
    ? '#f43f5e'
    : isWarning
    ? '#f59e0b'
    : '#8b5cf6'

  return (
    <div className={`flex items-center gap-2 px-3 py-1.5 rounded-xl border transition-all ${
      finished
        ? 'bg-red-500/10 border-red-500/30'
        : isDanger
        ? 'bg-red-500/8 border-red-500/20'
        : isWarning
        ? 'bg-amber-500/8 border-amber-500/20'
        : running
        ? 'bg-emerald-500/5 border-emerald-500/15'
        : 'bg-white/3 border-white/8'
    }`}>

      {/* Circular mini-progress */}
      <div className="relative w-7 h-7 shrink-0">
        <svg viewBox="0 0 28 28" className="w-full h-full -rotate-90">
          <circle cx="14" cy="14" r="11" fill="none" stroke="rgba(255,255,255,0.06)" strokeWidth="2.5" />
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
            ? <AlertTriangle size={10} className="text-red-400" />
            : <Timer size={9} className={colorClass} />
          }
        </div>
      </div>

      {/* Time display */}
      <span className={`font-mono text-sm font-bold tabular-nums ${colorClass} ${isDanger && running ? 'animate-pulse' : ''}`}>
        {String(mins).padStart(2, '0')}:{String(secs).padStart(2, '0')}
      </span>

      {finished && (
        <span className="text-red-400 text-xs font-medium animate-pulse">Time up!</span>
      )}

      {/* Controls */}
      <div className="flex items-center gap-1 ml-0.5">
        <button
          onClick={toggle}
          disabled={finished}
          title={running ? 'Pause' : 'Start timer'}
          className={`p-1 rounded-lg border transition-all disabled:opacity-30 ${
            running
              ? 'bg-amber-500/15 border-amber-500/30 text-amber-400 hover:bg-amber-500/25'
              : 'bg-violet-500/15 border-violet-500/30 text-violet-400 hover:bg-violet-500/25'
          }`}
        >
          {running ? <Pause size={11} /> : <Play size={11} />}
        </button>
        <button
          onClick={reset}
          title="Reset timer"
          className="p-1 rounded-lg border bg-white/4 border-white/10 text-white/30 hover:text-white/60 hover:border-white/20 transition-all"
        >
          <RotateCcw size={11} />
        </button>
      </div>
    </div>
  )
}

import React, { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { Gift, Sparkles, X, CheckCircle2, ArrowRight, Zap, Trophy, Flame } from 'lucide-react'

const EARLY_BIRD_KEY = 'bittu_ai_early_bird_seen'
const EARLY_BIRD_CLAIMED_KEY = 'bittu_ai_early_bird_claimed'

export default function EarlyBirdModal({ forceOpen = false, onCloseCustom }) {
  const [isOpen, setIsOpen] = useState(false)
  const navigate = useNavigate()

  useEffect(() => {
    const handleOpen = () => setIsOpen(true)
    window.addEventListener('open-early-bird', handleOpen)
    return () => window.removeEventListener('open-early-bird', handleOpen)
  }, [])

  useEffect(() => {
    if (forceOpen) {
      setIsOpen(true)
      return
    }

    // Auto show once after 1.5 seconds if not already claimed/dismissed
    const claimed = localStorage.getItem(EARLY_BIRD_CLAIMED_KEY)
    const seen = localStorage.getItem(EARLY_BIRD_KEY)

    if (!claimed && !seen) {
      const timer = setTimeout(() => {
        setIsOpen(true)
      }, 1500)
      return () => clearTimeout(timer)
    }
  }, [forceOpen])

  const handleClose = () => {
    setIsOpen(false)
    localStorage.setItem(EARLY_BIRD_KEY, 'true')
    onCloseCustom?.()
  }

  const handleClaim = () => {
    localStorage.setItem(EARLY_BIRD_CLAIMED_KEY, 'true')
    localStorage.setItem(EARLY_BIRD_KEY, 'true')
    setIsOpen(false)
    onCloseCustom?.()
    navigate('/dsa')
  }

  if (!isOpen) return null

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center p-3 sm:p-4 bg-black/75 backdrop-blur-md animate-fadeIn">
      <div className="relative w-full max-w-lg rounded-3xl border border-amber-500/30 bg-gradient-to-b from-[#180e29] via-[#0d0718] to-[#080210] p-6 sm:p-8 text-white shadow-2xl shadow-amber-500/15 overflow-hidden">

        {/* Ambient Top Glow */}
        <div className="absolute -top-24 left-1/2 -translate-x-1/2 w-80 h-80 rounded-full bg-gradient-to-b from-amber-500/20 via-violet-600/15 to-transparent blur-3xl pointer-events-none" />

        {/* Close Button */}
        <button
          onClick={handleClose}
          className="absolute top-4 right-4 p-2 rounded-full border border-white/10 bg-white/5 text-white/50 hover:text-white hover:bg-white/10 transition-all z-10"
          title="Close offer"
        >
          <X size={16} />
        </button>

        {/* Top Icon Badge */}
        <div className="relative z-10 flex flex-col items-center text-center">
          <div className="relative mb-3.5">
            <div className="w-16 h-16 rounded-2xl bg-gradient-to-tr from-amber-500 via-orange-500 to-violet-600 flex items-center justify-center shadow-lg shadow-amber-500/30 text-white animate-bounce-slow">
              <Gift size={32} />
            </div>
            <div className="absolute -top-1 -right-1 p-1 rounded-full bg-amber-400 text-slate-950">
              <Sparkles size={12} />
            </div>
          </div>

          {/* Offer Pill */}
          <div className="inline-flex items-center gap-1.5 px-3 py-1 rounded-full bg-amber-500/15 border border-amber-500/30 text-amber-300 text-xs font-mono font-bold uppercase tracking-wider mb-2.5">
            <Flame size={13} className="text-amber-400" />
            Special Early Bird Offer
          </div>

          {/* Headline */}
          <h2 className="text-xl sm:text-2xl font-black tracking-tight text-white mb-2 leading-snug">
            पहले <span className="bg-gradient-to-r from-amber-400 via-orange-400 to-amber-200 bg-clip-text text-transparent">100 लोगों के लिए</span> Free DSA Access!
          </h2>

          <p className="text-xs sm:text-sm text-white/70 leading-relaxed max-w-md mb-5">
            Join India's fastest growing developer platform. First 100 engineers get <strong className="text-amber-300 font-semibold">100% Free Lifetime Access</strong> to all 1,800 curated DSA problems, Monaco Python editor, visual diff, and weekly algorithmic contests!
          </p>

          {/* Spots Remaining Meter (Simulated Urgency) */}
          <div className="w-full bg-white/5 border border-white/10 rounded-2xl p-3.5 mb-5 text-left">
            <div className="flex items-center justify-between text-xs mb-1.5">
              <span className="text-white/70 font-medium flex items-center gap-1.5">
                <span className="w-2 h-2 rounded-full bg-emerald-400 animate-ping" />
                Claimed Passes:
              </span>
              <span className="font-mono font-bold text-amber-300">
                87 / 100 Claimed <span className="text-white/40 font-normal">(Only 13 Left!)</span>
              </span>
            </div>

            <div className="w-full h-2 rounded-full bg-white/10 overflow-hidden">
              <div
                className="h-full bg-gradient-to-r from-amber-500 via-orange-500 to-emerald-500 rounded-full transition-all duration-1000"
                style={{ width: '87%' }}
              />
            </div>
          </div>

          {/* What You Get Included (4 Perks) */}
          <div className="w-full grid grid-cols-2 gap-2 mb-6 text-left">
            {[
              { text: '1,800 Curated Problems' },
              { text: 'In-Browser Python WASM' },
              { text: 'FAANG Optimal Code Diff' },
              { text: 'Global Weekly Contests' }
            ].map((item, i) => (
              <div key={i} className="flex items-center gap-2 p-2 rounded-xl bg-white/[0.02] border border-white/5 text-xs text-white/80">
                <CheckCircle2 size={13} className="text-emerald-400 shrink-0" />
                <span className="truncate">{item.text}</span>
              </div>
            ))}
          </div>

          {/* Claim Action Button */}
          <button
            onClick={handleClaim}
            className="w-full py-3.5 px-6 rounded-2xl font-bold text-sm bg-gradient-to-r from-amber-500 via-orange-500 to-amber-400 text-slate-950 shadow-xl shadow-amber-500/25 hover:shadow-amber-500/40 hover:scale-[1.02] active:scale-[0.98] transition-all flex items-center justify-center gap-2"
          >
            <Zap size={16} className="fill-slate-950" />
            <span>Claim Free Lifetime Access Now</span>
            <ArrowRight size={16} />
          </button>

          <button
            onClick={handleClose}
            className="mt-3 text-xs text-white/40 hover:text-white/70 transition-colors"
          >
            I will claim later
          </button>
        </div>
      </div>
    </div>
  )
}

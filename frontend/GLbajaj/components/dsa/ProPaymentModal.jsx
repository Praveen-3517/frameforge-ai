import React, { useState, useEffect } from 'react'
import {
  Crown, Check, Zap, ShieldCheck, Sparkles,
  X, Lock, ArrowRight, CreditCard, Smartphone,
  Loader2, CheckCircle2, AlertCircle
} from 'lucide-react'
import { getApiUrl } from '../../utils/apiUrl'
import { saveProStatus } from '../../utils/proSubscription'
import { useAuth } from '../../context/AuthContext'

/**
 * Ensures Razorpay Checkout SDK is loaded in window
 */
function loadRazorpayScript() {
  return new Promise((resolve) => {
    if (typeof window !== 'undefined' && window.Razorpay) {
      resolve(true)
      return
    }

    const existingScript = document.querySelector('script[src*="checkout.razorpay.com"]')
    if (existingScript) {
      let attempts = 0
      const check = setInterval(() => {
        attempts++
        if (window.Razorpay) {
          clearInterval(check)
          resolve(true)
        } else if (attempts > 20) {
          clearInterval(check)
          resolve(!!window.Razorpay)
        }
      }, 100)
      return
    }

    const script = document.createElement('script')
    script.id = 'razorpay-sdk'
    script.src = 'https://checkout.razorpay.com/v1/checkout.js'
    script.async = true
    script.onload = () => resolve(true)
    script.onerror = () => resolve(false)
    document.body.appendChild(script)
  })
}

export default function ProPaymentModal({ isOpen, onClose, onSuccess, isLight = false }) {
  const { user } = useAuth()
  
  const [name, setName] = useState('')
  const [email, setEmail] = useState('')
  const [phone, setPhone] = useState('')
  
  const [loading, setLoading] = useState(false)
  const [statusMsg, setStatusMsg] = useState('')
  const [errorMsg, setErrorMsg] = useState('')
  const [successData, setSuccessData] = useState(null)

  // Pre-fill user data and preload Razorpay SDK on modal open
  useEffect(() => {
    if (isOpen) {
      loadRazorpayScript().catch(() => {})
    }
    if (user) {
      if (user.email && !email) setEmail(user.email)
      const userFullName = user.user_metadata?.full_name || user.fullName || ''
      if (userFullName && !name) setName(userFullName)
    }
  }, [user, isOpen])

  if (!isOpen) return null

  const handlePayment = async (e) => {
    e?.preventDefault()
    setErrorMsg('')

    const trimmedEmail = email.trim()
    if (!trimmedEmail || !trimmedEmail.includes('@')) {
      setErrorMsg('Please enter a valid email address for your payment receipt.')
      return
    }

    setLoading(true)
    setStatusMsg('Opening secure Razorpay UPI & Card checkout...')

    try {
      const apiUrl = getApiUrl()

      // Create official Razorpay checkout link (100% AdBlock-proof, works on all devices)
      const linkRes = await fetch(`${apiUrl}/api/payment/create-payment-link`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          amount: 149,
          email: trimmedEmail,
          name: name.trim() || 'Student Coder',
          plan_name: 'DSA Master Lifetime Pass (Java + C)'
        })
      })

      if (!linkRes.ok) {
        const errData = await linkRes.json().catch(() => ({}))
        throw new Error(errData.detail || errData.error || 'Failed to initialize payment gateway.')
      }

      const linkData = await linkRes.json()
      if (linkData.payment_link) {
        // Save user email to localStorage so status syncs immediately on return
        localStorage.setItem('user_email', trimmedEmail)
        setStatusMsg('Redirecting to official Razorpay payment page...')
        window.location.href = linkData.payment_link
        return
      }

      throw new Error('Could not generate payment link. Please try again.')
    } catch (err) {
      console.error('[Payment] Error:', err)
      setErrorMsg(err.message || 'Unable to open payment checkout. Please try again.')
      setLoading(false)
      setStatusMsg('')
    }
  }

  return (
    <div className="fixed inset-0 z-[100] flex items-center justify-center p-3 sm:p-4 bg-black/80 backdrop-blur-md animate-fadeIn">
      <div className={`relative w-full max-w-lg rounded-3xl border shadow-2xl overflow-hidden transition-all duration-300 ${
        isLight
          ? 'bg-white border-slate-200 text-slate-900 shadow-purple-500/10'
          : 'bg-[#0d091a] border-violet-500/30 text-white shadow-violet-950/60'
      }`}>
        
        {/* Ambient Top Glow */}
        <div className="absolute top-0 left-1/2 -translate-x-1/2 w-3/4 h-24 bg-gradient-to-r from-amber-500/20 via-violet-600/30 to-cyan-500/20 blur-2xl pointer-events-none" />

        {/* Close Button */}
        <button
          onClick={onClose}
          disabled={loading}
          className={`absolute top-4 right-4 p-2 rounded-full transition-colors z-20 ${
            isLight
              ? 'hover:bg-slate-100 text-slate-400 hover:text-slate-800'
              : 'hover:bg-white/10 text-white/40 hover:text-white'
          }`}
          aria-label="Close"
        >
          <X size={18} />
        </button>

        {/* ─── SUCCESS STATE ─── */}
        {successData ? (
          <div className="p-6 sm:p-8 text-center">
            <div className="w-16 h-16 rounded-3xl bg-emerald-500/15 border border-emerald-500/30 text-emerald-400 flex items-center justify-center mx-auto mb-4 shadow-lg shadow-emerald-500/20 animate-bounce">
              <CheckCircle2 size={36} />
            </div>

            <div className="inline-flex items-center gap-1.5 px-3 py-1 rounded-full bg-amber-500/15 border border-amber-500/30 text-amber-400 text-xs font-bold mb-3">
              <Crown size={13} className="text-amber-400" />
              <span>BITTU AI PRO MEMBER</span>
            </div>

            <h3 className="text-2xl font-black mb-2 tracking-tight">
              Payment Successful! 🎉
            </h3>
            <p className={`text-sm mb-6 max-w-sm mx-auto leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/70'}`}>
              Congratulations! Your <strong>DSA Master Lifetime Pass (Java + C)</strong> is now active. All 554+ problems, solutions, and premium features are unlocked permanently!
            </p>

            <div className={`p-3.5 rounded-2xl border text-xs font-mono mb-6 text-left ${
              isLight ? 'bg-slate-50 border-slate-200 text-slate-700' : 'bg-white/5 border-white/10 text-white/80'
            }`}>
              <div className="flex justify-between py-1 border-b border-white/5">
                <span>Account:</span>
                <span className="font-bold">{successData.email}</span>
              </div>
              <div className="flex justify-between py-1 border-b border-white/5">
                <span>Plan:</span>
                <span className="font-bold text-amber-500">₹149 Master Lifetime Pass (Java + C)</span>
              </div>
              <div className="flex justify-between py-1">
                <span>Status:</span>
                <span className="text-emerald-500 font-bold">● Lifetime Active</span>
              </div>
            </div>

            <button
              type="button"
              onClick={() => {
                onClose()
                if (onSuccess) onSuccess(successData)
              }}
              className="w-full py-3.5 rounded-xl font-bold text-sm bg-gradient-to-r from-violet-600 via-purple-600 to-cyan-500 text-white shadow-lg shadow-violet-600/30 hover:opacity-95 active:scale-[0.98] transition-all flex items-center justify-center gap-2 cursor-pointer"
            >
              <span>Start Solving Top Interview Questions</span>
              <ArrowRight size={16} />
            </button>
          </div>
        ) : (
          /* ─── CHECKOUT & PLAN DETAILS ─── */
          <div className="p-6 sm:p-7">
            {/* Header Badge & Brand Logo */}
            <div className="flex items-center gap-3 mb-3">
              <img
                src="/bittu-logo.jpg"
                alt="Bittu AI"
                className="w-11 h-11 rounded-2xl object-cover shadow-lg shadow-violet-500/25 border border-violet-400/30 shrink-0"
              />
              <div>
                <div className="flex items-center gap-2 mb-0.5">
                  <span className="inline-flex items-center gap-1.5 px-2.5 py-0.5 rounded-full bg-gradient-to-r from-amber-500/20 via-orange-500/20 to-cyan-500/20 border border-amber-500/40 text-amber-400 text-[10px] font-mono font-bold tracking-wider uppercase">
                    <Crown size={11} className="text-amber-400" />
                    DSA Master Pass
                  </span>
                  <span className="inline-flex items-center gap-1 px-2 py-0.5 rounded-full bg-emerald-500/15 border border-emerald-500/30 text-emerald-400 text-[10px] font-bold">
                    <Sparkles size={10} /> Lifetime Access
                  </span>
                </div>
                <span className="text-xs font-bold text-slate-500 dark:text-slate-400">
                  Java + C Complete Track
                </span>
              </div>
            </div>

            <h3 className="text-xl sm:text-2xl font-black tracking-tight mb-1.5">
              Unlock DSA with Java & DSA with C
            </h3>
            <p className={`text-xs sm:text-sm mb-4 leading-relaxed ${isLight ? 'text-slate-600' : 'text-white/70'}`}>
              Get full lifetime access to both <strong>DSA with Java (554+ Problems)</strong> and <strong>DSA with C (554+ Problems)</strong> with optimal code, Hindi/English explanations, and live compilers.
            </p>

            {/* Price Box */}
            <div className={`p-4 rounded-2xl border mb-5 flex items-center justify-between transition-all ${
              isLight
                ? 'bg-gradient-to-r from-violet-50 via-purple-50 to-amber-50 border-violet-200'
                : 'bg-gradient-to-r from-violet-950/40 via-purple-900/30 to-amber-950/20 border-violet-500/30'
            }`}>
              <div>
                <div className="flex items-baseline gap-2">
                  <span className={`text-3xl sm:text-4xl font-black ${isLight ? 'text-violet-900' : 'text-white'}`}>
                    ₹149
                  </span>
                  <span className={`text-xs line-through ${isLight ? 'text-slate-400' : 'text-white/40'}`}>
                    ₹4,999 (Coding Institutes)
                  </span>
                </div>
                <p className={`text-[11px] font-medium mt-0.5 ${isLight ? 'text-violet-700' : 'text-amber-300/90'}`}>
                  🔥 One-Time Payment · Lifetime Validity (No Recurring Fees)
                </p>
              </div>
              <div className="text-right">
                <span className="inline-block px-2.5 py-1 rounded-xl bg-gradient-to-r from-amber-500 to-orange-600 text-white text-[11px] font-bold shadow-md shadow-orange-500/30">
                  Lifetime Pass
                </span>
              </div>
            </div>

            {/* Value checklist */}
            <div className="space-y-2 mb-5">
              {[
                { title: '☕ Complete DSA with Java', desc: '554+ Problems, Collections, OOPs & Optimal Algorithms.' },
                { title: '⚡ Complete DSA with C Language', desc: '554+ Problems, Pointers, Memory Allocation & Structs.' },
                { title: '🎯 Optimal Code & Hindi/English Logic', desc: 'Instant solution viewer, diff comparer & interview hints.' },
                { title: '♾️ Lifetime Access on All Devices', desc: 'One-time ₹149 payment. Use anytime across mobile & laptop.' },
              ].map((item, idx) => (
                <div key={idx} className="flex items-start gap-2.5 text-xs">
                  <div className="w-4 h-4 rounded-full bg-emerald-500/20 text-emerald-400 flex items-center justify-center shrink-0 mt-0.5">
                    <Check size={10} strokeWidth={3} />
                  </div>
                  <div>
                    <span className={`font-bold ${isLight ? 'text-slate-800' : 'text-white'}`}>{item.title}: </span>
                    <span className={isLight ? 'text-slate-500' : 'text-white/60'}>{item.desc}</span>
                  </div>
                </div>
              ))}
            </div>

            {/* User Details Form */}
            <form onSubmit={handlePayment} className="space-y-3">
              <div className="grid grid-cols-1 sm:grid-cols-2 gap-2.5">
                <div>
                  <label className={`block text-[11px] font-semibold mb-1 ${isLight ? 'text-slate-700' : 'text-white/80'}`}>
                    Your Email (for receipt) <span className="text-rose-500">*</span>
                  </label>
                  <input
                    type="email"
                    required
                    value={email}
                    onChange={(e) => setEmail(e.target.value)}
                    placeholder="student@gmail.com"
                    disabled={loading}
                    className={`w-full px-3 py-2 rounded-xl text-xs border outline-none transition-all ${
                      isLight
                        ? 'bg-slate-50 border-slate-300 text-slate-900 focus:border-violet-500 focus:bg-white'
                        : 'bg-white/5 border-white/10 text-white focus:border-violet-400 focus:bg-white/10'
                    }`}
                  />
                </div>
                <div>
                  <label className={`block text-[11px] font-semibold mb-1 ${isLight ? 'text-slate-700' : 'text-white/80'}`}>
                    Full Name (Optional)
                  </label>
                  <input
                    type="text"
                    value={name}
                    onChange={(e) => setName(e.target.value)}
                    placeholder="Enter your full name"
                    disabled={loading}
                    className={`w-full px-3 py-2 rounded-xl text-xs border outline-none transition-all ${
                      isLight
                        ? 'bg-slate-50 border-slate-300 text-slate-900 focus:border-violet-500 focus:bg-white'
                        : 'bg-white/5 border-white/10 text-white focus:border-violet-400 focus:bg-white/10'
                    }`}
                  />
                </div>
              </div>

              {/* Error Banner */}
              {errorMsg && (
                <div className="flex items-center gap-2 p-2.5 rounded-xl bg-rose-500/15 border border-rose-500/30 text-rose-400 text-xs">
                  <AlertCircle size={14} className="shrink-0" />
                  <span>{errorMsg}</span>
                </div>
              )}

              {/* Status Message */}
              {loading && statusMsg && (
                <div className="flex items-center justify-center gap-2 py-1 text-xs text-violet-400 animate-pulse font-medium">
                  <Loader2 size={14} className="animate-spin" />
                  <span>{statusMsg}</span>
                </div>
              )}

              {/* Pay Button */}
              <button
                type="submit"
                disabled={loading}
                className="w-full py-3.5 rounded-xl font-bold text-sm bg-gradient-to-r from-violet-600 via-purple-600 to-indigo-600 hover:from-violet-500 hover:to-indigo-500 text-white shadow-lg shadow-violet-600/35 active:scale-[0.98] transition-all flex items-center justify-center gap-2 cursor-pointer disabled:opacity-50 disabled:cursor-not-allowed"
              >
                {loading ? (
                  <>
                    <Loader2 size={16} className="animate-spin" />
                    <span>Processing Secure Payment...</span>
                  </>
                ) : (
                  <>
                    <Zap size={16} className="text-amber-300 fill-amber-300" />
                    <span>Pay ₹149 & Unlock Lifetime Pass</span>
                    <ArrowRight size={15} />
                  </>
                )}
              </button>

              {/* Payment Methods Pill & Security Trust Badge */}
              <div className="flex flex-wrap items-center justify-center gap-3 pt-1 text-[10px] text-slate-400">
                <span className="flex items-center gap-1">
                  <Smartphone size={11} className="text-violet-400" />
                  <span>UPI / PhonePe / GPay / Paytm</span>
                </span>
                <span>•</span>
                <span className="flex items-center gap-1">
                  <CreditCard size={11} className="text-violet-400" />
                  <span>Debit & Credit Cards</span>
                </span>
                <span>•</span>
                <span className="flex items-center gap-1">
                  <ShieldCheck size={11} className="text-emerald-400" />
                  <span>256-Bit Razorpay Secured</span>
                </span>
              </div>
            </form>
          </div>
        )}
      </div>
    </div>
  )
}

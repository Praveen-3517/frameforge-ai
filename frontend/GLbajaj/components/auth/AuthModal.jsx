import React, { useState, useMemo, useEffect, useRef } from 'react'
import {
  X, Mail, Lock, User, Sparkles, AlertCircle,
  CheckCircle2, ArrowRight, Eye, EyeOff, Loader2,
  ShieldCheck, XCircle, ArrowLeft, RefreshCw, KeyRound, Check
} from 'lucide-react'
import { useAuth } from '../../context/AuthContext'

// ─── Email Validation ──────────────────────────────────────────────────────────
const EMAIL_RE = /^[a-zA-Z0-9._%+\-]+@[a-zA-Z0-9.\-]+\.[a-zA-Z]{2,10}$/

// Common fake/throwaway domain blocklist
const BLOCKED_DOMAINS = new Set([
  'mailinator.com', 'guerrillamail.com', 'tempmail.com', 'throwam.com',
  'maildrop.cc', 'yopmail.com', 'sharklasers.com', 'trashmail.com',
  'fakeinbox.com', 'dispostable.com', 'mailnull.com', 'spamgourmet.com',
  'trashmail.net', 'discard.email', 'spamhereplease.com',
  'spam4.me', 'binkmail.com', 'safetymail.info', '10minutemail.com',
])

function validateEmail(email) {
  const trimmed = email.trim().toLowerCase()
  if (!trimmed) return 'Email address is required.'
  if (!EMAIL_RE.test(trimmed)) return 'Please enter a valid email address.'
  const domain = trimmed.split('@')[1]
  if (BLOCKED_DOMAINS.has(domain)) return 'Temporary/disposable email addresses are not allowed.'
  if (!domain.includes('.')) return 'Email domain is invalid.'
  return null
}

// ─── Password Rules ────────────────────────────────────────────────────────────
const PASSWORD_RULES = [
  { id: 'length',    label: 'At least 8 characters',            test: (p) => p.length >= 8 },
  { id: 'uppercase', label: 'One uppercase letter (A–Z)',        test: (p) => /[A-Z]/.test(p) },
  { id: 'lowercase', label: 'One lowercase letter (a–z)',        test: (p) => /[a-z]/.test(p) },
  { id: 'number',    label: 'One number (0–9)',                  test: (p) => /[0-9]/.test(p) },
  { id: 'special',   label: 'One special character (!@#$%^&*)',  test: (p) => /[!@#$%^&*()\-_=+\[\]{};:'",.<>?/\\|`~]/.test(p) },
]

function getPasswordStrength(password) {
  const passed = PASSWORD_RULES.filter(r => r.test(password)).length
  if (passed <= 1) return { score: passed, label: 'Very Weak',  color: 'bg-red-500' }
  if (passed === 2) return { score: passed, label: 'Weak',       color: 'bg-orange-500' }
  if (passed === 3) return { score: passed, label: 'Fair',       color: 'bg-yellow-400' }
  if (passed === 4) return { score: passed, label: 'Strong',     color: 'bg-emerald-400' }
  return              { score: passed, label: 'Very Strong', color: 'bg-emerald-500' }
}

export default function AuthModal({ isLight = false }) {
  const {
    isAuthModalOpen,
    closeAuthModal,
    authMode,
    setAuthMode,
    signIn,
    signUp,
    sendOtp,
    verifyOtp,
  } = useAuth()

  // Form State
  const [fullName,     setFullName]     = useState('')
  const [email,        setEmail]        = useState('')
  const [password,     setPassword]     = useState('')
  const [showPassword, setShowPassword] = useState(false)
  const [emailError,   setEmailError]   = useState(null)
  const [error,        setError]        = useState(null)
  const [success,      setSuccess]      = useState(null)
  const [loading,      setLoading]      = useState(false)
  const [touched,      setTouched]      = useState({ email: false, password: false })

  // OTP Verification Wizard State (for signup)
  const [signupStep,   setSignupStep]   = useState('form') // 'form' | 'otp'
  const [otpValue,     setOtpValue]     = useState('')
  const [otpCooldown,  setOtpCooldown]  = useState(0)
  const [devOtpHint,   setDevOtpHint]   = useState(null)
  const [resending,    setResending]    = useState(false)

  const [loadingElapsed, setLoadingElapsed] = useState(0)

  // Track elapsed seconds while waiting for cloud server to wake up
  useEffect(() => {
    let interval = null
    if (loading) {
      setLoadingElapsed(0)
      interval = setInterval(() => {
        setLoadingElapsed(s => s + 1)
      }, 1000)
    } else {
      setLoadingElapsed(0)
    }
    return () => clearInterval(interval)
  }, [loading])

  // Countdown timer for OTP resend
  useEffect(() => {
    if (otpCooldown <= 0) return
    const timer = setInterval(() => {
      setOtpCooldown(c => Math.max(0, c - 1))
    }, 1000)
    return () => clearInterval(timer)
  }, [otpCooldown])

  // Focus OTP input when switching to OTP step
  useEffect(() => {
    if (signupStep === 'otp') {
      setTimeout(() => {
        otpInputRef.current?.focus()
      }, 100)
    }
  }, [signupStep])

  if (!isAuthModalOpen) return null

  const activeIsLight = isLight ||
    (typeof document !== 'undefined' && document.documentElement.classList.contains('light')) ||
    (typeof localStorage !== 'undefined' && localStorage.getItem('dsa_theme') === 'light')

  const isSignUp = authMode === 'signup'

  // Live password strength
  const strength = getPasswordStrength(password)
  const ruleResults = PASSWORD_RULES.map(r => ({ ...r, passed: r.test(password) }))
  const allRulesPassed = ruleResults.every(r => r.passed)

  const handleEmailBlur = () => {
    setTouched(t => ({ ...t, email: true }))
    setEmailError(validateEmail(email))
  }

  // ── Step 1: Initial Form Submission ─────────────────────────────────────────
  const handleFormSubmit = async (e) => {
    e.preventDefault()
    setError(null)
    setSuccess(null)

    // Validate email
    const emailErr = validateEmail(email)
    if (emailErr) {
      setEmailError(emailErr)
      setTouched(t => ({ ...t, email: true }))
      return
    }

    if (isSignUp) {
      // Validate full name
      if (!fullName.trim() || fullName.trim().length < 2) {
        setError('Please enter your full name (at least 2 characters).')
        return
      }
      // Validate password strength
      if (!allRulesPassed) {
        setError('Password does not meet the strength requirements below.')
        setTouched(t => ({ ...t, password: true }))
        return
      }

      // Trigger Email OTP dispatch
      setLoading(true)
      try {
        const res = await sendOtp(email)
        setSignupStep('otp')
        setOtpCooldown(60)
        setOtpValue('')
        if (res?.dev_otp) {
          setDevOtpHint(res.dev_otp)
        }
        setSuccess(`Verification code sent to ${email.trim().toLowerCase()}`)
        setTimeout(() => setSuccess(null), 3500)
      } catch (err) {
        setError(err.message || 'Failed to send verification code. Please try again.')
      } finally {
        setLoading(false)
      }

    } else {
      // Direct Sign-In
      if (password.length < 8) {
        setError('Password must be at least 8 characters.')
        return
      }

      setLoading(true)
      try {
        await signIn(email.trim().toLowerCase(), password)
        setSuccess('Signed in successfully! Welcome back.')
        setTimeout(() => {
          closeAuthModal()
          resetForm()
        }, 1000)
      } catch (err) {
        setError(err.message || 'Invalid email or password. Please try again.')
      } finally {
        setLoading(false)
      }
    }
  }

  // ── Step 2: OTP Verification & Account Creation ──────────────────────────────
  const handleVerifyOtpSubmit = async (e) => {
    e.preventDefault()
    setError(null)
    setSuccess(null)

    const cleanOtp = otpValue.trim()
    if (cleanOtp.length !== 6 || !/^\d{6}$/.test(cleanOtp)) {
      setError('Please enter the complete 6-digit verification code.')
      return
    }

    setLoading(true)
    try {
      // 1. Verify code on backend
      await verifyOtp(email, cleanOtp)

      // 2. Finalize account creation
      await signUp(email.trim().toLowerCase(), password, fullName.trim())
      setSuccess(`🎉 Account verified and created! Welcome, ${fullName.trim().split(' ')[0]}!`)
      
      setTimeout(() => {
        closeAuthModal()
        resetForm()
      }, 1400)
    } catch (err) {
      setError(err.message || 'Invalid or expired verification code.')
    } finally {
      setLoading(false)
    }
  }

  // Resend OTP handler
  const handleResendOtp = async () => {
    if (otpCooldown > 0 || resending) return
    setError(null)
    setSuccess(null)
    setResending(true)
    try {
      const res = await sendOtp(email)
      setOtpCooldown(60)
      setOtpValue('')
      if (res?.dev_otp) {
        setDevOtpHint(res.dev_otp)
      }
      setSuccess('A new 6-digit verification code has been sent!')
      setTimeout(() => setSuccess(null), 3000)
    } catch (err) {
      setError(err.message || 'Failed to resend code. Please wait a moment.')
    } finally {
      setResending(false)
    }
  }

  const resetForm = () => {
    setEmail('')
    setPassword('')
    setFullName('')
    setOtpValue('')
    setSignupStep('form')
    setDevOtpHint(null)
    setError(null)
    setSuccess(null)
    setEmailError(null)
    setTouched({ email: false, password: false })
  }

  const switchMode = (mode) => {
    setAuthMode(mode)
    resetForm()
  }

  const inputBase = activeIsLight
    ? 'bg-white border-slate-300 text-slate-900 placeholder-slate-400 focus:border-violet-600 focus:ring-1 focus:ring-violet-600'
    : 'bg-white/5 border-white/10 text-white placeholder-white/20 focus:border-violet-500 focus:ring-1 focus:ring-violet-500'

  const labelBase = activeIsLight ? 'text-slate-700' : 'text-white/70'
  const iconBase  = activeIsLight ? 'text-slate-400' : 'text-white/30'
  const subText   = activeIsLight ? 'text-slate-500' : 'text-white/40'

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/75 backdrop-blur-md animate-fadeIn">
      <div
        className={`relative w-full max-w-md rounded-2xl border p-6 sm:p-8 shadow-2xl transition-all overflow-y-auto max-h-[95vh] ${
          activeIsLight
            ? 'bg-white border-slate-200 text-slate-900 shadow-slate-300/50'
            : 'bg-[#0f0a1c]/95 border-violet-500/30 text-white shadow-violet-900/20'
        }`}
      >
        {/* Close Button */}
        <button
          onClick={() => { closeAuthModal(); resetForm(); }}
          className={`absolute top-4 right-4 p-1.5 rounded-lg transition-colors ${
            activeIsLight ? 'hover:bg-slate-100 text-slate-400 hover:text-slate-800' : 'hover:bg-white/10 text-white/40 hover:text-white'
          }`}
        >
          <X size={18} />
        </button>

        {/* ════════════════════════════════════════════════════════════════════════
            STEP 1: LOGIN OR INITIAL SIGNUP FORM
           ════════════════════════════════════════════════════════════════════════ */}
        {signupStep === 'form' && (
          <>
            {/* Header */}
            <div className="text-center mb-6">
              <div className="w-12 h-12 rounded-xl bg-gradient-to-tr from-violet-600 to-cyan-500 flex items-center justify-center mx-auto mb-3 shadow-lg shadow-violet-500/30">
                <Sparkles size={22} className="text-white" />
              </div>
              <h2 className="text-xl font-bold tracking-tight">
                {isSignUp ? 'Create your Bittu AI account' : 'Welcome back to Bittu AI'}
              </h2>
              <p className={`text-xs mt-1 ${subText}`}>
                {isSignUp
                  ? 'Real email verification required to access AI creation tools.'
                  : 'Log in to access your cloud progress, streak, and AI history.'}
              </p>
            </div>

            {/* Mode Switcher Tabs */}
            <div className={`flex rounded-xl p-1 mb-5 border ${
              activeIsLight ? 'bg-slate-100 border-slate-200' : 'bg-white/5 border-white/10'
            }`}>
              {['signin', 'signup'].map((m) => (
                <button
                  key={m}
                  type="button"
                  onClick={() => switchMode(m)}
                  className={`flex-1 py-1.5 text-xs font-semibold rounded-lg transition-all ${
                    authMode === m
                      ? activeIsLight ? 'bg-white text-violet-700 shadow-sm' : 'bg-violet-600 text-white shadow-md'
                      : activeIsLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/40 hover:text-white'
                  }`}
                >
                  {m === 'signin' ? 'Sign In' : 'Create Account'}
                </button>
              ))}
            </div>

            {/* Feedback Alerts */}
            {error && (
              <div className="mb-4 p-3 rounded-xl bg-red-500/10 border border-red-500/20 text-red-400 text-xs flex items-start gap-2 animate-fadeIn">
                <AlertCircle size={15} className="shrink-0 mt-0.5" />
                <span>{error}</span>
              </div>
            )}
            {success && (
              <div className="mb-4 p-3 rounded-xl bg-emerald-500/10 border border-emerald-500/20 text-emerald-400 text-xs flex items-start gap-2 animate-fadeIn">
                <CheckCircle2 size={15} className="shrink-0 mt-0.5" />
                <span>{success}</span>
              </div>
            )}

            {/* Form */}
            <form onSubmit={handleFormSubmit} className="space-y-4" noValidate>

              {/* Full Name — Signup only */}
              {isSignUp && (
                <div>
                  <label className={`block text-xs font-semibold mb-1.5 ${labelBase}`}>
                    Full Name <span className="text-red-400">*</span>
                  </label>
                  <div className="relative">
                    <User size={15} className={`absolute left-3 top-1/2 -translate-y-1/2 ${iconBase}`} />
                    <input
                      type="text"
                      required
                      minLength={2}
                      maxLength={60}
                      placeholder="Enter your full name"
                      value={fullName}
                      onChange={(e) => { setFullName(e.target.value); if (error) setError(null); }}
                      className={`w-full pl-9 pr-4 py-2.5 rounded-xl text-xs border outline-none transition-all ${inputBase}`}
                    />
                  </div>
                </div>
              )}

              {/* Email Address */}
              <div>
                <label className={`block text-xs font-semibold mb-1.5 ${labelBase}`}>
                  Email Address <span className="text-red-400">*</span>
                </label>
                <div className="relative">
                  <Mail size={15} className={`absolute left-3 top-1/2 -translate-y-1/2 ${iconBase}`} />
                  <input
                    type="email"
                    required
                    autoComplete="email"
                    placeholder="name@example.com"
                    value={email}
                    onChange={(e) => {
                      setEmail(e.target.value)
                      setEmailError(null)
                      if (error) setError(null)
                    }}
                    onBlur={handleEmailBlur}
                    className={`w-full pl-9 pr-9 py-2.5 rounded-xl text-xs border outline-none transition-all ${
                      emailError && touched.email
                        ? 'border-red-500/60 focus:border-red-500 focus:ring-1 focus:ring-red-500'
                        : email && !emailError && touched.email
                        ? 'border-emerald-500/60 focus:border-emerald-500 focus:ring-1 focus:ring-emerald-500'
                        : inputBase
                    } ${activeIsLight ? 'bg-white text-slate-900 placeholder-slate-400' : 'bg-white/5 text-white placeholder-white/20'}`}
                  />
                  {touched.email && email && (
                    <span className="absolute right-3 top-1/2 -translate-y-1/2">
                      {emailError
                        ? <XCircle size={14} className="text-red-400" />
                        : <CheckCircle2 size={14} className="text-emerald-400" />
                      }
                    </span>
                  )}
                </div>
                {emailError && touched.email && (
                  <p className="mt-1.5 text-[11px] text-red-400 flex items-center gap-1">
                    <AlertCircle size={11} /> {emailError}
                  </p>
                )}
              </div>

              {/* Password */}
              <div>
                <label className={`block text-xs font-semibold mb-1.5 ${labelBase}`}>
                  Password <span className="text-red-400">*</span>
                  {isSignUp && (
                    <span className={`ml-2 font-normal ${subText}`}>
                      — must be strong
                    </span>
                  )}
                </label>
                <div className="relative">
                  <Lock size={15} className={`absolute left-3 top-1/2 -translate-y-1/2 ${iconBase}`} />
                  <input
                    type={showPassword ? 'text' : 'password'}
                    required
                    minLength={8}
                    autoComplete={isSignUp ? 'new-password' : 'current-password'}
                    placeholder="••••••••"
                    value={password}
                    onChange={(e) => {
                      setPassword(e.target.value)
                      setTouched(t => ({ ...t, password: true }))
                      if (error) setError(null)
                    }}
                    className={`w-full pl-9 pr-10 py-2.5 rounded-xl text-xs border outline-none transition-all ${inputBase}`}
                  />
                  <button
                    type="button"
                    onClick={() => setShowPassword(s => !s)}
                    className={`absolute right-3 top-1/2 -translate-y-1/2 transition-colors ${
                      activeIsLight ? 'text-slate-400 hover:text-slate-600' : 'text-white/30 hover:text-white'
                    }`}
                  >
                    {showPassword ? <EyeOff size={15} /> : <Eye size={15} />}
                  </button>
                </div>

                {/* Password Strength Meter (Signup Only) */}
                {isSignUp && password.length > 0 && (
                  <div className="mt-2.5 space-y-2">
                    <div className="flex items-center gap-2">
                      <div className="flex-1 flex gap-1">
                        {[1, 2, 3, 4, 5].map((i) => (
                          <div
                            key={i}
                            className={`h-1 flex-1 rounded-full transition-all duration-300 ${
                              i <= strength.score ? strength.color : activeIsLight ? 'bg-slate-200' : 'bg-white/10'
                            }`}
                          />
                        ))}
                      </div>
                      <span className={`text-[10px] font-semibold min-w-[70px] text-right ${
                        strength.score <= 1 ? 'text-red-400' :
                        strength.score === 2 ? 'text-orange-400' :
                        strength.score === 3 ? 'text-yellow-400' :
                        'text-emerald-400'
                      }`}>
                        {strength.label}
                      </span>
                    </div>

                    {/* Rule checklist */}
                    <div className={`rounded-xl p-3 border space-y-1.5 ${
                      activeIsLight ? 'bg-slate-50 border-slate-200' : 'bg-white/4 border-white/8'
                    }`}>
                      {ruleResults.map((rule) => (
                        <div key={rule.id} className="flex items-center gap-2">
                          {rule.passed
                            ? <CheckCircle2 size={11} className="text-emerald-400 shrink-0" />
                            : <XCircle      size={11} className="text-red-400/60 shrink-0" />
                          }
                          <span className={`text-[11px] transition-colors ${
                            rule.passed
                              ? 'text-emerald-400'
                              : activeIsLight ? 'text-slate-400' : 'text-white/35'
                          }`}>
                            {rule.label}
                          </span>
                        </div>
                      ))}
                    </div>
                  </div>
                )}
              </div>

              {/* Submit Button */}
              <button
                type="submit"
                disabled={loading}
                className="w-full py-2.5 rounded-xl font-bold text-xs flex items-center justify-center gap-2 bg-gradient-to-r from-violet-600 via-purple-600 to-cyan-500 text-white shadow-lg shadow-violet-600/30 hover:scale-[1.02] active:scale-[0.98] transition-all disabled:opacity-50 disabled:cursor-not-allowed mt-2"
              >
                {loading ? (
                  <>
                    <Loader2 size={14} className="animate-spin" />
                    <span>{isSignUp ? 'Sending Verification Code...' : 'Signing in...'}</span>
                  </>
                ) : (
                  <>
                    <ShieldCheck size={14} />
                    <span>{isSignUp ? 'Verify Email & Continue' : 'Sign In Securely'}</span>
                    <ArrowRight size={14} />
                  </>
                )}
              </button>

              {/* Server waking up reassurance note if cold start */}
              {loading && loadingElapsed >= 3 && (
                <div className="mt-2.5 p-2 rounded-xl bg-violet-500/10 border border-violet-500/20 text-center animate-fadeIn">
                  <p className="text-[11px] text-violet-300 flex items-center justify-center gap-1.5 font-medium">
                    <Sparkles size={13} className="text-cyan-400 animate-pulse shrink-0" />
                    <span>Cloud server waking up ({loadingElapsed}s)... please hold on</span>
                  </p>
                </div>
              )}
            </form>

            {/* Footer Notice */}
            <p className={`text-center text-[10px] mt-5 leading-relaxed ${subText}`}>
              🔒 Passwords hashed with SHA-256 · Real OTP verification enforced.<br />
              100% Free · Powered by Bittu AI
            </p>
          </>
        )}

        {/* ════════════════════════════════════════════════════════════════════════
            STEP 2: EMAIL OTP VERIFICATION SCREEN (SIGNUP)
           ════════════════════════════════════════════════════════════════════════ */}
        {signupStep === 'otp' && (
          <div className="animate-fadeIn">
            {/* Back to Form Button */}
            <button
              onClick={() => { setSignupStep('form'); setError(null); }}
              className={`flex items-center gap-1.5 text-xs font-medium mb-4 transition-colors ${
                activeIsLight ? 'text-slate-500 hover:text-slate-900' : 'text-white/60 hover:text-white'
              }`}
            >
              <ArrowLeft size={14} />
              <span>Back / Edit Details</span>
            </button>

            {/* Header Icon */}
            <div className="text-center mb-6">
              <div className="w-14 h-14 rounded-2xl bg-gradient-to-tr from-violet-600 to-cyan-500 flex items-center justify-center mx-auto mb-3 shadow-lg shadow-violet-500/30 animate-pulse">
                <KeyRound size={26} className="text-white" />
              </div>
              <h2 className="text-xl font-bold tracking-tight">Check Your Inbox</h2>
              <p className={`text-xs mt-1.5 ${subText}`}>
                We've sent a 6-digit verification code to:
              </p>
              <div className="mt-2 inline-flex items-center gap-2 px-3 py-1 rounded-full text-xs font-semibold bg-violet-500/15 text-violet-400 border border-violet-500/30">
                <Mail size={12} />
                <span>{email}</span>
              </div>
            </div>

            {/* Instant Auto-Fill Hint (if email is delayed or in fallback) */}
            {devOtpHint && (
              <div className="mb-4 p-3 rounded-xl bg-violet-500/10 border border-violet-500/30 text-violet-200 text-xs flex items-center justify-between animate-fadeIn">
                <div className="flex items-center gap-2">
                  <Sparkles size={14} className="shrink-0 text-cyan-400" />
                  <span>Instant Verification Code: <strong className="font-mono text-sm tracking-widest text-cyan-200">{devOtpHint}</strong></span>
                </div>
                <button
                  type="button"
                  onClick={() => setOtpValue(devOtpHint)}
                  className="px-2.5 py-1 text-[11px] font-bold rounded-lg bg-gradient-to-r from-violet-600 to-cyan-500 hover:opacity-90 text-white transition-all shadow-sm"
                >
                  Auto-Fill
                </button>
              </div>
            )}

            {/* Alerts */}
            {error && (
              <div className="mb-4 p-3 rounded-xl bg-red-500/10 border border-red-500/20 text-red-400 text-xs flex items-start gap-2 animate-fadeIn">
                <AlertCircle size={15} className="shrink-0 mt-0.5" />
                <span>{error}</span>
              </div>
            )}
            {success && (
              <div className="mb-4 p-3 rounded-xl bg-emerald-500/10 border border-emerald-500/20 text-emerald-400 text-xs flex items-start gap-2 animate-fadeIn">
                <CheckCircle2 size={15} className="shrink-0 mt-0.5" />
                <span>{success}</span>
              </div>
            )}

            <form onSubmit={handleVerifyOtpSubmit} className="space-y-5">
              {/* 6-Digit OTP Input Visualizer */}
              <div>
                <label className={`block text-xs font-semibold text-center mb-3 ${labelBase}`}>
                  Enter 6-Digit Verification Code
                </label>

                {/* Unified Digit Display with Hidden Input */}
                <div className="relative flex justify-center">
                  <input
                    ref={otpInputRef}
                    type="text"
                    inputMode="numeric"
                    autoComplete="one-time-code"
                    maxLength={6}
                    value={otpValue}
                    onChange={(e) => {
                      const val = e.target.value.replace(/\D/g, '').slice(0, 6)
                      setOtpValue(val)
                      if (error) setError(null)
                    }}
                    className="absolute inset-0 w-full h-full opacity-0 cursor-pointer z-10"
                  />
                  
                  {/* 6 Individual Digit Boxes */}
                  <div className="flex gap-2 sm:gap-2.5">
                    {[0, 1, 2, 3, 4, 5].map((index) => {
                      const char = otpValue[index] || ''
                      const isCurrent = otpValue.length === index
                      return (
                        <div
                          key={index}
                          className={`w-11 h-13 sm:w-12 sm:h-14 rounded-xl border flex items-center justify-center font-mono text-xl font-bold transition-all ${
                            char
                              ? 'border-violet-500 bg-violet-500/10 text-violet-300 shadow-sm shadow-violet-500/20'
                              : isCurrent
                              ? 'border-violet-400 ring-2 ring-violet-500/30 bg-transparent'
                              : activeIsLight
                              ? 'border-slate-300 bg-slate-50 text-slate-400'
                              : 'border-white/10 bg-white/5 text-white/30'
                          }`}
                        >
                          {char || (isCurrent ? <span className="w-1.5 h-5 bg-violet-400 rounded animate-pulse" /> : '')}
                        </div>
                      )
                    })}
                  </div>
                </div>
              </div>

              {/* Submit Verification Button */}
              <button
                type="submit"
                disabled={loading || otpValue.length !== 6}
                className="w-full py-2.5 rounded-xl font-bold text-xs flex items-center justify-center gap-2 bg-gradient-to-r from-violet-600 via-purple-600 to-cyan-500 text-white shadow-lg shadow-violet-600/30 hover:scale-[1.02] active:scale-[0.98] transition-all disabled:opacity-40 disabled:cursor-not-allowed"
              >
                {loading ? (
                  <>
                    <Loader2 size={14} className="animate-spin" />
                    <span>Verifying Code...</span>
                  </>
                ) : (
                  <>
                    <Check size={15} />
                    <span>Verify & Complete Registration</span>
                  </>
                )}
              </button>

              {/* Resend Cooldown Section */}
              <div className="text-center pt-2">
                {otpCooldown > 0 ? (
                  <p className={`text-xs ${subText}`}>
                    Resend code in <strong className="text-violet-400 font-mono">{otpCooldown}s</strong>
                  </p>
                ) : (
                  <button
                    type="button"
                    disabled={resending}
                    onClick={handleResendOtp}
                    className="inline-flex items-center gap-1.5 text-xs font-semibold text-violet-400 hover:text-violet-300 transition-colors"
                  >
                    <RefreshCw size={12} className={resending ? 'animate-spin' : ''} />
                    <span>{resending ? 'Sending new code...' : 'Resend Verification Code'}</span>
                  </button>
                )}
              </div>

              {/* Security Badge */}
              <p className={`text-center text-[10px] leading-relaxed ${subText} pt-2 border-t border-white/5`}>
                ⏱️ Codes expire in 10 minutes. For security, maximum 5 attempts are allowed before lockout.
              </p>
            </form>
          </div>
        )}
      </div>
    </div>
  )
}

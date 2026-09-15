import React, { useState } from 'react'
import {
  X, Mail, Lock, User, Sparkles, AlertCircle,
  CheckCircle2, ArrowRight, Eye, EyeOff, Loader2
} from 'lucide-react'
import { useAuth } from '../../context/AuthContext'

export default function AuthModal({ isLight = false }) {
  const { isAuthModalOpen, closeAuthModal, authMode, setAuthMode, signIn, signUp } = useAuth()

  const [fullName, setFullName] = useState('')
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [showPassword, setShowPassword] = useState(false)
  const [error, setError] = useState(null)
  const [success, setSuccess] = useState(null)
  const [loading, setLoading] = useState(false)

  if (!isAuthModalOpen) return null

  const isSignUp = authMode === 'signup'

  const handleSubmit = async (e) => {
    e.preventDefault()
    setError(null)
    setSuccess(null)
    setLoading(true)

    try {
      if (isSignUp) {
        if (!fullName.trim()) {
          throw new Error('Please enter your full name')
        }
        if (password.length < 6) {
          throw new Error('Password must be at least 6 characters')
        }
        await signUp(email, password, fullName.trim())
        setSuccess('Account created successfully! Check your email to confirm your account or start browsing.')
        setTimeout(() => {
          closeAuthModal()
          setSuccess(null)
        }, 2500)
      } else {
        await signIn(email, password)
        setSuccess('Welcome back! Successfully logged in.')
        setTimeout(() => {
          closeAuthModal()
          setSuccess(null)
        }, 1200)
      }
    } catch (err) {
      setError(err.message || 'Authentication failed. Please try again.')
    } finally {
      setLoading(false)
    }
  }

  const switchMode = (mode) => {
    setAuthMode(mode)
    setError(null)
    setSuccess(null)
  }

  return (
    <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/70 backdrop-blur-md animate-fadeIn">
      {/* Modal Container */}
      <div
        className={`relative w-full max-w-md rounded-2xl border p-6 sm:p-8 shadow-2xl transition-all ${
          isLight
            ? 'bg-white border-slate-200 text-slate-900 shadow-slate-300/50'
            : 'bg-[#0f0a1c]/95 border-violet-500/30 text-white shadow-violet-900/20'
        }`}
      >
        {/* Close Button */}
        <button
          onClick={closeAuthModal}
          className={`absolute top-4 right-4 p-1.5 rounded-lg transition-colors ${
            isLight ? 'hover:bg-slate-100 text-slate-400 hover:text-slate-800' : 'hover:bg-white/10 text-white/40 hover:text-white'
          }`}
        >
          <X size={18} />
        </button>

        {/* Brand Header */}
        <div className="text-center mb-6">
          <div className="w-12 h-12 rounded-xl bg-gradient-to-tr from-violet-600 to-cyan-500 flex items-center justify-center mx-auto mb-3 shadow-lg shadow-violet-500/30">
            <Sparkles size={22} className="text-white" />
          </div>
          <h2 className="text-xl font-bold tracking-tight">
            {isSignUp ? 'Create your Bittu AI account' : 'Welcome back to Bittu AI'}
          </h2>
          <p className={`text-xs mt-1 ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
            {isSignUp
              ? 'Save your DSA progress, streak, and generated AI videos permanently.'
              : 'Log in to access your cloud progress and AI history.'}
          </p>
        </div>

        {/* Mode Tabs */}
        <div className={`flex rounded-xl p-1 mb-5 border ${
          isLight ? 'bg-slate-100 border-slate-200' : 'bg-white/5 border-white/10'
        }`}>
          <button
            type="button"
            onClick={() => switchMode('signin')}
            className={`flex-1 py-1.5 text-xs font-semibold rounded-lg transition-all ${
              !isSignUp
                ? isLight
                  ? 'bg-white text-violet-700 shadow-sm'
                  : 'bg-violet-600 text-white shadow-md'
                : isLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/40 hover:text-white'
            }`}
          >
            Sign In
          </button>
          <button
            type="button"
            onClick={() => switchMode('signup')}
            className={`flex-1 py-1.5 text-xs font-semibold rounded-lg transition-all ${
              isSignUp
                ? isLight
                  ? 'bg-white text-violet-700 shadow-sm'
                  : 'bg-violet-600 text-white shadow-md'
                : isLight ? 'text-slate-500 hover:text-slate-800' : 'text-white/40 hover:text-white'
            }`}
          >
            Create Account
          </button>
        </div>

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

        {/* Form */}
        <form onSubmit={handleSubmit} className="space-y-4">
          {isSignUp && (
            <div>
              <label className={`block text-xs font-semibold mb-1.5 ${isLight ? 'text-slate-700' : 'text-white/70'}`}>
                Full Name
              </label>
              <div className="relative">
                <User size={15} className={`absolute left-3 top-1/2 -translate-y-1/2 ${isLight ? 'text-slate-400' : 'text-white/30'}`} />
                <input
                  type="text"
                  required
                  placeholder="e.g. Praveen Kumar"
                  value={fullName}
                  onChange={(e) => setFullName(e.target.value)}
                  className={`w-full pl-9 pr-4 py-2 rounded-xl text-xs border outline-none transition-all ${
                    isLight
                      ? 'bg-white border-slate-300 text-slate-900 focus:border-violet-600 focus:ring-1 focus:ring-violet-600'
                      : 'bg-white/5 border-white/10 text-white focus:border-violet-500 focus:ring-1 focus:ring-violet-500'
                  }`}
                />
              </div>
            </div>
          )}

          <div>
            <label className={`block text-xs font-semibold mb-1.5 ${isLight ? 'text-slate-700' : 'text-white/70'}`}>
              Email Address
            </label>
            <div className="relative">
              <Mail size={15} className={`absolute left-3 top-1/2 -translate-y-1/2 ${isLight ? 'text-slate-400' : 'text-white/30'}`} />
              <input
                type="email"
                required
                placeholder="you@example.com"
                value={email}
                onChange={(e) => setEmail(e.target.value)}
                className={`w-full pl-9 pr-4 py-2 rounded-xl text-xs border outline-none transition-all ${
                  isLight
                    ? 'bg-white border-slate-300 text-slate-900 focus:border-violet-600 focus:ring-1 focus:ring-violet-600'
                    : 'bg-white/5 border-white/10 text-white focus:border-violet-500 focus:ring-1 focus:ring-violet-500'
                }`}
              />
            </div>
          </div>

          <div>
            <label className={`block text-xs font-semibold mb-1.5 ${isLight ? 'text-slate-700' : 'text-white/70'}`}>
              Password
            </label>
            <div className="relative">
              <Lock size={15} className={`absolute left-3 top-1/2 -translate-y-1/2 ${isLight ? 'text-slate-400' : 'text-white/30'}`} />
              <input
                type={showPassword ? 'text' : 'password'}
                required
                placeholder="••••••••"
                value={password}
                onChange={(e) => setPassword(e.target.value)}
                className={`w-full pl-9 pr-10 py-2 rounded-xl text-xs border outline-none transition-all ${
                  isLight
                    ? 'bg-white border-slate-300 text-slate-900 focus:border-violet-600 focus:ring-1 focus:ring-violet-600'
                    : 'bg-white/5 border-white/10 text-white focus:border-violet-500 focus:ring-1 focus:ring-violet-500'
                }`}
              />
              <button
                type="button"
                onClick={() => setShowPassword(!showPassword)}
                className={`absolute right-3 top-1/2 -translate-y-1/2 ${isLight ? 'text-slate-400 hover:text-slate-600' : 'text-white/30 hover:text-white'}`}
              >
                {showPassword ? <EyeOff size={15} /> : <Eye size={15} />}
              </button>
            </div>
          </div>

          <button
            type="submit"
            disabled={loading}
            className="w-full py-2.5 rounded-xl font-bold text-xs flex items-center justify-center gap-2 bg-gradient-to-r from-violet-600 via-purple-600 to-cyan-500 text-white shadow-lg shadow-violet-600/30 hover:scale-[1.02] active:scale-[0.98] transition-all disabled:opacity-50 disabled:cursor-not-allowed"
          >
            {loading ? (
              <>
                <Loader2 size={14} className="animate-spin" />
                <span>Processing...</span>
              </>
            ) : (
              <>
                <span>{isSignUp ? 'Create Free Account' : 'Sign In'}</span>
                <ArrowRight size={14} />
              </>
            )}
          </button>
        </form>

        {/* Footer Note */}
        <p className={`text-center text-[11px] mt-5 ${isLight ? 'text-slate-400' : 'text-white/30'}`}>
          100% Free · Cloud Synced · Powered by Supabase
        </p>
      </div>
    </div>
  )
}

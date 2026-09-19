import React, { useState } from 'react'
import {
  MessageSquarePlus, Star, X, CheckCircle2,
  Send, Sparkles, AlertCircle, MessageCircle
} from 'lucide-react'
import { useAuth } from '../context/AuthContext'

const FEEDBACK_STORAGE_KEY = 'bittu_ai_user_feedback'

const CATEGORIES = [
  { id: 'general', label: '⭐ General Experience' },
  { id: 'dsa', label: '💻 DSA Platform & Compiler' },
  { id: 'video', label: '🎥 AI Video & Tools' },
  { id: 'bug', label: '🐛 Bug Report' },
  { id: 'feature', label: '💡 Feature Request' }
]

const RATING_LABELS = {
  1: 'Needs Improvement 🙁',
  2: 'Fair 😐',
  3: 'Good 😊',
  4: 'Very Good 😃',
  5: 'Amazing! 🤩'
}

export default function FeedbackModal() {
  const { user } = useAuth()
  const [isOpen, setIsOpen] = useState(false)
  const [rating, setRating] = useState(5)
  const [hoverRating, setHoverRating] = useState(0)
  const [category, setCategory] = useState('general')
  const [message, setMessage] = useState('')
  const [name, setName] = useState('')
  const [email, setEmail] = useState('')
  const [submitted, setSubmitted] = useState(false)
  const [error, setError] = useState(null)

  // Listen for custom open-feedback events
  React.useEffect(() => {
    const handleOpen = () => setIsOpen(true)
    window.addEventListener('open-feedback', handleOpen)
    return () => window.removeEventListener('open-feedback', handleOpen)
  }, [])

  // Auto-fill name and email if logged in
  React.useEffect(() => {
    if (user) {
      if (user.user_metadata?.full_name && !name) {
        setName(user.user_metadata.full_name)
      }
      if (user.email && !email) {
        setEmail(user.email)
      }
    }
  }, [user, isOpen])

  const handleSubmit = (e) => {
    e.preventDefault()
    if (!message.trim()) {
      setError('Please enter your feedback message.')
      return
    }

    try {
      const existing = JSON.parse(localStorage.getItem(FEEDBACK_STORAGE_KEY) || '[]')
      const newFeedback = {
        id: 'fb_' + Date.now().toString(36),
        rating,
        category,
        message: message.trim(),
        name: name.trim() || (user ? user.user_metadata?.full_name || 'Anonymous User' : 'Anonymous User'),
        email: email.trim() || (user ? user.email : ''),
        createdAt: new Date().toISOString()
      }

      existing.unshift(newFeedback)
      localStorage.setItem(FEEDBACK_STORAGE_KEY, JSON.stringify(existing))

      setSubmitted(true)
      setError(null)
      setTimeout(() => {
        setSubmitted(false)
        setMessage('')
        setIsOpen(false)
      }, 2500)
    } catch (err) {
      setError('Something went wrong. Please try again.')
    }
  }

  return (
    <>
      {/* ── Floating Feedback Trigger Button (Bottom-Right) ── */}
      <button
        onClick={() => setIsOpen(true)}
        className="fixed bottom-5 right-5 z-40 flex items-center gap-2 px-3.5 py-2.5 rounded-full border border-violet-500/30 bg-gradient-to-r from-violet-600/90 to-cyan-600/90 hover:from-violet-500 hover:to-cyan-500 text-white text-xs font-bold shadow-xl shadow-violet-500/25 hover:shadow-violet-500/40 hover:scale-105 active:scale-95 backdrop-blur-md transition-all group"
        title="Share your feedback"
      >
        <MessageCircle size={15} className="group-hover:rotate-12 transition-transform" />
        <span className="hidden sm:inline">Feedback</span>
      </button>

      {/* ── Feedback Modal Dialog ── */}
      {isOpen && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-3 sm:p-4 bg-black/75 backdrop-blur-md animate-fadeIn">
          <div className="relative w-full max-w-lg rounded-3xl border border-violet-500/30 bg-[#0d0718] p-6 text-white shadow-2xl shadow-violet-900/30 overflow-hidden">

            {/* Ambient Backlight */}
            <div className="absolute -top-24 right-0 w-72 h-72 rounded-full bg-violet-600/20 blur-3xl pointer-events-none" />

            {/* Close Button */}
            <button
              onClick={() => setIsOpen(false)}
              className="absolute top-4 right-4 p-2 rounded-full border border-white/10 bg-white/5 text-white/50 hover:text-white hover:bg-white/10 transition-all z-10"
              title="Close modal"
            >
              <X size={16} />
            </button>

            {submitted ? (
              /* Success State */
              <div className="py-10 flex flex-col items-center text-center animate-fadeIn">
                <div className="w-16 h-16 rounded-2xl bg-emerald-500/20 border border-emerald-500/40 text-emerald-400 flex items-center justify-center mb-4 shadow-lg shadow-emerald-500/20 animate-bounce-slow">
                  <CheckCircle2 size={36} />
                </div>
                <h3 className="text-xl font-bold text-white mb-2">
                  🎉 Shukriya! Thank You!
                </h3>
                <p className="text-sm text-white/70 max-w-xs leading-relaxed">
                  Aapka feedback successfully record ho gaya hai. Hum aapke sujhavon se platform ko aur behtar banayenge!
                </p>
              </div>
            ) : (
              /* Form State */
              <form onSubmit={handleSubmit} className="relative z-10 space-y-4">
                {/* Header */}
                <div className="flex items-center gap-3">
                  <div className="w-10 h-10 rounded-xl bg-gradient-to-br from-violet-600 to-cyan-500 flex items-center justify-center text-white shadow-md shadow-violet-500/30 shrink-0">
                    <MessageSquarePlus size={20} />
                  </div>
                  <div>
                    <h3 className="text-base font-bold text-white tracking-tight">
                      Share Feedback / आपकी राय
                    </h3>
                    <p className="text-xs text-white/50">
                      Help us improve Bittu AI and the DSA Platform
                    </p>
                  </div>
                </div>

                {/* Rating Stars */}
                <div>
                  <label className="block text-xs font-semibold text-white/70 mb-1.5">
                    How was your experience? / आपका अनुभव कैसा रहा?
                  </label>
                  <div className="flex items-center gap-2">
                    {[1, 2, 3, 4, 5].map((star) => (
                      <button
                        type="button"
                        key={star}
                        onClick={() => setRating(star)}
                        onMouseEnter={() => setHoverRating(star)}
                        onMouseLeave={() => setHoverRating(0)}
                        className="p-1 transition-transform hover:scale-125"
                      >
                        <Star
                          size={24}
                          className={`${
                            (hoverRating || rating) >= star
                              ? 'text-amber-400 fill-amber-400 drop-shadow-[0_0_8px_rgba(251,191,36,0.5)]'
                              : 'text-white/20'
                          } transition-colors`}
                        />
                      </button>
                    ))}
                    <span className="text-xs font-mono font-medium text-amber-300 ml-2">
                      {RATING_LABELS[hoverRating || rating]}
                    </span>
                  </div>
                </div>

                {/* Category Selection */}
                <div>
                  <label className="block text-xs font-semibold text-white/70 mb-1.5">
                    Category / श्रेणी
                  </label>
                  <div className="flex flex-wrap gap-1.5">
                    {CATEGORIES.map((cat) => (
                      <button
                        type="button"
                        key={cat.id}
                        onClick={() => setCategory(cat.id)}
                        className={`px-2.5 py-1.5 rounded-lg text-xs font-medium border transition-all ${
                          category === cat.id
                            ? 'bg-violet-600/30 border-violet-500 text-violet-300 font-bold shadow-sm'
                            : 'bg-white/5 border-white/10 text-white/60 hover:text-white hover:bg-white/10'
                        }`}
                      >
                        {cat.label}
                      </button>
                    ))}
                  </div>
                </div>

                {/* Message */}
                <div>
                  <label className="block text-xs font-semibold text-white/70 mb-1.5">
                    Your Feedback / सुझाव या समस्या *
                  </label>
                  <textarea
                    rows={3}
                    required
                    value={message}
                    onChange={(e) => {
                      setMessage(e.target.value)
                      if (error) setError(null)
                    }}
                    placeholder="Apna feedback yahan likhein (kya accha laga ya kya improve hona chahiye)..."
                    className="w-full px-3.5 py-2.5 rounded-xl text-xs bg-white/5 border border-white/10 text-white placeholder-white/30 outline-none focus:border-violet-500 focus:ring-1 focus:ring-violet-500 transition-all resize-none"
                  />
                </div>

                {/* Optional Name & Email */}
                <div className="grid grid-cols-1 sm:grid-cols-2 gap-2.5">
                  <div>
                    <label className="block text-[11px] text-white/60 mb-1">
                      Your Name (Optional)
                    </label>
                    <input
                      type="text"
                      value={name}
                      onChange={(e) => setName(e.target.value)}
                      placeholder="Enter your name"
                      className="w-full px-3 py-1.5 rounded-lg text-xs bg-white/5 border border-white/10 text-white placeholder-white/30 outline-none focus:border-violet-500 transition-all"
                    />
                  </div>
                  <div>
                    <label className="block text-[11px] text-white/60 mb-1">
                      Your Email (Optional)
                    </label>
                    <input
                      type="email"
                      value={email}
                      onChange={(e) => setEmail(e.target.value)}
                      placeholder="you@example.com"
                      className="w-full px-3 py-1.5 rounded-lg text-xs bg-white/5 border border-white/10 text-white placeholder-white/30 outline-none focus:border-violet-500 transition-all"
                    />
                  </div>
                </div>

                {error && (
                  <div className="flex items-center gap-1.5 p-2 rounded-lg bg-red-500/10 border border-red-500/20 text-red-400 text-xs">
                    <AlertCircle size={13} />
                    <span>{error}</span>
                  </div>
                )}

                {/* Submit CTA */}
                <button
                  type="submit"
                  className="w-full py-2.5 px-4 rounded-xl font-bold text-xs bg-gradient-to-r from-violet-600 to-cyan-600 text-white shadow-lg shadow-violet-500/25 hover:opacity-95 active:scale-[0.98] transition-all flex items-center justify-center gap-2"
                >
                  <Send size={14} />
                  <span>Submit Feedback (राय भेजें)</span>
                </button>
              </form>
            )}
          </div>
        </div>
      )}
    </>
  )
}

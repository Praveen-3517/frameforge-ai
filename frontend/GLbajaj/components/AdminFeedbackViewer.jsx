import React, { useState, useEffect } from 'react'
import axios from 'axios'
import {
  Bell, X, Star, Trash2, CheckCircle2, MessageSquare,
  Sparkles, RefreshCw, Filter, Mail, User, Clock, AlertCircle
} from 'lucide-react'
import { getApiUrl } from '../utils/apiUrl'

const CATEGORY_ICONS = {
  general: '⭐',
  dsa: '💻',
  video: '🎥',
  bug: '🐛',
  feature: '💡'
}

export default function AdminFeedbackViewer() {
  const [isOpen, setIsOpen] = useState(false)
  const [feedbacks, setFeedbacks] = useState([])
  const [unreadCount, setUnreadCount] = useState(0)
  const [avgRating, setAvgRating] = useState(5.0)
  const [loading, setLoading] = useState(false)
  const [filterCategory, setFilterCategory] = useState('all') // 'all' | 'unread' | 'bug' | 'feature' | 'dsa'

  const fetchFeedbacks = async () => {
    try {
      setLoading(true)
      const API_URL = getApiUrl()
      const res = await axios.get(`${API_URL}/api/feedback/all`, { timeout: 8000 })
      if (res.data && res.data.success) {
        setFeedbacks(res.data.feedbacks || [])
        setUnreadCount(res.data.unread_count || 0)
        setAvgRating(res.data.average_rating || 5.0)
      }
    } catch (err) {
      console.warn('Could not fetch feedbacks from server:', err)
    } finally {
      setLoading(false)
    }
  }

  // Fetch on mount and listen for feedback-updated events
  useEffect(() => {
    fetchFeedbacks()
    const handleUpdate = () => fetchFeedbacks()
    window.addEventListener('feedback-updated', handleUpdate)
    window.addEventListener('open-admin-feedback', () => setIsOpen(true))

    // Polling every 30 seconds for background notifications
    const interval = setInterval(fetchFeedbacks, 30000)
    return () => {
      window.removeEventListener('feedback-updated', handleUpdate)
      window.removeEventListener('open-admin-feedback', () => setIsOpen(true))
      clearInterval(interval)
    }
  }, [])

  const handleMarkAllRead = async () => {
    try {
      const API_URL = getApiUrl()
      await axios.post(`${API_URL}/api/feedback/mark-read`, {})
      setFeedbacks(prev => prev.map(f => ({ ...f, is_read: true })))
      setUnreadCount(0)
    } catch (e) {}
  }

  const handleMarkSingleRead = async (id) => {
    try {
      const API_URL = getApiUrl()
      await axios.post(`${API_URL}/api/feedback/mark-read`, { ids: [id] })
      setFeedbacks(prev => prev.map(f => f.id === id ? { ...f, is_read: true } : f))
      setUnreadCount(prev => Math.max(0, prev - 1))
    } catch (e) {}
  }

  const handleDelete = async (id, e) => {
    e.stopPropagation()
    try {
      const API_URL = getApiUrl()
      await axios.delete(`${API_URL}/api/feedback/${id}`)
      setFeedbacks(prev => prev.filter(f => f.id !== id))
    } catch (e) {}
  }

  const filteredFeedbacks = feedbacks.filter(item => {
    if (filterCategory === 'unread') return !item.is_read
    if (filterCategory === 'all') return true
    return item.category === filterCategory
  })

  return (
    <>
      {/* ── Notification Bell Trigger Button (Top Bar / Floating) ── */}
      <button
        onClick={() => {
          setIsOpen(true)
          fetchFeedbacks()
        }}
        className="relative flex items-center justify-center p-2 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 hover:border-violet-500/40 text-white/80 hover:text-white transition-all shadow-md group"
        title="Admin Feedback & Notifications"
      >
        <Bell size={18} className={`transition-transform ${unreadCount > 0 ? 'text-amber-400 animate-pulse' : 'text-white/60 group-hover:rotate-12'}`} />
        {unreadCount > 0 && (
          <span className="absolute -top-1 -right-1 flex h-4 min-w-4 px-1 items-center justify-center rounded-full bg-rose-500 text-[10px] font-bold text-white shadow-lg shadow-rose-500/50 animate-bounce">
            {unreadCount > 9 ? '9+' : unreadCount}
          </span>
        )}
      </button>

      {/* ── Admin Feedback Drawer / Modal ── */}
      {isOpen && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-3 sm:p-6 bg-black/80 backdrop-blur-md animate-fadeIn">
          <div className="relative w-full max-w-2xl max-h-[88vh] rounded-3xl border border-violet-500/30 bg-[#0d0718] p-6 text-white shadow-2xl shadow-violet-900/40 flex flex-col overflow-hidden">
            
            {/* Ambient glow */}
            <div className="absolute -top-20 left-1/2 -translate-x-1/2 w-96 h-96 rounded-full bg-violet-600/20 blur-3xl pointer-events-none" />

            {/* Header */}
            <div className="relative z-10 flex items-center justify-between pb-4 border-b border-white/10 shrink-0">
              <div className="flex items-center gap-3">
                <div className="w-10 h-10 rounded-2xl bg-gradient-to-br from-amber-500 to-violet-600 flex items-center justify-center text-white shadow-lg shadow-amber-500/20">
                  <Bell size={20} />
                </div>
                <div>
                  <h3 className="text-lg font-bold text-white flex items-center gap-2">
                    User Feedback Notifications
                    {unreadCount > 0 && (
                      <span className="px-2 py-0.5 rounded-full bg-rose-500/20 border border-rose-500/40 text-rose-300 text-xs font-mono font-semibold">
                        {unreadCount} New
                      </span>
                    )}
                  </h3>
                  <p className="text-xs text-white/50">
                    Total: {feedbacks.length} feedbacks • Avg Rating: ⭐ {avgRating}/5.0
                  </p>
                </div>
              </div>

              <div className="flex items-center gap-2">
                <button
                  onClick={fetchFeedbacks}
                  className={`p-2 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-white/60 hover:text-white transition-all ${loading ? 'animate-spin text-cyan-400' : ''}`}
                  title="Refresh Feedbacks"
                >
                  <RefreshCw size={15} />
                </button>
                <button
                  onClick={() => setIsOpen(false)}
                  className="p-2 rounded-xl bg-white/5 hover:bg-white/10 border border-white/10 text-white/60 hover:text-white transition-all"
                  title="Close"
                >
                  <X size={16} />
                </button>
              </div>
            </div>

            {/* Filter Tabs & Quick Actions */}
            <div className="relative z-10 flex flex-wrap items-center justify-between gap-2 py-3 border-b border-white/5 shrink-0 text-xs">
              <div className="flex items-center gap-1.5 overflow-x-auto pb-1 max-w-full">
                {[
                  { id: 'all', label: `All (${feedbacks.length})` },
                  { id: 'unread', label: `Unread (${unreadCount})` },
                  { id: 'bug', label: '🐛 Bugs' },
                  { id: 'feature', label: '💡 Features' },
                  { id: 'dsa', label: '💻 DSA' },
                  { id: 'general', label: '⭐ General' },
                ].map(tab => (
                  <button
                    key={tab.id}
                    onClick={() => setFilterCategory(tab.id)}
                    className={`px-3 py-1.5 rounded-lg border font-medium transition-all ${
                      filterCategory === tab.id
                        ? 'bg-violet-600/30 border-violet-500/60 text-white font-bold shadow-sm shadow-violet-500/20'
                        : 'bg-white/5 border-white/5 text-white/50 hover:text-white hover:bg-white/10'
                    }`}
                  >
                    {tab.label}
                  </button>
                ))}
              </div>

              {unreadCount > 0 && (
                <button
                  onClick={handleMarkAllRead}
                  className="px-3 py-1.5 rounded-lg bg-emerald-500/10 hover:bg-emerald-500/20 border border-emerald-500/30 text-emerald-300 font-semibold flex items-center gap-1.5 transition-all text-xs"
                >
                  <CheckCircle2 size={13} /> Mark all read
                </button>
              )}
            </div>

            {/* Feedbacks List */}
            <div className="relative z-10 flex-1 overflow-y-auto py-3 space-y-3 pr-1 custom-scrollbar">
              {filteredFeedbacks.length === 0 ? (
                <div className="py-16 text-center text-white/40 flex flex-col items-center gap-2">
                  <MessageSquare size={36} className="text-white/20" />
                  <p className="text-sm font-medium">Koi feedback nahi mila is filter me.</p>
                  <p className="text-xs text-white/30">Jaise hi koi user feedback bhejega, yahan real-time notification aayega!</p>
                </div>
              ) : (
                filteredFeedbacks.map((fb) => (
                  <div
                    key={fb.id}
                    onClick={() => !fb.is_read && handleMarkSingleRead(fb.id)}
                    className={`relative p-4 rounded-2xl border transition-all cursor-pointer ${
                      !fb.is_read
                        ? 'bg-violet-950/40 border-violet-500/40 hover:border-violet-400/60 shadow-lg shadow-violet-900/20'
                        : 'bg-white/[0.02] border-white/10 hover:border-white/20'
                    }`}
                  >
                    {/* Unread Glowing Dot */}
                    {!fb.is_read && (
                      <span className="absolute top-4 right-4 flex h-2.5 w-2.5">
                        <span className="animate-ping absolute inline-flex h-full w-full rounded-full bg-rose-400 opacity-75"></span>
                        <span className="relative inline-flex rounded-full h-2.5 w-2.5 bg-rose-500"></span>
                      </span>
                    )}

                    {/* Meta Top: Name, Email, Category, Time */}
                    <div className="flex flex-wrap items-center justify-between gap-2 mb-2">
                      <div className="flex items-center gap-2">
                        <div className="w-7 h-7 rounded-lg bg-white/10 flex items-center justify-center text-white/80 font-bold text-xs">
                          {fb.name ? fb.name[0].toUpperCase() : 'U'}
                        </div>
                        <div>
                          <p className="text-xs font-bold text-white flex items-center gap-1">
                            {fb.name || 'Anonymous User'}
                            {fb.email && (
                              <span className="text-[11px] font-normal text-white/40">
                                ({fb.email})
                              </span>
                            )}
                          </p>
                        </div>
                      </div>

                      <div className="flex items-center gap-2">
                        <span className="px-2 py-0.5 rounded-md bg-white/5 border border-white/10 text-[11px] text-cyan-300 font-mono">
                          {CATEGORY_ICONS[fb.category] || '💬'} {fb.category || 'general'}
                        </span>
                        <div className="flex items-center text-amber-400">
                          {[...Array(5)].map((_, i) => (
                            <Star
                              key={i}
                              size={12}
                              className={i < (fb.rating || 5) ? 'fill-amber-400 text-amber-400' : 'text-white/20'}
                            />
                          ))}
                        </div>
                      </div>
                    </div>

                    {/* Feedback Message */}
                    <p className="text-sm text-white/90 whitespace-pre-wrap leading-relaxed bg-black/30 p-3 rounded-xl border border-white/5 font-sans my-2">
                      {fb.message}
                    </p>

                    {/* Footer: Date & Delete */}
                    <div className="flex items-center justify-between text-[11px] text-white/40 pt-1">
                      <span className="flex items-center gap-1">
                        <Clock size={11} /> {new Date(fb.created_at || fb.createdAt || Date.now()).toLocaleString()}
                      </span>
                      <button
                        onClick={(e) => handleDelete(fb.id, e)}
                        className="p-1 rounded-md text-white/30 hover:text-rose-400 hover:bg-rose-500/10 transition-colors"
                        title="Delete feedback"
                      >
                        <Trash2 size={13} />
                      </button>
                    </div>
                  </div>
                ))
              )}
            </div>

            {/* Modal Bottom note */}
            <div className="relative z-10 pt-3 border-t border-white/10 text-center text-xs text-white/40 shrink-0">
              💡 Yeh admin notification panel sabhi users ke feedback live dikhata hai.
            </div>

          </div>
        </div>
      )}
    </>
  )
}

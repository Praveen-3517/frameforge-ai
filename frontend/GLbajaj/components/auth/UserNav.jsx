import React, { useState, useRef, useEffect } from 'react'
import { User, LogOut, Sparkles, CheckCircle2, ChevronDown, Cloud } from 'lucide-react'
import { useAuth } from '../../context/AuthContext'

export default function UserNav({ isLight = false }) {
  const { user, loading, openAuthModal, signOut } = useAuth()
  const [dropdownOpen, setDropdownOpen] = useState(false)
  const dropdownRef = useRef(null)

  // Close dropdown on outside click
  useEffect(() => {
    const handleClickOutside = (event) => {
      if (dropdownRef.current && !dropdownRef.current.contains(event.target)) {
        setDropdownOpen(false)
      }
    }
    document.addEventListener('mousedown', handleClickOutside)
    return () => document.removeEventListener('mousedown', handleClickOutside)
  }, [])

  if (loading) {
    return (
      <div className={`w-8 h-8 rounded-lg animate-pulse ${isLight ? 'bg-slate-200' : 'bg-white/10'}`} />
    )
  }

  // If Not Logged In -> Show Sign In Button
  if (!user) {
    return (
      <button
        onClick={() => openAuthModal('signin')}
        className="flex items-center gap-1.5 px-3 py-1.5 rounded-lg text-xs font-semibold bg-gradient-to-r from-violet-600 to-cyan-600 text-white shadow-md shadow-violet-600/20 hover:scale-105 active:scale-95 transition-all"
      >
        <User size={13} />
        <span>Sign In</span>
      </button>
    )
  }

  // If Logged In -> Show Avatar with Dropdown
  const displayName = user.user_metadata?.full_name || user.email?.split('@')[0] || 'User'
  const initial = displayName.charAt(0).toUpperCase()

  return (
    <div className="relative" ref={dropdownRef}>
      <button
        onClick={() => setDropdownOpen(!dropdownOpen)}
        className={`flex items-center gap-2 p-1 pl-2 rounded-xl border transition-all ${
          isLight
            ? 'bg-white border-slate-200 text-slate-800 hover:bg-slate-50 shadow-sm'
            : 'bg-white/5 border-white/10 text-white hover:bg-white/10'
        }`}
      >
        <div className="w-6 h-6 rounded-lg bg-gradient-to-tr from-violet-600 to-cyan-500 text-white flex items-center justify-center text-xs font-bold shadow-sm">
          {initial}
        </div>
        <span className="text-xs font-semibold max-w-[100px] truncate hidden sm:inline">
          {displayName}
        </span>
        <ChevronDown size={13} className={`${isLight ? 'text-slate-400' : 'text-white/40'}`} />
      </button>

      {/* Dropdown Menu */}
      {dropdownOpen && (
        <div
          className={`absolute right-0 mt-2 w-56 rounded-2xl border p-2 shadow-2xl z-50 animate-fadeIn ${
            isLight
              ? 'bg-white border-slate-200 text-slate-900 shadow-slate-300/60'
              : 'bg-[#0f0a1c]/95 border-violet-500/20 text-white shadow-violet-950/40 backdrop-blur-xl'
          }`}
        >
          {/* User Info Header */}
          <div className={`p-2.5 border-b mb-1.5 ${isLight ? 'border-slate-100' : 'border-white/8'}`}>
            <p className="text-xs font-bold truncate">{displayName}</p>
            <p className={`text-[11px] truncate ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
              {user.email}
            </p>
            <div className="mt-2 flex items-center gap-1 text-[10px] text-emerald-500 font-semibold">
              <Cloud size={11} />
              <span>Cloud Sync Active</span>
            </div>
          </div>

          {/* Sign Out Button */}
          <button
            onClick={() => {
              signOut()
              setDropdownOpen(false)
            }}
            className={`w-full flex items-center gap-2 px-3 py-2 rounded-xl text-xs font-semibold text-red-400 transition-colors ${
              isLight ? 'hover:bg-red-50' : 'hover:bg-red-500/10'
            }`}
          >
            <LogOut size={13} />
            <span>Sign Out</span>
          </button>
        </div>
      )}
    </div>
  )
}

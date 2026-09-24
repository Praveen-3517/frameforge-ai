import React, { createContext, useContext, useState, useEffect } from 'react'
import { supabase } from '../utils/supabaseClient'
import { getApiUrl } from '../utils/apiUrl'

const AuthContext = createContext({})

const LOCAL_USERS_KEY   = 'bittu_ai_local_users'
const LOCAL_SESSION_KEY = 'bittu_ai_local_session'

// ─── Password hashing (SHA-256 + deterministic salt, Web Crypto API) ──────────
// Passwords are NEVER stored in plain text — only the hex digest is saved.
async function hashPassword(password) {
  const encoder = new TextEncoder()
  // Deterministic salt derived from a fixed app secret + the password itself.
  // This prevents trivial rainbow-table attacks on the stored hash.
  const salted = 'bittu_ai_2026_!xZ9#kL' + password
  const data   = encoder.encode(salted)
  const hashBuf = await crypto.subtle.digest('SHA-256', data)
  return Array.from(new Uint8Array(hashBuf))
    .map(b => b.toString(16).padStart(2, '0'))
    .join('')
}

// Check if Supabase URL is a real configured project (not a placeholder)
function isPlaceholderSupabase() {
  const url = import.meta.env.VITE_SUPABASE_URL || ''
  const key = import.meta.env.VITE_SUPABASE_ANON_KEY || ''
  return !url || !url.startsWith('https://') || !key || key.includes('placeholder')
}

export function AuthProvider({ children }) {
  const [user, setUser] = useState(null)
  const [session, setSession] = useState(null)
  const [loading, setLoading] = useState(true)
  const [isAuthModalOpen, setIsAuthModalOpen] = useState(false)
  const [authMode, setAuthMode] = useState('signin') // 'signin' | 'signup'

  useEffect(() => {
    // 1. Check local session first (instant load)
    try {
      const savedLocal = JSON.parse(localStorage.getItem(LOCAL_SESSION_KEY) || 'null')
      if (savedLocal?.user) {
        setUser(savedLocal.user)
        setSession({ user: savedLocal.user, access_token: 'local_token' })
        setLoading(false)
      }
    } catch {}

    // 2. If Supabase is real, check Supabase active session
    if (!isPlaceholderSupabase()) {
      supabase.auth.getSession().then(({ data: { session } }) => {
        if (session) {
          setSession(session)
          setUser(session.user)
          localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: session.user }))
        }
        setLoading(false)
      }).catch(() => {
        setLoading(false)
      })

      const { data: { subscription } } = supabase.auth.onAuthStateChange(
        (_event, session) => {
          if (session) {
            setSession(session)
            setUser(session.user)
            localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: session.user }))
          } else {
            // Only clear if not in local mode
            const local = JSON.parse(localStorage.getItem(LOCAL_SESSION_KEY) || 'null')
            if (!local?.user?.auth_provider || local.user.auth_provider !== 'local') {
              setUser(null)
              setSession(null)
            }
          }
          setLoading(false)
        }
      )

      return () => subscription.unsubscribe()
    } else {
      setLoading(false)
    }
  }, [])

  const openAuthModal = (mode = 'signin') => {
    setAuthMode(mode)
    setIsAuthModalOpen(true)
  }

  const closeAuthModal = () => {
    setIsAuthModalOpen(false)
  }

  // Local signup handler
  const localSignUp = async (email, password, fullName) => {
    const localUsers = JSON.parse(localStorage.getItem(LOCAL_USERS_KEY) || '[]')
    const normalizedEmail = email.toLowerCase().trim()
    const existing = localUsers.find(u => u.email === normalizedEmail)
    if (existing) {
      throw new Error('An account with this email already exists. Please Sign In.')
    }

    // Hash password before storing — NEVER store plain text
    const passwordHash = await hashPassword(password)

    const newUser = {
      id: 'usr_' + Date.now().toString(36) + Math.random().toString(36).slice(2, 7),
      email: normalizedEmail,
      passwordHash, // SHA-256 hash only — original password is never persisted
      user_metadata: {
        full_name: fullName.trim() || normalizedEmail.split('@')[0],
      },
      created_at: new Date().toISOString(),
      auth_provider: 'local',
    }

    localUsers.push(newUser)
    localStorage.setItem(LOCAL_USERS_KEY, JSON.stringify(localUsers))
    // Store session WITHOUT the password hash
    const sessionUser = { ...newUser }
    delete sessionUser.passwordHash
    localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: sessionUser }))

    setUser(sessionUser)
    setSession({ user: sessionUser, access_token: 'local_token' })
    return { user: sessionUser, session: { user: sessionUser } }
  }

  // Local signin handler
  const localSignIn = async (email, password) => {
    const localUsers = JSON.parse(localStorage.getItem(LOCAL_USERS_KEY) || '[]')
    const normalizedEmail = email.toLowerCase().trim()
    const foundUser = localUsers.find(u => u.email === normalizedEmail)

    if (!foundUser) {
      // No account found — require explicit signup; do NOT auto-create
      throw new Error('Account not found. Please click "Create Account" to sign up first.')
    }

    // Compare hashed password
    const inputHash = await hashPassword(password)
    if (foundUser.passwordHash !== inputHash) {
      throw new Error('Incorrect password. Please try again.')
    }

    // Return session without password hash
    const sessionUser = { ...foundUser }
    delete sessionUser.passwordHash
    localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: sessionUser }))
    setUser(sessionUser)
    setSession({ user: sessionUser, access_token: 'local_token' })
    return { user: sessionUser, session: { user: sessionUser } }
  }

  // Sign Up with Email, Password & Full Name
  const signUp = async (email, password, fullName = '') => {
    // If Supabase is real, try Supabase first
    if (!isPlaceholderSupabase()) {
      try {
        const { data, error } = await supabase.auth.signUp({
          email,
          password,
          options: {
            data: { full_name: fullName },
          },
        })
        if (error) throw error
        if (data?.user) {
          setUser(data.user)
          setSession(data.session)
          localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: data.user }))
          return data
        }
      } catch (sbError) {
        console.warn('Supabase signup failed, falling back to local auth:', sbError.message)
      }
    }

    // Seamless Local Fallback
    return localSignUp(email, password, fullName)
  }

  // Sign In with Email & Password
  const signIn = async (email, password) => {
    // If Supabase is real, try Supabase first
    if (!isPlaceholderSupabase()) {
      try {
        const { data, error } = await supabase.auth.signInWithPassword({
          email,
          password,
        })
        if (error) throw error
        if (data?.user) {
          setUser(data.user)
          setSession(data.session)
          localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: data.user }))
          return data
        }
      } catch (sbError) {
        console.warn('Supabase signin failed, falling back to local auth:', sbError.message)
      }
    }

    // Seamless Local Fallback
    return localSignIn(email, password)
  }

  // Sign Out
  const signOut = async () => {
    try {
      if (!isPlaceholderSupabase()) {
        await supabase.auth.signOut()
      }
    } catch {}

    localStorage.removeItem(LOCAL_SESSION_KEY)
    setUser(null)
    setSession(null)
  }

  // Request Email Verification OTP
  const sendOtp = async (email) => {
    const base = getApiUrl()
    const controller = new AbortController()
    const timeoutId = setTimeout(() => controller.abort(), 45000)
    try {
      const res = await fetch(`${base}/api/auth/send-otp`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email: email.trim().toLowerCase() }),
        signal: controller.signal,
      })
      clearTimeout(timeoutId)
      const data = await res.json().catch(() => ({}))
      if (!res.ok) {
        throw new Error(data.detail || data.error || 'Failed to send verification code.')
      }
      return data
    } catch (err) {
      clearTimeout(timeoutId)
      if (err.name === 'AbortError') {
        throw new Error('Connection timed out while waking server. Please click retry.')
      }
      throw err
    }
  }

  // Verify Email OTP Code
  const verifyOtp = async (email, otp) => {
    const base = getApiUrl()
    const controller = new AbortController()
    const timeoutId = setTimeout(() => controller.abort(), 30000)
    try {
      const res = await fetch(`${base}/api/auth/verify-otp`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email: email.trim().toLowerCase(), otp: otp.trim() }),
        signal: controller.signal,
      })
      clearTimeout(timeoutId)
      const data = await res.json().catch(() => ({}))
      if (!res.ok) {
        throw new Error(data.detail || data.error || 'Invalid verification code.')
      }
      return data
    } catch (err) {
      clearTimeout(timeoutId)
      if (err.name === 'AbortError') {
        throw new Error('Verification timed out. Please try again.')
      }
      throw err
    }
  }

  const value = {
    user,
    session,
    loading,
    isAuthModalOpen,
    setIsAuthModalOpen,
    authMode,
    setAuthMode,
    openAuthModal,
    closeAuthModal,
    signUp,
    signIn,
    signOut,
    sendOtp,
    verifyOtp,
  }

  return (
    <AuthContext.Provider value={value}>
      {children}
    </AuthContext.Provider>
  )
}

export function useAuth() {
  const context = useContext(AuthContext)
  if (!context) {
    throw new Error('useAuth must be used within an AuthProvider')
  }
  return context
}

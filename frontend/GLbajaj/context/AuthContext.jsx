import React, { createContext, useContext, useState, useEffect } from 'react'
import { supabase } from '../utils/supabaseClient'
import { getApiUrl } from '../utils/apiUrl'
import { fetchRemoteProStatus } from '../utils/proSubscription'

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

  // Auto-sync Pro Lifetime Pass on login across any device & sync local users to cloud
  useEffect(() => {
    if (user?.email) {
      fetchRemoteProStatus(user.email).catch(() => {})
    }

    // Sync any pre-existing local storage users to Central Cloud Server
    try {
      const localUsers = JSON.parse(localStorage.getItem(LOCAL_USERS_KEY) || '[]')
      if (localUsers.length > 0) {
        const base = getApiUrl()
        localUsers.forEach(u => {
          if (u.email && u.passwordHash) {
            fetch(`${base}/api/auth/sync-user`, {
              method: 'POST',
              headers: { 'Content-Type': 'application/json' },
              body: JSON.stringify({
                email: u.email,
                password: u.passwordHash,
                full_name: u.user_metadata?.full_name || ''
              })
            }).catch(() => {})
          }
        })
      }
    } catch {}
  }, [user?.email])

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

  // Sign Up with Email, Password & Full Name (Central Cloud Server + Supabase + Local)
  const signUp = async (email, password, fullName = '') => {
    const base = getApiUrl()
    const normalizedEmail = email.toLowerCase().trim()
    let cloudUser = null

    // 1. Central Backend Cloud DB Registration
    try {
      const res = await fetch(`${base}/api/auth/register`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          email: normalizedEmail,
          password,
          full_name: fullName
        })
      })
      const data = await res.json().catch(() => ({}))
      if (!res.ok) {
        throw new Error(data.detail || data.error || 'Registration failed.')
      }
      if (data?.user) {
        cloudUser = data.user
      }
    } catch (apiErr) {
      if (apiErr.message.includes('already exists')) {
        throw apiErr
      }
      console.warn('Central auth register error:', apiErr.message)
    }

    // 2. Supabase if configured
    if (!isPlaceholderSupabase()) {
      try {
        await supabase.auth.signUp({
          email: normalizedEmail,
          password,
          options: { data: { full_name: fullName } },
        })
      } catch (sbError) {}
    }

    // 3. Fallback / Local sync
    const localRes = await localSignUp(email, password, fullName).catch(() => ({}))
    const finalUser = cloudUser || localRes.user || {
      id: 'usr_' + Date.now().toString(36),
      email: normalizedEmail,
      user_metadata: { full_name: fullName || normalizedEmail.split('@')[0] }
    }

    setUser(finalUser)
    setSession({ user: finalUser, access_token: 'cloud_token' })
    localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: finalUser }))
    return { user: finalUser, session: { user: finalUser } }
  }

  // Sign In with Email & Password (Central Cloud Server + Supabase + Local)
  const signIn = async (email, password) => {
    const base = getApiUrl()
    const normalizedEmail = email.toLowerCase().trim()
    let cloudError = null

    // 1. Central Backend Cloud DB Login
    try {
      const res = await fetch(`${base}/api/auth/login`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({
          email: normalizedEmail,
          password
        })
      })
      const data = await res.json().catch(() => ({}))
      if (res.ok && data?.user) {
        setUser(data.user)
        setSession({ user: data.user, access_token: 'cloud_token' })
        localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: data.user }))
        return { user: data.user, session: { user: data.user } }
      } else if (!res.ok) {
        cloudError = data.detail || data.error
      }
    } catch (err) {
      console.warn('Central auth login error:', err.message)
    }

    // 2. Try Supabase if configured
    if (!isPlaceholderSupabase()) {
      try {
        const { data, error } = await supabase.auth.signInWithPassword({
          email: normalizedEmail,
          password,
        })
        if (!error && data?.user) {
          setUser(data.user)
          setSession(data.session)
          localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: data.user }))
          return data
        }
      } catch (sbError) {}
    }

    // 3. Try Local Storage
    try {
      return await localSignIn(email, password)
    } catch (localErr) {
      throw new Error(cloudError || localErr.message)
    }
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

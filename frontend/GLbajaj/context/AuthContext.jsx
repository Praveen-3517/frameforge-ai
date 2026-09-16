import React, { createContext, useContext, useState, useEffect } from 'react'
import { supabase } from '../utils/supabaseClient'

const AuthContext = createContext({})

const LOCAL_USERS_KEY = 'bittu_ai_local_users'
const LOCAL_SESSION_KEY = 'bittu_ai_local_session'

// Check if Supabase URL is a real configured project (not the placeholder)
function isPlaceholderSupabase() {
  const url = import.meta.env.VITE_SUPABASE_URL || 'https://vgiwwjfgujbkeovwwvcv.supabase.co'
  return url.includes('vgiwwjfgujbkeovwwvcv') || !url.startsWith('https://')
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
  const localSignUp = (email, password, fullName) => {
    const localUsers = JSON.parse(localStorage.getItem(LOCAL_USERS_KEY) || '[]')
    const normalizedEmail = email.toLowerCase().trim()
    const existing = localUsers.find(u => u.email === normalizedEmail)
    if (existing) {
      throw new Error('An account with this email already exists. Please Sign In.')
    }

    const newUser = {
      id: 'usr_' + Date.now().toString(36) + Math.random().toString(36).slice(2, 7),
      email: normalizedEmail,
      password, // Stored locally for offline authentication
      user_metadata: {
        full_name: fullName.trim() || normalizedEmail.split('@')[0],
      },
      created_at: new Date().toISOString(),
      auth_provider: 'local',
    }

    localUsers.push(newUser)
    localStorage.setItem(LOCAL_USERS_KEY, JSON.stringify(localUsers))
    localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: newUser }))

    setUser(newUser)
    setSession({ user: newUser, access_token: 'local_token' })
    return { user: newUser, session: { user: newUser } }
  }

  // Local signin handler
  const localSignIn = (email, password) => {
    const localUsers = JSON.parse(localStorage.getItem(LOCAL_USERS_KEY) || '[]')
    const normalizedEmail = email.toLowerCase().trim()
    const foundUser = localUsers.find(u => u.email === normalizedEmail)

    if (!foundUser) {
      // Auto-create for friendly demo testing if password meets criteria
      if (password && password.length >= 6) {
        return localSignUp(email, password, normalizedEmail.split('@')[0])
      }
      throw new Error('Account not found. Please click "Create Account" to sign up first.')
    }

    if (foundUser.password !== password) {
      throw new Error('Incorrect password. Please try again.')
    }

    localStorage.setItem(LOCAL_SESSION_KEY, JSON.stringify({ user: foundUser }))
    setUser(foundUser)
    setSession({ user: foundUser, access_token: 'local_token' })
    return { user: foundUser, session: { user: foundUser } }
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

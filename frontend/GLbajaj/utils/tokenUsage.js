/**
 * Bittu AI — Token Quota Client Manager (3 Tokens / 12 Days Cycle)
 * Provides centralized balance fetching, local caching, and real-time updates.
 */

import { getApiUrl } from './apiUrl'

const TOKENS_CACHE_KEY = 'bittu_user_tokens'

export function getCachedTokens(email) {
  try {
    const raw = localStorage.getItem(TOKENS_CACHE_KEY)
    if (!raw) return { tokens_remaining: 3, max_tokens: 3, can_generate: true, reset_text: '12d' }
    const parsed = JSON.parse(raw)
    if (email && parsed.email && parsed.email !== email.toLowerCase().trim()) {
      return { tokens_remaining: 3, max_tokens: 3, can_generate: true, reset_text: '12d' }
    }
    return parsed
  } catch {
    return { tokens_remaining: 3, max_tokens: 3, can_generate: true, reset_text: '12d' }
  }
}

export async function fetchUserTokens(email) {
  const cleanEmail = (email || localStorage.getItem('user_email') || 'guest@bittuai.online').trim().toLowerCase()
  try {
    const base = getApiUrl()
    const res = await fetch(`${base}/api/tokens/status?email=${encodeURIComponent(cleanEmail)}`)
    if (res.ok) {
      const data = await res.json()
      localStorage.setItem(TOKENS_CACHE_KEY, JSON.stringify(data))
      window.dispatchEvent(new CustomEvent('bittu_tokens_updated', { detail: data }))
      return data
    }
  } catch (err) {
    console.warn('[Tokens] Failed to fetch remote token status:', err)
  }
  return getCachedTokens(cleanEmail)
}

export async function consumeUserToken(email, action = 'ai_generation') {
  const cleanEmail = (email || localStorage.getItem('user_email') || 'guest@bittuai.online').trim().toLowerCase()
  const base = getApiUrl()
  
  const res = await fetch(`${base}/api/tokens/consume`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ email: cleanEmail, action }),
  })
  
  const data = await res.json().catch(() => ({}))
  
  if (!res.ok) {
    const errorMsg = data.detail || data.error || 'Token limit reached (0/3). Please wait for 12-day replenishment.'
    throw new Error(errorMsg)
  }
  
  // Update local cache
  const current = getCachedTokens(cleanEmail)
  const updated = {
    ...current,
    tokens_remaining: data.tokens_remaining,
    resets_at_iso: data.resets_at_iso,
    reset_text: data.reset_text,
    can_generate: data.tokens_remaining > 0,
  }
  localStorage.setItem(TOKENS_CACHE_KEY, JSON.stringify(updated))
  window.dispatchEvent(new CustomEvent('bittu_tokens_updated', { detail: updated }))
  return updated
}

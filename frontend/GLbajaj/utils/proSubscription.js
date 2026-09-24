/**
 * Bittu AI — DSA Pro Subscription State Manager
 * Handles local caching, backend status checks, and reactive state updates.
 */

import { getApiUrl } from './apiUrl'

const PRO_STORAGE_KEY = 'bittu_dsa_pro'

export function getCachedProStatus(userEmail = null) {
  try {
    const raw = localStorage.getItem(PRO_STORAGE_KEY)
    if (!raw) return { isPro: false, expiresAt: null }
    const parsed = JSON.parse(raw)
    
    // Check expiration timestamp
    if (parsed.expiresAt) {
      const expTime = new Date(parsed.expiresAt).getTime()
      if (!isNaN(expTime) && Date.now() > expTime) {
        localStorage.removeItem(PRO_STORAGE_KEY)
        return { isPro: false, expiresAt: null, expired: true }
      }
    }

    return {
      isPro: !!parsed.isPro,
      expiresAt: parsed.expiresAt || null,
      email: parsed.email || userEmail,
      plan: parsed.plan || 'DSA_LIFETIME_MASTER_PASS',
    }
  } catch {
    return { isPro: false, expiresAt: null }
  }
}

export function saveProStatus({ email, expiresAt, plan = 'DSA_LIFETIME_MASTER_PASS' }) {
  const data = {
    isPro: true,
    email: email || '',
    expiresAt: expiresAt || new Date(Date.now() + 36500 * 86400000).toISOString(),
    plan,
    updatedAt: new Date().toISOString(),
  }
  localStorage.setItem(PRO_STORAGE_KEY, JSON.stringify(data))
  window.dispatchEvent(new CustomEvent('bittu_pro_updated', { detail: data }))
  return data
}

export async function verifyPaymentLinkReturn(paymentId, email) {
  if (!paymentId) return { isPro: false }
  try {
    const base = getApiUrl()
    const res = await fetch(`${base}/api/payment/verify-payment-link`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ payment_id: paymentId, email }),
    })
    if (res.ok) {
      const data = await res.json()
      if (data.is_pro || data.success) {
        return saveProStatus({
          email: data.email || email,
          expiresAt: data.expires_at,
          plan: data.plan,
        })
      }
    }
  } catch (err) {
    console.error('[PaymentLink] Verification failed:', err)
  }
  return { isPro: false }
}

export async function fetchRemoteProStatus(email) {
  if (!email) return getCachedProStatus()
  try {
    const base = getApiUrl()
    const res = await fetch(`${base}/api/payment/status?email=${encodeURIComponent(email)}`)
    if (res.ok) {
      const data = await res.json()
      if (data.is_pro) {
        return saveProStatus({
          email,
          expiresAt: data.expires_at,
          plan: data.plan,
        })
      } else {
        localStorage.removeItem(PRO_STORAGE_KEY)
        return { isPro: false, expiresAt: null }
      }
    }
  } catch (err) {
    console.warn('[ProStatus] Failed to check remote status, falling back to cache:', err)
  }
  return getCachedProStatus(email)
}


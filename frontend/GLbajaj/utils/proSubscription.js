/**
 * Bittu AI — DSA Pro Subscription State Manager
 * Handles local caching, backend status checks, and reactive state updates.
 *
 * PLAN SEPARATION (2026-09-28):
 *  - DSA_JAVA_C_PASS        → Unlocks DSAHub + DSASolver (Java / C / Python problems)
 *  - TOP_INTERVIEW_PASS     → Unlocks Top Interview 150 questions only
 *  - DSA_LIFETIME_MASTER_PASS → Legacy plan (existing buyers): unlocks BOTH (backward compat)
 */

import { getApiUrl } from './apiUrl'

const PRO_STORAGE_KEY = 'bittu_dsa_pro'

/** Plans that grant DSA Java/C/Python problem access */
const DSA_PLANS = ['DSA_JAVA_C_PASS', 'DSA_LIFETIME_MASTER_PASS']

/** Plans that grant Top Interview 150 access */
const INTERVIEW_PLANS = ['TOP_INTERVIEW_PASS', 'DSA_LIFETIME_MASTER_PASS']

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

/**
 * Returns true if user has access to DSA Java/C/Python problems.
 * (DSA_JAVA_C_PASS or legacy DSA_LIFETIME_MASTER_PASS)
 */
export function isDsaPro(userEmail = null) {
  const status = getCachedProStatus(userEmail)
  if (!status.isPro) return false
  return DSA_PLANS.includes(status.plan)
}

/**
 * Returns true if user has access to Top Interview 150.
 * (TOP_INTERVIEW_PASS only — DSA pass does NOT grant this)
 */
export function isInterviewPro(userEmail = null) {
  const status = getCachedProStatus(userEmail)
  if (!status.isPro) return false
  return INTERVIEW_PLANS.includes(status.plan)
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

export async function verifyPaymentLinkReturn(paymentId, email, planId = null) {
  if (!paymentId) return { isPro: false }
  try {
    const base = getApiUrl()
    const res = await fetch(`${base}/api/payment/verify-payment-link`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ payment_id: paymentId, email, plan_id: planId }),
    })
    if (res.ok) {
      const data = await res.json()
      if (data.is_pro || data.success) {
        return saveProStatus({
          email: data.email || email,
          expiresAt: data.expires_at,
          plan: data.plan, // Backend returns the correct plan (DSA_JAVA_C_PASS or TOP_INTERVIEW_PASS)
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
        const cached = getCachedProStatus(email)
        if (cached?.email && cached.email.toLowerCase() === email.toLowerCase()) {
          localStorage.removeItem(PRO_STORAGE_KEY)
          window.dispatchEvent(new CustomEvent('bittu_pro_updated', { detail: { isPro: false, plan: null } }))
        }
        return { isPro: false, expiresAt: null }
      }
    }
  } catch (err) {
    console.warn('[ProStatus] Failed to check remote status, falling back to cache:', err)
  }
  return getCachedProStatus(email)
}


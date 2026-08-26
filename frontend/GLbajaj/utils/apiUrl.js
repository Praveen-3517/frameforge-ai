/**
 * Dynamic API Base URL Resolver
 * - When running on localhost / 127.0.0.1: uses relative '' so Vite proxy forwards to local backend (:8000)
 *   with zero latency, zero timeouts, and unlimited upload bandwidth.
 * - When deployed on production (e.g. Vercel): uses the Render cloud backend URL.
 */
export function getApiUrl() {
  if (typeof window !== 'undefined') {
    const host = window.location.hostname
    if (host === 'localhost' || host === '127.0.0.1') {
      return ''
    }
  }
  return import.meta.env.VITE_API_URL || 'https://frameforge-ai-fa8z.onrender.com'
}

export function getFullMediaUrl(pathOrFilename) {
  if (!pathOrFilename) return ''
  if (pathOrFilename.startsWith('http://') || pathOrFilename.startsWith('https://') || pathOrFilename.startsWith('data:')) {
    return pathOrFilename
  }
  const base = getApiUrl()
  const cleanPath = pathOrFilename.startsWith('/') ? pathOrFilename : `/api/media/${pathOrFilename}`
  return `${base}${cleanPath}`
}

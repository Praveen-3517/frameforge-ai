import React, { useState, useEffect } from 'react'
import { Coins, Sparkles, Clock, AlertCircle } from 'lucide-react'
import { fetchUserTokens, getCachedTokens } from '../utils/tokenUsage'
import { useAuth } from '../context/AuthContext'

export default function TokenBadge({ className = '' }) {
  const { user } = useAuth()
  const userEmail = user?.email || localStorage.getItem('user_email') || ''
  const [tokenInfo, setTokenInfo] = useState(() => getCachedTokens(userEmail))

  useEffect(() => {
    fetchUserTokens(userEmail).then((info) => {
      if (info) setTokenInfo(info)
    })

    const handleUpdate = (e) => {
      if (e.detail) setTokenInfo(e.detail)
    }

    window.addEventListener('bittu_tokens_updated', handleUpdate)
    return () => window.removeEventListener('bittu_tokens_updated', handleUpdate)
  }, [userEmail])

  const remaining = tokenInfo?.tokens_remaining ?? 3
  const max = tokenInfo?.max_tokens ?? 3
  const isExhausted = remaining <= 0

  return (
    <div
      className={`inline-flex items-center gap-1.5 px-3 py-1 rounded-xl border text-xs font-semibold backdrop-blur-md transition-all select-none shadow-sm ${
        isExhausted
          ? 'bg-rose-500/15 border-rose-500/30 text-rose-300'
          : remaining === 1
          ? 'bg-amber-500/15 border-amber-500/30 text-amber-300'
          : 'bg-gradient-to-r from-violet-500/15 to-cyan-500/15 border-violet-500/30 text-cyan-300'
      } ${className}`}
      title={`Token Balance: ${remaining}/${max} generations remaining. Replenishes every 12 days (${tokenInfo?.resets_at_iso || '12d'}).`}
    >
      <Coins size={13} className={isExhausted ? 'text-rose-400' : 'text-amber-400 fill-amber-400/30 animate-pulse'} />
      <span className="font-bold">
        {remaining}/{max} Tokens
      </span>
      {tokenInfo?.reset_text && (
        <span className={`text-[10px] font-mono px-1.5 py-0.2 rounded-md ${
          isExhausted ? 'bg-rose-500/20 text-rose-200 font-bold' : 'bg-white/10 text-white/70'
        }`}>
          {isExhausted ? `Resets in ${tokenInfo.reset_text}` : `• ${tokenInfo.reset_text}`}
        </span>
      )}
    </div>
  )
}

import { AlertTriangle, XCircle } from 'lucide-react'

export default function ErrorBanner({ message, onDismiss }) {
  if (!message) return null

  return (
    <div className="glass-card border border-rose-500/30 bg-rose-500/5 p-5 animate-in stagger-1">
      <div className="flex items-start gap-3">
        <AlertTriangle size={20} className="text-rose-400 shrink-0 mt-0.5" />
        <div className="flex-1 min-w-0">
          <p className="text-rose-300 font-semibold text-sm">Generation failed</p>
          <p className="text-rose-400/70 text-xs mt-1 break-words font-mono leading-relaxed">
            {message}
          </p>
        </div>
        {onDismiss && (
          <button
            id="btn-dismiss-error"
            onClick={onDismiss}
            className="text-rose-500/60 hover:text-rose-400 transition-colors shrink-0"
          >
            <XCircle size={18} />
          </button>
        )}
      </div>
    </div>
  )
}

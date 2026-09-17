import React from 'react'
import { Link } from 'react-router-dom'

export default class ErrorBoundary extends React.Component {
  constructor(props) {
    super(props)
    this.state = { hasError: false, error: null }
  }

  static getDerivedStateFromError(error) {
    return { hasError: true, error }
  }

  componentDidCatch(error, info) {
    console.error('🔴 ErrorBoundary caught:', error, info)
  }

  handleReset() {
    this.setState({ hasError: false, error: null })
  }

  render() {
    if (this.state.hasError) {
      return (
        <div className="min-h-screen bg-[#0B0D17] flex items-center justify-center px-4">
          <div className="max-w-md w-full text-center">
            {/* Glowing error orb */}
            <div className="w-20 h-20 mx-auto mb-6 rounded-full bg-gradient-to-br from-red-500/30 to-orange-500/20 border border-red-500/30 flex items-center justify-center shadow-lg shadow-red-500/10">
              <span className="text-3xl">⚠️</span>
            </div>

            <h1 className="text-xl font-bold text-white mb-2">
              Kuch galat ho gaya
            </h1>
            <p className="text-white/50 text-sm mb-1">Something went wrong on this page.</p>
            {this.state.error && (
              <p className="text-red-400/70 text-xs font-mono mb-6 bg-red-500/5 border border-red-500/10 rounded-lg px-3 py-2 break-all">
                {this.state.error.message}
              </p>
            )}

            <div className="flex items-center justify-center gap-3">
              <button
                onClick={() => this.handleReset()}
                className="px-4 py-2 rounded-xl bg-white/10 border border-white/10 text-white text-sm font-semibold hover:bg-white/15 transition-all"
              >
                🔄 Try Again
              </button>
              <Link
                to="/"
                onClick={() => this.handleReset()}
                className="px-4 py-2 rounded-xl bg-gradient-to-r from-violet-600 to-cyan-600 text-white text-sm font-semibold hover:opacity-90 transition-all"
              >
                🏠 Dashboard Par Jao
              </Link>
            </div>
          </div>
        </div>
      )
    }

    return this.props.children
  }
}

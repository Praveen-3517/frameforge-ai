import React from 'react'
import { Link } from 'react-router-dom'
import { Video, Shirt, Zap, Github } from 'lucide-react'
import StarField from '../components/StarField'

export default function Dashboard() {
  return (
    <div className="relative min-h-screen flex flex-col">
      <StarField />
      
      {/* Ambient orbs */}
      <div className="orb w-96 h-96 bg-violet-600/20 -top-48 -left-48" style={{ animationDelay: '0s' }} />
      <div className="orb w-80 h-80 bg-cyan-600/15 top-1/3 -right-40" style={{ animationDelay: '3s' }} />
      
      <header className="relative z-10 flex items-center justify-between px-6 py-5 max-w-6xl mx-auto w-full">
        <div className="flex items-center gap-2.5">
          <div className="w-8 h-8 rounded-lg bg-gradient-to-br from-violet-500 to-cyan-500 flex items-center justify-center shadow-lg shadow-violet-500/30">
            <Zap size={16} className="text-white" />
          </div>
          <span className="font-display font-bold text-white text-lg tracking-tight">
            One-Click <span className="gradient-text">AI Tools</span>
          </span>
        </div>
        <nav className="flex items-center gap-4">
          <a href="#" className="flex items-center gap-1.5 text-white/40 hover:text-white/70 text-sm font-medium transition-colors">
            <Github size={15} /> GitHub
          </a>
        </nav>
      </header>

      <main className="relative z-10 flex-1 flex flex-col items-center justify-center px-4 pb-16">
        <div className="text-center mb-12">
          <h1 className="text-4xl sm:text-5xl font-display font-bold text-white tracking-tight mb-4">
            Select an <span className="gradient-text">AI Tool</span>
          </h1>
          <p className="text-white/50 text-lg max-w-lg mx-auto">
            Welcome to your unified dashboard. Choose a tool below to get started.
          </p>
        </div>

        <div className="grid grid-cols-1 sm:grid-cols-2 gap-6 w-full max-w-3xl">
          {/* Tool 1 */}
          <Link to="/video" className="group block bg-white/5 border border-white/10 hover:border-violet-500/50 rounded-3xl p-6 transition-all hover:-translate-y-1 hover:shadow-2xl hover:shadow-violet-500/20 backdrop-blur-md text-left">
            <div className="w-12 h-12 rounded-xl bg-violet-500/20 border border-violet-500/30 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform">
              <Video className="text-violet-400" size={24} />
            </div>
            <h2 className="text-xl font-bold text-white mb-2 font-display">Text to Video</h2>
            <p className="text-sm text-white/50 leading-relaxed">
              Convert any story or script into a fully narrated, cinematic video with a single click. Completely automated.
            </p>
          </Link>

          {/* Tool 2 */}
          <Link to="/clothes" className="group block bg-white/5 border border-white/10 hover:border-cyan-500/50 rounded-3xl p-6 transition-all hover:-translate-y-1 hover:shadow-2xl hover:shadow-cyan-500/20 backdrop-blur-md text-left">
            <div className="w-12 h-12 rounded-xl bg-cyan-500/20 border border-cyan-500/30 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform">
              <Shirt className="text-cyan-400" size={24} />
            </div>
            <h2 className="text-xl font-bold text-white mb-2 font-display">AI Clothes Changer</h2>
            <p className="text-sm text-white/50 leading-relaxed">
              Upload a photo and instantly try on new outfits. Perfect virtual try-on while keeping your face and background unchanged.
            </p>
          </Link>
        </div>
      </main>
    </div>
  )
}

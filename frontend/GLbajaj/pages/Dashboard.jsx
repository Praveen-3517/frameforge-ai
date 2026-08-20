import React from 'react'
import { Link } from 'react-router-dom'
import { Video, Shirt, Zap, Github, Layers, Fingerprint, Sparkles } from 'lucide-react'
import StarField from '../components/StarField'

export default function Dashboard() {
  return (
    <div className="relative min-h-screen flex flex-col bg-[#0B0D17] text-white">
      <StarField />
      
      {/* Ambient orbs */}
      <div className="orb w-96 h-96 bg-violet-600/20 -top-48 -left-48" style={{ animationDelay: '0s' }} />
      <div className="orb w-80 h-80 bg-cyan-600/15 top-1/3 -right-40" style={{ animationDelay: '3s' }} />
      <div className="orb w-80 h-80 bg-pink-600/10 bottom-10 left-1/3" style={{ animationDelay: '5s' }} />
      
      <header className="relative z-10 flex items-center justify-between px-6 py-5 max-w-6xl mx-auto w-full">
        <div className="flex items-center gap-2.5">
          <div className="w-8 h-8 rounded-lg bg-gradient-to-br from-violet-500 to-cyan-500 flex items-center justify-center shadow-lg shadow-violet-500/30">
            <Zap size={16} className="text-white" />
          </div>
          <span className="font-display font-bold text-white text-lg tracking-tight">
            One-Click <span className="gradient-text">AI Tools</span>
          </span>
          <span className="hidden sm:inline-block px-2.5 py-0.5 rounded-full bg-white/5 border border-white/10 text-white/50 text-[11px] font-mono">
            Suite v3.0
          </span>
        </div>
        <nav className="flex items-center gap-4">
          <a
            href="http://localhost:8000/docs"
            target="_blank"
            rel="noopener noreferrer"
            className="text-white/40 hover:text-white/70 text-xs font-mono transition-colors"
          >
            API Docs
          </a>
          <a href="#" className="flex items-center gap-1.5 text-white/40 hover:text-white/70 text-sm font-medium transition-colors">
            <Github size={15} /> GitHub
          </a>
        </nav>
      </header>

      <main className="relative z-10 flex-1 flex flex-col items-center justify-center px-4 py-8 max-w-6xl mx-auto w-full">
        <div className="text-center mb-10">
          <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full bg-white/5 border border-white/10 text-xs font-mono text-white/70 mb-3">
            <Sparkles size={12} className="text-cyan-400" />
            AI Media Synthesis & Forensics Workspace
          </div>
          <h1 className="text-4xl sm:text-5xl font-display font-bold text-white tracking-tight mb-3">
            Select an <span className="gradient-text">AI Tool</span>
          </h1>
          <p className="text-white/50 text-base max-w-lg mx-auto">
            Choose a generative video engine, virtual fashion try-on, variant transformer, or forensic media analyzer below.
          </p>
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-5 w-full max-w-4xl">
          
          {/* Tool 1: Text to Video */}
          <Link
            to="/video"
            className="group block bg-white/5 border border-white/10 hover:border-violet-500/50 rounded-3xl p-6 transition-all hover:-translate-y-1 hover:shadow-2xl hover:shadow-violet-500/20 backdrop-blur-md text-left relative overflow-hidden"
          >
            <div className="w-12 h-12 rounded-xl bg-violet-500/20 border border-violet-500/30 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform">
              <Video className="text-violet-400" size={24} />
            </div>
            <div className="flex items-center justify-between mb-1.5">
              <h2 className="text-xl font-bold text-white font-display">Text to Video</h2>
              <span className="text-[11px] font-mono px-2 py-0.5 rounded bg-violet-500/10 text-violet-300 border border-violet-500/20">
                100% Free
              </span>
            </div>
            <p className="text-sm text-white/50 leading-relaxed">
              Convert any story or script into a fully narrated, cinematic video with a single click. Completely automated.
            </p>
          </Link>

          {/* Tool 2: AI Clothes Changer */}
          <Link
            to="/clothes"
            className="group block bg-white/5 border border-white/10 hover:border-pink-500/50 rounded-3xl p-6 transition-all hover:-translate-y-1 hover:shadow-2xl hover:shadow-pink-500/20 backdrop-blur-md text-left relative overflow-hidden"
          >
            <div className="w-12 h-12 rounded-xl bg-pink-500/20 border border-pink-500/30 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform">
              <Shirt className="text-pink-400" size={24} />
            </div>
            <div className="flex items-center justify-between mb-1.5">
              <h2 className="text-xl font-bold text-white font-display">AI Clothes Changer</h2>
              <span className="text-[11px] font-mono px-2 py-0.5 rounded bg-pink-500/10 text-pink-300 border border-pink-500/20">
                Virtual Try-On
              </span>
            </div>
            <p className="text-sm text-white/50 leading-relaxed">
              Upload a photo and instantly try on new outfits. Perfect virtual try-on while preserving pose and background.
            </p>
          </Link>

          {/* Tool 3: Video Variant Generator */}
          <Link
            to="/variant"
            className="group block bg-white/5 border border-white/10 hover:border-cyan-500/50 rounded-3xl p-6 transition-all hover:-translate-y-1 hover:shadow-2xl hover:shadow-cyan-500/20 backdrop-blur-md text-left relative overflow-hidden"
          >
            <div className="w-12 h-12 rounded-xl bg-cyan-500/20 border border-cyan-500/30 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform">
              <Layers className="text-cyan-400" size={24} />
            </div>
            <div className="flex items-center justify-between mb-1.5">
              <h2 className="text-xl font-bold text-white font-display">Create Video Variant</h2>
              <span className="text-[11px] font-mono px-2 py-0.5 rounded bg-cyan-500/10 text-cyan-300 border border-cyan-500/20">
                Transformer
              </span>
            </div>
            <p className="text-sm text-white/50 leading-relaxed">
              Transform and re-encode user-owned media with custom aspect ratio scaling, color grading, audio normalization, and fresh file hashes.
            </p>
          </Link>

          {/* Tool 4: Audio & Video Fingerprint Analyzer */}
          <Link
            to="/fingerprint"
            className="group block bg-white/5 border border-white/10 hover:border-emerald-500/50 rounded-3xl p-6 transition-all hover:-translate-y-1 hover:shadow-2xl hover:shadow-emerald-500/20 backdrop-blur-md text-left relative overflow-hidden"
          >
            <div className="w-12 h-12 rounded-xl bg-emerald-500/20 border border-emerald-500/30 flex items-center justify-center mb-4 group-hover:scale-110 transition-transform">
              <Fingerprint className="text-emerald-400" size={24} />
            </div>
            <div className="flex items-center justify-between mb-1.5">
              <h2 className="text-xl font-bold text-white font-display">Fingerprint Analyzer</h2>
              <span className="text-[11px] font-mono px-2 py-0.5 rounded bg-emerald-500/10 text-emerald-300 border border-emerald-500/20">
                Forensics
              </span>
            </div>
            <p className="text-sm text-white/50 leading-relaxed">
              Analyze audio waveforms, frequency spectrums, tempo/BPM, visual perceptual dHash, scene cuts, and compare dual media files.
            </p>
          </Link>

        </div>
      </main>
    </div>
  )
}

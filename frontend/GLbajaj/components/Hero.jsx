import { Sparkles, Film, Wand2 } from 'lucide-react'

export default function Hero() {
  return (
    <div className="relative text-center mb-12 animate-in stagger-1">
      {/* Badge */}
      <div className="inline-flex items-center gap-2 px-4 py-1.5 rounded-full mb-6
                      bg-violet-500/10 border border-violet-500/20 text-violet-300 text-sm font-medium">
        <Sparkles size={14} className="text-violet-400 animate-pulse" />
        Powered by GPT-4o · Replicate · OpenAI TTS
        <Sparkles size={14} className="text-violet-400 animate-pulse" />
      </div>

      {/* Main Heading */}
      <h1 className="font-display text-5xl md:text-7xl font-extrabold tracking-tight mb-5 leading-[1.05]">
        <span className="gradient-text">Text</span>
        <span className="text-white/20 mx-3">→</span>
        <span className="gradient-text">Video</span>
        <br />
        <span className="text-white text-4xl md:text-5xl font-bold">in seconds.</span>
      </h1>

      {/* Subtitle */}
      <p className="text-white/50 text-lg md:text-xl font-light max-w-2xl mx-auto leading-relaxed">
        Type a story, scene description, or script. Our AI pipeline breaks it into scenes,
        generates cinematic clips, adds a voiceover, and hands you a finished MP4.
      </p>

      {/* Feature Pills */}
      <div className="flex flex-wrap justify-center gap-3 mt-8">
        {[
          { icon: Wand2, label: 'AI Scene Writing', color: 'violet' },
          { icon: Film, label: 'Video Generation', color: 'cyan' },
          { icon: Sparkles, label: 'Auto Narration', color: 'rose' },
        ].map(({ icon: Icon, label, color }) => (
          <div
            key={label}
            className={`flex items-center gap-2 px-4 py-2 rounded-full text-sm font-medium
              ${color === 'violet' ? 'bg-violet-500/10 text-violet-300 border border-violet-500/20' : ''}
              ${color === 'cyan'   ? 'bg-cyan-500/10   text-cyan-300   border border-cyan-500/20'   : ''}
              ${color === 'rose'   ? 'bg-rose-500/10   text-rose-300   border border-rose-500/20'   : ''}
            `}
          >
            <Icon size={14} />
            {label}
          </div>
        ))}
      </div>
    </div>
  )
}

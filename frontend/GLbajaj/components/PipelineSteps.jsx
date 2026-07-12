import { CheckCircle2, Circle, Loader2, Brain, Mic2, Film, Scissors, Sparkles } from 'lucide-react'

const STEPS = [
  {
    id: 1,
    icon: Brain,
    title: 'Scene Writing',
    desc: 'Gemini AI creates 3 cinematic scene prompts',
    color: 'violet',
  },
  {
    id: 2,
    icon: Mic2,
    title: 'Voiceover',
    desc: 'Edge-TTS generates a cinematic MP3 narration',
    color: 'cyan',
  },
  {
    id: 3,
    icon: Film,
    title: 'Scene Images',
    desc: 'Pollinations AI generates 3 HD cinematic images',
    color: 'rose',
  },
  {
    id: 4,
    icon: Scissors,
    title: 'Final Edit',
    desc: 'MoviePy animates images with Ken Burns effect + audio',
    color: 'amber',
  },
]

function StepItem({ step, currentStep, isLast }) {
  const { icon: Icon, title, desc, color, id } = step
  const isDone = currentStep > id
  const isActive = currentStep === id
  const isPending = currentStep < id

  const colorMap = {
    violet: { ring: 'ring-violet-500/50', bg: 'bg-violet-500/20', text: 'text-violet-400', glow: 'shadow-violet-500/30', active: 'bg-violet-500', border: 'border-violet-500/30' },
    cyan:   { ring: 'ring-cyan-500/50',   bg: 'bg-cyan-500/20',   text: 'text-cyan-400',   glow: 'shadow-cyan-500/30',   active: 'bg-cyan-500',   border: 'border-cyan-500/30'   },
    rose:   { ring: 'ring-rose-500/50',   bg: 'bg-rose-500/20',   text: 'text-rose-400',   glow: 'shadow-rose-500/30',   active: 'bg-rose-500',   border: 'border-rose-500/30'   },
    amber:  { ring: 'ring-amber-500/50',  bg: 'bg-amber-500/20',  text: 'text-amber-400',  glow: 'shadow-amber-500/30',  active: 'bg-amber-500',  border: 'border-amber-500/30'  },
  }
  const c = colorMap[color]

  return (
    <div className="flex items-start gap-4 relative">
      {/* Connector line */}
      {!isLast && (
        <div className="absolute left-[22px] top-12 bottom-0 w-[2px] 
                        bg-gradient-to-b from-white/10 to-transparent" />
      )}

      {/* Icon Badge */}
      <div className={`
        relative z-10 flex items-center justify-center w-11 h-11 rounded-xl shrink-0
        transition-all duration-500
        ${isDone  ? `${c.active} shadow-lg ${c.glow}` : ''}
        ${isActive ? `${c.bg} ring-2 ${c.ring} shadow-lg ${c.glow}` : ''}
        ${isPending ? 'bg-white/5 ring-1 ring-white/10' : ''}
      `}>
        {isDone
          ? <CheckCircle2 size={20} className="text-white" />
          : isActive
            ? <Loader2 size={20} className={`${c.text} animate-spin`} />
            : <Icon size={18} className="text-white/30" />
        }
      </div>

      {/* Text */}
      <div className="pt-1.5 pb-6">
        <p className={`font-semibold text-sm transition-colors duration-300
          ${isDone ? 'text-white' : isActive ? c.text : 'text-white/30'}`}>
          {title}
        </p>
        <p className={`text-xs mt-0.5 transition-colors duration-300
          ${isActive || isDone ? 'text-white/50' : 'text-white/20'}`}>
          {desc}
        </p>
      </div>
    </div>
  )
}

export default function PipelineSteps({ currentStep }) {
  if (!currentStep) return null

  return (
    <div className="glass-card p-6 animate-in stagger-2">
      {/* Header */}
      <div className="flex items-center gap-2 mb-6">
        <div className="loading-bar flex-1" />
        <div className="flex items-center gap-1.5 text-xs text-white/40 font-mono shrink-0">
          <Sparkles size={11} className="text-violet-400" />
          Processing…
        </div>
        <div className="loading-bar flex-1" />
      </div>

      {/* Steps */}
      <div className="pl-1">
        {STEPS.map((step, i) => (
          <StepItem
            key={step.id}
            step={step}
            currentStep={currentStep}
            isLast={i === STEPS.length - 1}
          />
        ))}
      </div>

      {/* ETA notice */}
      <div className="mt-2 p-3 rounded-lg bg-white/3 border border-white/5 text-center">
        <p className="text-white/30 text-xs font-mono">
          ⏱ Est. 3–8 mins · AI video generation takes time
        </p>
      </div>
    </div>
  )
}

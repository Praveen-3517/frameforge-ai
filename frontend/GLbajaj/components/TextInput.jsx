import { Wand2, Lightbulb } from 'lucide-react'

const EXAMPLES = [
  "A lone astronaut discovers a glowing alien artifact buried in the red sands of Mars. She brushes it off carefully and it begins to pulse with golden light.",
  "A medieval blacksmith forges an enchanted sword at midnight. The blade absorbs moonlight and begins to glow, as ancient runes appear along its edge.",
  "A girl chases a paper lantern through a moonlit bamboo forest. The lantern leads her to a hidden waterfall where mythical creatures bathe in silver mist.",
]

export default function TextInput({ value, onChange, onSubmit, isLoading, charLimit = 2000 }) {
  const remaining = charLimit - value.length
  const isOverLimit = remaining < 0
  const isUnderMin = value.trim().length < 10

  const handleExample = (ex) => onChange(ex)

  return (
    <div className="glass-card p-6 space-y-5 animate-in stagger-2">

      {/* Label Row */}
      <div className="flex items-center justify-between">
        <label htmlFor="story-input" className="font-display font-semibold text-white text-sm flex items-center gap-2">
          <Wand2 size={16} className="text-violet-400" />
          Your Story / Script
        </label>
        <span className={`text-xs font-mono transition-colors
          ${remaining < 100 ? 'text-rose-400' : 'text-white/30'}`}>
          {remaining} chars left
        </span>
      </div>

      {/* Textarea */}
      <textarea
        id="story-input"
        className="textarea-cosmic h-44"
        placeholder="Describe your story, scene, or script… The more vivid and descriptive, the better the video."
        value={value}
        onChange={(e) => onChange(e.target.value)}
        maxLength={charLimit}
        disabled={isLoading}
        spellCheck
      />

      {/* Example prompts */}
      <div>
        <div className="flex items-center gap-1.5 text-white/30 text-xs mb-2 font-medium">
          <Lightbulb size={11} />
          Try an example
        </div>
        <div className="flex flex-col gap-2">
          {EXAMPLES.map((ex, i) => (
            <button
              key={i}
              id={`btn-example-${i + 1}`}
              onClick={() => handleExample(ex)}
              disabled={isLoading}
              className="text-left text-xs text-white/35 hover:text-white/70 px-3 py-2 rounded-lg
                         bg-white/3 border border-white/5 hover:border-violet-500/20 hover:bg-violet-500/5
                         transition-all duration-200 line-clamp-1 cursor-pointer disabled:cursor-not-allowed"
            >
              {ex.slice(0, 80)}…
            </button>
          ))}
        </div>
      </div>

      {/* Generate Button */}
      <button
        id="btn-generate"
        onClick={onSubmit}
        disabled={isLoading || isUnderMin || isOverLimit}
        className="btn-primary w-full text-base"
      >
        {isLoading ? (
          <>
            <svg className="animate-spin w-5 h-5 relative z-10" fill="none" viewBox="0 0 24 24">
              <circle className="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" strokeWidth="4" />
              <path className="opacity-75" fill="currentColor"
                d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4z" />
            </svg>
            <span className="relative z-10">Generating your video…</span>
          </>
        ) : (
          <>
            <Wand2 size={18} className="relative z-10" />
            <span className="relative z-10">Generate Video</span>
          </>
        )}
      </button>

      {/* Disclaimer */}
      <p className="text-center text-white/20 text-xs">
        AI video generation takes 3–8 minutes. Please keep this tab open.
      </p>
    </div>
  )
}

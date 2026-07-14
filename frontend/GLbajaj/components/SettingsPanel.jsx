import React from 'react'
import { Settings2 } from 'lucide-react'

export default function SettingsPanel({ options, setOptions, disabled }) {
  return (
    <div className="mt-4 bg-white/5 border border-white/10 rounded-2xl p-4 backdrop-blur-md">
      <div className="flex items-center gap-2 mb-4 text-white/80 font-medium text-sm">
        <Settings2 size={16} className="text-violet-400" />
        Video Generation Settings
      </div>
      
      <div className="grid grid-cols-1 sm:grid-cols-3 gap-4">
        {/* Style */}
        <div className="flex flex-col gap-1.5">
          <label className="text-xs text-white/50 font-medium">Style</label>
          <select 
            disabled={disabled}
            value={options.style}
            onChange={(e) => setOptions({...options, style: e.target.value})}
            className="bg-white/5 border border-white/10 rounded-xl px-3 py-2 text-sm text-white focus:outline-none focus:border-violet-500/50 transition-colors disabled:opacity-50"
          >
            <option value="Photorealistic, Cinematic, 8k">Cinematic</option>
            <option value="Anime style, Studio Ghibli, highly detailed">Anime</option>
            <option value="Watercolor painting, beautiful, artistic">Watercolor</option>
            <option value="Cyberpunk, neon lighting, futuristic">Cyberpunk</option>
            <option value="3D render, Pixar style, cute">3D Animation</option>
          </select>
        </div>

        {/* Quality */}
        <div className="flex flex-col gap-1.5">
          <label className="text-xs text-white/50 font-medium">Quality</label>
          <select 
            disabled={disabled}
            value={options.quality}
            onChange={(e) => setOptions({...options, quality: e.target.value})}
            className="bg-white/5 border border-white/10 rounded-xl px-3 py-2 text-sm text-white focus:outline-none focus:border-violet-500/50 transition-colors disabled:opacity-50"
          >
            <option value="720p">HD (720p)</option>
            <option value="1080p">Full HD (1080p)</option>
          </select>
        </div>

        {/* Aspect Ratio */}
        <div className="flex flex-col gap-1.5">
          <label className="text-xs text-white/50 font-medium">Format</label>
          <select 
            disabled={disabled}
            value={options.aspect_ratio}
            onChange={(e) => setOptions({...options, aspect_ratio: e.target.value})}
            className="bg-white/5 border border-white/10 rounded-xl px-3 py-2 text-sm text-white focus:outline-none focus:border-violet-500/50 transition-colors disabled:opacity-50"
          >
            <option value="16:9">YouTube (16:9)</option>
            <option value="9:16">Shorts / Reels (9:16)</option>
          </select>
        </div>
      </div>
    </div>
  )
}

import { useRef, useState } from 'react'
import { Play, Pause, Volume2, VolumeX, Download, Maximize2, RotateCcw, CheckCircle2 } from 'lucide-react'

export default function VideoPlayer({ videoUrl, jobId, onReset }) {
  const videoRef = useRef(null)
  const [playing, setPlaying] = useState(false)
  const [muted, setMuted] = useState(false)
  const [progress, setProgress] = useState(0)
  const [duration, setDuration] = useState(0)
  const [currentTime, setCurrentTime] = useState(0)
  const [hovered, setHovered] = useState(false)

  const togglePlay = () => {
    if (!videoRef.current) return
    if (playing) {
      videoRef.current.pause()
    } else {
      videoRef.current.play()
    }
    setPlaying(!playing)
  }

  const toggleMute = () => {
    if (!videoRef.current) return
    videoRef.current.muted = !muted
    setMuted(!muted)
  }

  const handleTimeUpdate = () => {
    if (!videoRef.current) return
    const curr = videoRef.current.currentTime
    const dur = videoRef.current.duration || 1
    setCurrentTime(curr)
    setProgress((curr / dur) * 100)
  }

  const handleLoadedMetadata = () => {
    if (videoRef.current) setDuration(videoRef.current.duration)
  }

  const handleSeek = (e) => {
    if (!videoRef.current) return
    const rect = e.currentTarget.getBoundingClientRect()
    const ratio = (e.clientX - rect.left) / rect.width
    videoRef.current.currentTime = ratio * (videoRef.current.duration || 0)
  }

  const handleEnded = () => setPlaying(false)

  const fullscreen = () => videoRef.current?.requestFullscreen?.()

  const fmt = (s) => {
    const m = Math.floor(s / 60)
    const sec = Math.floor(s % 60).toString().padStart(2, '0')
    return `${m}:${sec}`
  }

  return (
    <div className="animate-in stagger-2 space-y-6">

      {/* Success Banner */}
      <div className="flex items-center gap-3 p-4 rounded-xl
                      bg-emerald-500/10 border border-emerald-500/20">
        <CheckCircle2 size={20} className="text-emerald-400 shrink-0" />
        <div>
          <p className="text-emerald-300 font-semibold text-sm">Your video is ready!</p>
          <p className="text-white/40 text-xs mt-0.5 font-mono">Job ID: {jobId}</p>
        </div>
      </div>

      {/* Video Container */}
      <div
        className="relative rounded-2xl overflow-hidden video-glow bg-black group"
        onMouseEnter={() => setHovered(true)}
        onMouseLeave={() => setHovered(false)}
      >
        <video
          ref={videoRef}
          src={videoUrl}
          className="w-full aspect-video object-contain"
          onTimeUpdate={handleTimeUpdate}
          onLoadedMetadata={handleLoadedMetadata}
          onEnded={handleEnded}
          onClick={togglePlay}
        />

        {/* Controls Overlay */}
        <div className={`absolute inset-0 flex flex-col justify-end transition-opacity duration-300
                        ${hovered || !playing ? 'opacity-100' : 'opacity-0'}`}>
          {/* Gradient scrim */}
          <div className="absolute inset-0 bg-gradient-to-t from-black/80 via-transparent to-transparent pointer-events-none" />

          {/* Progress Bar */}
          <div
            className="relative z-10 mx-4 mb-3 h-1 rounded-full bg-white/20 cursor-pointer group/bar"
            onClick={handleSeek}
          >
            <div
              className="h-full rounded-full bg-gradient-to-r from-violet-500 to-cyan-500 relative"
              style={{ width: `${progress}%` }}
            >
              <div className="absolute right-0 top-1/2 -translate-y-1/2 w-3 h-3 rounded-full bg-white
                              opacity-0 group-hover/bar:opacity-100 transition-opacity" />
            </div>
          </div>

          {/* Controls Row */}
          <div className="relative z-10 flex items-center justify-between px-4 pb-4 gap-3">
            {/* Left: Play + Time */}
            <div className="flex items-center gap-3">
              <button
                id="btn-play-pause"
                onClick={togglePlay}
                className="flex items-center justify-center w-9 h-9 rounded-full
                           bg-white/10 hover:bg-white/20 border border-white/10
                           transition-all duration-200 text-white"
              >
                {playing ? <Pause size={16} /> : <Play size={16} />}
              </button>
              <span className="text-white/60 text-xs font-mono tabular-nums">
                {fmt(currentTime)} / {fmt(duration)}
              </span>
            </div>

            {/* Right: Mute + Fullscreen */}
            <div className="flex items-center gap-2">
              <button
                id="btn-mute"
                onClick={toggleMute}
                className="flex items-center justify-center w-9 h-9 rounded-full
                           bg-white/10 hover:bg-white/20 border border-white/10
                           transition-all duration-200 text-white"
              >
                {muted ? <VolumeX size={15} /> : <Volume2 size={15} />}
              </button>
              <button
                id="btn-fullscreen"
                onClick={fullscreen}
                className="flex items-center justify-center w-9 h-9 rounded-full
                           bg-white/10 hover:bg-white/20 border border-white/10
                           transition-all duration-200 text-white"
              >
                <Maximize2 size={15} />
              </button>
            </div>
          </div>
        </div>

        {/* Big play button when paused */}
        {!playing && (
          <button
            onClick={togglePlay}
            className="absolute inset-0 flex items-center justify-center"
          >
            <div className="flex items-center justify-center w-20 h-20 rounded-full
                            bg-white/10 backdrop-blur-sm border border-white/20
                            hover:bg-white/20 hover:scale-110 transition-all duration-300">
              <Play size={32} className="text-white ml-1" />
            </div>
          </button>
        )}
      </div>

      {/* Action Buttons */}
      <div className="flex flex-col sm:flex-row gap-3">
        <a
          id="btn-download-video"
          href={videoUrl}
          download={`frameforge_${jobId}.mp4`}
          className="btn-primary flex-1 text-center no-underline"
        >
          <Download size={18} className="relative z-10" />
          <span className="relative z-10">Download MP4</span>
        </a>

        <button
          id="btn-create-new"
          onClick={onReset}
          className="flex items-center justify-center gap-2 px-6 py-4 rounded-xl font-semibold
                     bg-white/5 border border-white/10 text-white/70 hover:text-white
                     hover:bg-white/10 hover:border-white/20 transition-all duration-200 flex-1"
        >
          <RotateCcw size={16} />
          Create New Video
        </button>
      </div>
    </div>
  )
}

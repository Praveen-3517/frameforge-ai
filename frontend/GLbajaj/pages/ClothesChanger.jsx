import React, { useState } from 'react'
import { Link } from 'react-router-dom'
import { ArrowLeft, Upload, Shirt, Image as ImageIcon, Download } from 'lucide-react'
import axios from 'axios'
import StarField from '../components/StarField'

export default function ClothesChanger() {
  const [image, setImage] = useState(null)
  const [preview, setPreview] = useState(null)
  const [prompt, setPrompt] = useState('')
  const [result, setResult] = useState(null)
  const [isLoading, setIsLoading] = useState(false)
  const [error, setError] = useState('')

  const handleImageChange = (e) => {
    const file = e.target.files[0]
    if (file) {
      setImage(file)
      setPreview(URL.createObjectURL(file))
      setResult(null)
    }
  }

  const handleGenerate = async () => {
    if (!image || !prompt) return
    setIsLoading(true)
    setError('')
    setResult(null)

    const formData = new FormData()
    formData.append('image', image)
    formData.append('prompt', prompt)

    try {
      const API_URL = import.meta.env.VITE_API_URL || 'http://localhost:8000'
      const res = await axios.post(`${API_URL}/change-clothes`, formData, {
        headers: { 'Content-Type': 'multipart/form-data' }
      })
      setResult(res.data.image_url)
    } catch (err) {
      setError(err.response?.data?.detail || 'Failed to change clothes. Please try again.')
    } finally {
      setIsLoading(false)
    }
  }

  return (
    <div className="relative min-h-screen flex flex-col">
      <StarField />
      <div className="orb w-96 h-96 bg-cyan-600/20 -top-48 -left-48" style={{ animationDelay: '0s' }} />

      <header className="relative z-10 flex items-center px-6 py-5 max-w-6xl mx-auto w-full">
        <Link to="/" className="flex items-center gap-2 text-white/50 hover:text-white transition-colors text-sm font-medium">
          <ArrowLeft size={16} /> Back to Dashboard
        </Link>
      </header>

      <main className="relative z-10 flex-1 flex flex-col items-center px-4 pb-16">
        <div className="w-full max-w-2xl mt-4">
          <div className="text-center mb-8">
            <h1 className="text-3xl sm:text-4xl font-display font-bold text-white tracking-tight mb-2">
              AI <span className="text-cyan-400">Clothes Changer</span>
            </h1>
            <p className="text-white/50">Upload a photo and describe your new outfit.</p>
          </div>

          <div className="bg-white/5 border border-white/10 rounded-3xl p-6 backdrop-blur-md">
            
            {error && (
              <div className="mb-4 bg-red-500/10 border border-red-500/20 text-red-400 p-4 rounded-xl text-sm">
                {error}
              </div>
            )}

            <div className="grid grid-cols-1 md:grid-cols-2 gap-6 mb-6">
              {/* Left: Original Image Upload */}
              <div>
                <label className="block text-sm font-medium text-white/70 mb-2">Original Photo</label>
                <div className="relative aspect-[3/4] bg-black/20 rounded-2xl border-2 border-dashed border-white/10 hover:border-cyan-500/50 transition-colors flex flex-col items-center justify-center overflow-hidden group">
                  {preview ? (
                    <img src={preview} alt="Upload preview" className="w-full h-full object-cover" />
                  ) : (
                    <div className="text-center p-4">
                      <Upload className="w-8 h-8 text-white/30 mx-auto mb-2" />
                      <p className="text-xs text-white/40">Click to upload photo</p>
                    </div>
                  )}
                  <input type="file" accept="image/*" onChange={handleImageChange} className="absolute inset-0 opacity-0 cursor-pointer" />
                </div>
              </div>

              {/* Right: Result Image */}
              <div>
                <label className="block text-sm font-medium text-white/70 mb-2">Result</label>
                <div className="relative aspect-[3/4] bg-black/20 rounded-2xl border border-white/5 flex items-center justify-center overflow-hidden">
                  {isLoading ? (
                    <div className="flex flex-col items-center animate-pulse">
                      <Shirt className="w-8 h-8 text-cyan-400 mb-2" />
                      <p className="text-xs text-cyan-400">Changing clothes...</p>
                    </div>
                  ) : result ? (
                    <img src={result} alt="Result" className="w-full h-full object-cover" />
                  ) : (
                    <div className="text-center p-4">
                      <ImageIcon className="w-8 h-8 text-white/10 mx-auto mb-2" />
                      <p className="text-xs text-white/20">Generated photo will appear here</p>
                    </div>
                  )}
                </div>
              </div>
            </div>

            <div className="space-y-4">
              <div>
                <label className="block text-sm font-medium text-white/70 mb-2">New Outfit Description</label>
                <input
                  type="text"
                  placeholder="e.g. a stylish blue business suit, white shirt"
                  value={prompt}
                  onChange={(e) => setPrompt(e.target.value)}
                  className="w-full bg-black/20 border border-white/10 rounded-xl px-4 py-3 text-white placeholder-white/20 focus:outline-none focus:border-cyan-500/50 transition-colors"
                />
              </div>

              <button
                onClick={handleGenerate}
                disabled={!image || !prompt || isLoading}
                className="w-full bg-cyan-500 hover:bg-cyan-400 disabled:bg-cyan-500/20 disabled:text-white/30 text-white font-bold py-3.5 rounded-xl shadow-lg shadow-cyan-500/20 transition-all flex items-center justify-center gap-2"
              >
                {isLoading ? 'Processing...' : 'Change Clothes'}
              </button>
              
              {result && (
                <a
                  href={result}
                  download="new_outfit.webp"
                  className="w-full bg-white/10 hover:bg-white/20 text-white font-bold py-3.5 rounded-xl border border-white/10 transition-all flex items-center justify-center gap-2"
                >
                  <Download size={20} /> Download Photo
                </a>
              )}
            </div>

          </div>
        </div>
      </main>
    </div>
  )
}

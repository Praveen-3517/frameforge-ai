import React from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import Dashboard from './pages/Dashboard'
import TextToVideo from './pages/TextToVideo'
import ClothesChanger from './pages/ClothesChanger'
import VideoVariantGenerator from './pages/VideoVariantGenerator'
import FingerprintAnalyzer from './pages/FingerprintAnalyzer'
import MultiViewPlayer from './pages/MultiViewPlayer'

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Dashboard />} />
        <Route path="/video" element={<TextToVideo />} />
        <Route path="/clothes" element={<ClothesChanger />} />
        <Route path="/variant" element={<VideoVariantGenerator />} />
        <Route path="/fingerprint" element={<FingerprintAnalyzer />} />
        <Route path="/multiview" element={<MultiViewPlayer />} />
      </Routes>
    </BrowserRouter>
  )
}

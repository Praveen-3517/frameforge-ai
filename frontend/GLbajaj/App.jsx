import React from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import { AuthProvider } from './context/AuthContext'
import AuthModal from './components/auth/AuthModal'
import Dashboard from './pages/Dashboard'
import TextToVideo from './pages/TextToVideo'
import ClothesChanger from './pages/ClothesChanger'
import VideoVariantGenerator from './pages/VideoVariantGenerator'
import FingerprintAnalyzer from './pages/FingerprintAnalyzer'
import MultiViewPlayer from './pages/MultiViewPlayer'
import KidsShortsGenerator from './pages/KidsShortsGenerator'
import DialogueVideoGenerator from './pages/DialogueVideoGenerator'
import DSAHub from './pages/DSAHub'
import DSASolver from './pages/DSASolver'

export default function App() {
  return (
    <AuthProvider>
      <BrowserRouter>
        <AuthModal />
        <Routes>
          <Route path="/" element={<Dashboard />} />
          <Route path="/dialogue" element={<DialogueVideoGenerator />} />
          <Route path="/video" element={<TextToVideo />} />
          <Route path="/kids" element={<KidsShortsGenerator />} />
          <Route path="/clothes" element={<ClothesChanger />} />
          <Route path="/variant" element={<VideoVariantGenerator />} />
          <Route path="/fingerprint" element={<FingerprintAnalyzer />} />
          <Route path="/multiview" element={<MultiViewPlayer />} />
          <Route path="/dsa" element={<DSAHub />} />
          <Route path="/dsa/:id" element={<DSASolver />} />
        </Routes>
      </BrowserRouter>
    </AuthProvider>
  )
}

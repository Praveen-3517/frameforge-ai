import React from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import { AuthProvider } from './context/AuthContext'
import AuthModal from './components/auth/AuthModal'
import EarlyBirdModal from './components/EarlyBirdModal'
import FeedbackModal from './components/FeedbackModal'
import ErrorBoundary from './components/ErrorBoundary'
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
        <EarlyBirdModal />
        <FeedbackModal />
        <Routes>
          <Route path="/" element={<ErrorBoundary><Dashboard /></ErrorBoundary>} />
          <Route path="/dialogue" element={<ErrorBoundary><DialogueVideoGenerator /></ErrorBoundary>} />
          <Route path="/video" element={<ErrorBoundary><TextToVideo /></ErrorBoundary>} />
          <Route path="/kids" element={<ErrorBoundary><KidsShortsGenerator /></ErrorBoundary>} />
          <Route path="/clothes" element={<ErrorBoundary><ClothesChanger /></ErrorBoundary>} />
          <Route path="/variant" element={<ErrorBoundary><VideoVariantGenerator /></ErrorBoundary>} />
          <Route path="/fingerprint" element={<ErrorBoundary><FingerprintAnalyzer /></ErrorBoundary>} />
          <Route path="/multiview" element={<ErrorBoundary><MultiViewPlayer /></ErrorBoundary>} />
          <Route path="/dsa" element={<ErrorBoundary><DSAHub /></ErrorBoundary>} />
          <Route path="/dsa/:id" element={<ErrorBoundary><DSASolver /></ErrorBoundary>} />
        </Routes>
      </BrowserRouter>
    </AuthProvider>
  )
}

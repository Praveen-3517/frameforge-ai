import React, { useEffect } from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import { AuthProvider } from './context/AuthContext'
import { getApiUrl } from './utils/apiUrl'
import AuthModal from './components/auth/AuthModal'
import EarlyBirdModal from './components/EarlyBirdModal'
import FeedbackModal from './components/FeedbackModal'
import AdminFeedbackViewer from './components/AdminFeedbackViewer'
import ErrorBoundary from './components/ErrorBoundary'
import Dashboard from './pages/Dashboard'
import TextToVideo from './pages/TextToVideo'
import ClothesChanger from './pages/ClothesChanger'
import FingerprintAnalyzer from './pages/FingerprintAnalyzer'
import MultiViewPlayer from './pages/MultiViewPlayer'
import KidsShortsGenerator from './pages/KidsShortsGenerator'
import DialogueVideoGenerator from './pages/DialogueVideoGenerator'
import DSAHub from './pages/DSAHub'
import DSASolver from './pages/DSASolver'
import TopInterview150 from './pages/TopInterview150'

export default function App() {
  // Silent background pre-warm of Render cloud backend on site load
  useEffect(() => {
    const prewarm = () => {
      const base = getApiUrl()
      if (base) {
        fetch(`${base}/health`, { method: 'GET', keepalive: true }).catch(() => {})
      }
    }
    // Fire immediately on mount
    prewarm()
    // Heartbeat every 10 minutes to keep Render alive while user is active
    const timer = setInterval(prewarm, 10 * 60 * 1000)
    return () => clearInterval(timer)
  }, [])
  return (
    <AuthProvider>
      <BrowserRouter>
        <AuthModal />
        <EarlyBirdModal />
        <FeedbackModal />
        <AdminFeedbackViewer />
        <Routes>
          <Route path="/" element={<ErrorBoundary><Dashboard /></ErrorBoundary>} />
          <Route path="/dialogue" element={<ErrorBoundary><DialogueVideoGenerator /></ErrorBoundary>} />
          <Route path="/video" element={<ErrorBoundary><TextToVideo /></ErrorBoundary>} />
          <Route path="/kids" element={<ErrorBoundary><KidsShortsGenerator /></ErrorBoundary>} />
          <Route path="/clothes" element={<ErrorBoundary><ClothesChanger /></ErrorBoundary>} />
          <Route path="/fingerprint" element={<ErrorBoundary><FingerprintAnalyzer /></ErrorBoundary>} />
          <Route path="/multiview" element={<ErrorBoundary><MultiViewPlayer /></ErrorBoundary>} />
          <Route path="/dsa" element={<ErrorBoundary><DSAHub /></ErrorBoundary>} />
          <Route path="/dsa/top-interview-150" element={<ErrorBoundary><TopInterview150 /></ErrorBoundary>} />
          <Route path="/dsa/:id" element={<ErrorBoundary><DSASolver /></ErrorBoundary>} />
        </Routes>
      </BrowserRouter>
    </AuthProvider>
  )
}

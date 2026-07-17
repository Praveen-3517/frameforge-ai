import React from 'react'
import { BrowserRouter, Routes, Route } from 'react-router-dom'
import Dashboard from './pages/Dashboard'
import TextToVideo from './pages/TextToVideo'
import ClothesChanger from './pages/ClothesChanger'

export default function App() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Dashboard />} />
        <Route path="/video" element={<TextToVideo />} />
        <Route path="/clothes" element={<ClothesChanger />} />
      </Routes>
    </BrowserRouter>
  )
}

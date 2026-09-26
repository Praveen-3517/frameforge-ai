import React, { useState } from 'react'
import { ShieldCheck, UserCheck, ExternalLink, Mail, Github, FileText, Info, X, Heart } from 'lucide-react'

export default function TrustFooter({ isLight }) {
  const [modalType, setModalType] = useState(null) // 'about' | 'privacy' | 'terms' | 'disclaimer' | null

  return (
    <>
      <footer className={`mt-14 pt-8 pb-10 border-t ${
        isLight ? 'border-slate-200/80 bg-white/40' : 'border-white/10 bg-black/20'
      } backdrop-blur-md`}>
        <div className="max-w-7xl mx-auto px-4 sm:px-6">
          
          {/* Top Banner: Verification & Disclaimer */}
          <div className={`p-4 rounded-2xl mb-8 border flex flex-col md:flex-row items-start md:items-center justify-between gap-4 ${
            isLight
              ? 'bg-gradient-to-r from-violet-50 to-indigo-50/50 border-violet-200 text-slate-700'
              : 'bg-gradient-to-r from-violet-950/20 via-[#0e101f] to-cyan-950/20 border-violet-500/20 text-white/80'
          }`}>
            <div className="flex items-center gap-3">
              <div className="w-9 h-9 rounded-xl bg-violet-600/20 border border-violet-500/30 flex items-center justify-center text-violet-400 shrink-0">
                <ShieldCheck size={20} />
              </div>
              <div>
                <h4 className="text-xs sm:text-sm font-bold flex items-center gap-2">
                  <span>Authentic Educational AI & DSA Platform</span>
                  <span className="text-[10px] px-2 py-0.5 rounded-full bg-emerald-500/20 text-emerald-400 font-mono border border-emerald-500/30">
                    100% Safe & Verified
                  </span>
                </h4>
                <p className={`text-[11px] sm:text-xs mt-0.5 ${isLight ? 'text-slate-600' : 'text-white/50'}`}>
                  Created & maintained by <strong>Praveen Kushwaha</strong> (MCA Student & AI Developer) for student learning & AI research.
                </p>
              </div>
            </div>

            <div className="flex items-center gap-2 w-full md:w-auto justify-end">
              <a
                href="https://github.com/Praveen-3517/frameforge-ai"
                target="_blank"
                rel="noreferrer"
                className="px-3 py-1.5 rounded-lg text-xs font-semibold bg-violet-600 hover:bg-violet-500 text-white flex items-center gap-1.5 transition-all shadow-sm"
              >
                <Github size={13} />
                <span>GitHub Source</span>
                <ExternalLink size={11} />
              </a>
            </div>
          </div>

          {/* Bottom Grid */}
          <div className="flex flex-col sm:flex-row items-center justify-between gap-4 text-xs">
            <div className={`flex flex-wrap items-center gap-x-6 gap-y-2 ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
              <span>© {new Date().getFullYear()} Bittu AI (bittuai.online)</span>
              <button onClick={() => setModalType('about')} className="hover:underline hover:text-violet-400">
                About Developer
              </button>
              <button onClick={() => setModalType('disclaimer')} className="hover:underline hover:text-violet-400">
                Brand Disclaimer
              </button>
              <button onClick={() => setModalType('privacy')} className="hover:underline hover:text-violet-400">
                Privacy Policy
              </button>
              <button onClick={() => setModalType('terms')} className="hover:underline hover:text-violet-400">
                Terms of Service
              </button>
            </div>

            <div className={`flex items-center gap-2 font-mono text-[11px] ${isLight ? 'text-slate-500' : 'text-white/40'}`}>
              <span>Built with</span>
              <Heart size={12} className="text-red-500 fill-red-500 inline" />
              <span>by Praveen Kushwaha</span>
            </div>
          </div>

        </div>
      </footer>

      {/* Trust & Policy Modal */}
      {modalType && (
        <div className="fixed inset-0 z-50 flex items-center justify-center p-4 bg-black/70 backdrop-blur-sm animate-fadeIn">
          <div className="relative w-full max-w-2xl max-h-[85vh] overflow-y-auto rounded-2xl bg-[#111322] border border-white/15 p-6 text-white shadow-2xl">
            
            {/* Close Button */}
            <button
              onClick={() => setModalType(null)}
              className="absolute top-4 right-4 p-2 rounded-lg bg-white/5 hover:bg-white/10 text-white/60 hover:text-white"
            >
              <X size={18} />
            </button>

            {/* Modal Content */}
            {modalType === 'about' && (
              <div className="space-y-4">
                <div className="flex items-center gap-3 border-b border-white/10 pb-4">
                  <UserCheck className="text-violet-400" size={24} />
                  <div>
                    <h3 className="text-lg font-bold">About Developer & Platform</h3>
                    <p className="text-xs text-white/50">Bittu AI — Educational AI & DSA Suite</p>
                  </div>
                </div>
                <p className="text-sm text-white/80 leading-relaxed">
                  <strong>Bittu AI (bittuai.online)</strong> is an independent open-source educational platform designed and developed by <strong>Praveen Kushwaha</strong> (MCA 1st Year student).
                </p>
                <div className="bg-white/5 rounded-xl p-4 border border-white/10 text-xs space-y-2 text-white/70">
                  <p><strong>🎯 Mission:</strong> To provide free, high-performance tools for Indian students to learn DSA with 1,800+ interactive coding problems in Python, C, and Java, alongside experimenting with generative AI media workflows.</p>
                  <p><strong>🔬 Technologies:</strong> Python FastAPI, React.js, Pyodide (WASM in-browser execution), Google Gemini API, OpenCV, SciPy, and Razorpay Payments.</p>
                  <p><strong>🌐 Developer Portfolio:</strong> <a href="https://github.com/Praveen-3517" target="_blank" rel="noreferrer" className="text-violet-400 underline">github.com/Praveen-3517</a></p>
                </div>
              </div>
            )}

            {modalType === 'disclaimer' && (
              <div className="space-y-4">
                <div className="flex items-center gap-3 border-b border-white/10 pb-4">
                  <Info className="text-cyan-400" size={24} />
                  <div>
                    <h3 className="text-lg font-bold">Brand & Legal Disclaimer</h3>
                    <p className="text-xs text-white/50">Independent Student Portfolio Project</p>
                  </div>
                </div>
                <div className="p-4 rounded-xl bg-cyan-950/20 border border-cyan-500/30 text-xs text-cyan-200/90 leading-relaxed space-y-3">
                  <p>
                    <strong>Notice of Independence:</strong> Bittu AI (hosted at <code>bittuai.online</code>) is an educational, non-commercial portfolio web application built by student developer <strong>Praveen Kushwaha</strong>.
                  </p>
                  <p>
                    This platform is <strong>NOT</strong> affiliated with, associated with, authorized by, endorsed by, or in any way officially connected with <strong>Sahinov Pvt Ltd</strong> (operators of <code>bittuai.com</code>) or any other commercial marketing agency.
                  </p>
                  <p>
                    The name "Bittu AI" is used purely as an educational project identifier. All trademarks, registered trademarks, and company names are the property of their respective owners.
                  </p>
                </div>
              </div>
            )}

            {modalType === 'privacy' && (
              <div className="space-y-4">
                <div className="flex items-center gap-3 border-b border-white/10 pb-4">
                  <ShieldCheck className="text-emerald-400" size={24} />
                  <div>
                    <h3 className="text-lg font-bold">Privacy Policy</h3>
                    <p className="text-xs text-white/50">Last updated: September 2026</p>
                  </div>
                </div>
                <div className="text-xs text-white/70 space-y-3 leading-relaxed">
                  <p><strong>1. Data Collection:</strong> We respect your privacy. Bittu AI does NOT harvest or sell personal data. The in-browser DSA code runner runs directly inside your own web browser via WebAssembly (Pyodide).</p>
                  <p><strong>2. Media Processing:</strong> Uploaded images and video prompts are processed ephemerally for generative AI tools and are not stored permanently or shared with third parties.</p>
                  <p><strong>3. Payment Safety:</strong> All Pro pass transactions are handled directly through <strong>Razorpay</strong>, an RBI-authorized payment gateway with PCI-DSS compliance and 256-bit encryption.</p>
                  <p><strong>4. Contact:</strong> For any privacy questions, reach out via our GitHub repository: <a href="https://github.com/Praveen-3517/frameforge-ai" className="text-violet-400 underline">Praveen-3517/frameforge-ai</a>.</p>
                </div>
              </div>
            )}

            {modalType === 'terms' && (
              <div className="space-y-4">
                <div className="flex items-center gap-3 border-b border-white/10 pb-4">
                  <FileText className="text-amber-400" size={24} />
                  <div>
                    <h3 className="text-lg font-bold">Terms of Service</h3>
                    <p className="text-xs text-white/50">Terms for using Bittu AI</p>
                  </div>
                </div>
                <div className="text-xs text-white/70 space-y-3 leading-relaxed">
                  <p><strong>1. Educational Use:</strong> Bittu AI is provided "as-is" for educational, programming practice, and generative AI research purposes.</p>
                  <p><strong>2. Fair Usage:</strong> Users agree not to misuse media generation tools for illegal, deceptive, or abusive purposes.</p>
                  <p><strong>3. Code Compilation:</strong> DSA problem submissions are evaluated in a local sandboxed browser environment.</p>
                </div>
              </div>
            )}

            <div className="pt-4 border-t border-white/10 flex justify-end">
              <button
                onClick={() => setModalType(null)}
                className="px-4 py-2 rounded-xl bg-violet-600 hover:bg-violet-500 text-xs font-bold text-white transition-all"
              >
                Close Window
              </button>
            </div>

          </div>
        </div>
      )}
    </>
  )
}

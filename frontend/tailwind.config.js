/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./GLbajaj/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      fontFamily: {
        sans: ['Inter', 'system-ui', 'sans-serif'],
        display: ['Outfit', 'Inter', 'sans-serif'],
        mono: ['JetBrains Mono', 'monospace'],
      },
      colors: {
        cosmic: {
          950: '#020008',
          900: '#06000f',
          800: '#0d0020',
          700: '#150032',
        },
        violet: {
          400: '#a78bfa',
          500: '#8b5cf6',
          600: '#7c3aed',
        },
        cyan: {
          400: '#22d3ee',
          500: '#06b6d4',
        },
        rose: {
          400: '#fb7185',
          500: '#f43f5e',
        },
      },
      animation: {
        'gradient-shift': 'gradientShift 6s ease infinite',
        'pulse-slow': 'pulse 3s cubic-bezier(0.4, 0, 0.6, 1) infinite',
        'float': 'float 6s ease-in-out infinite',
        'orbit': 'orbit 8s linear infinite',
        'shimmer': 'shimmer 2s linear infinite',
        'fade-in-up': 'fadeInUp 0.6s ease forwards',
        'scale-in': 'scaleIn 0.4s ease forwards',
        'spin-slow': 'spin 4s linear infinite',
        'bounce-gentle': 'bounceGentle 2s ease-in-out infinite',
        'glow-pulse': 'glowPulse 2s ease-in-out infinite',
      },
      keyframes: {
        gradientShift: {
          '0%, 100%': { backgroundPosition: '0% 50%' },
          '50%': { backgroundPosition: '100% 50%' },
        },
        float: {
          '0%, 100%': { transform: 'translateY(0px)' },
          '50%': { transform: 'translateY(-12px)' },
        },
        orbit: {
          '0%': { transform: 'rotate(0deg) translateX(60px) rotate(0deg)' },
          '100%': { transform: 'rotate(360deg) translateX(60px) rotate(-360deg)' },
        },
        shimmer: {
          '0%': { backgroundPosition: '-200% 0' },
          '100%': { backgroundPosition: '200% 0' },
        },
        fadeInUp: {
          '0%': { opacity: '0', transform: 'translateY(20px)' },
          '100%': { opacity: '1', transform: 'translateY(0)' },
        },
        scaleIn: {
          '0%': { opacity: '0', transform: 'scale(0.9)' },
          '100%': { opacity: '1', transform: 'scale(1)' },
        },
        bounceGentle: {
          '0%, 100%': { transform: 'translateY(0)' },
          '50%': { transform: 'translateY(-6px)' },
        },
        glowPulse: {
          '0%, 100%': { boxShadow: '0 0 20px rgba(139, 92, 246, 0.4)' },
          '50%': { boxShadow: '0 0 40px rgba(139, 92, 246, 0.8), 0 0 60px rgba(139, 92, 246, 0.3)' },
        },
      },
      backdropBlur: {
        xs: '2px',
      },
      backgroundSize: {
        '300%': '300%',
      },
    },
  },
  plugins: [],
}

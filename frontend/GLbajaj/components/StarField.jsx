import { useMemo } from 'react'

/* Generates a deterministic star field using seeded positions */
function Star({ style }) {
  return <div className="star" style={style} />
}

export default function StarField() {
  const stars = useMemo(() => {
    return Array.from({ length: 120 }, (_, i) => ({
      id: i,
      style: {
        left: `${(i * 37 + 11) % 100}%`,
        top: `${(i * 53 + 7) % 100}%`,
        width: i % 5 === 0 ? '2px' : '1px',
        height: i % 5 === 0 ? '2px' : '1px',
        '--duration': `${2 + (i % 5)}s`,
        '--delay': `${(i % 30) * 0.1}s`,
        '--max-opacity': i % 3 === 0 ? '0.9' : '0.4',
      },
    }))
  }, [])

  return (
    <div className="stars-bg">
      {stars.map((s) => <Star key={s.id} style={s.style} />)}
    </div>
  )
}

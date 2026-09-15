// ═══════════════════════════════════════════════════
//  DSA Stats — Streak, XP, Level, Activity Calendar
//  All data stored in localStorage (no backend needed)
// ═══════════════════════════════════════════════════

const KEYS = {
  streak: 'dsa_streak',
  lastDate: 'dsa_last_date',
  xp: 'dsa_xp',
  activity: 'dsa_activity',   // { "2026-09-15": 3 } — problems solved per day
}

// XP per difficulty
export const XP_MAP = { Easy: 10, Medium: 25, Hard: 50 }

// Level thresholds
export const LEVELS = [
  { name: 'Beginner',    min: 0,    icon: '🌱', color: '#6b7280' },
  { name: 'Coder',       min: 100,  icon: '💻', color: '#8b5cf6' },
  { name: 'Problem Solver', min: 300, icon: '🧩', color: '#06b6d4' },
  { name: 'Expert',      min: 700,  icon: '⚡', color: '#f59e0b' },
  { name: 'Master',      min: 1200, icon: '🏆', color: '#10b981' },
  { name: 'Legend',      min: 2000, icon: '👑', color: '#f43f5e' },
]

// ── Helpers ─────────────────────────────────────────
function todayStr() {
  return new Date().toISOString().slice(0, 10) // "2026-09-15"
}

function yesterdayStr() {
  const d = new Date()
  d.setDate(d.getDate() - 1)
  return d.toISOString().slice(0, 10)
}

function safeGet(key, fallback) {
  try { return JSON.parse(localStorage.getItem(key) ?? JSON.stringify(fallback)) }
  catch { return fallback }
}

function safeSet(key, value) {
  try { localStorage.setItem(key, JSON.stringify(value)) } catch {}
}

// ── Streak ──────────────────────────────────────────
export function getStreak() {
  return safeGet(KEYS.streak, 0)
}

export function updateStreak() {
  const last = safeGet(KEYS.lastDate, '')
  const today = todayStr()
  const yesterday = yesterdayStr()

  if (last === today) return getStreak()   // already updated today

  let streak = safeGet(KEYS.streak, 0)
  if (last === yesterday) {
    streak += 1   // consecutive day
  } else {
    streak = 1    // streak broken, reset to 1
  }

  safeSet(KEYS.streak, streak)
  safeSet(KEYS.lastDate, today)
  return streak
}

// ── XP ──────────────────────────────────────────────
export function getXP() {
  return safeGet(KEYS.xp, 0)
}

export function addXP(difficulty) {
  const gained = XP_MAP[difficulty] || 10
  const current = getXP()
  const next = current + gained
  safeSet(KEYS.xp, next)
  return { gained, total: next }
}

// ── Level ────────────────────────────────────────────
export function getLevel(xp = null) {
  const totalXP = xp ?? getXP()
  let level = LEVELS[0]
  for (const l of LEVELS) {
    if (totalXP >= l.min) level = l
    else break
  }
  const idx = LEVELS.indexOf(level)
  const nextLevel = LEVELS[idx + 1] || null
  const progressInLevel = nextLevel
    ? ((totalXP - level.min) / (nextLevel.min - level.min)) * 100
    : 100
  return { ...level, xp: totalXP, nextLevel, progressInLevel: Math.min(100, progressInLevel) }
}

// ── Activity Calendar ────────────────────────────────
export function getActivity() {
  return safeGet(KEYS.activity, {})
}

export function recordActivity(count = 1) {
  const activity = getActivity()
  const today = todayStr()
  activity[today] = (activity[today] || 0) + count
  safeSet(KEYS.activity, activity)
}

// Get last N days of activity
export function getRecentActivity(days = 30) {
  const activity = getActivity()
  const result = []
  for (let i = days - 1; i >= 0; i--) {
    const d = new Date()
    d.setDate(d.getDate() - i)
    const str = d.toISOString().slice(0, 10)
    result.push({ date: str, count: activity[str] || 0 })
  }
  return result
}

// ── On Solve — call this when a problem is solved ────
export function onProblemSolved(difficulty) {
  updateStreak()
  const xpResult = addXP(difficulty)
  recordActivity(1)
  return xpResult
}

// ── Topic Stats ──────────────────────────────────────
export function getTopicStats(solvedIds, allProblems) {
  const topicMap = {}
  for (const p of allProblems) {
    if (!topicMap[p.topic]) topicMap[p.topic] = { total: 0, solved: 0 }
    topicMap[p.topic].total++
    if (solvedIds.includes(p.id)) topicMap[p.topic].solved++
  }
  return Object.entries(topicMap)
    .map(([topic, data]) => ({ topic, ...data }))
    .sort((a, b) => b.total - a.total)
}

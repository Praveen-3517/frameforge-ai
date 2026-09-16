import { supabase } from './supabaseClient'

/**
 * Syncs DSA solved and bookmarks with Supabase for the authenticated user.
 * Provides instant local fallback if Supabase is unconfigured or offline.
 */

function isRealSupabase() {
  const url = import.meta.env.VITE_SUPABASE_URL || ''
  return url && !url.includes('vgiwwjfgujbkeovwwvcv') && url.startsWith('https://')
}

// Fetch cloud progress on user login and merge with local
export async function syncProgressOnLogin(userId) {
  if (!userId) return null

  const localSolved = JSON.parse(localStorage.getItem('dsa_solved') || '[]')
  const localBookmarks = JSON.parse(localStorage.getItem('dsa_bookmarks') || '[]')

  if (!isRealSupabase()) {
    return { solved: localSolved, bookmarks: localBookmarks }
  }

  try {
    // Fetch from Supabase
    const { data, error } = await supabase
      .from('user_dsa_progress')
      .select('*')
      .eq('user_id', userId)
      .single()

    if (error && error.code !== 'PGRST116') { // PGRST116 = no rows returned
      console.warn('Supabase fetch notice:', error.message)
      return { solved: localSolved, bookmarks: localBookmarks }
    }

    if (data) {
      // Merge unique solved IDs
      const mergedSolved = Array.from(new Set([...(data.solved_problems || []), ...localSolved]))
      const mergedBookmarks = Array.from(new Set([...(data.bookmarks || []), ...localBookmarks]))

      localStorage.setItem('dsa_solved', JSON.stringify(mergedSolved))
      localStorage.setItem('dsa_bookmarks', JSON.stringify(mergedBookmarks))

      // Update Supabase with merged result
      await supabase
        .from('user_dsa_progress')
        .upsert({
          user_id: userId,
          solved_problems: mergedSolved,
          bookmarks: mergedBookmarks,
          updated_at: new Date().toISOString(),
        })

      return { solved: mergedSolved, bookmarks: mergedBookmarks }
    } else {
      // Create new initial record in Supabase
      await supabase
        .from('user_dsa_progress')
        .insert({
          user_id: userId,
          solved_problems: localSolved,
          bookmarks: localBookmarks,
          created_at: new Date().toISOString(),
          updated_at: new Date().toISOString(),
        })

      return { solved: localSolved, bookmarks: localBookmarks }
    }
  } catch (err) {
    console.warn('Cloud sync on login notice:', err)
    return { solved: localSolved, bookmarks: localBookmarks }
  }
}

// Background upsert when a problem is solved or bookmarked
export async function saveProgressToCloud(userId, solvedList, bookmarksList) {
  if (!userId || !isRealSupabase()) return

  try {
    await supabase
      .from('user_dsa_progress')
      .upsert({
        user_id: userId,
        solved_problems: solvedList,
        bookmarks: bookmarksList,
        updated_at: new Date().toISOString(),
      })
  } catch (err) {
    console.warn('Background cloud save notice:', err)
  }
}

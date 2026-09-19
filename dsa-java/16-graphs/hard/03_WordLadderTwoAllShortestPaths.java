import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

/**
 * Problem: Word Ladder II - All Shortest Paths (LeetCode 126)
 * Asked in: Amazon, Google, Facebook, Microsoft
 * 
 * Given two words (beginWord and endWord), and a dictionary's word list,
 * find all shortest transformation sequence(s) from beginWord to endWord.
 * 
 * Approach:
 * BFS for Shortest Distance Map + DFS Backtracking for Path Reconstruction:
 * 1. BFS starting from beginWord:
 *    - Records minimum distance (depth) from beginWord to every reachable word.
 *    - Once endWord is reached at depth D, stop expanding further depths.
 * 2. DFS from endWord backwards to beginWord (or from beginWord forward):
 *    - Only step onto neighbor words whose distance is strictly currentDistance - 1 (or + 1).
 *    - This guarantees ONLY shortest paths are explored and constructed!
 * 
 * Time Complexity: O(N * 26 * L + Paths)
 * Space Complexity: O(N * L)
 */
class WordLadderTwoAllShortestPaths {

    public static List<List<String>> findLadders(String beginWord, String endWord, List<String> wordList) {
        List<List<String>> results = new ArrayList<>();
        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) return results;

        Map<String, Integer> distMap = new HashMap<>();
        Queue<String> queue = new ArrayDeque<>();

        queue.offer(beginWord);
        distMap.put(beginWord, 0);

        // BFS to calculate minimum distance to each word
        while (!queue.isEmpty()) {
            String curr = queue.poll();
            int currDist = distMap.get(curr);

            if (curr.equals(endWord)) break;

            char[] chars = curr.toCharArray();
            for (int i = 0; i < chars.length; i++) {
                char orig = chars[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == orig) continue;
                    chars[i] = c;
                    String next = new String(chars);

                    if (dict.contains(next) && !distMap.containsKey(next)) {
                        distMap.put(next, currDist + 1);
                        queue.offer(next);
                    }
                }
                chars[i] = orig;
            }
        }

        if (!distMap.containsKey(endWord)) return results;

        // DFS to reconstruct all paths
        List<String> path = new ArrayList<>();
        path.add(beginWord);
        dfs(beginWord, endWord, distMap, path, results);

        return results;
    }

    private static void dfs(String curr, String endWord, Map<String, Integer> distMap, List<String> path, List<List<String>> results) {
        if (curr.equals(endWord)) {
            results.add(new ArrayList<>(path));
            return;
        }

        int currDist = distMap.get(curr);
        char[] chars = curr.toCharArray();

        for (int i = 0; i < chars.length; i++) {
            char orig = chars[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == orig) continue;
                chars[i] = c;
                String next = new String(chars);

                // Only proceed if next word is on the shortest path (distance == currDist + 1)
                if (distMap.containsKey(next) && distMap.get(next) == currDist + 1) {
                    path.add(next);
                    dfs(next, endWord, distMap, path, results);
                    path.remove(path.size() - 1);
                }
            }
            chars[i] = orig;
        }
    }

    public static void main(String[] args) {
        String beginWord = "hit";
        String endWord = "cog";
        List<String> wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog");

        List<List<String>> ladders = findLadders(beginWord, endWord, wordList);
        System.out.println("Shortest Ladders: " + ladders);
        // Expected: [[hit, hot, dot, dog, cog], [hit, hot, lot, log, cog]]
    }
}

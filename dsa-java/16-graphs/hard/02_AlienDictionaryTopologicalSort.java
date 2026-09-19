import java.util.ArrayDeque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

/**
 * Problem: Alien Dictionary (LeetCode 269)
 * Asked in: Facebook, Amazon, Google, Microsoft, Airbnb
 * 
 * There is a new alien language that uses the English alphabet. However, the order among
 * the letters is unknown to you. You are given a list of strings words from the alien language's
 * dictionary, where the strings are sorted lexicographically by the rules of this new language.
 * Return a string of the unique letters in the new alien language sorted in lexicographically
 * increasing order. If the order is invalid, return "".
 * 
 * Approach:
 * Graph Modeling + Topological Sort (Kahn's Algorithm):
 * 1. Initialize directed graph with all unique characters present across all words.
 * 2. Compare adjacent words (words[i] and words[i+1]):
 *    - Prefix check: If words[i] starts with words[i+1] and words[i].length > words[i+1].length,
 *      the ordering is invalid (e.g., "apple" before "app"), return "".
 *    - Find first differing character: add directed edge c1 -> c2 and increment in-degree of c2.
 * 3. Run Kahn's algorithm (BFS on nodes with in-degree 0).
 * 4. If length of resulting string == number of unique characters, return string; else return "".
 * 
 * Time Complexity: O(C) where C is total length of all words in the input list.
 * Space Complexity: O(U + min(U^2, N)) where U is number of unique characters (<= 26).
 */
class AlienDictionaryTopologicalSort {

    public static String alienOrder(String[] words) {
        Map<Character, Set<Character>> adj = new HashMap<>();
        Map<Character, Integer> inDegree = new HashMap<>();

        // Initialize all unique characters
        for (String word : words) {
            for (char c : word.toCharArray()) {
                adj.putIfAbsent(c, new HashSet<>());
                inDegree.putIfAbsent(c, 0);
            }
        }

        // Build directed edges from adjacent words
        for (int i = 0; i < words.length - 1; i++) {
            String w1 = words[i];
            String w2 = words[i + 1];

            // Check invalid prefix order (e.g., "abcd" before "ab")
            if (w1.length() > w2.length() && w1.startsWith(w2)) {
                return "";
            }

            int minLen = Math.min(w1.length(), w2.length());
            for (int j = 0; j < minLen; j++) {
                char c1 = w1.charAt(j);
                char c2 = w2.charAt(j);
                if (c1 != c2) {
                    if (!adj.get(c1).contains(c2)) {
                        adj.get(c1).add(c2);
                        inDegree.put(c2, inDegree.get(c2) + 1);
                    }
                    break;
                }
            }
        }

        // BFS Kahn's Algorithm
        Queue<Character> queue = new ArrayDeque<>();
        for (char c : inDegree.keySet()) {
            if (inDegree.get(c) == 0) {
                queue.offer(c);
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!queue.isEmpty()) {
            char curr = queue.poll();
            sb.append(curr);

            for (char neighbor : adj.get(curr)) {
                inDegree.put(neighbor, inDegree.get(neighbor) - 1);
                if (inDegree.get(neighbor) == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        return sb.length() == inDegree.size() ? sb.toString() : "";
    }

    public static void main(String[] args) {
        String[] words1 = {"wrt", "wrf", "er", "ett", "rftt"};
        System.out.println("Alien Order 1: " + alienOrder(words1) + " (Expected: wertf)");

        String[] words2 = {"z", "x"};
        System.out.println("Alien Order 2: " + alienOrder(words2) + " (Expected: zx)");

        String[] words3 = {"z", "x", "z"};
        System.out.println("Alien Order 3 (Cycle): " + alienOrder(words3) + " (Expected: \"\")");
    }
}

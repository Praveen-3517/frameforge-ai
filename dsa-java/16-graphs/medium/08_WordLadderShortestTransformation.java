import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Queue;
import java.util.Set;

/**
 * Problem: Word Ladder (LeetCode 127)
 * Asked in: Amazon, Facebook, Google, Microsoft, Bloomberg
 * 
 * Given two words, beginWord and endWord, and a dictionary wordList, return the number
 * of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
 * 
 * Approach:
 * Unweighted Shortest Path with Breadth-First Search (BFS):
 * 1. Convert wordList to a HashSet for O(1) existence checks.
 * 2. If endWord is not in the set, return 0.
 * 3. Enqueue beginWord at step 1.
 * 4. In BFS:
 *    - For each character position (0 to L-1) of current word, try replacing with 'a' through 'z'.
 *    - If new string equals endWord, return level + 1.
 *    - If new string exists in dictionary set, remove from set (marks visited) and enqueue.
 * 
 * Time Complexity: O(M^2 * N) where M is word length, N is number of words.
 * Space Complexity: O(M * N) for the word set and queue.
 */
class WordLadderShortestTransformation {

    public static int ladderLength(String beginWord, String endWord, List<String> wordList) {
        Set<String> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) return 0;

        Queue<String> queue = new ArrayDeque<>();
        queue.offer(beginWord);
        int steps = 1;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();

            for (int i = 0; i < levelSize; i++) {
                String currentWord = queue.poll();
                char[] chars = currentWord.toCharArray();

                for (int pos = 0; pos < chars.length; pos++) {
                    char originalChar = chars[pos];

                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue;
                        chars[pos] = c;
                        String newWord = new String(chars);

                        if (newWord.equals(endWord)) {
                            return steps + 1;
                        }

                        if (dict.contains(newWord)) {
                            dict.remove(newWord); // Mark visited
                            queue.offer(newWord);
                        }
                    }
                    chars[pos] = originalChar;
                }
            }
            steps++;
        }

        return 0;
    }

    public static void main(String[] args) {
        String beginWord = "hit";
        String endWord = "cog";
        List<String> wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog");

        System.out.println("Ladder length: " + ladderLength(beginWord, endWord, wordList) + " (Expected: 5)");
        // hit -> hot -> dot -> dog -> cog
    }
}

/**
 * Problem: Maximum Score Words Formed by Letters (LeetCode 1255)
 * Asked in: Google, Amazon
 * 
 * Given a list of words, list of single letters (might be duplicates), and score of every character.
 * Return the maximum score of any valid set of words formed by using the given letters.
 * Each letter can only be used once. Each word can only be used once.
 * 
 * Approach - Bitmask Enumeration over All Subsets of Words:
 * For each bitmask from 0 to 2^n - 1 (representing which words to include):
 * 1. Count letter usage for selected words.
 * 2. Check if available letters can support this combination.
 * 3. If valid, compute and track maximum score.
 * 
 * Time Complexity: O(2^N * L) where N = words count, L = avg word length
 * Space Complexity: O(1) auxiliary
 */
class MaximumScoreWordsFormedByLetters {

    public static int maxScoreWords(String[] words, char[] letters, int[] score) {
        int[] available = new int[26];
        for (char c : letters) {
            available[c - 'a']++;
        }

        int n = words.length;
        int maxScore = 0;

        for (int mask = 0; mask < (1 << n); mask++) {
            int[] used = new int[26];
            int currentScore = 0;
            boolean valid = true;

            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue;
                for (char c : words[i].toCharArray()) {
                    used[c - 'a']++;
                    currentScore += score[c - 'a'];
                }
            }

            for (int j = 0; j < 26; j++) {
                if (used[j] > available[j]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                maxScore = Math.max(maxScore, currentScore);
            }
        }

        return maxScore;
    }

    public static void main(String[] args) {
        String[] words = {"dog", "cat", "dad", "good"};
        char[] letters = {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'};
        int[] score = {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        System.out.println("Max score: " + maxScoreWords(words, letters, score) + " (Expected: 23)");
        // "dad" + "good" = 5+1+5 + 3+2+2+5 = 11 + 12 = 23... 
        // Actually "dad"=d+a+d=5+1+5=11, "good"=g+o+o+d=3+2+2+5=12, total=23
    }
}

/**
 * Problem: Longest Repeating Character Replacement (LeetCode 424)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Facebook, Bloomberg
 * 
 * You are given a string s and an integer k. You can choose any character of the string
 * and change it to any other uppercase English character. You can perform this operation
 * at most k times. Return the length of the longest substring containing the same letter
 * you can get after performing the above operations.
 * 
 * Key Insight:
 * In a valid window [left, right], we need:
 * windowSize - maxFreq <= k
 * where maxFreq is the count of the most frequent character in the window.
 * 
 * We don't need to re-compute maxFreq when shrinking — we only expand when we find a better maxFreq.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1) - only 26 characters.
 */
class LongestRepeatingCharacterReplacement {

    public static int characterReplacement(String s, int k) {
        int[] freq = new int[26];
        int left = 0;
        int maxFreq = 0; // max frequency of any character in the current window
        int maxLength = 0;

        for (int right = 0; right < s.length(); right++) {
            freq[s.charAt(right) - 'A']++;
            maxFreq = Math.max(maxFreq, freq[s.charAt(right) - 'A']);

            // If replacements needed exceed k, shrink window
            int windowSize = right - left + 1;
            if (windowSize - maxFreq > k) {
                freq[s.charAt(left++) - 'A']--;
            }

            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }

    public static void main(String[] args) {
        System.out.println(characterReplacement("ABAB", 2) + " (Expected: 4)");
        // Replace both A's or both B's -> "BBBB" or "AAAA", length 4
        System.out.println(characterReplacement("AABABBA", 1) + " (Expected: 4)");
        // "AABA" -> replace one B: "AAAA", length 4
    }
}

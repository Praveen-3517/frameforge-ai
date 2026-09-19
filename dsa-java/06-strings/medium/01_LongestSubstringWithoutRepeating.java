import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 * Given a string `s`, find the length of the longest substring without repeating characters.
 * (LeetCode 3: Longest Substring Without Repeating Characters).
 *
 * Example:
 * s = "abcabcbb" -> 3 ("abc")
 * s = "bbbbb"    -> 1 ("b")
 * s = "pwwkew"   -> 3 ("wke")
 *
 * Asked in: Amazon, Microsoft, Google, Facebook / Meta, Bloomberg (Top 3 Most Asked)
 *
 * Approach:
 * - Optimized Sliding Window with Last-Seen Index Map:
 *   Maintain `left` pointer of window and `maxLen`.
 *   - For each character at index `right`:
 *     If `s[right]` was seen previously at `prevIdx >= left`:
 *       Jump `left = prevIdx + 1` directly, bypassing all redundant sub-windows!
 *     Record character position: `map.put(s.charAt(right), right)`.
 *     Update `maxLen = Math.max(maxLen, right - left + 1)`.
 * - Time: O(N), Space: O(min(N, AlphabetSize)).
 */
class LongestSubstringWithoutRepeating {

    public static int lengthOfLongestSubstring(String s) {
        if (s == null || s.isEmpty()) return 0;

        // Map character -> last seen index
        Map<Character, Integer> lastSeen = new HashMap<>();
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < s.length(); right++) {
            char ch = s.charAt(right);

            if (lastSeen.containsKey(ch)) {
                // Advance left pointer to the right of the duplicate character
                left = Math.max(left, lastSeen.get(ch) + 1);
            }

            lastSeen.put(ch, right);
            maxLen = Math.max(maxLen, right - left + 1);
        }

        return maxLen;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 3: Longest Substring Without Repeating Characters ===");

        String[] testCases = { "abcabcbb", "bbbbb", "pwwkew", "", "dvdf", "abba" };

        for (String str : testCases) {
            int len = lengthOfLongestSubstring(str);
            System.out.printf("String: %-12s ==> Max Unique Substring Length: %d%n",
                    "\"" + str + "\"", len);
        }
    }
}

/*
 * Time Complexity: O(N) - Right pointer scans each character once.
 * Space Complexity: O(min(N, Sigma)) - Map stores unique characters in current window.
 */

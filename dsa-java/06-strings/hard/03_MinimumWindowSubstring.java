/**
 * Problem Statement:
 * Given two strings `s` and `t` of lengths `m` and `n` respectively, return the minimum window substring
 * of `s` such that every character in `t` (including duplicates) is included in the window.
 * If there is no such substring, return the empty string "".
 * (LeetCode 76: Minimum Window Substring - Hard).
 *
 * Example:
 * s = "ADOBECODEBANC", t = "ABC" -> Output: "BANC"
 * s = "a", t = "a"               -> Output: "a"
 * s = "a", t = "aa"              -> Output: ""
 *
 * Asked in: Facebook / Meta (High Frequency), Google, Amazon, LinkedIn
 *
 * Approach:
 * - Dynamic Sliding Window with Frequency Counting (O(N) Time, O(1) Space):
 *   1. Count target character requirements in `int[] targetFreq = new int[128]`.
 *      Count how many unique characters must be matched: `required = uniqueCount`.
 *   2. Expand `right` pointer over `s`:
 *      Increment `windowFreq[s.charAt(right)]++`.
 *      If count matches requirement: `formed++`.
 *   3. While `formed == required` (all characters in t are satisfied):
 *      - Record new minimum window `[left, right]`.
 *      - Shrink window from `left`:
 *        Decrement `windowFreq[s.charAt(left)]--`.
 *        If count drops below `targetFreq[s.charAt(left)]`: `formed--`.
 *        Advance `left++`.
 *   4. Return minimum substring if found, else `""`.
 */
class MinimumWindowSubstring {

    public static String minWindow(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) return "";

        int[] targetFreq = new int[128];
        int required = 0;

        for (int i = 0; i < t.length(); i++) {
            char c = t.charAt(i);
            if (targetFreq[c] == 0) required++;
            targetFreq[c]++;
        }

        int[] windowFreq = new int[128];
        int formed = 0;
        int left = 0;

        int minLen = Integer.MAX_VALUE;
        int minStart = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            windowFreq[c]++;

            if (targetFreq[c] > 0 && windowFreq[c] == targetFreq[c]) {
                formed++;
            }

            // Shrink window while all requirements are met
            while (formed == required) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minStart = left;
                }

                char leftChar = s.charAt(left);
                windowFreq[leftChar]--;
                if (targetFreq[leftChar] > 0 && windowFreq[leftChar] < targetFreq[leftChar]) {
                    formed--;
                }
                left++;
            }
        }

        return (minLen == Integer.MAX_VALUE) ? "" : s.substring(minStart, minStart + minLen);
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 76: Minimum Window Substring (Sliding Window) ===");

        String s = "ADOBECODEBANC";
        String t = "ABC";
        String window = minWindow(s, t);

        System.out.printf("s: \"%s\"%nt: \"%s\"%nMinimum Window Substring: \"%s\" (Expected: \"BANC\")%n",
                s, t, window);
    }
}

/*
 * Time Complexity: O(M + N) - Each character in s is visited at most twice (by left and right pointers).
 * Space Complexity: O(1) - Fixed 128-element ASCII arrays.
 */

/**
 * Problem Statement:
 * Given a string `s`, return the longest palindromic substring in `s`.
 * (LeetCode 5: Longest Palindromic Substring).
 *
 * Example:
 * s = "babad" -> "bab" (or "aba")
 * s = "cbbd"  -> "bb"
 *
 * Asked in: Amazon, Microsoft, Facebook / Meta, Google, Apple
 *
 * Approach:
 * - Expand Around Center (O(N^2) Time, O(1) Space):
 *   A palindrome mirrors around its center. There are 2N - 1 potential centers in a string of length N:
 *   - N single-character centers (odd-length palindromes, e.g. "aba" centered at 'b').
 *   - N - 1 two-character centers (even-length palindromes, e.g. "abba" centered between 'b' and 'b').
 *   For each index `i`:
 *   - Expand around odd center `(i, i)`
 *   - Expand around even center `(i, i + 1)`
 *   - Update global maximum substring coordinates `[start, start + maxLen]`.
 */
class LongestPalindromicSubstringExpand {

    public static String longestPalindrome(String s) {
        if (s == null || s.length() < 2) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < s.length(); i++) {
            // Odd length palindrome
            int len1 = expandAroundCenter(s, i, i);
            // Even length palindrome
            int len2 = expandAroundCenter(s, i, i + 1);

            int len = Math.max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                // Calculate starting index of the palindrome
                start = i - (len - 1) / 2;
            }
        }

        return s.substring(start, start + maxLen);
    }

    private static int expandAroundCenter(String s, int left, int right) {
        while (left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
            left--;
            right++;
        }
        // When loop exits, s[left] != s[right]. Valid palindrome was s[left+1 .. right-1]
        // Length = (right - 1) - (left + 1) + 1 = right - left - 1
        return right - left - 1;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 5: Longest Palindromic Substring (Expand Around Center) ===");

        String[] testStrings = { "babad", "cbbd", "a", "ac", "racecar", "forgeeksskeegfor" };

        for (String str : testStrings) {
            String lps = longestPalindrome(str);
            System.out.printf("String: %-20s ==> Longest Palindrome: \"%s\"%n",
                    "\"" + str + "\"", lps);
        }
    }
}

/*
 * Time Complexity: O(N^2) - 2N centers expanded outwards.
 * Space Complexity: O(1) - Constant stack pointers.
 */

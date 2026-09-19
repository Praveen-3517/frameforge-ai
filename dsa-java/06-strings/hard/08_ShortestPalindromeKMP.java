/**
 * Problem Statement:
 * You are given a string `s`. You can convert `s` to a palindrome by adding characters in front of it.
 * Return the shortest palindrome you can find by performing this transformation.
 * (LeetCode 214: Shortest Palindrome - Hard).
 *
 * Example:
 * s = "aacecaaa" -> Output: "aaacecaaa"
 * s = "abcd"     -> Output: "dcbabcd"
 *
 * Asked in: Google, Amazon, Microsoft, Apple
 *
 * Approach:
 * - KMP LPS Array on Mirrored String (O(N) Time, O(N) Space):
 *   To minimize added characters in front, we must find the LONGEST PALINDROMIC PREFIX of `s`.
 *   Any characters remaining after this prefix must be reversed and prepended in front.
 *   - Construct a combined string:
 *     `temp = s + '#' + reverse(s)`
 *     (The sentinel '#' ensures the prefix does not match across the boundary into the reverse part).
 *   - Compute the KMP LPS (Longest Proper Prefix which is also Suffix) array for `temp`.
 *   - The last element `lps[temp.length() - 1]` gives the exact length of the longest prefix of `s`
 *     that is simultaneously a suffix of `reverse(s)`.
 *     This length `L` is precisely the length of the longest palindromic prefix of `s`!
 *   - The non-palindromic suffix is `s.substring(L)`.
 *   - Final Answer: `new StringBuilder(suffix).reverse().toString() + s`.
 */
class ShortestPalindromeKMP {

    public static String shortestPalindrome(String s) {
        if (s == null || s.length() <= 1) return s;

        String rev = new StringBuilder(s).reverse().toString();
        String combined = s + "#" + rev;

        // Compute LPS array for combined string
        int m = combined.length();
        int[] lps = new int[m];
        int len = 0;
        int i = 1;

        while (i < m) {
            if (combined.charAt(i) == combined.charAt(len)) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        // Length of the longest palindromic prefix of s
        int palPrefixLen = lps[m - 1];

        // The remaining suffix must be reversed and prepended
        String nonPalSuffix = s.substring(palPrefixLen);
        String prefixToPrepend = new StringBuilder(nonPalSuffix).reverse().toString();

        return prefixToPrepend + s;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 214: Shortest Palindrome (KMP LPS Prefix Mirror) ===");

        String[] testStrings = { "aacecaaa", "abcd", "racecar", "banana", "a" };

        for (String str : testStrings) {
            String sp = shortestPalindrome(str);
            System.out.printf("Input: %-10s ==> Shortest Palindrome: \"%s\"%n",
                    "\"" + str + "\"", sp);
        }
    }
}

/*
 * Time Complexity: O(N) - Linear pass for LPS computation on string of length 2N + 1.
 * Space Complexity: O(N) - Storage for mirrored string and LPS array.
 */

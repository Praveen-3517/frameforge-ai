/**
 * Problem Statement:
 * Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle`
 * in `haystack`, or -1 if `needle` is not part of `haystack`.
 * Implement the Knuth-Morris-Pratt (KMP) linear-time string matching algorithm.
 * (LeetCode 28: Find the Index of the First Occurrence in a String).
 *
 * Example:
 * haystack = "sadbutsad", needle = "sad" -> 0
 * haystack = "leetcode", needle = "leeto"  -> -1
 *
 * Asked in: Google, Microsoft, Amazon, Facebook / Meta
 *
 * Approach:
 * - Knuth-Morris-Pratt (KMP) Algorithm (O(N + M) Time, O(M) Space):
 *   Avoids the naive O(N * M) backtrack by utilizing previous match information.
 *   1. Step 1: Precompute the LPS (Longest Proper Prefix which is also Suffix) array for `needle`:
 *      `lps[i]` is the length of the longest proper prefix of `needle[0..i]` that is also a suffix of `needle[0..i]`.
 *   2. Step 2: Search `haystack` using two pointers `i` (for haystack) and `j` (for needle):
 *      - If `haystack[i] == needle[j]`: increment both `i++` and `j++`.
 *      - If `j == needle.length()`: Full match found! Return `i - j`.
 *      - If mismatch occurs (`haystack[i] != needle[j]`):
 *        - If `j != 0`: Fall back `j = lps[j - 1]` without rewinding `i`!
 *        - If `j == 0`: Increment `i++`.
 */
class KMPStringMatchingAlgorithm {

    // Precompute Longest Prefix-Suffix (LPS) Array
    public static int[] buildLPS(String pattern) {
        int m = pattern.length();
        int[] lps = new int[m];
        int len = 0; // Length of previous longest prefix suffix
        int i = 1;

        while (i < m) {
            if (pattern.charAt(i) == pattern.charAt(len)) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1]; // Fallback to shorter prefix
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

    public static int strStr(String haystack, String needle) {
        if (needle == null || needle.isEmpty()) return 0;
        if (haystack == null || haystack.length() < needle.length()) return -1;

        int n = haystack.length();
        int m = needle.length();
        int[] lps = buildLPS(needle);

        int i = 0; // Pointer for haystack
        int j = 0; // Pointer for needle

        while (i < n) {
            if (haystack.charAt(i) == needle.charAt(j)) {
                i++;
                j++;
            }

            if (j == m) {
                return i - j; // Match found at index i - j
            } else if (i < n && haystack.charAt(i) != needle.charAt(j)) {
                if (j != 0) {
                    j = lps[j - 1]; // Shift needle using LPS
                } else {
                    i++;
                }
            }
        }

        return -1; // Needle not found
    }

    public static void main(String[] args) {
        System.out.println("=== Knuth-Morris-Pratt (KMP) Substring Search ===");

        String haystack1 = "ABABDABACDABABCABAB";
        String needle1 = "ABABCABAB";
        System.out.printf("Haystack: %s%nNeedle  : %s%nFirst Match Index: %d (Expected: 10)%n%n",
                haystack1, needle1, strStr(haystack1, needle1));

        String haystack2 = "sadbutsad";
        String needle2 = "sad";
        System.out.printf("Haystack: %s%nNeedle  : %s%nFirst Match Index: %d (Expected: 0)%n",
                haystack2, needle2, strStr(haystack2, needle2));
    }
}

/*
 * Time Complexity: O(N + M) where N = haystack.length(), M = needle.length().
 * Space Complexity: O(M) - Storage for the LPS array.
 */

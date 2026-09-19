/**
 * Problem Statement:
 * Given a string `s`, return the longest palindromic substring in `s`.
 * Implement Manacher's Algorithm to achieve strictly linear O(N) runtime complexity.
 * (LeetCode 5: Longest Palindromic Substring - Optimal O(N)).
 *
 * Example:
 * s = "babad" -> "bab"
 * s = "forgeeksskeegfor" -> "geeksskeeg"
 *
 * Asked in: Google, Uber, ByteDance, TopCoder
 *
 * Approach:
 * - Manacher's Algorithm (Strictly O(N) Time and Space):
 *   1. Transform `s` into `T` by inserting sentinel characters `#` between characters:
 *      "aba" -> "^#a#b#a#$"
 *      Sentinels eliminate the distinction between odd and even-length palindromes,
 *      and start/end sentinels ('^' and '$') prevent index out-of-bounds checks!
 *   2. Array `P[i]`: Stores the palindrome radius centered at index `i` in `T`.
 *   3. Maintain center `C` and right boundary `R` of the palindrome that reaches farthest right:
 *      For current index `i`:
 *      - Mirror of `i` around `C`: `iMirror = 2 * C - i`.
 *      - If `i < R`: We can initialize `P[i] = Math.min(R - i, P[iMirror])` using pre-calculated symmetry!
 *      - Expand outward: while `T[i + 1 + P[i]] == T[i - 1 - P[i]]`, increment `P[i]++`.
 *      - If expansion exceeds `R`: update `C = i` and `R = i + P[i]`.
 *   4. Track the maximum radius in `P` and map back to original indices in `s`.
 */
class ManachersLongestPalindrome {

    public static String longestPalindromeManacher(String s) {
        if (s == null || s.length() < 2) return s;

        // Step 1: Preprocess string to eliminate even/odd distinctions
        StringBuilder t = new StringBuilder("^");
        for (int i = 0; i < s.length(); i++) {
            t.append("#").append(s.charAt(i));
        }
        t.append("#$");

        char[] T = t.toString().toCharArray();
        int n = T.length;
        int[] P = new int[n]; // Palindrome radius array
        int C = 0, R = 0;     // Current center and right boundary

        int maxLen = 0;
        int centerIndex = 0;

        for (int i = 1; i < n - 1; i++) {
            int iMirror = 2 * C - i;

            if (i < R) {
                P[i] = Math.min(R - i, P[iMirror]);
            }

            // Expand around center i
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            // Update right boundary
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }

            // Track maximum
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        // Map back to original string indices
        int start = (centerIndex - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    public static void main(String[] args) {
        System.out.println("=== Manacher's Algorithm: O(N) Longest Palindromic Substring ===");

        String[] testStrings = {
            "babad",
            "cbbd",
            "forgeeksskeegfor",
            "racecar",
            "abacdfgdcaba",
            "bananas"
        };

        for (String str : testStrings) {
            String lps = longestPalindromeManacher(str);
            System.out.printf("String: %-20s ==> Longest Palindrome: \"%s\"%n",
                    "\"" + str + "\"", lps);
        }
    }
}

/*
 * Time Complexity: O(N) - The while loop only expands when i + P[i] extends beyond R.
 * Space Complexity: O(N) - Preprocessed character array and radius array.
 */

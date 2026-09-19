/**
 * Problem Statement:
 * Given an input string `s` and a pattern `p`, implement regular expression matching with support
 * for '.' and '*' where:
 *   - '.' Matches any single character.
 *   - '*' Matches zero or more of the PRECEDING element.
 * The matching should cover the entire input string (not partial).
 * (LeetCode 10: Regular Expression Matching - Hard).
 *
 * Example:
 * s = "aa", p = "a"   -> false
 * s = "aa", p = "a*"  -> true
 * s = "ab", p = ".*"  -> true
 *
 * Asked in: Google, Facebook / Meta, Amazon, Microsoft, Apple
 *
 * Approach:
 * - 2D Dynamic Programming (O(M * N) Time & Space):
 *   `dp[i][j]` represents whether `s[0..i-1]` matches `p[0..j-1]`.
 *   - Base Case: `dp[0][0] = true` (empty string matches empty pattern).
 *   - Patterns matching empty string:
 *     For `j` from 2 to n: if `p[j-1] == '*'`: `dp[0][j] = dp[0][j - 2]` (e.g. "a*", "a*b*").
 *   - Transitions:
 *     - If `p[j-1] == '.' || p[j-1] == s[i-1]`:
 *       `dp[i][j] = dp[i - 1][j - 1]`
 *     - If `p[j-1] == '*'`:
 *       1. Zero occurrences of preceding char `p[j-2]`:
 *          `dp[i][j] = dp[i][j - 2]`
 *       2. One or more occurrences of preceding char:
 *          If `p[j-2] == '.' || p[j-2] == s[i-1]`:
 *            `dp[i][j] = dp[i][j] || dp[i - 1][j]`
 */
class RegularExpressionMatchingDP {

    public static boolean isMatch(String s, String p) {
        int m = s.length();
        int n = p.length();
        boolean[][] dp = new boolean[m + 1][n + 1];

        dp[0][0] = true;

        // Deal with patterns with '*' matching empty string s
        for (int j = 2; j <= n; j++) {
            if (p.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sc = s.charAt(i - 1);
                char pc = p.charAt(j - 1);

                if (pc == '.' || pc == sc) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (pc == '*') {
                    // Option 1: 0 occurrences of preceding char
                    dp[i][j] = dp[i][j - 2];

                    // Option 2: 1 or more occurrences
                    char prevChar = p.charAt(j - 2);
                    if (prevChar == '.' || prevChar == sc) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 10: Regular Expression Matching (2D DP) ===");

        String[][] testCases = {
            { "aa", "a" },
            { "aa", "a*" },
            { "ab", ".*" },
            { "aab", "c*a*b" },
            { "mississippi", "mis*is*p*." }
        };

        for (String[] tc : testCases) {
            boolean match = isMatch(tc[0], tc[1]);
            System.out.printf("s: %-15s | p: %-15s ==> Match: %s%n",
                    "\"" + tc[0] + "\"", "\"" + tc[1] + "\"", match);
        }
    }
}

/*
 * Time Complexity: O(M * N) - Computes each cell in the (M+1) x (N+1) DP matrix once.
 * Space Complexity: O(M * N) - DP state table.
 */

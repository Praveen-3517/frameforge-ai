/**
 * Problem: Regular Expression Matching (LeetCode 10)
 * Asked in: Facebook, Google, Amazon, Microsoft
 * 
 * Given an input string s and a pattern p, implement regular expression matching with
 * support for '.' and '*' where:
 * - '.' Matches any single character.
 * - '*' Matches zero or more of the preceding element.
 * 
 * Approach:
 * 2D Dynamic Programming:
 * Let dp[i][j] be true if s[0..i-1] matches p[0..j-1].
 * - Base case: dp[0][0] = true.
 * - Empty string matches pattern if pattern has '*' canceling preceding character:
 *   dp[0][j] = dp[0][j - 2] if p[j - 1] == '*'.
 * - Transitions:
 *   - If p[j - 1] == s[i - 1] or p[j - 1] == '.':
 *     dp[i][j] = dp[i - 1][j - 1]
 *   - If p[j - 1] == '*':
 *     - 0 occurrences of preceding char: dp[i][j] = dp[i][j - 2]
 *     - 1 or more occurrences (if preceding char matches s[i-1]):
 *       dp[i][j] = dp[i][j] || dp[i - 1][j]
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */
class RegularExpressionMatchingDP {

    public static boolean isMatch(String s, String p) {
        int m = s.length();
        int n = p.length();
        boolean[][] dp = new boolean[m + 1][n + 1];

        dp[0][0] = true;

        // Handles patterns like a*, a*b*, a*b*c* matching empty string
        for (int j = 2; j <= n; j++) {
            if (p.charAt(j - 1) == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                char sc = s.charAt(i - 1);
                char pc = p.charAt(j - 1);

                if (pc == sc || pc == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (pc == '*') {
                    // 0 instances of preceding character
                    dp[i][j] = dp[i][j - 2];

                    char prevChar = p.charAt(j - 2);
                    if (prevChar == sc || prevChar == '.') {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }

        return dp[m][n];
    }

    public static void main(String[] args) {
        System.out.println("Match 'aa' with 'a': " + isMatch("aa", "a") + " (Expected: false)");
        System.out.println("Match 'aa' with 'a*': " + isMatch("aa", "a*") + " (Expected: true)");
        System.out.println("Match 'ab' with '.*': " + isMatch("ab", ".*") + " (Expected: true)");
        System.out.println("Match 'aab' with 'c*a*b': " + isMatch("aab", "c*a*b") + " (Expected: true)");
    }
}

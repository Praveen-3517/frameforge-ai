/**
 * Problem: Longest Common Subsequence (LeetCode 1143)
 * Asked in: Amazon, Microsoft, Google, Bloomberg
 * 
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 * If there is no common subsequence, return 0.
 * 
 * Approach:
 * 2D Dynamic Programming:
 * Let dp[i][j] be LCS length of text1[0..i-1] and text2[0..j-1].
 * - If text1[i-1] == text2[j-1]:
 *     dp[i][j] = 1 + dp[i-1][j-1]
 * - Else:
 *     dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 * 
 * Time Complexity: O(M * N) where M = text1.length(), N = text2.length().
 * Space Complexity: O(M * N) (or O(min(M, N)) with space optimization).
 */
class LongestCommonSubsequence {

    public static int longestCommonSubsequence(String text1, String text2) {
        int m = text1.length();
        int n = text2.length();
        int[][] dp = new int[m + 1][n + 1];

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1.charAt(i - 1) == text2.charAt(j - 1)) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }

    public static void main(String[] args) {
        System.out.println("LCS('abcde', 'ace'): " + longestCommonSubsequence("abcde", "ace") + " (Expected: 3)");
        System.out.println("LCS('abc', 'abc'): " + longestCommonSubsequence("abc", "abc") + " (Expected: 3)");
        System.out.println("LCS('abc', 'def'): " + longestCommonSubsequence("abc", "def") + " (Expected: 0)");
    }
}

/**
 * Problem: Edit Distance / Levenshtein Distance (LeetCode 72)
 * Asked in: Google, Amazon, Microsoft, Facebook
 * 
 * Given two strings word1 and word2, return the minimum number of operations required
 * to convert word1 to word2.
 * You have the following three operations permitted on a word:
 * 1. Insert a character
 * 2. Delete a character
 * 3. Replace a character
 * 
 * Approach:
 * 2D Dynamic Programming:
 * dp[i][j] represents min edit distance between word1[0..i-1] and word2[0..j-1].
 * - If word1[i-1] == word2[j-1]: dp[i][j] = dp[i-1][j-1]
 * - Else: dp[i][j] = 1 + min(
 *       dp[i][j-1],    // Insert
 *       dp[i-1][j],    // Delete
 *       dp[i-1][j-1]   // Replace
 *   )
 * 
 * Time Complexity: O(M * N) where M = word1.length(), N = word2.length().
 * Space Complexity: O(M * N)
 */
class EditDistanceLevenshtein {

    public static int minDistance(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();
        int[][] dp = new int[m + 1][n + 1];

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i - 1) == word2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + Math.min(dp[i - 1][j - 1], // Replace
                                    Math.min(dp[i - 1][j],   // Delete
                                             dp[i][j - 1])); // Insert
                }
            }
        }

        return dp[m][n];
    }

    public static void main(String[] args) {
        System.out.println("horse -> ros: " + minDistance("horse", "ros") + " (Expected: 3)");
        System.out.println("intention -> execution: " + minDistance("intention", "execution") + " (Expected: 5)");
    }
}

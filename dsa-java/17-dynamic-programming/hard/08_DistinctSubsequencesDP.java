/**
 * Problem: Distinct Subsequences (LeetCode 115)
 * Asked in: Google, Amazon, Facebook
 * 
 * Given two strings s and t, return the number of distinct subsequences of s which equals t.
 * 
 * Approach:
 * 1D Space-Optimized Dynamic Programming:
 * Let dp[j] be the number of distinct subsequences of s prefix that equal t[0..j-1].
 * - Base case: dp[0] = 1 (empty string t is formed by 1 subsequence: the empty one).
 * - For each character sChar in s:
 *   - Iterate backwards j from t.length() down to 1:
 *     - If sChar == t[j - 1]:
 *       dp[j] += dp[j - 1]
 * 
 * Time Complexity: O(M * N) where M = s.length(), N = t.length().
 * Space Complexity: O(N) using 1D array.
 */
class DistinctSubsequencesDP {

    public static int numDistinct(String s, String t) {
        int m = s.length();
        int n = t.length();
        int[] dp = new int[n + 1];

        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            char sc = s.charAt(i);
            for (int j = n; j >= 1; j--) {
                if (sc == t.charAt(j - 1)) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[n];
    }

    public static void main(String[] args) {
        System.out.println("Distinct 'rabbbit', 'rabbit': " + numDistinct("rabbbit", "rabbit") + " (Expected: 3)");
        System.out.println("Distinct 'babgbag', 'bag': " + numDistinct("babgbag", "bag") + " (Expected: 5)");
    }
}

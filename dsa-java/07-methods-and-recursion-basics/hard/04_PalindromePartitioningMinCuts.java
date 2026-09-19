/*
 * Problem Statement:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * Example:
 * Input: s = "aab"
 * Output: 1 (Partition ["aa", "b"] requires 1 cut)
 * 
 * Example 2:
 * Input: s = "a"
 * Output: 0
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 */

import java.util.Arrays;

class PalindromePartitioningMinCuts {

    /**
     * Approach:
     * Memoized Recursion:
     * Let minCuts(i) be the minimum cuts required for substring s[i...n-1].
     * Base case: if i == n, return 0 cuts.
     * For every j from i to n - 1:
     *   if s[i...j] is palindrome:
     *     cuts = 1 + minCuts(j + 1)
     * Result is minCuts(0) - 1 (since k pieces need k - 1 cuts).
     */
    public static int minCut(String s) {
        int n = s.length();
        // Precompute palindrome table for O(1) checks
        boolean[][] isPal = new boolean[n][n];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s.charAt(i) == s.charAt(j) && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }

        int[] memo = new int[n];
        Arrays.fill(memo, -1);
        return solve(0, s, isPal, memo) - 1;
    }

    private static int solve(int i, String s, boolean[][] isPal, int[] memo) {
        if (i == s.length()) return 0;
        if (memo[i] != -1) return memo[i];

        int minCost = Integer.MAX_VALUE;
        for (int j = i; j < s.length(); j++) {
            if (isPal[i][j]) {
                int cost = 1 + solve(j + 1, s, isPal, memo);
                minCost = Math.min(minCost, cost);
            }
        }
        return memo[i] = minCost;
    }

    public static void main(String[] args) {
        String[] testStrings = {"aab", "a", "ab", "racecar", "ababbbabbababa"};

        System.out.println("--- Minimum Palindrome Partitioning Cuts ---");
        for (String s : testStrings) {
            System.out.printf("s = %-16s -> Min cuts: %d%n", "\"" + s + "\"", minCut(s));
        }
    }
}

/*
 * Time Complexity: O(N^2) - Subproblem states N, each transitions up to N times.
 * Space Complexity: O(N^2) for palindrome lookup table and O(N) recursion stack.
 */

/**
 * Problem: Palindrome Partitioning II (LeetCode 132)
 * Asked in: Amazon, Google, Facebook, Microsoft
 * 
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * Approach:
 * 1. Precompute Palindromic Substrings:
 *    isPal[i][j] is true if s[i..j] is a palindrome:
 *    isPal[i][j] = (s[i] == s[j]) && (j - i <= 2 || isPal[i + 1][j - 1]).
 * 2. 1D DP for Minimum Cuts:
 *    Let cuts[i] be the minimum cuts needed for prefix s[0..i].
 *    - If isPal[0][i] is true: cuts[i] = 0 (no cuts needed!).
 *    - Otherwise, cuts[i] = min_{0 <= j < i and isPal[j + 1][i]} (cuts[j] + 1).
 * 
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2) for palindrome table and cuts array.
 */
class PalindromePartitioningTwoMinCuts {

    public static int minCut(String s) {
        int n = s.length();
        boolean[][] isPal = new boolean[n][n];

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s.charAt(i) == s.charAt(j) && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }

        int[] cuts = new int[n];
        for (int i = 0; i < n; i++) {
            if (isPal[0][i]) {
                cuts[i] = 0;
            } else {
                cuts[i] = i; // worst case: cut every character
                for (int j = 0; j < i; j++) {
                    if (isPal[j + 1][i]) {
                        cuts[i] = Math.min(cuts[i], cuts[j] + 1);
                    }
                }
            }
        }

        return cuts[n - 1];
    }

    public static void main(String[] args) {
        System.out.println("Min cuts for 'aab': " + minCut("aab") + " (Expected: 1)"); // "aa" | "b"
        System.out.println("Min cuts for 'a': " + minCut("a") + " (Expected: 0)");
        System.out.println("Min cuts for 'ab': " + minCut("ab") + " (Expected: 1)");
    }
}

import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Problem: Word Break (LeetCode 139)
 * Asked in: Facebook, Amazon, Google, Bloomberg, Apple
 * 
 * Given a string s and a dictionary of strings wordDict, return true if s can be
 * segmented into a space-separated sequence of one or more dictionary words.
 * 
 * Approach:
 * 1D Dynamic Programming:
 * Let dp[i] be true if prefix s[0..i-1] can be segmented using dictionary words.
 * - Base case: dp[0] = true (empty string).
 * - For i from 1 to s.length():
 *   - For j from 0 to i - 1:
 *     - If dp[j] is true and wordDict contains s.substring(j, i):
 *       dp[i] = true, break.
 * 
 * Time Complexity: O(N^2 * L) where N is s.length() and L is max word length.
 * Space Complexity: O(N) for DP array + O(Dict) for HashSet.
 */
class WordBreakDP {

    public static boolean wordBreak(String s, List<String> wordDict) {
        Set<String> wordSet = new HashSet<>(wordDict);
        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordSet.contains(s.substring(j, i))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }

    public static void main(String[] args) {
        System.out.println("leetcode: " + wordBreak("leetcode", Arrays.asList("leet", "code")) + " (Expected: true)");
        System.out.println("applepenapple: " + wordBreak("applepenapple", Arrays.asList("apple", "pen")) + " (Expected: true)");
        System.out.println("catsandog: " + wordBreak("catsandog", Arrays.asList("cats", "dog", "sand", "and", "cat")) + " (Expected: false)");
    }
}

/**
 * Problem: Burst Balloons (LeetCode 312)
 * Asked in: Google, Amazon, Microsoft, ByteDance
 * 
 * You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it.
 * You are asked to burst all the balloons. If you burst balloon i, you get nums[i - 1] * nums[i] * nums[i + 1] coins.
 * If i - 1 or i + 1 goes out of bounds, treat it as a balloon with 1 painted on it.
 * Return the maximum coins you can collect.
 * 
 * Approach:
 * Reverse Thinking + Interval / MCM Dynamic Programming:
 * Instead of asking which balloon to burst FIRST (which creates dependent disjoint subproblems),
 * ask which balloon k is the LAST to burst in open range (left, right)!
 * If balloon k is the last to burst in (left, right), its neighbors at that moment will be
 * left and right!
 * State Transition:
 * dp[left][right] = max_{k in (left, right)} (
 *     nums[left] * nums[k] * nums[right] + dp[left][k] + dp[k][right]
 * )
 * 
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2)
 */
class BurstBalloonsMCMIntervalDP {

    public static int maxCoins(int[] nums) {
        int n = nums.length;
        // Pad with 1 at both boundaries
        int[] arr = new int[n + 2];
        arr[0] = 1;
        arr[n + 1] = 1;
        System.arraycopy(nums, 0, arr, 1, n);

        int m = arr.length;
        int[][] dp = new int[m][m];

        // length is window size between left and right (at least 2 to have elements inside)
        for (int len = 2; len < m; len++) {
            for (int left = 0; left < m - len; left++) {
                int right = left + len;

                for (int k = left + 1; k < right; k++) {
                    int coins = arr[left] * arr[k] * arr[right] + dp[left][k] + dp[k][right];
                    dp[left][right] = Math.max(dp[left][right], coins);
                }
            }
        }

        return dp[0][m - 1];
    }

    public static void main(String[] args) {
        int[] nums1 = {3, 1, 5, 8};
        System.out.println("Max coins 1: " + maxCoins(nums1) + " (Expected: 167)");

        int[] nums2 = {1, 5};
        System.out.println("Max coins 2: " + maxCoins(nums2) + " (Expected: 10)");
    }
}

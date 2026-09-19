/**
 * Problem: House Robber (LeetCode 198)
 * Asked in: Amazon, Google, Microsoft, Facebook, Apple
 * 
 * You are a professional robber planning to rob houses along a street. Each house has a
 * certain amount of money stashed. Adjacent houses have security systems connected that
 * will automatically contact the police if two adjacent houses were broken into on the same night.
 * Given an integer array nums representing the amount of money of each house, return the
 * maximum amount of money you can rob tonight without alerting the police.
 * 
 * Approach:
 * Linear 1D DP:
 * At house i:
 * - Option 1: Rob house i -> profit = nums[i] + rob(i - 2)
 * - Option 2: Skip house i -> profit = rob(i - 1)
 * dp[i] = max(dp[i - 1], nums[i] + dp[i - 2])
 * Space optimized to O(1) using two variables.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class HouseRobberOneLinear {

    public static int rob(int[] nums) {
        if (nums == null || nums.length == 0) return 0;
        if (nums.length == 1) return nums[0];

        int prev2 = 0;
        int prev1 = 0;

        for (int num : nums) {
            int curr = Math.max(prev1, num + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 3, 1};
        System.out.println("Max loot 1: " + rob(nums1) + " (Expected: 4)");

        int[] nums2 = {2, 7, 9, 3, 1};
        System.out.println("Max loot 2: " + rob(nums2) + " (Expected: 12)");
    }
}

/**
 * Problem: Target Sum (LeetCode 494)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * You are given an integer array nums and an integer target.
 * You want to build an expression out of nums by adding one of the symbols '+' and '-'
 * before each integer in nums and then concatenate all the integers.
 * Return the number of different expressions that you can build, which evaluates to target.
 * 
 * Approach:
 * Mathematical Reduction to Subset Sum (0/1 Knapsack):
 * Let P = subset of positive elements, N = subset of negative elements.
 * P - N = target
 * P + N = totalSum
 * Adding equations: 2P = target + totalSum  =>  P = (target + totalSum) / 2
 * Problem reduces to finding number of subsets with sum P!
 * Constraints: (target + totalSum) must be non-negative and even.
 * 
 * Time Complexity: O(N * P) where P = (target + totalSum) / 2.
 * Space Complexity: O(P) using 1D DP array.
 */
class TargetSumDP {

    public static int findTargetSumWays(int[] nums, int target) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;

        // Valid subset check
        if (Math.abs(target) > totalSum || (target + totalSum) % 2 != 0) {
            return 0;
        }

        int subsetSum = (target + totalSum) / 2;
        int[] dp = new int[subsetSum + 1];
        dp[0] = 1; // One way to make sum 0 (empty subset)

        for (int num : nums) {
            for (int j = subsetSum; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }

        return dp[subsetSum];
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 1, 1, 1, 1};
        System.out.println("Ways for target 3: " + findTargetSumWays(nums1, 3) + " (Expected: 5)");

        int[] nums2 = {1};
        System.out.println("Ways for target 1: " + findTargetSumWays(nums2, 1) + " (Expected: 1)");
    }
}

/**
 * Problem: Partition Equal Subset Sum (LeetCode 416)
 * Asked in: Facebook, Amazon, Microsoft, Uber
 * 
 * Given an integer array nums, return true if you can partition the array into two subsets
 * such that the sum of the elements in both subsets is equal or false otherwise.
 * 
 * Approach:
 * 0/1 Knapsack / Subset Sum DP:
 * 1. Compute total sum S. If S is odd, return false (cannot partition into two equal integers).
 * 2. Target sum T = S / 2.
 * 3. Use 1D boolean array dp of size T + 1:
 *    - dp[0] = true (0 sum is always achievable).
 *    - For each num in nums:
 *      - Iterate backwards j from T down to num:
 *        dp[j] = dp[j] || dp[j - num]
 * 4. Return dp[T].
 * 
 * Time Complexity: O(N * Target) = O(N * S / 2)
 * Space Complexity: O(Target) = O(S / 2)
 */
class PartitionEqualSubsetSum {

    public static boolean canPartition(int[] nums) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;

        if (totalSum % 2 != 0) return false;

        int target = totalSum / 2;
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;

        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 5, 11, 5};
        System.out.println("Can partition [1, 5, 11, 5]: " + canPartition(nums1) + " (Expected: true)");

        int[] nums2 = {1, 2, 3, 5};
        System.out.println("Can partition [1, 2, 3, 5]: " + canPartition(nums2) + " (Expected: false)");
    }
}

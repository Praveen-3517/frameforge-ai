/**
 * Problem: Maximum Subarray / Kadane's Algorithm (LeetCode 53)
 * Asked in: Amazon, Microsoft, Apple, Google, Bloomberg
 * 
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 * 
 * Approach:
 * Kadane's Algorithm (1D DP):
 * Let dp[i] be the maximum subarray sum ending at index i.
 * Transition:
 * dp[i] = max(nums[i], nums[i] + dp[i - 1])
 * Either start a fresh subarray at nums[i], or extend the existing previous subarray.
 * Maintain running maximum in O(1) space.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class MaximumSubarrayKadaneDP {

    public static int maxSubArray(int[] nums) {
        int currentMax = nums[0];
        int globalMax = nums[0];

        for (int i = 1; i < nums.length; i++) {
            currentMax = Math.max(nums[i], currentMax + nums[i]);
            globalMax = Math.max(globalMax, currentMax);
        }

        return globalMax;
    }

    public static void main(String[] args) {
        int[] nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        System.out.println("Max Subarray 1: " + maxSubArray(nums1) + " (Expected: 6)");

        int[] nums2 = {1};
        System.out.println("Max Subarray 2: " + maxSubArray(nums2) + " (Expected: 1)");

        int[] nums3 = {5, 4, -1, 7, 8};
        System.out.println("Max Subarray 3: " + maxSubArray(nums3) + " (Expected: 23)");
    }
}

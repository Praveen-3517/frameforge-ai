/**
 * Problem: Trapping Rain Water (LeetCode 42 - DP Solution)
 * Asked in: Amazon, Google, Microsoft, Bloomberg, Apple
 * 
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 * 
 * Approach:
 * Prefix and Suffix Max DP Arrays:
 * Water trapped at bar i is determined by:
 *   water[i] = max(0, min(maxLeft[i], maxRight[i]) - height[i])
 * 1. Precompute maxLeft array where maxLeft[i] is maximum height in height[0..i].
 * 2. Precompute maxRight array where maxRight[i] is maximum height in height[i..n-1].
 * 3. Sum water trapped across all indices.
 * 
 * Time Complexity: O(N) with three linear passes.
 * Space Complexity: O(N) for DP arrays.
 */
class TrappingRainWaterDP {

    public static int trap(int[] height) {
        if (height == null || height.length <= 2) return 0;

        int n = height.length;
        int[] leftMax = new int[n];
        int[] rightMax = new int[n];

        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(leftMax[i - 1], height[i]);
        }

        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = Math.max(rightMax[i + 1], height[i]);
        }

        int totalWater = 0;
        for (int i = 0; i < n; i++) {
            totalWater += Math.min(leftMax[i], rightMax[i]) - height[i];
        }

        return totalWater;
    }

    public static void main(String[] args) {
        int[] height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        System.out.println("Trapped water 1: " + trap(height1) + " (Expected: 6)");

        int[] height2 = {4, 2, 0, 3, 2, 5};
        System.out.println("Trapped water 2: " + trap(height2) + " (Expected: 9)");
    }
}

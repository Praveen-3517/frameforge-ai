/**
 * Problem Statement:
 * Given `n` non-negative integers representing an elevation map where the width of each bar is 1,
 * compute how much water it can trap after raining.
 * (LeetCode 42: Trapping Rain Water - Hard).
 *
 * Example:
 * height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 *
 * Asked in: Google, Amazon, Microsoft, Apple, Bloomberg, Goldman Sachs
 *
 * Approach:
 * - Optimal Converging Two-Pointer While Loop (O(N) Time, O(1) Space):
 *   Water trapped above bar `i` is determined by: `min(maxLeft, maxRight) - height[i]`.
 *   Instead of computing prefix and suffix maximum arrays (which cost O(N) space):
 *   - Maintain two pointers `left = 0` and `right = n - 1`, and running peaks `leftMax` and `rightMax`.
 *   - The key invariant: If `height[left] <= height[right]`:
 *     We know with certainty that `leftMax <= rightMax` (or `right` provides a taller boundary).
 *     Therefore, trapped water at `left` depends ONLY on `leftMax`!
 *     - If `height[left] >= leftMax`: update `leftMax = height[left]`.
 *     - Else: `trapped += leftMax - height[left]`.
 *     Advance `left++`.
 *   - Symmetrically for the right side when `height[right] < height[left]`:
 *     - If `height[right] >= rightMax`: update `rightMax = height[right]`.
 *     - Else: `trapped += rightMax - height[right]`.
 *     Advance `right--`.
 */
class TrappingRainWaterTwoPointers {

    public static int trap(int[] height) {
        if (height == null || height.length <= 2) return 0;

        int left = 0;
        int right = height.length - 1;
        int leftMax = 0;
        int rightMax = 0;
        int trappedWater = 0;

        while (left < right) {
            if (height[left] <= height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    trappedWater += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    trappedWater += rightMax - height[right];
                }
                right--;
            }
        }

        return trappedWater;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 42: Trapping Rain Water (Two-Pointer O(1) Space) ===");

        int[][] testElevations = {
            { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 }, // Expected: 6
            { 4, 2, 0, 3, 2, 5 },                   // Expected: 9
            { 3, 0, 2, 0, 4 },                      // Expected: 7
            { 5, 4, 3, 2, 1 },                      // Monotonic decreasing -> 0
            { 1, 2, 3, 4, 5 }                       // Monotonic increasing -> 0
        };

        for (int[] h : testElevations) {
            int trapped = trap(h);
            System.out.printf("Elevation: %s%n ==> Trapped Water Units: %d%n%n",
                    java.util.Arrays.toString(h), trapped);
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass converging two pointers.
 * Space Complexity: O(1) - Constant auxiliary stack variables.
 */

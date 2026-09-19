import java.util.Arrays;

/**
 * Problem Statement:
 * Given `n` non-negative integers representing an elevation map where the width of each bar is 1,
 * compute how much water it can trap after raining.
 * (LeetCode 42: Trapping Rain Water - Hard).
 *
 * Asked in: Google, Amazon, Microsoft, Facebook / Meta
 *
 * Approach:
 * - Method 1: Prefix & Suffix Maximum Arrays (O(N) Time, O(N) Space):
 *   `leftMax[i] = max(leftMax[i - 1], height[i])`
 *   `rightMax[i] = max(rightMax[i + 1], height[i])`
 *   `trapped[i] = min(leftMax[i], rightMax[i]) - height[i]`.
 * - Method 2: Two-Pointer Converging Window (O(N) Time, O(1) Space):
 *   Left pointer tracks `leftMax`, right pointer tracks `rightMax`.
 *   Water trapped on the side with smaller peak is strictly determined by that side's maximum.
 */
class TrappingRainWaterArray {

    // Method 1: Prefix & Suffix Max Arrays (O(N) space)
    public static int trapPrefixSuffix(int[] height) {
        if (height == null || height.length <= 2) return 0;
        int n = height.length;

        int[] leftMax = new int[n];
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(leftMax[i - 1], height[i]);
        }

        int[] rightMax = new int[n];
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = Math.max(rightMax[i + 1], height[i]);
        }

        int trapped = 0;
        for (int i = 0; i < n; i++) {
            trapped += Math.min(leftMax[i], rightMax[i]) - height[i];
        }

        return trapped;
    }

    // Method 2: Two Pointers (O(1) space)
    public static int trapTwoPointers(int[] height) {
        if (height == null || height.length <= 2) return 0;

        int left = 0, right = height.length - 1;
        int leftMax = 0, rightMax = 0;
        int trapped = 0;

        while (left < right) {
            if (height[left] <= height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    trapped += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    trapped += rightMax - height[right];
                }
                right--;
            }
        }

        return trapped;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 42: Trapping Rain Water (Prefix/Suffix vs Two Pointers) ===");

        int[] elevation = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
        int ans1 = trapPrefixSuffix(elevation);
        int ans2 = trapTwoPointers(elevation);

        System.out.println("Elevation: " + Arrays.toString(elevation));
        System.out.printf("Prefix/Suffix Method : %d units%n", ans1);
        System.out.printf("Two Pointers Method   : %d units%n", ans2);
    }
}

/*
 * Time Complexity: O(N) - Linear scan across the elevation array.
 * Space Complexity: O(1) for Two Pointers, O(N) for Prefix/Suffix arrays.
 */

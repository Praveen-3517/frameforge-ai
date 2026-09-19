/**
 * Problem: Container With Most Water (LeetCode 11)
 * Category: Two Pointers (Opposite Ends) | Medium
 * Asked in: Amazon, Google, Apple, Microsoft, Facebook
 * 
 * You are given an integer array height of length n. There are n vertical lines drawn such that
 * the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container such that the container
 * contains the most water. Return the maximum amount of water a container can store.
 * 
 * Approach - Greedy Two Pointer:
 * Water = min(height[left], height[right]) * (right - left).
 * Move the pointer with the SHORTER height inward (since the shorter side limits capacity).
 * Moving the taller side can only decrease or maintain width without increasing height limit.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class ContainerWithMostWaterTwoPointer {

    public static int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int maxWater = 0;

        while (left < right) {
            int water = Math.min(height[left], height[right]) * (right - left);
            maxWater = Math.max(maxWater, water);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxWater;
    }

    public static void main(String[] args) {
        System.out.println(maxArea(new int[]{1, 8, 6, 2, 5, 4, 8, 3, 7}) + " (Expected: 49)");
        // Lines at index 1 (height=8) and 8 (height=7), width=7, water=7*7=49
        System.out.println(maxArea(new int[]{1, 1}) + " (Expected: 1)");
    }
}

/*
 * Problem Statement:
 * Given n non-negative integers representing an elevation map where the width of each
 * bar is 1, compute how much water it can trap after raining.
 * Implement both:
 * 1. Monotonic Stack Approach (O(N) time, O(N) space)
 * 2. Two-Pointer Approach (O(N) time, O(1) space)
 * (LeetCode 42: Trapping Rain Water)
 * 
 * Example:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * 
 * Asked in: Google, Amazon, Facebook/Meta, Apple, Microsoft, Bloomberg
 */

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class TrappingRainWaterTwoPointersAndStack {

    // Approach 1: Monotonic Stack (Computes trapped water horizontally bounded by troughs)
    public static int trapStack(int[] height) {
        Deque<Integer> stack = new ArrayDeque<>(); // Stores indices
        int water = 0;

        for (int curr = 0; curr < height.length; curr++) {
            while (!stack.isEmpty() && height[curr] > height[stack.peek()]) {
                int bottomIdx = stack.pop();
                if (stack.isEmpty()) break;

                int leftIdx = stack.peek();
                int distance = curr - leftIdx - 1;
                int boundedHeight = Math.min(height[leftIdx], height[curr]) - height[bottomIdx];
                water += distance * boundedHeight;
            }
            stack.push(curr);
        }

        return water;
    }

    // Approach 2: Two Pointers (O(1) space optimal)
    public static int trapTwoPointers(int[] height) {
        if (height == null || height.length < 3) return 0;

        int left = 0, right = height.length - 1;
        int leftMax = 0, rightMax = 0;
        int totalWater = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= leftMax) {
                    leftMax = height[left];
                } else {
                    totalWater += leftMax - height[left];
                }
                left++;
            } else {
                if (height[right] >= rightMax) {
                    rightMax = height[right];
                } else {
                    totalWater += rightMax - height[right];
                }
                right--;
            }
        }

        return totalWater;
    }

    public static void main(String[] args) {
        int[] height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

        System.out.println("Elevation map: " + Arrays.toString(height));
        System.out.println("Trapped Water (Stack):        " + trapStack(height) + " units (Expected: 6)");
        System.out.println("Trapped Water (Two Pointers): " + trapTwoPointers(height) + " units (Expected: 6)");
    }
}

/*
 * Time Complexity: O(N) linear time for both approaches.
 * Space Complexity: Stack: O(N); Two Pointers: O(1) auxiliary space.
 */

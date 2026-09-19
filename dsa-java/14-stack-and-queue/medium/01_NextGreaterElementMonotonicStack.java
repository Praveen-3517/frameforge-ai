/*
 * Problem Statement:
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
 * return the next greater number for every element in nums.
 * The next greater number of a number x is the first greater number to its traversing-order
 * next in the array, which means you could search circularly to find its next greater number.
 * If it doesn't exist, return -1 for this number.
 * (LeetCode 503: Next Greater Element II)
 * 
 * Example:
 * Input: nums = [1,2,1]
 * Output: [2,-1,2]
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 */

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class NextGreaterElementMonotonicStack {

    /**
     * Approach:
     * Monotonic Decreasing Stack over 2N Circular Range:
     * - Loop from 2N - 1 down to 0 using modulo indexing (i % n).
     * - While stack is not empty and stack.peek() <= nums[i % n], pop stack.
     * - If i < n, result[i] is stack.peek() (or -1 if stack is empty).
     * - Push nums[i % n] onto stack.
     */
    public static int[] nextGreaterElements(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);

        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 2 * n - 1; i >= 0; i--) {
            int val = nums[i % n];
            while (!stack.isEmpty() && stack.peek() <= val) {
                stack.pop();
            }

            if (i < n) {
                if (!stack.isEmpty()) {
                    result[i] = stack.peek();
                }
            }

            stack.push(val);
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 1};
        System.out.println("Nums: [1, 2, 1]");
        System.out.println("Next Greater Elements: " + Arrays.toString(nextGreaterElements(nums1)));

        int[] nums2 = {1, 2, 3, 4, 3};
        System.out.println("\nNums: [1, 2, 3, 4, 3]");
        System.out.println("Next Greater Elements: " + Arrays.toString(nextGreaterElements(nums2)));
    }
}

/*
 * Time Complexity: O(N) - Each element is pushed and popped at most twice across 2N loop.
 * Space Complexity: O(N) monotonic stack storage.
 */

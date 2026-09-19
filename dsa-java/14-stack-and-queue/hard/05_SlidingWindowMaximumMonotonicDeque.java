/*
 * Problem Statement:
 * Implement Sliding Window Maximum using an optimal Monotonic Deque:
 * - Return maximum element in every contiguous sliding window of size k in array nums.
 * - Monotonic decreasing deque stores candidate indices in O(N) time.
 * (LeetCode 239: Sliding Window Maximum)
 * 
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 * 
 * Asked in: Amazon, Google, Citadel, Microsoft
 */

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class SlidingWindowMaximumMonotonicDeque {

    public static int[] maxSlidingWindow(int[] nums, int k) {
        if (nums == null || k <= 0) return new int[0];
        int n = nums.length;
        int[] result = new int[n - k + 1];
        int outIdx = 0;

        Deque<Integer> deque = new ArrayDeque<>(); // Stores indices

        for (int i = 0; i < n; i++) {
            // Evict elements outside the current window
            while (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
                deque.pollFirst();
            }

            // Maintain monotonic decreasing order of values
            while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
                deque.pollLast();
            }

            deque.offerLast(i);

            // Record maximum for window ending at i
            if (i >= k - 1) {
                result[outIdx++] = nums[deque.peekFirst()];
            }
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;

        System.out.println("Array: " + Arrays.toString(nums) + ", Window: " + k);
        System.out.println("Max Sliding Window: " + Arrays.toString(maxSlidingWindow(nums, k)));
    }
}

/*
 * Time Complexity: O(N) - Each index pushed and popped from deque at most once.
 * Space Complexity: O(k) deque holding at most k elements.
 */

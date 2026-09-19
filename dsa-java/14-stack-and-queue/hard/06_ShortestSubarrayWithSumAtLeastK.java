/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the length of the shortest
 * non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.
 * Note: nums can contain negative numbers, which precludes standard two-pointer sliding windows!
 * (LeetCode 862: Shortest Subarray with Sum at Least K)
 * 
 * Example:
 * Input: nums = [2,-1,2], k = 3
 * Output: 3
 * 
 * Asked in: Google, Goldman Sachs, Amazon
 */

import java.util.ArrayDeque;
import java.util.Deque;

class ShortestSubarrayWithSumAtLeastK {

    /**
     * Approach:
     * Prefix Sums + Monotonic Deque:
     * 1. Compute prefix sums as long[] to prevent integer overflow.
     * 2. Maintain a monotonic increasing deque of indices:
     *    - While P[i] - P[deque.peekFirst()] >= k:
     *      A valid subarray found! Update minLen and pollFirst() because any later end index
     *      would produce a longer subarray with this start index.
     *    - While P[i] <= P[deque.peekLast()]:
     *      pollLast() because index i has a smaller prefix sum and is farther right,
     *      making previous larger prefix sum indices obsolete!
     */
    public static int shortestSubarray(int[] nums, int k) {
        int n = nums.length;
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        int minLen = Integer.MAX_VALUE;
        Deque<Integer> deque = new ArrayDeque<>();

        for (int i = 0; i <= n; i++) {
            // Check valid subarray satisfying sum >= k
            while (!deque.isEmpty() && prefix[i] - prefix[deque.peekFirst()] >= k) {
                minLen = Math.min(minLen, i - deque.pollFirst());
            }

            // Maintain monotonic increasing prefix sums
            while (!deque.isEmpty() && prefix[i] <= prefix[deque.peekLast()]) {
                deque.pollLast();
            }

            deque.offerLast(i);
        }

        return minLen == Integer.MAX_VALUE ? -1 : minLen;
    }

    public static void main(String[] args) {
        int[] nums1 = {1};
        int k1 = 1;
        System.out.println("nums: [1], k = 1 -> Shortest length: " + shortestSubarray(nums1, k1));

        int[] nums2 = {1, 2};
        int k2 = 4;
        System.out.println("nums: [1, 2], k = 4 -> Shortest length: " + shortestSubarray(nums2, k2));

        int[] nums3 = {2, -1, 2};
        int k3 = 3;
        System.out.println("nums: [2, -1, 2], k = 3 -> Shortest length: " + shortestSubarray(nums3, k3));
    }
}

/*
 * Time Complexity: O(N) - Each prefix index enters and leaves deque at most once.
 * Space Complexity: O(N) for prefix sums and monotonic deque.
 */

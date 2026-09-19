/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the k-th largest element in the array.
 * Note that it is the k-th largest element in sorted order, not the k-th distinct element.
 * 
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 * 
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Apple, Google
 */

import java.util.PriorityQueue;

class KthLargestElementInArray {

    /**
     * Approach:
     * Min-Heap of Size K:
     * - Maintain a min-heap of capacity K.
     * - Iterate through nums:
     *   - Add num to heap.
     *   - If heap size exceeds K, poll (evict) the smallest.
     * - After processing all elements, the root of the min-heap is the K-th largest element!
     */
    public static int findKthLargest(int[] nums, int k) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(k);

        for (int num : nums) {
            minHeap.offer(num);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        return minHeap.peek();
    }

    public static void main(String[] args) {
        int[] nums1 = {3, 2, 1, 5, 6, 4};
        int k1 = 2;
        System.out.println("Input: [3, 2, 1, 5, 6, 4], k = 2");
        System.out.println("2nd largest: " + findKthLargest(nums1, k1));

        int[] nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        int k2 = 4;
        System.out.println("\nInput: [3, 2, 3, 1, 2, 4, 5, 5, 6], k = 4");
        System.out.println("4th largest: " + findKthLargest(nums2, k2));
    }
}

/*
 * Time Complexity: O(N log K) - Each insertion into heap of size K takes O(log K).
 * Space Complexity: O(K) - Heap stores exactly K elements.
 */

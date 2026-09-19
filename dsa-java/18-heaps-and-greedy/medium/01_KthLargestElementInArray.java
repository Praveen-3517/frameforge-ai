import java.util.PriorityQueue;

/**
 * Problem: Kth Largest Element in an Array (LeetCode 215)
 * Asked in: Facebook, Amazon, Google, Microsoft, Apple
 * 
 * Given an integer array nums and an integer k, return the kth largest element in the array.
 * Note that it is the kth largest element in sorted order, not the kth distinct element.
 * 
 * Approach:
 * Min-Heap of size K:
 * Maintain a Min-Heap of size k.
 * For each num:
 * - Offer num to minHeap.
 * - If size > k, poll the smallest element.
 * The root of the heap is the k-th largest element!
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(K)
 */
class KthLargestElementInArray {

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
        System.out.println("2nd largest: " + findKthLargest(nums1, 2) + " (Expected: 5)");

        int[] nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        System.out.println("4th largest: " + findKthLargest(nums2, 4) + " (Expected: 4)");
    }
}

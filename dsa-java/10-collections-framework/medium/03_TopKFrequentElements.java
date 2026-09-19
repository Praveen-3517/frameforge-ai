/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * You may return the answer in any order.
 * 
 * Example:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1, 2]
 * 
 * Asked in: Amazon, Facebook/Meta, Google, Bloomberg, Microsoft
 */

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class TopKFrequentElements {

    /**
     * Approach:
     * 1. Count frequencies using HashMap: O(N).
     * 2. Maintain a Min-Heap of size K comparing entry frequencies.
     * 3. For every key in map, offer to heap; if size exceeds K, poll smallest frequency.
     * 4. Remaining K elements in heap are top K frequent: O(U log K).
     */
    public static int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> countMap = new HashMap<>();
        for (int n : nums) {
            countMap.merge(n, 1, Integer::sum);
        }

        // Min-Heap ordered by frequency (lowest frequency on top)
        PriorityQueue<Integer> heap = new PriorityQueue<>(
                (a, b) -> Integer.compare(countMap.get(a), countMap.get(b))
        );

        for (int key : countMap.keySet()) {
            heap.offer(key);
            if (heap.size() > k) {
                heap.poll();
            }
        }

        int[] result = new int[k];
        for (int i = k - 1; i >= 0; i--) {
            result[i] = heap.poll();
        }
        return result;
    }

    public static void main(String[] args) {
        int[] nums = {1, 1, 1, 2, 2, 3};
        int k = 2;

        int[] topK = topKFrequent(nums, k);
        System.out.println("Array: " + Arrays.toString(nums) + ", k = " + k);
        System.out.println("Top " + k + " frequent elements: " + Arrays.toString(topK));
    }
}

/*
 * Time Complexity: O(N log K) where N is array length and K is heap size.
 * Space Complexity: O(N) for hash map frequency storage and min-heap.
 */

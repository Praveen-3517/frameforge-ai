import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

/**
 * Problem: Top K Frequent Elements (LeetCode 347)
 * Asked in: Facebook, Amazon, Google, Microsoft, Bloomberg
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * 
 * Approach:
 * Frequency Map + Min-Heap of size K:
 * 1. Count frequencies in a HashMap.
 * 2. Maintain a Min-Heap of map entries ordered by entry.getValue() ascending.
 * 3. Keep size of heap <= k by polling smallest frequency entries.
 * 4. Remaining k entries are the top frequent elements!
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(N) for frequency map + O(K) for heap.
 */
class TopKFrequentElements {

    public static int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        for (int num : nums) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }

        // Min-heap ordered by frequency
        PriorityQueue<Map.Entry<Integer, Integer>> minHeap = 
            new PriorityQueue<>(Comparator.comparingInt(Map.Entry::getValue));

        for (Map.Entry<Integer, Integer> entry : freqMap.entrySet()) {
            minHeap.offer(entry);
            if (minHeap.size() > k) {
                minHeap.poll();
            }
        }

        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = minHeap.poll().getKey();
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 1, 1, 2, 2, 3};
        System.out.println("Top 2: " + Arrays.toString(topKFrequent(nums1, 2))); // [2, 1]

        int[] nums2 = {1};
        System.out.println("Top 1: " + Arrays.toString(topKFrequent(nums2, 1))); // [1]
    }
}

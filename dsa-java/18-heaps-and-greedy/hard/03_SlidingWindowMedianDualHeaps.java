import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

/**
 * Problem: Sliding Window Median (LeetCode 480)
 * Asked in: Google, Amazon, Facebook
 * 
 * The median is the unique element such that the count of elements <= median is at least (k + 1) / 2.
 * Given an integer array nums and an integer k, find the median of the consecutive window of size k
 * sliding across the array.
 * 
 * Approach:
 * Dual Heaps with Lazy Deletion:
 * - maxHeap (lower half), minHeap (upper half).
 * - HashMap `delayed` maps value to count of pending removals.
 * - When window slides:
 *   - Record outgoing element in `delayed`.
 *   - Insert incoming element into appropriate heap.
 *   - Rebalance heap sizes so that maxHeap.size == minHeap.size (or + 1).
 *   - Prune invalid elements lazily from top of both heaps.
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(K)
 */
class SlidingWindowMedianDualHeaps {

    public static double[] medianSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        double[] result = new double[n - k + 1];

        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        Map<Integer, Integer> delayed = new HashMap<>();

        // Initialize first window
        for (int i = 0; i < k; i++) {
            maxHeap.offer(nums[i]);
        }
        for (int i = 0; i < k / 2; i++) {
            minHeap.offer(maxHeap.poll());
        }

        result[0] = getMedian(maxHeap, minHeap, k);

        for (int i = k; i < n; i++) {
            int outgoing = nums[i - k];
            int incoming = nums[i];
            int balance = 0; // Tracks size imbalance introduced

            // 1. Mark outgoing for lazy deletion
            delayed.put(outgoing, delayed.getOrDefault(outgoing, 0) + 1);
            if (outgoing <= maxHeap.peek()) {
                balance--;
            } else {
                balance++;
            }

            // 2. Insert incoming element
            if (!maxHeap.isEmpty() && incoming <= maxHeap.peek()) {
                maxHeap.offer(incoming);
                balance++;
            } else {
                minHeap.offer(incoming);
                balance--;
            }

            // 3. Rebalance heaps
            if (balance < 0) {
                maxHeap.offer(minHeap.poll());
            } else if (balance > 0) {
                minHeap.offer(maxHeap.poll());
            }

            // 4. Prune invalid roots
            prune(maxHeap, delayed);
            prune(minHeap, delayed);

            result[i - k + 1] = getMedian(maxHeap, minHeap, k);
        }

        return result;
    }

    private static void prune(PriorityQueue<Integer> heap, Map<Integer, Integer> delayed) {
        while (!heap.isEmpty() && delayed.containsKey(heap.peek())) {
            int root = heap.peek();
            int count = delayed.get(root);
            if (count == 1) {
                delayed.remove(root);
            } else {
                delayed.put(root, count - 1);
            }
            heap.poll();
        }
    }

    private static double getMedian(PriorityQueue<Integer> maxHeap, PriorityQueue<Integer> minHeap, int k) {
        if (k % 2 != 0) {
            return (double) maxHeap.peek();
        } else {
            return ((double) maxHeap.peek() + (double) minHeap.peek()) / 2.0;
        }
    }

    public static void main(String[] args) {
        int[] nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;
        double[] medians = medianSlidingWindow(nums, k);
        System.out.println("Sliding window medians: " + Arrays.toString(medians));
        // Expected: [1.0, -1.0, -1.0, 3.0, 5.0, 6.0]
    }
}

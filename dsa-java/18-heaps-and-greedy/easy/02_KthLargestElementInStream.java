import java.util.PriorityQueue;

/**
 * Problem: Kth Largest Element in a Stream (LeetCode 703)
 * Asked in: Amazon, Google, Facebook
 * 
 * Design a class to find the kth largest element in a stream.
 * Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * 
 * Approach:
 * Min-Heap of size K:
 * - A Min-Heap of size k maintains the k largest numbers seen so far.
 * - The root (peek) of this Min-Heap is always the k-th largest element!
 * - When adding a number:
 *   - Offer num into heap.
 *   - If heap.size() > k, poll root.
 *   - Return heap.peek().
 * 
 * Time Complexity: O(log K) per add operation.
 * Space Complexity: O(K) storage.
 */
class KthLargestElementInStream {

    private final PriorityQueue<Integer> minHeap;
    private final int k;

    public KthLargestElementInStream(int k, int[] nums) {
        this.k = k;
        this.minHeap = new PriorityQueue<>(k);

        for (int num : nums) {
            add(num);
        }
    }

    public int add(int val) {
        minHeap.offer(val);
        if (minHeap.size() > k) {
            minHeap.poll();
        }
        return minHeap.peek();
    }

    public static void main(String[] args) {
        int[] init = {4, 5, 8, 2};
        KthLargestElementInStream kthLargest = new KthLargestElementInStream(3, init);

        System.out.println("add(3): " + kthLargest.add(3) + " (Expected: 4)");
        System.out.println("add(5): " + kthLargest.add(5) + " (Expected: 5)");
        System.out.println("add(10): " + kthLargest.add(10) + " (Expected: 5)");
        System.out.println("add(9): " + kthLargest.add(9) + " (Expected: 8)");
        System.out.println("add(4): " + kthLargest.add(4) + " (Expected: 8)");
    }
}

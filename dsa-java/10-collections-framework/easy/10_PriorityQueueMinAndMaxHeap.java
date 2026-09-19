/*
 * Problem Statement:
 * Demonstrate `java.util.PriorityQueue` as Min-Heap and Max-Heap:
 * - Default PriorityQueue creates a Min-Heap (smallest element has highest priority).
 * - Passing `Collections.reverseOrder()` or custom Comparator creates a Max-Heap.
 * - Inspect and extract elements in sorted priority order using `poll()`.
 * 
 * Asked in: Amazon, Microsoft, Uber, Apple
 */

import java.util.Collections;
import java.util.PriorityQueue;

class PriorityQueueMinAndMaxHeap {

    public static void main(String[] args) {
        int[] rawNumbers = {45, 12, 89, 3, 27, 64};

        // 1. Min-Heap (Default)
        System.out.println("--- 1. Min-Heap (Smallest First) ---");
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int n : rawNumbers) minHeap.offer(n);

        System.out.println("Min-Heap root (peek): " + minHeap.peek());
        System.out.print("Polling order: ");
        while (!minHeap.isEmpty()) {
            System.out.print(minHeap.poll() + " ");
        }
        System.out.println();

        // 2. Max-Heap (Reverse Order)
        System.out.println("\n--- 2. Max-Heap (Largest First) ---");
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (int n : rawNumbers) maxHeap.offer(n);

        System.out.println("Max-Heap root (peek): " + maxHeap.peek());
        System.out.print("Polling order: ");
        while (!maxHeap.isEmpty()) {
            System.out.print(maxHeap.poll() + " ");
        }
        System.out.println();
    }
}

/*
 * Time Complexity: offer(e): O(log N), poll(): O(log N), peek(): O(1).
 * Space Complexity: O(N) array storage for binary heap.
 */

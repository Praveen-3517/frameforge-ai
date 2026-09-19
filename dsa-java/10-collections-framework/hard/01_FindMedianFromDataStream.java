/*
 * Problem Statement:
 * Design a data structure that supports the following two operations:
 * - void addNum(int num): Adds an integer num from the data stream to the data structure.
 * - double findMedian(): Returns the median of all elements so far.
 * (LeetCode 295: Find Median from Data Stream)
 * 
 * Asked in: Google, Amazon, Facebook/Meta, Apple, Microsoft, Goldman Sachs
 */

import java.util.Collections;
import java.util.PriorityQueue;

class FindMedianFromDataStream {

    static class MedianFinder {
        // Max-heap stores smaller half of numbers
        private final PriorityQueue<Integer> maxHeap;
        // Min-heap stores larger half of numbers
        private final PriorityQueue<Integer> minHeap;

        public MedianFinder() {
            maxHeap = new PriorityQueue<>(Collections.reverseOrder());
            minHeap = new PriorityQueue<>();
        }

        public void addNum(int num) {
            // Always insert into maxHeap first
            maxHeap.offer(num);

            // Balance order: largest in maxHeap must be <= smallest in minHeap
            minHeap.offer(maxHeap.poll());

            // Balance sizes: maxHeap can have at most 1 more element than minHeap
            if (minHeap.size() > maxHeap.size()) {
                maxHeap.offer(minHeap.poll());
            }
        }

        public double findMedian() {
            if (maxHeap.size() > minHeap.size()) {
                return maxHeap.peek();
            } else {
                return (maxHeap.peek() + minHeap.peek()) / 2.0;
            }
        }
    }

    public static void main(String[] args) {
        MedianFinder mf = new MedianFinder();

        int[] stream = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};

        System.out.println("--- Median From Data Stream (Dual Heaps) ---");
        for (int x : stream) {
            mf.addNum(x);
            System.out.printf("Added %2d -> Current Median: %.1f%n", x, mf.findMedian());
        }
    }
}

/*
 * Time Complexity: addNum: O(log N) heap insertions; findMedian: O(1) peek.
 * Space Complexity: O(N) to store stream elements across both heaps.
 */

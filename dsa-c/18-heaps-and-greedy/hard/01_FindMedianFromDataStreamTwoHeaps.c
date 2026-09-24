/**
 * Problem: Find Median from Data Stream (LeetCode 295)
 * Asked in: Google, Amazon, Facebook, Microsoft, Apple
 * 
 * The median is the middle value in an ordered integer list. If the size of the list
 * is even, there is no middle value, and the median is the mean of the two middle values.
 * Design a data structure that supports:
 * - addNum(num): Adds the integer num from the data stream.
 * - findMedian(): Returns the median of all elements so far.
 * 
 * Approach:
 * Two Heaps (Max-Heap for lower half, Min-Heap for upper half):
 * - maxHeap stores lower half of numbers (inverted order).
 * - minHeap stores upper half of numbers (natural order).
 * Balancing invariant:
 * - maxHeap.size() == minHeap.size() OR maxHeap.size() == minHeap.size() + 1.
 * - Every element in maxHeap <= every element in minHeap.
 * If total count is odd, median is maxHeap.peek().
 * If total count is even, median is (maxHeap.peek() + minHeap.peek()) / 2.0.
 * 
 * Time Complexity:
 * - addNum: O(log N)
 * - findMedian: O(1)
 * Space Complexity: O(N)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

static const PriorityQueue<int> maxHeap; // lower half
    static const PriorityQueue<int> minHeap; // upper half

    FindMedianFromDataStreamTwoHeaps() {
        this.maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        this.minHeap = new PriorityQueue<>();
    }

    void addNum(int num) {
        maxHeap.offer(num);
        minHeap.offer(maxHeap.poll());

        // Maintain balance invariant
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.offer(minHeap.poll());
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.peek();
        } else {
            return (maxHeap.peek() + minHeap.peek()) / 2.0;
        }
    }

    int main(void) {
        FindMedianFromDataStreamTwoHeaps medianFinder = new FindMedianFromDataStreamTwoHeaps();
        medianFinder.addNum(1);
        medianFinder.addNum(2);
        printf("Median after 1, 2: " + medianFinder.findMedian() + " (Expected: 1.5)\n");
        medianFinder.addNum(3);
        printf("Median after 1, 2, 3: " + medianFinder.findMedian() + " (Expected: 2.0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

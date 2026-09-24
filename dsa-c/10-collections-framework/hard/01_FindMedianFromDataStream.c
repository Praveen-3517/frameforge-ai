/*
 * Problem Statement:
 * Design a data structure that supports the following two operations:
 * - void addNum(int num): Adds an integer num from the data stream to the data structure.
 * - double findMedian(): Returns the median of all elements so far.
 * (LeetCode 295: Find Median from Data Stream)
 * 
 * Asked in: Google, Amazon, Facebook/Meta, Apple, Microsoft, Goldman Sachs
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

static class MedianFinder {
        // Max-heap stores smaller half of numbers
        static const PriorityQueue<int> maxHeap;
        // Min-heap stores larger half of numbers
        static const PriorityQueue<int> minHeap;

        MedianFinder() {
            maxHeap = new PriorityQueue<>(Collections.reverseOrder());
            minHeap = new PriorityQueue<>();
        }

        void addNum(int num) {
            // Always insert into maxHeap first
            maxHeap.offer(num);

            // Balance order: largest in maxHeap must be <= smallest in minHeap
            minHeap.offer(maxHeap.poll());

            // Balance sizes: maxHeap can have at most 1 more element than minHeap
            if (minHeap.size() > maxHeap.size()) {
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
    }

    int main(void) {
        MedianFinder mf = new MedianFinder();

        int* stream = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};

        printf("--- Median From Data Stream (Dual Heaps) ---\n");
        for (size_t _idx = 0; _idx < sizeof(stream)/sizeof(stream[0]); _idx++) {
        int x = stream[_idx];
            mf.addNum(x);
            printf("Added %2d -> Current Median: %.1f\n", x, mf.findMedian());
        }
        return 0;
}

/*
 * Time Complexity: addNum: O(log N) heap insertions; findMedian: O(1) peek.
 * Space Complexity: O(N) to store stream elements across both heaps.
 */

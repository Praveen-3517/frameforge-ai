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

static const PriorityQueue<int> minHeap;
    static const int k;

    KthLargestElementInStream(int k, int* nums) {
        this.k = k;
        this.minHeap = new PriorityQueue<>(k);

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            add(num);
        }
    }

    int add(int val) {
        minHeap.offer(val);
        if (minHeap.size() > k) {
            minHeap.poll();
        }
        return minHeap.peek();
    }

    int main(void) {
        int* init = {4, 5, 8, 2};
        KthLargestElementInStream kthLargest = new KthLargestElementInStream(3, init);

        printf("add(3): " + kthLargest.add(3) + " (Expected: 4)\n");
        printf("add(5): " + kthLargest.add(5) + " (Expected: 5)\n");
        printf("add(10): " + kthLargest.add(10) + " (Expected: 5)\n");
        printf("add(9): " + kthLargest.add(9) + " (Expected: 8)\n");
        printf("add(4): " + kthLargest.add(4) + " (Expected: 8)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

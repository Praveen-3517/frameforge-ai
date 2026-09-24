/*
 * Problem Statement:
 * Demonstrate `java.util.PriorityQueue` as Min-Heap and Max-Heap:
 * - Default PriorityQueue creates a Min-Heap (smallest element has highest priority).
 * - Passing `Collections.reverseOrder()` or custom Comparator creates a Max-Heap.
 * - Inspect and extract elements in sorted priority order using `poll()`.
 * 
 * Asked in: Amazon, Microsoft, Uber, Apple
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

int main(void) {
        int* rawNumbers = {45, 12, 89, 3, 27, 64};

        // 1. Min-Heap (Default)
        printf("--- 1. Min-Heap (Smallest First) ---\n");
        PriorityQueue<int> minHeap = new PriorityQueue<>();
        for (int n : rawNumbers) minHeap.offer(n);

        printf("Min-Heap root (peek): %d\n", minHeap.peek());
        printf("%s", "Polling order: ");
        while (!minHeap.isEmpty()) {
            printf("%s", minHeap.poll() + " ");
        }
        printf("\n");

        // 2. Max-Heap (Reverse Order)
        printf("\n--- 2. Max-Heap (Largest First) ---\n");
        PriorityQueue<int> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (int n : rawNumbers) maxHeap.offer(n);

        printf("Max-Heap root (peek): %d\n", maxHeap.peek());
        printf("%s", "Polling order: ");
        while (!maxHeap.isEmpty()) {
            printf("%s", maxHeap.poll() + " ");
        }
        printf("\n");
        return 0;
}

/*
 * Time Complexity: offer(e): O(log N), poll(): O(log N), peek(): O(1).
 * Space Complexity: O(N) array storage for binary heap.
 */

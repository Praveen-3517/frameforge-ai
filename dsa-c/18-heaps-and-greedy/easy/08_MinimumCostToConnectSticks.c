/**
 * Problem: Minimum Cost to Connect Sticks (LeetCode 1167)
 * Asked in: Amazon, Google
 * 
 * You have some number of sticks with positive integer lengths given in an array sticks.
 * You can connect any two sticks of lengths x and y into one stick by paying a cost of x + y.
 * You must connect all sticks until there is only one stick remaining.
 * Return the minimum cost of connecting all the given sticks into one stick.
 * 
 * Approach:
 * Greedy Huffman Coding Strategy (Min-Heap):
 * To minimize total cost, always combine the two shortest sticks currently available,
 * as smaller sticks contribute less when accumulated repeatedly.
 * 1. Insert all stick lengths into a Min-Heap.
 * 2. While heap size > 1:
 *    - Pop two smallest sticks x and y.
 *    - Cost to combine = x + y.
 *    - Accumulate totalCost += cost.
 *    - Push combined stick back into Min-Heap.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for Min-Heap.
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

int connectSticks(int* sticks) {
        PriorityQueue<int> minHeap = new PriorityQueue<>();
        for (size_t _idx = 0; _idx < sizeof(sticks)/sizeof(sticks[0]); _idx++) {
        int stick = sticks[_idx];
            minHeap.offer(stick);
        }

        int totalCost = 0;

        while (minHeap.size() > 1) {
            int first = minHeap.poll();
            int second = minHeap.poll();
            int combined = first + second;

            totalCost += combined;
            minHeap.offer(combined);
        }

        return totalCost;
    }

    int main(void) {
        int* sticks1 = {2, 4, 3};
        printf("Min cost 1: " + connectSticks(sticks1) + " (Expected: 14)\n");
        // Combine 2 + 3 = 5 (cost 5), sticks: [4, 5]
        // Combine 4 + 5 = 9 (cost 9), total = 5 + 9 = 14

        int* sticks2 = {1, 8, 3, 5};
        printf("Min cost 2: " + connectSticks(sticks2) + " (Expected: 30)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

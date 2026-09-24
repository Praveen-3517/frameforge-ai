/**
 * Problem: Last Stone Weight (LeetCode 1046)
 * Asked in: Amazon, Google, LinkedIn
 * 
 * You are given an array of integers stones where stones[i] is the weight of the ith stone.
 * We are playing a game with the stones. On each turn, we choose the heaviest two stones
 * with weights x and y with x <= y:
 * - If x == y, both stones are destroyed.
 * - If x != y, stone of weight x is destroyed, and stone of weight y has new weight y - x.
 * Return the weight of the last remaining stone, or 0 if none remain.
 * 
 * Approach:
 * Max-Heap (PriorityQueue with Collections.reverseOrder()):
 * In each round, extract two largest elements. If not equal, insert difference back into heap.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for Max-Heap.
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

int lastStoneWeight(int* stones) {
        PriorityQueue<int> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (size_t _idx = 0; _idx < sizeof(stones)/sizeof(stones[0]); _idx++) {
        int stone = stones[_idx];
            maxHeap.offer(stone);
        }

        while (maxHeap.size() > 1) {
            int y = maxHeap.poll();
            int x = maxHeap.poll();

            if (y > x) {
                maxHeap.offer(y - x);
            }
        }

        return maxHeap.isEmpty() ? 0 : maxHeap.peek();
    }

    int main(void) {
        int* stones1 = {2, 7, 4, 1, 8, 1};
        printf("Last stone: " + lastStoneWeight(stones1) + " (Expected: 1)\n");

        int* stones2 = {1};
        printf("Last stone: " + lastStoneWeight(stones2) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

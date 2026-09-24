/**
 * Problem: Relative Ranks (LeetCode 506)
 * Asked in: Google
 * 
 * You are given an integer array score of size n, where score[i] is the score of the ith athlete.
 * All the scores are guaranteed to be unique.
 * The athletes are placed based on their scores:
 * 1st: "Gold Medal", 2nd: "Silver Medal", 3rd: "Bronze Medal", 4th+: their placement number string ("4", "5", ...).
 * 
 * Approach:
 * Max-Heap with Index Tracking:
 * Push [score, originalIndex] into a Max-Heap ordered by score descending.
 * Pop each athlete, assigning rank according to placement count.
 * 
 * Time Complexity: O(N log N)
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

const char*[] findRelativeRanks(int* score) {
        int n = n;
        const char*[] result = new const char*[n];

        // Max-heap: [score, originalIndex]
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> int.compare(b[0], a[0]));

        for (int i = 0; i < n; i++) {
            maxHeap.offer((int[]){score[i], i});
        }

        int rank = 1;
        while (!maxHeap.isEmpty()) {
            int* athlete = maxHeap.poll();
            int idx = athlete[1];

            if (rank == 1) {
                result[idx] = "Gold Medal";
            } else if (rank == 2) {
                result[idx] = "Silver Medal";
            } else if (rank == 3) {
                result[idx] = "Bronze Medal";
            } else {
                result[idx] = const char*.valueOf(rank);
            }
            rank++;
        }

        return result;
    }

    int main(void) {
        int* score1 = {5, 4, 3, 2, 1};
        printf("Ranks 1: %d\n", "[array]"));
        // Expected: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]

        int* score2 = {10, 3, 8, 9, 4};
        printf("Ranks 2: %d\n", "[array]"));
        // Expected: ["Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

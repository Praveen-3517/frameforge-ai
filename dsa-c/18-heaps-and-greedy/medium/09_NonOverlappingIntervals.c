/**
 * Problem: Non-overlapping Intervals (LeetCode 435)
 * Asked in: Facebook, Amazon, Google
 * 
 * Given an array of intervals intervals where intervals[i] = [starti, endi], return
 * the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
 * 
 * Approach:
 * Classic Activity Selection (Greedy by End Time):
 * 1. To MAXIMIZE the number of mutually compatible intervals, always pick the interval that ENDS EARLIEST.
 * 2. Sort intervals by end time ascending.
 * 3. Track `prevEnd`.
 *    - If current.start < prevEnd: Overlap detected! We must remove this interval -> removals++.
 *    - Else: No overlap, keep interval -> update prevEnd = current.end.
 * 
 * Time Complexity: O(N log N) for sorting.
 * Space Complexity: O(1) auxiliary space.
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

int eraseOverlapIntervals(int** intervals) {
        if (intervals == NULL || n == 0) return 0;

        // Sort by end time ascending
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[1]));

        int removals = 0;
        int prevEnd = intervals[0][1];

        for (int i = 1; i < n; i++) {
            if (intervals[i][0] < prevEnd) {
                removals++; // Overlap -> remove interval with larger end time
            } else {
                prevEnd = intervals[i][1];
            }
        }

        return removals;
    }

    int main(void) {
        int** int1 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
        printf("Removals 1: " + eraseOverlapIntervals(int1) + " (Expected: 1)\n");

        int** int2 = {{1, 2}, {1, 2}, {1, 2}};
        printf("Removals 2: " + eraseOverlapIntervals(int2) + " (Expected: 2)\n");

        int** int3 = {{1, 2}, {2, 3}};
        printf("Removals 3: " + eraseOverlapIntervals(int3) + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/*
 * Problem Statement:
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping
 * intervals, and return an array of the non-overlapping intervals that cover all the
 * intervals in the input.
 * (LeetCode 56: Merge Intervals)
 * 
 * Example 1:
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Bloomberg, Microsoft
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

/**
     * Approach:
     * Sort & Merge:
     * 1. Sort intervals by start time: O(N log N).
     * 2. Initialize current interval.
     * 3. For each subsequent interval:
     *    - If next.start <= current.end: Overlap! Merge by current.end = max(current.end, next.end).
     *    - Else: Disjoint! Add current to results, make next the current interval.
     */
    int** merge(int** intervals) {
        if (n <= 1) return intervals;

        // Sort by start time
        Arrays.sort(intervals, (a, b) -> int.compare(a[0], b[0]));

        int* merged = new ArrayList<>();
        int* current = intervals[0];
        merged.add(current);

        for (int i = 1; i < n; i++) {
            int* next = intervals[i];

            if (next[0] <= current[1]) {
                // Overlapping: extend the end
                current[1] = MAX(current[1], next[1]);
            } else {
                // Non-overlapping: start a new interval
                current = next;
                merged.add(current);
            }
        }

        return merged.toArray((int*)malloc((merged.size()) * sizeof(int))[]);
    }

    int main(void) {
        int** intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

        printf("Input intervals:  %d\n", Arrays.deepToString(intervals));
        int** result = merge(intervals);
        printf("Merged intervals: %d\n", Arrays.deepToString(result));
        return 0;
}

/*
 * Time Complexity: O(N log N) sorting step dominates.
 * Space Complexity: O(N) auxiliary space to hold merged intervals.
 */

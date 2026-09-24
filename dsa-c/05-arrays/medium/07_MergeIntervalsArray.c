/**
 * Problem Statement:
 * Given an array of intervals where `intervals[i] = [start, end]`, merge all overlapping intervals,
 * and return an array of the non-overlapping intervals that cover all the intervals in the input.
 * (LeetCode 56: Merge Intervals).
 *
 * Example:
 * intervals = [[1,3],[2,6],[8,10],[15,18]] -> [[1,6],[8,10],[15,18]]
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft, Bloomberg
 *
 * Approach:
 * - Sort by Start Time & Greedy Linear Merge:
 *   1. Sort intervals primarily by start coordinate `a[0]`:
 *      `Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));`
 *   2. Iterate through each interval `curr`:
 *      - If `merged` is empty OR `curr[0] > prev[1]` (no overlap):
 *        Add `curr` as a new interval.
 *      - Else (overlap detected because `curr[0] <= prev[1]`):
 *        Merge intervals by extending the previous end:
 *        `prev[1] = Math.max(prev[1], curr[1]);`
 *   3. Convert merged list to 2D array.
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

int** merge(int** intervals) {
        if (intervals == NULL || n <= 1) return intervals;

        // Sort by start time ascending
        Arrays.sort(intervals, (a, b) -> int.compare(a[0], b[0]));

        int* merged = new ArrayList<>();
        int* currentInterval = intervals[0];
        merged.add(currentInterval);

        for (int i = 1; i < n; i++) {
            int* nextInterval = intervals[i];

            if (nextInterval[0] <= currentInterval[1]) {
                // Overlapping: expand upper bound
                currentInterval[1] = MAX(currentInterval[1], nextInterval[1]);
            } else {
                // Disjoint: begin new interval
                currentInterval = nextInterval;
                merged.add(currentInterval);
            }
        }

        return merged.toArray((int*)malloc((merged.size()) * sizeof(int))[]);
    }

    int main(void) {
        printf("=== LeetCode 56: Merge Overlapping Intervals ===\n");

        int** intervals = {
            { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 }
        };

        printf("Original Intervals: %d\n", Arrays.deepToString(intervals));
        int** result = merge(intervals);
        printf("Merged Intervals  : %d\n", Arrays.deepToString(result));
        return 0;
}

/*
 * Time Complexity: O(N log N) - Sorting the N intervals dominates runtime.
 * Space Complexity: O(N) - Storage for merged intervals.
 */

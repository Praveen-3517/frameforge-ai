/**
 * Problem: Merge Intervals (LeetCode 56)
 * Asked in: Facebook, Amazon, Google, Microsoft, Bloomberg
 * 
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping
 * intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
 * 
 * Approach:
 * Greedy Interval Merging:
 * 1. Sort intervals by start time ascending.
 * 2. Maintain a list of merged intervals.
 * 3. For each interval:
 *    - If merged list is empty or current.start > lastMerged.end:
 *      Add current as a new interval.
 *    - Else (overlap):
 *      Extend lastMerged.end = max(lastMerged.end, current.end).
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for merged list.
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
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));

        int* merged = new ArrayList<>();
        int* current = intervals[0];
        merged.add(current);

        for (int i = 1; i < n; i++) {
            int* interval = intervals[i];

            if (interval[0] <= current[1]) {
                // Overlapping -> merge by taking max end
                current[1] = MAX(current[1], interval[1]);
            } else {
                // Disjoint -> advance current
                current = interval;
                merged.add(current);
            }
        }

        return merged.toArray((int*)malloc((merged.size()) * sizeof(int))[]);
    }

    int main(void) {
        int** int1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
        printf("Merged 1: %d\n", Arrays.deepToString(merge(int1)));
        // Expected: [[1, 6], [8, 10], [15, 18]]

        int** int2 = {{1, 4}, {4, 5}};
        printf("Merged 2: %d\n", Arrays.deepToString(merge(int2)));
        // Expected: [[1, 5]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

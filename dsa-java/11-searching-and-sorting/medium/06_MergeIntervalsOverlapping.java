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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class MergeIntervalsOverlapping {

    /**
     * Approach:
     * Sort & Merge:
     * 1. Sort intervals by start time: O(N log N).
     * 2. Initialize current interval.
     * 3. For each subsequent interval:
     *    - If next.start <= current.end: Overlap! Merge by current.end = max(current.end, next.end).
     *    - Else: Disjoint! Add current to results, make next the current interval.
     */
    public static int[][] merge(int[][] intervals) {
        if (intervals.length <= 1) return intervals;

        // Sort by start time
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        List<int[]> merged = new ArrayList<>();
        int[] current = intervals[0];
        merged.add(current);

        for (int i = 1; i < intervals.length; i++) {
            int[] next = intervals[i];

            if (next[0] <= current[1]) {
                // Overlapping: extend the end
                current[1] = Math.max(current[1], next[1]);
            } else {
                // Non-overlapping: start a new interval
                current = next;
                merged.add(current);
            }
        }

        return merged.toArray(new int[merged.size()][]);
    }

    public static void main(String[] args) {
        int[][] intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

        System.out.println("Input intervals:  " + Arrays.deepToString(intervals));
        int[][] result = merge(intervals);
        System.out.println("Merged intervals: " + Arrays.deepToString(result));
    }
}

/*
 * Time Complexity: O(N log N) sorting step dominates.
 * Space Complexity: O(N) auxiliary space to hold merged intervals.
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

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
class MergeIntervalsArray {

    public static int[][] merge(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) return intervals;

        // Sort by start time ascending
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        List<int[]> merged = new ArrayList<>();
        int[] currentInterval = intervals[0];
        merged.add(currentInterval);

        for (int i = 1; i < intervals.length; i++) {
            int[] nextInterval = intervals[i];

            if (nextInterval[0] <= currentInterval[1]) {
                // Overlapping: expand upper bound
                currentInterval[1] = Math.max(currentInterval[1], nextInterval[1]);
            } else {
                // Disjoint: begin new interval
                currentInterval = nextInterval;
                merged.add(currentInterval);
            }
        }

        return merged.toArray(new int[merged.size()][]);
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 56: Merge Overlapping Intervals ===");

        int[][] intervals = {
            { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 }
        };

        System.out.println("Original Intervals: " + Arrays.deepToString(intervals));
        int[][] result = merge(intervals);
        System.out.println("Merged Intervals  : " + Arrays.deepToString(result));
    }
}

/*
 * Time Complexity: O(N log N) - Sorting the N intervals dominates runtime.
 * Space Complexity: O(N) - Storage for merged intervals.
 */

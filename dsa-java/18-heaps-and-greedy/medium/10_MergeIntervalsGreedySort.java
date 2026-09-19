import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

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
class MergeIntervalsGreedySort {

    public static int[][] merge(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) return intervals;

        // Sort by start time ascending
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));

        List<int[]> merged = new ArrayList<>();
        int[] current = intervals[0];
        merged.add(current);

        for (int i = 1; i < intervals.length; i++) {
            int[] interval = intervals[i];

            if (interval[0] <= current[1]) {
                // Overlapping -> merge by taking max end
                current[1] = Math.max(current[1], interval[1]);
            } else {
                // Disjoint -> advance current
                current = interval;
                merged.add(current);
            }
        }

        return merged.toArray(new int[merged.size()][]);
    }

    public static void main(String[] args) {
        int[][] int1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
        System.out.println("Merged 1: " + Arrays.deepToString(merge(int1)));
        // Expected: [[1, 6], [8, 10], [15, 18]]

        int[][] int2 = {{1, 4}, {4, 5}};
        System.out.println("Merged 2: " + Arrays.deepToString(merge(int2)));
        // Expected: [[1, 5]]
    }
}

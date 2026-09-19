import java.util.Arrays;
import java.util.Comparator;

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
class NonOverlappingIntervals {

    public static int eraseOverlapIntervals(int[][] intervals) {
        if (intervals == null || intervals.length == 0) return 0;

        // Sort by end time ascending
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[1]));

        int removals = 0;
        int prevEnd = intervals[0][1];

        for (int i = 1; i < intervals.length; i++) {
            if (intervals[i][0] < prevEnd) {
                removals++; // Overlap -> remove interval with larger end time
            } else {
                prevEnd = intervals[i][1];
            }
        }

        return removals;
    }

    public static void main(String[] args) {
        int[][] int1 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
        System.out.println("Removals 1: " + eraseOverlapIntervals(int1) + " (Expected: 1)");

        int[][] int2 = {{1, 2}, {1, 2}, {1, 2}};
        System.out.println("Removals 2: " + eraseOverlapIntervals(int2) + " (Expected: 2)");

        int[][] int3 = {{1, 2}, {2, 3}};
        System.out.println("Removals 3: " + eraseOverlapIntervals(int3) + " (Expected: 0)");
    }
}

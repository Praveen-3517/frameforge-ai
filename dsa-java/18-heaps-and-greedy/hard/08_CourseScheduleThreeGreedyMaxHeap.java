import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Problem: Course Schedule III (LeetCode 630)
 * Asked in: Google, Amazon, Uber
 * 
 * There are n different online courses numbered from 1 to n. You are given an array
 * courses where courses[i] = [durationi, lastDayi].
 * You start on the 1st day and must finish course i before or at lastDayi.
 * Return the maximum number of courses that you can take.
 * 
 * Approach:
 * Greedy Sorting + Max-Heap Eviction:
 * 1. Sort courses by deadline (lastDay) ascending.
 * 2. Maintain total elapsed time `time` and a Max-Heap storing durations of courses currently taken.
 * 3. For each course [duration, lastDay]:
 *    - Take the course: `time += duration`, `maxHeap.offer(duration)`.
 *    - If `time > lastDay`:
 *      We missed the deadline! Greedily evict the course that took the MOST time:
 *      `time -= maxHeap.poll()`.
 * 4. Heap size represents maximum number of courses we can take.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */
class CourseScheduleThreeGreedyMaxHeap {

    public static int scheduleCourse(int[][] courses) {
        // Sort by deadline ascending
        Arrays.sort(courses, Comparator.comparingInt(a -> a[1]));

        // Max-heap of durations
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int time = 0;

        for (int[] course : courses) {
            int duration = course[0];
            int lastDay = course[1];

            time += duration;
            maxHeap.offer(duration);

            if (time > lastDay) {
                time -= maxHeap.poll(); // Evict the longest duration course
            }
        }

        return maxHeap.size();
    }

    public static void main(String[] args) {
        int[][] courses1 = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
        System.out.println("Max courses 1: " + scheduleCourse(courses1) + " (Expected: 3)");

        int[][] courses2 = {{1, 2}};
        System.out.println("Max courses 2: " + scheduleCourse(courses2) + " (Expected: 1)");

        int[][] courses3 = {{3, 2}, {4, 3}};
        System.out.println("Max courses 3: " + scheduleCourse(courses3) + " (Expected: 0)");
    }
}

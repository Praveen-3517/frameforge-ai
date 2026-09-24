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

int scheduleCourse(int** courses) {
        // Sort by deadline ascending
        Arrays.sort(courses, Comparator.comparingInt(a -> a[1]));

        // Max-heap of durations
        PriorityQueue<int> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int time = 0;

        for (int* course : courses) {
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

    int main(void) {
        int** courses1 = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
        printf("Max courses 1: " + scheduleCourse(courses1) + " (Expected: 3)\n");

        int** courses2 = {{1, 2}};
        printf("Max courses 2: " + scheduleCourse(courses2) + " (Expected: 1)\n");

        int** courses3 = {{3, 2}, {4, 3}};
        printf("Max courses 3: " + scheduleCourse(courses3) + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/**
 * Problem: Course Schedule (LeetCode 207)
 * Asked in: Amazon, Google, Microsoft, Facebook, Apple, Twitter
 * 
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
 * You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that
 * you must take bi first if you want to take ai.
 * Return true if you can finish all courses. Otherwise, return false.
 * 
 * Approach:
 * Kahn's Algorithm for Cycle Detection in Directed Graphs:
 * 1. Compute in-degree (number of prerequisite dependencies) for each course.
 * 2. Enqueue all courses with in-degree == 0 (courses with no prerequisites).
 * 3. While queue is not empty:
 *    - Dequeue course `curr`, increment `completedCount`.
 *    - For each dependent course `next` of `curr`:
 *      - Decrement in-degree of `next`.
 *      - If in-degree becomes 0, enqueue `next`.
 * 4. If completedCount == numCourses, no cycle exists -> return true!
 * 
 * Time Complexity: O(V + E) where V = numCourses and E = prerequisites.length.
 * Space Complexity: O(V + E) for adjacency list and in-degree array.
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

bool canFinish(int numCourses, int** prerequisites) {
        int*> adj = new ArrayList<>(numCourses);
        for (int i = 0; i < numCourses; i++) {
            adj.add(new ArrayList<>());
        }

        int* inDegree = (int*)malloc((numCourses) * sizeof(int));

        for (int* pre : prerequisites) {
            int course = pre[0];
            int dependency = pre[1];
            adj.get(dependency).add(course);
            inDegree[course]++;
        }

        Queue<int> queue = new ArrayDeque<>();
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
            }
        }

        int completedCourses = 0;

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            completedCourses++;

            for (int neighbor : adj.get(curr)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        return completedCourses == numCourses;
    }

    int main(void) {
        int** pre1 = {{1, 0}};
        printf("Can finish 2 courses: " + canFinish(2, pre1) + " (Expected: true)\n");

        int** pre2 = {{1, 0}, {0, 1}};
        printf("Can finish 2 courses with cycle: " + canFinish(2, pre2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/**
 * Problem: Course Schedule II (LeetCode 210)
 * Asked in: Amazon, Google, Microsoft, Facebook, Apple
 * 
 * Return the ordering of courses you should take to finish all courses.
 * If there are multiple valid orders, return any of them.
 * If it is impossible to finish all courses, return an empty array.
 * 
 * Approach:
 * Kahn's Algorithm (Topological Sort BFS):
 * Record each node in an array `order` as it is popped with inDegree 0.
 * If total popped equals numCourses, return `order`; else return empty array `int[0]`.
 * 
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
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

int* findOrder(int numCourses, int** prerequisites) {
        int*> adj = new ArrayList<>(numCourses);
        for (int i = 0; i < numCourses; i++) {
            adj.add(new ArrayList<>());
        }

        int* inDegree = (int*)malloc((numCourses) * sizeof(int));
        for (int* pre : prerequisites) {
            adj.get(pre[1]).add(pre[0]);
            inDegree[pre[0]]++;
        }

        Queue<int> queue = new ArrayDeque<>();
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                queue.offer(i);
            }
        }

        int* order = (int*)malloc((numCourses) * sizeof(int));
        int idx = 0;

        while (!queue.isEmpty()) {
            int curr = queue.poll();
            order[idx++] = curr;

            for (int neighbor : adj.get(curr)) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        return idx == numCourses ? order : (int*)malloc((0) * sizeof(int));
    }

    int main(void) {
        int** pre = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
        int* order = findOrder(4, pre);
        printf("Course order: " + "[array]\n");
        // Valid order: [0, 1, 2, 3] or [0, 2, 1, 3]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

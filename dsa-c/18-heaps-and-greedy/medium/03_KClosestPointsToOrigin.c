/**
 * Problem: K Closest Points to Origin (LeetCode 973)
 * Asked in: Facebook, Amazon, Google, Apple
 * 
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane
 * and an integer k, return the k closest points to the origin (0, 0).
 * Distance is Euclidean: sqrt(x^2 + y^2).
 * 
 * Approach:
 * Max-Heap of size K:
 * Keep the k smallest distances by maintaining a Max-Heap of size k comparing (x^2 + y^2).
 * When heap size exceeds k, poll the point with the largest distance.
 * 
 * Time Complexity: O(N log K)
 * Space Complexity: O(K) for the Max-Heap.
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

int** kClosest(int** points, int k) {
        // Max-heap comparing distance squared: (x^2 + y^2) descending
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> 
            int.compare(b[0] * b[0] + b[1] * b[1], a[0] * a[0] + a[1] * a[1])
        );

        for (int* p : points) {
            maxHeap.offer(p);
            if (maxHeap.size() > k) {
                maxHeap.poll();
            }
        }

        int** result = (int*)malloc((k) * sizeof(int))[2];
        for (int i = 0; i < k; i++) {
            result[i] = maxHeap.poll();
        }

        return result;
    }

    int main(void) {
        int** points1 = {{1, 3}, {-2, 2}};
        int** res1 = kClosest(points1, 1);
        printf("Closest 1: %d\n", Arrays.deepToString(res1)); // [[-2, 2]]

        int** points2 = {{3, 3}, {5, -1}, {-2, 4}};
        int** res2 = kClosest(points2, 2);
        printf("Closest 2: %d\n", Arrays.deepToString(res2)); // [[3, 3], [-2, 4]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

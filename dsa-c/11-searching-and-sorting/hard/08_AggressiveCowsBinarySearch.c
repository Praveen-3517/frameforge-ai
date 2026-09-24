/*
 * Problem Statement:
 * You are given an array of integers stalls representing the coordinates of stalls on
 * a straight line. You have k aggressive cows. You want to place all k cows into the stalls
 * such that the minimum distance between any two cows is as large as possible.
 * Return the largest possible minimum distance.
 * (Classic SPOJ / LeetCode / Interview Problem: Aggressive Cows)
 * 
 * Example:
 * Input: stalls = [1, 2, 4, 8, 9], k = 3
 * Output: 3 (Stalls chosen: 1, 4, 8; min distance is min(3, 4) = 3)
 * 
 * Asked in: Google, Amazon, Microsoft, Flipkart
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

/**
     * Approach:
     * Binary Search on Maximum Minimum Distance:
     * 1. Sort the stall positions: O(N log N).
     * 2. Search range for min distance:
     *    low = 1
     *    high = stalls[n-1] - stalls[0]
     * 3. Predicate canPlaceCows(dist, k):
     *    Greedily place first cow at stalls[0].
     *    Place next cow at stalls[i] only if stalls[i] - lastPlaced >= dist.
     *    If cowsPlaced >= k, then dist is feasible!
     * 4. If feasible, search right half (low = mid + 1) to maximize distance.
     *    Else, search left half (high = mid - 1).
     */
    int maxMinDistance(int* stalls, int k) {
        Arrays.sort(stalls);
        int n = n;

        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canPlaceCows(stalls, k, mid)) {
                ans = mid;      // Mid is feasible, try larger distance
                low = mid + 1;
            } else {
                high = mid - 1; // Distance too large, decrease
            }
        }

        return ans;
    }

    static bool canPlaceCows(int* stalls, int k, int dist) {
        int count = 1; // Place 1st cow at stalls[0]
        int lastPos = stalls[0];

        for (int i = 1; i < n; i++) {
            if (stalls[i] - lastPos >= dist) {
                count++;
                lastPos = stalls[i];
                if (count >= k) return true;
            }
        }

        return false;
    }

    int main(void) {
        int* stalls = {1, 2, 4, 8, 9};
        int k = 3;

        printf("Stalls: [array], Cows k = %d\n", k);
        printf("Maximum minimum distance: " + maxMinDistance(stalls, k) + " (Expected: 3)\n");

        int* stalls2 = {10, 1, 2, 7, 5};
        int k2 = 3;
        printf("\nStalls: [10, 1, 2, 7, 5], Cows k = 3\n");
        printf("Maximum minimum distance: %d\n", maxMinDistance(stalls2, k2));
        return 0;
}

/*
 * Time Complexity: O(N log N + N log(max_dist))
 * Space Complexity: O(1) auxiliary space.
 */

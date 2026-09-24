/*
 * Problem Statement:
 * Koko loves to eat bananas. There are n piles of bananas, the i-th pile has piles[i] bananas.
 * The guards have gone and will come back in h hours.
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile
 * of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats
 * all of them instead and will not eat any more bananas during this hour.
 * Return the minimum integer k such that she can eat all the bananas within h hours.
 * (LeetCode 875: Koko Eating Bananas)
 * 
 * Example:
 * Input: piles = [3, 6, 7, 11], h = 8
 * Output: 4
 * 
 * Asked in: Google, Airbnb, Amazon, Bloomberg
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
     * Binary Search on Answer:
     * - Search space for speed k: [1, max(piles)].
     * - Monotonic property: If speed k is sufficient to eat in <= h hours, any speed > k
     *   will also be sufficient.
     * - If canFinish(k, h): try smaller speed (high = mid).
     * - Else: must increase speed (low = mid + 1).
     */
    int minEatingSpeed(int* piles, int h) {
        int low = 1;
        int high = 1;
        for (size_t _idx = 0; _idx < sizeof(piles)/sizeof(piles[0]); _idx++) {
        int p = piles[_idx];
            if (p > high) high = p;
        }

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canFinish(piles, h, mid)) {
                high = mid; // viable, look for smaller valid speed
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

    static bool canFinish(int* piles, int h, int speed) {
        long long totalHours = 0;
        for (size_t _idx = 0; _idx < sizeof(piles)/sizeof(piles[0]); _idx++) {
        int p = piles[_idx];
            // Ceiling division: (p + speed - 1) / speed
            totalHours += (p + speed - 1) / speed;
            if (totalHours > h) return false;
        }
        return totalHours <= h;
    }

    int main(void) {
        int* piles = {3, 6, 7, 11};
        int h = 8;

        printf("Piles: [3, 6, 7, 11], Max Hours: 8\n");
        printf("Minimum eating speed k: %d\n", minEatingSpeed(piles, h));

        int* piles2 = {30, 11, 23, 4, 20};
        int h2 = 5;
        printf("\nPiles: [30, 11, 23, 4, 20], Max Hours: 5\n");
        printf("Minimum eating speed k: %d\n", minEatingSpeed(piles2, h2));
        return 0;
}

/*
 * Time Complexity: O(N * log(max(piles))) where N is piles length.
 * Space Complexity: O(1) auxiliary space.
 */

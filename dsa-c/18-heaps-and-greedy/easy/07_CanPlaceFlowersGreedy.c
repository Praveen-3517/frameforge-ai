/**
 * Problem: Can Place Flowers (LeetCode 605)
 * Asked in: Facebook, LinkedIn, Google
 * 
 * You have a long flowerbed in which some plots are planted, and some are not.
 * However, flowers cannot be planted in adjacent plots.
 * Given an integer array flowerbed containing 0's and 1's, and an integer n, return
 * true if n new flowers can be planted in the flowerbed without violating the rule.
 * 
 * Approach:
 * Greedy Linear Scan:
 * At each plot i, if plot is empty (0), check if left neighbor is 0 (or i == 0)
 * and right neighbor is 0 (or i == len - 1).
 * If both adjacent plots are free, plant flower at i (flowerbed[i] = 1) and decrement n.
 * If n <= 0, return true.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

bool canPlaceFlowers(int* flowerbed, int n) {
        int len = n;

        for (int i = 0; i < len; i++) {
            if (flowerbed[i] == 0) {
                bool emptyLeft = (i == 0 || flowerbed[i - 1] == 0);
                bool emptyRight = (i == len - 1 || flowerbed[i + 1] == 0);

                if (emptyLeft && emptyRight) {
                    flowerbed[i] = 1;
                    n--;
                    if (n <= 0) return true;
                }
            }
        }

        return n <= 0;
    }

    int main(void) {
        int* fb1 = {1, 0, 0, 0, 1};
        printf("Can place 1: " + canPlaceFlowers(fb1, 1) + " (Expected: true)\n");

        int* fb2 = {1, 0, 0, 0, 1};
        printf("Can place 2: " + canPlaceFlowers(fb2, 2) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

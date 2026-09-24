/**
 * Problem: Counting Bits (LeetCode 338)
 * Asked in: Amazon, Google, Facebook, Apple
 * 
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
 * ans[i] is the number of 1's in the binary representation of i.
 * 
 * Approach:
 * Dynamic Programming with Bit Manipulation:
 * Notice that right-shifting i by 1 (i >> 1) preserves all bits except the least significant bit.
 * Therefore:
 *   dp[i] = dp[i >> 1] + (i & 1)
 * 
 * Time Complexity: O(N) single pass.
 * Space Complexity: O(1) auxiliary space (excluding returned array).
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

int* countBits(int n) {
        int* dp = (int*)malloc((n + 1) * sizeof(int));

        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i >> 1] + (i & 1);
        }

        return dp;
    }

    int main(void) {
        printf("Bits up to 2: " + "[array]") + " (Expected: [0, 1, 1])\n");
        printf("Bits up to 5: " + "[array]") + " (Expected: [0, 1, 1, 2, 1, 2])\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

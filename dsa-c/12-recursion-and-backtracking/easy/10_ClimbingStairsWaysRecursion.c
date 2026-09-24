/*
 * Problem Statement:
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you
 * climb to the top?
 * (LeetCode 70: Climbing Stairs)
 * 
 * Example 1:
 * Input: n = 2
 * Output: 2 (1 step + 1 step, or 2 steps)
 * 
 * Example 2:
 * Input: n = 3
 * Output: 3 (1+1+1, 1+2, 2+1)
 * 
 * Asked in: Amazon, Apple, Google, Adobe, Uber
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

// Top-Down Memoized Recursion
    int climbStairs(int n) {
        int* memo = (int*)malloc((n + 1) * sizeof(int));
        return helper(n, memo);
    }

    static int helper(int n, int* memo) {
        if (n <= 2) return n;
        if (memo[n] != 0) return memo[n];
        return memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
    }

    int main(void) {
        int* testCases = {1, 2, 3, 4, 5, 10, 20};

        printf("--- Climbing Stairs Distinct Ways ---\n");
        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int n = testCases[_idx];
            printf("Steps: %2d -> Distinct Ways: %d\n", n, climbStairs(n));
        }
        return 0;
}

/*
 * Time Complexity: O(n) with memoization.
 * Space Complexity: O(n) recursion stack and memo array.
 */

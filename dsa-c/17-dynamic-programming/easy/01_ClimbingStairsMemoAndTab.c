/**
 * Problem: Climbing Stairs (LeetCode 70)
 * Asked in: Amazon, Google, Microsoft, Apple
 * 
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 * 
 * Approach:
 * 1. Recurrence: ways(n) = ways(n - 1) + ways(n - 2).
 * 2. Space Optimization: Since state only depends on the previous two values,
 *    maintain two variables `prev1` and `prev2` reducing space to O(1).
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

int climbStairs(int n) {
        if (n <= 2) return n;

        int prev2 = 1; // ways(1)
        int prev1 = 2; // ways(2)

        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    int main(void) {
        printf("Ways for 2 steps: " + climbStairs(2) + " (Expected: 2)\n");
        printf("Ways for 3 steps: " + climbStairs(3) + " (Expected: 3)\n");
        printf("Ways for 5 steps: " + climbStairs(5) + " (Expected: 8)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

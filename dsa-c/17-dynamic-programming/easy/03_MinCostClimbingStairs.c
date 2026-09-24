/**
 * Problem: Min Cost Climbing Stairs (LeetCode 746)
 * Asked in: Amazon, Google, Microsoft
 * 
 * You are given an integer array cost where cost[i] is the cost of ith step on a staircase.
 * Once you pay the cost, you can either climb one or two steps.
 * You can either start from the step with index 0, or the step with index 1.
 * Return the minimum cost to reach the top of the floor.
 * 
 * Approach:
 * dp[i] = cost to reach step i.
 * dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]).
 * Optimized with two variables for O(1) space.
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

int minCostClimbingStairs(int* cost) {
        int n = n;
        int prev2 = cost[0];
        int prev1 = cost[1];

        for (int i = 2; i < n; i++) {
            int curr = cost[i] + MIN(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return MIN(prev1, prev2);
    }

    int main(void) {
        int* cost1 = {10, 15, 20};
        printf("Min cost 1: " + minCostClimbingStairs(cost1) + " (Expected: 15)\n");

        int* cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
        printf("Min cost 2: " + minCostClimbingStairs(cost2) + " (Expected: 6)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

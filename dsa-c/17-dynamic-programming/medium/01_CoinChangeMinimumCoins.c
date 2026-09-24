/**
 * Problem: Coin Change (LeetCode 322)
 * Asked in: Amazon, Microsoft, Facebook, Apple, Google
 * 
 * You are given an integer array coins representing coins of different denominations
 * and an integer amount representing a total amount of money. Return the fewest number
 * of coins that you need to make up that amount. If that amount cannot be made up, return -1.
 * You may assume you have an infinite number of each kind of coin.
 * 
 * Approach:
 * Unbounded Knapsack / Bottom-Up 1D DP:
 * Let dp[i] be the minimum coins needed to make amount i.
 * - Base case: dp[0] = 0; initialize rest with amount + 1.
 * - For each amount i from 1 to amount:
 *   - For each coin in coins:
 *     - If i - coin >= 0:
 *       dp[i] = min(dp[i], 1 + dp[i - coin])
 * 
 * Time Complexity: O(amount * |coins|)
 * Space Complexity: O(amount)
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

int coinChange(int* coins, int amount) {
        int max = amount + 1;
        int* dp = (int*)malloc((amount + 1) * sizeof(int));
        Arrays.fill(dp, max);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (size_t _idx = 0; _idx < sizeof(coins)/sizeof(coins[0]); _idx++) {
        int coin = coins[_idx];
                if (i - coin >= 0) {
                    dp[i] = MIN(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }

    int main(void) {
        int* coins1 = {1, 2, 5};
        printf("Min coins for 11: " + coinChange(coins1, 11) + " (Expected: 3)\n");

        int* coins2 = {2};
        printf("Min coins for 3: " + coinChange(coins2, 3) + " (Expected: -1)\n");

        int* coins3 = {1};
        printf("Min coins for 0: " + coinChange(coins3, 0) + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

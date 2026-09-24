/**
 * Problem: Best Time to Buy and Sell Stock IV (LeetCode 188)
 * Asked in: Google, Amazon, Facebook, Bloomberg
 * 
 * You are given an integer array prices where prices[i] is the price of a given stock
 * on the ith day, and an integer k. Complete at most k transactions.
 * Return the maximum profit you can achieve.
 * 
 * Approach:
 * State Machine DP:
 * - If k >= n / 2, we can make as many transactions as we want (greedy peak-valley approach).
 * - Otherwise:
 *   Maintain buy[t] and sell[t] arrays for 1 <= t <= k:
 *   buy[t] represents max balance after t-th buy.
 *   sell[t] represents max balance after t-th sell.
 *   Transition for day price:
 *   buy[t] = max(buy[t], sell[t - 1] - price)
 *   sell[t] = max(sell[t], buy[t] + price)
 * 
 * Time Complexity: O(N * K)
 * Space Complexity: O(K)
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

int maxProfit(int k, int* prices) {
        if (prices == NULL || n == 0 || k == 0) return 0;
        int n = n;

        // Unlimited transactions optimization
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i - 1]) {
                    maxProfit += prices[i] - prices[i - 1];
                }
            }
            return maxProfit;
        }

        int* buy = (int*)malloc((k + 1) * sizeof(int));
        int* sell = (int*)malloc((k + 1) * sizeof(int));
        Arrays.fill(buy, -prices[0]);

        for (size_t _idx = 0; _idx < sizeof(prices)/sizeof(prices[0]); _idx++) {
        int price = prices[_idx];
            for (int t = 1; t <= k; t++) {
                buy[t] = MAX(buy[t], sell[t - 1] - price);
                sell[t] = MAX(sell[t], buy[t] + price);
            }
        }

        return sell[k];
    }

    int main(void) {
        int* prices1 = {2, 4, 1};
        printf("Max profit (k=2): " + maxProfit(2, prices1) + " (Expected: 2)\n");

        int* prices2 = {3, 2, 6, 5, 0, 3};
        printf("Max profit (k=2): " + maxProfit(2, prices2) + " (Expected: 7)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

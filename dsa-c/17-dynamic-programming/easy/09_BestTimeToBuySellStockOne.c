/**
 * Problem: Best Time to Buy and Sell Stock (LeetCode 121)
 * Asked in: Amazon, Facebook, Microsoft, Apple, Google
 * 
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing
 * a different day in the future to sell that stock. Return the maximum profit.
 * 
 * Approach:
 * One-Pass Dynamic Tracking:
 * Track the minimum buying price seen so far (`minPrice`).
 * For each price:
 * - profit = price - minPrice
 * - maxProfit = max(maxProfit, profit)
 * - minPrice = min(minPrice, price)
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

int maxProfit(int* prices) {
        if (prices == NULL || n == 0) return 0;

        int minPrice = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < n; i++) {
            if (prices[i] < minPrice) {
                minPrice = prices[i];
            } else {
                maxProfit = MAX(maxProfit, prices[i] - minPrice);
            }
        }

        return maxProfit;
    }

    int main(void) {
        int* prices1 = {7, 1, 5, 3, 6, 4};
        printf("Max Profit 1: " + maxProfit(prices1) + " (Expected: 5)\n");

        int* prices2 = {7, 6, 4, 3, 1};
        printf("Max Profit 2: " + maxProfit(prices2) + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

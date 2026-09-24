/*
 * Problem Statement:
 * You are given an integer array prices where prices[i] is the price of the i-th item in a shop.
 * There is a special discount: if you buy the i-th item, then you will receive a discount
 * equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <= prices[i].
 * Otherwise, you receive no discount at all.
 * Return an integer array answer where answer[i] is the final price you will pay for the i-th item.
 * (LeetCode 1475: Final Prices With a Special Discount in a Shop)
 * 
 * Example:
 * Input: prices = [8,4,6,2,3]
 * Output: [4,2,4,2,3]
 * 
 * Asked in: Amazon, Google, Microsoft
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
     * Monotonic Increasing Stack of Indices:
     * - Maintain stack of item indices waiting for their next smaller/equal price discount.
     * - For each current price at index i:
     *   - While stack is not empty and prices[stack.peek()] >= prices[i]:
     *     - An eligible discount is found! Deduct prices[i] from prices[stack.pop()].
     *   - Push index i onto stack.
     */
    int* finalPrices(int* prices) {
        int* result = prices.clone();
        Deque<int> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && prices[stack.peek()] >= prices[i]) {
                int discountIdx = stack.pop();
                result[discountIdx] -= prices[i];
            }
            stack.push(i);
        }

        return result;
    }

    int main(void) {
        int* prices = {8, 4, 6, 2, 3};
        printf("Original prices: " + "[array]\n");
        printf("Discounted:      " + "[array]") + " (Expected: [4, 2, 4, 2, 3])\n");

        int* p2 = {1, 2, 3, 4, 5};
        printf("Ascending prices: %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(N) - Each index pushed and popped from stack at most once.
 * Space Complexity: O(N) monotonic stack.
 */

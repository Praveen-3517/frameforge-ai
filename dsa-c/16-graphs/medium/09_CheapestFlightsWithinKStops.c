/**
 * Problem: Cheapest Flights Within K Stops (LeetCode 787)
 * Asked in: Amazon, Airbnb, Google, Microsoft
 * 
 * There are n cities connected by flights where flights[i] = [from, to, price].
 * Given src, dst, and k, return the cheapest price from src to dst with at most k stops.
 * If there is no such route, return -1.
 * 
 * Approach:
 * Bellman-Ford with k + 1 iterations:
 * At most k stops means at most k + 1 edges!
 * - Maintain a prices[] array initialized to infinity; prices[src] = 0.
 * - Run k + 1 rounds:
 *   - Create a copy of prices: tmpPrices = Arrays.copyOf(prices, n).
 *   - For each flight [u, v, cost]:
 *     - If prices[u] != inf and prices[u] + cost < tmpPrices[v]:
 *       tmpPrices[v] = prices[u] + cost.
 *   - prices = tmpPrices.
 * 
 * Time Complexity: O(K * E) where E is number of flights.
 * Space Complexity: O(N) for distance arrays.
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

int findCheapestPrice(int n, int** flights, int src, int dst, int k) {
        int* prices = (int*)malloc((n) * sizeof(int));
        Arrays.fill(prices, INT_MAX);
        prices[src] = 0;

        for (int i = 0; i <= k; i++) {
            int* tmpPrices = Arrays.copyOf(prices, n);

            for (int* flight : flights) {
                int u = flight[0];
                int v = flight[1];
                int cost = flight[2];

                if (prices[u] != INT_MAX && prices[u] + cost < tmpPrices[v]) {
                    tmpPrices[v] = prices[u] + cost;
                }
            }
            prices = tmpPrices;
        }

        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }

    int main(void) {
        int n = 4;
        int** flights = {
            {0, 1, 100},
            {1, 2, 100},
            {2, 0, 100},
            {1, 3, 600},
            {2, 3, 200}
        };

        printf("Cheapest price (k=1): " + findCheapestPrice(n, flights, 0, 3, 1) + " (Expected: 700)\n");
        printf("Cheapest price (k=2): " + findCheapestPrice(n, flights, 0, 3, 2) + " (Expected: 400)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

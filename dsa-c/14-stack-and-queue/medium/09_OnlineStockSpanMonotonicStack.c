/*
 * Problem Statement:
 * Design an algorithm that collects daily price quotes for some stock and returns the
 * span of that stock's price for the current day.
 * The span of the stock's price today is defined as the maximum number of consecutive days
 * (starting from today and going backward) for which the stock price was less than or equal to today's price.
 * (LeetCode 901: Online Stock Span)
 * 
 * Example:
 * next(100) -> 1
 * next(80)  -> 1
 * next(60)  -> 1
 * next(70)  -> 2
 * next(60)  -> 1
 * next(75)  -> 4
 * next(85)  -> 6
 * 
 * Asked in: Amazon, Google, Microsoft, Adobe
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

static class StockSpanner {
        // Each entry stores [price, span]
        static const Deque<int[]> stack = new ArrayDeque<>();

        int next(int price) {
            int span = 1;

            while (!stack.isEmpty() && stack.peek()[0] <= price) {
                span += stack.pop()[1];
            }

            stack.push((int[]){price, span});
            return span;
        }
    }

    int main(void) {
        StockSpanner spanner = new StockSpanner();
        int* prices = {100, 80, 60, 70, 60, 75, 85};

        printf("--- Online Stock Span Testing ---\n");
        for (size_t _idx = 0; _idx < sizeof(prices)/sizeof(prices[0]); _idx++) {
        int p = prices[_idx];
            printf("Price: %3d -> Span: %d\n", p, spanner.next(p));
        }
        return 0;
}

/*
 * Time Complexity: Amortized O(1) per next() call (each price pushed and popped at most once).
 * Space Complexity: O(N) monotonic stack storage.
 */

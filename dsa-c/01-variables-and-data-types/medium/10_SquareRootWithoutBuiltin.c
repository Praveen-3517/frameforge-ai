/**
 * Problem Statement:
 * Given a non-negative integer `x`, compute and return the square root of `x` rounded down
 * to the nearest integer (integer square root).
 * Do NOT use built-in exponent functions like `Math.sqrt(x)` or `Math.pow(x, 0.5)`.
 * Avoid integer overflow when squaring large numbers (`mid * mid`).
 * (LeetCode 69: Sqrt(x)).
 *
 * Asked in: Google, Amazon, Microsoft, Apple
 *
 * Approach:
 * - Binary Search in range `[1, x]`:
 *   - For `x = 0` or `x = 1`, return `x`.
 *   - Search space `left = 1, right = x / 2`.
 *   - Midpoint `mid = left + (right - left) / 2`.
 *   - Overflow Trap: Doing `if (mid * mid <= x)` will overflow 32-bit integer when `mid > 46340`.
 *   - Overflow-safe check: Use division `if (mid <= x / mid)` or promote `mid` to `long`.
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

int mySqrt(int x) {
        if (x < 2) return x;

        int left = 1;
        int right = x / 2;
        int ans = 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // Overflow-safe check equivalent to: mid * mid <= x
            if (mid <= x / mid) {
                ans = mid;         // mid is a candidate floor answer
                left = mid + 1;    // Try to find a larger answer on the right
            } else {
                right = mid - 1;   // mid * mid > x, search left
            }
        }

        return ans;
    }

    int main(void) {
        int* testCases = { 0, 1, 4, 8, 9, 2147395599, INT_MAX };

        printf("=== LeetCode 69: int Sqrt(x) via Overflow-Safe Binary Search ===\n");
        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int x = testCases[_idx];
            int sqrt = mySqrt(x);
            int expected = (int) sqrt(x);
            printf("x = %-12d ==> mySqrt: %-8d | Math.sqrt: %-8d\n", x, sqrt, expected);
            assert sqrt == expected : "Mismatch detected!";
        }
        printf("All test cases passed!\n");
        return 0;
}

/*
 * Time Complexity: O(log X) - Binary search space is halved each step.
 * Space Complexity: O(1) - Constant variables with no extra allocation.
 */

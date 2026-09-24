/**
 * Problem: Bitwise AND of Numbers Range (LeetCode 201)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given two integers left and right that represent the range [left, right],
 * return the bitwise AND of all numbers in this range, inclusive.
 * 
 * Approach - Common Prefix Extraction:
 * The AND of all numbers in [left, right] equals the common bit prefix of left and right.
 * When left != right, the AND includes the rightmost varying bits becoming 0.
 * Algorithm: Right-shift both left and right until they are equal, counting shifts.
 * The result is (left or right, same at this point) << shiftCount.
 * 
 * Time Complexity: O(log N) - at most 32 iterations.
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

int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        return left << shift;
    }

    int main(void) {
        printf("AND [5,7]: " + rangeBitwiseAnd(5, 7) + " (Expected: 4)\n");
        // 5=101, 6=110, 7=111 -> AND=100=4
        printf("AND [0,0]: " + rangeBitwiseAnd(0, 0) + " (Expected: 0)\n");
        printf("AND [1,2147483647]: " + rangeBitwiseAnd(1, 2147483647) + " (Expected: 0)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

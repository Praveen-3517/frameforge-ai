/**
 * Problem: Add Binary (LeetCode 67)
 * Asked in: Amazon, Facebook, Microsoft
 * 
 * Given two binary strings a and b, return their sum as a binary string.
 * 
 * Approach:
 * Simulate binary addition from the rightmost bits with a carry:
 * - Start from the end of both strings and work left.
 * - sum = digitA + digitB + carry.
 * - Appended bit = sum % 2, new carry = sum / 2.
 * - Prepend each bit to result (or append and reverse at the end).
 * 
 * Time Complexity: O(max(A.length, B.length))
 * Space Complexity: O(max(A.length, B.length)) for result.
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

const char* addBinary(const char* a, const char* b) {
        StringBuilder result = new StringBuilder();
        int i = ((int)strlen(a)) - 1;
        int j = ((int)strlen(b)) - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += a[i--] - '0';
            }
            if (j >= 0) {
                sum += b[j--] - '0';
            }

            result.append(sum % 2);
            carry = sum / 2;
        }

        return result.reverse().toString();
    }

    int main(void) {
        printf("11 + 1: " + addBinary("11", "1") + " (Expected: 100)\n");
        printf("1010 + 1011: " + addBinary("1010", "1011") + " (Expected: 10101)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

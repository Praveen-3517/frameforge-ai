/**
 * Problem Statement:
 * Given an integer `n`:
 * 1. Reverse its digits using an iterative `while` loop.
 * 2. Determine whether the original number is a Palindrome (reads the same forwards and backwards).
 * Note: Negative numbers can never be palindromes because of the leading '-' sign.
 * (LeetCode 9: Palindrome Number).
 *
 * Asked in: TCS, Infosys, Amazon, Microsoft, Wipro
 *
 * Approach:
 * - Digit Extraction Loop:
 *   - While `temp != 0`:
 *     Extract last digit: `int digit = temp % 10;`
 *     Append to reversed number: `reversed = reversed * 10 + digit;`
 *     Truncate last digit: `temp /= 10;`
 * - Palindrome check:
 *   If original `n < 0`, return false immediately.
 *   Otherwise, `n == reversed`.
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

long long reverseDigits(int n) {
        long long reversed = 0;
        int temp = abs(n);

        while (temp > 0) {
            int digit = temp % 10;
            reversed = reversed * 10 + digit;
            temp /= 10;
        }

        return (n < 0) ? -reversed : reversed;
    }

    bool isPalindrome(int n) {
        // Negative numbers are not palindromes
        // Also numbers ending in 0 (except 0 itself) cannot be palindromes
        if (n < 0 || (n % 10 == 0 && n != 0)) {
            return false;
        }

        long long reversed = reverseDigits(n);
        return reversed == n;
    }

    int main(void) {
        printf("=== Iterative Digit Reversal & Palindrome Checker ===\n");

        int* testNumbers = { 121, -121, 10, 0, 1234321, 12345, 9, 1000000001 };

        for (size_t _idx = 0; _idx < sizeof(testNumbers)/sizeof(testNumbers[0]); _idx++) {
        int n = testNumbers[_idx];
            long long rev = reverseDigits(n);
            bool pal = isPalindrome(n);
            printf("Number: %11d | Reversed: %11d | Is Palindrome: %s\n",
                    n, rev, pal);
        }
        return 0;
}

/*
 * Time Complexity: O(log10 |N|) - Number of decimal digits in N.
 * Space Complexity: O(1) - Constant stack registers.
 */

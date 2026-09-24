/*
 * Problem Statement:
 * Given a positive decimal integer N, convert it to its binary representation using recursion.
 * For N = 0, return "0".
 * 
 * Example 1:
 * Input: N = 10
 * Output: "1010"
 * 
 * Example 2:
 * Input: N = 25
 * Output: "11001"
 * 
 * Asked in: Amazon, Infosys, TCS, Cognizant
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
     * Decimal to binary conversion recursively divides the number by 2 and records remainder.
     * Base case:
     * - if n == 0 return "0" (when initially 0) or "" (during recursive unwinding).
     * Recursive relation:
     * - decimalToBinary(n / 2) + (n % 2)
     */
    const char* toBinary(int n) {
        if (n == 0) return "0";
        return toBinaryHelper(n);
    }

    static const char* toBinaryHelper(int n) {
        if (n == 0) return "";
        return toBinaryHelper(n / 2) + (n % 2);
    }

    // Also count set bits recursively
    int countSetBits(int n) {
        if (n == 0) return 0;
        return (n & 1) + countSetBits(n >>> 1);
    }

    int main(void) {
        int* testCases = {0, 1, 10, 25, 42, 255};

        printf("--- Decimal to Binary Conversion via Recursion ---\n");
        for (size_t _idx = 0; _idx < sizeof(testCases)/sizeof(testCases[0]); _idx++) {
        int num = testCases[_idx];
            const char* bin = toBinary(num);
            int setBits = countSetBits(num);
            printf("Decimal: %3d -> Binary: %8s | Set bits: %d | Built-in: %s\n",
                    num, bin, setBits, toBinaryString(num));
        }
        return 0;
}

/*
 * Time Complexity: O(log N) - Number of recursive calls equals the number of bits in N.
 * Space Complexity: O(log N) - Recursive call stack depth is equal to log2(N).
 */

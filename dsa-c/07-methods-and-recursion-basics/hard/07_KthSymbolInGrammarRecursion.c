/*
 * Problem Statement:
 * We build a table of n rows (1-indexed). We start by writing 0 in the 1st row.
 * In every subsequent row, we look at the previous row and replace each occurrence of 0
 * with 01, and each occurrence of 1 with 10.
 * Given two integers n and k, return the k-th (1-indexed) symbol in the n-th row.
 * 
 * Example:
 * Row 1: 0
 * Row 2: 01
 * Row 3: 0110
 * Row 4: 01101001
 * Input: n = 4, k = 5
 * Output: 1
 * 
 * Asked in: Google, Amazon, Adobe, Bloomberg
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
     * Divide and Conquer Math Recursion:
     * Row n has length 2^(n-1).
     * The first half of row n is identical to row n-1.
     * The second half of row n is the bitwise complement (inverse) of row n-1.
     * 
     * If k <= mid (where mid = 2^(n-2)):
     *   kthGrammar(n, k) = kthGrammar(n - 1, k)
     * Else:
     *   kthGrammar(n, k) = 1 ^ kthGrammar(n - 1, k - mid)
     * 
     * Even simpler observation:
     * kthGrammar(n, k) depends solely on the count of 1s in the binary representation
     * of (k - 1). If number of set bits is even -> 0, else -> 1!
     */
    int kthGrammar(int n, int k) {
        if (n == 1) return 0;
        int mid = 1 << (n - 2);
        if (k <= mid) {
            return kthGrammar(n - 1, k);
        } else {
            return 1 ^ kthGrammar(n - 1, k - mid);
        }
    }

    // O(1) bit-count shortcut for comparison
    int kthGrammarBitCount(int k) {
        return int.bitCount(k - 1) % 2;
    }

    int main(void) {
        int** tests = {
            {1, 1},
            {2, 1},
            {2, 2},
            {4, 5},
            {30, 434991989}
        };

        printf("--- K-th Symbol in Grammar ---\n");
        for (int* t : tests) {
            int n = t[0];
            int k = t[1];
            int resRec = kthGrammar(n, k);
            int resBit = kthGrammarBitCount(k);
            printf("n = %2d, k = %10d -> Symbol: %d (Bit count check: %d)\n",
                    n, k, resRec, resBit);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Halves k at each level, descending N levels.
 * Space Complexity: O(N) - Recursion call stack depth.
 */

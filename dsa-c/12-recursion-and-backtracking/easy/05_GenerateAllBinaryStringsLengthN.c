/*
 * Problem Statement:
 * Given a positive integer n, generate all 2^n binary strings of length n.
 * 
 * Example:
 * Input: n = 3
 * Output: ["000", "001", "010", "011", "100", "101", "110", "111"]
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
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

int* generateBinaryStrings(int n) {
        int* result = new ArrayList<>();
        char* current = (char*)malloc((n) * sizeof(char));
        backtrack(0, n, current, result);
        return result;
    }

    static void backtrack(int index, int n, char* current, int* result) {
        if (index == n) {
            result.add(new const char*(current));
            return;
        }

        // Try '0'
        current[index] = '0';
        backtrack(index + 1, n, current, result);

        // Try '1'
        current[index] = '1';
        backtrack(index + 1, n, current, result);
    }

    int main(void) {
        int n = 3;
        int* strings = generateBinaryStrings(n);

        printf("Binary strings of length " + n + " (Total = " + strings.size() + "):\n");
        printf("%d\n", strings);
        return 0;
}

/*
 * Time Complexity: O(2^N * N) - 2^N strings created, each copied in O(N).
 * Space Complexity: O(N) recursion stack and buffer.
 */

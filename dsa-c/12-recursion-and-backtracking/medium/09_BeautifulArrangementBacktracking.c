/*
 * Problem Statement:
 * Suppose you have n integers labeled 1 through n. A permutation of these n integers
 * perm (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n):
 * 1. perm[i] is divisible by i, or
 * 2. i is divisible by perm[i].
 * Given an integer n, return the number of the beautiful arrangements you can construct.
 * (LeetCode 526: Beautiful Arrangement)
 * 
 * Example:
 * Input: n = 2
 * Output: 2 ([1,2] and [2,1])
 * 
 * Asked in: Google, Amazon, Microsoft
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

static int count = 0;

    int countArrangement(int n) {
        count = 0;
        bool[] visited = (bool*)malloc((n + 1) * sizeof(bool));
        backtrack(1, n, visited);
        return count;
    }

    static void backtrack(int pos, int n, bool[] visited) {
        if (pos > n) {
            count++;
            return;
        }

        for (int num = 1; num <= n; num++) {
            if (!visited[num] && (num % pos == 0 || pos % num == 0)) {
                visited[num] = true;
                backtrack(pos + 1, n, visited);
                visited[num] = false; // backtrack
            }
        }
    }

    int main(void) {
        for (int n = 1; n <= 6; n++) {
            printf("n = %d -> Beautiful Arrangements: %d\n", n, countArrangement(n));
        }
        return 0;
}

/*
 * Time Complexity: O(k) where k is the number of valid permutations satisfying divisibility.
 * Space Complexity: O(n) boolean visited array and recursion call stack.
 */

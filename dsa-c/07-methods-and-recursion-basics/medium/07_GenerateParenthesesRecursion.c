/*
 * Problem Statement:
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 * 
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * 
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Apple, Adobe
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
     * Backtracking with validity constraints:
     * Maintain count of open parentheses and close parentheses used so far.
     * Rules:
     * 1. Can add '(' if open < n.
     * 2. Can add ')' if close < open.
     * Base case: When string length reaches 2 * n, a valid combination is complete.
     */
    int* generateParenthesis(int n) {
        int* result = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        backtrack(n, 0, 0, sb, result);
        return result;
    }

    static void backtrack(int n, int open, int close, StringBuilder sb, int* result) {
        if (((int)strlen(sb)) == 2 * n) {
            result.add(sb.toString());
            return;
        }

        if (open < n) {
            sb.append('(');
            backtrack(n, open + 1, close, sb, result);
            sb.deleteCharAt(((int)strlen(sb)) - 1); // backtrack
        }

        if (close < open) {
            sb.append(')');
            backtrack(n, open, close + 1, sb, result);
            sb.deleteCharAt(((int)strlen(sb)) - 1); // backtrack
        }
    }

    int main(void) {
        int n = 3;
        int* validCombos = generateParenthesis(n);

        printf("--- Well-formed Parentheses for N = " + n + " ---\n");
        printf("Total combinations (Catalan number C_3 = 5): %d\n", validCombos.size());
        for (const char* s : validCombos) {
            printf("  %d\n", s);
        }

        printf("\nTotal combinations for N = 4 (Catalan number C_4 = 14): %d\n", generateParenthesis(4).size());
        return 0;
}

/*
 * Time Complexity: O(4^N / sqrt(N)) - Proportional to N-th Catalan number C_N.
 * Space Complexity: O(N) - Maximum recursion depth is 2*N.
 */

/**
 * Problem Statement:
 * Given a string `s` representing a valid expression, implement a basic calculator
 * to evaluate it, and return the result of the evaluation.
 * The expression string may contain:
 *   - Non-negative integers
 *   - Addition '+' and Subtraction '-'
 *   - Parentheses '(' and ')'
 *   - Empty spaces ' '
 * (LeetCode 224: Basic Calculator - Hard).
 *
 * Asked in: Google, Facebook / Meta, Microsoft, Amazon
 *
 * Approach:
 * - Stack-Based Parenthesis Scope Evaluation:
 *   Maintain running state:
 *   - `result`: Evaluated sum at the current parenthesis level.
 *   - `number`: Currently parsed multi-digit number.
 *   - `sign`: Current sign (+1 or -1).
 *   When '(' is reached:
 *   - Save the current `result` and `sign` onto the stack.
 *   - Reset `result = 0` and `sign = 1` to begin a fresh sub-expression scope.
 *   When ')' is reached:
 *   - Finish adding the current number to `result`.
 *   - Multiply `result` by the scope sign popped from the stack.
 *   - Add the previous scope result popped from the stack.
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

int calculate(const char* s) {
        Deque<int> stack = new ArrayDeque<>();
        int result = 0;
        int number = 0;
        int sign = 1; // 1 for '+', -1 for '-'

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char ch = s[i];

            if (ch >= '0' && ch <= '9') {
                number = number * 10 + (ch - '0');
            } else if (ch == '+') {
                result += sign * number;
                number = 0;
                sign = 1;
            } else if (ch == '-') {
                result += sign * number;
                number = 0;
                sign = -1;
            } else if (ch == '(') {
                // Save context before entering parenthesis scope
                stack.push(result);
                stack.push(sign);
                // Reset for inside parentheses
                result = 0;
                sign = 1;
            } else if (ch == ')') {
                result += sign * number;
                number = 0;
                // Pop scope sign first, then previous outer result
                int prevSign = stack.pop();
                int prevResult = stack.pop();
                result = prevResult + (prevSign * result);
            }
        }

        if (number != 0) {
            result += sign * number;
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 224: Basic Calculator with Parentheses ===\n");

        const char*[] expressions = {
            "1 + 1",
            " 2-1 + 2 ",
            "(1+(4+5+2)-3)+(6+8)",
            "-(3 + (4 + 5))",
            "1 - (-2)",
            "2147483647"
        };

        for (const char* expr : expressions) {
            printf("Expression: %-25s ==> Result: %d\n", "\"" + expr + "\"", calculate(expr));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single linear scan of the string.
 * Space Complexity: O(N) - Stack memory bounded by the maximum nesting depth of parentheses.
 */

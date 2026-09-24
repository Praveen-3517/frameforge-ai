/*
 * Problem Statement:
 * Given a string s representing a valid expression, implement a basic calculator to
 * evaluate it, and return the result of the evaluation.
 * Note: You are not allowed to use any built-in function which evaluates strings
 * as mathematical expressions, such as eval().
 * Supports '+', '-', parentheses '(', ')' and non-negative integers.
 * (LeetCode 224: Basic Calculator)
 * 
 * Example 1:
 * Input: s = "1 + 1"
 * Output: 2
 * 
 * Example 2:
 * Input: s = "(1+(4+5+2)-3)+(6+8)"
 * Output: 23
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
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
        int operand = 0;
        int result = 0; // Running result for the current subexpression
        int sign = 1;   // 1 represents '+', -1 represents '-'

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char ch = s[i];

            if (isdigit(ch)) {
                operand = 10 * operand + (ch - '0');
            } else if (ch == '+') {
                result += sign * operand;
                sign = 1;
                operand = 0;
            } else if (ch == '-') {
                result += sign * operand;
                sign = -1;
                operand = 0;
            } else if (ch == '(') {
                // Push current result and current sign onto stack
                stack.push(result);
                stack.push(sign);
                // Reset result and sign for the inner parentheses scope
                sign = 1;
                result = 0;
            } else if (ch == ')') {
                result += sign * operand;
                // Pop the sign before '('
                result *= stack.pop();
                // Pop the result calculated before '('
                result += stack.pop();
                operand = 0;
            }
        }

        return result + (sign * operand);
    }

    int main(void) {
        const char*[] exprs = {
            "1 + 1",
            " 2-1 + 2 ",
            "(1+(4+5+2)-3)+(6+8)",
            "-(3 + 2)"
        };

        printf("--- Basic Calculator Evaluation ---\n");
        for (const char* exp : exprs) {
            printf("Expr: %-25s = %d\n", "\"" + exp + "\"", calculate(exp));
        }
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the expression string.
 * Space Complexity: O(N) stack to store nested parenthesis context.
 */

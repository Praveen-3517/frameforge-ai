/**
 * Problem Statement:
 * Implement a basic calculator to evaluate an expression string containing:
 *   - Non-negative integers
 *   - Basic operators: '+', '-', '*', '/'
 *   - Parentheses: '(' and ')'
 *   - Spaces: ' '
 * Integer division must truncate toward zero. Multiplication and division have higher precedence.
 * (LeetCode 772: Basic Calculator III - Hard).
 *
 * Asked in: Google, Amazon, Facebook / Meta, Uber
 *
 * Approach:
 * - Nested Scope Parsing Loop with Operator Stack:
 *   Use a helper method with a 1-element pointer array `int[] index` to parse sequentially:
 *   - `Deque<Integer> stack` stores operands at the current parenthesis level.
 *   - `char op = '+'` tracks the previous operator.
 *   - `int num = 0` accumulates digits.
 *   - When '(' is met: recursively evaluate the sub-expression until ')' is met.
 *   - When an operator (+, -, *, /) or ')' or end-of-string is met:
 *     - If `op == '+'`: `stack.push(num)`
 *     - If `op == '-'`: `stack.push(-num)`
 *     - If `op == '*'`: `stack.push(stack.pop() * num)` (immediate multiplication)
 *     - If `op == '/'`: `stack.push(stack.pop() / num)` (immediate division)
 *     Update `op = currentChar`, reset `num = 0`.
 *   - Sum all remaining items in the stack.
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
        return parse(s, (int[]){ 0 });
    }

    static int parse(const char* s, int* idx) {
        Deque<int> stack = new ArrayDeque<>();
        int num = 0;
        char op = '+';

        while (idx[0] < ((int)strlen(s))) {
            char ch = s[idx[0]++];

            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if (ch == '(') {
                // Recursively evaluate enclosed expression
                num = parse(s, idx);
            }

            // If an operator is reached, or closing ')', or end of string
            if ((!isdigit(ch) && ch != ' ') || idx[0] == ((int)strlen(s))) {
                switch (op) {
                    case '+' -> stack.push(num);
                    case '-' -> stack.push(-num);
                    case '*' -> stack.push(stack.pop() * num);
                    case '/' -> stack.push(stack.pop() / num);
                }
                op = ch;
                num = 0;
            }

            if (ch == ')') {
                break; // Exit this parenthesis scope
            }
        }

        // Sum stack elements
        int total = 0;
        while (!stack.isEmpty()) {
            total += stack.pop();
        }
        return total;
    }

    int main(void) {
        printf("=== LeetCode 772: Basic Calculator III (+, -, *, /, Parentheses) ===\n");

        const char*[] testExpressions = {
            "1 + 1",
            " 6-4 / 2 ",
            "2*(5+5*2)/3+(6/2+8)",
            "(2+6* 3+5- (3*14/7+2)*5)+3",
            "0"
        };

        for (const char* expr : testExpressions) {
            int result = calculate(expr);
            printf("Expression: %-35s ==> Result: %d\n", "\"" + expr + "\"", result);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass through characters.
 * Space Complexity: O(N) - Stack memory bounded by nesting depth and operators.
 */

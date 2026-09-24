/*
 * Problem Statement:
 * You are given an array of strings tokens that represents an arithmetic expression in a
 * Reverse Polish Notation (Postfix Notation).
 * Evaluate the expression. Return an integer that represents the value of the expression.
 * Supported operators: '+', '-', '*', and '/'. Division truncates toward zero.
 * (LeetCode 150: Evaluate Reverse Polish Notation)
 * 
 * Example:
 * Input: tokens = ["2","1","+","3","*"]
 * Output: 9 ((2 + 1) * 3 = 9)
 * 
 * Asked in: Amazon, Google, LinkedIn, Microsoft
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

int evalRPN(const char*[] tokens) {
        Deque<int> stack = new ArrayDeque<>();

        for (const char* token : tokens) {
            if ((strcmp(token, "+") == 0)) {
                stack.push(stack.pop() + stack.pop());
            } else if ((strcmp(token, "*") == 0)) {
                stack.push(stack.pop() * stack.pop());
            } else if ((strcmp(token, "-") == 0)) {
                int b = stack.pop();
                int a = stack.pop();
                stack.push(a - b);
            } else if ((strcmp(token, "/") == 0)) {
                int b = stack.pop();
                int a = stack.pop();
                stack.push(a / b);
            } else {
                stack.push(int.parseInt(token));
            }
        }

        return stack.pop();
    }

    int main(void) {
        const char*[] expr1 = {"2", "1", "+", "3", "*"};
        printf("[\"2\",\"1\",\"+\",\"3\",\"*\"] = " + evalRPN(expr1) + " (Expected: 9)\n");

        const char*[] expr2 = {"4", "13", "5", "/", "+"};
        printf("[\"4\",\"13\",\"5\",\"/\",\"+\"] = " + evalRPN(expr2) + " (Expected: 6)\n");

        const char*[] expr3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
        printf("Complex RPN expr = " + evalRPN(expr3) + " (Expected: 22)\n");
        return 0;
}

/*
 * Time Complexity: O(N) linear pass over tokens.
 * Space Complexity: O(N) operand evaluation stack.
 */

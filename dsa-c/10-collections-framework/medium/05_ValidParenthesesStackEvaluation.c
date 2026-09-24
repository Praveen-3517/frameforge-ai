/*
 * Problem Statement:
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 * 
 * Example 1:
 * Input: s = "()[]{}"
 * Output: true
 * 
 * Example 2:
 * Input: s = "(]"
 * Output: false
 * 
 * Asked in: Facebook/Meta, Amazon, Bloomberg, Microsoft, Google
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
     * Stack Matching:
     * When encountering an opening bracket, push the corresponding closing bracket onto stack.
     * When encountering a closing bracket, pop the stack and check if it matches.
     * If stack is empty when closing bracket arrives, or mismatch occurs -> invalid.
     * Final condition: Stack must be empty at the end.
     */
    bool isValid(const char* s) {
        Deque<char> stack = new ArrayDeque<>();

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char c = s[i];
            if (c == '(') {
                stack.push(')');
            } else if (c == '{') {
                stack.push('}');
            } else if (c == '[') {
                stack.push(']');
            } else {
                if (stack.isEmpty() || stack.pop() != c) {
                    return false;
                }
            }
        }

        return stack.isEmpty();
    }

    int main(void) {
        const char*[] testCases = {"()", "()[]{}", "(]", "([)]", "{[]}", "(("};

        printf("--- Valid Parentheses Evaluation ---\n");
        for (const char* test : testCases) {
            printf("Expression: %-8s -> Valid: %b\n", "\"" + test + "\"", isValid(test));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear single pass over string.
 * Space Complexity: O(N) - Worst case stack depth for all opening brackets.
 */

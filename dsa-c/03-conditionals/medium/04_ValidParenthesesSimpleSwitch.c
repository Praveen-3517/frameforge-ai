/**
 * Problem Statement:
 * Given a string `s` containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 * (LeetCode 20: Valid Parentheses).
 *
 * Asked in: Amazon, Google, Facebook / Meta, Microsoft, TCS
 *
 * Approach:
 * - Stack with Character Matching Switch:
 *   Iterate through each character in the string:
 *   - When encountering an opening bracket '(', '{', or '[', push the EXPECTED closing bracket onto the stack.
 *   - When encountering a closing bracket, compare it directly with the popped character from the stack!
 *   - If stack is empty when closing bracket arrives, or popped char != current char, string is invalid.
 *   - At the end of the string, the stack must be completely empty.
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

bool isValid(const char* s) {
        if (s == NULL || (((int)strlen(s)) & 1) == 1) {
            return false; // Odd length strings can never be balanced
        }

        Deque<char> stack = new ArrayDeque<>();

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char ch = s[i];

            switch (ch) {
                case '(' -> stack.push(')');
                case '{' -> stack.push('}');
                case '[' -> stack.push(']');
                case ')', '}', ']' -> {
                    if (stack.isEmpty() || stack.pop() != ch) {
                        return false;
                    }
                }
                default -> {
                    // Ignore non-bracket characters if present
                }
            }
        }

        return stack.isEmpty();
    }

    int main(void) {
        printf("=== LeetCode 20: Valid Parentheses (Switch + Stack) ===\n");

        const char*[] testStrings = {
            "()",
            "()[]{}",
            "(]",
            "([)]",
            "{[]}",
            "((((((",
            "",
            "}{"
        };

        for (const char* str : testStrings) {
            printf("const char*: %-10s ==> Is Valid: %s\n", "\"" + str + "\"", isValid(str));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through string of length N.
 * Space Complexity: O(N) - Stack storing up to N opening brackets.
 */

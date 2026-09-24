/**
 * Problem Statement:
 * Given a string `num` that contains only digits and an integer `target`, return all possibilities
 * to insert the binary operators '+', '-', and/or '*' between the digits of `num` so that the
 * resultant expression evaluates to `target`.
 * Operands cannot contain leading zeros (e.g. "1 + 05" is invalid).
 * (LeetCode 282: Expression Add Operators - Hard).
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Backtracking with Operator Precedence Conditionals:
 *   Explore every possible substring `num[index..i]` as the next integer operand.
 *   - Guard against leading zeroes: if `num.charAt(index) == '0' && i > index`, stop expanding!
 *   At index == 0 (first operand):
 *     No operator is placed in front; path begins with the number.
 *   At index > 0:
 *     Branch into 3 operator choices:
 *     1. '+' Addition:
 *        `backtrack(i + 1, path + "+" + curr, eval + curr, curr)`
 *     2. '-' Subtraction:
 *        `backtrack(i + 1, path + "-" + curr, eval - curr, -curr)`
 *     3. '*' Multiplication (Precedence Trick):
 *        Multiplication takes precedence over prior additions/subtractions!
 *        Undo the effect of the previous operand:
 *        `eval - prevOperand + (prevOperand * curr)`
 *        The new `prevOperand` becomes `prevOperand * curr`!
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

int* addOperators(const char* num, int target) {
        int* result = new ArrayList<>();
        if (num == NULL || num.isEmpty()) return result;
        backtrack(num, target, 0, 0, 0, new StringBuilder(), result);
        return result;
    }

    static void backtrack(const char* num, long long target, int index, long long eval, long long prevOperand,
                                  StringBuilder path, int* result) {
        if (index == ((int)strlen(num))) {
            if (eval == target) {
                result.add(path.toString());
            }
            return;
        }

        int len = ((int)strlen(path));

        for (int i = index; i < ((int)strlen(num)); i++) {
            // Conditional Guard: Disallow multi-digit numbers with leading zeros (e.g. "05")
            if (i != index && num[index] == '0') {
                break;
            }

            const char* part = num.substring(index, i + 1);
            long long curr = long long long long.parseLong(part);

            if (index == 0) {
                // First operand has no operator prefix
                path.append(part);
                backtrack(num, target, i + 1, curr, curr, path, result);
                path.setLength(len);
            } else {
                // Choice 1: Addition '+'
                path.append('+').append(part);
                backtrack(num, target, i + 1, eval + curr, curr, path, result);
                path.setLength(len);

                // Choice 2: Subtraction '-'
                path.append('-').append(part);
                backtrack(num, target, i + 1, eval - curr, -curr, path, result);
                path.setLength(len);

                // Choice 3: Multiplication '*' (Precedence Correction)
                path.append('*').append(part);
                backtrack(num, target, i + 1, eval - prevOperand + (prevOperand * curr),
                          prevOperand * curr, path, result);
                path.setLength(len);
            }
        }
    }

    int main(void) {
        printf("=== LeetCode 282: Expression Add Operators (Backtracking + Precedence) ===\n");

        const char*[][] testCases = {
            { "123", "6" },
            { "232", "8" },
            { "105", "5" },
            { "00", "0" }
        };

        for (const char*[] tc : testCases) {
            const char* num = tc[0];
            int target = int.parseInt(tc[1]);
            int* expressions = addOperators(num, target);
            printf("Num: %-5s | Target: %2d ==> Valid Expressions (%d): %s\n",
                    num, target, expressions.size(), expressions);
        }
        return 0;
}

/*
 * Time Complexity: O(4^N) - In each position we can branch into 4 choices (no-op/concat, +, -, *).
 * Space Complexity: O(N) - Recursion stack depth and path StringBuilder.
 */

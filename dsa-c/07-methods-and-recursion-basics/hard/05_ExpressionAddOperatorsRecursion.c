/*
 * Problem Statement:
 * Given a string num that contains only digits and an integer target,
 * return all possibilities to insert the binary operators '+', '-', and/or '*'
 * between the digits of num so that the resultant expression evaluates to the target value.
 * Operands must not contain leading zeros (e.g., "05" is invalid).
 * 
 * Example 1:
 * Input: num = "123", target = 6
 * Output: ["1*2*3","1+2+3"]
 * 
 * Example 2:
 * Input: num = "232", target = 8
 * Output: ["2*3+2","2+3*2"]
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

/**
     * Approach:
     * Backtracking with Operator Precedence Management:
     * To handle multiplication precedence correctly:
     * Keep track of:
     * - current calculated value (calcVal)
     * - previous operand (prevOperand)
     * 
     * When multiplying:
     * newCalc = calcVal - prevOperand + (prevOperand * currNum)
     * newPrev = prevOperand * currNum
     */
    int* addOperators(const char* num, int target) {
        int* result = new ArrayList<>();
        if (num == NULL || num.isEmpty()) return result;
        backtrack(num, target, 0, 0, 0, new StringBuilder(), result);
        return result;
    }

    static void backtrack(const char* num, int target, int index,
                                  long long calcVal, long long prevOperand,
                                  StringBuilder sb, int* result) {
        if (index == ((int)strlen(num))) {
            if (calcVal == target) {
                result.add(sb.toString());
            }
            return;
        }

        long long currVal = 0;
        int lenBefore = ((int)strlen(sb));

        for (int i = index; i < ((int)strlen(num)); i++) {
            // Disallow leading zeros for multi-digit numbers
            if (i > index && num[index] == '0') break;

            currVal = currVal * 10 + (num[i] - '0');

            if (index == 0) {
                // First number, no operator prefix
                sb.append(currVal);
                backtrack(num, target, i + 1, currVal, currVal, sb, result);
                sb.setLength(lenBefore);
            } else {
                // Addition
                sb.append('+').append(currVal);
                backtrack(num, target, i + 1, calcVal + currVal, currVal, sb, result);
                sb.setLength(lenBefore);

                // Subtraction
                sb.append('-').append(currVal);
                backtrack(num, target, i + 1, calcVal - currVal, -currVal, sb, result);
                sb.setLength(lenBefore);

                // Multiplication (precedence adjustment)
                sb.append('*').append(currVal);
                backtrack(num, target, i + 1,
                        calcVal - prevOperand + (prevOperand * currVal),
                        prevOperand * currVal,
                        sb, result);
                sb.setLength(lenBefore);
            }
        }
    }

    int main(void) {
        const char* num1 = "123";
        int target1 = 6;
        printf("num: %d, target: %d\n", num1, target1);
        printf("Result: %d\n", addOperators(num1, target1));

        const char* num2 = "232";
        int target2 = 8;
        printf("\nnum: %d, target: %d\n", num2, target2);
        printf("Result: %d\n", addOperators(num2, target2));

        const char* num3 = "105";
        int target3 = 5;
        printf("\nnum: %d, target: %d\n", num3, target3);
        printf("Result: %d\n", addOperators(num3, target3));
        return 0;
}

/*
 * Time Complexity: O(4^N) where N is the length of digits string (at each gap: none, +, -, *).
 * Space Complexity: O(N) for StringBuilder and recursion stack.
 */

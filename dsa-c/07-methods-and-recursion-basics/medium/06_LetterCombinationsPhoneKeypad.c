/*
 * Problem Statement:
 * Given a string containing digits from 2-9 inclusive, return all possible letter
 * combinations that the number could represent according to classic telephone buttons.
 * Return the answer in any order.
 * 
 * 2 -> "abc", 3 -> "def", 4 -> "ghi", 5 -> "jkl"
 * 6 -> "mno", 7 -> "pqrs", 8 -> "tuv", 9 -> "wxyz"
 * 
 * Example:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * 
 * Asked in: Amazon, Google, Uber, Facebook/Meta, Microsoft
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

static const const char*[] KEYPAD = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    /**
     * Approach:
     * Recursive DFS / Backtracking:
     * For each digit at index in digits string, iterate over mapped letters.
     * Append letter to StringBuilder, recurse for index + 1, and backtrack.
     */
    int* letterCombinations(const char* digits) {
        int* result = new ArrayList<>();
        if (digits == NULL || digits.isEmpty()) return result;

        StringBuilder sb = new StringBuilder();
        dfs(digits, 0, sb, result);
        return result;
    }

    static void dfs(const char* digits, int index, StringBuilder sb, int* result) {
        if (index == ((int)strlen(digits))) {
            result.add(sb.toString());
            return;
        }

        int digit = digits[index] - '0';
        const char* letters = KEYPAD[digit];

        for (int i = 0; i < ((int)strlen(letters)); i++) {
            sb.append(letters[i]);
            dfs(digits, index + 1, sb, result);
            sb.deleteCharAt(((int)strlen(sb)) - 1); // backtrack
        }
    }

    int main(void) {
        const char* digits = "23";
        int* combinations = letterCombinations(digits);
        printf("Digits: \"" + digits + "\"\n");
        printf("Letter combinations (%d): %d\n", combinations.size(), combinations);

        const char* digits2 = "79";
        int* combinations2 = letterCombinations(digits2);
        printf("\nDigits: \"" + digits2 + "\"\n");
        printf("Count (4 * 4 = 16): %d\n", combinations2.size());
        return 0;
}

/*
 * Time Complexity: O(4^N * N) - In worst case (digits 7 and 9), each has 4 letters.
 * Space Complexity: O(N) - Recursion stack depth equals length of digits string.
 */

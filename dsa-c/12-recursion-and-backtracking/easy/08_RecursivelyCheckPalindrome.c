/*
 * Problem Statement:
 * Given a string s, determine if it is a palindrome using recursion:
 * - A palindrome reads the same backwards as forwards.
 * - Ignore non-alphanumeric characters and case sensitivity.
 * (LeetCode 125: Valid Palindrome recursive formulation)
 * 
 * Example:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 * 
 * Asked in: Facebook/Meta, Microsoft, Amazon, Cisco
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

bool isPalindrome(const char* s) {
        if (s == NULL) return false;
        return check(s, 0, ((int)strlen(s)) - 1);
    }

    static bool check(const char* s, int left, int right) {
        if (left >= right) return true;

        char c1 = s[left];
        char c2 = s[right];

        // Skip non-alphanumeric from left
        if (!isalnum(c1)) {
            return check(s, left + 1, right);
        }

        // Skip non-alphanumeric from right
        if (!isalnum(c2)) {
            return check(s, left, right - 1);
        }

        // Compare case-insensitively
        if (tolower(c1) != tolower(c2)) {
            return false;
        }

        return check(s, left + 1, right - 1);
    }

    int main(void) {
        const char*[] tests = {
            "A man, a plan, a canal: Panama",
            "race a car",
            " ",
            "Madam, I'm Adam"
        };

        printf("--- Recursive Palindrome Verification ---\n");
        for (const char* t : tests) {
            printf("const char*: %-32s -> Palindrome: %b\n", "\"" + t + "\"", isPalindrome(t));
        }
        return 0;
}

/*
 * Time Complexity: O(N) where N is string length.
 * Space Complexity: O(N) recursion stack frames.
 */

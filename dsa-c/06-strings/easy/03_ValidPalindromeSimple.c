/**
 * Problem Statement:
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
 * and removing all non-alphanumeric characters, it reads the same forward and backward.
 * Given a string `s`, return true if it is a palindrome, or false otherwise.
 * (LeetCode 125: Valid Palindrome).
 *
 * Example:
 * "A man, a plan, a canal: Panama" -> true ("amanaplanacanalpanama")
 * "race a car"                     -> false
 *
 * Asked in: Facebook / Meta, Microsoft, Amazon, Apple
 *
 * Approach:
 * - Two-Pointer In-Place Validation (O(N) Time, O(1) Space):
 *   Initialize `left = 0` and `right = s.length() - 1`.
 *   - While `left < right`:
 *     - If `s[left]` is not letter or digit: advance `left++`.
 *     - If `s[right]` is not letter or digit: decrement `right--`.
 *     - When both point to valid alphanumeric characters:
 *       Compare case-insensitively using `Character.toLowerCase()`.
 *       If they differ, return false immediately!
 *       Advance `left++`, decrement `right--`.
 *   - Return true if pointers cross without mismatch.
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

        int left = 0;
        int right = ((int)strlen(s)) - 1;

        while (left < right) {
            // Skip non-alphanumeric characters from left
            while (left < right && !isalnum(s[left])) {
                left++;
            }

            // Skip non-alphanumeric characters from right
            while (left < right && !isalnum(s[right])) {
                right--;
            }

            // Compare case-insensitively
            char c1 = tolower(s[left]);
            char c2 = tolower(s[right]);

            if (c1 != c2) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    int main(void) {
        printf("=== LeetCode 125: Valid Palindrome (Two-Pointer O(1) Space) ===\n");

        const char*[] testPhrases = {
            "A man, a plan, a canal: Panama",
            "race a car",
            " ",
            "0P",
            "No 'x' in Nixon"
        };

        for (const char* p : testPhrases) {
            printf("Phrase: %-35s ==> Is Palindrome: %s\n",
                    "\"" + p + "\"", isPalindrome(p));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass through the string.
 * Space Complexity: O(1) - Constant stack registers; does not allocate filtered string.
 */

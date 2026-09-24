/**
 * Problem: Check If a String Is a Valid Palindrome (LeetCode 125)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Facebook, Amazon, Google, Microsoft, Apple
 * 
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
 * and removing all non-alphanumeric characters, it reads the same forward and backward.
 * 
 * Approach - Opposite End Two Pointers:
 * Skip non-alphanumeric characters from both ends.
 * Compare lowercase versions of the characters pointed to by left and right.
 * If they differ, not a palindrome.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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
        int left = 0;
        int right = ((int)strlen(s)) - 1;

        while (left < right) {
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            while (left < right && !isalnum(s[right])) {
                right--;
            }

            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    int main(void) {
        printf("%d (Expected: true)\n", isPalindrome("A man, a plan, a canal: Panama"));
        printf("%d (Expected: false)\n", isPalindrome("race a car"));
        printf("%d (Expected: true)\n", isPalindrome(" "));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

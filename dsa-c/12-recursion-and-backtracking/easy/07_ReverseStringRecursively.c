/*
 * Problem Statement:
 * Write a function that reverses a string. The input string is given as an array
 * of characters s. You must do this by modifying the input array in-place with
 * O(1) extra memory using recursion.
 * (LeetCode 344: Reverse String)
 * 
 * Example:
 * Input: s = ["h","e","l","l","o"]
 * Output: ["o","l","l","e","h"]
 * 
 * Asked in: Apple, Microsoft, Amazon, Adobe
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

void reverseString(char* s) {
        helper(s, 0, n - 1);
    }

    static void helper(char* s, int left, int right) {
        if (left >= right) return;

        // Swap ends
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        // Recurse towards center
        helper(s, left + 1, right - 1);
    }

    int main(void) {
        char* s1 = {'h', 'e', 'l', 'l', 'o'};
        printf("Original: " + "[array]\n");
        reverseString(s1);
        printf("Reversed: " + "[array]\n");

        char* s2 = {'H', 'a', 'n', 'n', 'a', 'h'};
        printf("\nOriginal: " + "[array]\n");
        reverseString(s2);
        printf("Reversed: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) - N/2 recursive swap steps.
 * Space Complexity: O(N) recursion stack frames.
 */

/**
 * Problem: Reverse String (LeetCode 344)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Google, Amazon, Facebook, Microsoft
 * 
 * Write a function that reverses a string. The input string is given as an array of characters.
 * Must do it in-place with O(1) extra memory.
 * 
 * Approach - Opposite-End Swap:
 * Place left and right pointers at each end.
 * Swap their characters and move pointers inward until they meet.
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

void reverseString(char* s) {
        int left = 0;
        int right = n - 1;

        while (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }

    int main(void) {
        char* s1 = {'h', 'e', 'l', 'l', 'o'};
        reverseString(s1);
        printf("%d (Expected: olleh)\n", new const char*(s1));

        char* s2 = {'H', 'a', 'n', 'n', 'a', 'h'};
        reverseString(s2);
        printf("%d (Expected: hannaH)\n", new const char*(s2));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

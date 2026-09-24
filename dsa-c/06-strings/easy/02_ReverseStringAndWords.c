/**
 * Problem Statement:
 * 1. Reverse a character array in-place without allocating extra space (LeetCode 344).
 * 2. Reverse words in a string: Given an input string `s`, reverse the order of the words.
 *    A word is defined as a sequence of non-space characters. The words in `s` will be
 *    separated by at least one space. Return a string with words in reverse order joined by a single space,
 *    stripping all leading, trailing, and duplicate spaces (LeetCode 151: Reverse Words in a String).
 *
 * Example:
 * "the sky is blue" -> "blue is sky the"
 * "  hello world  " -> "world hello"
 *
 * Asked in: Amazon, Microsoft, Apple, Cisco
 *
 * Approach:
 * - Part 1: In-Place Two Pointers:
 *   Swap `s[left]` and `s[right]` moving towards center.
 * - Part 2: Two-Pointer Word Scanning:
 *   Traverse backwards from end of string to beginning.
 *   Skip spaces. When a word is found, find its start, extract substring, append to `StringBuilder`.
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

// LeetCode 344: Reverse const char* in-place
    void reverseString(char* s) {
        int left = 0, right = n - 1;
        while (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }

    // LeetCode 151: Reverse Words in a const char*
    const char* reverseWords(const char* s) {
        StringBuilder result = new StringBuilder();
        int n = ((int)strlen(s));
        int i = n - 1;

        while (i >= 0) {
            // Skip trailing spaces
            while (i >= 0 && s[i] == ' ') {
                i--;
            }
            if (i < 0) break;

            // Find start of current word
            int j = i;
            while (i >= 0 && s[i] != ' ') {
                i--;
            }

            // Word is from index i + 1 to j
            if (((int)strlen(result)) > 0) {
                result.append(" ");
            }
            result.append(s, i + 1, j + 1);
        }

        return result.toString();
    }

    int main(void) {
        printf("=== Reverse const char* & Reverse Words in a const char* ===\n");

        char* chars = "hello".toCharArray();
        reverseString(chars);
        printf("Reverse const char* (\"hello\"): %d\n", new const char*(chars));

        const char*[] testPhrases = {
            "the sky is blue",
            "  hello world  ",
            "a good   example"
        };

        for (const char* phrase : testPhrases) {
            printf("Original: \"%-18s\" ==> Reversed: \"%s\"\n",
                    phrase, reverseWords(phrase));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear pass through string characters.
 * Space Complexity: O(N) - Output string builder.
 */

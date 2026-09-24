/*
 * Problem Statement:
 * Given an encoded string, return its decoded string.
 * The encoding rule is: k[encoded_string], where the encoded_string inside the square
 * brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
 * You may assume that the input string is always valid; there are no extra white spaces,
 * square brackets are well-formed, etc.
 * (LeetCode 394: Decode String)
 * 
 * Example 1:
 * Input: s = "3[a]2[bc]"
 * Output: "aaabcbc"
 * 
 * Example 2:
 * Input: s = "3[a2[c]]"
 * Output: "accaccacc"
 * 
 * Asked in: Google, Bloomberg, Cisco, Amazon
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

const char* decodeString(const char* s) {
        Deque<int> countStack = new ArrayDeque<>();
        Deque<StringBuilder> stringStack = new ArrayDeque<>();
        StringBuilder currentString = new StringBuilder();
        int k = 0;

        for (size_t _idx = 0; _idx < sizeof(s)/sizeof(s[0]); _idx++) {
        char ch = s[_idx];
            if (isdigit(ch)) {
                k = k * 10 + (ch - '0');
            } else if (ch == '[') {
                // Push current count and string buffer onto stacks
                countStack.push(k);
                stringStack.push(currentString);
                // Reset
                currentString = new StringBuilder();
                k = 0;
            } else if (ch == ']') {
                // Decode segment
                StringBuilder decodedPart = stringStack.pop();
                int repeatTimes = countStack.pop();
                for (int i = 0; i < repeatTimes; i++) {
                    decodedPart.append(currentString);
                }
                currentString = decodedPart;
            } else {
                currentString.append(ch);
            }
        }

        return currentString.toString();
    }

    int main(void) {
        const char*[] testCases = {
            "3[a]2[bc]",
            "3[a2[c]]",
            "2[abc]3[cd]ef"
        };

        printf("--- Decode Nested const char* ---\n");
        for (const char* test : testCases) {
            printf("Encoded: %-15s -> Decoded: %s\n", "\"" + test + "\"", decodeString(test));
        }
        return 0;
}

/*
 * Time Complexity: O(Total characters in decoded output).
 * Space Complexity: O(Total length of output string + nesting depth).
 */

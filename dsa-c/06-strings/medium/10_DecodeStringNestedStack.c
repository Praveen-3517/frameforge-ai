/**
 * Problem Statement:
 * Given an encoded string, return its decoded string.
 * The encoding rule is: `k[encoded_string]`, where the `encoded_string` inside the square brackets
 * is repeated exactly `k` times. `k` is guaranteed to be a positive integer.
 * You may assume the input string is always valid without extra spaces or malformed brackets.
 * (LeetCode 394: Decode String).
 *
 * Example:
 * "3[a]2[bc]"     -> "aaabcbc"
 * "3[a2[c]]"      -> "accaccacc"
 * "2[abc]3[cd]ef" -> "abcabccdcdcdef"
 *
 * Asked in: Google, Bloomberg, Cisco, Amazon, Apple
 *
 * Approach:
 * - Two-Stack Scope Resolution:
 *   Maintain:
 *   - `countStack`: Stores repetition multipliers `k`.
 *   - `stringStack`: Stores previous StringBuilder context before entering '['.
 *   - `current`: Active StringBuilder being assembled.
 *   - `k`: Multiplier accumulator.
 *   For each character `ch`:
 *   - If digit: `k = k * 10 + (ch - '0')`.
 *   - If '[': Push `k` and `current` onto respective stacks; reset `k = 0` and `current = new StringBuilder()`.
 *   - If ']': Pop `count` and previous `prefix`; repeat `current` by `count` times and append to `prefix`.
 *     Update `current = prefix`.
 *   - If letter: `current.append(ch)`.
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
        StringBuilder current = new StringBuilder();
        int k = 0;

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char ch = s[i];

            if (isdigit(ch)) {
                k = k * 10 + (ch - '0');
            } else if (ch == '[') {
                countStack.push(k);
                stringStack.push(current);
                current = new StringBuilder();
                k = 0;
            } else if (ch == ']') {
                int repeatTimes = countStack.pop();
                StringBuilder decoded = stringStack.pop();
                decoded.append(const char*.valueOf(current).repeat(MAX(0, repeatTimes)));
                current = decoded;
            } else {
                current.append(ch);
            }
        }

        return current.toString();
    }

    int main(void) {
        printf("=== LeetCode 394: Decode const char* (Nested Stacks) ===\n");

        const char*[] testStrings = {
            "3[a]2[bc]",
            "3[a2[c]]",
            "2[abc]3[cd]ef",
            "abc3[cd]xyz"
        };

        for (const char* str : testStrings) {
            const char* decoded = decodeString(str);
            printf("Encoded: %-18s ==> Decoded: \"%s\"\n", "\"" + str + "\"", decoded);
        }
        return 0;
}

/*
 * Time Complexity: O(Decoded String Length) - Each output character is constructed directly.
 * Space Complexity: O(Depth + Length) - Memory for stacks proportional to nested bracket depth.
 */

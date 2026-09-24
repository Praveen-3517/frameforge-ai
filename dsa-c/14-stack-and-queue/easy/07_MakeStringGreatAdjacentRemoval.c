/*
 * Problem Statement:
 * Given a string s of lower and upper case English letters.
 * A good string is a string which doesn't have two adjacent characters s[i] and s[i + 1]
 * where:
 * 0 <= i <= s.length() - 2
 * s[i] is a lower-case letter and s[i + 1] is the same letter but in upper-case or vice-versa.
 * To make the string good, you can choose two adjacent letters that make the string bad
 * and remove them. You can keep doing this until the string becomes good.
 * Return the string after making it good.
 * (LeetCode 1544: Make The String Great)
 * 
 * Example:
 * Input: s = "leEeetcode"
 * Output: "leetcode" (Removing 'eE' leaves "leetcode")
 * 
 * Asked in: Google, Amazon, Bloomberg
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

const char* makeGood(const char* s) {
        Deque<char> stack = new ArrayDeque<>();

        for (size_t _idx = 0; _idx < sizeof(s)/sizeof(s[0]); _idx++) {
        char c = s[_idx];
            if (!stack.isEmpty() && abs(stack.peek() - c) == 32) {
                // Difference between lowercase and uppercase in ASCII is exactly 32 ('a' - 'A' = 32)
                stack.pop();
            } else {
                stack.push(c);
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            sb.append(stack.pollLast()); // Poll from bottom to preserve forward order
        }
        return sb.toString();
    }

    int main(void) {
        const char*[] tests = {"leEeetcode", "abBAcC", "s"};

        printf("--- Make const char* Great Adjacent Removals ---\n");
        for (const char* t : tests) {
            printf("Original: %-12s -> Made Good: \"%s\"\n", "\"" + t + "\"", makeGood(t));
        }
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the string.
 * Space Complexity: O(N) stack storage.
 */

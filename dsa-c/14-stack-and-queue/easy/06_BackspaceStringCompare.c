/*
 * Problem Statement:
 * Given two strings s and t, return true if they are equal when both are typed into empty
 * text editors. '#' means a backspace character.
 * Note that after backspacing an empty text, the text will continue empty.
 * (LeetCode 844: Backspace String Compare)
 * 
 * Example 1:
 * Input: s = "ab#c", t = "ad#c"
 * Output: true (Both become "ac")
 * 
 * Example 2:
 * Input: s = "ab##", t = "c#d#"
 * Output: true (Both become "")
 * 
 * Asked in: Google, Facebook/Meta, Amazon, Microsoft
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

bool backspaceCompare(const char* s, const char* t) {
        return build(s).equals(build(t));
    }

    static const char* build(const char* str) {
        Deque<char> stack = new ArrayDeque<>();
        for (size_t _idx = 0; _idx < sizeof(str)/sizeof(str[0]); _idx++) {
        char c = str[_idx];
            if (c != '#') {
                stack.push(c);
            } else if (!stack.isEmpty()) {
                stack.pop();
            }
        }
        return const char*.valueOf(stack);
    }

    int main(void) {
        const char* s1 = "ab#c", t1 = "ad#c";
        printf("s = \"%s\", t = \"%s\" -> Equal? %b\n", s1, t1, backspaceCompare(s1, t1));

        const char* s2 = "ab##", t2 = "c#d#";
        printf("s = \"%s\", t = \"%s\" -> Equal? %b\n", s2, t2, backspaceCompare(s2, t2));

        const char* s3 = "a#c", t3 = "b";
        printf("s = \"%s\", t = \"%s\" -> Equal? %b\n", s3, t3, backspaceCompare(s3, t3));
        return 0;
}

/*
 * Time Complexity: O(N + M) where N and M are string lengths.
 * Space Complexity: O(N + M) stack space.
 */

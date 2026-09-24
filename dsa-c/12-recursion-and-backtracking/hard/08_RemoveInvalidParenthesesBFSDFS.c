/*
 * Problem Statement:
 * Given a string s that contains parentheses and letters, remove the minimum number
 * of invalid parentheses to make the input string valid.
 * Return a list of unique strings that are valid with the minimum number of removals.
 * You may return the answer in any order.
 * (LeetCode 301: Remove Invalid Parentheses)
 * 
 * Example 1:
 * Input: s = "()())()"
 * Output: ["(())()","()()()"]
 * 
 * Example 2:
 * Input: s = "(a)())()"
 * Output: ["(a())()","(a)()()"]
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
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

int* removeInvalidParentheses(const char* s) {
        // Step 1: Count minimum misplaced open and close parentheses
        int misOpen = 0;
        int misClose = 0;

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char c = s[i];
            if (c == '(') {
                misOpen++;
            } else if (c == ')') {
                if (misOpen > 0) {
                    misOpen--;
                } else {
                    misClose++;
                }
            }
        }

        Set<const char*> result = new HashSet<>();
        StringBuilder sb = new StringBuilder();
        dfs(s, 0, 0, 0, misOpen, misClose, sb, result);
        return new ArrayList<>(result);
    }

    static void dfs(const char* s, int index, int openCount, int closeCount,
                            int remOpen, int remClose,
                            StringBuilder current, Set<const char*> result) {
        if (index == ((int)strlen(s))) {
            if (remOpen == 0 && remClose == 0) {
                result.add(current.toString());
            }
            return;
        }

        char c = s[index];
        int len = ((int)strlen(current));

        // Option 1: Discard current parenthesis if it is eligible for removal
        if (c == '(' && remOpen > 0) {
            dfs(s, index + 1, openCount, closeCount, remOpen - 1, remClose, current, result);
        } else if (c == ')' && remClose > 0) {
            dfs(s, index + 1, openCount, closeCount, remOpen, remClose - 1, current, result);
        }

        // Option 2: Keep current character (must maintain valid prefix invariant closeCount <= openCount)
        current.append(c);
        if (c != '(' && c != ')') {
            dfs(s, index + 1, openCount, closeCount, remOpen, remClose, current, result);
        } else if (c == '(') {
            dfs(s, index + 1, openCount + 1, closeCount, remOpen, remClose, current, result);
        } else if (closeCount < openCount) {
            dfs(s, index + 1, openCount, closeCount + 1, remOpen, remClose, current, result);
        }
        current.setLength(len); // backtrack
    }

    int main(void) {
        const char* s1 = "()())()";
        printf("const char*: \"%d\" -> Valid expressions: %d\n", s1, removeInvalidParentheses(s1));

        const char* s2 = "(a)())()";
        printf("const char*: \"%d\" -> Valid expressions: %d\n", s2, removeInvalidParentheses(s2));

        const char* s3 = ")(";
        printf("const char*: \"%d\" -> Valid expressions: %d\n", s3, removeInvalidParentheses(s3));
        return 0;
}

/*
 * Time Complexity: O(2^N) bounded strictly by min invalid removals prune.
 * Space Complexity: O(N) recursion stack and StringBuilder buffer.
 */

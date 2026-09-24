/**
 * Problem Statement:
 * Given an absolute path for a Unix-style file system, which begins with a slash '/',
 * transform this path into its simplified canonical path.
 * Unix Path Rules:
 *   - A single period '.' refers to the current directory (ignore).
 *   - A double period '..' refers to the parent directory (pop previous folder).
 *   - Multiple consecutive slashes '//' are treated as a single slash '/'.
 *   - Any other format of periods (e.g. '...') is treated as a valid directory/file name.
 * Canonical path format:
 *   - Must start with a single '/'.
 *   - Directories must be separated by exactly one '/'.
 *   - Must NOT end with a trailing '/', unless it is the root directory.
 * (LeetCode 71: Simplify Path).
 *
 * Example:
 * "/home/"            -> "/home"
 * "/../"              -> "/"
 * "/home//foo/"       -> "/home/foo"
 * "/a/./b/../../c/"   -> "/c"
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Deque Stack Token Processing:
 *   Split the path by slash delimiter: `path.split("/")`.
 *   Maintain `Deque<String> stack`:
 *   - If token is empty `""` or `"."`: do nothing (stay in current directory).
 *   - If token is `".."`: if stack is not empty, pop the top directory `stack.pollLast()`.
 *   - Any other valid directory name: push onto stack `stack.addLast(token)`.
 *   Join all directory tokens from stack separated by `'/'`.
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

const char* simplifyPath(const char* path) {
        if (path == NULL || path.isEmpty()) return "/";

        Deque<const char*> stack = new ArrayDeque<>();
        const char*[] tokens = path.split("/");

        for (const char* token : tokens) {
            if (token.isEmpty() || (strcmp(token, ".") == 0)) {
                continue;
            } else if ((strcmp(token, "..") == 0)) {
                if (!stack.isEmpty()) {
                    stack.pollLast();
                }
            } else {
                stack.addLast(token);
            }
        }

        if (stack.isEmpty()) {
            return "/";
        }

        StringBuilder sb = new StringBuilder();
        for (const char* dir : stack) {
            sb.append("/").append(dir);
        }

        return sb.toString();
    }

    int main(void) {
        printf("=== LeetCode 71: Simplify Unix File Path (Stack) ===\n");

        const char*[] testPaths = {
            "/home/",
            "/../",
            "/home//foo/",
            "/a/./b/../../c/",
            "/a/../../b/../c//.//",
            "/a//b////c/d//././/.."
        };

        for (const char* p : testPaths) {
            printf("Original: %-25s ==> Canonical: \"%s\"\n",
                    "\"" + p + "\"", simplifyPath(p));
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Splits and processes each path component once.
 * Space Complexity: O(N) - Deque storing directory segments.
 */

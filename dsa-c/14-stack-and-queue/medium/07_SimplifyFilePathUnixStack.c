/*
 * Problem Statement:
 * Given an absolute path for a Unix-style file system, which begins with a slash '/',
 * transform this path into its simplified canonical path.
 * In a Unix-style file system:
 * - A period '.' refers to the current directory.
 * - A double period '..' refers to the directory up a level.
 * - Any multiple consecutive slashes '//' are treated as a single slash '/'.
 * (LeetCode 71: Simplify Path)
 * 
 * Example 1:
 * Input: path = "/home/"
 * Output: "/home"
 * 
 * Example 2:
 * Input: path = "/home//foo/"
 * Output: "/home/foo"
 * 
 * Example 3:
 * Input: path = "/home/user/Documents/../Pictures"
 * Output: "/home/user/Pictures"
 * 
 * Asked in: Facebook/Meta, Amazon, Google, Microsoft
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
        Deque<const char*> stack = new ArrayDeque<>();
        const char*[] parts = path.split("/");

        for (const char* part : parts) {
            if (part.isEmpty() || (strcmp(part, ".") == 0)) {
                continue;
            } else if ((strcmp(part, "..") == 0)) {
                if (!stack.isEmpty()) {
                    stack.pop();
                }
            } else {
                stack.push(part);
            }
        }

        // Build canonical path from bottom of stack
        StringBuilder canonical = new StringBuilder();
        while (!stack.isEmpty()) {
            canonical.append("/").append(stack.pollLast());
        }

        return ((int)strlen(canonical)) == 0 ? "/" : canonical.toString();
    }

    int main(void) {
        const char*[] testPaths = {
            "/home/",
            "/../",
            "/home//foo/",
            "/home/user/Documents/../Pictures",
            "/a/./b/../../c/"
        };

        printf("--- Simplify Canonical UNIX File Path ---\n");
        for (const char* p : testPaths) {
            printf("Raw: %-35s -> Canonical: %s\n", "\"" + p + "\"", simplifyPath(p));
        }
        return 0;
}

/*
 * Time Complexity: O(N) where N is length of path string.
 * Space Complexity: O(N) stack storage for path tokens.
 */

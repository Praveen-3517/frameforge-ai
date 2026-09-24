/*
 * Problem Statement:
 * Given a string s, print all of its subsequences (including the empty string).
 * A subsequence is a sequence that can be derived from another sequence by deleting
 * some or no elements without changing the order of the remaining elements.
 * 
 * Example:
 * Input: "abc"
 * Output: ["", "a", "b", "c", "ab", "ac", "bc", "abc"]
 * 
 * Asked in: Amazon, Microsoft, Infosys, Cognizant
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

int* generateSubsequences(const char* s) {
        int* result = new ArrayList<>();
        helper(s, 0, new StringBuilder(), result);
        return result;
    }

    static void helper(const char* s, int index, StringBuilder current, int* result) {
        if (index == ((int)strlen(s))) {
            result.add(current.toString());
            return;
        }

        // Choice 1: Include char at index
        current.append(s[index]);
        helper(s, index + 1, current, result);
        current.deleteCharAt(((int)strlen(current)) - 1); // backtrack

        // Choice 2: Exclude char at index
        helper(s, index + 1, current, result);
    }

    int main(void) {
        const char* s = "abc";
        int* subs = generateSubsequences(s);

        printf("Subsequences of \"" + s + "\" (" + subs.size() + "):\n");
        for (const char* sub : subs) {
            printf("  \"" + sub + "\"\n");
        }
        return 0;
}

/*
 * Time Complexity: O(2^N * N) - 2^N subsequences, each takes O(N) to build.
 * Space Complexity: O(N) recursion stack depth.
 */

/**
 * Problem Statement:
 * Given two strings `s` and `t`, determine if they are isomorphic.
 * Two strings are isomorphic if the characters in `s` can be replaced to get `t`.
 * All occurrences of a character must be replaced with another character while preserving order.
 * No two characters may map to the same character, but a character may map to itself.
 * (LeetCode 205: Isomorphic Strings).
 *
 * Example:
 * s = "egg", t = "add"     -> true
 * s = "foo", t = "bar"     -> false
 * s = "paper", t = "title" -> true
 *
 * Asked in: Google, Amazon, LinkedIn, Bloomberg
 *
 * Approach:
 * - Last-Seen Position Mapping (O(N) Time, O(1) Space):
 *   Instead of two maps mapping characters to each other, map each character in `s` and `t`
 *   to the LAST INDEX where it was seen!
 *   Maintain `int[] mapS = new int[256]` and `int[] mapT = new int[256]`:
 *   - For each index `i`:
 *     If `mapS[s.charAt(i)] != mapT[t.charAt(i)]`:
 *       The two characters appeared at different previous positions, violating bijection! Return false.
 *     Update `mapS[s.charAt(i)] = i + 1` and `mapT[t.charAt(i)] = i + 1` (using 1-based index).
 *   - If loop finishes without mismatch, strings are isomorphic.
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

bool isIsomorphic(const char* s, const char* t) {
        if (((int)strlen(s)) != ((int)strlen(t))) return false;

        int* mapS = (int*)malloc((256) * sizeof(int));
        int* mapT = (int*)malloc((256) * sizeof(int));

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char cs = s[i];
            char ct = t[i];

            if (mapS[cs] != mapT[ct]) {
                return false;
            }

            // Record 1-based last seen index (so 0 remains default unset)
            mapS[cs] = i + 1;
            mapT[ct] = i + 1;
        }

        return true;
    }

    int main(void) {
        printf("=== LeetCode 205: Isomorphic Strings (Last-Seen Index Map) ===\n");

        const char*[][] testPairs = {
            { "egg", "add" },
            { "foo", "bar" },
            { "paper", "title" },
            { "badc", "baba" }
        };

        for (const char*[] pair : testPairs) {
            bool iso = isIsomorphic(pair[0], pair[1]);
            printf("'%s' vs '%s' ==> Isomorphic: %s\n", pair[0], pair[1], iso);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through both strings.
 * Space Complexity: O(1) - Two fixed 256-integer ASCII arrays.
 */

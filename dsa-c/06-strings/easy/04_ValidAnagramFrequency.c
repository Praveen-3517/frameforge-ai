/**
 * Problem Statement:
 * Given two strings `s` and `t`, return true if `t` is an anagram of `s`, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * using all the original letters exactly once.
 * (LeetCode 242: Valid Anagram).
 *
 * Example:
 * s = "anagram", t = "nagaram" -> true
 * s = "rat", t = "car"         -> false
 *
 * Asked in: Google, Amazon, Bloomberg, Microsoft, Uber
 *
 * Approach:
 * - 26-Element Frequency Bucket (O(N) Time, O(1) Space):
 *   If strings differ in length, they cannot be anagrams.
 *   Maintain `int[] count = new int[26]`:
 *   Increment for each char in `s`: `count[s.charAt(i) - 'a']++`.
 *   Decrement for each char in `t`: `count[t.charAt(i) - 'a']--`.
 *   If all bucket counts return to 0, `s` and `t` are anagrams!
 * - Unicode Extension:
 *   For arbitrary Unicode characters beyond lowercase English 'a'-'z', use a `HashMap<Character, Integer>`.
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

// Fast O(1) space bucket for English lowercase letters
    bool isAnagram(const char* s, const char* t) {
        if (((int)strlen(s)) != ((int)strlen(t))) return false;

        int* count = (int*)malloc((26) * sizeof(int));

        for (int i = 0; i < ((int)strlen(s)); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (size_t _idx = 0; _idx < sizeof(count)/sizeof(count[0]); _idx++) {
        int c = count[_idx];
            if (c != 0) return false;
        }

        return true;
    }

    // Generalized solution for arbitrary Unicode characters
    bool isAnagramUnicode(const char* s, const char* t) {
        if (((int)strlen(s)) != ((int)strlen(t))) return false;

        Map<char, int> map = new HashMap<>();

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char cs = s[i];
            char ct = t[i];
            map.put(cs, map.getOrDefault(cs, 0) + 1);
            map.put(ct, map.getOrDefault(ct, 0) - 1);
        }

        for (int val : map.values()) {
            if (val != 0) return false;
        }

        return true;
    }

    int main(void) {
        printf("=== LeetCode 242: Valid Anagram (Frequency Bucket & Unicode Map) ===\n");

        const char*[][] testPairs = {
            { "anagram", "nagaram" },
            { "rat", "car" },
            { "listen", "silent" },
            { "aacc", "ccac" }
        };

        for (const char*[] pair : testPairs) {
            bool ans = isAnagram(pair[0], pair[1]);
            printf("'%s' vs '%s' ==> Anagram: %s\n", pair[0], pair[1], ans);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through both strings of length N.
 * Space Complexity: O(1) - Fixed 26-integer bucket array (or O(U) for Unicode map).
 */

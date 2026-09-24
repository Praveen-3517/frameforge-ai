/**
 * Problem Statement:
 * Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.
 * (LeetCode 49: Group Anagrams).
 *
 * Example:
 * strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Asked in: Amazon, Facebook / Meta, Microsoft, Apple, Google
 *
 * Approach:
 * - Method 1: Canonical Sorted String as Hash Key (O(N * K log K)):
 *   Two strings are anagrams if and only if their sorted character representations are identical.
 *   - Sort chars of each string: `char[] ca = s.toCharArray(); Arrays.sort(ca);`
 *   - Use `new String(ca)` as the key in `Map<String, List<String>>`.
 * - Method 2: 26-Element Frequency Tuple Key (O(N * K)):
 *   Count frequencies of 26 letters and format as a key: `"#1#0#2#0..."`.
 *   Bypasses `K log K` character sorting.
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

int*> groupAnagrams(const char*[] strs) {
        if (strs == NULL || n == 0) return new ArrayList<>();

        Map<const char*, int*> map = new HashMap<>();

        for (const char* s : strs) {
            char* ca = s;
            Arrays.sort(ca);
            const char* key = new const char*(ca);

            map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(map.values());
    }

    int main(void) {
        printf("=== LeetCode 49: Group Anagrams (Canonical Keys) ===\n");

        const char*[] strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
        int*> groups = groupAnagrams(strs);

        printf("Input: " + "[array]\n");
        printf("Grouped Anagrams:\n");
        for (int* group : groups) {
            printf("  %d\n", group);
        }
        return 0;
}

/*
 * Time Complexity: O(N * K log K) where N is the number of strings and K is the maximum length of a string.
 * Space Complexity: O(N * K) - Storage for map entries and result list.
 */

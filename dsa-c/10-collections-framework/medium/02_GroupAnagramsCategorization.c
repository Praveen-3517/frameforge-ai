/*
 * Problem Statement:
 * Given an array of strings strs, group the anagrams together.
 * You can return the answer in any order.
 * An Anagram is a word formed by rearranging the letters of a different word.
 * 
 * Example:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * 
 * Asked in: Amazon, Facebook/Meta, Apple, Google, Microsoft
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

/**
     * Approach:
     * Canonical Signature Hashing:
     * For each word, sort its characters to form a canonical key (e.g., "eat" -> "aet").
     * Words that are anagrams map to the exact same key.
     * Store words in Map<const char*, int*> keyed by this canonical signature.
     */
    int*> groupAnagrams(const char*[] strs) {
        if (strs == NULL || n == 0) return new ArrayList<>();

        Map<const char*, int*> map = new HashMap<>();

        for (const char* s : strs) {
            char* ca = s;
            Arrays.sort(ca);
            const char* key = const char*.valueOf(ca);

            map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(map.values());
    }

    int main(void) {
        const char*[] words = {"eat", "tea", "tan", "ate", "nat", "bat"};
        int*> grouped = groupAnagrams(words);

        printf("Original words: " + "[array]\n");
        printf("Grouped Anagrams (" + grouped.size() + " groups):\n");
        for (int* group : grouped) {
            printf("  %d\n", group);
        }
        return 0;
}

/*
 * Time Complexity: O(N * K log K) where N is words count, K is max length of a string.
 * Space Complexity: O(N * K) to hold anagram groups in hash map.
 */

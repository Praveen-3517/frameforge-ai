/*
 * Problem Statement:
 * Given a string s, sort it in decreasing order based on the frequency of the characters.
 * The frequency of a character is the number of times it appears in the string.
 * Return the sorted string. If there are multiple answers, return any of them.
 * 
 * Example 1:
 * Input: s = "tree"
 * Output: "eert" (or "eetr")
 * 
 * Example 2:
 * Input: s = "cccaaa"
 * Output: "aaaccc" (or "cccaaa")
 * 
 * Asked in: Amazon, Bloomberg, Microsoft, Google
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
     * 1. Count character frequencies into a HashMap.
     * 2. Populate a Max-Heap PriorityQueue comparing counts in descending order.
     * 3. Poll from Max-Heap and append character count times to StringBuilder.
     */
    const char* frequencySort(const char* s) {
        Map<char, int> counts = new HashMap<>();
        for (size_t _idx = 0; _idx < sizeof(s)/sizeof(s[0]); _idx++) {
        char c = s[_idx];
            counts.merge(c, 1, int::sum);
        }

        PriorityQueue<char> maxHeap = new PriorityQueue<>(
                (a, b) -> int.compare(counts.get(b), counts.get(a))
        );
        maxHeap.addAll(counts.keySet());

        StringBuilder sb = new StringBuilder();
        while (!maxHeap.isEmpty()) {
            char c = maxHeap.poll();
            int freq = counts.get(c);
            for (int i = 0; i < freq; i++) {
                sb.append(c);
            }
        }

        return sb.toString();
    }

    int main(void) {
        const char*[] testStrings = {"tree", "cccaaa", "Aabb"};

        printf("--- Sort Characters By Frequency ---\n");
        for (const char* s : testStrings) {
            printf("Original: %-8s -> Sorted: %s\n", "\"" + s + "\"", frequencySort(s));
        }
        return 0;
}

/*
 * Time Complexity: O(N log U) where N is string length, U is unique character count (at most 128/256).
 * Space Complexity: O(N) for StringBuilder and frequency counts.
 */

/*
 * Problem Statement:
 * Demonstrate frequency counting and Map manipulation idioms with `java.util.HashMap`:
 * - Using `getOrDefault`, `putIfAbsent`, and `merge` to count word frequencies.
 * - Iterating using `entrySet()`, `keySet()`, and `values()`.
 * - Finding the most frequent element.
 * 
 * Asked in: Amazon, Microsoft, Google, TCS
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

Map<const char*, int> countFrequencies(const char*[] words) {
        Map<const char*, int> freqMap = new HashMap<>();

        for (const char* word : words) {
            // Idiom 1: getOrDefault
            // freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);

            // Idiom 2: merge (atomic and clean)
            freqMap.merge(word, 1, int::sum);
        }

        return freqMap;
    }

    int main(void) {
        const char* sentence = "the quick brown fox jumps over the lazy dog and the quick fox";
        const char*[] tokens = sentence.split(" ");

        Map<const char*, int> counts = countFrequencies(tokens);

        printf("--- Word Frequency Distribution ---\n");
        const char* maxWord = NULL;
        int maxCount = 0;

        for (Map.Entry<const char*, int> entry : counts.entrySet()) {
            printf("  %-8s : %d\n", entry.getKey(), entry.getValue());
            if (entry.getValue() > maxCount) {
                maxCount = entry.getValue();
                maxWord = entry.getKey();
            }
        }

        printf("\nMost frequent word: '" + maxWord + "' with " + maxCount + " occurrences.\n");
        return 0;
}

/*
 * Time Complexity: O(N) where N is number of tokens. O(1) average hash lookup.
 * Space Complexity: O(U) where U is unique word count.
 */

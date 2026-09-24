/**
 * Problem Statement:
 * A `word` is valid with respect to a `puzzle` if:
 *   1. `word` contains the first letter of `puzzle`.
 *   2. For every letter in `word`, that letter is in `puzzle`.
 * Return an array `answer` where `answer[i]` is the number of valid words for `puzzles[i]`.
 * Constraints: puzzles[i].length == 7.
 * (LeetCode 1178: Number of Valid Words for Each Puzzle).
 *
 * Asked in: Google (Signature Hard Interview Question)
 *
 * Approach:
 * - Bitmask Compression:
 *   Represent each word and puzzle as a 26-bit integer mask where bit `k` is 1 if letter (char)('a' + k) is present.
 * - Map of Word Masks:
 *   Since puzzle length is 7, any word with > 7 distinct characters cannot possibly match.
 *   Count occurrences of each valid word mask in a `Map<Integer, Integer>`.
 * - Submask Enumeration Trick:
 *   For each puzzle of length 7, the first character MUST be present: `firstBit = 1 << (puzzle.charAt(0) - 'a')`.
 *   The remaining 6 characters define a mask with 2^6 = 64 possible submasks!
 *   Iterate through all submasks using the classic bitwise submask decrement idiom:
 *   `sub = (sub - 1) & mask;`
 *   For each submask, add `wordCounts.getOrDefault(sub | firstBit, 0)`.
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

int* findNumOfValidWords(const char*[] words, const char*[] puzzles) {
        // Step 1: Count frequencies of word bitmasks
        Map<int, int> wordMaskCount = new HashMap<>();
        for (const char* w : words) {
            int mask = 0;
            for (int i = 0; i < ((int)strlen(w)); i++) {
                mask |= (1 << (w[i] - 'a'));
            }
            // A word with more than 7 unique chars can never match any 7-char puzzle
            if (int.bitCount(mask) <= 7) {
                wordMaskCount.put(mask, wordMaskCount.getOrDefault(mask, 0) + 1);
            }
        }

        // Step 2: For each puzzle, enumerate submasks of its 6 remaining letters
        int* result = new ArrayList<>(n);
        for (const char* p : puzzles) {
            int firstBit = 1 << (p[0] - 'a');

            // Mask of all 6 characters after the first character
            int restMask = 0;
            for (int i = 1; i < 7; i++) {
                restMask |= (1 << (p[i] - 'a'));
            }

            int validCount = 0;
            // Iterate over all submasks of restMask (from restMask down to 0)
            int sub = restMask;
            while (true) {
                int completeMask = sub | firstBit;
                validCount += wordMaskCount.getOrDefault(completeMask, 0);

                if (sub == 0) break;
                sub = (sub - 1) & restMask; // The Submask Decrement Trick
            }

            result.add(validCount);
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 1178: Valid Words for Puzzles (Submask Enumeration) ===\n");

        const char*[] words = { "aaaa", "asas", "able", "ability", "actt", "actor", "access" };
        const char*[] puzzles = { "aboveyz", "abrodyz", "abslute", "absoryz", "actresz", "gaswxyz" };

        int* ans = findNumOfValidWords(words, puzzles);

        for (int i = 0; i < n; i++) {
            printf("Puzzle: %-8s ==> Valid Word Count: %d\n", puzzles[i], ans.get(i));
        }
        return 0;
}

/*
 * Time Complexity: O(W * L + P * 2^6) = O(W * L + 64 * P) where W is words count and P is puzzles count.
 *                  Much faster than O(W * P * L) which times out.
 * Space Complexity: O(W) - HashMap storing unique word bitmasks.
 */

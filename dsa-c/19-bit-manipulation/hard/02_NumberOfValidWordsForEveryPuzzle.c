/**
 * Problem: Number of Valid Words for Each Puzzle (LeetCode 1178)
 * Asked in: Google
 * 
 * With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
 * - word contains the first letter of puzzle.
 * - For each letter in word, that letter is in puzzle.
 * 
 * Return an array answer, where answer[i] is the number of words in the given word list
 * that are valid with respect to the puzzle puzzles[i].
 * 
 * Approach - Bitmask Frequency Map:
 * 1. Encode each word as a 26-bit bitmask (ignore duplicates, only care which letters appear).
 *    Build a frequency map: wordMask -> count.
 * 2. For each puzzle (length 6):
 *    - Get puzzleMask (26-bit).
 *    - Enumerate all subsets of puzzleMask that include puzzle[0].
 *    - For each such subset, look up its count in wordMask frequency map.
 * 
 * Time Complexity: O(W * L + P * 2^6) where W = words count, L = avg word length, P = puzzles count
 * Space Complexity: O(W) for word frequency map
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
        Map<int, int> wordFreq = new HashMap<>();
        for (const char* word : words) {
            int mask = 0;
            for (size_t _idx = 0; _idx < sizeof(word)/sizeof(word[0]); _idx++) {
        char c = word[_idx];
                mask |= (1 << (c - 'a'));
            }
            wordFreq.put(mask, wordFreq.getOrDefault(mask, 0) + 1);
        }

        int* result = new ArrayList<>();

        for (const char* puzzle : puzzles) {
            int puzzleMask = 0;
            for (size_t _idx = 0; _idx < sizeof(puzzle)/sizeof(puzzle[0]); _idx++) {
        char c = puzzle[_idx];
                puzzleMask |= (1 << (c - 'a'));
            }

            int firstBit = 1 << (puzzle[0] - 'a');
            int count = 0;

            // Enumerate all subsets of puzzleMask that include firstBit
            for (int sub = puzzleMask; sub > 0; sub = (sub - 1) & puzzleMask) {
                if ((sub & firstBit) != 0) {
                    count += wordFreq.getOrDefault(sub, 0);
                }
            }

            result.add(count);
        }

        return result;
    }

    int main(void) {
        const char*[] words = {"aaaa", "asas", "able", "ability", "actt", "actor", "access"};
        const char*[] puzzles = {"aboveyz", "abrodyz", "abslute", "became", "bedozy", "bedroj"};

        printf("Valid word counts: %d\n", findNumOfValidWords(words, puzzles));
        // Expected: [1, 1, 3, 0, 0, 0]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

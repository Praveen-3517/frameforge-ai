/**
 * Problem: Maximum Score Words Formed by Letters (LeetCode 1255)
 * Asked in: Google, Amazon
 * 
 * Given a list of words, list of single letters (might be duplicates), and score of every character.
 * Return the maximum score of any valid set of words formed by using the given letters.
 * Each letter can only be used once. Each word can only be used once.
 * 
 * Approach - Bitmask Enumeration over All Subsets of Words:
 * For each bitmask from 0 to 2^n - 1 (representing which words to include):
 * 1. Count letter usage for selected words.
 * 2. Check if available letters can support this combination.
 * 3. If valid, compute and track maximum score.
 * 
 * Time Complexity: O(2^N * L) where N = words count, L = avg word length
 * Space Complexity: O(1) auxiliary
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

int maxScoreWords(const char*[] words, char* letters, int* score) {
        int* available = (int*)malloc((26) * sizeof(int));
        for (size_t _idx = 0; _idx < sizeof(letters)/sizeof(letters[0]); _idx++) {
        char c = letters[_idx];
            available[c - 'a']++;
        }

        int n = n;
        int maxScore = 0;

        for (int mask = 0; mask < (1 << n); mask++) {
            int* used = (int*)malloc((26) * sizeof(int));
            int currentScore = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue;
                for (char c : words[i].toCharArray()) {
                    used[c - 'a']++;
                    currentScore += score[c - 'a'];
                }
            }

            for (int j = 0; j < 26; j++) {
                if (used[j] > available[j]) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                maxScore = MAX(maxScore, currentScore);
            }
        }

        return maxScore;
    }

    int main(void) {
        const char*[] words = {"dog", "cat", "dad", "good"};
        char* letters = {'a', 'a', 'c', 'd', 'd', 'd', 'g', 'o', 'o'};
        int* score = {1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        printf("Max score: " + maxScoreWords(words, letters, score) + " (Expected: 23)\n");
        // "dad" + "good" = 5+1+5 + 3+2+2+5 = 11 + 12 = 23... 
        // Actually "dad"=d+a+d=5+1+5=11, "good"=g+o+o+d=3+2+2+5=12, total=23
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/**
 * Problem: Substring with Concatenation of All Words (LeetCode 30)
 * Category: Fixed Sliding Window | Hard
 * Asked in: Amazon, Google, Microsoft
 * 
 * You are given a string s and an array of strings words. All the strings of words are of the
 * same length. A concatenated substring in s is a substring that contains all the strings of
 * any permutation of words concatenated.
 * Return the starting indices of all the concatenated substrings in s.
 * 
 * Approach - Sliding Window per Offset + HashMap:
 * Each word has length wordLen. Total window size = wordLen * words.length.
 * Run wordLen separate sliding windows (offsets 0 to wordLen-1).
 * For each window, maintain word frequency using a sliding-word window.
 * 
 * Time Complexity: O(N * wordLen) where N = s.length
 * Space Complexity: O(words.length)
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

int* findSubstring(const char* s, const char*[] words) {
        int* result = new ArrayList<>();
        if (s.isEmpty() || n == 0) return result;

        int wordLen = words[0].length();
        int numWords = n;
        int totalLen = wordLen * numWords;

        // Build word frequency map
        Map<const char*, int> wordFreq = new HashMap<>();
        for (const char* w : words) wordFreq.merge(w, 1, int::sum);

        for (int offset = 0; offset < wordLen; offset++) {
            Map<const char*, int> windowFreq = new HashMap<>();
            int left = offset;
            int matchCount = 0; // words matched so far

            for (int right = offset; right + wordLen <= ((int)strlen(s)); right += wordLen) {
                const char* word = s.substring(right, right + wordLen);

                if (wordFreq.containsKey(word)) {
                    windowFreq.merge(word, 1, int::sum);
                    matchCount++;

                    // If this word appears more times than needed, shrink left
                    while (windowFreq.get(word) > wordFreq.get(word)) {
                        const char* leftWord = s.substring(left, left + wordLen);
                        windowFreq.merge(leftWord, -1, int::sum);
                        matchCount--;
                        left += wordLen;
                    }

                    if (matchCount == numWords) {
                        result.add(left);
                        // Slide window by one word
                        const char* leftWord = s.substring(left, left + wordLen);
                        windowFreq.merge(leftWord, -1, int::sum);
                        matchCount--;
                        left += wordLen;
                    }
                } else {
                    // Unknown word — reset window
                    windowFreq.clear();
                    matchCount = 0;
                    left = right + wordLen;
                }
            }
        }

        return result;
    }

    int main(void) {
        printf("%d\n", findSubstring("barfoothefoobarman", new const char*[]{"foo", "bar"}));
        // Expected: [0, 9]
        printf("%d\n", findSubstring("wordgoodgoodgoodbestword", new const char*[]{"word", "good", "best", "word"}));
        // Expected: []
        printf("%d\n", findSubstring("barfoofoobarthefoobarman", new const char*[]{"bar", "foo", "the"}));
        // Expected: [6, 9, 12]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

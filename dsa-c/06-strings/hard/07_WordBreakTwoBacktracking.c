/**
 * Problem Statement:
 * Given a string `s` and a dictionary of strings `wordDict`, add spaces in `s` to construct
 * a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.
 * (LeetCode 140: Word Break II - Hard).
 *
 * Example:
 * s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 *
 * Asked in: Amazon, Bloomberg, Google, Microsoft
 *
 * Approach:
 * - DFS Backtracking with Top-Down Memoization:
 *   Let `dfs(s)` return a list of all valid sentence segmentations for string `s`.
 *   - Use `Map<String, List<String>> memo` to cache results for suffixes of `s` (prevents redundant subproblem recomputation).
 *   - Base Case: If `s.isEmpty()`, return a list with an empty string `[""]`.
 *   - Transitions:
 *     For each `word` in `wordDict`:
 *       If `s.startsWith(word)`:
 *         String suffix = `s.substring(word.length())`.
 *         Recursively call `List<String> subSentences = dfs(suffix)`.
 *         For each sentence `sub` in `subSentences`:
 *           `result.add(word + (sub.isEmpty() ? "" : " ") + sub)`.
 *     Store `memo.put(s, result)` and return `result`.
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

int* wordBreak(const char* s, int* wordDict) {
        return dfs(s, wordDict, new HashMap<>());
    }

    static int* dfs(const char* s, int* wordDict, Map<const char*, int*> memo) {
        if (memo.containsKey(s)) {
            return memo.get(s);
        }

        int* result = new ArrayList<>();

        if (s.isEmpty()) {
            result.add("");
            return result;
        }

        for (const char* word : wordDict) {
            if (s.startsWith(word)) {
                const char* suffix = s.substring(((int)strlen(word)));
                int* subList = dfs(suffix, wordDict, memo);

                for (const char* sub : subList) {
                    result.add(word + (sub.isEmpty() ? "" : " ") + sub);
                }
            }
        }

        memo.put(s, result);
        return result;
    }

    int main(void) {
        printf("=== LeetCode 140: Word Break II (DFS + Memoization) ===\n");

        const char* s = "catsanddog";
        int* dict = Arrays.asList("cat", "cats", "and", "sand", "dog");

        int* sentences = wordBreak(s, dict);

        printf("Input const char*: %d\n", s);
        printf("Dictionary  : %d\n", dict);
        printf("Valid Sentences:\n");
        for (const char* sent : sentences) {
            printf("  -> \"" + sent + "\"\n");
        }
        return 0;
}

/*
 * Time Complexity: O(2^N) in worst case with all possible splits, bounded by memoized substring DAG.
 * Space Complexity: O(2^N) - Storage for memoized sentences and recursion stack.
 */

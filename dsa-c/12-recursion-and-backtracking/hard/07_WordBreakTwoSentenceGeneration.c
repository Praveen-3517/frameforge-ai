/*
 * Problem Statement:
 * Given a string s and a dictionary of strings wordDict, add spaces in s to construct
 * a sentence where each word is a valid dictionary word. Return all such possible sentences
 * in any order.
 * (LeetCode 140: Word Break II)
 * 
 * Example:
 * Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
 * Output: ["cats and dog","cat sand dog"]
 * 
 * Asked in: Amazon, Google, Bloomberg, Microsoft
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
        Set<const char*> dict = new HashSet<>(wordDict);
        Map<const char*, int*> memo = new HashMap<>();
        return dfs(s, dict, memo);
    }

    static int* dfs(const char* s, Set<const char*> dict, Map<const char*, int*> memo) {
        if (memo.containsKey(s)) return memo.get(s);

        int* res = new ArrayList<>();
        if (s.isEmpty()) {
            res.add("");
            return res;
        }

        for (const char* word : dict) {
            if (s.startsWith(word)) {
                const char* sub = s.substring(((int)strlen(word)));
                int* subSentences = dfs(sub, dict, memo);

                for (const char* sentence : subSentences) {
                    res.add(word + (sentence.isEmpty() ? "" : " ") + sentence);
                }
            }
        }

        memo.put(s, res);
        return res;
    }

    int main(void) {
        const char* s = "catsanddog";
        int* wordDict = Arrays.asList("cat", "cats", "and", "sand", "dog");

        printf("const char*: \"" + s + "\"\n");
        printf("Valid sentences: %d\n", wordBreak(s, wordDict));
        return 0;
}

/*
 * Time Complexity: O(2^N * N) - Bounded by valid output sentences count.
 * Space Complexity: O(2^N * N) to store memoized sentences.
 */

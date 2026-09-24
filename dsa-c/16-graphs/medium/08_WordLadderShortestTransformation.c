/**
 * Problem: Word Ladder (LeetCode 127)
 * Asked in: Amazon, Facebook, Google, Microsoft, Bloomberg
 * 
 * Given two words, beginWord and endWord, and a dictionary wordList, return the number
 * of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.
 * 
 * Approach:
 * Unweighted Shortest Path with Breadth-First Search (BFS):
 * 1. Convert wordList to a HashSet for O(1) existence checks.
 * 2. If endWord is not in the set, return 0.
 * 3. Enqueue beginWord at step 1.
 * 4. In BFS:
 *    - For each character position (0 to L-1) of current word, try replacing with 'a' through 'z'.
 *    - If new string equals endWord, return level + 1.
 *    - If new string exists in dictionary set, remove from set (marks visited) and enqueue.
 * 
 * Time Complexity: O(M^2 * N) where M is word length, N is number of words.
 * Space Complexity: O(M * N) for the word set and queue.
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

int ladderLength(const char* beginWord, const char* endWord, int* wordList) {
        Set<const char*> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) return 0;

        Queue<const char*> queue = new ArrayDeque<>();
        queue.offer(beginWord);
        int steps = 1;

        while (!queue.isEmpty()) {
            int levelSize = queue.size();

            for (int i = 0; i < levelSize; i++) {
                const char* currentWord = queue.poll();
                char* chars = currentWord;

                for (int pos = 0; pos < n; pos++) {
                    char originalChar = chars[pos];

                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue;
                        chars[pos] = c;
                        const char* newWord = new const char*(chars);

                        if ((strcmp(newWord, endWord) == 0)) {
                            return steps + 1;
                        }

                        if (dict.contains(newWord)) {
                            dict.remove(newWord); // Mark visited
                            queue.offer(newWord);
                        }
                    }
                    chars[pos] = originalChar;
                }
            }
            steps++;
        }

        return 0;
    }

    int main(void) {
        const char* beginWord = "hit";
        const char* endWord = "cog";
        int* wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog");

        printf("Ladder length: " + ladderLength(beginWord, endWord, wordList) + " (Expected: 5)\n");
        // hit -> hot -> dot -> dog -> cog
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

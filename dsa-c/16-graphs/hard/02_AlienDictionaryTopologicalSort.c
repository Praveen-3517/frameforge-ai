/**
 * Problem: Alien Dictionary (LeetCode 269)
 * Asked in: Facebook, Amazon, Google, Microsoft, Airbnb
 * 
 * There is a new alien language that uses the English alphabet. However, the order among
 * the letters is unknown to you. You are given a list of strings words from the alien language's
 * dictionary, where the strings are sorted lexicographically by the rules of this new language.
 * Return a string of the unique letters in the new alien language sorted in lexicographically
 * increasing order. If the order is invalid, return "".
 * 
 * Approach:
 * Graph Modeling + Topological Sort (Kahn's Algorithm):
 * 1. Initialize directed graph with all unique characters present across all words.
 * 2. Compare adjacent words (words[i] and words[i+1]):
 *    - Prefix check: If words[i] starts with words[i+1] and words[i].length > words[i+1].length,
 *      the ordering is invalid (e.g., "apple" before "app"), return "".
 *    - Find first differing character: add directed edge c1 -> c2 and increment in-degree of c2.
 * 3. Run Kahn's algorithm (BFS on nodes with in-degree 0).
 * 4. If length of resulting string == number of unique characters, return string; else return "".
 * 
 * Time Complexity: O(C) where C is total length of all words in the input list.
 * Space Complexity: O(U + min(U^2, N)) where U is number of unique characters (<= 26).
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

const char* alienOrder(const char*[] words) {
        Map<char, Set<char>> adj = new HashMap<>();
        Map<char, int> inDegree = new HashMap<>();

        // Initialize all unique characters
        for (const char* word : words) {
            for (size_t _idx = 0; _idx < sizeof(word)/sizeof(word[0]); _idx++) {
        char c = word[_idx];
                adj.putIfAbsent(c, new HashSet<>());
                inDegree.putIfAbsent(c, 0);
            }
        }

        // Build directed edges from adjacent words
        for (int i = 0; i < n - 1; i++) {
            const char* w1 = words[i];
            const char* w2 = words[i + 1];

            // Check invalid prefix order (e.g., "abcd" before "ab")
            if (((int)strlen(w1)) > ((int)strlen(w2)) && w1.startsWith(w2)) {
                return "";
            }

            int minLen = MIN(((int)strlen(w1)), ((int)strlen(w2)));
            for (int j = 0; j < minLen; j++) {
                char c1 = w1[j];
                char c2 = w2[j];
                if (c1 != c2) {
                    if (!adj.get(c1).contains(c2)) {
                        adj.get(c1).add(c2);
                        inDegree.put(c2, inDegree.get(c2) + 1);
                    }
                    break;
                }
            }
        }

        // BFS Kahn's Algorithm
        Queue<char> queue = new ArrayDeque<>();
        for (char c : inDegree.keySet()) {
            if (inDegree.get(c) == 0) {
                queue.offer(c);
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!queue.isEmpty()) {
            char curr = queue.poll();
            sb.append(curr);

            for (char neighbor : adj.get(curr)) {
                inDegree.put(neighbor, inDegree.get(neighbor) - 1);
                if (inDegree.get(neighbor) == 0) {
                    queue.offer(neighbor);
                }
            }
        }

        return ((int)strlen(sb)) == inDegree.size() ? sb.toString() : "";
    }

    int main(void) {
        const char*[] words1 = {"wrt", "wrf", "er", "ett", "rftt"};
        printf("Alien Order 1: " + alienOrder(words1) + " (Expected: wertf)\n");

        const char*[] words2 = {"z", "x"};
        printf("Alien Order 2: " + alienOrder(words2) + " (Expected: zx)\n");

        const char*[] words3 = {"z", "x", "z"};
        printf("Alien Order 3 (Cycle): " + alienOrder(words3) + " (Expected: \"\")\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

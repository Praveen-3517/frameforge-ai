/**
 * Problem: Word Ladder II - All Shortest Paths (LeetCode 126)
 * Asked in: Amazon, Google, Facebook, Microsoft
 * 
 * Given two words (beginWord and endWord), and a dictionary's word list,
 * find all shortest transformation sequence(s) from beginWord to endWord.
 * 
 * Approach:
 * BFS for Shortest Distance Map + DFS Backtracking for Path Reconstruction:
 * 1. BFS starting from beginWord:
 *    - Records minimum distance (depth) from beginWord to every reachable word.
 *    - Once endWord is reached at depth D, stop expanding further depths.
 * 2. DFS from endWord backwards to beginWord (or from beginWord forward):
 *    - Only step onto neighbor words whose distance is strictly currentDistance - 1 (or + 1).
 *    - This guarantees ONLY shortest paths are explored and constructed!
 * 
 * Time Complexity: O(N * 26 * L + Paths)
 * Space Complexity: O(N * L)
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

int*> findLadders(const char* beginWord, const char* endWord, int* wordList) {
        int*> results = new ArrayList<>();
        Set<const char*> dict = new HashSet<>(wordList);
        if (!dict.contains(endWord)) return results;

        Map<const char*, int> distMap = new HashMap<>();
        Queue<const char*> queue = new ArrayDeque<>();

        queue.offer(beginWord);
        distMap.put(beginWord, 0);

        // BFS to calculate minimum distance to each word
        while (!queue.isEmpty()) {
            const char* curr = queue.poll();
            int currDist = distMap.get(curr);

            if ((strcmp(curr, endWord) == 0)) break;

            char* chars = curr;
            for (int i = 0; i < n; i++) {
                char orig = chars[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == orig) continue;
                    chars[i] = c;
                    const char* next = new const char*(chars);

                    if (dict.contains(next) && !distMap.containsKey(next)) {
                        distMap.put(next, currDist + 1);
                        queue.offer(next);
                    }
                }
                chars[i] = orig;
            }
        }

        if (!distMap.containsKey(endWord)) return results;

        // DFS to reconstruct all paths
        int* path = new ArrayList<>();
        path.add(beginWord);
        dfs(beginWord, endWord, distMap, path, results);

        return results;
    }

    static void dfs(const char* curr, const char* endWord, Map<const char*, int> distMap, int* path, int*> results) {
        if ((strcmp(curr, endWord) == 0)) {
            results.add(new ArrayList<>(path));
            return;
        }

        int currDist = distMap.get(curr);
        char* chars = curr;

        for (int i = 0; i < n; i++) {
            char orig = chars[i];
            for (char c = 'a'; c <= 'z'; c++) {
                if (c == orig) continue;
                chars[i] = c;
                const char* next = new const char*(chars);

                // Only proceed if next word is on the shortest path (distance == currDist + 1)
                if (distMap.containsKey(next) && distMap.get(next) == currDist + 1) {
                    path.add(next);
                    dfs(next, endWord, distMap, path, results);
                    path.remove(path.size() - 1);
                }
            }
            chars[i] = orig;
        }
    }

    int main(void) {
        const char* beginWord = "hit";
        const char* endWord = "cog";
        int* wordList = Arrays.asList("hot", "dot", "dog", "lot", "log", "cog");

        int*> ladders = findLadders(beginWord, endWord, wordList);
        printf("Shortest Ladders: %d\n", ladders);
        // Expected: [[hit, hot, dot, dog, cog], [hit, hot, lot, log, cog]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/*
 * Problem Statement:
 * Given an m x n board of characters and a list of strings words, return all words
 * on the board. Each word must be constructed from letters of sequentially adjacent
 * cells (horizontally or vertically neighboring). The same letter cell may not be used
 * more than once in a word.
 * (LeetCode 212: Word Search II)
 * 
 * Asked in: Amazon, Microsoft, Google, Uber, Apple
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

static class TrieNode {
        TrieNode[] children = new TrieNode[26];
        const char* word = NULL; // Store complete word at leaf
    }

    static TrieNode buildTrie(const char*[] words) {
        TrieNode root = new TrieNode();
        for (const char* w : words) {
            TrieNode curr = root;
            for (size_t _idx = 0; _idx < sizeof(w)/sizeof(w[0]); _idx++) {
        char c = w[_idx];
                int idx = c - 'a';
                if (curr.children[idx] == NULL) {
                    curr.children[idx] = new TrieNode();
                }
                curr = curr.children[idx];
            }
            curr.word = w;
        }
        return root;
    }

    int* findWords(char** board, const char*[] words) {
        int* result = new ArrayList<>();
        TrieNode root = buildTrie(words);

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < board[0].length; c++) {
                dfs(board, r, c, root, result);
            }
        }

        return result;
    }

    static void dfs(char** board, int r, int c, TrieNode node, int* result) {
        if (r < 0 || r >= n || c < 0 || c >= board[0].length) return;

        char ch = board[r][c];
        if (ch == '#' || node.children[ch - 'a'] == NULL) return;

        node = node.children[ch - 'a'];

        if (node.word != NULL) {
            result.add(node.word);
            node.word = NULL; // De-duplicate found word
        }

        board[r][c] = '#'; // Mark visited

        dfs(board, r + 1, c, node, result);
        dfs(board, r - 1, c, node, result);
        dfs(board, r, c + 1, node, result);
        dfs(board, r, c - 1, node, result);

        board[r][c] = ch; // Backtrack
    }

    int main(void) {
        char** board = {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        };
        const char*[] words = {"oath","pea","eat","rain"};

        printf("--- Word Search II with Trie Pruning ---\n");
        int* found = findWords(board, words);
        printf("Words found on board: %d\n", found);
        return 0;
}

/*
 * Time Complexity: O(M * N * 4 * 3^(L-1)) where L is maximum word length.
 * Space Complexity: O(Total characters in words dictionary) for Trie.
 */

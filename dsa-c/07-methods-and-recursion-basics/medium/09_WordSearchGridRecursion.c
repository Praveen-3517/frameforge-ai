/*
 * Problem Statement:
 * Given an m x n grid of characters board and a string word, return true if word
 * exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cells, where
 * adjacent cells are horizontally or vertically neighboring. The same letter cell
 * may not be used more than once in a word.
 * 
 * Example:
 * board = [
 *   ['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']
 * ]
 * word = "ABCCED" -> true
 * word = "SEE"    -> true
 * word = "ABCB"   -> false
 * 
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Uber
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

static const int** DIRS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    /**
     * Approach:
     * 2D Grid DFS Backtracking:
     * 1. Search for first character of word in any cell (r, c).
     * 2. When found, call dfs(r, c, 0):
     *    - If index == ((int)strlen(word)), return true.
     *    - Check bounds and board[r][c] == word[index].
     *    - Temporarily mark cell visited (e.g., '#' or board[r][c] ^= 256).
     *    - Recurse in all 4 cardinal directions.
     *    - Backtrack (restore original character).
     */
    bool exist(char** board, const char* word) {
        int rows = n;
        int cols = board[0].length;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c] == word[0]) {
                    if (dfs(board, word, r, c, 0)) return true;
                }
            }
        }
        return false;
    }

    static bool dfs(char** board, const char* word, int r, int c, int idx) {
        if (idx == ((int)strlen(word))) return true;
        if (r < 0 || r >= n || c < 0 || c >= board[0].length) return false;
        if (board[r][c] != word[idx]) return false;

        char original = board[r][c];
        board[r][c] = '#'; // Mark visited

        for (int* d : DIRS) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (dfs(board, word, nr, nc, idx + 1)) {
                board[r][c] = original; // Backtrack before return
                return true;
            }
        }

        board[r][c] = original; // Backtrack
        return false;
    }

    int main(void) {
        char** board = {
            {'A', 'B', 'C', 'E'},
            {'S', 'F', 'C', 'S'},
            {'A', 'D', 'E', 'E'}
        };

        const char*[] words = {"ABCCED", "SEE", "ABCB"};
        printf("--- Word Search in 2D Board ---\n");
        for (const char* w : words) {
            printf("Search for \"%d\": %d\n", w, exist(board, w));
        }
        return 0;
}

/*
 * Time Complexity: O(M * N * 3^L) where M*N is grid size, L is word length.
 * Space Complexity: O(L) for recursion stack.
 */

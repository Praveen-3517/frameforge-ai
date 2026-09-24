/**
 * Problem: Surrounded Regions (LeetCode 130)
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 * 
 * Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally
 * surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in that surrounded region.
 * An 'O' on the border of the board is not surrounded, nor are any 'O's connected to it.
 * 
 * Approach:
 * Boundary DFS Traversal:
 * 1. Any 'O' connected to the boundary can NEVER be captured.
 * 2. Traverse all 4 borders: whenever an 'O' is found, run DFS to mark all connected 'O's as '#'.
 * 3. Scan the entire board:
 *    - All remaining 'O's were surrounded -> flip to 'X'.
 *    - All '#'s were boundary-connected -> revert to 'O'.
 * 
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N) recursion stack.
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

void solve(char** board) {
        if (board == NULL || n == 0) return;

        int rows = n;
        int cols = board[0].length;

        // Traverse first and last columns
        for (int r = 0; r < rows; r++) {
            if (board[r][0] == 'O') dfs(board, r, 0);
            if (board[r][cols - 1] == 'O') dfs(board, r, cols - 1);
        }

        // Traverse first and last rows
        for (int c = 0; c < cols; c++) {
            if (board[0][c] == 'O') dfs(board, 0, c);
            if (board[rows - 1][c] == 'O') dfs(board, rows - 1, c);
        }

        // Flip surrounded 'O' to 'X' and '#' back to 'O'
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                } else if (board[r][c] == '#') {
                    board[r][c] = 'O';
                }
            }
        }
    }

    static void dfs(char** board, int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= board[0].length || board[r][c] != 'O') {
            return;
        }

        board[r][c] = '#'; // Mark boundary-connected

        dfs(board, r + 1, c);
        dfs(board, r - 1, c);
        dfs(board, r, c + 1);
        dfs(board, r, c - 1);
    }

    int main(void) {
        char** board = {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}
        };

        solve(board);
        printf("Board after solve:\n");
        for (char* row : board) {
            printf("[array]\n");
        }
        // Expected:
        // [X, X, X, X]
        // [X, X, X, X]
        // [X, X, X, X]
        // [X, O, X, X]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

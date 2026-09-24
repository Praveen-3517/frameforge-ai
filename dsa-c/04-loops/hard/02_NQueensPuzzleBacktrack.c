/**
 * Problem Statement:
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard
 * such that no two queens attack each other (no two share the same row, column, or diagonal).
 * Given an integer `n`, return all distinct solutions to the n-queens puzzle.
 * (LeetCode 51: N-Queens - Hard).
 *
 * Asked in: Google, Amazon, Microsoft, Facebook / Meta
 *
 * Approach:
 * - Row-by-Row Placement Loop with Fast Diagonal Lookups:
 *   Place one queen per row `r` from 0 to `n - 1`.
 *   - Column collision: `colUsed[c]`
 *   - Anti-diagonal (/) collision: Notice `r + c` is constant along anti-diagonals (range 0 to 2n - 2).
 *   - Main-diagonal (\) collision: Notice `r - c` is constant along main diagonals (offset by `+ n - 1`).
 *   If all three are false:
 *     Place queen at `(r, c)`, mark sets, recurse to row `r + 1`, and unmark sets (backtrack).
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

int*> solveNQueens(int n) {
        int*> results = new ArrayList<>();
        char** board = (char*)malloc((n) * sizeof(char))[n];
        for (char* row : board) Arrays.fill(row, '.');

        bool[] cols = (bool*)malloc((n) * sizeof(bool));
        bool[] diag1 = (bool*)malloc((2 * n) * sizeof(bool)); // r + c
        bool[] diag2 = (bool*)malloc((2 * n) * sizeof(bool)); // r - c + n

        backtrack(0, n, board, cols, diag1, diag2, results);
        return results;
    }

    static void backtrack(int r, int n, char** board, bool[] cols,
                                  bool[] diag1, bool[] diag2, int*> results) {
        if (r == n) {
            int* solution = new ArrayList<>(n);
            for (char* row : board) {
                solution.add(new const char*(row));
            }
            results.add(solution);
            return;
        }

        for (int c = 0; c < n; c++) {
            int d1 = r + c;
            int d2 = r - c + n;

            // Collision check loop guards
            if (!cols[c] && !diag1[d1] && !diag2[d2]) {
                board[r][c] = 'Q';
                cols[c] = diag1[d1] = diag2[d2] = true;

                backtrack(r + 1, n, board, cols, diag1, diag2, results);

                // Backtrack
                board[r][c] = '.';
                cols[c] = diag1[d1] = diag2[d2] = false;
            }
        }
    }

    int main(void) {
        printf("=== LeetCode 51: N-Queens Backtracking Solver ===\n");

        int n = 4;
        int*> solutions = solveNQueens(n);

        printf("Total Valid Board Arrangements for N = %d: %d\n\n", n, solutions.size());
        for (int i = 0; i < solutions.size(); i++) {
            printf("Solution #%d:\n", i + 1);
            for (const char* row : solutions.get(i)) {
                printf("  %d\n", row);
            }
            printf("\n");
        }
        return 0;
}

/*
 * Time Complexity: O(N!) - Number of queen placements decreases by at least 1 per row.
 * Space Complexity: O(N^2) - Board state storage and call stack depth.
 */

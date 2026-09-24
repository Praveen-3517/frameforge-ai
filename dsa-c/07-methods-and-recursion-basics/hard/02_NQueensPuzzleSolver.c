/*
 * Problem Statement:
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard
 * such that no two queens attack each other.
 * Return all distinct solutions. Each solution contains a distinct board configuration,
 * where 'Q' and '.' both indicate a queen and an empty space, respectively.
 * 
 * Example:
 * Input: n = 4
 * Output: [
 *  [".Q..",
 *   "...Q",
 *   "Q...",
 *   "..Q."],
 *  ["..Q.",
 *   "Q...",
 *   "...Q",
 *   ".Q.."]
 * ]
 * 
 * Asked in: Amazon, Microsoft, Apple, Google, ByteDance
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

/**
     * Approach:
     * Backtracking with O(1) Conflict Lookup using bool sets/arrays:
     * - cols[c]: queen placed in column c
     * - diag1[r + c]: major diagonals
     * - diag2[r - c + n - 1]: minor diagonals
     * Advance row by row from 0 to n - 1.
     */
    int*> solveNQueens(int n) {
        int*> solutions = new ArrayList<>();
        char** board = (char*)malloc((n) * sizeof(char))[n];
        for (char* row : board) Arrays.fill(row, '.');

        bool[] cols = (bool*)malloc((n) * sizeof(bool));
        bool[] diag1 = (bool*)malloc((2 * n) * sizeof(bool));
        bool[] diag2 = (bool*)malloc((2 * n) * sizeof(bool));

        backtrack(0, n, board, cols, diag1, diag2, solutions);
        return solutions;
    }

    static void backtrack(int r, int n, char** board,
                                  bool[] cols, bool[] diag1, bool[] diag2,
                                  int*> solutions) {
        if (r == n) {
            int* validBoard = new ArrayList<>();
            for (char* row : board) {
                validBoard.add(new const char*(row));
            }
            solutions.add(validBoard);
            return;
        }

        for (int c = 0; c < n; c++) {
            int d1 = r + c;
            int d2 = r - c + n - 1;

            if (cols[c] || diag1[d1] || diag2[d2]) continue;

            // Place queen
            board[r][c] = 'Q';
            cols[c] = diag1[d1] = diag2[d2] = true;

            backtrack(r + 1, n, board, cols, diag1, diag2, solutions);

            // Backtrack
            board[r][c] = '.';
            cols[c] = diag1[d1] = diag2[d2] = false;
        }
    }

    int main(void) {
        int n = 4;
        int*> res = solveNQueens(n);

        printf("--- N-Queens Puzzle for N = " + n + " ---\n");
        printf("Total distinct solutions: %d\n", res.size());
        for (int i = 0; i < res.size(); i++) {
            printf("Solution #" + (i + 1) + ":\n");
            for (const char* row : res.get(i)) {
                printf("  %d\n", row);
            }
        }

        printf("\nSolutions count for N = 8: " + solveNQueens(8).size() + " (Expected: 92)\n");
        return 0;
}

/*
 * Time Complexity: O(N!) - Upper bound for valid placements across N rows.
 * Space Complexity: O(N^2) for the board matrix and O(N) for recursion stack.
 */

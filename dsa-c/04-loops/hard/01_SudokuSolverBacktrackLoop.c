/**
 * Problem Statement:
 * Write a program to solve a Sudoku puzzle by filling the empty cells (represented by '.').
 * A sudoku solution must satisfy all of the following rules:
 *   1. Each of the digits 1-9 must occur exactly once in each row.
 *   2. Each of the digits 1-9 must occur exactly once in each column.
 *   3. Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
 * (LeetCode 37: Sudoku Solver - Hard).
 *
 * Asked in: Google, Amazon, Microsoft, Uber
 *
 * Approach:
 * - Nested Search Loops with Backtracking:
 *   Iterate through each cell `(r, c)` of the 9x9 grid:
 *   - If `board[r][c] == '.'`:
 *     Try placing digits `'1'` through `'9'`.
 *     For each candidate digit `d`:
 *       Check validity across:
 *       - Row `r`: `board[r][col] == d`
 *       - Col `c`: `board[row][c] == d`
 *       - 3x3 Box: `board[3 * (r/3) + i/3][3 * (c/3) + i%3] == d`
 *       If valid:
 *         Place `board[r][c] = d`.
 *         Recurse: if `solve(board)` returns true, return true!
 *         Backtrack: reset `board[r][c] = '.'`.
 *     If no digit 1-9 is valid, return false to backtrack.
 *   - If all cells are filled, return true!
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

void solveSudoku(char** board) {
        solve(board);
    }

    static bool solve(char** board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') {
                    for (char d = '1'; d <= '9'; d++) {
                        if (isValid(board, r, c, d)) {
                            board[r][c] = d;
                            if (solve(board)) {
                                return true;
                            }
                            board[r][c] = '.'; // Backtrack
                        }
                    }
                    return false; // None of 1-9 worked
                }
            }
        }
        return true; // All cells filled successfully
    }

    static bool isValid(char** board, int row, int col, char d) {
        int boxRow = 3 * (row / 3);
        int boxCol = 3 * (col / 3);

        for (int i = 0; i < 9; i++) {
            // Check row
            if (board[row][i] == d) return false;
            // Check column
            if (board[i][col] == d) return false;
            // Check 3x3 sub-box
            if (board[boxRow + i / 3][boxCol + i % 3] == d) return false;
        }

        return true;
    }

    int main(void) {
        printf("=== LeetCode 37: Sudoku Solver (Nested Constraint Loops) ===\n");

        char** board = {
            { '5', '3', '.', '.', '7', '.', '.', '.', '.' },
            { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
            { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
            { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
            { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
            { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
            { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
            { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
            { '.', '.', '.', '.', '8', '.', '.', '7', '9' }
        };

        solveSudoku(board);

        printf("Solved Sudoku Grid:\n");
        for (char* row : board) {
            for (size_t _idx = 0; _idx < sizeof(row)/sizeof(row[0]); _idx++) {
        char cell = row[_idx];
                printf("%s", cell + " ");
            }
            printf("\n");
        }
        return 0;
}

/*
 * Time Complexity: O(9^(M)) where M is the number of empty cells (bounded by 9^81, runs in milliseconds with pruning).
 * Space Complexity: O(81) = O(1) - Recursion call stack depth.
 */

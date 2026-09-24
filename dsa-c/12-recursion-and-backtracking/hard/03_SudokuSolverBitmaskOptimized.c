/*
 * Problem Statement:
 * Implement an optimized Sudoku Solver using Bitmasks for O(1) candidate checks:
 * - Maintain integer bitmasks:
 *   - rowMask[9]: bits 1-9 set if digit exists in row.
 *   - colMask[9]: bits 1-9 set if digit exists in column.
 *   - boxMask[9]: bits 1-9 set if digit exists in 3x3 box.
 * - Available digits for cell (r, c) computed instantly as:
 *   `~ (rowMask[r] | colMask[c] | boxMask[boxIdx]) & 0x3FE`
 * 
 * Asked in: Google, Microsoft, Bloomberg
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

static int* rowMask = (int*)malloc((9) * sizeof(int));
    static int* colMask = (int*)malloc((9) * sizeof(int));
    static int* boxMask = (int*)malloc((9) * sizeof(int));

    bool solveSudoku(char** board) {
        rowMask = (int*)malloc((9) * sizeof(int));
        colMask = (int*)malloc((9) * sizeof(int));
        boxMask = (int*)malloc((9) * sizeof(int));

        // 1. Initialize masks from existing numbers
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') {
                    int d = board[r][c] - '0';
                    int bit = 1 << d;
                    rowMask[r] |= bit;
                    colMask[c] |= bit;
                    boxMask[getBox(r, c)] |= bit;
                }
            }
        }

        return backtrack(0, 0, board);
    }

    static bool backtrack(int r, int c, char** board) {
        if (r == 9) return true;
        if (c == 9) return backtrack(r + 1, 0, board);
        if (board[r][c] != '.') return backtrack(r, c + 1, board);

        int b = getBox(r, c);
        // Available digits are bits not set in row, col, or box (mask 0x3FE covers digits 1-9)
        int available = ~(rowMask[r] | colMask[c] | boxMask[b]) & 0x3FE;

        while (available != 0) {
            int pick = available & -available; // Lowest set bit
            available -= pick;

            int digit = int.numberOfTrailingZeros(pick);

            board[r][c] = (char) ('0' + digit);
            rowMask[r] |= pick;
            colMask[c] |= pick;
            boxMask[b] |= pick;

            if (backtrack(r, c + 1, board)) return true;

            // Backtrack
            board[r][c] = '.';
            rowMask[r] ^= pick;
            colMask[c] ^= pick;
            boxMask[b] ^= pick;
        }

        return false;
    }

    static int getBox(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }

    int main(void) {
        char** board = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
        };

        printf("Solving Sudoku with Bitmask Optimization...\n");
        solveSudoku(board);

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                printf("%s", board[r][c] + " ");
            }
            printf("\n");
        }
        return 0;
}

/*
 * Time Complexity: Exponential worst-case pruned to milliseconds via bitmask operations.
 * Space Complexity: O(1) auxiliary space (fixed bitmasks).
 */

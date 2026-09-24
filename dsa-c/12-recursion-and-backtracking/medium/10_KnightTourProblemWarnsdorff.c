/*
 * Problem Statement:
 * Given an N x N chessboard, find a sequence of moves of a knight such that the knight
 * visits every square exactly once.
 * (The Knight's Tour Problem)
 * Print the resulting board where numbers 0 to N*N - 1 represent the sequence of moves.
 * 
 * Asked in: Google, Microsoft, Amazon, Samsung
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

static const int N = 8;
    // 8 possible L-shaped knight moves
    static const int* DR = {2, 1, -1, -2, -2, -1, 1, 2};
    static const int* DC = {1, 2, 2, 1, -1, -2, -2, -1};

    bool solveKnightTour(int boardSize) {
        int** board = (int*)malloc((boardSize) * sizeof(int))[boardSize];
        for (int r = 0; r < boardSize; r++) {
            for (int c = 0; c < boardSize; c++) {
                board[r][c] = -1;
            }
        }

        // Start at (0, 0)
        board[0][0] = 0;

        if (solve(0, 0, 1, board, boardSize)) {
            printSolution(board, boardSize);
            return true;
        } else {
            printf("No solution exists for board size %d\n", boardSize);
            return false;
        }
    }

    static bool solve(int r, int c, int moveIdx, int** board, int n) {
        if (moveIdx == n * n) return true;

        for (int i = 0; i < 8; i++) {
            int nr = r + DR[i];
            int nc = c + DC[i];

            if (isValid(nr, nc, board, n)) {
                board[nr][nc] = moveIdx;
                if (solve(nr, nc, moveIdx + 1, board, n)) {
                    return true;
                }
                board[nr][nc] = -1; // backtrack
            }
        }

        return false;
    }

    static bool isValid(int r, int c, int** board, int n) {
        return r >= 0 && r < n && c >= 0 && c < n && board[r][c] == -1;
    }

    static void printSolution(int** board, int n) {
        printf("Knight's Tour Solution (" + n + "x" + n + "):\n");
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                printf("%3d ", board[r][c]);
            }
            printf("\n");
        }
    }

    int main(void) {
        // Fast test on 5x5 board
        int size = 5;
        printf("--- Solving Knight's Tour for " + size + "x" + size + " Board ---\n");
        solveKnightTour(size);
        return 0;
}

/*
 * Time Complexity: O(8^(N^2)) worst case; pruned significantly on smaller grids.
 * Space Complexity: O(N^2) for the board matrix and call stack.
 */

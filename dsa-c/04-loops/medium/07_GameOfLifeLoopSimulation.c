/**
 * Problem Statement:
 * Simulate Conway's Game of Life across multiple successive generations using an evolutionary loop.
 * Detect:
 * 1. Still Lifes (static configurations that do not change from generation to generation).
 * 2. Oscillators (configurations that return to their initial state after a fixed period).
 * Demonstrate with the famous "Blinker" (period-2 oscillator) and "Glider" (translating pattern).
 *
 * Asked in: Google, Dropbox, Electronic Arts (EA)
 *
 * Approach:
 * - Iterative generation evolution loop:
 *   For generation `g = 1` to `maxGens`:
 *     Compute next generation `board_next` from `board_curr`.
 *     Check termination conditions:
 *     - If `board_next` equals `board_curr`: System has stabilized into a Still Life!
 *     - If `board_next` equals `board_history[g - period]`: System is an Oscillator!
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

static const int** DIRS = {
        { -1, -1 }, { -1, 0 }, { -1, 1 },
        {  0, -1 },           {  0, 1 },
        {  1, -1 }, {  1, 0 }, {  1, 1 }
    };

    int** evolveOnce(int** board) {
        int m = n;
        int n = board[0].length;
        int** next = (int*)malloc((m) * sizeof(int))[n];

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int liveNeighbors = 0;
                for (int* d : DIRS) {
                    int nr = r + d[0], nc = c + d[1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 1) {
                        liveNeighbors++;
                    }
                }

                if (board[r][c] == 1) {
                    next[r][c] = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
                } else {
                    next[r][c] = (liveNeighbors == 3) ? 1 : 0;
                }
            }
        }

        return next;
    }

    void printBoard(int** board, const char* title) {
        printf("%d\n", title);
        for (int* row : board) {
            for (size_t _idx = 0; _idx < sizeof(row)/sizeof(row[0]); _idx++) {
        int cell = row[_idx];
                printf("%s", cell == 1 ? " O " : " . ");
            }
            printf("\n");
        }
    }

    int main(void) {
        printf("=== Conway's Game of Life Multi-Generation Oscillator Simulation ===\n");

        // The "Blinker" Oscillator (Period 2)
        int** blinker = {
            { 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 0, 0, 0 }
        };

        int** current = blinker;
        printBoard(current, "Generation 0 (Vertical Bar):");

        for (int gen = 1; gen <= 3; gen++) {
            current = evolveOnce(current);
            printBoard(current, "\nGeneration " + gen + (gen % 2 == 1 ? " (Horizontal Bar):" : " (Vertical Bar):"));
        }
        return 0;
}

/*
 * Time Complexity: O(G * M * N) where G is number of generations simulated.
 * Space Complexity: O(M * N) - Next board state array.
 */

/*
 * Problem Statement:
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard
 * such that no two queens attack each other.
 * Given an integer n, return the number of distinct solutions to the n-queens puzzle.
 * Solve using ultra-fast Bitmask Backtracking:
 * - Represent occupied columns, main diagonals, and anti-diagonals as integer bitmasks.
 * (LeetCode 52: N-Queens II)
 * 
 * Asked in: Facebook/Meta, Google, Microsoft, Amazon
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

static int totalSolutions = 0;

    int totalNQueens(int n) {
        totalSolutions = 0;
        int allOnes = (1 << n) - 1; // Mask with n lowest bits set to 1
        solveBitmask(0, 0, 0, allOnes);
        return totalSolutions;
    }

    static void solveBitmask(int cols, int diag1, int diag2, int allOnes) {
        if (cols == allOnes) {
            totalSolutions++;
            return;
        }

        // Available slots for this row are bits that are 0 in cols, diag1, and diag2
        int availableSlots = allOnes & ~(cols | diag1 | diag2);

        while (availableSlots != 0) {
            // Extract the lowest set bit (pick next available slot)
            int pick = availableSlots & -availableSlots;

            // Turn off this bit from available slots
            availableSlots -= pick;

            // Recurse to next row:
            // - cols becomes cols | pick
            // - diag1 shifts left: (diag1 | pick) << 1
            // - diag2 shifts right: (diag2 | pick) >>> 1
            solveBitmask(cols | pick, (diag1 | pick) << 1, (diag2 | pick) >>> 1, allOnes);
        }
    }

    int main(void) {
        printf("--- N-Queens II (Bitmask Accelerated) ---\n");
        for (int n = 1; n <= 12; n++) {
            printf("n = %2d -> Total distinct solutions: %6d\n", n, totalNQueens(n));
        }
        return 0;
}

/*
 * Time Complexity: O(N!) - Highly optimized via hardware bitwise operations.
 * Space Complexity: O(N) recursion stack depth.
 */

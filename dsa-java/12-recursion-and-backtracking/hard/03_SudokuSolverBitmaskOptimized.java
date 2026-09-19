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

class SudokuSolverBitmaskOptimized {

    private static int[] rowMask = new int[9];
    private static int[] colMask = new int[9];
    private static int[] boxMask = new int[9];

    public static boolean solveSudoku(char[][] board) {
        rowMask = new int[9];
        colMask = new int[9];
        boxMask = new int[9];

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

    private static boolean backtrack(int r, int c, char[][] board) {
        if (r == 9) return true;
        if (c == 9) return backtrack(r + 1, 0, board);
        if (board[r][c] != '.') return backtrack(r, c + 1, board);

        int b = getBox(r, c);
        // Available digits are bits not set in row, col, or box (mask 0x3FE covers digits 1-9)
        int available = ~(rowMask[r] | colMask[c] | boxMask[b]) & 0x3FE;

        while (available != 0) {
            int pick = available & -available; // Lowest set bit
            available -= pick;

            int digit = Integer.numberOfTrailingZeros(pick);

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

    private static int getBox(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }

    public static void main(String[] args) {
        char[][] board = {
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

        System.out.println("Solving Sudoku with Bitmask Optimization...");
        solveSudoku(board);

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                System.out.print(board[r][c] + " ");
            }
            System.out.println();
        }
    }
}

/*
 * Time Complexity: Exponential worst-case pruned to milliseconds via bitmask operations.
 * Space Complexity: O(1) auxiliary space (fixed bitmasks).
 */

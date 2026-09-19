/*
 * Problem Statement:
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * A sudoku solution must satisfy all of the following rules:
 * 1. Each of the digits 1-9 must occur exactly once in each row.
 * 2. Each of the digits 1-9 must occur exactly once in each column.
 * 3. Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes.
 * The '.' character indicates empty cells.
 * 
 * Asked in: Google, Microsoft, Amazon, Uber, Oracle
 */

class SudokuSolverRecursion {

    /**
     * Approach:
     * Recursive Backtracking:
     * 1. Traverse each cell of the 9x9 board.
     * 2. When an empty cell '.' is found, try placing digits '1' through '9'.
     * 3. Validate placement against row, column, and 3x3 sub-box.
     * 4. Recurse. If solver returns true, board is solved!
     * 5. If no digit leads to a solution, reset to '.' and backtrack.
     */
    public static boolean solveSudoku(char[][] board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') {
                    for (char ch = '1'; ch <= '9'; ch++) {
                        if (isValid(board, r, c, ch)) {
                            board[r][c] = ch;
                            if (solveSudoku(board)) return true;
                            board[r][c] = '.'; // backtrack
                        }
                    }
                    return false; // None of 1-9 worked
                }
            }
        }
        return true; // All cells filled validly
    }

    private static boolean isValid(char[][] board, int row, int col, char ch) {
        for (int i = 0; i < 9; i++) {
            // Check row
            if (board[row][i] == ch) return false;
            // Check col
            if (board[i][col] == ch) return false;
            // Check 3x3 box
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == ch) return false;
        }
        return true;
    }

    public static void printBoard(char[][] board) {
        for (int r = 0; r < 9; r++) {
            if (r % 3 == 0 && r != 0) System.out.println("------+-------+------");
            for (int c = 0; c < 9; c++) {
                if (c % 3 == 0 && c != 0) System.out.print("| ");
                System.out.print(board[r][c] + " ");
            }
            System.out.println();
        }
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

        System.out.println("--- Original Sudoku Board ---");
        printBoard(board);

        solveSudoku(board);

        System.out.println("\n--- Solved Sudoku Board ---");
        printBoard(board);
    }
}

/*
 * Time Complexity: O(9^(empty cells)) in the worst case, but heavily pruned by validity checks.
 * Space Complexity: O(1) auxiliary space (board is fixed 9x9, stack depth at most 81).
 */

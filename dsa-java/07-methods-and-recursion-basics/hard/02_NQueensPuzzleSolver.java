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

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class NQueensPuzzleSolver {

    /**
     * Approach:
     * Backtracking with O(1) Conflict Lookup using boolean sets/arrays:
     * - cols[c]: queen placed in column c
     * - diag1[r + c]: major diagonals
     * - diag2[r - c + n - 1]: minor diagonals
     * Advance row by row from 0 to n - 1.
     */
    public static List<List<String>> solveNQueens(int n) {
        List<List<String>> solutions = new ArrayList<>();
        char[][] board = new char[n][n];
        for (char[] row : board) Arrays.fill(row, '.');

        boolean[] cols = new boolean[n];
        boolean[] diag1 = new boolean[2 * n];
        boolean[] diag2 = new boolean[2 * n];

        backtrack(0, n, board, cols, diag1, diag2, solutions);
        return solutions;
    }

    private static void backtrack(int r, int n, char[][] board,
                                  boolean[] cols, boolean[] diag1, boolean[] diag2,
                                  List<List<String>> solutions) {
        if (r == n) {
            List<String> validBoard = new ArrayList<>();
            for (char[] row : board) {
                validBoard.add(new String(row));
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

    public static void main(String[] args) {
        int n = 4;
        List<List<String>> res = solveNQueens(n);

        System.out.println("--- N-Queens Puzzle for N = " + n + " ---");
        System.out.println("Total distinct solutions: " + res.size());
        for (int i = 0; i < res.size(); i++) {
            System.out.println("Solution #" + (i + 1) + ":");
            for (String row : res.get(i)) {
                System.out.println("  " + row);
            }
        }

        System.out.println("\nSolutions count for N = 8: " + solveNQueens(8).size() + " (Expected: 92)");
    }
}

/*
 * Time Complexity: O(N!) - Upper bound for valid placements across N rows.
 * Space Complexity: O(N^2) for the board matrix and O(N) for recursion stack.
 */

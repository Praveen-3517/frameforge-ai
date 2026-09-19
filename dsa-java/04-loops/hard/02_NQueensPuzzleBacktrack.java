import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

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
class NQueensPuzzleBacktrack {

    public static List<List<String>> solveNQueens(int n) {
        List<List<String>> results = new ArrayList<>();
        char[][] board = new char[n][n];
        for (char[] row : board) Arrays.fill(row, '.');

        boolean[] cols = new boolean[n];
        boolean[] diag1 = new boolean[2 * n]; // r + c
        boolean[] diag2 = new boolean[2 * n]; // r - c + n

        backtrack(0, n, board, cols, diag1, diag2, results);
        return results;
    }

    private static void backtrack(int r, int n, char[][] board, boolean[] cols,
                                  boolean[] diag1, boolean[] diag2, List<List<String>> results) {
        if (r == n) {
            List<String> solution = new ArrayList<>(n);
            for (char[] row : board) {
                solution.add(new String(row));
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

    public static void main(String[] args) {
        System.out.println("=== LeetCode 51: N-Queens Backtracking Solver ===");

        int n = 4;
        List<List<String>> solutions = solveNQueens(n);

        System.out.printf("Total Valid Board Arrangements for N = %d: %d%n%n", n, solutions.size());
        for (int i = 0; i < solutions.size(); i++) {
            System.out.printf("Solution #%d:%n", i + 1);
            for (String row : solutions.get(i)) {
                System.out.println("  " + row);
            }
            System.out.println();
        }
    }
}

/*
 * Time Complexity: O(N!) - Number of queen placements decreases by at least 1 per row.
 * Space Complexity: O(N^2) - Board state storage and call stack depth.
 */

import java.util.Arrays;

/**
 * Problem Statement:
 * Conway's Game of Life on an m x n board:
 * Each cell has 8 neighbors (horizontal, vertical, diagonal).
 * Transition Rules:
 *   1. Any live cell with < 2 live neighbors dies (under-population).
 *   2. Any live cell with 2 or 3 live neighbors lives to the next generation.
 *   3. Any live cell with > 3 live neighbors dies (over-population).
 *   4. Any dead cell with exactly 3 live neighbors becomes live (reproduction).
 * Solve in-place without allocating an auxiliary m x n matrix (O(1) space).
 * (LeetCode 289: Game of Life).
 *
 * Asked in: Google, Amazon, Dropbox, Bloomberg
 *
 * Approach:
 * - 2-Bit State Encoding Conditionals (O(1) Memory):
 *   Instead of allocating a new matrix, encode the past and future states in the same integer:
 *   - State 0: Dead -> Remains Dead (0 -> 0)
 *   - State 1: Live -> Remains Live (1 -> 1)
 *   - State 2: Live -> Becomes Dead (1 -> 0)
 *   - State 3: Dead -> Becomes Live (0 -> 1)
 * - Notice that cells that were originally LIVE have value 1 or 2.
 *   So when checking neighbor counts, `board[nr][nc] == 1 || board[nr][nc] == 2` indicates a live neighbor!
 * - Apply rules:
 *   - If live (1) and neighbors < 2 or > 3: change to 2.
 *   - If dead (0) and neighbors == 3: change to 3.
 * - Second pass:
 *   Map states 0, 2 -> 0, and states 1, 3 -> 1 via `board[r][c] %= 2`!
 */
class GameOfLifeTransitionRules {

    private static final int[][] DIRS = {
        { -1, -1 }, { -1, 0 }, { -1, 1 },
        {  0, -1 },           {  0, 1 },
        {  1, -1 }, {  1, 0 }, {  1, 1 }
    };

    public static void gameOfLife(int[][] board) {
        int m = board.length;
        int n = board[0].length;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int liveNeighbors = 0;

                for (int[] d : DIRS) {
                    int nr = r + d[0];
                    int nc = c + d[1];

                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        // Cells with 1 or 2 were originally alive
                        if (board[nr][nc] == 1 || board[nr][nc] == 2) {
                            liveNeighbors++;
                        }
                    }
                }

                // Apply transition conditionals
                if (board[r][c] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        board[r][c] = 2; // Live -> Dead
                    }
                } else if (board[r][c] == 0) {
                    if (liveNeighbors == 3) {
                        board[r][c] = 3; // Dead -> Live
                    }
                }
            }
        }

        // Second pass: decode new states
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                board[r][c] %= 2; // 0 & 2 become 0; 1 & 3 become 1
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 289: Conway's Game of Life (In-Place Bit Encoding) ===");

        int[][] board = {
            { 0, 1, 0 },
            { 0, 0, 1 },
            { 1, 1, 1 },
            { 0, 0, 0 }
        };

        System.out.println("Initial Board:");
        for (int[] row : board) System.out.println(Arrays.toString(row));

        gameOfLife(board);

        System.out.println("\nNext Generation:");
        for (int[] row : board) System.out.println(Arrays.toString(row));
    }
}

/*
 * Time Complexity: O(M * N) - Two passes through the M x N grid checking 8 neighbors per cell.
 * Space Complexity: O(1) - Constant auxiliary space (in-place state transition flags).
 */

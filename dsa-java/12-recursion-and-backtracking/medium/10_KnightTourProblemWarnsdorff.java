/*
 * Problem Statement:
 * Given an N x N chessboard, find a sequence of moves of a knight such that the knight
 * visits every square exactly once.
 * (The Knight's Tour Problem)
 * Print the resulting board where numbers 0 to N*N - 1 represent the sequence of moves.
 * 
 * Asked in: Google, Microsoft, Amazon, Samsung
 */

class KnightTourProblemWarnsdorff {

    private static final int N = 8;
    // 8 possible L-shaped knight moves
    private static final int[] DR = {2, 1, -1, -2, -2, -1, 1, 2};
    private static final int[] DC = {1, 2, 2, 1, -1, -2, -2, -1};

    public static boolean solveKnightTour(int boardSize) {
        int[][] board = new int[boardSize][boardSize];
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
            System.out.println("No solution exists for board size " + boardSize);
            return false;
        }
    }

    private static boolean solve(int r, int c, int moveIdx, int[][] board, int n) {
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

    private static boolean isValid(int r, int c, int[][] board, int n) {
        return r >= 0 && r < n && c >= 0 && c < n && board[r][c] == -1;
    }

    private static void printSolution(int[][] board, int n) {
        System.out.println("Knight's Tour Solution (" + n + "x" + n + "):");
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                System.out.printf("%3d ", board[r][c]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        // Fast test on 5x5 board
        int size = 5;
        System.out.println("--- Solving Knight's Tour for " + size + "x" + size + " Board ---");
        solveKnightTour(size);
    }
}

/*
 * Time Complexity: O(8^(N^2)) worst case; pruned significantly on smaller grids.
 * Space Complexity: O(N^2) for the board matrix and call stack.
 */

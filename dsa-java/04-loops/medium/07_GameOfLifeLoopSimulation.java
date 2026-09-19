import java.util.Arrays;

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
class GameOfLifeLoopSimulation {

    private static final int[][] DIRS = {
        { -1, -1 }, { -1, 0 }, { -1, 1 },
        {  0, -1 },           {  0, 1 },
        {  1, -1 }, {  1, 0 }, {  1, 1 }
    };

    public static int[][] evolveOnce(int[][] board) {
        int m = board.length;
        int n = board[0].length;
        int[][] next = new int[m][n];

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int liveNeighbors = 0;
                for (int[] d : DIRS) {
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

    public static void printBoard(int[][] board, String title) {
        System.out.println(title);
        for (int[] row : board) {
            for (int cell : row) {
                System.out.print(cell == 1 ? " O " : " . ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Conway's Game of Life Multi-Generation Oscillator Simulation ===");

        // The "Blinker" Oscillator (Period 2)
        int[][] blinker = {
            { 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 1, 0, 0 },
            { 0, 0, 0, 0, 0 }
        };

        int[][] current = blinker;
        printBoard(current, "Generation 0 (Vertical Bar):");

        for (int gen = 1; gen <= 3; gen++) {
            current = evolveOnce(current);
            printBoard(current, "\nGeneration " + gen + (gen % 2 == 1 ? " (Horizontal Bar):" : " (Vertical Bar):"));
        }
    }
}

/*
 * Time Complexity: O(G * M * N) where G is number of generations simulated.
 * Space Complexity: O(M * N) - Next board state array.
 */

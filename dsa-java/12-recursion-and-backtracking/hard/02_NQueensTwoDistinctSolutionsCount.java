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

class NQueensTwoDistinctSolutionsCount {

    private static int totalSolutions = 0;

    public static int totalNQueens(int n) {
        totalSolutions = 0;
        int allOnes = (1 << n) - 1; // Mask with n lowest bits set to 1
        solveBitmask(0, 0, 0, allOnes);
        return totalSolutions;
    }

    private static void solveBitmask(int cols, int diag1, int diag2, int allOnes) {
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

    public static void main(String[] args) {
        System.out.println("--- N-Queens II (Bitmask Accelerated) ---");
        for (int n = 1; n <= 12; n++) {
            System.out.printf("n = %2d -> Total distinct solutions: %6d%n", n, totalNQueens(n));
        }
    }
}

/*
 * Time Complexity: O(N!) - Highly optimized via hardware bitwise operations.
 * Space Complexity: O(N) recursion stack depth.
 */

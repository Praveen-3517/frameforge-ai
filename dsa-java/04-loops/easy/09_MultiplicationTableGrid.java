/**
 * Problem Statement:
 * Generate a clean, tabular 2D multiplication table from 1 to N with properly aligned
 * row headers, column headers, and borders.
 *
 * Asked in: TCS, Infosys, Wipro, Capgemini
 *
 * Approach:
 * - Nested loops:
 *   - Outer loop iterates over multiplicand (rows 1 to N).
 *   - Inner loop iterates over multiplier (cols 1 to N).
 * - Formatting:
 *   Use `System.out.printf("%4d", val)` to ensure right-aligned tabular formatting regardless of digit length.
 */
class MultiplicationTableGrid {

    public static void printTable(int n) {
        System.out.printf("=== Multiplication Table (1 to %d) ===%n%n", n);

        // Print header row
        System.out.print("   * |");
        for (int c = 1; c <= n; c++) {
            System.out.printf("%4d", c);
        }
        System.out.println();

        // Print separator line
        System.out.print("-----+");
        for (int c = 1; c <= n; c++) {
            System.out.print("----");
        }
        System.out.println();

        // Print table rows
        for (int r = 1; r <= n; r++) {
            System.out.printf("%4d |", r);
            for (int c = 1; c <= n; c++) {
                System.out.printf("%4d", r * c);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        printTable(10);
    }
}

/*
 * Time Complexity: O(N^2) - Iterates through N * N cells.
 * Space Complexity: O(1) - Formatted console stream output only.
 */

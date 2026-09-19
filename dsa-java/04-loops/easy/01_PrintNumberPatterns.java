/**
 * Problem Statement:
 * Print three standard geometric patterns frequently asked in service-based company coding rounds:
 * 1. Centered Star Pyramid of height N.
 * 2. Full Star Diamond of height 2N - 1.
 * 3. Hollow Square of size N.
 *
 * Asked in: TCS, Infosys, Wipro, Capgemini, Cognizant
 *
 * Approach:
 * - Nested loop coordinates:
 *   - Outer loop controls row index `r` (from 1 to N).
 *   - Inner loop 1 prints leading spaces for centering.
 *   - Inner loop 2 prints stars.
 * - Diamond: Print upper pyramid (1 to N), then inverted lower pyramid (N - 1 down to 1).
 * - Hollow Square: Print star if `r == 0 || r == n-1 || c == 0 || c == n-1`, else space.
 */
class PrintNumberPatterns {

    public static void printPyramid(int n) {
        System.out.printf("--- 1. Star Pyramid (Height %d) ---%n", n);
        for (int r = 1; r <= n; r++) {
            // Print leading spaces
            for (int s = 1; s <= n - r; s++) {
                System.out.print(" ");
            }
            // Print stars
            for (int star = 1; star <= 2 * r - 1; star++) {
                System.out.print("*");
            }
            System.out.println();
        }
    }

    public static void printDiamond(int n) {
        System.out.printf("%n--- 2. Star Diamond (Radius %d) ---%n", n);
        // Upper half (including center row)
        for (int r = 1; r <= n; r++) {
            for (int s = 1; s <= n - r; s++) System.out.print(" ");
            for (int star = 1; star <= 2 * r - 1; star++) System.out.print("*");
            System.out.println();
        }
        // Lower half
        for (int r = n - 1; r >= 1; r--) {
            for (int s = 1; s <= n - r; s++) System.out.print(" ");
            for (int star = 1; star <= 2 * r - 1; star++) System.out.print("*");
            System.out.println();
        }
    }

    public static void printHollowSquare(int n) {
        System.out.printf("%n--- 3. Hollow Square (Size %d) ---%n", n);
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (r == 0 || r == n - 1 || c == 0 || c == n - 1) {
                    System.out.print("* ");
                } else {
                    System.out.print("  ");
                }
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 04 (Easy): Geometric Pattern Generation via Nested Loops ===");
        printPyramid(5);
        printDiamond(4);
        printHollowSquare(5);
    }
}

/*
 * Time Complexity: O(N^2) - Nested rows and columns.
 * Space Complexity: O(1) - Constant stack space.
 */

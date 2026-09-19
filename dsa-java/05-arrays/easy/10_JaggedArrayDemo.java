/**
 * Problem Statement:
 * Demonstrate Java's Jagged Arrays (Arrays of Arrays with non-uniform row lengths):
 * 1. Allocate and initialize an uneven 2D jagged array on the JVM heap.
 * 2. Traverse and print jagged arrays dynamically using `array[r].length`.
 * 3. Explain the memory architecture and overhead of jagged arrays vs flat 1D contiguous arrays.
 *
 * Asked in: Oracle, TCS, Infosys, IBM
 *
 * Approach:
 * - JVM Heap Architecture:
 *   In Java, `int[][] jagged = new int[3][]` allocates an array of 3 object references (initially null).
 *   Each row is then instantiated independently:
 *     `jagged[0] = new int[2];`
 *     `jagged[1] = new int[4];`
 *     `jagged[2] = new int[3];`
 *   Rows can reside anywhere in heap memory and do not need to be contiguous!
 * - Object Overhead:
 *   Each sub-array is a full Java object carrying a 12-16 byte object header and a 4-byte length.
 *   Hence, jagged arrays trade slightly higher memory overhead and cache-miss rates for flexible dimensions.
 */
class JaggedArrayDemo {

    public static int[][] createPascalJagged(int n) {
        int[][] jagged = new int[n][];

        for (int r = 0; r < n; r++) {
            jagged[r] = new int[r + 1]; // Row r has length r + 1
            for (int c = 0; c <= r; c++) {
                if (c == 0 || c == r) {
                    jagged[r][c] = 1;
                } else {
                    jagged[r][c] = jagged[r - 1][c - 1] + jagged[r - 1][c];
                }
            }
        }

        return jagged;
    }

    public static void printJaggedArray(int[][] arr) {
        System.out.printf("Outer Array Length: %d (Rows)%n", arr.length);
        for (int r = 0; r < arr.length; r++) {
            System.out.printf("Row %d (length %d): ", r, arr[r].length);
            for (int c = 0; c < arr[r].length; c++) {
                System.out.printf("%3d ", arr[r][c]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Java Jagged Arrays (Heap Layout & Dynamic Row Lengths) ===");

        int[][] jaggedPascal = createPascalJagged(5);
        printJaggedArray(jaggedPascal);

        System.out.println("\n--- Explicit Custom Uneven Allocation ---");
        int[][] uneven = new int[4][];
        uneven[0] = new int[] { 10, 20 };
        uneven[1] = new int[] { 30, 40, 50, 60, 70 };
        uneven[2] = new int[] { 80 };
        uneven[3] = new int[] { 90, 100, 110 };
        printJaggedArray(uneven);
    }
}

/*
 * Time Complexity: O(Total Elements) - Linear scan of all populated cells.
 * Space Complexity: O(Total Elements) - Heap objects for outer array and sub-arrays.
 */

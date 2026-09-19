/**
 * Problem Statement:
 * Given a non-negative integer `n`, count the number of set bits (1s) in its binary representation.
 * Compare the naive bit-shifting approach with Brian Kernighan’s optimal Algorithm.
 * (LeetCode 191: Number of 1 Bits).
 *
 * Asked in: Google, Microsoft, Adobe, Cisco
 *
 * Approach:
 * Naive Approach:
 *   Loop through all 32 bits, checking `(n & 1)` and right-shifting. Runs in O(32) = O(1) always.
 *
 * Brian Kernighan’s Algorithm:
 *   In each step, perform `n = n & (n - 1)`.
 *   Subtracting 1 from a number flips all bits after the rightmost set bit, including the rightmost set bit itself.
 *   Therefore, `n & (n - 1)` clears the lowest set bit in `n`.
 *   Loop runs strictly proportional to the number of SET bits (Hamming weight), not total bits.
 */
class CountSetBitsBrianKernighan {

    // Method 1: Naive 32-bit Shift
    public static int countBitsNaive(int n) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            count += (n & 1);
            n >>>= 1; // Unsigned right shift
        }
        return count;
    }

    // Method 2: Brian Kernighan's Algorithm (Optimal)
    public static int countBitsKernighan(int n) {
        int count = 0;
        while (n != 0) {
            n = n & (n - 1); // Clears the lowest set bit
            count++;
        }
        return count;
    }

    public static void main(String[] args) {
        int[] testCases = { 0, 1, 7, 15, 1024, 1023, -1, Integer.MAX_VALUE };

        System.out.println("=== Hamming Weight (Set Bits Count) ===");
        for (int n : testCases) {
            int naive = countBitsNaive(n);
            int kernighan = countBitsKernighan(n);
            int builtIn = Integer.bitCount(n);

            System.out.printf("Number: %-12d | Binary: %-32s | Kernighan: %2d | BuiltIn: %2d%n",
                    n, Integer.toBinaryString(n), kernighan, builtIn);

            assert kernighan == builtIn : "Mismatch with built-in!";
        }
        System.out.println("All test cases matched successfully!");
    }
}

/*
 * Time Complexity:
 *   - Naive: O(32) = O(1) fixed.
 *   - Brian Kernighan: O(K) where K is the count of set bits (1 <= K <= 32).
 * Space Complexity: O(1) - Pure register manipulation.
 */

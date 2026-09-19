/**
 * Problem Statement:
 * Find the minimum and maximum of two integers without using branching:
 * No `if-else`, ternary `? :`, `switch`, loops, or `Math.min` / `Math.max`.
 * Must handle 32-bit overflow when `(a - b)` exceeds integer limits.
 *
 * Asked in: Goldman Sachs, Intel, Bloomberg, Microsoft
 *
 * Approach:
 * - Method 1: Sign-Bit Masking:
 *   In two's complement, arithmetic right-shifting by 31 bits produces:
 *   `mask = (a - b) >> 31`
 *   - If a < b: (a - b) is negative, so mask = -1 (all 1s in binary: 0xFFFFFFFF).
 *   - If a >= b: (a - b) is non-negative, so mask = 0 (all 0s in binary: 0x00000000).
 *   Then:
 *   `min = b + ((a - b) & mask);`
 *     -> When a < b: b + (a - b) = a
 *     -> When a >= b: b + 0 = b
 *   `max = a - ((a - b) & mask);`
 *     -> When a < b: a - (a - b) = b
 *     -> When a >= b: a - 0 = a
 * - Overflow Safety:
 *   To safely prevent `(a - b)` 32-bit integer overflow (e.g. `Integer.MAX_VALUE - (-5)`),
 *   perform the difference in 64-bit `long`.
 */
class MinMaxWithoutBranching {

    public static int getMin(int a, int b) {
        long diff = (long) a - (long) b;
        long mask = diff >> 63; // 0 if a >= b, -1 if a < b
        return (int) (b + (diff & mask));
    }

    public static int getMax(int a, int b) {
        long diff = (long) a - (long) b;
        long mask = diff >> 63; // 0 if a >= b, -1 if a < b
        return (int) (a - (diff & mask));
    }

    public static void main(String[] args) {
        System.out.println("=== Branchless Min and Max Using Bitwise Sign Masks ===");

        int[][] testPairs = {
            { 15, 27 },
            { 45, 12 },
            { -10, -30 },
            { 0, -5 },
            { 100, 100 },
            { Integer.MAX_VALUE, -100 }, // Overflow test
            { Integer.MIN_VALUE, 50 }    // Underflow test
        };

        for (int[] pair : testPairs) {
            int a = pair[0];
            int b = pair[1];
            int minVal = getMin(a, b);
            int maxVal = getMax(a, b);
            System.out.printf("Pair (%11d, %11d) ==> Min: %11d | Max: %11d%n",
                    a, b, minVal, maxVal);
        }
    }
}

/*
 * Time Complexity: O(1) - Single arithmetic shift and bitwise AND operation.
 * Space Complexity: O(1) - Stack register variables only.
 */

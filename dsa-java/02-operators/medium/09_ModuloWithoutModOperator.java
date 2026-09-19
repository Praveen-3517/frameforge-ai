/**
 * Problem Statement:
 * Compute the modulo `n % d` without using the modulo (%) operator.
 * Address two scenarios:
 * 1. Fast Modulo when `d` is a known power of 2 (e.g., d = 2, 4, 8, 16, 64, 1024...).
 *    Explain why Java's `HashMap` forces capacity to be a power of two: `index = hash & (n - 1)`.
 * 2. General Modulo for arbitrary integer `d` using bitwise exponential shift subtraction.
 *
 * Asked in: Amazon, Oracle, Intel, Qualcomm, High Frequency Trading
 *
 * Approach:
 * - Scenario 1: Power of 2 (O(1)):
 *   When `d = 2^k`, the lowest k bits represent the remainder.
 *   `d - 1` creates a bitmask with the lowest k bits set to 1.
 *   `remainder = n & (d - 1);`
 *   This is 10x-20x faster than CPU hardware division instruction!
 * - Scenario 2: Arbitrary Divisor (O(log n)):
 *   Use exponential bit-shifting to subtract the largest multiple of `d` from `n`:
 *   Find highest `k` such that `(d << k) <= n`.
 *   Subtract `(d << k)` from `n` and repeat until `n < d`.
 */
class ModuloWithoutModOperator {

    // Scenario 1: Fast Modulo for Power-of-Two Divisors
    public static int modPowerOfTwo(int n, int d) {
        // Precondition: d must be a positive power of 2
        return n & (d - 1);
    }

    // Scenario 2: General Modulo for any positive dividend and divisor
    public static int modGeneral(int n, int d) {
        if (d == 0) {
            throw new ArithmeticException("Division by zero");
        }

        boolean isNegativeDividend = n < 0;
        long dividend = Math.abs((long) n);
        long divisor = Math.abs((long) d);

        while (dividend >= divisor) {
            long tempDivisor = divisor;
            while (dividend >= (tempDivisor << 1)) {
                tempDivisor <<= 1;
            }
            dividend -= tempDivisor;
        }

        int remainder = (int) dividend;
        return isNegativeDividend ? -remainder : remainder;
    }

    public static void main(String[] args) {
        System.out.println("=== Modulo Without '%' Operator (Power-of-2 vs General) ===");

        System.out.println("--- 1. Power-of-Two Fast Modulo (HashMap Index Pattern) ---");
        int[] powerDivisors = { 2, 4, 8, 16, 32, 64, 1024 };
        int sampleNum = 157;
        for (int d : powerDivisors) {
            int fastMod = modPowerOfTwo(sampleNum, d);
            System.out.printf("%d & (%d - 1) = %3d (Java %%: %3d)%n", sampleNum, d, fastMod, sampleNum % d);
        }

        System.out.println("\n--- 2. General Modulo for Arbitrary Divisors ---");
        int[][] testPairs = {
            { 157, 13 },
            { 100, 7 },
            { 25, 5 },
            { 3, 10 },
            { -45, 6 },
            { 1000000, 33 }
        };

        for (int[] pair : testPairs) {
            int n = pair[0];
            int d = pair[1];
            int modVal = modGeneral(n, d);
            System.out.printf("%5d %% %2d ==> Bitwise Mod: %2d | Standard Java %%: %2d%n",
                    n, d, modVal, n % d);
        }
    }
}

/*
 * Time Complexity:
 *   - Power-of-two: O(1) single cycle CPU instruction.
 *   - General: O(log^2 N) using exponential bit shifts.
 * Space Complexity: O(1) - Primitive register variables only.
 */

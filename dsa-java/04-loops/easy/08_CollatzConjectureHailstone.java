/**
 * Problem Statement:
 * Simulate the Collatz Conjecture (also known as the 3n + 1 problem or Hailstone Sequence):
 * Starting from any positive integer `n`:
 *   - If n is even: n = n / 2
 *   - If n is odd : n = 3 * n + 1
 * The conjecture asserts that the sequence always reaches 1.
 * Return:
 *   1. Total step count to reach 1.
 *   2. The peak (maximum) value encountered in the trajectory.
 * Guard against 32-bit integer overflow using 64-bit `long` (intermediate values can grow massively).
 *
 * Asked in: Amazon, Google, Qualcomm, Math Olympiad Coding
 *
 * Approach:
 * - Loop Invariant:
 *   Use a `while (n != 1)` loop with a `long` variable.
 *   Track `steps++` and update `peak = Math.max(peak, n)`.
 *   Bitwise parity check: `if ((n & 1) == 0) n >>>= 1; else n = 3 * n + 1;`
 */
class CollatzConjectureHailstone {

    public static void printCollatzTrajectory(long n) {
        if (n <= 0) {
            throw new IllegalArgumentException("Collatz sequence is defined for positive integers only.");
        }

        long curr = n;
        long peak = n;
        int steps = 0;

        StringBuilder preview = new StringBuilder();
        preview.append(curr);

        while (curr != 1) {
            if ((curr & 1) == 0) {
                curr >>>= 1; // Even: divide by 2
            } else {
                curr = 3 * curr + 1; // Odd: 3n + 1
            }

            steps++;
            peak = Math.max(peak, curr);

            if (steps <= 8) {
                preview.append(" -> ").append(curr);
            }
        }

        if (steps > 8) {
            preview.append(" -> ... -> 1");
        }

        System.out.printf("Start: %7d | Steps: %4d | Peak: %11d | Path: %s%n",
                n, steps, peak, preview);
    }

    public static void main(String[] args) {
        System.out.println("=== Collatz Conjecture / Hailstone Sequence Simulation ===");

        long[] testStarters = { 1, 6, 11, 27, 837799L };

        for (long start : testStarters) {
            printCollatzTrajectory(start);
        }
    }
}

/*
 * Time Complexity: Unproven mathematically, but bounded empirically by O(steps).
 * Space Complexity: O(1) - Constant stack registers.
 */

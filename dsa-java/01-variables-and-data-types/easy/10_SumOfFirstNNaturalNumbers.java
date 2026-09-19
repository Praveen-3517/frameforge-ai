/**
 * Problem Statement:
 * Given an integer `n`, compute the sum of the first `n` natural numbers (1 + 2 + ... + n).
 * Prevent 32-bit integer overflow when `n` is large (e.g. n = 100,000).
 *
 * Asked in: Microsoft, Amazon, TCS
 *
 * Approach:
 * - Mathematical formula: S = n * (n + 1) / 2
 * - Pitfall: If n = 100,000, n * (n + 1) = 10,000,100,000 which exceeds Integer.MAX_VALUE (2,147,483,647).
 *   If evaluated purely as 32-bit `int`, it silently overflows into negative numbers.
 * - Solution: Cast `n` to `long` before multiplication: `(long) n * (n + 1) / 2`.
 */
class SumOfFirstNNaturalNumbers {

    // Buggy implementation vulnerable to integer overflow
    public static int sumBuggy(int n) {
        return (n * (n + 1)) / 2;
    }

    // Correct, overflow-safe implementation using 64-bit promotion
    public static long sumSafe(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("n must be non-negative.");
        }
        return ((long) n * (n + 1L)) / 2L;
    }

    public static void main(String[] args) {
        System.out.println("=== Sum of First N Natural Numbers ===");

        int[] testCases = { 10, 100, 1000, 70000, 100000 };

        for (int n : testCases) {
            long safeResult = sumSafe(n);
            int buggyResult = sumBuggy(n);

            System.out.println("n = " + n);
            System.out.println("  Safe (long) result : " + safeResult);
            System.out.println("  Buggy (int) result : " + buggyResult +
                    (safeResult != buggyResult ? " <--- OVERFLOW DETECTED!" : ""));
            System.out.println();
        }
    }
}

/*
 * Time Complexity: O(1) - Constant closed-form formula.
 * Space Complexity: O(1) - Single 64-bit long return.
 */

/**
 * Problem Statement:
 * Generate the first N numbers of the Fibonacci sequence:
 *   F(0) = 0, F(1) = 1, F(n) = F(n - 1) + F(n - 2) for n >= 2.
 * Implement an iterative solution using constant auxiliary space O(1).
 * Handle large values of N safely using 64-bit `long` (since F(47) overflows signed 32-bit `int`).
 *
 * Asked in: TCS, Infosys, Amazon, Accenture, Wipro
 *
 * Approach:
 * - Space-Optimized Iterative Loop:
 *   Instead of allocating an array of size N (which costs O(N) heap memory),
 *   maintain only two variables: `prev2 = 0` and `prev1 = 1`.
 *   In each iteration of the loop:
 *     `long current = prev1 + prev2;`
 *     `prev2 = prev1;`
 *     `prev1 = current;`
 * - Time: O(N), Space: O(1).
 */
class FibonacciSeriesUpToN {

    public static long[] generateFibonacci(int n) {
        if (n <= 0) return new long[0];
        if (n == 1) return new long[] { 0L };

        long[] fib = new long[n];
        fib[0] = 0L;
        fib[1] = 1L;

        for (int i = 2; i < n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }

        return fib;
    }

    public static long getNthFibonacciSpaceOptimized(int n) {
        if (n <= 0) return 0L;
        if (n == 1) return 1L;

        long prev2 = 0L;
        long prev1 = 1L;

        for (int i = 2; i <= n; i++) {
            long curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    public static void main(String[] args) {
        System.out.println("=== Iterative Fibonacci Series (O(1) Space) ===");

        int n = 15;
        long[] sequence = generateFibonacci(n);
        System.out.printf("First %d Fibonacci Numbers:%n", n);
        for (int i = 0; i < sequence.length; i++) {
            System.out.printf("F(%2d) = %4d%n", i, sequence[i]);
        }

        System.out.println("\nLarge Fibonacci Calculation (64-Bit Safe):");
        int[] queryTerms = { 20, 30, 45, 50 };
        for (int q : queryTerms) {
            System.out.printf("F(%2d) = %d%n", q, getNthFibonacciSpaceOptimized(q));
        }
    }
}

/*
 * Time Complexity: O(N) - Single loop of N iterations.
 * Space Complexity: O(1) - Two local register variables.
 */

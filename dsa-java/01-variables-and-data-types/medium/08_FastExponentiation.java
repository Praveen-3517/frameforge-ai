/**
 * Problem Statement:
 * Implement `myPow(x, n)` which calculates `x` raised to the power `n` (i.e., `x^n`).
 * Must handle negative powers, fractional results, and `n = Integer.MIN_VALUE` edge case.
 * (LeetCode 50: Pow(x, n)).
 *
 * Asked in: Google, Amazon, Meta, Bloomberg
 *
 * Approach:
 * - Binary Exponentiation (Exponentiation by Squaring):
 *     If n is even: x^n = (x^2)^(n/2)
 *     If n is odd:  x^n = x * (x^2)^((n-1)/2)
 * - Corner Case: `n = -214748348 (Integer.MIN_VALUE)`. Negating `-n` directly in 32-bit `int`
 *   causes integer overflow back to `Integer.MIN_VALUE`!
 *   We must promote `n` to 64-bit `long N = n` before negating.
 * - If `N < 0`: compute `myPow(1/x, -N)`.
 */
class FastExponentiation {

    public static double myPow(double x, int n) {
        long N = n; // Promote to long to avoid -Integer.MIN_VALUE overflow
        if (N < 0) {
            x = 1.0 / x;
            N = -N;
        }

        double result = 1.0;
        double currentProduct = x;

        while (N > 0) {
            if ((N & 1) == 1) { // If LSB is set (odd power)
                result *= currentProduct;
            }
            currentProduct *= currentProduct; // Square the base
            N >>= 1; // Divide power by 2
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 50: Binary Exponentiation ===");

        double[][] testCases = {
            { 2.0, 10 },
            { 2.1, 3 },
            { 2.0, -2 },
            { 1.0, Integer.MAX_VALUE },
            { 1.0, Integer.MIN_VALUE },
            { -1.0, Integer.MIN_VALUE },
            { 2.0, -2147483648 }
        };

        for (double[] tc : testCases) {
            double x = tc[0];
            int n = (int) tc[1];
            double res = myPow(x, n);
            System.out.printf("Base: %-6.2f | Exp: %-12d ==> Result: %e%n", x, n, res);
        }
    }
}

/*
 * Time Complexity: O(log N) - Exponent is halved in each iteration.
 * Space Complexity: O(1) - Iterative approach using constant variables.
 */

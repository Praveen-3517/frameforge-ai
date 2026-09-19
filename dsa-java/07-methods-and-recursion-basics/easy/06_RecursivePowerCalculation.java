/**
 * Problem Statement:
 * Compute `x^n` (x raised to the power n) using recursion.
 * Compare two implementations:
 * 1. Naive Linear Recursion: `O(N)` time and call stack depth.
 * 2. Logarithmic Divide-and-Conquer Exponentiation: `O(log N)` time and call stack depth.
 *
 * Asked in: Amazon, Microsoft, TCS, Infosys
 *
 * Approach:
 * - Method 1: Linear Recursion (O(N)):
 *   `power(x, n) = x * power(x, n - 1)` with base case `n == 0 -> 1`.
 * - Method 2: Divide & Conquer (O(log N)):
 *   - If n is even: `x^n = (x^(n/2))^2`
 *   - If n is odd : `x^n = x * (x^(n/2))^2`
 *   Evaluating `half = power(x, n / 2)` once and squaring halves the problem size at each step!
 */
class RecursivePowerCalculation {

    // Linear Recursion: O(N)
    public static long powerLinear(long x, int n) {
        if (n == 0) return 1L;
        return x * powerLinear(x, n - 1);
    }

    // Divide and Conquer: O(log N)
    public static long powerDivideAndConquer(long x, int n) {
        if (n == 0) return 1L;

        long half = powerDivideAndConquer(x, n / 2);

        if ((n & 1) == 0) {
            return half * half;
        } else {
            return x * half * half;
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Recursive Power Calculation: O(N) vs O(log N) ===");

        long x = 2;
        int n = 30;

        long ansLinear = powerLinear(x, n);
        long ansLog = powerDivideAndConquer(x, n);

        System.out.printf("%d^%d via Linear Recursion (O(N))       : %d%n", x, n, ansLinear);
        System.out.printf("%d^%d via Divide & Conquer (O(log N)) : %d%n", x, n, ansLog);
    }
}

/*
 * Time Complexity:
 *   - Linear: O(N)
 *   - Divide & Conquer: O(log N)
 * Space Complexity:
 *   - Linear: O(N) call stack frames
 *   - Divide & Conquer: O(log N) call stack frames
 */

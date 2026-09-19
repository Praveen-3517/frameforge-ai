/*
 * Problem Statement:
 * Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).
 * Both x (double) and n (int, can be negative, zero, or positive) are provided.
 * Must handle integer boundary edge case n = Integer.MIN_VALUE (-2147483648).
 * 
 * Example 1:
 * Input: x = 2.00000, n = 10
 * Output: 1024.00000
 * 
 * Example 2:
 * Input: x = 2.00000, n = -2
 * Output: 0.25000 (1/(2^2) = 1/4)
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Bloomberg, LinkedIn
 */

class PowXNFastDivideConquer {

    /**
     * Approach:
     * Fast Binary Exponentiation (Divide and Conquer):
     * If n is even: x^n = (x^2)^(n/2) = (x^(n/2))^2
     * If n is odd:  x^n = x * (x^(n - 1))
     * For negative n: x^n = 1 / (x^(-n))
     * To prevent integer overflow when n = Integer.MIN_VALUE, cast n to long.
     */
    public static double myPow(double x, int n) {
        long N = n;
        if (N < 0) {
            x = 1.0 / x;
            N = -N;
        }
        return fastPow(x, N);
    }

    private static double fastPow(double x, long n) {
        if (n == 0) return 1.0;
        if (n == 1) return x;

        double half = fastPow(x, n / 2);
        if (n % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }

    public static void main(String[] args) {
        double[][] tests = {
            {2.0, 10},
            {2.1, 3},
            {2.0, -2},
            {5.0, 0},
            {1.0, 2147483647},
            {-1.0, -2147483648}
        };

        System.out.println("--- Binary Exponentiation (Fast Pow) ---");
        for (double[] test : tests) {
            double x = test[0];
            int n = (int) test[1];
            double result = myPow(x, n);
            double expected = Math.pow(x, n);
            System.out.printf("pow(%.2f, %11d) = %14.6f | Expected: %14.6f%n", x, n, result, expected);
        }
    }
}

/*
 * Time Complexity: O(log |n|) - The exponent halves with each recursive step.
 * Space Complexity: O(log |n|) - Recursion stack frames proportional to log |n|.
 */

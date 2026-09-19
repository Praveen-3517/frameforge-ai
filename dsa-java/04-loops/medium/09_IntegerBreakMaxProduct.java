/**
 * Problem Statement:
 * Given an integer `n`, break it into the sum of `k` positive integers, where `k >= 2`,
 * and maximize the product of those integers.
 * Return the maximum product you can achieve.
 * (LeetCode 343: Integer Break).
 *
 * Example:
 * n = 2  -> 1 * 1 = 1
 * n = 10 -> 3 * 3 * 4 = 36
 *
 * Asked in: Amazon, Bloomberg, Microsoft, Google
 *
 * Approach:
 * - Mathematical Greedy Loop:
 *   - The maximum product is achieved when parts are as close to Euler's number `e ≈ 2.718` as possible.
 *     The closest integer is 3 (with 2 being second best).
 *   - Notice that for any factor >= 5, splitting into (factor - 3) and 3 yields:
 *     `3 * (factor - 3) = 3 * factor - 9 > factor`.
 *   - For factor = 4, 2 * 2 = 4 (better to keep 4 than split into 3 and 1).
 *   - Greedy loop:
 *     While `n > 4`: multiply product by 3 and subtract 3 from n.
 *     Finally, multiply by remaining `n` (which is 2, 3, or 4).
 *   - Base cases: For n = 2 return 1; for n = 3 return 2.
 */
class IntegerBreakMaxProduct {

    public static int integerBreak(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;

        int product = 1;

        // Greedily consume factors of 3
        while (n > 4) {
            product *= 3;
            n -= 3;
        }

        // Multiply remaining 2, 3, or 4
        product *= n;

        return product;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 343: Integer Break (Greedy Max Product Loop) ===");

        int[] testCases = { 2, 3, 4, 5, 6, 8, 10, 15 };

        for (int n : testCases) {
            int maxProd = integerBreak(n);
            System.out.printf("n = %2d ==> Max Product: %d%n", n, maxProd);
        }
    }
}

/*
 * Time Complexity: O(N / 3) = O(N) loop steps (or O(log N) with exponentiation).
 * Space Complexity: O(1) - Constant stack registers.
 */

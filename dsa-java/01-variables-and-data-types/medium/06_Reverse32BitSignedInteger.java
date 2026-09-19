/**
 * Problem Statement:
 * Given a signed 32-bit integer `x`, return `x` with its digits reversed.
 * If reversing `x` causes the value to go outside the signed 32-bit integer range
 * [-2^31, 2^31 - 1], then return 0.
 * Assume the environment does not allow storing 64-bit integers (`long` is prohibited in solution).
 * (LeetCode 7: Reverse Integer).
 *
 * Asked in: Amazon, Apple, Bloomberg, Microsoft
 *
 * Approach:
 * - Pop digits one by one: `pop = x % 10; x /= 10;`
 * - Before pushing `rev = rev * 10 + pop`, check if doing so will overflow:
 *     1. If `rev > Integer.MAX_VALUE / 10` or (`rev == Integer.MAX_VALUE / 10 && pop > 7`) -> return 0.
 *     2. If `rev < Integer.MIN_VALUE / 10` or (`rev == Integer.MIN_VALUE / 10 && pop < -8`) -> return 0.
 */
class Reverse32BitSignedInteger {

    public static int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;

            // Check for positive overflow
            if (rev > Integer.MAX_VALUE / 10 || (rev == Integer.MAX_VALUE / 10 && pop > 7)) {
                return 0;
            }
            // Check for negative underflow
            if (rev < Integer.MIN_VALUE / 10 || (rev == Integer.MIN_VALUE / 10 && pop < -8)) {
                return 0;
            }

            rev = rev * 10 + pop;
        }
        return rev;
    }

    public static void main(String[] args) {
        int[] testCases = {
            123,
            -123,
            120,
            0,
            1534236469, // Reversing this exceeds Integer.MAX_VALUE -> returns 0
            -2147483412,
            Integer.MAX_VALUE
        };

        System.out.println("=== LeetCode 7: Reverse 32-bit Integer ===");
        for (int x : testCases) {
            int reversed = reverse(x);
            System.out.printf("Input: %-12d ==> Output: %-12d%n", x, reversed);
        }
    }
}

/*
 * Time Complexity: O(log10 |x|) - Loop runs at most 10 times for 32-bit integer.
 * Space Complexity: O(1) - Constant stack space with zero 64-bit long promotion.
 */

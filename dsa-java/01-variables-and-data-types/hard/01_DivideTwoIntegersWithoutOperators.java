/**
 * Problem Statement:
 * Given two integers `dividend` and `divisor`, divide two integers without using
 * multiplication, division, and mod operator.
 * Return the quotient after dividing dividend by divisor.
 * Integer division should truncate toward zero.
 * Assume 32-bit signed integers; handle overflow when `dividend = -2147483648` and `divisor = -1`
 * (should clamp to `Integer.MAX_VALUE`).
 * (LeetCode 29: Divide Two Integers).
 *
 * Asked in: Facebook, Amazon, Google, Microsoft
 *
 * Approach:
 * - Exponential Bit Shifting (Bitwise Long Division):
 *   Instead of linear subtraction (which TLEs for 2^31 / 1), subtract largest multiples
 *   of divisor shifted by powers of two: `(divisor << shift)`.
 * - To prevent 32-bit overflow during negation of `Integer.MIN_VALUE`, convert both numbers
 *   to `long` or work entirely with negative numbers in two's complement.
 */
class DivideTwoIntegersWithoutOperators {

    public static int divide(int dividend, int divisor) {
        // Corner Case: Overflow on Integer.MIN_VALUE / -1
        if (dividend == Integer.MIN_VALUE && divisor == -1) {
            return Integer.MAX_VALUE;
        }

        // Determine sign of quotient
        boolean isNegative = (dividend < 0) ^ (divisor < 0);

        // Convert to long to avoid abs(Integer.MIN_VALUE) overflow
        long dvd = Math.abs((long) dividend);
        long dvs = Math.abs((long) divisor);

        int quotient = 0;

        // Exponential bit shift subtraction
        while (dvd >= dvs) {
            long tempDivisor = dvs;
            int multiple = 1;

            // Double the divisor as long as it fits inside dvd
            while (dvd >= (tempDivisor << 1)) {
                tempDivisor <<= 1;
                multiple <<= 1;
            }

            dvd -= tempDivisor;
            quotient += multiple;
        }

        return isNegative ? -quotient : quotient;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 29: Divide Two Integers (Bit Shifts) ===");

        int[][] testCases = {
            { 10, 3 },
            { 7, -3 },
            { 0, 1 },
            { -1, 1 },
            { Integer.MIN_VALUE, -1 },  // Overflow edge case
            { Integer.MIN_VALUE, 1 },
            { Integer.MIN_VALUE, 2 },
            { 2147483647, 2 }
        };

        for (int[] tc : testCases) {
            int dividend = tc[0];
            int divisor = tc[1];
            int result = divide(dividend, divisor);
            System.out.printf("Divide(%d, %d) ==> Quotient: %d%n", dividend, divisor, result);
        }
    }
}

/*
 * Time Complexity: O(log^2 N) - In each step we find the largest power of two multiple in O(log N).
 * Space Complexity: O(1) - Primitive register variables only.
 */

/**
 * Problem: Divide Two Integers (LeetCode 29)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * Given two integers dividend and divisor, divide them without using multiplication,
 * division, or mod operator. Truncate toward zero. Clamp to 32-bit signed integer range.
 * 
 * Approach - Bit Shift Division:
 * Binary long division: Starting from the highest power of 2 * divisor that fits into dividend,
 * subtract and accumulate quotient bits.
 * 
 * Edge case: dividend = Integer.MIN_VALUE and divisor = -1 overflows to Integer.MAX_VALUE.
 * 
 * Time Complexity: O(log^2 N)
 * Space Complexity: O(1)
 */
class DivideTwoIntegersBitShift {

    public static int divide(int dividend, int divisor) {
        // Handle overflow edge case
        if (dividend == Integer.MIN_VALUE && divisor == -1) {
            return Integer.MAX_VALUE;
        }

        // Determine sign of result
        boolean negative = (dividend < 0) != (divisor < 0);

        // Work with positive long values to avoid overflow
        long a = Math.abs((long) dividend);
        long b = Math.abs((long) divisor);
        long quotient = 0;

        while (a >= b) {
            long temp = b;
            long multiple = 1;

            // Find the largest multiple of b that fits into a
            while (a >= (temp << 1)) {
                temp <<= 1;
                multiple <<= 1;
            }

            a -= temp;
            quotient += multiple;
        }

        return negative ? (int) -quotient : (int) quotient;
    }

    public static void main(String[] args) {
        System.out.println("10 / 3 = " + divide(10, 3) + " (Expected: 3)");
        System.out.println("7 / -3 = " + divide(7, -3) + " (Expected: -2)");
        System.out.println("MIN_VALUE / -1 = " + divide(Integer.MIN_VALUE, -1) + " (Expected: 2147483647)");
    }
}

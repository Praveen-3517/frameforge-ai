/**
 * Problem Statement:
 * Multiply a given integer `n` by 7 without using the multiplication (*) operator.
 * Extend this pattern to demonstrate how compilers optimize constant multiplications
 * using shift-and-add / shift-and-subtract sequences.
 *
 * Example:
 * n = 4  -> 28
 * n = -3 -> -21
 *
 * Asked in: Adobe, Qualcomm, Samsung, TCS
 *
 * Approach:
 * - Mathematical Decomposition:
 *   7 * n = (8 - 1) * n = (8 * n) - n
 * - Bitwise Left Shift:
 *   Multiplying by powers of two is equivalent to left shifting: 8 * n == (n << 3).
 *   Therefore: `(n << 3) - n`.
 * - Precedence Gotcha:
 *   Bitwise shifts `<<` have lower precedence than subtraction `-`!
 *   Writing `n << 3 - n` evaluates as `n << (3 - n)`, leading to catastrophic bugs!
 *   Always enclose shift operations in parentheses: `((n << 3) - n)`.
 */
class MultiplyBySevenBitwise {

    public static int multiplyBy7(int n) {
        // Correct parentheses to prevent precedence bug: << has lower precedence than -
        return (n << 3) - n;
    }

    public static int multiplyBy9(int n) {
        // 9 * n = 8 * n + n
        return (n << 3) + n;
    }

    public static int multiplyBy15(int n) {
        // 15 * n = 16 * n - n
        return (n << 4) - n;
    }

    public static void main(String[] args) {
        System.out.println("=== Multiply by 7 (and other constants) Without '*' Operator ===");

        int[] testCases = { 0, 1, 4, -3, 10, -12, 1000 };

        for (int n : testCases) {
            int by7 = multiplyBy7(n);
            int by9 = multiplyBy9(n);
            int by15 = multiplyBy15(n);
            System.out.printf("n = %5d ==> *7: %6d | *9: %6d | *15: %6d (Verified: %s)%n",
                    n, by7, by9, by15, (by7 == n * 7) ? "OK" : "ERROR");
        }
    }
}

/*
 * Time Complexity: O(1) - Bitwise shift and subtraction run in 1 CPU cycle.
 * Space Complexity: O(1) - Constant stack registers.
 */

/**
 * Problem Statement:
 * In Java, all numeric primitive types (byte, short, int, long) are signed (two's complement).
 * There are no native `unsigned int` keywords like in C/C++.
 * Demonstrate how to:
 * 1. Treat a 32-bit `int` as an unsigned 32-bit value [0, 2^32 - 1].
 * 2. Compare two integers as unsigned values.
 * 3. Divide and parse unsigned integers.
 * Compare manual masking `(n & 0xFFFFFFFFL)` with Java 8's `Integer.compareUnsigned`.
 *
 * Asked in: Google, Microsoft, Qualcomm
 *
 * Approach:
 * - Negative signed numbers (e.g., `-1`) have their MSB set to 1.
 * - In unsigned 32-bit arithmetic, `0xFFFFFFFF` is `4,294,967,295`, the maximum possible value!
 * - Standard signed comparison: `-1 < 1` is `true`.
 * - Unsigned comparison: `-1` (4294967295) `>` `1` is `true`!
 * - In Java 8+, `Integer.compareUnsigned(x, y)` provides this directly.
 * - Manually, we can convert both to `long` with `x & 0xFFFFFFFFL` and compare.
 */
class UnsignedIntComparison {

    // Manual unsigned comparison using 64-bit mask
    public static int compareUnsignedManual(int x, int y) {
        long ux = x & 0xFFFFFFFFL;
        long uy = y & 0xFFFFFFFFL;
        return Long.compare(ux, uy);
    }

    public static String toUnsignedStringManual(int x) {
        long ux = x & 0xFFFFFFFFL;
        return Long.toString(ux);
    }

    public static void main(String[] args) {
        int a = -1; // Binary: 11111111 11111111 11111111 11111111
        int b = 1;  // Binary: 00000000 00000000 00000000 00000001

        System.out.println("=== Signed vs. Unsigned Integer Semantics ===");
        System.out.println("Variable a = " + a + " (Signed Decimal)");
        System.out.println("Variable a = " + Integer.toUnsignedString(a) + " (Unsigned Decimal)");
        System.out.println("Variable b = " + b);

        System.out.println("\n--- Comparison Results ---");
        System.out.println("Standard Signed (a < b):       " + (a < b)); // true (-1 < 1)
        System.out.println("Integer.compareUnsigned(a, b): " + (Integer.compareUnsigned(a, b) > 0 ? "a > b" : "a <= b")); // a > b
        System.out.println("Manual Masked Compare(a, b):   " + (compareUnsignedManual(a, b) > 0 ? "a > b" : "a <= b"));

        // Division demonstration
        int dividend = -1; // 4294967295
        int divisor = 2;
        int unsignedDivResult = Integer.divideUnsigned(dividend, divisor);
        System.out.println("\nUnsigned Division of -1 (4294967295) / 2 = " + Integer.toUnsignedString(unsignedDivResult));
    }
}

/*
 * Time Complexity: O(1) - Single instruction primitive bitmasking and branchless comparison.
 * Space Complexity: O(1) - Stack allocation.
 */

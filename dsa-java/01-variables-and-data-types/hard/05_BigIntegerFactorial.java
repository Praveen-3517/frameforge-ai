import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Problem Statement:
 * Compute the factorial of large integers (e.g., 100!, 200!) where the answer has hundreds of digits
 * and far exceeds the 64-bit capacity of Java's primitive `long` (20! is the maximum `long`).
 * Solve this without using Java's built-in `BigInteger` class by simulating arbitrary-precision
 * multiplication using an array/list of digits.
 * Then verify accuracy against `java.math.BigInteger`.
 *
 * Asked in: Amazon, Microsoft, TCS CodeVita, Infosys InfyTQ
 *
 * Approach:
 * - Represent the large number as a list of decimal digits stored in reverse order
 *   (index 0 is least significant digit / units place).
 * - For multiplying by integer `x`:
 *   Multiply each digit by `x`, add `carry`, compute new digit `sum % 10`, and update `carry = sum / 10`.
 *   After processing all existing digits, append remaining carry digits.
 * - Format the result by reversing the list back to standard representation.
 */
class BigIntegerFactorial {

    // Custom arbitrary precision factorial implementation without BigInteger
    public static String computeFactorialCustom(int n) {
        if (n < 0) return "Undefined";
        if (n == 0 || n == 1) return "1";

        List<Integer> digits = new ArrayList<>();
        digits.add(1); // 1! = 1

        for (int factor = 2; factor <= n; factor++) {
            int carry = 0;
            for (int i = 0; i < digits.size(); i++) {
                int product = digits.get(i) * factor + carry;
                digits.set(i, product % 10);
                carry = product / 10;
            }

            // Append leftover carry
            while (carry > 0) {
                digits.add(carry % 10);
                carry /= 10;
            }
        }

        // Reverse to standard big-endian display
        StringBuilder sb = new StringBuilder(digits.size());
        for (int i = digits.size() - 1; i >= 0; i--) {
            sb.append(digits.get(i));
        }
        return sb.toString();
    }

    // Built-in reference implementation for validation
    public static BigInteger computeFactorialBuiltIn(int n) {
        BigInteger result = BigInteger.ONE;
        for (int i = 2; i <= n; i++) {
            result = result.multiply(BigInteger.valueOf(i));
        }
        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== Arbitrary-Precision Factorial (Custom Array vs BigInteger) ===");

        int[] testCases = { 5, 10, 20, 30, 50, 100 };

        for (int n : testCases) {
            String customAns = computeFactorialCustom(n);
            BigInteger builtInAns = computeFactorialBuiltIn(n);

            boolean isMatch = customAns.equals(builtInAns.toString());
            System.out.printf("Factorial(%d):%n", n);
            System.out.printf("  Digit Count : %d digits%n", customAns.length());
            if (customAns.length() <= 80) {
                System.out.printf("  Result      : %s%n", customAns);
            } else {
                System.out.printf("  Result      : %s...%s (truncated)%n",
                        customAns.substring(0, 35),
                        customAns.substring(customAns.length() - 35));
            }
            System.out.printf("  Matches BigInteger: %s%n%n", isMatch ? "YES (100% Correct)" : "FAIL");
        }
    }
}

/*
 * Time Complexity: O(N * D) where N is the factorial target and D is the number of digits in N!
 *                  By Stirling's approximation, D ≈ O(N log N), making total time O(N^2 log N).
 * Space Complexity: O(N log N) - Memory required to store the decimal digits.
 */

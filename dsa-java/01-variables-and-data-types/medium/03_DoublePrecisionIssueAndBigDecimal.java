/**
 * Problem Statement:
 * Demonstrate the fundamental IEEE 754 floating-point precision limitation
 * where `0.1 + 0.2 != 0.3` in Java `double`/`float`.
 * Provide the industry standard solution using `java.math.BigDecimal` for financial applications.
 *
 * Asked in: Goldman Sachs, Morgan Stanley, Amazon, PayPal
 *
 * Approach:
 * - Binary computers cannot accurately represent decimal fractions whose denominators
 *   contain prime factors other than 2 (e.g., 1/10 has factor 5).
 * - `0.1` in binary is an infinite repeating fraction: `0.0001100110011..._2`.
 * - Rounding errors accumulate during arithmetic operations.
 * - Solution: `BigDecimal` stores arbitrary-precision unscaled integer and a 32-bit integer scale.
 * - Golden Rule: ALWAYS instantiate `BigDecimal` using the `String` constructor `new BigDecimal("0.1")`
 *   or `BigDecimal.valueOf(0.1)`, NEVER `new BigDecimal(0.1)`.
 */
import java.math.BigDecimal;
import java.math.RoundingMode;

class DoublePrecisionIssueAndBigDecimal {

    public static void demonstrateDoubleError() {
        System.out.println("--- 1. The Classic IEEE 754 Floating-Point Inaccuracy ---");
        double a = 0.1;
        double b = 0.2;
        double sum = a + b;

        System.out.println("a = " + a);
        System.out.println("b = " + b);
        System.out.println("a + b = " + sum); // 0.30000000000000004
        System.out.println("Is (a + b == 0.3)? " + (sum == 0.3)); // false
    }

    public static void demonstrateBigDecimalSolution() {
        System.out.println("\n--- 2. The Financial Solution: BigDecimal ---");
        // Correct way: String constructor avoids binary approximation
        BigDecimal bd1 = new BigDecimal("0.1");
        BigDecimal bd2 = new BigDecimal("0.2");
        BigDecimal bdSum = bd1.add(bd2);

        System.out.println("BigDecimal(\"0.1\") + BigDecimal(\"0.2\") = " + bdSum);
        System.out.println("Is bdSum.compareTo(new BigDecimal(\"0.3\")) == 0? " +
                (bdSum.compareTo(new BigDecimal("0.3")) == 0)); // true
    }

    public static void demonstrateBigDecimalPitfall() {
        System.out.println("\n--- 3. Common Pitfall: new BigDecimal(double) vs new BigDecimal(String) ---");
        BigDecimal bad = new BigDecimal(0.1);
        BigDecimal good = new BigDecimal("0.1");

        System.out.println("new BigDecimal(0.1)   => " + bad);  // 0.1000000000000000055511151231257827021181583404541015625
        System.out.println("new BigDecimal(\"0.1\") => " + good); // 0.1 (exact!)
    }

    public static void demonstrateFinancialRounding() {
        System.out.println("\n--- 4. Financial Currency Rounding (HALF_EVEN / Banker's Rounding) ---");
        BigDecimal price = new BigDecimal("49.995");
        BigDecimal rounded = price.setScale(2, RoundingMode.HALF_EVEN);
        System.out.println("Original Price: " + price + " -> Rounded to 2 decimal places: " + rounded);
    }

    public static void main(String[] args) {
        demonstrateDoubleError();
        demonstrateBigDecimalSolution();
        demonstrateBigDecimalPitfall();
        demonstrateFinancialRounding();
    }
}

/*
 * Time Complexity:
 *   - double operations: O(1) in hardware FPU.
 *   - BigDecimal operations: O(N) where N is the number of digits.
 * Space Complexity:
 *   - double: O(1) primitive stack.
 *   - BigDecimal: O(N) heap object memory.
 */

/**
 * Problem Statement:
 * Demonstrate relational operators (<, <=, >, >=, ==, !=) and logical operators (&&, ||, !).
 * Show the difference between:
 * 1. Short-circuit logical AND (&&) and non-short-circuit bitwise AND (&) when evaluating booleans.
 * 2. Short-circuit logical OR (||) and non-short-circuit bitwise OR (|).
 * 3. How short-circuit evaluation guarantees NullPointer safety and prevents Division by Zero.
 *
 * Asked in: Infosys, Accenture, Oracle, Wipro
 *
 * Approach:
 * - `&&` evaluates right-hand operand ONLY if left-hand operand is true.
 * - `||` evaluates right-hand operand ONLY if left-hand operand is false.
 * - `&` and `|` always evaluate BOTH operands, even if the result is already determined.
 * - Practical idiom: `if (obj != null && obj.isValid())` prevents NullPointerException.
 * - Practical idiom: `if (b != 0 && a / b > 2)` prevents ArithmeticException.
 */
class RelationalAndLogicalDemo {

    public static boolean sideEffectMethod(String name, boolean returnValue) {
        System.out.println("   [Side Effect Executed]: Method " + name + " was called!");
        return returnValue;
    }

    public static void demonstrateShortCircuitAND() {
        System.out.println("--- Short-Circuit (&&) vs Non-Short-Circuit (&) ---");

        System.out.println("Test 1: false && sideEffectMethod()");
        boolean r1 = false && sideEffectMethod("AND_Short", true);
        System.out.println("Result: " + r1 + " (Notice side effect was NOT called)");

        System.out.println("\nTest 2: false & sideEffectMethod()");
        boolean r2 = false & sideEffectMethod("AND_NonShort", true);
        System.out.println("Result: " + r2 + " (Notice side effect WAS called!)");
    }

    public static void demonstrateShortCircuitOR() {
        System.out.println("\n--- Short-Circuit (||) vs Non-Short-Circuit (|) ---");

        System.out.println("Test 1: true || sideEffectMethod()");
        boolean r1 = true || sideEffectMethod("OR_Short", true);
        System.out.println("Result: " + r1 + " (Notice side effect was NOT called)");

        System.out.println("\nTest 2: true | sideEffectMethod()");
        boolean r2 = true | sideEffectMethod("OR_NonShort", true);
        System.out.println("Result: " + r2 + " (Notice side effect WAS called!)");
    }

    public static void demonstrateExceptionSafety() {
        System.out.println("\n--- Real World Safety: Guarding Against Exceptions ---");

        String str = null;
        // Safe: short-circuits on str != null
        if (str != null && str.length() > 5) {
            System.out.println("String is valid");
        } else {
            System.out.println("Safely caught null string without NullPointerException!");
        }

        int divisor = 0;
        // Safe: short-circuits on divisor != 0
        if (divisor != 0 && (100 / divisor) > 5) {
            System.out.println("Quotient check passed");
        } else {
            System.out.println("Safely bypassed division by zero without ArithmeticException!");
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 02 (Easy): Relational & Logical Short-Circuit Operators ===");
        demonstrateShortCircuitAND();
        demonstrateShortCircuitOR();
        demonstrateExceptionSafety();
    }
}

/*
 * Time Complexity: O(1) - Boolean comparisons and condition branching.
 * Space Complexity: O(1) - Constant stack space.
 */

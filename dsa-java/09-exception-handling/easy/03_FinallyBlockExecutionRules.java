/*
 * Problem Statement:
 * Demonstrate the strict execution semantics of Java's `finally` block:
 * 1. `finally` executes when NO exception occurs.
 * 2. `finally` executes when an exception IS thrown and caught.
 * 3. `finally` executes even when a `return` statement is encountered inside `try` or `catch`.
 * 4. Understand that `finally` overrides return values of `try` if it also contains `return`
 *    (an anti-pattern to avoid in production).
 * 
 * Asked in: Amazon, Oracle, Goldman Sachs, Cisco
 */

class FinallyBlockExecutionRules {

    public static int testReturnWithFinally(boolean triggerException) {
        try {
            System.out.println("  [Try] Executing try block...");
            if (triggerException) {
                int x = 10 / 0; // Throws ArithmeticException
            }
            return 100; // Return value from try
        } catch (ArithmeticException e) {
            System.out.println("  [Catch] Caught ArithmeticException.");
            return 200; // Return value from catch
        } finally {
            System.out.println("  [Finally] Executing cleanup code in finally block.");
        }
    }

    public static int testFinallyOverride() {
        try {
            return 1;
        } finally {
            // Anti-pattern: return in finally overrides previous return!
            return 2;
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Scenario 1: No Exception ---");
        int res1 = testReturnWithFinally(false);
        System.out.println("Result returned: " + res1);

        System.out.println("\n--- Scenario 2: Exception Occurs and Caught ---");
        int res2 = testReturnWithFinally(true);
        System.out.println("Result returned: " + res2);

        System.out.println("\n--- Scenario 3: Finally Overriding Return ---");
        int res3 = testFinallyOverride();
        System.out.println("Result returned (overridden by finally): " + res3);
    }
}

/*
 * Time Complexity: O(1) linear execution of try-catch-finally.
 * Space Complexity: O(1) stack memory.
 */

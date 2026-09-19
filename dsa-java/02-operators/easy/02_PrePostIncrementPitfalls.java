/**
 * Problem Statement:
 * Analyze and demonstrate Java's increment and decrement operators (++ and --):
 * 1. Difference between pre-increment (++x) and post-increment (x++).
 * 2. The classic Java trap: `x = x++` and why `x` remains unchanged.
 * 3. Left-to-right operand evaluation in compound expressions like `x++ + ++x`.
 *
 * Asked in: Amazon, TCS, Wipro, Cognizant, Capgemini
 *
 * Approach:
 * - Pre-increment (`++x`): Increments value first, then evaluates to new value.
 * - Post-increment (`x++`): Evaluates to current value first, then increments the variable.
 * - `x = x++` Trap:
 *   In Java, evaluation order is strictly Left-to-Right.
 *   The RHS `x++` produces the current value of x (say 5), and internally increments x to 6.
 *   Then the assignment `=` writes the produced value (5) back to x, wiping out the increment!
 * - In complex expressions: `int a = 5; int res = a++ + ++a * a--;`
 *   Break down step-by-step strictly from left to right.
 */
class PrePostIncrementPitfalls {

    public static void testAssignmentTrap() {
        System.out.println("--- The Classic 'x = x++' Trap ---");
        int x = 5;
        x = x++;
        System.out.println("Result of 'x = x++' when x was 5: " + x + " (Expected 5 in Java)");

        int y = 5;
        y = ++y;
        System.out.println("Result of 'y = ++y' when y was 5: " + y + " (Expected 6)");
    }

    public static void testComplexExpression() {
        System.out.println("\n--- Complex Multi-Operator Expression ---");
        int a = 5;
        // Evaluation order:
        // 1. a++ evaluates to 5, 'a' becomes 6
        // 2. ++a increments 'a' to 7, evaluates to 7
        // 3. a-- evaluates to 7, 'a' becomes 6
        // Precedence: * happens before +
        // res = 5 + (7 * 7) = 5 + 49 = 54
        int res = a++ + ++a * a--;
        System.out.println("Expression: a++ + ++a * a-- (with initial a = 5)");
        System.out.println("Computed Result: " + res);
        System.out.println("Final Value of a: " + a);
    }

    public static void testLoopBehavior() {
        System.out.println("\n--- Post-increment in Loop Condition ---");
        int count = 0;
        while (count++ < 3) {
            System.out.println("Inside loop, count value is: " + count);
        }
        System.out.println("After loop, count value is: " + count);
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 02 (Easy): Pre/Post Increment Mechanics & Gotchas ===");
        testAssignmentTrap();
        testComplexExpression();
        testLoopBehavior();
    }
}

/*
 * Time Complexity: O(1) - Primitive register increments and loads.
 * Space Complexity: O(1) - Constant local variable storage.
 */

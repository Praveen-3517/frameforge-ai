/**
 * Problem Statement:
 * Given three integers a, b, and c, determine the maximum and minimum values using
 * the ternary conditional operator (? :) without using Math.max / Math.min.
 * Also demonstrate the subtle Java numeric type promotion rules inside ternary expressions.
 *
 * Asked in: Capgemini, TCS, Wipro, Cognizant
 *
 * Approach:
 * - Nested Ternary:
 *   `max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);`
 * - Type Promotion Rule in Ternary:
 *   If the second and third operands of `? :` have different numeric types (e.g., int and double),
 *   the result is promoted to the common wider type (binary numeric promotion), even if the
 *   branch selected is an int!
 *   Example: `true ? 1 : 2.0` results in `1.0` (double)!
 */
class TernaryMaxOfThree {

    public static int findMax(int a, int b, int c) {
        return (a >= b) ? ((a >= c) ? a : c) : ((b >= c) ? b : c);
    }

    public static int findMin(int a, int b, int c) {
        return (a <= b) ? ((a <= c) ? a : c) : ((b <= c) ? b : c);
    }

    public static void testTypePromotionTrap() {
        System.out.println("--- Ternary Type Promotion Trap ---");
        // Operand 2 is int (1), Operand 3 is double (2.0)
        // Expression evaluates to Double 1.0, not Integer 1!
        Number result = true ? Integer.valueOf(1) : Double.valueOf(2.0);
        System.out.println("Expression: true ? Integer.valueOf(1) : Double.valueOf(2.0)");
        System.out.println("Result Value : " + result);
        System.out.println("Result Type  : " + result.getClass().getName());

        char ch = true ? 'X' : 65536; // 65536 doesn't fit in char, promotes to int!
        System.out.println("Expression: true ? 'X' : 65536 -> Promotes 'X' to ASCII int: " + (int) ch);
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 02 (Easy): Ternary Conditional Operator & Type Promotion ===");

        int[][] testTriplets = {
            { 10, 25, 15 },
            { -5, -20, -1 },
            { 100, 100, 50 },
            { 42, 42, 42 }
        };

        for (int[] t : testTriplets) {
            int a = t[0], b = t[1], c = t[2];
            int max = findMax(a, b, c);
            int min = findMin(a, b, c);
            System.out.printf("Inputs: (%d, %d, %d) ==> Max: %d | Min: %d%n", a, b, c, max, min);
        }

        System.out.println();
        testTypePromotionTrap();
    }
}

/*
 * Time Complexity: O(1) - Constant number of comparisons.
 * Space Complexity: O(1) - Primitive register variables only.
 */

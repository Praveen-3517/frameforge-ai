/**
 * Problem Statement:
 * Demonstrate the behavior of Java's arithmetic operators (+, -, *, /, %) with special attention to:
 * 1. Integer division truncation (towards zero).
 * 2. Division and modulo by zero exceptions (ArithmeticException for ints vs Infinity/NaN for floats).
 * 3. Modulo behavior with negative numbers: (-a % b), (a % -b), and comparison with Math.floorMod().
 *
 * Asked in: TCS, Infosys, Cognizant, Wipro
 *
 * Approach:
 * - In Java, integer division truncates decimal fractions towards 0: 7 / 2 = 3 and -7 / 2 = -3.
 * - Floating point division by zero yields Infinity or NaN, never throwing ArithmeticException.
 * - The sign of `a % b` in Java always takes the sign of dividend `a`.
 * - `Math.floorMod(a, b)` follows mathematical Euclidean definition where the result matches the sign of divisor `b`.
 */
class ArithmeticOperationsAndModDemo {

    public static void demonstrateDivision() {
        System.out.println("--- Integer Truncation vs Float Division ---");
        int a = 7, b = 2;
        System.out.println("7 / 2 (int)         : " + (a / b));
        System.out.println("-7 / 2 (int)        : " + (-a / b));
        System.out.println("7.0 / 2 (double)    : " + (7.0 / b));
        System.out.println("1.0 / 0.0 (float)   : " + (1.0 / 0.0));
        System.out.println("-1.0 / 0.0 (float)  : " + (-1.0 / 0.0));
        System.out.println("0.0 / 0.0 (float)   : " + (0.0 / 0.0));
    }

    public static void demonstrateModuloRules() {
        System.out.println("\n--- Java % Operator vs Math.floorMod() ---");
        int[][] pairs = { { 7, 3 }, { -7, 3 }, { 7, -3 }, { -7, -3 } };

        for (int[] p : pairs) {
            int dividend = p[0];
            int divisor = p[1];
            int javaMod = dividend % divisor;
            int mathFloorMod = Math.floorMod(dividend, divisor);

            System.out.printf("%4d %% %4d ==> Java %%: %2d | Math.floorMod(): %2d%n",
                    dividend, divisor, javaMod, mathFloorMod);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 02 (Easy): Arithmetic Operators & Modulo Deep Dive ===");
        demonstrateDivision();
        demonstrateModuloRules();
    }
}

/*
 * Time Complexity: O(1) - Constant time CPU arithmetic operations.
 * Space Complexity: O(1) - Uses only stack registers.
 */

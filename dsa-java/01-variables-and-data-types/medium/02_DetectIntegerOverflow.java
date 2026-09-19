/**
 * Problem Statement:
 * Given two 32-bit integers `a` and `b`, detect whether their addition `a + b`
 * or multiplication `a * b` will result in an arithmetic overflow, BEFORE performing the operation.
 * Compare manual condition checks with Java 8's `Math.addExact` / `Math.multiplyExact`.
 *
 * Asked in: Google, Microsoft, Bloomberg
 *
 * Approach:
 * Addition Overflow Conditions:
 *   If b > 0 and a > Integer.MAX_VALUE - b  --> Overflow
 *   If b < 0 and a < Integer.MIN_VALUE - b  --> Underflow
 *
 * Multiplication Overflow Conditions:
 *   If a > 0, b > 0 and a > Integer.MAX_VALUE / b  --> Overflow
 *   If a > 0, b < 0 and b < Integer.MIN_VALUE / a  --> Underflow
 *   If a < 0, b > 0 and a < Integer.MIN_VALUE / b  --> Underflow
 *   If a < 0, b < 0 and a < Integer.MAX_VALUE / b  --> Overflow
 *
 * Java 8+ provides `Math.addExact` and `Math.multiplyExact` which throw `ArithmeticException`.
 */
class DetectIntegerOverflow {

    public static boolean willAdditionOverflow(int a, int b) {
        if (b > 0 && a > Integer.MAX_VALUE - b) return true;
        if (b < 0 && a < Integer.MIN_VALUE - b) return true;
        return false;
    }

    public static boolean willMultiplicationOverflow(int a, int b) {
        if (a == 0 || b == 0) return false;
        if (a > 0) {
            if (b > 0) return a > Integer.MAX_VALUE / b;
            else       return b < Integer.MIN_VALUE / a;
        } else {
            if (b > 0) return a < Integer.MIN_VALUE / b;
            else       return a < Integer.MAX_VALUE / b;
        }
    }

    public static void main(String[] args) {
        System.out.println("=== 32-bit Integer Addition Overflow Tests ===");
        int[][] addPairs = {
            { 1000, 2000 },
            { Integer.MAX_VALUE, 1 },
            { Integer.MAX_VALUE - 10, 15 },
            { Integer.MIN_VALUE, -1 }
        };

        for (int[] pair : addPairs) {
            int a = pair[0], b = pair[1];
            boolean manualCheck = willAdditionOverflow(a, b);
            boolean builtInThrew = false;
            try {
                Math.addExact(a, b);
            } catch (ArithmeticException e) {
                builtInThrew = true;
            }
            System.out.printf("Add(%d, %d) -> Manual Overflow: %-5b | Math.addExact Threw: %-5b%n",
                    a, b, manualCheck, builtInThrew);
        }

        System.out.println("\n=== 32-bit Integer Multiplication Overflow Tests ===");
        int[][] multPairs = {
            { 100, 500 },
            { 100000, 100000 },
            { Integer.MAX_VALUE / 2, 3 },
            { -100000, 100000 }
        };

        for (int[] pair : multPairs) {
            int a = pair[0], b = pair[1];
            boolean manualCheck = willMultiplicationOverflow(a, b);
            boolean builtInThrew = false;
            try {
                Math.multiplyExact(a, b);
            } catch (ArithmeticException e) {
                builtInThrew = true;
            }
            System.out.printf("Mult(%d, %d) -> Manual Overflow: %-5b | Math.multiplyExact Threw: %-5b%n",
                    a, b, manualCheck, builtInThrew);
        }
    }
}

/*
 * Time Complexity: O(1) - Constant integer comparisons and divisions.
 * Space Complexity: O(1) - Zero extra heap memory.
 */

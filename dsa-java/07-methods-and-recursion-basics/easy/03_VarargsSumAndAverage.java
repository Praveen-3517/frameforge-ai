/**
 * Problem Statement:
 * Implement variable argument (varargs: `int... numbers`) utility methods in Java to calculate:
 * 1. Total sum
 * 2. Average (mean)
 * 3. Minimum and Maximum values
 * Discuss the two fundamental language rules for Varargs in Java:
 *   Rule 1: Varargs must be the LAST parameter in the method declaration.
 *   Rule 2: A method can have at most ONE varargs parameter.
 *
 * Asked in: TCS, Infosys, Wipro, Accenture
 *
 * Approach:
 * - Varargs Desugaring:
 *   The compiler internally rewrites `int... numbers` to `int[] numbers`.
 *   At call sites, `calculateSum(1, 2, 3)` is rewritten to `calculateSum(new int[] { 1, 2, 3 })`.
 * - Zero-argument call handling: Check `numbers.length == 0`.
 */
class VarargsSumAndAverage {

    public static long calculateSum(int... numbers) {
        long sum = 0;
        for (int n : numbers) {
            sum += n;
        }
        return sum;
    }

    public static double calculateAverage(int... numbers) {
        if (numbers.length == 0) return 0.0;
        return (double) calculateSum(numbers) / numbers.length;
    }

    public static int findMax(int first, int... rest) {
        // Enforcing at least one argument at compile-time by separating first parameter!
        int max = first;
        for (int n : rest) {
            if (n > max) max = n;
        }
        return max;
    }

    public static void main(String[] args) {
        System.out.println("=== Java Variable Arguments (Varargs) Utility Suite ===");

        System.out.println("Sum of (10, 20, 30)            : " + calculateSum(10, 20, 30));
        System.out.println("Sum of (1, 2, 3, 4, 5, 6, 7, 8): " + calculateSum(1, 2, 3, 4, 5, 6, 7, 8));
        System.out.println("Sum of zero arguments ()       : " + calculateSum());

        System.out.printf("Average of (15, 25, 35, 45)    : %.2f%n", calculateAverage(15, 25, 35, 45));
        System.out.println("Max of (5, 99, -10, 42, 88)    : " + findMax(5, 99, -10, 42, 88));
    }
}

/*
 * Time Complexity: O(K) where K is the number of vararg arguments.
 * Space Complexity: O(K) - Compiler allocates array for vararg arguments.
 */

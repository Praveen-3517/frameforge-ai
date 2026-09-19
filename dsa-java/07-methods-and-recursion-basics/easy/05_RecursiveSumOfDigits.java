/**
 * Problem Statement:
 * 1. Compute the sum of digits of an integer `n` recursively.
 * 2. Compute the recursive Digital Root (repeatedly summing digits until a single digit remains).
 *
 * Example:
 * n = 9875 -> Sum = 9 + 8 + 7 + 5 = 29 -> Digital Root = 2 + 9 = 11 -> 1 + 1 = 2
 *
 * Asked in: Infosys, Capgemini, TCS, Wipro
 *
 * Approach:
 * - Recursive Sum of Digits:
 *   Base Case: If `n == 0`, return 0.
 *   Recursive Step: `(n % 10) + sumOfDigits(n / 10)`.
 * - Recursive Digital Root:
 *   Base Case: If `n < 10`, return `n`.
 *   Recursive Step: `digitalRoot(sumOfDigits(n))`.
 */
class RecursiveSumOfDigits {

    public static int sumOfDigits(int n) {
        n = Math.abs(n);
        if (n == 0) return 0;
        return (n % 10) + sumOfDigits(n / 10);
    }

    public static int digitalRoot(int n) {
        n = Math.abs(n);
        if (n < 10) return n;
        return digitalRoot(sumOfDigits(n));
    }

    public static void main(String[] args) {
        System.out.println("=== Recursive Sum of Digits & Digital Root ===");

        int[] testNumbers = { 0, 7, 1234, 9875, 999999, -456 };

        for (int num : testNumbers) {
            int sum = sumOfDigits(num);
            int root = digitalRoot(num);
            System.out.printf("Number: %7d ==> Digit Sum: %2d | Digital Root: %d%n",
                    num, sum, root);
        }
    }
}

/*
 * Time Complexity: O(log10 N) - One recursive call per digit.
 * Space Complexity: O(log10 N) - Stack frames bounded by the number of decimal digits.
 */

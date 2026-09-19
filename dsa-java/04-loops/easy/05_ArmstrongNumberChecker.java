/**
 * Problem Statement:
 * Determine whether a given positive integer `n` is an Armstrong Number (also known as a
 * Narcissistic Number).
 * An Armstrong number of K digits is an integer such that the sum of its digits each raised
 * to the power of K is equal to the number itself.
 *
 * Example:
 * 153 (3 digits): 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153 (Armstrong!)
 * 1634 (4 digits): 1^4 + 6^4 + 3^4 + 4^4 = 1 + 1296 + 81 + 256 = 1634 (Armstrong!)
 * 370 (3 digits): 3^3 + 7^3 + 0^3 = 27 + 343 + 0 = 370 (Armstrong!)
 *
 * Asked in: TCS, Infosys, Cognizant, Wipro, Capgemini
 *
 * Approach:
 * - Two-pass loop algorithm:
 *   1. Loop 1 (Count digits):
 *      Count the total number of decimal digits `k` in `n`.
 *   2. Loop 2 (Accumulate power sums):
 *      Extract each digit `d = temp % 10`.
 *      Compute `d^k` (using fast integer multiplication loop instead of floating-point `Math.pow`).
 *      Accumulate `sum += d^k`.
 *   3. Compare `sum == n`.
 */
class ArmstrongNumberChecker {

    // Fast integer power to avoid floating-point inaccuracies
    private static long intPow(int base, int exp) {
        long result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
    }

    public static boolean isArmstrong(int n) {
        if (n < 0) return false;

        // Step 1: Count number of digits
        int k = 0;
        int temp = n;
        while (temp > 0) {
            k++;
            temp /= 10;
        }

        // 0 is considered an Armstrong number (0^1 = 0)
        if (n == 0) return true;

        // Step 2: Sum of digits raised to power k
        long sum = 0;
        temp = n;
        while (temp > 0) {
            int digit = temp % 10;
            sum += intPow(digit, k);
            temp /= 10;
        }

        return sum == n;
    }

    public static void main(String[] args) {
        System.out.println("=== Armstrong / Narcissistic Number Checker ===");

        int[] testNumbers = { 0, 1, 9, 153, 370, 371, 407, 1634, 8208, 9474, 100, 125, 54748 };

        for (int num : testNumbers) {
            System.out.printf("Number: %6d ==> Is Armstrong: %s%n", num, isArmstrong(num));
        }
    }
}

/*
 * Time Complexity: O(log10 N) - Two passes over the digits of N.
 * Space Complexity: O(1) - Constant stack registers.
 */

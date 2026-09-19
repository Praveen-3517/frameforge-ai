/**
 * Problem Statement:
 * Given an integer `n`:
 * 1. Reverse its digits using an iterative `while` loop.
 * 2. Determine whether the original number is a Palindrome (reads the same forwards and backwards).
 * Note: Negative numbers can never be palindromes because of the leading '-' sign.
 * (LeetCode 9: Palindrome Number).
 *
 * Asked in: TCS, Infosys, Amazon, Microsoft, Wipro
 *
 * Approach:
 * - Digit Extraction Loop:
 *   - While `temp != 0`:
 *     Extract last digit: `int digit = temp % 10;`
 *     Append to reversed number: `reversed = reversed * 10 + digit;`
 *     Truncate last digit: `temp /= 10;`
 * - Palindrome check:
 *   If original `n < 0`, return false immediately.
 *   Otherwise, `n == reversed`.
 */
class ReverseNumberAndPalindrome {

    public static long reverseDigits(int n) {
        long reversed = 0;
        int temp = Math.abs(n);

        while (temp > 0) {
            int digit = temp % 10;
            reversed = reversed * 10 + digit;
            temp /= 10;
        }

        return (n < 0) ? -reversed : reversed;
    }

    public static boolean isPalindrome(int n) {
        // Negative numbers are not palindromes
        // Also numbers ending in 0 (except 0 itself) cannot be palindromes
        if (n < 0 || (n % 10 == 0 && n != 0)) {
            return false;
        }

        long reversed = reverseDigits(n);
        return reversed == n;
    }

    public static void main(String[] args) {
        System.out.println("=== Iterative Digit Reversal & Palindrome Checker ===");

        int[] testNumbers = { 121, -121, 10, 0, 1234321, 12345, 9, 1000000001 };

        for (int n : testNumbers) {
            long rev = reverseDigits(n);
            boolean pal = isPalindrome(n);
            System.out.printf("Number: %11d | Reversed: %11d | Is Palindrome: %s%n",
                    n, rev, pal);
        }
    }
}

/*
 * Time Complexity: O(log10 |N|) - Number of decimal digits in N.
 * Space Complexity: O(1) - Constant stack registers.
 */

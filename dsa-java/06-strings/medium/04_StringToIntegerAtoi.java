/**
 * Problem Statement:
 * Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer.
 * Rules:
 *   1. Whitespace: Ignore any leading whitespace (" ").
 *   2. Signedness: Determine sign by checking if the next char is '-' or '+'. Assume positive if neither.
 *   3. Conversion: Read integer digits until non-digit is met or end is reached. Ignore remaining characters.
 *   4. Rounding/Clamping: If the integer is outside 32-bit signed integer range [-2^31, 2^31 - 1],
 *      clamp to Integer.MIN_VALUE (-2147483648) or Integer.MAX_VALUE (2147483647).
 * (LeetCode 8: String to Integer - atoi).
 *
 * Asked in: Amazon, Microsoft, Facebook / Meta, Bloomberg, Apple
 *
 * Approach:
 * - Deterministic Sequential Parser:
 *   1. Step 1: Skip leading spaces `while (i < n && s.charAt(i) == ' ') i++;`.
 *   2. Step 2: Parse optional '+' or '-' sign.
 *   3. Step 3: Loop while `s.charAt(i)` is a digit:
 *      - Overflow check before multiplying by 10:
 *        If `total > Integer.MAX_VALUE / 10` OR `(total == Integer.MAX_VALUE / 10 && digit > 7)`:
 *        Return `sign == 1 ? Integer.MAX_VALUE : Integer.MIN_VALUE`.
 *      - Accumulate: `total = total * 10 + digit`.
 *   4. Return `total * sign`.
 */
class StringToIntegerAtoi {

    public static int myAtoi(String s) {
        if (s == null || s.isEmpty()) return 0;

        int n = s.length();
        int i = 0;
        int sign = 1;
        int total = 0;

        // 1. Skip leading whitespace
        while (i < n && s.charAt(i) == ' ') {
            i++;
        }
        if (i == n) return 0;

        // 2. Check for optional sign
        char firstChar = s.charAt(i);
        if (firstChar == '+' || firstChar == '-') {
            sign = (firstChar == '-') ? -1 : 1;
            i++;
        }

        // 3. Process digits with overflow guard
        while (i < n) {
            char ch = s.charAt(i);
            if (ch < '0' || ch > '9') {
                break; // Stop at first non-digit
            }

            int digit = ch - '0';

            // Check overflow before updating total
            if (total > Integer.MAX_VALUE / 10 || (total == Integer.MAX_VALUE / 10 && digit > 7)) {
                return (sign == 1) ? Integer.MAX_VALUE : Integer.MIN_VALUE;
            }

            total = total * 10 + digit;
            i++;
        }

        return total * sign;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 8: String to Integer (myAtoi) ===");

        String[] testStrings = {
            "42",
            "   -042",
            "1337c0d3",
            "0-1",
            "words and 987",
            "-91283472332", // Underflow -> Integer.MIN_VALUE
            "2147483648"    // Overflow -> Integer.MAX_VALUE
        };

        for (String str : testStrings) {
            int parsed = myAtoi(str);
            System.out.printf("Input: %-18s ==> Parsed Int: %d%n", "\"" + str + "\"", parsed);
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through string characters.
 * Space Complexity: O(1) - Constant stack space.
 */

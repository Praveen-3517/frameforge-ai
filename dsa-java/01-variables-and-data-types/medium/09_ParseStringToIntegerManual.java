/**
 * Problem Statement:
 * Implement the `myAtoi(string s)` function, which converts a string to a 32-bit signed integer.
 * The algorithm must:
 * 1. Ignore leading whitespace.
 * 2. Check for an optional '+' or '-' sign.
 * 3. Read subsequent digits until the next non-digit character or end of input.
 * 4. Clamp the integer if it is out of the 32-bit signed integer range:
 *    return `Integer.MIN_VALUE` if underflow, `Integer.MAX_VALUE` if overflow.
 * (LeetCode 8: String to Integer (atoi)).
 *
 * Asked in: Amazon, Microsoft, LinkedIn, Uber
 *
 * Approach:
 * - Handle empty or null strings.
 * - Skip whitespace with `while (i < n && s.charAt(i) == ' ') i++`.
 * - Read sign: check `'+'` or `'-'`.
 * - Process digits:
 *     Check overflow before multiplying: `total > Integer.MAX_VALUE / 10 || (total == Integer.MAX_VALUE / 10 && digit > 7)`.
 */
class ParseStringToIntegerManual {

    public static int myAtoi(String s) {
        if (s == null || s.isEmpty()) return 0;

        int i = 0, n = s.length();
        // 1. Discard leading whitespaces
        while (i < n && s.charAt(i) == ' ') {
            i++;
        }
        if (i == n) return 0;

        // 2. Check sign
        int sign = 1;
        if (s.charAt(i) == '+' || s.charAt(i) == '-') {
            sign = (s.charAt(i) == '-') ? -1 : 1;
            i++;
        }

        // 3. Convert digits and guard against overflow
        int total = 0;
        while (i < n) {
            char ch = s.charAt(i);
            if (ch < '0' || ch > '9') break;

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
        String[] testInputs = {
            "42",
            "   -42",
            "4193 with words",
            "words and 987",
            "-91283472332", // Underflow -> Integer.MIN_VALUE (-2147483648)
            "2147483648",   // Overflow -> Integer.MAX_VALUE (2147483647)
            "+-12",
            ""
        };

        System.out.println("=== LeetCode 8: Manual myAtoi Implementation ===");
        for (String input : testInputs) {
            int parsed = myAtoi(input);
            System.out.printf("Input: %-25s ==> Output: %d%n", "\"" + input + "\"", parsed);
        }
    }
}

/*
 * Time Complexity: O(N) where N is the length of the string (linear single-pass scan).
 * Space Complexity: O(1) - Constant stack space.
 */

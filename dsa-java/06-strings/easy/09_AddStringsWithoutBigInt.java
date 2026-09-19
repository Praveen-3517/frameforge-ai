/**
 * Problem Statement:
 * Given two non-negative integers `num1` and `num2` represented as string,
 * return the sum of `num1` and `num2` as a string.
 * Requirements:
 *   - You must NOT use any built-in BigInteger library.
 *   - You must NOT convert the inputs to integer directly.
 * (LeetCode 415: Add Strings).
 *
 * Example:
 * num1 = "11", num2 = "123" -> "134"
 * num1 = "456", num2 = "77"  -> "533"
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Two-Pointer Decimal Ripple-Carry Addition:
 *   Start at the least significant digits: `i = num1.length() - 1` and `j = num2.length() - 1`.
 *   Maintain `carry = 0`.
 *   While `i >= 0 || j >= 0 || carry > 0`:
 *     `int sum = carry;`
 *     If `i >= 0`: `sum += num1.charAt(i--) - '0';`
 *     If `j >= 0`: `sum += num2.charAt(j--) - '0';`
 *     Append `sum % 10` to `StringBuilder`.
 *     Update `carry = sum / 10`.
 *   Reverse the `StringBuilder` to produce the standard big-endian result.
 */
class AddStringsWithoutBigInt {

    public static String addStrings(String num1, String num2) {
        StringBuilder sb = new StringBuilder();
        int i = num1.length() - 1;
        int j = num2.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += num1.charAt(i) - '0';
                i--;
            }

            if (j >= 0) {
                sum += num2.charAt(j) - '0';
                j--;
            }

            sb.append(sum % 10);
            carry = sum / 10;
        }

        return sb.reverse().toString();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 415: Add Large Strings (Decimal Ripple Carry) ===");

        String[][] testPairs = {
            { "11", "123" },
            { "456", "77" },
            { "0", "0" },
            { "99999999999999999999", "1" },
            { "12345678901234567890", "98765432109876543210" }
        };

        for (String[] pair : testPairs) {
            String sum = addStrings(pair[0], pair[1]);
            System.out.printf("  %s%n+ %s%n= %s%n%n", pair[0], pair[1], sum);
        }
    }
}

/*
 * Time Complexity: O(max(N, M)) - Linear traversal of digits.
 * Space Complexity: O(max(N, M)) - StringBuilder for output string.
 */

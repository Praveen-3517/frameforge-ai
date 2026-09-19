/**
 * Problem Statement:
 * Given two binary strings `a` and `b`, return their sum as a binary string.
 * The strings may be up to 10,000 characters long, far exceeding standard 64-bit primitive integers.
 * (LeetCode 67: Add Binary).
 *
 * Asked in: Facebook / Meta, Amazon, Microsoft, Apple, Bloomberg
 *
 * Approach:
 * - Two-Pointer Binary Ripple-Carry Addition:
 *   Start from the least significant bits (rightmost characters) and iterate backwards.
 *   Accumulate the sum of digits from `a`, `b`, and the existing `carry`.
 *   Current binary bit: `sum % 2`
 *   New carry: `sum / 2`
 *   Append each bit to a `StringBuilder` and reverse at the end.
 */
class AddBinaryStrings {

    public static String addBinary(String a, String b) {
        StringBuilder sb = new StringBuilder();
        int i = a.length() - 1;
        int j = b.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += a.charAt(i) - '0';
                i--;
            }

            if (j >= 0) {
                sum += b.charAt(j) - '0';
                j--;
            }

            sb.append(sum % 2);
            carry = sum / 2;
        }

        return sb.reverse().toString();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 67: Arbitrary-Length Binary String Addition ===");

        String[][] testCases = {
            { "11", "1" },
            { "1010", "1011" },
            { "0", "0" },
            { "11111111", "1" },
            { "10000000000000000000000000000001", "11111111111111111111111111111111" }
        };

        for (String[] tc : testCases) {
            String a = tc[0];
            String b = tc[1];
            String sum = addBinary(a, b);
            System.out.printf("  %s%n+ %s%n= %s%n%n", a, b, sum);
        }
    }
}

/*
 * Time Complexity: O(max(N, M)) - Linear traversal over the length of the longer binary string.
 * Space Complexity: O(max(N, M)) - Auxiliary StringBuilder to store the resulting sum string.
 */

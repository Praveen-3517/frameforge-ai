/**
 * Problem Statement:
 * Implement manual number-base conversions without using built-in library methods
 * (`Integer.toBinaryString` or `Integer.parseInt(s, 2)`):
 * 1. Convert an integer to its Binary representation string.
 * 2. Convert a Binary string back to its Decimal integer representation.
 * Handle negative numbers in two's complement.
 *
 * Asked in: Amazon, Microsoft, TCS, Infosys
 *
 * Approach:
 * - Decimal to Binary (Non-negative):
 *     Repeatedly extract `n % 2` (or `n & 1`) and divide `n / 2` (or `n >> 1`),
 *     prepending remainder to StringBuilder.
 * - Binary to Decimal:
 *     Iterate from left to right: `decimal = decimal * 2 + (char - '0')`.
 */
class BinaryToDecimalAndDecimalToBinary {

    public static String decimalToBinary(int n) {
        if (n == 0) return "0";
        if (n == Integer.MIN_VALUE) return "10000000000000000000000000000000";

        boolean isNegative = (n < 0);
        // If negative, work with positive long or bitwise shifting
        if (isNegative) {
            // Display full 32-bit two's complement for negative integers
            StringBuilder sb = new StringBuilder();
            for (int i = 31; i >= 0; i--) {
                sb.append((n >> i) & 1);
            }
            return sb.toString();
        }

        StringBuilder sb = new StringBuilder();
        while (n > 0) {
            sb.append(n & 1);
            n >>= 1;
        }
        return sb.reverse().toString();
    }

    public static int binaryToDecimal(String binaryStr) {
        if (binaryStr == null || binaryStr.isEmpty()) {
            throw new IllegalArgumentException("Binary string must not be empty.");
        }

        // If 32-bit two's complement negative binary string
        if (binaryStr.length() == 32 && binaryStr.charAt(0) == '1') {
            int result = 0;
            for (int i = 0; i < 32; i++) {
                result = (result << 1) | (binaryStr.charAt(i) - '0');
            }
            return result;
        }

        int decimal = 0;
        for (int i = 0; i < binaryStr.length(); i++) {
            char c = binaryStr.charAt(i);
            if (c != '0' && c != '1') {
                throw new IllegalArgumentException("Invalid binary character: " + c);
            }
            decimal = (decimal << 1) + (c - '0');
        }
        return decimal;
    }

    public static void main(String[] args) {
        int[] testValues = { 0, 1, 13, 42, 255, 1024, -5 };

        System.out.println("=== Decimal to Binary & Inverse Conversion ===");
        for (int val : testValues) {
            String binary = decimalToBinary(val);
            int backToDec = binaryToDecimal(binary);
            System.out.printf("Decimal: %-6d ==> Binary: %-32s ==> Reconstructed: %d%n",
                    val, binary, backToDec);
            assert val == backToDec : "Mismatch detected!";
        }
        System.out.println("All conversions verified successfully!");
    }
}

/*
 * Time Complexity:
 *   - Decimal to Binary: O(log N) operations (number of bits in N).
 *   - Binary to Decimal: O(L) where L is the length of binary string.
 * Space Complexity: O(log N) for StringBuilder buffer.
 */

/**
 * Problem: Add Binary (LeetCode 67)
 * Asked in: Amazon, Facebook, Microsoft
 * 
 * Given two binary strings a and b, return their sum as a binary string.
 * 
 * Approach:
 * Simulate binary addition from the rightmost bits with a carry:
 * - Start from the end of both strings and work left.
 * - sum = digitA + digitB + carry.
 * - Appended bit = sum % 2, new carry = sum / 2.
 * - Prepend each bit to result (or append and reverse at the end).
 * 
 * Time Complexity: O(max(A.length, B.length))
 * Space Complexity: O(max(A.length, B.length)) for result.
 */
class AddBinaryStrings {

    public static String addBinary(String a, String b) {
        StringBuilder result = new StringBuilder();
        int i = a.length() - 1;
        int j = b.length() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;

            if (i >= 0) {
                sum += a.charAt(i--) - '0';
            }
            if (j >= 0) {
                sum += b.charAt(j--) - '0';
            }

            result.append(sum % 2);
            carry = sum / 2;
        }

        return result.reverse().toString();
    }

    public static void main(String[] args) {
        System.out.println("11 + 1: " + addBinary("11", "1") + " (Expected: 100)");
        System.out.println("1010 + 1011: " + addBinary("1010", "1011") + " (Expected: 10101)");
    }
}

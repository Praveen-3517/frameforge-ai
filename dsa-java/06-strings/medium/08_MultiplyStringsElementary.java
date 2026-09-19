/**
 * Problem Statement:
 * Given two non-negative integers `num1` and `num2` represented as strings, return the product
 * of `num1` and `num2`, also represented as a string.
 * Must NOT use any built-in BigInteger library or convert directly to integer.
 * (LeetCode 43: Multiply Strings).
 *
 * Example:
 * num1 = "123", num2 = "456" -> "56088"
 *
 * Asked in: Facebook / Meta, Google, Microsoft, Amazon
 *
 * Approach:
 * - Grade-School Array Multiplication:
 *   Multiplying m-digit and n-digit numbers produces at most m + n digits.
 *   - Pre-allocate `int[] pos = new int[m + n]`.
 *   - Traverse indices `i` (from m-1 down to 0) and `j` (from n-1 down to 0):
 *     `mul = (num1[i] - '0') * (num2[j] - '0')`
 *     `sum = mul + pos[i + j + 1]`
 *     `pos[i + j] += sum / 10`
 *     `pos[i + j + 1] = sum % 10`
 *   - Build output string skipping leading zeros.
 */
class MultiplyStringsElementary {

    public static String multiply(String num1, String num2) {
        if ("0".equals(num1) || "0".equals(num2)) return "0";

        int m = num1.length();
        int n = num2.length();
        int[] pos = new int[m + n];

        for (int i = m - 1; i >= 0; i--) {
            int d1 = num1.charAt(i) - '0';
            for (int j = n - 1; j >= 0; j--) {
                int d2 = num2.charAt(j) - '0';
                int mul = d1 * d2;

                int p1 = i + j;
                int p2 = i + j + 1;
                int sum = mul + pos[p2];

                pos[p1] += sum / 10;
                pos[p2] = sum % 10;
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int p : pos) {
            if (!(sb.length() == 0 && p == 0)) {
                sb.append(p);
            }
        }

        return sb.length() == 0 ? "0" : sb.toString();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 43: Multiply Large Strings (No BigInteger) ===");

        String[][] testCases = {
            { "2", "3" },
            { "123", "456" },
            { "999", "999" },
            { "123456789", "987654321" }
        };

        for (String[] tc : testCases) {
            String product = multiply(tc[0], tc[1]);
            System.out.printf("%s * %s = %s%n", tc[0], tc[1], product);
        }
    }
}

/*
 * Time Complexity: O(M * N) - Each digit pair is multiplied once.
 * Space Complexity: O(M + N) - Storage for product digit array.
 */

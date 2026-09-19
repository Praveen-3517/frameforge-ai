/*
 * Problem Statement:
 * Given a positive decimal integer N, convert it to its binary representation using recursion.
 * For N = 0, return "0".
 * 
 * Example 1:
 * Input: N = 10
 * Output: "1010"
 * 
 * Example 2:
 * Input: N = 25
 * Output: "11001"
 * 
 * Asked in: Amazon, Infosys, TCS, Cognizant
 */

class DecimalToBinaryRecursion {

    /**
     * Approach:
     * Decimal to binary conversion recursively divides the number by 2 and records remainder.
     * Base case:
     * - if n == 0 return "0" (when initially 0) or "" (during recursive unwinding).
     * Recursive relation:
     * - decimalToBinary(n / 2) + (n % 2)
     */
    public static String toBinary(int n) {
        if (n == 0) return "0";
        return toBinaryHelper(n);
    }

    private static String toBinaryHelper(int n) {
        if (n == 0) return "";
        return toBinaryHelper(n / 2) + (n % 2);
    }

    // Also count set bits recursively
    public static int countSetBits(int n) {
        if (n == 0) return 0;
        return (n & 1) + countSetBits(n >>> 1);
    }

    public static void main(String[] args) {
        int[] testCases = {0, 1, 10, 25, 42, 255};

        System.out.println("--- Decimal to Binary Conversion via Recursion ---");
        for (int num : testCases) {
            String bin = toBinary(num);
            int setBits = countSetBits(num);
            System.out.printf("Decimal: %3d -> Binary: %8s | Set bits: %d | Built-in: %s%n",
                    num, bin, setBits, Integer.toBinaryString(num));
        }
    }
}

/*
 * Time Complexity: O(log N) - Number of recursive calls equals the number of bits in N.
 * Space Complexity: O(log N) - Recursive call stack depth is equal to log2(N).
 */

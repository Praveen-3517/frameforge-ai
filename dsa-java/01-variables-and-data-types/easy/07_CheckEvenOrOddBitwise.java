/**
 * Problem Statement:
 * Determine whether a given integer is Even or Odd without using the modulo `%` operator.
 *
 * Asked in: Amazon, TCS, Microsoft
 *
 * Approach:
 * - Any integer's binary representation has its least significant bit (LSB) set to:
 *     `0` if Even (multiples of 2)
 *     `1` if Odd (2k + 1)
 * - Evaluating `(n & 1)`:
 *     If `(n & 1) == 0` -> Number is Even.
 *     If `(n & 1) == 1` -> Number is Odd.
 * - This bitwise check also naturally works for negative integers without extra logic.
 */
class CheckEvenOrOddBitwise {

    public static boolean isEven(int n) {
        return (n & 1) == 0;
    }

    public static boolean isOdd(int n) {
        return (n & 1) != 0;
    }

    public static void main(String[] args) {
        int[] testNumbers = { 0, 4, 7, -8, -13, 1024, 1025 };

        System.out.println("=== Bitwise Even/Odd Check (n & 1) ===");
        for (int n : testNumbers) {
            String binary = Integer.toBinaryString(n);
            // Pad binary for clarity
            System.out.printf("Number: %-6d | LSB: %d | Status: %s%n",
                    n, (n & 1), isEven(n) ? "EVEN" : "ODD");
        }
    }
}

/*
 * Time Complexity: O(1) - Single CPU bitwise AND instruction.
 * Space Complexity: O(1) - Zero allocation.
 */

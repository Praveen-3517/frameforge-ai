/**
 * Problem Statement:
 * Given two integers `a` and `b`, return the sum of the two integers without using
 * the operators `+` and `-`.
 * (LeetCode 371: Sum of Two Integers).
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft, Apple
 *
 * Approach:
 * - Digital Half-Adder Circuit Logic:
 *   1. Bitwise XOR (`a ^ b`) calculates the sum of bits without considering carry (0+0=0, 1+0=1, 1+1=0).
 *   2. Bitwise AND (`a & b`) finds where carries are generated (1+1 produces a carry of 1).
 *   3. Left shift carry by 1 (`(a & b) << 1`) aligns the carry with the next higher bit position.
 *   4. Repeat iteratively or recursively until the carry becomes 0.
 */
class AddWithoutPlusOperator {

    // Iterative Solution
    public static int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1; // Calculate carry bits shifted left
            a = a ^ b;                // Calculate sum without carry
            b = carry;                // Carry becomes new operand to add
        }
        return a;
    }

    // Recursive Solution
    public static int getSumRecursive(int a, int b) {
        return (b == 0) ? a : getSumRecursive(a ^ b, (a & b) << 1);
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 371: Sum of Two Integers Without '+' or '-' ===");

        int[][] testCases = {
            { 1, 2 },
            { 2, 3 },
            { -1, 1 },
            { -14, 7 },
            { -20, -30 },
            { 0, 100 },
            { 1000, 2500 }
        };

        for (int[] tc : testCases) {
            int a = tc[0];
            int b = tc[1];
            int sumIter = getSum(a, b);
            int sumRec = getSumRecursive(a, b);
            System.out.printf("Sum(%d, %d) ==> Iterative: %d | Recursive: %d | Expected: %d%n",
                    a, b, sumIter, sumRec, a + b);
        }
    }
}

/*
 * Time Complexity: O(1) - Loop executes at most 32 times for 32-bit integers.
 * Space Complexity: O(1) - Constant stack registers.
 */

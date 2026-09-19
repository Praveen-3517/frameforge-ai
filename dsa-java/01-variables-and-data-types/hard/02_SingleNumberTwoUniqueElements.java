/**
 * Problem Statement:
 * Given an integer array `nums`, in which exactly two elements appear only once
 * and all the other elements appear exactly twice. Find the two elements that appear only once.
 * Your algorithm must run in linear runtime O(n) and use only constant extra space O(1).
 * (LeetCode 260: Single Number III).
 *
 * Asked in: Google, Amazon, Microsoft, Directi
 *
 * Approach:
 * 1. XOR all numbers in the array. Since `x ^ x = 0`, all duplicate pairs cancel out.
 *    The final result is `xorSum = a ^ b`, where `a` and `b` are the two unique elements.
 * 2. Since `a != b`, `xorSum != 0`, which means there is at least one set bit where `a` and `b` differ.
 * 3. Find the lowest set bit (rightmost 1-bit) using `diff = xorSum & (-xorSum)`.
 * 4. Partition the entire array into two groups:
 *      Group 1: Numbers that have this bit set (`(num & diff) != 0`)
 *      Group 2: Numbers that have this bit cleared (`(num & diff) == 0`)
 * 5. `a` and `b` will fall into different groups, and duplicates will fall into the same group and cancel out.
 */
import java.util.Arrays;

class SingleNumberTwoUniqueElements {

    public static int[] singleNumber(int[] nums) {
        // Step 1: XOR all elements to obtain a ^ b
        int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }

        // Step 2: Extract rightmost set bit (diff bit)
        // Two's complement trick: x & -x isolates lowest set bit
        int diff = xorSum & (-xorSum);

        // Step 3: Divide into two groups and XOR independently
        int a = 0;
        int b = 0;
        for (int num : nums) {
            if ((num & diff) != 0) {
                a ^= num; // Belongs to group with bit set
            } else {
                b ^= num; // Belongs to group with bit 0
            }
        }

        return new int[]{ a, b };
    }

    public static void main(String[] args) {
        int[] input1 = { 1, 2, 1, 3, 2, 5 };
        int[] res1 = singleNumber(input1);
        System.out.println("Input:  " + Arrays.toString(input1));
        System.out.println("Output: " + Arrays.toString(res1)); // [3, 5] (or [5, 3])

        int[] input2 = { -1, 0 };
        int[] res2 = singleNumber(input2);
        System.out.println("\nInput:  " + Arrays.toString(input2));
        System.out.println("Output: " + Arrays.toString(res2));

        int[] input3 = { 0, 1 };
        int[] res3 = singleNumber(input3);
        System.out.println("\nInput:  " + Arrays.toString(input3));
        System.out.println("Output: " + Arrays.toString(res3));
    }
}

/*
 * Time Complexity: O(N) - Exactly two passes over the array.
 * Space Complexity: O(1) - Constant auxiliary registers without HashSet/HashMap.
 */

import java.util.Arrays;

/**
 * Problem: Counting Bits (LeetCode 338)
 * Asked in: Amazon, Google, Facebook, Apple
 * 
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
 * ans[i] is the number of 1's in the binary representation of i.
 * 
 * Approach:
 * Dynamic Programming with Bit Manipulation:
 * Notice that right-shifting i by 1 (i >> 1) preserves all bits except the least significant bit.
 * Therefore:
 *   dp[i] = dp[i >> 1] + (i & 1)
 * 
 * Time Complexity: O(N) single pass.
 * Space Complexity: O(1) auxiliary space (excluding returned array).
 */
class CountingBitsDP {

    public static int[] countBits(int n) {
        int[] dp = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i >> 1] + (i & 1);
        }

        return dp;
    }

    public static void main(String[] args) {
        System.out.println("Bits up to 2: " + Arrays.toString(countBits(2)) + " (Expected: [0, 1, 1])");
        System.out.println("Bits up to 5: " + Arrays.toString(countBits(5)) + " (Expected: [0, 1, 1, 2, 1, 2])");
    }
}

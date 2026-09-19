import java.util.Arrays;

/**
 * Problem: Counting Bits (LeetCode 338)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
 * ans[i] is the number of 1's in the binary representation of i.
 * 
 * Approach - Two Methods:
 * 1. Kernighan's: For each number, repeatedly clear lowest set bit (O(N * popcount)).
 * 2. DP Bit Recurrence:
 *    dp[i] = dp[i >> 1] + (i & 1)
 *    Right-shifting i by 1 gives us a number we already computed.
 *    We just add 1 if i's LSB is set.
 * 
 * Time Complexity: O(N) for DP approach.
 * Space Complexity: O(1) auxiliary (not counting result array).
 */
class CountingBitsBitmask {

    public static int[] countBits(int n) {
        int[] dp = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i >> 1] + (i & 1);
        }
        return dp;
    }

    public static void main(String[] args) {
        System.out.println("Bits 0..2: " + Arrays.toString(countBits(2)) + " (Expected: [0, 1, 1])");
        System.out.println("Bits 0..5: " + Arrays.toString(countBits(5)) + " (Expected: [0, 1, 1, 2, 1, 2])");
        System.out.println("Bits 0..7: " + Arrays.toString(countBits(7)));
    }
}

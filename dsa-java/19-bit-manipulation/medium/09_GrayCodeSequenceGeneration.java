import java.util.ArrayList;
import java.util.List;

/**
 * Problem: Gray Code (LeetCode 89)
 * Asked in: Amazon, Google, Microsoft
 * 
 * An n-bit gray code sequence is a sequence of 2^n integers where:
 * - Every integer is in the inclusive range [0, 2^n - 1].
 * - The first integer is 0.
 * - An integer appears no more than once.
 * - The binary representation of every pair of adjacent integers differ by exactly one bit.
 * - The binary representation of the first and last integers differ by exactly one bit.
 * Return any valid n-bit gray code sequence.
 * 
 * Approach - Binary-to-Gray Formula:
 * Gray code for integer i: i ^ (i >> 1)
 * Simply iterate i from 0 to 2^n - 1 and apply the formula.
 * 
 * Time Complexity: O(2^N)
 * Space Complexity: O(2^N)
 */
class GrayCodeSequenceGeneration {

    public static List<Integer> grayCode(int n) {
        int total = 1 << n; // 2^n
        List<Integer> result = new ArrayList<>(total);
        for (int i = 0; i < total; i++) {
            result.add(i ^ (i >> 1));
        }
        return result;
    }

    public static void main(String[] args) {
        System.out.println("Gray code (n=2): " + grayCode(2));
        // Expected: [0, 1, 3, 2] or any valid sequence

        System.out.println("Gray code (n=3): " + grayCode(3));
        // Expected: [0, 1, 3, 2, 6, 7, 5, 4] or any valid sequence
    }
}

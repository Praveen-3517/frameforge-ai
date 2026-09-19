/**
 * Problem: Number of 1 Bits / Hamming Weight (LeetCode 191)
 * Asked in: Microsoft, Apple, Google, Amazon
 * 
 * Write a function that takes the binary representation of a positive integer
 * and returns the number of set bits it has (also known as the Hamming weight).
 * 
 * Approach:
 * Brian Kernighan's Algorithm:
 * The operation n = n & (n - 1) clears the lowest set bit of n in O(1).
 * Repeating this until n becomes 0 counts exactly the number of set bits in
 * iterations equal to the number of set bits (rather than looping 32 times).
 * 
 * Time Complexity: O(Number of set bits) <= 32
 * Space Complexity: O(1)
 */
class NumberOfOneBitsKernighan {

    public static int hammingWeight(int n) {
        int count = 0;
        while (n != 0) {
            n = n & (n - 1);
            count++;
        }
        return count;
    }

    public static void main(String[] args) {
        System.out.println("Set bits in 11 (1011): " + hammingWeight(11) + " (Expected: 3)");
        System.out.println("Set bits in 128 (10000000): " + hammingWeight(128) + " (Expected: 1)");
        System.out.println("Set bits in 2147483645: " + hammingWeight(2147483645) + " (Expected: 30)");
    }
}

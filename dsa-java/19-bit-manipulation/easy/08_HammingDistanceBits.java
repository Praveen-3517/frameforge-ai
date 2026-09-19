/**
 * Problem: Hamming Distance (LeetCode 461)
 * Asked in: Amazon, Google, Microsoft
 * 
 * The Hamming distance between two integers is the number of positions at which
 * the corresponding bits are different.
 * Given two integers x and y, return the Hamming distance between them.
 * 
 * Approach:
 * 1. XOR x and y: the result has 1-bits exactly where x and y differ.
 * 2. Count the set bits in x ^ y using Kernighan's algorithm.
 * 
 * Time Complexity: O(1) - at most 32 iterations.
 * Space Complexity: O(1)
 */
class HammingDistanceBits {

    public static int hammingDistance(int x, int y) {
        int xorResult = x ^ y;
        int count = 0;
        while (xorResult != 0) {
            xorResult &= (xorResult - 1); // clear lowest set bit
            count++;
        }
        return count;
    }

    public static void main(String[] args) {
        // 1 = 0001, 4 = 0100 -> differ at bits 0 and 2
        System.out.println("Hamming(1, 4): " + hammingDistance(1, 4) + " (Expected: 2)");

        // 3 = 011, 1 = 001 -> differ at bit 1
        System.out.println("Hamming(3, 1): " + hammingDistance(3, 1) + " (Expected: 1)");
    }
}

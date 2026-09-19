/**
 * Problem: Power of Two (LeetCode 231)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an integer n, return true if it is a power of two. Otherwise, return false.
 * An integer n is a power of two if there exists an integer x such that n == 2^x.
 * 
 * Approach:
 * Bit Manipulation:
 * A power of two has exactly one set bit in its binary representation.
 * n & (n - 1) clears the lowest set bit.
 * So if n > 0 and n & (n - 1) == 0, then n is a power of two!
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class PowerOfTwoBitCheck {

    public static boolean isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }

    public static void main(String[] args) {
        System.out.println("1 is power of 2: " + isPowerOfTwo(1) + " (Expected: true)");
        System.out.println("16 is power of 2: " + isPowerOfTwo(16) + " (Expected: true)");
        System.out.println("3 is power of 2: " + isPowerOfTwo(3) + " (Expected: false)");
        System.out.println("0 is power of 2: " + isPowerOfTwo(0) + " (Expected: false)");
        System.out.println("-16 is power of 2: " + isPowerOfTwo(-16) + " (Expected: false)");
    }
}

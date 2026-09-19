/**
 * Problem: Power of Four (LeetCode 342)
 * Asked in: Google, Amazon
 * 
 * Given an integer n, return true if it is a power of four. Otherwise, return false.
 * An integer n is a power of four if there exists an integer x such that n == 4^x.
 * 
 * Approach - Pure Bit Manipulation (No Loops, No Log):
 * A power of four must:
 * 1. Be positive: n > 0
 * 2. Have exactly one set bit (power of 2): (n & (n - 1)) == 0
 * 3. That single set bit must be at an EVEN bit position (bit 0, 2, 4, 6, ...):
 *    4^0=1(bit0), 4^1=4(bit2), 4^2=16(bit4), 4^3=64(bit6)...
 *    Mask for even positions in 32-bit: 0x55555555 = 01010101...01010101
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class PowerOfFourBitwise {

    public static boolean isPowerOfFour(int n) {
        return n > 0 
            && (n & (n - 1)) == 0           // exactly one set bit
            && (n & 0x55555555) != 0;       // set bit is at an even position
    }

    public static void main(String[] args) {
        System.out.println("1 is power of 4: " + isPowerOfFour(1) + " (Expected: true)");   // 4^0
        System.out.println("4 is power of 4: " + isPowerOfFour(4) + " (Expected: true)");   // 4^1
        System.out.println("16 is power of 4: " + isPowerOfFour(16) + " (Expected: true)"); // 4^2
        System.out.println("5 is power of 4: " + isPowerOfFour(5) + " (Expected: false)");
        System.out.println("2 is power of 4: " + isPowerOfFour(2) + " (Expected: false)");  // power of 2, not 4
        System.out.println("8 is power of 4: " + isPowerOfFour(8) + " (Expected: false)");  // 2^3, not power of 4
    }
}

/**
 * Problem: Reverse Bits (LeetCode 190)
 * Asked in: Apple, Amazon, Microsoft
 * 
 * Reverse bits of a given 32 bits unsigned integer.
 * 
 * Approach:
 * Bit-by-bit extraction and placement:
 * For each of the 32 bit positions:
 * 1. Extract the LSB of n: bit = n & 1
 * 2. Left-shift result by 1 and OR in the extracted bit.
 * 3. Right-shift n by 1 (logical shift >>> to avoid sign extension).
 * 
 * Time Complexity: O(32) = O(1)
 * Space Complexity: O(1)
 */
class ReverseBits32BitInteger {

    public static int reverseBits(int n) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            result = (result << 1) | (n & 1);
            n >>>= 1;
        }
        return result;
    }

    public static void main(String[] args) {
        // 43261596 = 00000010100101000001111010011100
        // Reversed = 00111001011110000010100101000000 = 964176192
        System.out.println("Reversed 43261596: " + reverseBits(43261596) + " (Expected: 964176192)");

        // -3 in 32-bit = 11111111111111111111111111111101
        // Reversed    = 10111111111111111111111111111111 = -1073741825
        System.out.println("Reversed -3: " + reverseBits(-3) + " (Expected: -1073741825)");
    }
}

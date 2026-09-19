/**
 * Problem: Binary Number with Alternating Bits (LeetCode 693)
 * Asked in: Microsoft, Amazon
 * 
 * Given a positive integer, check whether it has alternating bits:
 * namely, if two adjacent bits will always have different values.
 * 
 * Approach:
 * Bit Manipulation Trick:
 * If n has alternating bits, then n ^ (n >> 1) should produce all 1-bits
 * (a number of the form 000...111...).
 * A number m has all 1-bits iff m & (m + 1) == 0.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
class BinaryNumberWithAlternatingBits {

    public static boolean hasAlternatingBits(int n) {
        int m = n ^ (n >> 1);
        // m should be all 1s: 0001, 0011, 0111, etc.
        return (m & (m + 1)) == 0;
    }

    public static void main(String[] args) {
        // 5 = 101 -> alternating
        System.out.println("5 (101) alternating: " + hasAlternatingBits(5) + " (Expected: true)");
        // 7 = 111 -> not alternating
        System.out.println("7 (111) alternating: " + hasAlternatingBits(7) + " (Expected: false)");
        // 11 = 1011 -> not alternating
        System.out.println("11 (1011) alternating: " + hasAlternatingBits(11) + " (Expected: false)");
        // 10 = 1010 -> alternating
        System.out.println("10 (1010) alternating: " + hasAlternatingBits(10) + " (Expected: true)");
    }
}

/**
 * Problem: Sum of Two Integers Without + or - (LeetCode 371)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * Given two integers a and b, return the sum of the two integers
 * without using the operators + and -.
 * 
 * Approach - Full Adder via Bit Manipulation:
 * A full adder:
 * - sum bits (no carry) = a ^ b
 * - carry bits = (a & b) << 1
 * Repeat until carry becomes 0.
 * 
 * Time Complexity: O(1) - max 32 iterations.
 * Space Complexity: O(1)
 */
class SumOfTwoIntegersWithoutPlusMinus {

    public static int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1;
            a = a ^ b;   // sum without carry
            b = carry;   // carry propagated
        }
        return a;
    }

    public static void main(String[] args) {
        System.out.println("1 + 2 = " + getSum(1, 2) + " (Expected: 3)");
        System.out.println("2 + 3 = " + getSum(2, 3) + " (Expected: 5)");
        System.out.println("-1 + 1 = " + getSum(-1, 1) + " (Expected: 0)");
        System.out.println("-7 + 3 = " + getSum(-7, 3) + " (Expected: -4)");
    }
}

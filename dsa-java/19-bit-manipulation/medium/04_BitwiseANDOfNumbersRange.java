/**
 * Problem: Bitwise AND of Numbers Range (LeetCode 201)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given two integers left and right that represent the range [left, right],
 * return the bitwise AND of all numbers in this range, inclusive.
 * 
 * Approach - Common Prefix Extraction:
 * The AND of all numbers in [left, right] equals the common bit prefix of left and right.
 * When left != right, the AND includes the rightmost varying bits becoming 0.
 * Algorithm: Right-shift both left and right until they are equal, counting shifts.
 * The result is (left or right, same at this point) << shiftCount.
 * 
 * Time Complexity: O(log N) - at most 32 iterations.
 * Space Complexity: O(1)
 */
class BitwiseANDOfNumbersRange {

    public static int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        return left << shift;
    }

    public static void main(String[] args) {
        System.out.println("AND [5,7]: " + rangeBitwiseAnd(5, 7) + " (Expected: 4)");
        // 5=101, 6=110, 7=111 -> AND=100=4
        System.out.println("AND [0,0]: " + rangeBitwiseAnd(0, 0) + " (Expected: 0)");
        System.out.println("AND [1,2147483647]: " + rangeBitwiseAnd(1, 2147483647) + " (Expected: 0)");
    }
}

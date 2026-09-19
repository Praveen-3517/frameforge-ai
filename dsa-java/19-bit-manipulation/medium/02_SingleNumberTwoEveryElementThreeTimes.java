/**
 * Problem: Single Number II (LeetCode 137)
 * Asked in: Amazon, Microsoft, Google
 * 
 * Given an integer array nums where every element appears exactly three times
 * except for one element which appears exactly once. Find that single one.
 * Must use O(1) extra space.
 * 
 * Approach - Bit Counting Modulo 3:
 * For every bit position, count the sum of that bit across all numbers.
 * Since triple-appearing numbers contribute 0 or 3 to each bit count,
 * the bit count mod 3 isolates the unique element's contribution.
 * 
 * Alternative Two-Variable Bit Circuit:
 * Maintain `ones` and `twos`:
 * - `ones` = bits seen odd number of times (mod 3 == 1)
 * - `twos` = bits seen twice (mod 3 == 2)
 * - A bit exits both when it has appeared 3 times.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class SingleNumberTwoEveryElementThreeTimes {

    public static int singleNumber(int[] nums) {
        int ones = 0;
        int twos = 0;

        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }

        return ones;
    }

    public static void main(String[] args) {
        int[] nums1 = {2, 2, 3, 2};
        System.out.println("Single (appear once): " + singleNumber(nums1) + " (Expected: 3)");

        int[] nums2 = {0, 1, 0, 1, 0, 1, 99};
        System.out.println("Single (appear once): " + singleNumber(nums2) + " (Expected: 99)");
    }
}

import java.util.Arrays;

/**
 * Problem: Single Number III (LeetCode 260)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an integer array nums, in which exactly two elements appear only once
 * and all other elements appear exactly twice, find the two elements that appear once.
 * You must use O(1) extra space.
 * 
 * Approach - XOR with Bit Separator:
 * 1. XOR all numbers: xorAll = a ^ b (where a, b are the two unique elements).
 * 2. Find any set bit in xorAll (use xorAll & (-xorAll) to isolate rightmost set bit = diffBit).
 *    This bit differs between a and b.
 * 3. Partition array into two groups based on diffBit:
 *    - Group 1: numbers where diffBit is set.
 *    - Group 2: numbers where diffBit is clear.
 * 4. XOR each group independently: pairs cancel, leaving a and b.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class SingleNumberThreeTwoUniqueElements {

    public static int[] singleNumber(int[] nums) {
        int xorAll = 0;
        for (int num : nums) {
            xorAll ^= num;
        }

        // Isolate the rightmost differing bit
        int diffBit = xorAll & (-xorAll);

        int a = 0;
        int b = 0;

        for (int num : nums) {
            if ((num & diffBit) != 0) {
                a ^= num;
            } else {
                b ^= num;
            }
        }

        return new int[]{a, b};
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 1, 3, 2, 5};
        System.out.println("Two unique: " + Arrays.toString(singleNumber(nums1)));
        // Expected: [3, 5] (order may vary)

        int[] nums2 = {-1, 0};
        System.out.println("Two unique: " + Arrays.toString(singleNumber(nums2)));
        // Expected: [-1, 0]
    }
}

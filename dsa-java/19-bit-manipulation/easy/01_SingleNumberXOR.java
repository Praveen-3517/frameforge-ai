/**
 * Problem: Single Number (LeetCode 136)
 * Asked in: Amazon, Google, Microsoft, Apple, Bloomberg
 * 
 * Given a non-empty array of integers nums, every element appears twice except for one.
 * Find that single one. You must implement a solution with linear runtime complexity
 * and use only constant extra space.
 * 
 * Approach:
 * XOR Cancellation:
 * x ^ x = 0
 * x ^ 0 = x
 * XOR is associative and commutative. XORing all numbers cancels duplicate pairs,
 * leaving only the unique element.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class SingleNumberXOR {

    public static int singleNumber(int[] nums) {
        int single = 0;
        for (int num : nums) {
            single ^= num;
        }
        return single;
    }

    public static void main(String[] args) {
        int[] nums1 = {2, 2, 1};
        System.out.println("Single number 1: " + singleNumber(nums1) + " (Expected: 1)");

        int[] nums2 = {4, 1, 2, 1, 2};
        System.out.println("Single number 2: " + singleNumber(nums2) + " (Expected: 4)");

        int[] nums3 = {1};
        System.out.println("Single number 3: " + singleNumber(nums3) + " (Expected: 1)");
    }
}

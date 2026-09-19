/**
 * Problem: Missing Number (LeetCode 268)
 * Asked in: Microsoft, Amazon, Google, Apple, Bloomberg
 * 
 * Given an array nums containing n distinct numbers in the range [0, n],
 * return the only number in the range that is missing from the array.
 * 
 * Approach - XOR:
 * XOR all indices from 0 to n, then XOR all array values.
 * Every index that appears in both cancels out via XOR (x ^ x = 0).
 * The missing number remains as only one index has no matching value.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class MissingNumberXOR {

    public static int missingNumber(int[] nums) {
        int xor = nums.length; // XOR with n first
        for (int i = 0; i < nums.length; i++) {
            xor ^= i;
            xor ^= nums[i];
        }
        return xor;
    }

    public static void main(String[] args) {
        int[] nums1 = {3, 0, 1};
        System.out.println("Missing from [3,0,1]: " + missingNumber(nums1) + " (Expected: 2)");

        int[] nums2 = {0, 1};
        System.out.println("Missing from [0,1]: " + missingNumber(nums2) + " (Expected: 2)");

        int[] nums3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
        System.out.println("Missing from [9..0]: " + missingNumber(nums3) + " (Expected: 8)");
    }
}

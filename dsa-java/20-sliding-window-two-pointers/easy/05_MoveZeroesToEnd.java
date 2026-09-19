/**
 * Problem: Move Zeroes (LeetCode 283)
 * Category: Two Pointers (Slow-Fast) | Easy
 * Asked in: Facebook, Amazon, Microsoft, Apple
 * 
 * Given an integer array nums, move all 0's to the end of it while maintaining the
 * relative order of the non-zero elements. Must modify in-place without making a copy.
 * 
 * Approach - Slow/Fast Two-Pointer:
 * `slow` tracks position to place next non-zero element.
 * `fast` scans through the array.
 * - When nums[fast] != 0: place at nums[slow], advance slow.
 * - Fill the remaining positions from slow to end with 0.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class MoveZeroesToEnd {

    public static void moveZeroes(int[] nums) {
        int slow = 0;

        // Move all non-zero elements to the front
        for (int fast = 0; fast < nums.length; fast++) {
            if (nums[fast] != 0) {
                nums[slow++] = nums[fast];
            }
        }

        // Fill remaining positions with 0
        while (slow < nums.length) {
            nums[slow++] = 0;
        }
    }

    public static void main(String[] args) {
        int[] arr1 = {0, 1, 0, 3, 12};
        moveZeroes(arr1);
        System.out.println(java.util.Arrays.toString(arr1) + " (Expected: [1, 3, 12, 0, 0])");

        int[] arr2 = {0};
        moveZeroes(arr2);
        System.out.println(java.util.Arrays.toString(arr2) + " (Expected: [0])");

        int[] arr3 = {1, 0, 0, 3, 0, 0, 11, 0, 5};
        moveZeroes(arr3);
        System.out.println(java.util.Arrays.toString(arr3));
    }
}

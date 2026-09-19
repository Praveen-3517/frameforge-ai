/**
 * Problem: Remove Duplicates from Sorted Array (LeetCode 26)
 * Category: Two Pointers (Slow Writer / Fast Reader) | Easy
 * Asked in: Amazon, Facebook, Microsoft, Apple, Google
 * 
 * Given an integer array nums sorted in non-decreasing order, remove the duplicates
 * in-place such that each unique element appears only once. Return the new length.
 * 
 * Approach - Slow Writer / Fast Reader:
 * `slow` = last position of a written unique element.
 * `fast` scans forward looking for the next element different from nums[slow].
 * When nums[fast] != nums[slow]: advance slow, copy fast to slow.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class RemoveDuplicatesSortedArrayTwoPointer {

    public static int removeDuplicates(int[] nums) {
        if (nums.length == 0) return 0;

        int slow = 0;

        for (int fast = 1; fast < nums.length; fast++) {
            if (nums[fast] != nums[slow]) {
                slow++;
                nums[slow] = nums[fast];
            }
        }

        return slow + 1; // length of unique elements
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 1, 2};
        int len1 = removeDuplicates(nums1);
        System.out.println("Unique length: " + len1 + " (Expected: 2)");
        System.out.println("Array first " + len1 + " elements: " + java.util.Arrays.toString(java.util.Arrays.copyOf(nums1, len1)));

        int[] nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
        int len2 = removeDuplicates(nums2);
        System.out.println("Unique length: " + len2 + " (Expected: 5)");
    }
}

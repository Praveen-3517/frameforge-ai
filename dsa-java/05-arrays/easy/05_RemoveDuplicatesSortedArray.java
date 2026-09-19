import java.util.Arrays;

/**
 * Problem Statement:
 * Given an integer array `nums` sorted in non-decreasing order, remove the duplicates in-place
 * such that each unique element appears only once. The relative order of the elements should be kept the same.
 * Return `k`, the number of unique elements.
 * (LeetCode 26: Remove Duplicates from Sorted Array).
 *
 * Example:
 * nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
 * Output: k = 5, nums = [0, 1, 2, 3, 4, ...]
 *
 * Asked in: Facebook / Meta, Amazon, Microsoft, Google, Apple
 *
 * Approach:
 * - Two-Pointer In-Place Compaction:
 *   - Pointer `k`: The write-pointer pointing to the position for the next unique element (starts at 1).
 *   - Pointer `i`: The read-pointer scanning through the array (starts at 1).
 *   - Invariant: Elements `nums[0..k-1]` are unique and sorted.
 *   - For each element `nums[i]`:
 *     If `nums[i] != nums[k - 1]`:
 *       `nums[k] = nums[i];`
 *       `k++;`
 *   - Return `k`.
 */
class RemoveDuplicatesSortedArray {

    public static int removeDuplicates(int[] nums) {
        if (nums == null || nums.length == 0) return 0;

        int k = 1;

        for (int i = 1; i < nums.length; i++) {
            if (nums[i] != nums[k - 1]) {
                nums[k] = nums[i];
                k++;
            }
        }

        return k;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 26: Remove Duplicates from Sorted Array ===");

        int[] nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
        System.out.println("Original Array: " + Arrays.toString(nums));

        int k = removeDuplicates(nums);
        System.out.println("Unique Element Count k: " + k);
        System.out.println("Compacted Array Prefix: " + Arrays.toString(Arrays.copyOf(nums, k)));
    }
}

/*
 * Time Complexity: O(N) - Single linear pass over the array.
 * Space Complexity: O(1) - Modifies the array strictly in-place.
 */

/*
 * Problem Statement:
 * Given an array of integers nums sorted in non-decreasing order, find the starting
 * and ending position of a given target value.
 * If target is not found in the array, return [-1, -1].
 * You must write an algorithm with O(log n) runtime complexity.
 * (LeetCode 34: Find First and Last Position of Element in Sorted Array)
 * 
 * Example:
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3, 4]
 * 
 * Asked in: Facebook/Meta, Amazon, LinkedIn, Microsoft, Google
 */

import java.util.Arrays;

class FindFirstAndLastPositionInSortedArray {

    /**
     * Approach:
     * Dual Binary Search (Finding Left Bound and Right Bound):
     * - First search: finds first index of target by continuing search in left half when found.
     * - Second search: finds last index of target by continuing search in right half when found.
     */
    public static int[] searchRange(int[] nums, int target) {
        int first = findBound(nums, target, true);
        if (first == -1) return new int[]{-1, -1};
        int last = findBound(nums, target, false);
        return new int[]{first, last};
    }

    private static int findBound(int[] nums, int target, boolean isFirst) {
        int low = 0;
        int high = nums.length - 1;
        int bound = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) {
                bound = mid;
                if (isFirst) {
                    high = mid - 1; // Keep searching left for earlier occurrence
                } else {
                    low = mid + 1;  // Keep searching right for later occurrence
                }
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return bound;
    }

    public static void main(String[] args) {
        int[] nums = {5, 7, 7, 8, 8, 10};

        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("Target 8: " + Arrays.toString(searchRange(nums, 8)));
        System.out.println("Target 6: " + Arrays.toString(searchRange(nums, 6)));
        System.out.println("Target 5: " + Arrays.toString(searchRange(nums, 5)));
    }
}

/*
 * Time Complexity: O(log N) - Two independent binary searches.
 * Space Complexity: O(1) auxiliary space.
 */

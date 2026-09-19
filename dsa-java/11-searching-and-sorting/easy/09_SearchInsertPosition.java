/*
 * Problem Statement:
 * Given a sorted array of distinct integers and a target value, return the index if
 * the target is found. If not, return the index where it would be if it were inserted in order.
 * You must write an algorithm with O(log n) runtime complexity.
 * (LeetCode 35: Search Insert Position - Lower Bound)
 * 
 * Example 1:
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 * 
 * Asked in: Google, Amazon, Apple, Microsoft
 */

import java.util.Arrays;

class SearchInsertPosition {

    /**
     * Approach:
     * Lower Bound Binary Search:
     * If target found, return mid.
     * When loop terminates (low > high), `low` represents the smallest index
     * where nums[low] >= target (the exact insertion point).
     */
    public static int searchInsert(int[] nums, int target) {
        int low = 0;
        int high = nums.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return low;
    }

    public static void main(String[] args) {
        int[] nums = {1, 3, 5, 6};

        System.out.println("Array: " + Arrays.toString(nums));
        int[] targets = {5, 2, 7, 0};

        for (int t : targets) {
            System.out.printf("Target %d -> Insertion index: %d%n", t, searchInsert(nums, t));
        }
    }
}

/*
 * Time Complexity: O(log N) - Standard binary search.
 * Space Complexity: O(1) auxiliary space.
 */

/*
 * Problem Statement:
 * A peak element is an element that is strictly greater than its neighbors.
 * Given a 0-indexed integer array nums, find a peak element, and return its index.
 * If the array contains multiple peaks, return the index to any of the peaks.
 * You may imagine that nums[-1] = nums[n] = -infinity.
 * You must write an algorithm that runs in O(log n) time.
 * (LeetCode 162: Find Peak Element)
 * 
 * Example:
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 5 (nums[5] == 6 is greater than its neighbors 5 and 4)
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
 */

class FindPeakElementBinarySearch {

    /**
     * Approach:
     * Binary Search on Slopes:
     * - Compare nums[mid] with nums[mid + 1]:
     *   - If nums[mid] < nums[mid + 1]: We are on an upward slope. A peak is guaranteed
     *     to exist to the right (low = mid + 1).
     *   - If nums[mid] > nums[mid + 1]: We are on a downward slope. A peak is guaranteed
     *     to exist at mid or to the left (high = mid).
     * - Terminate when low == high.
     */
    public static int findPeakElement(int[] nums) {
        int low = 0;
        int high = nums.length - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] < nums[mid + 1]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 1, 3, 5, 6, 4};

        int peakIdx = findPeakElement(nums);
        System.out.println("Array: [1, 2, 1, 3, 5, 6, 4]");
        System.out.printf("Peak found at index %d (value = %d)%n", peakIdx, nums[peakIdx]);
    }
}

/*
 * Time Complexity: O(log N) binary search steps.
 * Space Complexity: O(1) auxiliary space.
 */

/*
 * Problem Statement:
 * Given the array nums after the possible rotation and an integer target,
 * return the index of target if it is in nums, or -1 if it is not in nums.
 * You must write an algorithm with O(log n) runtime complexity.
 * (LeetCode 33: Search in Rotated Sorted Array)
 * 
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * 
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Google, Bloomberg
 */

class SearchInRotatedSortedArray {

    /**
     * Approach:
     * One-Pass Modified Binary Search:
     * Key insight: At least one half of the array (left half or right half)
     * is guaranteed to be strictly sorted!
     * 1. If nums[low] <= nums[mid], left half is sorted:
     *    - If target is between nums[low] and nums[mid], search left (high = mid - 1).
     *    - Otherwise, search right (low = mid + 1).
     * 2. Else, right half is sorted:
     *    - If target is between nums[mid] and nums[high], search right (low = mid + 1).
     *    - Otherwise, search left (high = mid - 1).
     */
    public static int search(int[] nums, int target) {
        int low = 0;
        int high = nums.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) return mid;

            // Check if left half is sorted
            if (nums[low] <= nums[mid]) {
                if (target >= nums[low] && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else { // Right half is sorted
                if (target > nums[mid] && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        int[] nums = {4, 5, 6, 7, 0, 1, 2};

        System.out.println("Rotated array: [4, 5, 6, 7, 0, 1, 2]");
        int[] targets = {0, 3, 4, 2};

        for (int t : targets) {
            System.out.printf("Search for %d: Index %d%n", t, search(nums, t));
        }
    }
}

/*
 * Time Complexity: O(log N) - Search range is halved in each step.
 * Space Complexity: O(1) auxiliary space.
 */

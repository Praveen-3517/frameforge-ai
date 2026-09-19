/**
 * Problem: Count Subarrays with Bounded Maximum (LeetCode 795)
 * Category: Two Pointers | Hard
 * Asked in: Amazon, Google
 * 
 * Given an integer array nums and two integers left and right, return the number of
 * contiguous non-empty subarrays such that the value of the maximum array element in
 * that subarray is in the range [left, right].
 * 
 * Approach - Count(max <= right) - Count(max <= left-1):
 * Helper function countAtMost(bound): counts subarrays where max <= bound.
 * For each i, dp = (i - start) = number of subarrays ending at i with max <= bound.
 * If nums[i] > bound: reset start = i + 1, dp = 0.
 * 
 * Answer = countAtMost(right) - countAtMost(left - 1)
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class CountSubarraysWithBoundedMaximum {

    private static long countAtMost(int[] nums, int bound) {
        long count = 0;
        int start = 0;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > bound) {
                start = i + 1; // reset window
            }
            count += i - start + 1;
        }

        return count;
    }

    public static int numSubarrayBoundedMax(int[] nums, int left, int right) {
        return (int) (countAtMost(nums, right) - countAtMost(nums, left - 1));
    }

    public static void main(String[] args) {
        System.out.println(numSubarrayBoundedMax(new int[]{2, 1, 4, 3}, 2, 3) + " (Expected: 3)");
        // [2], [2,1], [3] — three subarrays with max in [2,3]
        System.out.println(numSubarrayBoundedMax(new int[]{2, 9, 2, 5, 6}, 2, 8) + " (Expected: 7)");
    }
}

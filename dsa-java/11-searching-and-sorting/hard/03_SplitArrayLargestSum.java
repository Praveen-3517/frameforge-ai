/*
 * Problem Statement:
 * Given an integer array nums and an integer k, split nums into k non-empty subarrays
 * such that the largest sum of any subarray is minimized.
 * Return the minimized largest sum of the split.
 * (LeetCode 410: Split Array Largest Sum)
 * 
 * Example:
 * Input: nums = [7,2,5,10,8], k = 2
 * Output: 18 (Subarrays: [7,2,5] (sum 14) and [10,8] (sum 18); largest sum is 18)
 * 
 * Asked in: Google, Amazon, Facebook/Meta, ByteDance
 */

class SplitArrayLargestSum {

    /**
     * Approach:
     * Binary Search on Answer:
     * - Lower bound (low): max element in nums (a subarray of size 1 cannot be smaller than max(nums)).
     * - Upper bound (high): sum of all elements in nums (single subarray containing all elements).
     * - Monotonic test: canSplit(maxAllowedSum, k):
     *   Greedily accumulate elements into a subarray. When sum exceeds maxAllowedSum,
     *   start a new subarray. If total subarrays needed <= k, the bound is feasible.
     */
    public static int splitArray(int[] nums, int k) {
        int low = 0;
        int high = 0;

        for (int num : nums) {
            low = Math.max(low, num);
            high += num;
        }

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (canSplit(nums, k, mid)) {
                high = mid; // Try smaller max sum
            } else {
                low = mid + 1; // Need larger capacity
            }
        }

        return low;
    }

    private static boolean canSplit(int[] nums, int k, int maxAllowedSum) {
        int subarrays = 1;
        int currentSum = 0;

        for (int num : nums) {
            if (currentSum + num > maxAllowedSum) {
                subarrays++;
                currentSum = num;
                if (subarrays > k) return false;
            } else {
                currentSum += num;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        int[] nums = {7, 2, 5, 10, 8};
        int k = 2;

        System.out.println("Array: [7, 2, 5, 10, 8], k = 2");
        System.out.println("Minimized largest sum: " + splitArray(nums, k));

        int[] nums2 = {1, 2, 3, 4, 5};
        int k2 = 2;
        System.out.println("\nArray: [1, 2, 3, 4, 5], k = 2");
        System.out.println("Minimized largest sum: " + splitArray(nums2, k2));
    }
}

/*
 * Time Complexity: O(N * log(sum(nums) - max(nums)))
 * Space Complexity: O(1) auxiliary space.
 */

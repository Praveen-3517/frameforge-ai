/*
 * Problem Statement:
 * The distance of a pair of integers a and b is defined as the absolute difference |a - b|.
 * Given an integer array nums and an integer k, return the k-th smallest distance among
 * all the pairs nums[i] and nums[j] where 0 <= i < j < nums.length.
 * (LeetCode 719: Find K-th Smallest Pair Distance)
 * 
 * Example:
 * Input: nums = [1,3,1], k = 1
 * Output: 0 (Pairs: (1,3) diff 2, (1,1) diff 0, (3,1) diff 2; 1st smallest distance is 0)
 * 
 * Asked in: Google, Citadel, Two Sigma
 */

import java.util.Arrays;

class FindKthSmallestPairDistance {

    /**
     * Approach:
     * Binary Search on Pair Distance + Two-Pointer Sliding Window Count:
     * 1. Sort nums: O(N log N).
     * 2. The pair distance lies in range [0, nums[n-1] - nums[0]].
     * 3. For a guess distance 'mid', count how many pairs have distance <= mid
     *    in O(N) using two pointers:
     *    - For each right pointer, advance left pointer until nums[right] - nums[left] <= mid.
     *    - All pairs between left and right have distance <= mid: count += (right - left).
     * 4. If count >= k, candidate distance is viable; search left half (high = mid).
     *    Else, search right half (low = mid + 1).
     */
    public static int smallestDistancePair(int[] nums, int k) {
        Arrays.sort(nums);
        int n = nums.length;

        int low = 0;
        int high = nums[n - 1] - nums[0];

        while (low < high) {
            int mid = low + (high - low) / 2;

            int count = countPairsWithDistanceAtMost(nums, mid);
            if (count >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }

    private static int countPairsWithDistanceAtMost(int[] nums, int dist) {
        int count = 0;
        int left = 0;

        for (int right = 0; right < nums.length; right++) {
            while (nums[right] - nums[left] > dist) {
                left++;
            }
            count += (right - left);
        }

        return count;
    }

    public static void main(String[] args) {
        int[] nums = {1, 3, 1};
        int k = 1;

        System.out.println("Array: [1, 3, 1], k = 1");
        System.out.println("1st smallest distance: " + smallestDistancePair(nums, k));

        int[] nums2 = {1, 1, 1};
        int k2 = 2;
        System.out.println("\nArray: [1, 1, 1], k = 2");
        System.out.println("2nd smallest distance: " + smallestDistancePair(nums2, k2));
    }
}

/*
 * Time Complexity: O(N log N + N log(maxDist))
 * Space Complexity: O(1) auxiliary space.
 */

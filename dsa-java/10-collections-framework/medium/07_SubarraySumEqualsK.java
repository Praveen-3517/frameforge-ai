/*
 * Problem Statement:
 * Given an array of integers nums and an integer k, return the total number of subarrays
 * whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 * 
 * Example 1:
 * Input: nums = [1, 1, 1], k = 2
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [1, 2, 3], k = 3
 * Output: 2 ([1,2] and [3])
 * 
 * Asked in: Facebook/Meta, Amazon, Google, Microsoft, ByteDance
 */

import java.util.HashMap;
import java.util.Map;

class SubarraySumEqualsK {

    /**
     * Approach:
     * Prefix Sum with HashMap:
     * If prefixSum[j] - prefixSum[i] = k, then the subarray between i and j sums to k.
     * Rearranged: prefixSum[i] = prefixSum[j] - k.
     * Store counts of prefix sums in a HashMap.
     * Initialize map with (0 -> 1) to account for subarrays starting at index 0.
     */
    public static int subarraySum(int[] nums, int k) {
        int count = 0;
        int currentSum = 0;
        Map<Integer, Integer> prefixMap = new HashMap<>();
        prefixMap.put(0, 1);

        for (int num : nums) {
            currentSum += num;
            if (prefixMap.containsKey(currentSum - k)) {
                count += prefixMap.get(currentSum - k);
            }
            prefixMap.merge(currentSum, 1, Integer::sum);
        }

        return count;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 1, 1};
        int k1 = 2;
        System.out.println("nums: [1, 1, 1], k = 2 -> Subarrays: " + subarraySum(nums1, k1));

        int[] nums2 = {1, -1, 0};
        int k2 = 0;
        System.out.println("nums: [1, -1, 0], k = 0 -> Subarrays: " + subarraySum(nums2, k2));

        int[] nums3 = {3, 4, 7, 2, -3, 1, 4, 2};
        int k3 = 7;
        System.out.println("nums: [3, 4, 7, 2, -3, 1, 4, 2], k = 7 -> Subarrays: " + subarraySum(nums3, k3));
    }
}

/*
 * Time Complexity: O(N) - Single pass through the array.
 * Space Complexity: O(N) - Storing prefix sums in HashMap.
 */

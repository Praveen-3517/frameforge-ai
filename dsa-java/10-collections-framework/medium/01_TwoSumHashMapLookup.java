/*
 * Problem Statement:
 * Given an array of integers nums and an integer target, return indices of the two
 * numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use
 * the same element twice. You can return the answer in any order.
 * 
 * Example:
 * Input: nums = [2, 7, 11, 15], target = 9
 * Output: [0, 1] (nums[0] + nums[1] == 9)
 * 
 * Asked in: Amazon, Google, Apple, Microsoft, Meta
 */

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

class TwoSumHashMapLookup {

    /**
     * Approach:
     * One-Pass Hash Table:
     * While iterating, check if the complement (target - nums[i]) already exists in the map.
     * If yes, return the pair of indices.
     * If no, insert nums[i] -> i into map.
     */
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }
            map.put(nums[i], i);
        }

        throw new IllegalArgumentException("No two sum solution exists");
    }

    public static void main(String[] args) {
        int[] nums = {2, 7, 11, 15};
        int target = 9;

        int[] indices = twoSum(nums, target);
        System.out.println("Nums: " + Arrays.toString(nums) + ", Target: " + target);
        System.out.println("Solution Indices: " + Arrays.toString(indices));
        System.out.printf("Verification: nums[%d] (%d) + nums[%d] (%d) = %d%n",
                indices[0], nums[indices[0]], indices[1], nums[indices[1]], target);
    }
}

/*
 * Time Complexity: O(N) - Single pass through the array with O(1) hash lookups.
 * Space Complexity: O(N) - Map stores up to N elements.
 */

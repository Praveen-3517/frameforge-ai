/*
 * Problem Statement:
 * Given an integer array nums that may contain duplicates, return all possible subsets
 * (the power set). The solution set must not contain duplicate subsets.
 * Return the solution in any order.
 * (LeetCode 90: Subsets II)
 * 
 * Example:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * 
 * Asked in: Facebook/Meta, Amazon, Bloomberg, Microsoft
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class SubsetsTwoWithDuplicates {

    /**
     * Approach:
     * Backtracking with Duplicate Pruning:
     * 1. Sort the input array so duplicate numbers are adjacent.
     * 2. In loop starting from `start` to `nums.length`:
     *    - If i > start and nums[i] == nums[i - 1], SKIP nums[i] to prevent duplicate subsets
     *      at the same recursive depth.
     */
    public static List<List<Integer>> subsetsWithDup(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> result = new ArrayList<>();
        backtrack(0, nums, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(int start, int[] nums, List<Integer> current, List<List<Integer>> result) {
        result.add(new ArrayList<>(current));

        for (int i = start; i < nums.length; i++) {
            // Duplicate pruning
            if (i > start && nums[i] == nums[i - 1]) continue;

            current.add(nums[i]);
            backtrack(i + 1, nums, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 2};
        List<List<Integer>> powerSet = subsetsWithDup(nums);

        System.out.println("Array: [1, 2, 2]");
        System.out.println("Unique subsets (" + powerSet.size() + "):");
        for (List<Integer> subset : powerSet) {
            System.out.println("  " + subset);
        }
    }
}

/*
 * Time Complexity: O(N * 2^N) - At most 2^N subsets generated and copied.
 * Space Complexity: O(N) recursion stack and temporary list.
 */

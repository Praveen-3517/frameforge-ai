/*
 * Problem Statement:
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example:
 * Input: nums = [1, 2, 3]
 * Output: [[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]
 * 
 * Asked in: Amazon, Facebook/Meta, Microsoft, Apple, Uber
 */

import java.util.ArrayList;
import java.util.List;

class SubsetsRecursiveGeneration {

    /**
     * Approach:
     * Recursive Pick / Don't Pick (Backtracking):
     * At each element at index i, we have 2 choices:
     * 1. Include nums[i] in the current subset.
     * 2. Do not include nums[i].
     * Base case: When index reaches nums.length, add a snapshot of current subset to results.
     */
    public static List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> current = new ArrayList<>();
        backtrack(nums, 0, current, result);
        return result;
    }

    private static void backtrack(int[] nums, int index, List<Integer> current, List<List<Integer>> result) {
        if (index == nums.length) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Choice 1: Include nums[index]
        current.add(nums[index]);
        backtrack(nums, index + 1, current, result);

        // Choice 2: Exclude nums[index] (backtrack)
        current.remove(current.size() - 1);
        backtrack(nums, index + 1, current, result);
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        List<List<Integer>> powerSet = subsets(nums);

        System.out.println("Input: [1, 2, 3]");
        System.out.println("Total subsets (2^N = " + (1 << nums.length) + "): " + powerSet.size());
        System.out.println("Subsets:");
        for (List<Integer> subset : powerSet) {
            System.out.println("  " + subset);
        }
    }
}

/*
 * Time Complexity: O(N * 2^N) - 2^N total subsets, each takes O(N) to copy into result list.
 * Space Complexity: O(N) - Recursion call stack and temporary list current storage.
 */

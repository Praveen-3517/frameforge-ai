/*
 * Problem Statement:
 * You are given an integer array nums and an integer target.
 * You want to build an expression out of nums by adding one of the symbols '+' and '-'
 * before each integer in nums and then concatenate all the integers.
 * Return the number of different expressions that you can build, which evaluates to target.
 * (LeetCode 494: Target Sum)
 * 
 * Example:
 * Input: nums = [1,1,1,1,1], target = 3
 * Output: 5
 * 
 * Asked in: Facebook/Meta, Amazon, Google
 */

import java.util.HashMap;
import java.util.Map;

class TargetSumExpressionWays {

    public static int findTargetSumWays(int[] nums, int target) {
        Map<String, Integer> memo = new HashMap<>();
        return backtrack(nums, 0, 0, target, memo);
    }

    private static int backtrack(int[] nums, int index, int currentSum, int target, Map<String, Integer> memo) {
        if (index == nums.length) {
            return currentSum == target ? 1 : 0;
        }

        String stateKey = index + "," + currentSum;
        if (memo.containsKey(stateKey)) {
            return memo.get(stateKey);
        }

        // Branch 1: Add nums[index]
        int add = backtrack(nums, index + 1, currentSum + nums[index], target, memo);
        // Branch 2: Subtract nums[index]
        int subtract = backtrack(nums, index + 1, currentSum - nums[index], target, memo);

        int totalWays = add + subtract;
        memo.put(stateKey, totalWays);
        return totalWays;
    }

    public static void main(String[] args) {
        int[] nums = {1, 1, 1, 1, 1};
        int target = 3;

        System.out.println("Nums: [1, 1, 1, 1, 1], Target: 3");
        System.out.println("Total expressions equaling target: " + findTargetSumWays(nums, target) + " (Expected: 5)");
    }
}

/*
 * Time Complexity: O(N * S) where S is the sum range of nums.
 * Space Complexity: O(N * S) memoization table + O(N) call stack.
 */

/*
 * Problem Statement:
 * Given an array of distinct integers candidates and a target integer target,
 * return a list of all unique combinations of candidates where the chosen numbers sum to target.
 * You may return the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times.
 * 
 * Example:
 * Input: candidates = [2, 3, 6, 7], target = 7
 * Output: [[2, 2, 3], [7]]
 * 
 * Asked in: Facebook/Meta, Amazon, Airbnb, Google, Apple
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class CombinationSumRecursive {

    /**
     * Approach:
     * Recursive Backtracking with Unlimited Choices:
     * Sort candidates to enable pruning when candidates[i] > remaining target.
     * At index i:
     * - We can pick candidates[i] and remain at index i (unlimited usage).
     * - Or advance to index i + 1.
     */
    public static List<List<Integer>> combinationSum(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> current = new ArrayList<>();
        backtrack(candidates, target, 0, current, result);
        return result;
    }

    private static void backtrack(int[] candidates, int remain, int start, List<Integer> current, List<List<Integer>> result) {
        if (remain == 0) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            // Prune branch if element exceeds remaining target
            if (candidates[i] > remain) break;

            current.add(candidates[i]);
            // Notice: pass i (not i + 1) because same element can be reused
            backtrack(candidates, remain - candidates[i], i, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        int[] candidates = {2, 3, 6, 7};
        int target = 7;

        List<List<Integer>> combos = combinationSum(candidates, target);
        System.out.println("Candidates: " + Arrays.toString(candidates) + ", Target: " + target);
        System.out.println("Combinations summing to " + target + ":");
        for (List<Integer> c : combos) {
            System.out.println("  " + c);
        }

        int[] c2 = {2, 3, 5};
        int t2 = 8;
        System.out.println("\nCandidates: " + Arrays.toString(c2) + ", Target: " + t2);
        System.out.println("Combinations summing to " + t2 + ": " + combinationSum(c2, t2));
    }
}

/*
 * Time Complexity: O(2^(T/M)) where T is target value and M is minimal candidate value.
 * Space Complexity: O(T/M) stack frames at maximum recursion depth.
 */

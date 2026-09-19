/*
 * Problem Statement:
 * Given a collection of candidate numbers (candidates) and a target number (target),
 * find all unique combinations in candidates where the candidate numbers sum to target.
 * Each number in candidates may only be used ONCE in the combination.
 * Note: The solution set must not contain duplicate combinations.
 * (LeetCode 40: Combination Sum II)
 * 
 * Example:
 * Input: candidates = [10,1,2,7,6,1,5], target = 8
 * Output: [
 *   [1,1,6],
 *   [1,2,5],
 *   [1,7],
 *   [2,6]
 * ]
 * 
 * Asked in: Amazon, Google, Microsoft, Facebook/Meta
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class CombinationSumTwoUnique {

    /**
     * Approach:
     * Sort + Backtrack + Duplicate Pruning:
     * 1. Sort candidates.
     * 2. When candidates[i] > remaining target, break early (pruning).
     * 3. When i > start and candidates[i] == candidates[i-1], skip to prevent duplicate branch.
     * 4. Advance to i + 1 because each number can only be used once.
     */
    public static List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> result = new ArrayList<>();
        backtrack(candidates, target, 0, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(int[] candidates, int remain, int start, List<Integer> current, List<List<Integer>> result) {
        if (remain == 0) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            if (candidates[i] > remain) break; // Prune branch

            // Skip duplicates at same recursion level
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            current.add(candidates[i]);
            backtrack(candidates, remain - candidates[i], i + 1, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        int[] candidates = {10, 1, 2, 7, 6, 1, 5};
        int target = 8;

        List<List<Integer>> combos = combinationSum2(candidates, target);
        System.out.println("Candidates: " + Arrays.toString(candidates) + ", Target: " + target);
        System.out.println("Combinations (" + combos.size() + "):");
        for (List<Integer> c : combos) {
            System.out.println("  " + c);
        }
    }
}

/*
 * Time Complexity: O(2^N) bounded by number of subsets.
 * Space Complexity: O(N) recursion stack.
 */

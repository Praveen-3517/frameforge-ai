/*
 * Problem Statement:
 * Given a collection of numbers, nums, that might contain duplicates,
 * return all possible unique permutations in any order.
 * 
 * Example:
 * Input: nums = [1, 1, 2]
 * Output: [[1,1,2], [1,2,1], [2,1,1]]
 * 
 * Asked in: LinkedIn, Amazon, Microsoft, Uber, Google
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class PermutationsTwoWithDuplicates {

    /**
     * Approach:
     * Backtracking with Duplicate Pruning:
     * 1. Sort the array so identical numbers are consecutive.
     * 2. Track visited state using boolean[] used.
     * 3. Pruning condition: if nums[i] == nums[i-1] and !used[i-1], skip nums[i]
     *    because the previous duplicate has already been processed at this level.
     */
    public static List<List<Integer>> permuteUnique(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(nums);
        boolean[] used = new boolean[nums.length];
        backtrack(nums, used, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(int[] nums, boolean[] used, List<Integer> current, List<List<Integer>> result) {
        if (current.size() == nums.length) {
            result.add(new ArrayList<>(current));
            return;
        }

        for (int i = 0; i < nums.length; i++) {
            if (used[i]) continue;
            // Duplicate pruning: only use duplicate if its previous neighbor is currently in use
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

            used[i] = true;
            current.add(nums[i]);
            backtrack(nums, used, current, result);
            current.remove(current.size() - 1); // backtrack
            used[i] = false;
        }
    }

    public static void main(String[] args) {
        int[] nums = {1, 1, 2};
        List<List<Integer>> result = permuteUnique(nums);

        System.out.println("Input: " + Arrays.toString(nums));
        System.out.println("Unique permutations (" + result.size() + "):");
        for (List<Integer> p : result) {
            System.out.println("  " + p);
        }
    }
}

/*
 * Time Complexity: O(N! * N) - bounded by unique permutations.
 * Space Complexity: O(N) - boolean[] used, recursion stack, and current permutation list.
 */

/*
 * Problem Statement:
 * Given an array nums of distinct integers, return all the possible permutations.
 * You can return the answer in any order.
 * 
 * Example:
 * Input: nums = [1, 2, 3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * 
 * Asked in: Microsoft, Amazon, Google, Adobe, LinkedIn
 */

import java.util.ArrayList;
import java.util.List;

class PermutationsRecursive {

    /**
     * Approach:
     * Recursive In-Place Swapping:
     * At index 'start', swap nums[start] with every nums[i] where i ranges from start to end.
     * Recurse for start + 1.
     * Backtrack by swapping back to restore the original array state.
     */
    public static List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, 0, result);
        return result;
    }

    private static void backtrack(int[] nums, int start, List<List<Integer>> result) {
        if (start == nums.length) {
            List<Integer> current = new ArrayList<>();
            for (int num : nums) current.add(num);
            result.add(current);
            return;
        }

        for (int i = start; i < nums.length; i++) {
            swap(nums, start, i);
            backtrack(nums, start + 1, result);
            swap(nums, start, i); // backtrack
        }
    }

    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        List<List<Integer>> perms = permute(nums);

        System.out.println("Permutations of [1, 2, 3]: Total = " + perms.size());
        for (List<Integer> p : perms) {
            System.out.println("  " + p);
        }
    }
}

/*
 * Time Complexity: O(N * N!) - N! permutations, copying each takes O(N).
 * Space Complexity: O(N) - Recursion tree depth is N.
 */

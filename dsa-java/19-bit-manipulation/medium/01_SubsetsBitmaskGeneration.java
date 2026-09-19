import java.util.ArrayList;
import java.util.List;

/**
 * Problem: Subsets (LeetCode 78)
 * Asked in: Amazon, Facebook, Google, Microsoft, Bloomberg
 * 
 * Given an integer array nums of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Approach - Bitmask Enumeration:
 * For an array of n elements, there are exactly 2^n subsets.
 * Each subset corresponds to a bitmask from 0 to 2^n - 1.
 * If bit j is set in mask i, include nums[j] in subset i.
 * 
 * Time Complexity: O(2^N * N)
 * Space Complexity: O(2^N * N)
 */
class SubsetsBitmaskGeneration {

    public static List<List<Integer>> subsets(int[] nums) {
        int n = nums.length;
        int totalSubsets = 1 << n; // 2^n
        List<List<Integer>> result = new ArrayList<>();

        for (int mask = 0; mask < totalSubsets; mask++) {
            List<Integer> subset = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) != 0) {
                    subset.add(nums[j]);
                }
            }
            result.add(subset);
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 3};
        List<List<Integer>> res = subsets(nums1);
        System.out.println("All subsets of [1,2,3]: " + res);
        System.out.println("Total: " + res.size() + " (Expected: 8)");
    }
}

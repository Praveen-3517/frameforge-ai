import java.util.ArrayList;
import java.util.List;

/**
 * Problem Statement:
 * Given an integer array `nums` of unique elements, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * Solve this iteratively using bit manipulation and binary bitmasks.
 * (LeetCode 78: Subsets).
 *
 * Asked in: Facebook / Meta, Amazon, Microsoft, Google, Bloomberg
 *
 * Approach:
 * - Binary Representation of Subsets:
 *   An array with N elements has 2^N distinct subsets.
 *   Each subset corresponds to a unique integer `mask` in the range [0, 2^N - 1].
 * - The i-th bit of `mask` determines whether element `nums[i]` is included in that subset:
 *   - If `(mask & (1 << i)) != 0`, include `nums[i]`.
 *   - Otherwise, exclude `nums[i]`.
 * - Time Complexity: O(N * 2^N) to build all subsets.
 *   Space Complexity: O(N * 2^N) for output storage.
 */
class BitwiseSubsetsPowerSet {

    public static List<List<Integer>> subsets(int[] nums) {
        int n = nums.length;
        int totalSubsets = 1 << n; // 2^N subsets
        List<List<Integer>> result = new ArrayList<>(totalSubsets);

        for (int mask = 0; mask < totalSubsets; mask++) {
            List<Integer> currentSubset = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                // Check if the i-th bit is set in mask
                if ((mask & (1 << i)) != 0) {
                    currentSubset.add(nums[i]);
                }
            }
            result.add(currentSubset);
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 78: Power Set Generation via Bitmasks ===");

        int[] nums = { 1, 2, 3 };
        List<List<Integer>> allSubsets = subsets(nums);

        System.out.println("Input Array: " + java.util.Arrays.toString(nums));
        System.out.printf("Total Subsets (2^%d = %d):%n", nums.length, allSubsets.size());

        for (int i = 0; i < allSubsets.size(); i++) {
            String binaryMask = String.format("%3s", Integer.toBinaryString(i)).replace(' ', '0');
            System.out.printf("  Mask [%s] (%2d) ==> %s%n", binaryMask, i, allSubsets.get(i));
        }
    }
}

/*
 * Time Complexity: O(N * 2^N) - Iterate through 2^N bitmasks, each checking N bits.
 * Space Complexity: O(N * 2^N) - Memory required to store all subsets.
 */

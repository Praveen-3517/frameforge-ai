/*
 * Problem Statement:
 * Given an unsorted integer array nums, return the smallest missing positive integer.
 * You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.
 * (LeetCode 41: First Missing Positive)
 * 
 * Example 1:
 * Input: nums = [1, 2, 0]
 * Output: 3
 * 
 * Example 2:
 * Input: nums = [3, 4, -1, 1]
 * Output: 2
 * 
 * Asked in: Amazon, Google, Microsoft, Facebook/Meta
 */

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class FirstMissingPositiveArrayMap {

    /**
     * Approach 1: HashSet Lookup (O(N) time, O(N) space)
     */
    public static int firstMissingPositiveSet(int[] nums) {
        Set<Integer> set = new HashSet<>();
        for (int x : nums) {
            if (x > 0) set.add(x);
        }

        int target = 1;
        while (set.contains(target)) {
            target++;
        }
        return target;
    }

    /**
     * Approach 2: In-place Index Mapping / Cycle Placement (O(N) time, O(1) space)
     * Place each number x at its correct index (x - 1) if 1 <= x <= n.
     */
    public static int firstMissingPositiveOptimal(int[] nums) {
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                // Swap nums[i] to its target index nums[i] - 1
                int targetIdx = nums[i] - 1;
                int temp = nums[i];
                nums[i] = nums[targetIdx];
                nums[targetIdx] = temp;
            }
        }

        // Find first slot where nums[i] != i + 1
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1;
    }

    public static void main(String[] args) {
        int[][] tests = {
            {1, 2, 0},
            {3, 4, -1, 1},
            {7, 8, 9, 11, 12},
            {1}
        };

        System.out.println("--- First Missing Positive Integer ---");
        for (int[] t : tests) {
            int resSet = firstMissingPositiveSet(t);
            int resOpt = firstMissingPositiveOptimal(t.clone());
            System.out.printf("Array: %-20s -> Missing: %d (Optimal: %d)%n",
                    Arrays.toString(t), resSet, resOpt);
        }
    }
}

/*
 * Time Complexity: O(N) - Each number swapped into correct spot at most once.
 * Space Complexity: Optimal: O(1) auxiliary space.
 */

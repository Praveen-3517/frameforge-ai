/*
 * Problem Statement:
 * Given an array of positive integers nums and a target integer target,
 * return true if there exists a subset whose elements sum up exactly to target,
 * otherwise return false.
 * 
 * Example:
 * Input: nums = [3, 34, 4, 12, 5, 2], target = 9
 * Output: true (subset [4, 5] sums to 9)
 * 
 * Asked in: Amazon, Samsung, Adobe, Cisco
 */

class SumOfSubsetsEqualsTarget {

    /**
     * Approach:
     * Recursive Pick / Don't Pick:
     * At index i:
     * - Include nums[i]: recurse with target - nums[i]
     * - Exclude nums[i]: recurse with target
     * Base cases:
     * - if target == 0: return true.
     * - if index == nums.length or target < 0: return false.
     */
    public static boolean hasSubsetSum(int[] nums, int target) {
        return helper(nums, 0, target);
    }

    private static boolean helper(int[] nums, int index, int target) {
        if (target == 0) return true;
        if (index == nums.length || target < 0) return false;

        // Include or exclude
        return helper(nums, index + 1, target - nums[index]) ||
               helper(nums, index + 1, target);
    }

    public static void main(String[] args) {
        int[] nums = {3, 34, 4, 12, 5, 2};

        System.out.println("Nums: [3, 34, 4, 12, 5, 2]");
        int[] targets = {9, 30, 14, 100};

        for (int t : targets) {
            System.out.printf("Subset summing to %3d exists? %b%n", t, hasSubsetSum(nums, t));
        }
    }
}

/*
 * Time Complexity: O(2^N) in worst case exploration.
 * Space Complexity: O(N) recursion stack depth.
 */

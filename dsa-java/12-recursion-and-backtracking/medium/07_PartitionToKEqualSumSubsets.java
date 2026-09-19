/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return true if it is possible to divide
 * this array into k non-empty subsets whose sums are all equal.
 * (LeetCode 698: Partition to K Equal Sum Subsets)
 * 
 * Example:
 * Input: nums = [4,3,2,3,5,2,1], k = 4
 * Output: true (Subsets: [5], [1,4], [2,3], [2,3] each sum to 5)
 * 
 * Asked in: Amazon, Google, LinkedIn
 */

import java.util.Arrays;

class PartitionToKEqualSumSubsets {

    /**
     * Approach:
     * Backtracking with Crucial Pruning:
     * 1. Total sum must be divisible by k. Target sum per subset = sum / k.
     * 2. Sort array in descending order to place larger elements first (prunes impossible branches earlier).
     * 3. Track visited elements using boolean[] visited.
     * 4. When current subset sum hits target, recurse with k - 1 and reset current sum to 0.
     */
    public static boolean canPartitionKSubsets(int[] nums, int k) {
        int sum = 0;
        for (int n : nums) sum += n;
        if (sum % k != 0) return false;

        int target = sum / k;
        Arrays.sort(nums);
        if (nums[nums.length - 1] > target) return false;

        boolean[] visited = new boolean[nums.length];
        return backtrack(nums.length - 1, nums, visited, k, 0, target);
    }

    private static boolean backtrack(int index, int[] nums, boolean[] visited, int k, int currentSum, int target) {
        if (k == 1) return true; // Last subset automatically sums to target

        if (currentSum == target) {
            // One subset complete! Build the next subset
            return backtrack(nums.length - 1, nums, visited, k - 1, 0, target);
        }

        for (int i = index; i >= 0; i--) {
            if (visited[i] || currentSum + nums[i] > target) continue;

            visited[i] = true;
            if (backtrack(i - 1, nums, visited, k, currentSum + nums[i], target)) {
                return true;
            }
            visited[i] = false; // backtrack

            // Crucial pruning: If first element attempted for this subset failed, no other choice will work
            if (currentSum == 0) break;
        }

        return false;
    }

    public static void main(String[] args) {
        int[] nums = {4, 3, 2, 3, 5, 2, 1};
        int k = 4;

        System.out.println("Nums: " + Arrays.toString(nums) + ", k = " + k);
        System.out.println("Can partition into " + k + " equal subsets? " + canPartitionKSubsets(nums, k));
    }
}

/*
 * Time Complexity: O(k * 2^N) with strong pruning.
 * Space Complexity: O(N) visited array and call stack.
 */

import java.util.Arrays;

/**
 * Problem Statement:
 * Given an array `nums`. We define a running sum of an array as:
 *   `runningSum[i] = sum(nums[0] ... nums[i])`.
 * Return the running sum of `nums`.
 * Additionally demonstrate how a Prefix Sum array enables O(1) static Range Sum Queries.
 * (LeetCode 1480: Running Sum of 1d Array).
 *
 * Example:
 * [1, 2, 3, 4] -> [1, 3, 6, 10]
 *
 * Asked in: Amazon, Apple, Google, Adobe
 *
 * Approach:
 * - Prefix Sum Recurrence:
 *   `runningSum[i] = runningSum[i - 1] + nums[i]` for i >= 1.
 * - Range Sum Query Application:
 *   Sum of subarray nums[L..R] is computed in O(1) time:
 *   `sum(L, R) = prefix[R] - (L > 0 ? prefix[L - 1] : 0)`.
 */
class RunningSumOf1DArray {

    // Return new array with prefix sum
    public static int[] runningSum(int[] nums) {
        if (nums == null || nums.length == 0) return new int[0];

        int[] prefix = new int[nums.length];
        prefix[0] = nums[0];

        for (int i = 1; i < nums.length; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }

        return prefix;
    }

    // O(1) Range Sum Query helper
    public static int rangeSumQuery(int[] prefix, int left, int right) {
        if (left == 0) return prefix[right];
        return prefix[right] - prefix[left - 1];
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 1480: Running Sum (Prefix Sum & O(1) Range Query) ===");

        int[] nums = { 3, 1, 2, 10, 1 };
        int[] prefix = runningSum(nums);

        System.out.println("Original Array : " + Arrays.toString(nums));
        System.out.println("Running Sum    : " + Arrays.toString(prefix));

        // Range query tests
        System.out.println("\nRange Sum Queries in O(1) time:");
        System.out.printf("Sum of range [1..3] (indices 1 to 3: 1+2+10) = %d%n", rangeSumQuery(prefix, 1, 3));
        System.out.printf("Sum of range [0..4] (entire array sum)       = %d%n", rangeSumQuery(prefix, 0, 4));
    }
}

/*
 * Time Complexity:
 *   - Precomputation: O(N)
 *   - Range query: O(1)
 * Space Complexity: O(N) - Storage for the prefix sum array.
 */

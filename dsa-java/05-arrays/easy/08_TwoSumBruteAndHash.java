import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 * Given an array of integers `nums` and an integer `target`, return indices of the two numbers
 * such that they add up to target.
 * Assume exactly one valid solution exists, and you may not use the same element twice.
 * (LeetCode 1: Two Sum).
 *
 * Example:
 * nums = [2, 7, 11, 15], target = 9 -> [0, 1]
 *
 * Asked in: Google, Amazon, Facebook / Meta, Apple, Microsoft (The #1 Most Asked Question)
 *
 * Approach:
 * - Method 1: Brute Force (O(N^2) Time, O(1) Space):
 *   Nested loops checking all pairs `(i, j)`.
 * - Method 2: One-Pass HashMap (O(N) Time, O(N) Space):
 *   For each element `nums[i]`:
 *   - The required complement is `complement = target - nums[i]`.
 *   - Check if `complement` is already in the hash map.
 *   - If found, return `[map.get(complement), i]`.
 *   - Otherwise, store `map.put(nums[i], i)` and proceed.
 */
class TwoSumBruteAndHash {

    // Optimal One-Pass HashMap: O(N) Time, O(N) Space
    public static int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];

            if (map.containsKey(complement)) {
                return new int[] { map.get(complement), i };
            }

            map.put(nums[i], i);
        }

        return new int[0];
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 1: Two Sum (One-Pass HashMap O(N)) ===");

        int[] nums = { 2, 7, 11, 15 };
        int target = 9;

        int[] result = twoSum(nums, target);
        System.out.println("Array : " + Arrays.toString(nums));
        System.out.println("Target: " + target);
        System.out.printf("Indices: %s (Values: %d + %d = %d)%n",
                Arrays.toString(result), nums[result[0]], nums[result[1]], target);
    }
}

/*
 * Time Complexity: O(N) - Single pass over the array with O(1) average hash lookups.
 * Space Complexity: O(N) - Storage for up to N entries in the hash map.
 */

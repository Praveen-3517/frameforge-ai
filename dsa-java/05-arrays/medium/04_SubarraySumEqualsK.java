import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 * Given an array of integers `nums` and an integer `k`, return the total number of subarrays
 * whose sum equals to `k`.
 * (LeetCode 560: Subarray Sum Equals K).
 *
 * Example:
 * nums = [1, 1, 1], k = 2 -> Output: 2 ([1, 1] at index 0..1, and [1, 1] at index 1..2)
 * nums = [1, 2, 3], k = 3 -> Output: 2 ([1, 2] and [3])
 *
 * Asked in: Facebook / Meta (#1 High Frequency), Google, Amazon, Microsoft
 *
 * Approach:
 * - Why Sliding Window / Two Pointers FAILS:
 *   The array may contain NEGATIVE numbers. Because adding a number does not guarantee the sum increases,
 *   monotonicity does not hold, breaking two-pointer/sliding window assumptions!
 * - Prefix Sum + Frequency HashMap (O(N) Time, O(N) Space):
 *   Subarray `nums[i..j]` sums to `k` if and only if:
 *   `prefixSum[j] - prefixSum[i - 1] == k`
 *   Rearranging:
 *   `prefixSum[i - 1] == prefixSum[j] - k`
 *   - As we maintain `runningSum`:
 *     Check how many times `(runningSum - k)` has appeared previously in `prefixCountMap`.
 *     Add that count to our result!
 *     Then record `runningSum` in the map.
 *   - Base Case: `map.put(0, 1)` represents an empty prefix having sum 0 before index 0.
 */
class SubarraySumEqualsK {

    public static int subarraySum(int[] nums, int k) {
        if (nums == null || nums.length == 0) return 0;

        Map<Integer, Integer> prefixCountMap = new HashMap<>();
        prefixCountMap.put(0, 1); // Base case: prefix of sum 0 occurs once initially

        int runningSum = 0;
        int totalSubarrays = 0;

        for (int num : nums) {
            runningSum += num;

            // Check if (runningSum - k) was seen before
            if (prefixCountMap.containsKey(runningSum - k)) {
                totalSubarrays += prefixCountMap.get(runningSum - k);
            }

            // Record current running sum
            prefixCountMap.put(runningSum, prefixCountMap.getOrDefault(runningSum, 0) + 1);
        }

        return totalSubarrays;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 560: Subarray Sum Equals K (Prefix Sum + Map) ===");

        int[][] testArrays = {
            { 1, 1, 1 },
            { 1, 2, 3 },
            { 1, -1, 0 },
            { 3, 4, 7, 2, -3, 1, 4, 2 }
        };
        int[] kValues = { 2, 3, 0, 7 };

        for (int i = 0; i < testArrays.length; i++) {
            int count = subarraySum(testArrays[i], kValues[i]);
            System.out.printf("Array: %-25s | k = %d ==> Count: %d%n",
                    java.util.Arrays.toString(testArrays[i]), kValues[i], count);
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through the array with O(1) hash map lookups.
 * Space Complexity: O(N) - Storage for up to N distinct prefix sums.
 */

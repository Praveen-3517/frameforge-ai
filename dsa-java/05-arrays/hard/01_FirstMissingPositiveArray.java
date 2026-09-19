import java.util.Arrays;

/**
 * Problem Statement:
 * Given an unsorted integer array `nums`, return the smallest positive integer that is not present in `nums`.
 * Must run in O(N) time and use O(1) auxiliary memory.
 * (LeetCode 41: First Missing Positive - Hard).
 *
 * Asked in: Amazon, Google, Microsoft, Facebook / Meta
 *
 * Approach:
 * - Cyclic Index Mapping (O(N) Time, O(1) Space):
 *   Array of length N can hold integers from 1 to N at index `0` to `N - 1`.
 *   Iterate through array:
 *   While `nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]`:
 *     Swap `nums[i]` and `nums[nums[i] - 1]`.
 *   Second pass:
 *     Return first `i + 1` where `nums[i] != i + 1`.
 *     If all 1..N are placed, return `n + 1`.
 */
class FirstMissingPositiveArray {

    public static int firstMissingPositive(int[] nums) {
        if (nums == null || nums.length == 0) return 1;

        int n = nums.length;

        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                int targetIdx = nums[i] - 1;
                int temp = nums[i];
                nums[i] = nums[targetIdx];
                nums[targetIdx] = temp;
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 41: First Missing Positive (Cyclic Array Indexing) ===");

        int[][] testArrays = {
            { 1, 2, 0 },
            { 3, 4, -1, 1 },
            { 7, 8, 9, 11, 12 },
            { 1, 2, 3 }
        };

        for (int[] arr : testArrays) {
            int[] orig = arr.clone();
            int ans = firstMissingPositive(arr);
            System.out.printf("Array: %-18s ==> First Missing: %d%n", Arrays.toString(orig), ans);
        }
    }
}

/*
 * Time Complexity: O(N) - Each number is placed in its home index at most once.
 * Space Complexity: O(1) - Pure in-place cyclic index placement.
 */

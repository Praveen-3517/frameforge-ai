import java.util.Arrays;

/**
 * Problem: Longest Increasing Subsequence (LeetCode 300)
 * Asked in: Google, Amazon, Microsoft, Apple, Bloomberg
 * 
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * 
 * Approach:
 * Patience Sorting + Binary Search (O(N log N)):
 * Maintain an array `tails` where `tails[i]` stores the smallest tail of all increasing subsequences of length i + 1.
 * For each num in nums:
 * - Use binary search (`Arrays.binarySearch`) to find num's position in `tails`.
 * - If not found, binarySearch returns `-(insertion_point) - 1`.
 * - If insertion_point == size, append num to tails (increasing LIS length by 1).
 * - Otherwise, update `tails[insertion_point] = num` (maintaining smaller possible tail).
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for tails array.
 */
class LongestIncreasingSubsequence {

    public static int lengthOfLIS(int[] nums) {
        int[] tails = new int[nums.length];
        int size = 0;

        for (int x : nums) {
            int i = Arrays.binarySearch(tails, 0, size, x);
            if (i < 0) {
                i = -(i + 1);
            }
            tails[i] = x;
            if (i == size) {
                size++;
            }
        }

        return size;
    }

    public static void main(String[] args) {
        int[] nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
        System.out.println("LIS length 1: " + lengthOfLIS(nums1) + " (Expected: 4)");

        int[] nums2 = {0, 1, 0, 3, 2, 3};
        System.out.println("LIS length 2: " + lengthOfLIS(nums2) + " (Expected: 4)");

        int[] nums3 = {7, 7, 7, 7, 7, 7, 7};
        System.out.println("LIS length 3: " + lengthOfLIS(nums3) + " (Expected: 1)");
    }
}

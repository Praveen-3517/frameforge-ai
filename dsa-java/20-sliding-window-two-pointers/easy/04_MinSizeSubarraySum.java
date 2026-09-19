/**
 * Problem: Minimum Size Subarray Sum (LeetCode 209)
 * Category: Variable-Size Sliding Window | Easy/Medium
 * Asked in: Amazon, Facebook, Google, Microsoft
 * 
 * Given an array of positive integers nums and a positive integer target, return the
 * minimal length of a subarray whose sum is >= target. If no such subarray exists, return 0.
 * 
 * Approach - Variable Sliding Window:
 * 1. Expand: add arr[right] to windowSum.
 * 2. Shrink: while windowSum >= target, record window size and remove arr[left].
 * 3. Move left forward to shrink the window.
 * 
 * This ensures we find the minimum length window satisfying the sum condition.
 * 
 * Time Complexity: O(N) amortized — each element enters and leaves the window once.
 * Space Complexity: O(1)
 */
class MinSizeSubarraySum {

    public static int minSubArrayLen(int target, int[] nums) {
        int left = 0;
        int windowSum = 0;
        int minLength = Integer.MAX_VALUE;

        for (int right = 0; right < nums.length; right++) {
            windowSum += nums[right];

            while (windowSum >= target) {
                minLength = Math.min(minLength, right - left + 1);
                windowSum -= nums[left++]; // shrink window from left
            }
        }

        return minLength == Integer.MAX_VALUE ? 0 : minLength;
    }

    public static void main(String[] args) {
        System.out.println("Min length: " + minSubArrayLen(7, new int[]{2, 3, 1, 2, 4, 3}) + " (Expected: 2)");
        // [4, 3] has sum 7 with length 2
        System.out.println("Min length: " + minSubArrayLen(4, new int[]{1, 4, 4}) + " (Expected: 1)");
        System.out.println("Min length: " + minSubArrayLen(11, new int[]{1, 1, 1, 1, 1, 1, 1, 1}) + " (Expected: 0)");
    }
}

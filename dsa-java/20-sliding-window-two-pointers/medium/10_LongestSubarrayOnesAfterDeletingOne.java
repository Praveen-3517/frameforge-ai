/**
 * Problem: Longest Subarray of 1's After Deleting One Element (LeetCode 1493)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Facebook
 * 
 * Given a binary array nums, you should delete one element from it.
 * Return the size of the longest non-empty subarray containing only 1's in the resulting array.
 * Return 0 if there is no such subarray.
 * 
 * Approach - Variable Window (At Most 1 Zero):
 * Maintain a window with at most one zero. When zeroCount > 1, shrink from left.
 * Answer = max window size - 1 (because we must delete exactly one element,
 * even if the window has no zeros, we delete one 1).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class LongestSubarrayOnesAfterDeletingOne {

    public static int longestSubarray(int[] nums) {
        int left = 0;
        int zeroCount = 0;
        int maxLength = 0;

        for (int right = 0; right < nums.length; right++) {
            if (nums[right] == 0) zeroCount++;

            while (zeroCount > 1) {
                if (nums[left++] == 0) zeroCount--;
            }

            // -1 because we must delete exactly one element from window
            maxLength = Math.max(maxLength, right - left); // (right - left + 1) - 1
        }

        return maxLength;
    }

    public static void main(String[] args) {
        System.out.println(longestSubarray(new int[]{1, 1, 0, 1}) + " (Expected: 3)");
        System.out.println(longestSubarray(new int[]{0, 1, 1, 1, 0, 1, 1, 0, 1}) + " (Expected: 5)");
        System.out.println(longestSubarray(new int[]{1, 1, 1}) + " (Expected: 2)"); // must delete one '1'
    }
}

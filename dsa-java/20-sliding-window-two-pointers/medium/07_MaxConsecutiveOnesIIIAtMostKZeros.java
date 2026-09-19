/**
 * Problem: Max Consecutive Ones III (LeetCode 1004)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Google, Bloomberg, Facebook
 * 
 * Given a binary array nums and an integer k, return the maximum number of consecutive 1's
 * in the array if you can flip at most k 0's.
 * 
 * Approach - Variable Sliding Window (At Most K Zeros):
 * Maintain a window that contains at most k zeros.
 * Expand right; if nums[right] == 0, decrement k.
 * If k < 0 (exceeded flips), shrink from left:
 *   if nums[left] == 0, increment k back; advance left.
 * Track max window size.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class MaxConsecutiveOnesIIIAtMostKZeros {

    public static int longestOnes(int[] nums, int k) {
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < nums.length; right++) {
            if (nums[right] == 0) k--;

            while (k < 0) {
                if (nums[left++] == 0) k++;
            }

            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }

    public static void main(String[] args) {
        System.out.println(longestOnes(new int[]{1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0}, 2) + " (Expected: 6)");
        // Flip 2 zeros at positions 9 and 10: window [1,1,1,1,0,1,1,1,1,1] -> 6 ones
        System.out.println(longestOnes(new int[]{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1}, 3) + " (Expected: 10)");
    }
}

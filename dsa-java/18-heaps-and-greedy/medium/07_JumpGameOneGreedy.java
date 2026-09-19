/**
 * Problem: Jump Game (LeetCode 55)
 * Asked in: Amazon, Google, Microsoft, Apple
 * 
 * You are given an integer array nums. You are initially positioned at the array's first index,
 * and each element in the array represents your maximum jump length at that position.
 * Return true if you can reach the last index, or false otherwise.
 * 
 * Approach:
 * Greedy Max Reachable Horizon:
 * Track maxReach: the farthest index we can reach so far.
 * - At each index i:
 *   - If i > maxReach, we can never reach this index -> return false.
 *   - Update maxReach = max(maxReach, i + nums[i]).
 *   - If maxReach >= nums.length - 1, return true.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class JumpGameOneGreedy {

    public static boolean canJump(int[] nums) {
        int maxReach = 0;

        for (int i = 0; i < nums.length; i++) {
            if (i > maxReach) {
                return false;
            }
            maxReach = Math.max(maxReach, i + nums[i]);
            if (maxReach >= nums.length - 1) {
                return true;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        int[] nums1 = {2, 3, 1, 1, 4};
        System.out.println("Can jump 1: " + canJump(nums1) + " (Expected: true)");

        int[] nums2 = {3, 2, 1, 0, 4};
        System.out.println("Can jump 2: " + canJump(nums2) + " (Expected: false)");
    }
}

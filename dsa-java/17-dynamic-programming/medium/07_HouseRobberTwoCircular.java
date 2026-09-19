/**
 * Problem: House Robber II (LeetCode 213)
 * Asked in: Amazon, Microsoft, Google
 * 
 * All houses at this place are arranged in a circle. That means the first house is the
 * neighbor of the last one. Meanwhile, adjacent houses have a security system connected,
 * and it will automatically contact the police if two adjacent houses are broken into.
 * Return the maximum amount of money you can rob tonight without alerting the police.
 * 
 * Approach:
 * Circular reduction to two linear House Robber subproblems:
 * Since house 0 and house n - 1 cannot both be robbed:
 * - Case 1: Rob houses in range [0, n - 2] (exclude last house).
 * - Case 2: Rob houses in range [1, n - 1] (exclude first house).
 * Answer = max(Case 1, Case 2).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class HouseRobberTwoCircular {

    public static int rob(int[] nums) {
        if (nums == null || nums.length == 0) return 0;
        if (nums.length == 1) return nums[0];
        if (nums.length == 2) return Math.max(nums[0], nums[1]);

        return Math.max(robRange(nums, 0, nums.length - 2),
                        robRange(nums, 1, nums.length - 1));
    }

    private static int robRange(int[] nums, int start, int end) {
        int prev2 = 0;
        int prev1 = 0;

        for (int i = start; i <= end; i++) {
            int curr = Math.max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }

    public static void main(String[] args) {
        int[] nums1 = {2, 3, 2};
        System.out.println("Max loot 1: " + rob(nums1) + " (Expected: 3)");

        int[] nums2 = {1, 2, 3, 1};
        System.out.println("Max loot 2: " + rob(nums2) + " (Expected: 4)");

        int[] nums3 = {1, 2, 3};
        System.out.println("Max loot 3: " + rob(nums3) + " (Expected: 3)");
    }
}

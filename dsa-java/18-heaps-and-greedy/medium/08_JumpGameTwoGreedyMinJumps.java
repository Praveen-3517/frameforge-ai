/**
 * Problem: Jump Game II (LeetCode 45)
 * Asked in: Amazon, Google, Microsoft, Apple
 * 
 * You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].
 * Each element nums[i] represents the maximum length of a forward jump from index i.
 * Return the minimum number of jumps to reach nums[n - 1].
 * 
 * Approach:
 * Implicit BFS / Greedy Window:
 * - Maintain two boundaries:
 *   - currentEnd: the farthest point reachable with current number of jumps.
 *   - farthest: the farthest point reachable with one additional jump.
 * - When index i reaches currentEnd, we MUST take another jump -> jumps++, currentEnd = farthest.
 * 
 * Time Complexity: O(N) single pass.
 * Space Complexity: O(1)
 */
class JumpGameTwoGreedyMinJumps {

    public static int jump(int[] nums) {
        if (nums.length <= 1) return 0;

        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i < nums.length - 1; i++) {
            farthest = Math.max(farthest, i + nums[i]);

            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
                if (currentEnd >= nums.length - 1) break;
            }
        }

        return jumps;
    }

    public static void main(String[] args) {
        int[] nums1 = {2, 3, 1, 1, 4};
        System.out.println("Min jumps 1: " + jump(nums1) + " (Expected: 2)"); // jump to index 1, then to index 4

        int[] nums2 = {2, 3, 0, 1, 4};
        System.out.println("Min jumps 2: " + jump(nums2) + " (Expected: 2)");
    }
}

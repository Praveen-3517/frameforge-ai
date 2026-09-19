/**
 * Problem: Min Cost Climbing Stairs (LeetCode 746)
 * Asked in: Amazon, Google, Microsoft
 * 
 * You are given an integer array cost where cost[i] is the cost of ith step on a staircase.
 * Once you pay the cost, you can either climb one or two steps.
 * You can either start from the step with index 0, or the step with index 1.
 * Return the minimum cost to reach the top of the floor.
 * 
 * Approach:
 * dp[i] = cost to reach step i.
 * dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]).
 * Optimized with two variables for O(1) space.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class MinCostClimbingStairs {

    public static int minCostClimbingStairs(int[] cost) {
        int n = cost.length;
        int prev2 = cost[0];
        int prev1 = cost[1];

        for (int i = 2; i < n; i++) {
            int curr = cost[i] + Math.min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return Math.min(prev1, prev2);
    }

    public static void main(String[] args) {
        int[] cost1 = {10, 15, 20};
        System.out.println("Min cost 1: " + minCostClimbingStairs(cost1) + " (Expected: 15)");

        int[] cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
        System.out.println("Min cost 2: " + minCostClimbingStairs(cost2) + " (Expected: 6)");
    }
}

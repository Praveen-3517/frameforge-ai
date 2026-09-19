/*
 * Problem Statement:
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you
 * climb to the top?
 * (LeetCode 70: Climbing Stairs)
 * 
 * Example 1:
 * Input: n = 2
 * Output: 2 (1 step + 1 step, or 2 steps)
 * 
 * Example 2:
 * Input: n = 3
 * Output: 3 (1+1+1, 1+2, 2+1)
 * 
 * Asked in: Amazon, Apple, Google, Adobe, Uber
 */

class ClimbingStairsWaysRecursion {

    // Top-Down Memoized Recursion
    public static int climbStairs(int n) {
        int[] memo = new int[n + 1];
        return helper(n, memo);
    }

    private static int helper(int n, int[] memo) {
        if (n <= 2) return n;
        if (memo[n] != 0) return memo[n];
        return memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
    }

    public static void main(String[] args) {
        int[] testCases = {1, 2, 3, 4, 5, 10, 20};

        System.out.println("--- Climbing Stairs Distinct Ways ---");
        for (int n : testCases) {
            System.out.printf("Steps: %2d -> Distinct Ways: %d%n", n, climbStairs(n));
        }
    }
}

/*
 * Time Complexity: O(n) with memoization.
 * Space Complexity: O(n) recursion stack and memo array.
 */

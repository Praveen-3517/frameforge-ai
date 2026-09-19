import java.util.Arrays;

/**
 * Problem: Coin Change (LeetCode 322)
 * Asked in: Amazon, Microsoft, Facebook, Apple, Google
 * 
 * You are given an integer array coins representing coins of different denominations
 * and an integer amount representing a total amount of money. Return the fewest number
 * of coins that you need to make up that amount. If that amount cannot be made up, return -1.
 * You may assume you have an infinite number of each kind of coin.
 * 
 * Approach:
 * Unbounded Knapsack / Bottom-Up 1D DP:
 * Let dp[i] be the minimum coins needed to make amount i.
 * - Base case: dp[0] = 0; initialize rest with amount + 1.
 * - For each amount i from 1 to amount:
 *   - For each coin in coins:
 *     - If i - coin >= 0:
 *       dp[i] = min(dp[i], 1 + dp[i - coin])
 * 
 * Time Complexity: O(amount * |coins|)
 * Space Complexity: O(amount)
 */
class CoinChangeMinimumCoins {

    public static int coinChange(int[] coins, int amount) {
        int max = amount + 1;
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, max);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = Math.min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        int[] coins1 = {1, 2, 5};
        System.out.println("Min coins for 11: " + coinChange(coins1, 11) + " (Expected: 3)");

        int[] coins2 = {2};
        System.out.println("Min coins for 3: " + coinChange(coins2, 3) + " (Expected: -1)");

        int[] coins3 = {1};
        System.out.println("Min coins for 0: " + coinChange(coins3, 0) + " (Expected: 0)");
    }
}

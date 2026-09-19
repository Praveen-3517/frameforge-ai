import java.util.Arrays;

/**
 * Problem: Best Time to Buy and Sell Stock IV (LeetCode 188)
 * Asked in: Google, Amazon, Facebook, Bloomberg
 * 
 * You are given an integer array prices where prices[i] is the price of a given stock
 * on the ith day, and an integer k. Complete at most k transactions.
 * Return the maximum profit you can achieve.
 * 
 * Approach:
 * State Machine DP:
 * - If k >= n / 2, we can make as many transactions as we want (greedy peak-valley approach).
 * - Otherwise:
 *   Maintain buy[t] and sell[t] arrays for 1 <= t <= k:
 *   buy[t] represents max balance after t-th buy.
 *   sell[t] represents max balance after t-th sell.
 *   Transition for day price:
 *   buy[t] = max(buy[t], sell[t - 1] - price)
 *   sell[t] = max(sell[t], buy[t] + price)
 * 
 * Time Complexity: O(N * K)
 * Space Complexity: O(K)
 */
class BestTimeToBuySellStockFourKTransactions {

    public static int maxProfit(int k, int[] prices) {
        if (prices == null || prices.length == 0 || k == 0) return 0;
        int n = prices.length;

        // Unlimited transactions optimization
        if (k >= n / 2) {
            int maxProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i - 1]) {
                    maxProfit += prices[i] - prices[i - 1];
                }
            }
            return maxProfit;
        }

        int[] buy = new int[k + 1];
        int[] sell = new int[k + 1];
        Arrays.fill(buy, -prices[0]);

        for (int price : prices) {
            for (int t = 1; t <= k; t++) {
                buy[t] = Math.max(buy[t], sell[t - 1] - price);
                sell[t] = Math.max(sell[t], buy[t] + price);
            }
        }

        return sell[k];
    }

    public static void main(String[] args) {
        int[] prices1 = {2, 4, 1};
        System.out.println("Max profit (k=2): " + maxProfit(2, prices1) + " (Expected: 2)");

        int[] prices2 = {3, 2, 6, 5, 0, 3};
        System.out.println("Max profit (k=2): " + maxProfit(2, prices2) + " (Expected: 7)");
    }
}

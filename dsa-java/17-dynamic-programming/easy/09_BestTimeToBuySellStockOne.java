/**
 * Problem: Best Time to Buy and Sell Stock (LeetCode 121)
 * Asked in: Amazon, Facebook, Microsoft, Apple, Google
 * 
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing
 * a different day in the future to sell that stock. Return the maximum profit.
 * 
 * Approach:
 * One-Pass Dynamic Tracking:
 * Track the minimum buying price seen so far (`minPrice`).
 * For each price:
 * - profit = price - minPrice
 * - maxProfit = max(maxProfit, profit)
 * - minPrice = min(minPrice, price)
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class BestTimeToBuySellStockOne {

    public static int maxProfit(int[] prices) {
        if (prices == null || prices.length == 0) return 0;

        int minPrice = prices[0];
        int maxProfit = 0;

        for (int i = 1; i < prices.length; i++) {
            if (prices[i] < minPrice) {
                minPrice = prices[i];
            } else {
                maxProfit = Math.max(maxProfit, prices[i] - minPrice);
            }
        }

        return maxProfit;
    }

    public static void main(String[] args) {
        int[] prices1 = {7, 1, 5, 3, 6, 4};
        System.out.println("Max Profit 1: " + maxProfit(prices1) + " (Expected: 5)");

        int[] prices2 = {7, 6, 4, 3, 1};
        System.out.println("Max Profit 2: " + maxProfit(prices2) + " (Expected: 0)");
    }
}

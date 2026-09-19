/*
 * Problem Statement:
 * You are given an integer array prices where prices[i] is the price of the i-th item in a shop.
 * There is a special discount: if you buy the i-th item, then you will receive a discount
 * equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <= prices[i].
 * Otherwise, you receive no discount at all.
 * Return an integer array answer where answer[i] is the final price you will pay for the i-th item.
 * (LeetCode 1475: Final Prices With a Special Discount in a Shop)
 * 
 * Example:
 * Input: prices = [8,4,6,2,3]
 * Output: [4,2,4,2,3]
 * 
 * Asked in: Amazon, Google, Microsoft
 */

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class FinalPricesSpecialDiscount {

    /**
     * Approach:
     * Monotonic Increasing Stack of Indices:
     * - Maintain stack of item indices waiting for their next smaller/equal price discount.
     * - For each current price at index i:
     *   - While stack is not empty and prices[stack.peek()] >= prices[i]:
     *     - An eligible discount is found! Deduct prices[i] from prices[stack.pop()].
     *   - Push index i onto stack.
     */
    public static int[] finalPrices(int[] prices) {
        int[] result = prices.clone();
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < prices.length; i++) {
            while (!stack.isEmpty() && prices[stack.peek()] >= prices[i]) {
                int discountIdx = stack.pop();
                result[discountIdx] -= prices[i];
            }
            stack.push(i);
        }

        return result;
    }

    public static void main(String[] args) {
        int[] prices = {8, 4, 6, 2, 3};
        System.out.println("Original prices: " + Arrays.toString(prices));
        System.out.println("Discounted:      " + Arrays.toString(finalPrices(prices)) + " (Expected: [4, 2, 4, 2, 3])");

        int[] p2 = {1, 2, 3, 4, 5};
        System.out.println("Ascending prices: " + Arrays.toString(finalPrices(p2)));
    }
}

/*
 * Time Complexity: O(N) - Each index pushed and popped from stack at most once.
 * Space Complexity: O(N) monotonic stack.
 */

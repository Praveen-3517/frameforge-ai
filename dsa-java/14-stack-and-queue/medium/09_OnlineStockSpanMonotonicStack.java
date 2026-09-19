/*
 * Problem Statement:
 * Design an algorithm that collects daily price quotes for some stock and returns the
 * span of that stock's price for the current day.
 * The span of the stock's price today is defined as the maximum number of consecutive days
 * (starting from today and going backward) for which the stock price was less than or equal to today's price.
 * (LeetCode 901: Online Stock Span)
 * 
 * Example:
 * next(100) -> 1
 * next(80)  -> 1
 * next(60)  -> 1
 * next(70)  -> 2
 * next(60)  -> 1
 * next(75)  -> 4
 * next(85)  -> 6
 * 
 * Asked in: Amazon, Google, Microsoft, Adobe
 */

import java.util.ArrayDeque;
import java.util.Deque;

class OnlineStockSpanMonotonicStack {

    static class StockSpanner {
        // Each entry stores [price, span]
        private final Deque<int[]> stack = new ArrayDeque<>();

        public int next(int price) {
            int span = 1;

            while (!stack.isEmpty() && stack.peek()[0] <= price) {
                span += stack.pop()[1];
            }

            stack.push(new int[]{price, span});
            return span;
        }
    }

    public static void main(String[] args) {
        StockSpanner spanner = new StockSpanner();
        int[] prices = {100, 80, 60, 70, 60, 75, 85};

        System.out.println("--- Online Stock Span Testing ---");
        for (int p : prices) {
            System.out.printf("Price: %3d -> Span: %d%n", p, spanner.next(p));
        }
    }
}

/*
 * Time Complexity: Amortized O(1) per next() call (each price pushed and popped at most once).
 * Space Complexity: O(N) monotonic stack storage.
 */

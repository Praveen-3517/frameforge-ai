import java.util.Collections;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * Problem: IPO (LeetCode 502)
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given n projects where the ith project has a pure profit profits[i] and requires a minimum capital capital[i].
 * Initially, you have w capital. When you finish a project, you obtain its pure profit and the profit
 * will be added to your total capital. Pick at most k distinct projects to maximize your final capital.
 * 
 * Approach:
 * Two Heaps / Greedy Selection:
 * 1. Min-Heap `minCapitalHeap` stores projects [capital, profit] sorted by required capital ascending.
 * 2. Max-Heap `maxProfitHeap` stores profits of projects that are currently affordable with available capital w.
 * 3. Repeat k times:
 *    - Transfer all projects from minCapitalHeap whose required capital <= w into maxProfitHeap.
 *    - If maxProfitHeap is empty, we cannot afford any more projects -> break.
 *    - Greedily pick the project with the highest profit: w += maxProfitHeap.poll().
 * 
 * Time Complexity: O(N log N + K log N)
 * Space Complexity: O(N)
 */
class IPOProjectSelectionMaxHeap {

    public static int findMaximizedCapital(int k, int w, int[] profits, int[] capital) {
        int n = profits.length;

        // Min-heap ordered by capital required
        PriorityQueue<int[]> minCapitalHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        for (int i = 0; i < n; i++) {
            minCapitalHeap.offer(new int[]{capital[i], profits[i]});
        }

        // Max-heap ordered by profit
        PriorityQueue<Integer> maxProfitHeap = new PriorityQueue<>(Collections.reverseOrder());

        for (int step = 0; step < k; step++) {
            // Unlock all projects we can afford
            while (!minCapitalHeap.isEmpty() && minCapitalHeap.peek()[0] <= w) {
                maxProfitHeap.offer(minCapitalHeap.poll()[1]);
            }

            if (maxProfitHeap.isEmpty()) {
                break; // Cannot afford any remaining projects
            }

            w += maxProfitHeap.poll();
        }

        return w;
    }

    public static void main(String[] args) {
        int k1 = 2, w1 = 0;
        int[] profits1 = {1, 2, 3};
        int[] capital1 = {0, 1, 1};
        System.out.println("Max Capital 1: " + findMaximizedCapital(k1, w1, profits1, capital1) + " (Expected: 4)");

        int k2 = 3, w2 = 0;
        int[] profits2 = {1, 2, 3};
        int[] capital2 = {0, 1, 2};
        System.out.println("Max Capital 2: " + findMaximizedCapital(k2, w2, profits2, capital2) + " (Expected: 6)");
    }
}

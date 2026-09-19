import java.util.Arrays;

/**
 * Problem: Cheapest Flights Within K Stops (LeetCode 787)
 * Asked in: Amazon, Airbnb, Google, Microsoft
 * 
 * There are n cities connected by flights where flights[i] = [from, to, price].
 * Given src, dst, and k, return the cheapest price from src to dst with at most k stops.
 * If there is no such route, return -1.
 * 
 * Approach:
 * Bellman-Ford with k + 1 iterations:
 * At most k stops means at most k + 1 edges!
 * - Maintain a prices[] array initialized to infinity; prices[src] = 0.
 * - Run k + 1 rounds:
 *   - Create a copy of prices: tmpPrices = Arrays.copyOf(prices, n).
 *   - For each flight [u, v, cost]:
 *     - If prices[u] != inf and prices[u] + cost < tmpPrices[v]:
 *       tmpPrices[v] = prices[u] + cost.
 *   - prices = tmpPrices.
 * 
 * Time Complexity: O(K * E) where E is number of flights.
 * Space Complexity: O(N) for distance arrays.
 */
class CheapestFlightsWithinKStops {

    public static int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        int[] prices = new int[n];
        Arrays.fill(prices, Integer.MAX_VALUE);
        prices[src] = 0;

        for (int i = 0; i <= k; i++) {
            int[] tmpPrices = Arrays.copyOf(prices, n);

            for (int[] flight : flights) {
                int u = flight[0];
                int v = flight[1];
                int cost = flight[2];

                if (prices[u] != Integer.MAX_VALUE && prices[u] + cost < tmpPrices[v]) {
                    tmpPrices[v] = prices[u] + cost;
                }
            }
            prices = tmpPrices;
        }

        return prices[dst] == Integer.MAX_VALUE ? -1 : prices[dst];
    }

    public static void main(String[] args) {
        int n = 4;
        int[][] flights = {
            {0, 1, 100},
            {1, 2, 100},
            {2, 0, 100},
            {1, 3, 600},
            {2, 3, 200}
        };

        System.out.println("Cheapest price (k=1): " + findCheapestPrice(n, flights, 0, 3, 1) + " (Expected: 700)");
        System.out.println("Cheapest price (k=2): " + findCheapestPrice(n, flights, 0, 3, 2) + " (Expected: 400)");
    }
}

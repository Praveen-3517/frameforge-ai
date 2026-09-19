import java.util.PriorityQueue;

/**
 * Problem: Minimum Cost to Connect Sticks (LeetCode 1167)
 * Asked in: Amazon, Google
 * 
 * You have some number of sticks with positive integer lengths given in an array sticks.
 * You can connect any two sticks of lengths x and y into one stick by paying a cost of x + y.
 * You must connect all sticks until there is only one stick remaining.
 * Return the minimum cost of connecting all the given sticks into one stick.
 * 
 * Approach:
 * Greedy Huffman Coding Strategy (Min-Heap):
 * To minimize total cost, always combine the two shortest sticks currently available,
 * as smaller sticks contribute less when accumulated repeatedly.
 * 1. Insert all stick lengths into a Min-Heap.
 * 2. While heap size > 1:
 *    - Pop two smallest sticks x and y.
 *    - Cost to combine = x + y.
 *    - Accumulate totalCost += cost.
 *    - Push combined stick back into Min-Heap.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for Min-Heap.
 */
class MinimumCostToConnectSticks {

    public static int connectSticks(int[] sticks) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int stick : sticks) {
            minHeap.offer(stick);
        }

        int totalCost = 0;

        while (minHeap.size() > 1) {
            int first = minHeap.poll();
            int second = minHeap.poll();
            int combined = first + second;

            totalCost += combined;
            minHeap.offer(combined);
        }

        return totalCost;
    }

    public static void main(String[] args) {
        int[] sticks1 = {2, 4, 3};
        System.out.println("Min cost 1: " + connectSticks(sticks1) + " (Expected: 14)");
        // Combine 2 + 3 = 5 (cost 5), sticks: [4, 5]
        // Combine 4 + 5 = 9 (cost 9), total = 5 + 9 = 14

        int[] sticks2 = {1, 8, 3, 5};
        System.out.println("Min cost 2: " + connectSticks(sticks2) + " (Expected: 30)");
    }
}

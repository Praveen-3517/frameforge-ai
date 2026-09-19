import java.util.Collections;
import java.util.PriorityQueue;

/**
 * Problem: Last Stone Weight (LeetCode 1046)
 * Asked in: Amazon, Google, LinkedIn
 * 
 * You are given an array of integers stones where stones[i] is the weight of the ith stone.
 * We are playing a game with the stones. On each turn, we choose the heaviest two stones
 * with weights x and y with x <= y:
 * - If x == y, both stones are destroyed.
 * - If x != y, stone of weight x is destroyed, and stone of weight y has new weight y - x.
 * Return the weight of the last remaining stone, or 0 if none remain.
 * 
 * Approach:
 * Max-Heap (PriorityQueue with Collections.reverseOrder()):
 * In each round, extract two largest elements. If not equal, insert difference back into heap.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N) for Max-Heap.
 */
class LastStoneWeight {

    public static int lastStoneWeight(int[] stones) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for (int stone : stones) {
            maxHeap.offer(stone);
        }

        while (maxHeap.size() > 1) {
            int y = maxHeap.poll();
            int x = maxHeap.poll();

            if (y > x) {
                maxHeap.offer(y - x);
            }
        }

        return maxHeap.isEmpty() ? 0 : maxHeap.peek();
    }

    public static void main(String[] args) {
        int[] stones1 = {2, 7, 4, 1, 8, 1};
        System.out.println("Last stone: " + lastStoneWeight(stones1) + " (Expected: 1)");

        int[] stones2 = {1};
        System.out.println("Last stone: " + lastStoneWeight(stones2) + " (Expected: 1)");
    }
}

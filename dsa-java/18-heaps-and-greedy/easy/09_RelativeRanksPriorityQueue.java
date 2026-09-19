import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * Problem: Relative Ranks (LeetCode 506)
 * Asked in: Google
 * 
 * You are given an integer array score of size n, where score[i] is the score of the ith athlete.
 * All the scores are guaranteed to be unique.
 * The athletes are placed based on their scores:
 * 1st: "Gold Medal", 2nd: "Silver Medal", 3rd: "Bronze Medal", 4th+: their placement number string ("4", "5", ...).
 * 
 * Approach:
 * Max-Heap with Index Tracking:
 * Push [score, originalIndex] into a Max-Heap ordered by score descending.
 * Pop each athlete, assigning rank according to placement count.
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */
class RelativeRanksPriorityQueue {

    public static String[] findRelativeRanks(int[] score) {
        int n = score.length;
        String[] result = new String[n];

        // Max-heap: [score, originalIndex]
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> Integer.compare(b[0], a[0]));

        for (int i = 0; i < n; i++) {
            maxHeap.offer(new int[]{score[i], i});
        }

        int rank = 1;
        while (!maxHeap.isEmpty()) {
            int[] athlete = maxHeap.poll();
            int idx = athlete[1];

            if (rank == 1) {
                result[idx] = "Gold Medal";
            } else if (rank == 2) {
                result[idx] = "Silver Medal";
            } else if (rank == 3) {
                result[idx] = "Bronze Medal";
            } else {
                result[idx] = String.valueOf(rank);
            }
            rank++;
        }

        return result;
    }

    public static void main(String[] args) {
        int[] score1 = {5, 4, 3, 2, 1};
        System.out.println("Ranks 1: " + Arrays.toString(findRelativeRanks(score1)));
        // Expected: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]

        int[] score2 = {10, 3, 8, 9, 4};
        System.out.println("Ranks 2: " + Arrays.toString(findRelativeRanks(score2)));
        // Expected: ["Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"]
    }
}

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

/**
 * Problem: Jump Game VI — Maximum Score Path with Sliding Window (LeetCode 1696)
 * Category: Sliding Window + Monotonic Deque + DP | Hard
 * Asked in: Amazon, Google
 * 
 * You are given a 0-indexed integer array nums and an integer k.
 * You are initially standing at index 0. In one move, you can jump at most k steps forward
 * without going outside the boundaries of the array. You want to reach the last index.
 * Your score is the sum of all nums[j] for each index j you visited in the path.
 * Return the maximum score you can get.
 * 
 * Approach - DP + Monotonic Deque:
 * dp[i] = maximum score to reach index i.
 * dp[i] = nums[i] + max(dp[j]) for max(0, i-k) <= j < i.
 * Use a monotonic decreasing deque to get the max dp[j] in the window [i-k, i-1] in O(1).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for dp; O(K) for deque.
 */
class JumpGameVIMaxScoreMonotonicDeque {

    public static int maxResult(int[] nums, int k) {
        int n = nums.length;
        int[] dp = new int[n];
        dp[0] = nums[0];

        Deque<Integer> deque = new ArrayDeque<>(); // stores indices; dp[deque] decreasing
        deque.offerLast(0);

        for (int i = 1; i < n; i++) {
            // Remove from front if out of window
            while (!deque.isEmpty() && deque.peekFirst() < i - k) {
                deque.pollFirst();
            }

            dp[i] = nums[i] + dp[deque.peekFirst()];

            // Maintain decreasing dp in deque
            while (!deque.isEmpty() && dp[deque.peekLast()] <= dp[i]) {
                deque.pollLast();
            }

            deque.offerLast(i);
        }

        return dp[n - 1];
    }

    public static void main(String[] args) {
        System.out.println(maxResult(new int[]{1, -1, -2, 4, -7, 3}, 2) + " (Expected: 7)");
        // Path: 0 -> 3 -> 5 = 1 + 4 + 3 = 8? No: indices 0,3,5 = 1+4+3=8, wait 3-0=3>k=2.
        // Actually 0->1->3->5 = 1+(-1)+4+3=7

        System.out.println(maxResult(new int[]{10, -5, -2, 4, 0, 3}, 3) + " (Expected: 17)");
        System.out.println(maxResult(new int[]{1, -5, -20, 4, -1, 3, -6, -3}, 2) + " (Expected: 0)");
    }
}

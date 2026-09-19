import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem: Constrained Subsequence Sum (LeetCode 1425)
 * Asked in: Google, Uber, Amazon
 * 
 * Given an integer array nums and an integer k, return the maximum sum of a non-empty
 * subsequence such that for every two consecutive elements in the subsequence,
 * nums[i] and nums[j] (where i < j), the condition j - i <= k is satisfied.
 * 
 * Approach:
 * DP with Monotonic Decreasing Deque:
 * dp[i] = maximum subsequence sum ending at index i.
 * dp[i] = nums[i] + max(0, max_{i-k <= j < i} dp[j])
 * Using a monotonic double-ended queue, we maintain indices in sliding window [i-k, i-1]
 * with values dp[index] in decreasing order.
 * - If front index < i - k, poll front.
 * - dp[i] = nums[i] + max(0, dp[deque.peekFirst()])
 * - Pop elements from back while dp[deque.peekLast()] <= dp[i].
 * - Push i into deque.
 * 
 * Time Complexity: O(N) where N is array length (each index pushed and popped at most once).
 * Space Complexity: O(N) for DP array and deque.
 */
class ConstrainedSubsequenceSumDeque {

    public static int constrainedSubsetSum(int[] nums, int k) {
        int n = nums.length;
        int[] dp = new int[n];
        Deque<Integer> deque = new ArrayDeque<>();
        int maxSum = nums[0];

        for (int i = 0; i < n; i++) {
            // Remove indices out of range [i - k, i - 1]
            while (!deque.isEmpty() && deque.peekFirst() < i - k) {
                deque.pollFirst();
            }

            int prevMax = deque.isEmpty() ? 0 : Math.max(0, dp[deque.peekFirst()]);
            dp[i] = nums[i] + prevMax;
            maxSum = Math.max(maxSum, dp[i]);

            // Maintain monotonic decreasing order of dp values
            while (!deque.isEmpty() && dp[deque.peekLast()] <= dp[i]) {
                deque.pollLast();
            }
            deque.offerLast(i);
        }

        return maxSum;
    }

    public static void main(String[] args) {
        int[] nums1 = {10, 2, -10, 5, 20};
        int k1 = 2;
        System.out.println("Test 1: " + constrainedSubsetSum(nums1, k1) + " (Expected: 37)");

        int[] nums2 = {-1, -2, -3};
        int k2 = 1;
        System.out.println("Test 2: " + constrainedSubsetSum(nums2, k2) + " (Expected: -1)");

        int[] nums3 = {10, -2, -10, -5, 20};
        int k3 = 2;
        System.out.println("Test 3: " + constrainedSubsetSum(nums3, k3) + " (Expected: 23)");
    }
}

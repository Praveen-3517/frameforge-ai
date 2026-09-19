import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

/**
 * Problem Statement:
 * You are given an array of integers `nums`, and a sliding window of size `k` moving from left to right.
 * You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.
 * Return the max sliding window.
 * (LeetCode 239: Sliding Window Maximum - Hard).
 *
 * Example:
 * nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
 * Window [1  3  -1] -> max 3
 * Window [3  -1 -3] -> max 3
 * Window [-1 -3  5] -> max 5
 * Window [-3  5  3] -> max 5
 * Window [5   3  6] -> max 6
 * Window [3   6  7] -> max 7
 * Output: [3, 3, 5, 5, 6, 7]
 *
 * Asked in: Amazon, Google, Microsoft, Facebook / Meta, Citadel
 *
 * Approach:
 * - Monotonic Decreasing Deque Loop (O(N) Time, O(K) Space):
 *   The double-ended queue (`Deque`) stores INDICES in monotonically decreasing order of values:
 *   - The front of the deque (`peekFirst()`) is always the index of the MAXIMUM element in the window!
 *   - For each index `i`:
 *     1. Window expiration: If `deque.peekFirst() <= i - k`, it has fallen outside the window; pop front.
 *     2. Monotonic maintenance: While `!deque.isEmpty()` and `nums[deque.peekLast()] <= nums[i]`,
 *        the existing elements can never become the maximum as long as `nums[i]` is in the window!
 *        Pop back repeatedly.
 *     3. Push `i` to back of deque.
 *     4. If `i >= k - 1`, record window maximum `nums[deque.peekFirst()]`.
 */
class SlidingWindowMaximumLoop {

    public static int[] maxSlidingWindow(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) return new int[0];

        int n = nums.length;
        int[] result = new int[n - k + 1];
        Deque<Integer> deque = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            // 1. Remove indices outside the current sliding window
            if (!deque.isEmpty() && deque.peekFirst() <= i - k) {
                deque.pollFirst();
            }

            // 2. Remove smaller elements from the back of deque
            while (!deque.isEmpty() && nums[deque.peekLast()] <= nums[i]) {
                deque.pollLast();
            }

            // 3. Add current element index
            deque.offerLast(i);

            // 4. Record the maximum once the initial window of size k is reached
            if (i >= k - 1) {
                result[i - k + 1] = nums[deque.peekFirst()];
            }
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 239: Sliding Window Maximum (Monotonic Deque Loop) ===");

        int[] nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;

        int[] maxes = maxSlidingWindow(nums, k);
        System.out.println("Input Array : " + Arrays.toString(nums));
        System.out.println("Window Size : " + k);
        System.out.println("Window Maxes: " + Arrays.toString(maxes));
    }
}

/*
 * Time Complexity: O(N) - Every element index is pushed to and popped from the deque at most once.
 * Space Complexity: O(K) - Deque holds at most K indices at any time.
 */

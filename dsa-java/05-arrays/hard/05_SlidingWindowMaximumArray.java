import java.util.Arrays;

/**
 * Problem Statement:
 * Given an array of integers `nums`, there is a sliding window of size `k` moving from left to right.
 * Return the max sliding window.
 * Implement an ultra-fast, zero-allocation array-based monotonic deque (no object allocations).
 * (LeetCode 239: Sliding Window Maximum - Hard).
 *
 * Asked in: Amazon, Citadel, Jump Trading, Google
 *
 * Approach:
 * - Low-Latency Primitive Deque Array:
 *   Standard `java.util.ArrayDeque<Integer>` suffers from object boxing (`Integer` autoboxing overhead)
 *   and pointer dereferencing.
 *   In high-frequency trading and competitive programming, simulate the deque using a flat `int[] deque`
 *   with `head` and `tail` index pointers:
 *   - `head`: Front pointer
 *   - `tail`: Back pointer (points to the next insertion slot)
 *   - Size = `tail - head`.
 *   - Push back: `deque[tail++] = val`
 *   - Pop back: `tail--`
 *   - Pop front: `head++`
 *   - Peek front: `deque[head]`
 *   - Peek back: `deque[tail - 1]`
 */
class SlidingWindowMaximumArray {

    public static int[] maxSlidingWindowPrimitive(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) return new int[0];

        int n = nums.length;
        int[] result = new int[n - k + 1];

        // Primitive int array deque: stores indices
        int[] deque = new int[n];
        int head = 0;
        int tail = 0;

        for (int i = 0; i < n; i++) {
            // Evict expired indices outside window [i - k + 1, i]
            if (head < tail && deque[head] <= i - k) {
                head++;
            }

            // Evict smaller values from the back
            while (head < tail && nums[deque[tail - 1]] <= nums[i]) {
                tail--;
            }

            // Push current index
            deque[tail++] = i;

            // Record window maximum
            if (i >= k - 1) {
                result[i - k + 1] = nums[deque[head]];
            }
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 239: Sliding Window Maximum (Primitive Array Deque) ===");

        int[] nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;

        int[] ans = maxSlidingWindowPrimitive(nums, k);
        System.out.println("Array : " + Arrays.toString(nums));
        System.out.println("k     : " + k);
        System.out.println("Maxes : " + Arrays.toString(ans));
    }
}

/*
 * Time Complexity: O(N) - Linear single pass; zero object allocations.
 * Space Complexity: O(N) - Flat primitive array storage for deque.
 */

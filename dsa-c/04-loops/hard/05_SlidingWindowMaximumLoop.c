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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

int* maxSlidingWindow(int* nums, int k) {
        if (nums == NULL || n == 0 || k <= 0) return (int*)malloc((0) * sizeof(int));

        int n = n;
        int* result = (int*)malloc((n - k + 1) * sizeof(int));
        Deque<int> deque = new ArrayDeque<>();

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

    int main(void) {
        printf("=== LeetCode 239: Sliding Window Maximum (Monotonic Deque Loop) ===\n");

        int* nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;

        int* maxes = maxSlidingWindow(nums, k);
        printf("Input Array : " + "[array]\n");
        printf("Window Size : %d\n", k);
        printf("Window Maxes: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) - Every element index is pushed to and popped from the deque at most once.
 * Space Complexity: O(K) - Deque holds at most K indices at any time.
 */

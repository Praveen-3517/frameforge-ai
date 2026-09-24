/*
 * Problem Statement:
 * You are given an array of integers nums, there is a sliding window of size k which is
 * moving from the very left of the array to the very right. You can only see the k numbers
 * in the window. Each time the sliding window moves right by one position.
 * Return the max sliding window.
 * (LeetCode 239: Sliding Window Maximum)
 * 
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 * 
 * Asked in: Amazon, Google, Citadel, Microsoft, ByteDance
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

/**
     * Approach:
     * Monotonic Decreasing Deque:
     * - The Deque stores indices of elements in descending value order.
     * - For each index i:
     *   1. Evict elements outside the current window: deque.peekFirst() <= i - k.
     *   2. Evict smaller elements from tail: while nums[deque.peekLast()] <= nums[i], pollLast().
     *   3. Add index i to deque tail.
     *   4. Once i >= k - 1, the front of the deque is the maximum for the window!
     */
    int* maxSlidingWindow(int* nums, int k) {
        if (nums == NULL || k <= 0) return (int*)malloc((0) * sizeof(int));
        int n = n;
        int* result = (int*)malloc((n - k + 1) * sizeof(int));
        int ri = 0;

        // Stores indices
        Deque<int> deque = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            // 1. Remove indices outside window [i - k + 1, i]
            while (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
                deque.pollFirst();
            }

            // 2. Maintain monotonic decreasing property
            while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
                deque.pollLast();
            }

            // 3. Add current element index
            deque.offerLast(i);

            // 4. Record current max
            if (i >= k - 1) {
                result[ri++] = nums[deque.peekFirst()];
            }
        }

        return result;
    }

    int main(void) {
        int* nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;

        int* maxes = maxSlidingWindow(nums, k);
        printf("Nums: [array], Window k = %d\n", k);
        printf("Sliding Window Maximums: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) - Every element index is pushed and popped from the deque at most once.
 * Space Complexity: O(k) - Deque holds at most k indices.
 */

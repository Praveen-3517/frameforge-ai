/**
 * Problem: Sliding Window Maximum (LeetCode 239)
 * Category: Sliding Window + Monotonic Deque | Hard
 * Asked in: Amazon, Google, Apple, Bloomberg, Microsoft
 * 
 * You are given an array of integers nums, there is a sliding window of size k which is
 * moving from the very left of the array to the very right. You can only see the k numbers
 * in the window. Return the max sliding window.
 * 
 * Approach - Monotonic Decreasing Deque:
 * Maintain a deque of indices such that nums[deque] is always in decreasing order.
 * 1. Before adding right, pop from the back all indices with nums[idx] <= nums[right] (they can never be max).
 * 2. Pop from the front if the front index is out of window (index <= right - k).
 * 3. The front of the deque always holds the index of the current window maximum.
 * 
 * Time Complexity: O(N) — each index pushed and popped at most once.
 * Space Complexity: O(K) for the deque.
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
        int n = n;
        int* result = (int*)malloc((n - k + 1) * sizeof(int));
        Deque<int> deque = new ArrayDeque<>(); // stores indices

        for (int right = 0; right < n; right++) {
            // Remove elements from front that are out of window
            while (!deque.isEmpty() && deque.peekFirst() <= right - k) {
                deque.pollFirst();
            }

            // Remove from back all elements smaller than nums[right] (useless)
            while (!deque.isEmpty() && nums[deque.peekLast()] <= nums[right]) {
                deque.pollLast();
            }

            deque.offerLast(right);

            // Start recording results once first full window is complete
            if (right >= k - 1) {
                result[right - k + 1] = nums[deque.peekFirst()];
            }
        }

        return result;
    }

    int main(void) {
        int* result = maxSlidingWindow((int[]){1, 3, -1, -3, 5, 3, 6, 7}, 3);
        printf("%d\n", java.util."[array]");
        // Expected: [3, 3, 5, 5, 6, 7]

        printf("%d\n", java.util."[array]"));
        // Expected: [1]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

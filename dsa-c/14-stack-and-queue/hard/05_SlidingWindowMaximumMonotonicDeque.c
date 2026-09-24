/*
 * Problem Statement:
 * Implement Sliding Window Maximum using an optimal Monotonic Deque:
 * - Return maximum element in every contiguous sliding window of size k in array nums.
 * - Monotonic decreasing deque stores candidate indices in O(N) time.
 * (LeetCode 239: Sliding Window Maximum)
 * 
 * Example:
 * Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
 * Output: [3,3,5,5,6,7]
 * 
 * Asked in: Amazon, Google, Citadel, Microsoft
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
        if (nums == NULL || k <= 0) return (int*)malloc((0) * sizeof(int));
        int n = n;
        int* result = (int*)malloc((n - k + 1) * sizeof(int));
        int outIdx = 0;

        Deque<int> deque = new ArrayDeque<>(); // Stores indices

        for (int i = 0; i < n; i++) {
            // Evict elements outside the current window
            while (!deque.isEmpty() && deque.peekFirst() < i - k + 1) {
                deque.pollFirst();
            }

            // Maintain monotonic decreasing order of values
            while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) {
                deque.pollLast();
            }

            deque.offerLast(i);

            // Record maximum for window ending at i
            if (i >= k - 1) {
                result[outIdx++] = nums[deque.peekFirst()];
            }
        }

        return result;
    }

    int main(void) {
        int* nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;

        printf("Array: [array], Window: %d\n", k);
        printf("Max Sliding Window: %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(N) - Each index pushed and popped from deque at most once.
 * Space Complexity: O(k) deque holding at most k elements.
 */

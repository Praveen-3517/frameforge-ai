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

int* maxSlidingWindowPrimitive(int* nums, int k) {
        if (nums == NULL || n == 0 || k <= 0) return (int*)malloc((0) * sizeof(int));

        int n = n;
        int* result = (int*)malloc((n - k + 1) * sizeof(int));

        // Primitive int array deque: stores indices
        int* deque = (int*)malloc((n) * sizeof(int));
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

    int main(void) {
        printf("=== LeetCode 239: Sliding Window Maximum (Primitive Array Deque) ===\n");

        int* nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
        int k = 3;

        int* ans = maxSlidingWindowPrimitive(nums, k);
        printf("Array : " + "[array]\n");
        printf("k     : %d\n", k);
        printf("Maxes : " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) - Linear single pass; zero object allocations.
 * Space Complexity: O(N) - Flat primitive array storage for deque.
 */

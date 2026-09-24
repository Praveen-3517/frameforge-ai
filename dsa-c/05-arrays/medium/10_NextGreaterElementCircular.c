/**
 * Problem Statement:
 * Given a circular integer array `nums` (the next element of `nums[n - 1]` is `nums[0]`),
 * return the next greater number for every element in `nums`.
 * If no greater element exists, return -1 for that element.
 * (LeetCode 503: Next Greater Element II).
 *
 * Example:
 * nums = [1, 2, 1] -> Output: [2, -1, 2]
 * nums = [1, 2, 3, 4, 3] -> Output: [2, 3, 4, -1, 4]
 *
 * Asked in: Google, Amazon, Bloomberg, Microsoft
 *
 * Approach:
 * - Monotonic Decreasing Stack over Doubled Virtual Array:
 *   To handle circularity, simulate iterating through the array twice:
 *   Loop index `i` runs from `2 * n - 1` down to 0, using `i % n` for array access.
 *   - The stack maintains indices of elements in strictly decreasing order of values.
 *   - For each index `idx = i % n`:
 *     1. While `!stack.isEmpty()` and `nums[stack.peek()] <= nums[idx]`:
 *        The element at top of stack is <= current element, so it cannot be the "next greater".
 *        Pop it off!
 *     2. If `i < n` (during the actual first pass of the array):
 *        If stack is not empty, `result[i] = nums[stack.peek()]`.
 *     3. Push `idx` onto the stack.
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

int* nextGreaterElements(int* nums) {
        int n = n;
        int* result = (int*)malloc((n) * sizeof(int));
        Arrays.fill(result, -1);

        Deque<int> stack = new ArrayDeque<>(); // Stack of indices

        // Loop through 2 * n - 1 down to 0
        for (int i = 2 * n - 1; i >= 0; i--) {
            int idx = i % n;

            while (!stack.isEmpty() && nums[stack.peek()] <= nums[idx]) {
                stack.pop();
            }

            if (i < n && !stack.isEmpty()) {
                result[i] = nums[stack.peek()];
            }

            stack.push(idx);
        }

        return result;
    }

    int main(void) {
        printf("=== LeetCode 503: Next Greater Element II (Circular Monotonic Stack) ===\n");

        int** testArrays = {
            { 1, 2, 1 },
            { 1, 2, 3, 4, 3 },
            { 5, 4, 3, 2, 1 }
        };

        for (int* arr : testArrays) {
            int* nge = nextGreaterElements(arr);
            printf("Array: %-18s ==> Next Greater: %s\n",
                    "[array]", "[array]");
        }
        return 0;
}

/*
 * Time Complexity: O(N) - 2N iterations, with each index pushed and popped at most once.
 * Space Complexity: O(N) - Monotonic stack holds at most N elements.
 */

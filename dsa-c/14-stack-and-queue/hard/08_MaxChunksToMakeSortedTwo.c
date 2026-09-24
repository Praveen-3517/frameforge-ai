/**
 * Problem: Max Chunks To Make Sorted II (LeetCode 768)
 * Asked in: Google, Amazon, Microsoft
 * 
 * Given an integer array arr (which may contain duplicates), split arr into the
 * maximum number of chunks such that sorting each chunk individually and
 * concatenating the results produces a sorted array.
 * 
 * Approach:
 * Monotonic Stack of Chunk Maximums:
 * - Each element in the stack represents the maximum value in that chunk.
 * - For each number num in arr:
 *     - If stack is empty or num >= stack.peek(), num can start a new chunk -> push(num).
 *     - If num < stack.peek(), num must merge with previous chunks whose max > num.
 *       Pop the current chunk's max as curMax, then keep popping any chunk max > num.
 *       Finally, push curMax back into the stack.
 * - The number of chunks is stack.size().
 * 
 * Time Complexity: O(N) where each element is pushed and popped at most once.
 * Space Complexity: O(N) for stack storage.
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

int maxChunksToSorted(int* arr) {
        Deque<int> stack = new ArrayDeque<>();

        for (size_t _idx = 0; _idx < sizeof(arr)/sizeof(arr[0]); _idx++) {
        int num = arr[_idx];
            if (stack.isEmpty() || num >= stack.peek()) {
                stack.push(num);
            } else {
                int curMax = stack.pop();
                while (!stack.isEmpty() && stack.peek() > num) {
                    stack.pop();
                }
                stack.push(curMax);
            }
        }

        return stack.size();
    }

    int main(void) {
        int* arr1 = {2, 1, 3, 4, 4};
        printf("Test 1: " + maxChunksToSorted(arr1) + " (Expected: 4)\n");

        int* arr2 = {5, 4, 3, 2, 1};
        printf("Test 2: " + maxChunksToSorted(arr2) + " (Expected: 1)\n");

        int* arr3 = {1, 0, 1, 3, 2};
        printf("Test 3: " + maxChunksToSorted(arr3) + " (Expected: 3)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/*
 * Problem Statement:
 * Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
 * return the next greater number for every element in nums.
 * The next greater number of a number x is the first greater number to its traversing-order
 * next in the array, which means you could search circularly to find its next greater number.
 * If it doesn't exist, return -1 for this number.
 * (LeetCode 503: Next Greater Element II)
 * 
 * Example:
 * Input: nums = [1,2,1]
 * Output: [2,-1,2]
 * 
 * Asked in: Amazon, Google, Microsoft, Bloomberg
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
     * Monotonic Decreasing Stack over 2N Circular Range:
     * - Loop from 2N - 1 down to 0 using modulo indexing (i % n).
     * - While stack is not empty and stack.peek() <= nums[i % n], pop stack.
     * - If i < n, result[i] is stack.peek() (or -1 if stack is empty).
     * - Push nums[i % n] onto stack.
     */
    int* nextGreaterElements(int* nums) {
        int n = n;
        int* result = (int*)malloc((n) * sizeof(int));
        Arrays.fill(result, -1);

        Deque<int> stack = new ArrayDeque<>();

        for (int i = 2 * n - 1; i >= 0; i--) {
            int val = nums[i % n];
            while (!stack.isEmpty() && stack.peek() <= val) {
                stack.pop();
            }

            if (i < n) {
                if (!stack.isEmpty()) {
                    result[i] = stack.peek();
                }
            }

            stack.push(val);
        }

        return result;
    }

    int main(void) {
        int* nums1 = {1, 2, 1};
        printf("Nums: [1, 2, 1]\n");
        printf("Next Greater Elements: %d\n", "[array]"));

        int* nums2 = {1, 2, 3, 4, 3};
        printf("\nNums: [1, 2, 3, 4, 3]\n");
        printf("Next Greater Elements: %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(N) - Each element is pushed and popped at most twice across 2N loop.
 * Space Complexity: O(N) monotonic stack storage.
 */

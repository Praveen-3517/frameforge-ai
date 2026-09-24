/**
 * Problem Statement:
 * Given an integer array `nums`, return an array `answer` such that `answer[i]` is equal to
 * the product of all the elements of `nums` except `nums[i]`.
 * Requirements:
 *   - You must NOT use the division operator.
 *   - The algorithm must run in O(N) time.
 *   - Auxiliary space must be O(1) (the output array does not count as extra space).
 * (LeetCode 238: Product of Array Except Self).
 *
 * Example:
 * nums = [1, 2, 3, 4] -> Output: [24, 12, 8, 6]
 * nums = [-1, 1, 0, -3, 3] -> Output: [0, 0, 9, 0, 0]
 *
 * Asked in: Amazon, Apple, Facebook / Meta, Microsoft, Google
 *
 * Approach:
 * - Prefix & Suffix Product Accumulation (O(N) Time, O(1) Auxiliary Space):
 *   Every `answer[i]` is equal to:
 *   `prefixProduct(elements to the left of i) * suffixProduct(elements to the right of i)`.
 *   - Pass 1 (Left-to-Right):
 *     Store in `answer[i]` the product of all elements to the left of `i`:
 *     `answer[0] = 1;`
 *     `answer[i] = answer[i - 1] * nums[i - 1];`
 *   - Pass 2 (Right-to-Left):
 *     Maintain a single running `suffixProduct` variable (initially 1).
 *     `answer[i] = answer[i] * suffixProduct;`
 *     `suffixProduct *= nums[i];`
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

int* productExceptSelf(int* nums) {
        int n = n;
        int* answer = (int*)malloc((n) * sizeof(int));

        // Pass 1: Build prefix products directly into answer array
        answer[0] = 1;
        for (int i = 1; i < n; i++) {
            answer[i] = answer[i - 1] * nums[i - 1];
        }

        // Pass 2: Multiply by suffix products backwards
        int suffixProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            answer[i] *= suffixProduct;
            suffixProduct *= nums[i];
        }

        return answer;
    }

    int main(void) {
        printf("=== LeetCode 238: Product of Array Except Self (Division-Free) ===\n");

        int** testArrays = {
            { 1, 2, 3, 4 },
            { -1, 1, 0, -3, 3 },
            { 2, 3, 5, 0, 0 }
        };

        for (int* arr : testArrays) {
            int* prod = productExceptSelf(arr);
            printf("Array: %-18s ==> Product Except Self: %s\n",
                    "[array]", "[array]");
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Two passes over the array of size N.
 * Space Complexity: O(1) - Constant auxiliary memory (output array excluded).
 */

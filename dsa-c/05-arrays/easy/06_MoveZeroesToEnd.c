/**
 * Problem Statement:
 * Given an integer array `nums`, move all 0's to the end of it while maintaining the relative
 * order of the non-zero elements.
 * You must do this in-place without making a copy of the array.
 * (LeetCode 283: Move Zeroes).
 *
 * Example:
 * nums = [0, 1, 0, 3, 12] -> Output: [1, 3, 12, 0, 0]
 *
 * Asked in: Facebook / Meta, Bloomberg, Amazon, Apple, Microsoft
 *
 * Approach:
 * - Snowball / Two-Pointer Swap In-Place:
 *   - Pointer `insertPos` tracks the destination for the next non-zero element.
 *   - For each element `nums[i]`:
 *     If `nums[i] != 0`:
 *       If `i != insertPos`:
 *         Swap `nums[insertPos]` and `nums[i]`.
 *       `insertPos++;`
 *   - This simultaneously shifts non-zeros forward and rolls zeroes backward in a single pass!
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

void moveZeroes(int* nums) {
        if (nums == NULL || n <= 1) return;

        int insertPos = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                if (i != insertPos) {
                    int temp = nums[insertPos];
                    nums[insertPos] = nums[i];
                    nums[i] = temp;
                }
                insertPos++;
            }
        }
    }

    int main(void) {
        printf("=== LeetCode 283: Move Zeroes to End In-Place ===\n");

        int** testCases = {
            { 0, 1, 0, 3, 12 },
            { 0, 0, 1 },
            { 1, 2, 3 },
            { 0, 0, 0 }
        };

        for (int* arr : testCases) {
            int* original = arr.clone();
            moveZeroes(arr);
            printf("Original: %-18s ==> Result: %s\n",
                    "[array]", "[array]");
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through the array.
 * Space Complexity: O(1) - Constant auxiliary space.
 */

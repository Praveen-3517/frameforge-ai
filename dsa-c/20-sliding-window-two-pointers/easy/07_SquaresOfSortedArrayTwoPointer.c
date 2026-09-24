/**
 * Problem: Squares of a Sorted Array (LeetCode 977)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Amazon, Microsoft, Google
 * 
 * Given an integer array sorted in non-decreasing order, return an array of the
 * squares of each number sorted in non-decreasing order.
 * 
 * Approach - Two-End Merge:
 * The largest square is at either the leftmost (most negative) or rightmost element.
 * Use two pointers at each end. Compare their absolute values, insert the larger
 * square at the end of the result array.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the result array.
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

int* sortedSquares(int* nums) {
        int n = n;
        int* result = (int*)malloc((n) * sizeof(int));
        int left = 0;
        int right = n - 1;
        int pos = n - 1; // fill from the end

        while (left <= right) {
            int leftSq = nums[left] * nums[left];
            int rightSq = nums[right] * nums[right];

            if (leftSq > rightSq) {
                result[pos--] = leftSq;
                left++;
            } else {
                result[pos--] = rightSq;
                right--;
            }
        }

        return result;
    }

    int main(void) {
        printf("%d\n", "[array]"));
        // Expected: [0, 1, 9, 16, 100]
        printf("%d\n", "[array]"));
        // Expected: [4, 9, 9, 49, 121]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

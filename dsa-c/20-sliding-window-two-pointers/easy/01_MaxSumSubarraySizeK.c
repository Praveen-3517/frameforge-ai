/**
 * Problem: Maximum Sum Subarray of Size K
 * Category: Fixed-Size Sliding Window | Easy
 * Asked in: Amazon, Google, Microsoft
 * 
 * Given an array of positive integers and a positive integer K,
 * find the maximum sum of any contiguous subarray of size K.
 * 
 * Approach - Fixed Sliding Window:
 * 1. Compute sum of first K elements.
 * 2. Slide the window right: add the new element, remove the leftmost element.
 * 3. Track maximum at each window position.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

int maxSumSubarray(int* arr, int k) {
        if (n < k) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        int windowSum = 0;
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }

        int maxSum = windowSum;
        for (int i = k; i < n; i++) {
            windowSum += arr[i] - arr[i - k]; // slide: add new, remove old
            maxSum = MAX(maxSum, windowSum);
        }

        return maxSum;
    }

    int main(void) {
        int* arr1 = {2, 3, 4, 1, 5};
        printf("Max sum k=3: " + maxSumSubarray(arr1, 3) + " (Expected: 10)\n");
        // Window [3,4,1]=8, [4,1,5]=10 -> max=10

        int* arr2 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
        printf("Max sum k=4: " + maxSumSubarray(arr2, 4) + " (Expected: 39)\n");
        // Window [2,10,23,3] = 38? Actually [10,23,3,1]=37, let's see: [2,10,23,3]=38, [10,23,3,1]=37
        // Max should be 39 from [4,2,10,23]=39
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

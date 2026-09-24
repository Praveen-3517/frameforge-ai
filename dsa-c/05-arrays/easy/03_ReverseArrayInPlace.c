/**
 * Problem Statement:
 * Given an array `arr`, reverse the array elements in-place without using extra array memory.
 * Also implement a general range reversal helper: `reverseRange(arr, start, end)` which serves
 * as a crucial sub-routine in array rotation and permutation algorithms.
 *
 * Asked in: Infosys, Wipro, TCS, Cognizant
 *
 * Approach:
 * - Two-Pointer In-Place Reversal:
 *   Initialize `left = 0` and `right = arr.length - 1`.
 *   While `left < right`:
 *     Swap `arr[left]` and `arr[right]`.
 *     Advance `left++`, decrement `right--`.
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

void reverse(int* arr) {
        if (arr == NULL || n <= 1) return;
        reverseRange(arr, 0, n - 1);
    }

    void reverseRange(int* arr, int start, int end) {
        while (start < end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }

    int main(void) {
        printf("=== In-Place Array Reversal (Two Pointers) ===\n");

        int* arr1 = { 1, 2, 3, 4, 5, 6 };
        printf("Original: " + "[array]\n");
        reverse(arr1);
        printf("Reversed: " + "[array]\n");

        int* arr2 = { 10, 20, 30, 40, 50, 60, 70 };
        printf("\nOriginal: " + "[array]\n");
        reverseRange(arr2, 2, 5); // Reverse sub-segment [30, 40, 50, 60]
        printf("Range [2..5] Reversed: " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) - N/2 swaps.
 * Space Complexity: O(1) - Constant auxiliary space.
 */

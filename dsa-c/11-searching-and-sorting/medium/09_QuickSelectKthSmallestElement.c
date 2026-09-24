/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the k-th smallest element in the array
 * using the QuickSelect algorithm.
 * Note: QuickSelect finds the k-th element in expected O(N) time without sorting the whole array.
 * 
 * Example:
 * Input: nums = [7, 10, 4, 3, 20, 15], k = 3
 * Output: 7 (Sorted: [3, 4, 7, 10, 15, 20]; 3rd smallest is 7)
 * 
 * Asked in: Google, Amazon, Facebook/Meta, Microsoft
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

static const Random rand = new Random();

    int quickSelect(int* nums, int k) {
        // k is 1-based, so target index is k - 1
        return select(nums, 0, n - 1, k - 1);
    }

    static int select(int* nums, int low, int high, int targetIdx) {
        if (low == high) return nums[low];

        // Randomized pivot to avoid O(N^2) worst case on pre-sorted arrays
        int randomPivotIdx = low + rand.nextInt(high - low + 1);
        swap(nums, randomPivotIdx, high);

        int pivotIndex = partition(nums, low, high);

        if (pivotIndex == targetIdx) {
            return nums[pivotIndex];
        } else if (pivotIndex < targetIdx) {
            return select(nums, pivotIndex + 1, high, targetIdx);
        } else {
            return select(nums, low, pivotIndex - 1, targetIdx);
        }
    }

    static int partition(int* nums, int low, int high) {
        int pivot = nums[high];
        int i = low;

        for (int j = low; j < high; j++) {
            if (nums[j] <= pivot) {
                swap(nums, i, j);
                i++;
            }
        }
        swap(nums, i, high);
        return i;
    }

    static void swap(int* nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    int main(void) {
        int* nums = {7, 10, 4, 3, 20, 15};
        int k = 3;

        printf("Array: " + "[array]\n");
        printf("%d-th smallest element: %d\n", k, quickSelect(nums, k));

        int* nums2 = {12, 3, 5, 7, 19};
        printf("\nArray: " + "[array]\n");
        printf("2nd smallest element: %d\n", quickSelect(nums2, 2));
        return 0;
}

/*
 * Time Complexity: Average: O(N); Worst Case: O(N^2) (mitigated by randomized pivot).
 * Space Complexity: O(log N) recursion stack.
 */

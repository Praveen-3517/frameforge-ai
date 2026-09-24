/*
 * Problem Statement:
 * Given an integer array nums, return an integer array counts where counts[i] is
 * the number of smaller elements to the right of nums[i].
 * (LeetCode 315: Count of Smaller Numbers After Self)
 * 
 * Example:
 * Input: nums = [5,2,6,1]
 * Output: [2,1,1,0]
 * Explanation:
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 * 
 * Asked in: Google, Amazon, Microsoft, Apple
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

static class Element {
        int val;
        int originalIndex;

        Element(int val, int originalIndex) {
            this.val = val;
            this.originalIndex = originalIndex;
        }
    }

    /**
     * Approach:
     * Modified Merge Sort tracking element original indices:
     * While merging left half and right half:
     * If element from right half is smaller than left half element, rightCounter increases.
     * When element from left half is placed into merged array, its answer increases
     * by rightCounter (all elements from right half placed before it were smaller).
     */
    int* countSmaller(int* nums) {
        int n = n;
        int* counts = (int*)malloc((n) * sizeof(int));
        Element[] elements = new Element[n];

        for (int i = 0; i < n; i++) {
            elements[i] = new Element(nums[i], i);
        }

        Element[] temp = new Element[n];
        mergeSort(elements, 0, n - 1, temp, counts);

        int* result = new ArrayList<>();
        for (int c : counts) result.add(c);
        return result;
    }

    static void mergeSort(Element[] arr, int low, int high, Element[] temp, int* counts) {
        if (low >= high) return;

        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid, temp, counts);
        mergeSort(arr, mid + 1, high, temp, counts);

        int i = low;
        int j = mid + 1;
        int k = low;
        int rightSmallerCount = 0;

        while (i <= mid && j <= high) {
            if (arr[j].val < arr[i].val) {
                temp[k++] = arr[j++];
                rightSmallerCount++;
            } else {
                counts[arr[i].originalIndex] += rightSmallerCount;
                temp[k++] = arr[i++];
            }
        }

        while (i <= mid) {
            counts[arr[i].originalIndex] += rightSmallerCount;
            temp[k++] = arr[i++];
        }

        while (j <= high) {
            temp[k++] = arr[j++];
        }

        for (int idx = low; idx <= high; idx++) {
            arr[idx] = temp[idx];
        }
    }

    int main(void) {
        int* nums = {5, 2, 6, 1};

        printf("Array: " + "[array]\n");
        printf("Count smaller after self: " + countSmaller(nums) + " (Expected: [2, 1, 1, 0])\n");

        int* nums2 = {-1, -1};
        printf("\nArray: " + "[array]\n");
        printf("Count smaller after self: " + countSmaller(nums2) + " (Expected: [0, 0])\n");
        return 0;
}

/*
 * Time Complexity: O(N log N) - Divide and conquer Merge Sort.
 * Space Complexity: O(N) temporary element array and counts.
 */

/*
 * Problem Statement:
 * Given an array nums with n objects colored red, white, or blue, sort them in-place
 * so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
 * We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
 * You must solve this problem without using the library's sort function, in one pass with O(1) space.
 * (LeetCode 75: Sort Colors / Dutch National Flag Problem by Edsger Dijkstra)
 * 
 * Example:
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 * 
 * Asked in: Microsoft, Amazon, Facebook/Meta, Apple, Google
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
     * Three-Pointer Dutch National Flag Partitioning:
     * Pointers:
     * - low: boundary where elements < low are 0s.
     * - mid: current element being examined.
     * - high: boundary where elements > high are 2s.
     * 
     * If nums[mid] == 0: swap(nums, low, mid); low++; mid++;
     * If nums[mid] == 1: mid++;
     * If nums[mid] == 2: swap(nums, mid, high); high--; (mid does NOT advance because swapped element is unexamined!)
     */
    void sortColors(int* nums) {
        int low = 0;
        int mid = 0;
        int high = n - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums, low, mid);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else { // nums[mid] == 2
                swap(nums, mid, high);
                high--;
            }
        }
    }

    static void swap(int* nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    int main(void) {
        int* nums = {2, 0, 2, 1, 1, 0};

        printf("Original: " + "[array]\n");
        sortColors(nums);
        printf("Sorted:   " + "[array]\n");
        return 0;
}

/*
 * Time Complexity: O(N) single pass through the array.
 * Space Complexity: O(1) strictly in-place.
 */

/**
 * Problem: 3Sum (LeetCode 15)
 * Category: Two Pointers | Medium
 * Asked in: Amazon, Facebook, Google, Apple, Microsoft, Bloomberg
 * 
 * Given an integer array nums, return all triplets [nums[i], nums[j], nums[k]] such that
 * i != j, i != k, j != k, and nums[i] + nums[j] + nums[k] == 0.
 * The solution set must not contain duplicate triplets.
 * 
 * Approach - Sort + Two Pointer for each pivot:
 * 1. Sort the array.
 * 2. For each index i (pivot), use two pointers left=i+1, right=n-1 to find pairs
 *    summing to -nums[i].
 * 3. Skip duplicate pivots and duplicate pointer values to avoid redundant triplets.
 * 
 * Time Complexity: O(N²)
 * Space Complexity: O(1) auxiliary (excluding output list).
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

int*> threeSum(int* nums) {
        Arrays.sort(nums);
        int*> result = new ArrayList<>();

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicate pivot

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    while (left < right && nums[left] == nums[left + 1]) left++;   // skip dup
                    while (left < right && nums[right] == nums[right - 1]) right--; // skip dup
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }

    int main(void) {
        printf("%d\n", threeSum((int[]){-1, 0, 1, 2, -1, -4}));
        // Expected: [[-1,-1,2],[-1,0,1]]
        printf("%d\n", threeSum((int[]){0, 1, 1}));
        // Expected: []
        printf("%d\n", threeSum((int[]){0, 0, 0}));
        // Expected: [[0,0,0]]
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

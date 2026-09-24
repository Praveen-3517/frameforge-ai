/*
 * Problem Statement:
 * Given an integer array nums, return the maximum difference between two successive
 * elements in its sorted form. If the array contains less than two elements, return 0.
 * You must write an algorithm that runs in linear time and uses linear extra space.
 * (LeetCode 164: Maximum Gap)
 * 
 * Example:
 * Input: nums = [3,6,9,1]
 * Output: 3 (Sorted: [1,3,6,9]; max difference between successive elements is 3)
 * 
 * Asked in: Amazon, Google, Microsoft, Adobe
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
     * Bucket Sort using Pigeonhole Principle:
     * - Let min and max be the extreme values of the array.
     * - The average gap between N elements across range [min, max] is:
     *   gap = ceil((max - min) / (N - 1)).
     * - The maximum gap MUST be >= this average gap!
     * - By creating buckets of size 'gap', the maximum gap CANNOT occur between two
     *   elements inside the SAME bucket!
     * - Thus, we only need to store min and max for each bucket, and compare each
     *   bucket's min with the previous non-empty bucket's max.
     */
    int maximumGap(int* nums) {
        if (nums == NULL || n < 2) return 0;

        int n = n;
        int min = nums[0];
        int max = nums[0];

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int x = nums[_idx];
            min = MIN(min, x);
            max = MAX(max, x);
        }

        if (min == max) return 0;

        // Bucket size and count
        int bucketSize = MAX(1, (max - min) / (n - 1));
        int bucketCount = (max - min) / bucketSize + 1;

        int* bucketMin = (int*)malloc((bucketCount) * sizeof(int));
        int* bucketMax = (int*)malloc((bucketCount) * sizeof(int));
        Arrays.fill(bucketMin, INT_MAX);
        Arrays.fill(bucketMax, INT_MIN);

        // Put numbers into buckets
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int x = nums[_idx];
            int idx = (x - min) / bucketSize;
            bucketMin[idx] = MIN(bucketMin[idx], x);
            bucketMax[idx] = MAX(bucketMax[idx], x);
        }

        // Calculate max gap between consecutive non-empty buckets
        int maxGap = 0;
        int prevMax = min;

        for (int i = 0; i < bucketCount; i++) {
            if (bucketMin[i] == INT_MAX) continue; // Empty bucket

            maxGap = MAX(maxGap, bucketMin[i] - prevMax);
            prevMax = bucketMax[i];
        }

        return maxGap;
    }

    int main(void) {
        int* nums = {3, 6, 9, 1};

        printf("Array: " + "[array]\n");
        printf("Maximum Gap: " + maximumGap(nums) + " (Expected: 3)\n");

        int* nums2 = {10};
        printf("Single element array maximum gap: %d\n", maximumGap(nums2));
        return 0;
}

/*
 * Time Complexity: O(N) linear time bucket assignment and pass.
 * Space Complexity: O(N) bucket arrays.
 */

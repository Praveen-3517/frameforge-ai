/*
 * Problem Statement:
 * Given an array of integers nums and an integer k, return the total number of subarrays
 * whose sum equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 * 
 * Example 1:
 * Input: nums = [1, 1, 1], k = 2
 * Output: 2
 * 
 * Example 2:
 * Input: nums = [1, 2, 3], k = 3
 * Output: 2 ([1,2] and [3])
 * 
 * Asked in: Facebook/Meta, Amazon, Google, Microsoft, ByteDance
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
     * Prefix Sum with HashMap:
     * If prefixSum[j] - prefixSum[i] = k, then the subarray between i and j sums to k.
     * Rearranged: prefixSum[i] = prefixSum[j] - k.
     * Store counts of prefix sums in a HashMap.
     * Initialize map with (0 -> 1) to account for subarrays starting at index 0.
     */
    int subarraySum(int* nums, int k) {
        int count = 0;
        int currentSum = 0;
        Map<int, int> prefixMap = new HashMap<>();
        prefixMap.put(0, 1);

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            currentSum += num;
            if (prefixMap.containsKey(currentSum - k)) {
                count += prefixMap.get(currentSum - k);
            }
            prefixMap.merge(currentSum, 1, int::sum);
        }

        return count;
    }

    int main(void) {
        int* nums1 = {1, 1, 1};
        int k1 = 2;
        printf("nums: [1, 1, 1], k = 2 -> Subarrays: %d\n", subarraySum(nums1, k1));

        int* nums2 = {1, -1, 0};
        int k2 = 0;
        printf("nums: [1, -1, 0], k = 0 -> Subarrays: %d\n", subarraySum(nums2, k2));

        int* nums3 = {3, 4, 7, 2, -3, 1, 4, 2};
        int k3 = 7;
        printf("nums: [3, 4, 7, 2, -3, 1, 4, 2], k = 7 -> Subarrays: %d\n", subarraySum(nums3, k3));
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through the array.
 * Space Complexity: O(N) - Storing prefix sums in HashMap.
 */

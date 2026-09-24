/*
 * Problem Statement:
 * Given an array of integers nums and an integer target, return indices of the two
 * numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use
 * the same element twice. You can return the answer in any order.
 * 
 * Example:
 * Input: nums = [2, 7, 11, 15], target = 9
 * Output: [0, 1] (nums[0] + nums[1] == 9)
 * 
 * Asked in: Amazon, Google, Apple, Microsoft, Meta
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
     * One-Pass Hash Table:
     * While iterating, check if the complement (target - nums[i]) already exists in the map.
     * If yes, return the pair of indices.
     * If no, insert nums[i] -> i into map.
     */
    int* twoSum(int* nums, int target) {
        Map<int, int> map = new HashMap<>();

        for (int i = 0; i < n; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return (int[]){ map.get(complement), i };
            }
            map.put(nums[i], i);
        }

        fprintf(stderr, "Exception: invalid argument
"); return 0;
    }

    int main(void) {
        int* nums = {2, 7, 11, 15};
        int target = 9;

        int* indices = twoSum(nums, target);
        printf("Nums: [array], Target: %d\n", target);
        printf("Solution Indices: " + "[array]\n");
        printf("Verification: nums[%d] (%d) + nums[%d] (%d) = %d\n",
                indices[0], nums[indices[0]], indices[1], nums[indices[1]], target);
        return 0;
}

/*
 * Time Complexity: O(N) - Single pass through the array with O(1) hash lookups.
 * Space Complexity: O(N) - Map stores up to N elements.
 */

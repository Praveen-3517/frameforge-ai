/**
 * Problem: Split Array into Consecutive Subsequences (LeetCode 659)
 * Asked in: Google, Amazon
 * 
 * You are given an integer array nums that is sorted in non-decreasing order.
 * Determine if it is possible to split nums into one or more subsequences such
 * that both of the following conditions are true:
 * 1. Each subsequence is a consecutive increasing sequence.
 * 2. Each subsequence has a length of 3 or more.
 * 
 * Approach:
 * Greedy Choice with Frequency & Need Maps:
 * - countMap: frequency of each remaining number.
 * - needMap: number of existing valid sequences that need num to extend them.
 * For each num in nums:
 * - If countMap[num] == 0, already consumed -> skip.
 * - If needMap[num] > 0:
 *   - Greedily append num to existing sequence! needMap[num]--, needMap[num + 1]++.
 * - Else if countMap[num + 1] > 0 and countMap[num + 2] > 0:
 *   - Form a new sequence of length 3: [num, num+1, num+2].
 *   - needMap[num + 3]++.
 * - Otherwise: Cannot place num -> return false.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
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

bool isPossible(int* nums) {
        Map<int, int> countMap = new HashMap<>();
        Map<int, int> needMap = new HashMap<>();

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            countMap.put(num, countMap.getOrDefault(num, 0) + 1);
        }

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if (countMap.get(num) == 0) continue;

            if (needMap.getOrDefault(num, 0) > 0) {
                // Greedily append to an existing sequence
                needMap.put(num, needMap.get(num) - 1);
                needMap.put(num + 1, needMap.getOrDefault(num + 1, 0) + 1);
            } else if (countMap.getOrDefault(num + 1, 0) > 0 && countMap.getOrDefault(num + 2, 0) > 0) {
                // Form a new sequence of length 3
                countMap.put(num + 1, countMap.get(num + 1) - 1);
                countMap.put(num + 2, countMap.get(num + 2) - 1);
                needMap.put(num + 3, needMap.getOrDefault(num + 3, 0) + 1);
            } else {
                return false;
            }

            countMap.put(num, countMap.get(num) - 1);
        }

        return true;
    }

    int main(void) {
        int* nums1 = {1, 2, 3, 3, 4, 5};
        printf("Possible 1: " + isPossible(nums1) + " (Expected: true)\n"); // [1,2,3], [3,4,5]

        int* nums2 = {1, 2, 3, 3, 4, 4, 5, 5};
        printf("Possible 2: " + isPossible(nums2) + " (Expected: true)\n");

        int* nums3 = {1, 2, 3, 4, 4, 5};
        printf("Possible 3: " + isPossible(nums3) + " (Expected: false)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

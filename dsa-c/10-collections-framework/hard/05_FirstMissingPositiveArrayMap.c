/*
 * Problem Statement:
 * Given an unsorted integer array nums, return the smallest missing positive integer.
 * You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.
 * (LeetCode 41: First Missing Positive)
 * 
 * Example 1:
 * Input: nums = [1, 2, 0]
 * Output: 3
 * 
 * Example 2:
 * Input: nums = [3, 4, -1, 1]
 * Output: 2
 * 
 * Asked in: Amazon, Google, Microsoft, Facebook/Meta
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
     * Approach 1: HashSet Lookup (O(N) time, O(N) space)
     */
    int firstMissingPositiveSet(int* nums) {
        Set<int> set = new HashSet<>();
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int x = nums[_idx];
            if (x > 0) set.add(x);
        }

        int target = 1;
        while (set.contains(target)) {
            target++;
        }
        return target;
    }

    /**
     * Approach 2: In-place Index Mapping / Cycle Placement (O(N) time, O(1) space)
     * Place each number x at its correct index (x - 1) if 1 <= x <= n.
     */
    int firstMissingPositiveOptimal(int* nums) {
        int n = n;

        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                // Swap nums[i] to its target index nums[i] - 1
                int targetIdx = nums[i] - 1;
                int temp = nums[i];
                nums[i] = nums[targetIdx];
                nums[targetIdx] = temp;
            }
        }

        // Find first slot where nums[i] != i + 1
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1;
    }

    int main(void) {
        int** tests = {
            {1, 2, 0},
            {3, 4, -1, 1},
            {7, 8, 9, 11, 12},
            {1}
        };

        printf("--- First Missing Positive int ---\n");
        for (int* t : tests) {
            int resSet = firstMissingPositiveSet(t);
            int resOpt = firstMissingPositiveOptimal(t.clone());
            printf("Array: %-20s -> Missing: %d (Optimal: %d)\n",
                    "[array]", resSet, resOpt);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Each number swapped into correct spot at most once.
 * Space Complexity: Optimal: O(1) auxiliary space.
 */

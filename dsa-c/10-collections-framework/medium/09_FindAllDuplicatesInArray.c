/*
 * Problem Statement:
 * Given an integer array nums of length n where all the integers of nums are in the
 * range [1, n] and each integer appears once or twice, return an array of all the
 * integers that appears twice.
 * Show:
 * 1. HashSet approach (O(N) time, O(N) space).
 * 2. In-place index negation approach (O(N) time, O(1) auxiliary space).
 * 
 * Example:
 * Input: nums = [4,3,2,7,8,2,3,1]
 * Output: [2, 3]
 * 
 * Asked in: Amazon, Microsoft, Pocket Gems, Facebook/Meta
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

// Approach 1: HashSet Detection
    int* findDuplicatesHashSet(int* nums) {
        int* result = new ArrayList<>();
        Set<int> seen = new HashSet<>();

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if (seen.contains(num)) {
                result.add(num);
            } else {
                seen.add(num);
            }
        }
        return result;
    }

    // Approach 2: In-place Index Negation (O(1) extra space)
    int* findDuplicatesInPlace(int* nums) {
        int* result = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int val = abs(nums[i]);
            int index = val - 1;

            if (nums[index] < 0) {
                // Already visited, so val is a duplicate!
                result.add(val);
            } else {
                // Mark as visited by negating
                nums[index] = -nums[index];
            }
        }

        // Restore original array values
        for (int i = 0; i < n; i++) {
            nums[i] = abs(nums[i]);
        }

        return result;
    }

    int main(void) {
        int* nums = {4, 3, 2, 7, 8, 2, 3, 1};

        printf("--- Find All Duplicates in Array ---\n");
        printf("HashSet approach:  %d\n", findDuplicatesHashSet(nums));
        printf("In-place approach: %d\n", findDuplicatesInPlace(nums));
        return 0;
}

/*
 * Time Complexity: O(N) linear scan for both methods.
 * Space Complexity: HashSet: O(N), In-place: O(1) auxiliary space.
 */

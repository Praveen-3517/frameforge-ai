/**
 * Problem: Maximum XOR of Two Numbers in an Array (LeetCode 421)
 * Asked in: Google, Amazon, Facebook
 * 
 * Given an integer array nums, return the maximum result of nums[i] XOR nums[j],
 * where 0 <= i <= j < n.
 * 
 * Approach - Greedy Bit-by-Bit with Prefix Set:
 * From the most significant bit to the least:
 * 1. Compute a prefix of all numbers using the current bit mask.
 * 2. Assume we can achieve max XOR by setting this bit to 1 (candidate = ans | (1 << bit)).
 * 3. For the candidate to be achievable, there must exist two prefixes a, b in the prefix set
 *    such that a ^ b == candidate, i.e. for every prefix a, check if a ^ candidate is in set.
 * 4. If achievable, update ans = candidate.
 * 
 * Time Complexity: O(N * 32) = O(N)
 * Space Complexity: O(N) for the prefix set.
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

int findMaximumXOR(int* nums) {
        int maxXOR = 0;
        int mask = 0;

        for (int bit = 31; bit >= 0; bit--) {
            mask |= (1 << bit);

            Set<int> prefixes = new HashSet<>();
            for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
                prefixes.add(num & mask);
            }

            int candidate = maxXOR | (1 << bit);

            for (size_t _idx = 0; _idx < sizeof(prefixes)/sizeof(prefixes[0]); _idx++) {
        int prefix = prefixes[_idx];
                if (prefixes.contains(candidate ^ prefix)) {
                    maxXOR = candidate;
                    break;
                }
            }
        }

        return maxXOR;
    }

    int main(void) {
        int* nums1 = {3, 10, 5, 25, 2, 8};
        printf("Max XOR: " + findMaximumXOR(nums1) + " (Expected: 28)\n");
        // 5 XOR 25 = 28

        int* nums2 = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
        printf("Max XOR: " + findMaximumXOR(nums2) + " (Expected: 127)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

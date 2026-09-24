/**
 * Problem Statement:
 * Given an integer array `nums` and an integer `k`, return true if `nums` has a good subarray.
 * A good subarray is a contiguous subarray where:
 *   1. Its length is at least two (length >= 2).
 *   2. The sum of the elements of the subarray is a multiple of `k` (sum % k == 0).
 * (LeetCode 523: Continuous Subarray Sum).
 *
 * Example:
 * nums = [23, 2, 4, 6, 7], k = 6 -> true ([23, 2, 4] sums to 29; [2, 4] sums to 6)
 *
 * Asked in: Facebook / Meta, Amazon, ByteDance
 *
 * Approach:
 * - Prefix Sum Modulo K with Earliest Index Map:
 *   If `(prefixSum[j] - prefixSum[i]) % k == 0`, then:
 *   `prefixSum[j] % k == prefixSum[i] % k`.
 *   If the SAME remainder has been seen at a prior index `prevIdx`, the subarray
 *   between `prevIdx + 1` and `j` is guaranteed to have a sum that is a multiple of `k`!
 * - Condition for Length >= 2:
 *   We require `j - prevIdx >= 2`.
 *   To maximize `j - prevIdx`, DO NOT overwrite existing remainders in the map!
 *   Only insert a remainder the FIRST time it is encountered.
 * - Base Case:
 *   `map.put(0, -1)` to handle subarrays starting from index 0 whose sum is a multiple of k.
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

bool checkSubarraySum(int* nums, int k) {
        if (nums == NULL || n < 2) return false;

        // Map remainder -> earliest index seen
        Map<int, int> remainderIndexMap = new HashMap<>();
        remainderIndexMap.put(0, -1); // Base case for subarrays starting at index 0

        int runningSum = 0;

        for (int i = 0; i < n; i++) {
            runningSum += nums[i];
            int remainder = runningSum % k;

            if (remainderIndexMap.containsKey(remainder)) {
                // Check if subarray length is at least 2
                if (i - remainderIndexMap.get(remainder) >= 2) {
                    return true;
                }
            } else {
                // Store only the earliest occurrence of this remainder
                remainderIndexMap.put(remainder, i);
            }
        }

        return false;
    }

    int main(void) {
        printf("=== LeetCode 523: Continuous Subarray Sum (Modulo K Map) ===\n");

        int** testArrays = {
            { 23, 2, 4, 6, 7 },
            { 23, 2, 6, 4, 7 },
            { 23, 2, 6, 4, 7 },
            { 0, 0 }
        };
        int* kValues = { 6, 6, 13, 1 };

        for (int i = 0; i < n; i++) {
            bool result = checkSubarraySum(testArrays[i], kValues[i]);
            printf("Array: %-20s | k = %2d ==> Good Subarray: %s\n",
                    java.util."[array]", kValues[i], result);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Single linear pass with O(1) hash map operations.
 * Space Complexity: O(min(N, K)) - Up to K distinct remainders stored in map.
 */

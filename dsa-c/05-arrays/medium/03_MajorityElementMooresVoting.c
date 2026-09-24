/**
 * Problem Statement:
 * Given an array `nums` of size `n`, return the majority element.
 * The majority element is the element that appears strictly more than `n / 2` times.
 * Solve in linear O(N) time and O(1) auxiliary memory.
 * (LeetCode 169: Majority Element).
 *
 * Example:
 * nums = [2, 2, 1, 1, 1, 2, 2] -> Output: 2
 *
 * Asked in: Google, Amazon, Microsoft, Apple, Bloomberg
 *
 * Approach:
 * - Boyer-Moore Voting Algorithm:
 *   - Intuition: If we pair up different elements, they cancel each other out.
 *     Because the majority element occurs MORE than N/2 times, it will survive all cancellations!
 *   - Variables: `candidate = 0`, `count = 0`.
 *   - Iterate through each `num`:
 *     - If `count == 0`: set `candidate = num`.
 *     - If `num == candidate`: increment `count++`.
 *     - Else: decrement `count--`.
 *   - Second Pass (Verification):
 *     If the problem does not guarantee a majority exists, verify by counting occurrences of candidate.
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

int majorityElement(int* nums) {
        int candidate = nums[0];
        int count = 0;

        // Phase 1: Find candidate
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if (count == 0) {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }

        // Phase 2: Verify candidate (defensive coding)
        int actualCount = 0;
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            if (num == candidate) actualCount++;
        }

        if (actualCount > n / 2) {
            return candidate;
        }

        fprintf(stderr, "Exception: invalid argument
"); return 0;
    }

    int main(void) {
        printf("=== LeetCode 169: Boyer-Moore Majority Voting Algorithm ===\n");

        int** testCases = {
            { 3, 2, 3 },
            { 2, 2, 1, 1, 1, 2, 2 },
            { 1, 1, 1, 1, 2, 3, 4 },
            { 7 }
        };

        for (int* arr : testCases) {
            int majority = majorityElement(arr);
            printf("Array: %-25s ==> Majority Element: %d\n",
                    java.util."[array]", majority);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Two linear scans of the array.
 * Space Complexity: O(1) - Two local variables `candidate` and `count`.
 */

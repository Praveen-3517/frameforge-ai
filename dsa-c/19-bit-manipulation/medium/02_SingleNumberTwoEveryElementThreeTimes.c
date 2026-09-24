/**
 * Problem: Single Number II (LeetCode 137)
 * Asked in: Amazon, Microsoft, Google
 * 
 * Given an integer array nums where every element appears exactly three times
 * except for one element which appears exactly once. Find that single one.
 * Must use O(1) extra space.
 * 
 * Approach - Bit Counting Modulo 3:
 * For every bit position, count the sum of that bit across all numbers.
 * Since triple-appearing numbers contribute 0 or 3 to each bit count,
 * the bit count mod 3 isolates the unique element's contribution.
 * 
 * Alternative Two-Variable Bit Circuit:
 * Maintain `ones` and `twos`:
 * - `ones` = bits seen odd number of times (mod 3 == 1)
 * - `twos` = bits seen twice (mod 3 == 2)
 * - A bit exits both when it has appeared 3 times.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

int singleNumber(int* nums) {
        int ones = 0;
        int twos = 0;

        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }

        return ones;
    }

    int main(void) {
        int* nums1 = {2, 2, 3, 2};
        printf("Single (appear once): " + singleNumber(nums1) + " (Expected: 3)\n");

        int* nums2 = {0, 1, 0, 1, 0, 1, 99};
        printf("Single (appear once): " + singleNumber(nums2) + " (Expected: 99)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

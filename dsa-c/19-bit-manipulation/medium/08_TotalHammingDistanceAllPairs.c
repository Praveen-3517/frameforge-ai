/**
 * Problem: Total Hamming Distance (LeetCode 477)
 * Asked in: Facebook, Google, Amazon
 * 
 * The Hamming distance between two integers is the number of positions at which the
 * corresponding bits are different. Given an integer array nums, return the sum of
 * Hamming distances between all pairs of the integers in nums.
 * 
 * Approach - Column-wise Bit Counting:
 * For each bit position b (0 to 31):
 * - Count how many numbers have bit b set: countOnes.
 * - The others: countZeros = n - countOnes.
 * - Each (1, 0) pair contributes 1 to the Hamming distance for this bit.
 * - Number of such pairs at bit b: countOnes * countZeros.
 * Sum across all 32 bits gives total Hamming distance.
 * 
 * Time Complexity: O(32 * N) = O(N)
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

int totalHammingDistance(int* nums) {
        int totalDistance = 0;
        int n = n;

        for (int bit = 0; bit < 32; bit++) {
            int countOnes = 0;
            for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
                countOnes += (num >> bit) & 1;
            }
            totalDistance += countOnes * (n - countOnes);
        }

        return totalDistance;
    }

    int main(void) {
        int* nums1 = {4, 14, 2};
        printf("Total Hamming Distance: " + totalHammingDistance(nums1) + " (Expected: 6)\n");
        // Pairs: (4,14)=2, (4,2)=2, (14,2)=2 -> total=6

        int* nums2 = {4, 14, 4};
        printf("Total Hamming Distance: " + totalHammingDistance(nums2) + " (Expected: 4)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

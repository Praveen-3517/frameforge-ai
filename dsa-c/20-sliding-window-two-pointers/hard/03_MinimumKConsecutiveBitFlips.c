/**
 * Problem: Minimum Number of K Consecutive Bit Flips (LeetCode 995)
 * Category: Sliding Window | Hard
 * Asked in: Google
 * 
 * You are given a binary array nums and an integer k.
 * A k-bit flip is choosing a subarray of length k from nums and simultaneously
 * changing every 0 in the subarray to 1, and every 1 in the subarray to 0.
 * Return the minimum number of k-bit flips required so that there is no 0 in the array.
 * Return -1 if it is not possible.
 * 
 * Approach - Sliding Window Flip Count (XOR Trick):
 * Instead of actually flipping, maintain a variable `flipped` tracking how many times
 * the current index has been flipped (mod 2).
 * Use a difference array (or deque): `flipChange[i] = 1` means a flip started at i expires at i+k.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for the flipChange array.
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

int minKBitFlips(int* nums, int k) {
        int n = n;
        int* flipChange = (int*)malloc((n + 1) * sizeof(int)); // flipChange[i] = 1 means a flip started at i-k ends here
        int totalFlips = 0;
        int currentFlips = 0; // number of active flips at position i (mod 2)

        for (int i = 0; i < n; i++) {
            currentFlips ^= flipChange[i]; // expire flips that no longer cover index i

            // Effective value at index i = nums[i] XOR (currentFlips % 2)
            if (nums[i] == currentFlips % 2) {
                // need to flip: nums[i] ^ 1 flipped state should be 1
                // effective bit after current flips: nums[i] XOR currentFlips
                // We need it to be 1, so if nums[i] ^ (currentFlips & 1) == 0, flip
            }

            int effectiveBit = nums[i] ^ (currentFlips & 1);
            if (effectiveBit == 0) {
                // We need to flip starting at i
                if (i + k > n) return -1; // can't flip, goes out of bounds
                totalFlips++;
                currentFlips ^= 1;
                if (i + k <= n) flipChange[i + k] ^= 1; // flip expires after index i+k-1
            }
        }

        return totalFlips;
    }

    int main(void) {
        printf("%d (Expected: 2)\n", minKBitFlips((int[]){0, 1, 0}, 1));
        // Flip index 0 and index 2
        printf("%d (Expected: -1)\n", minKBitFlips((int[]){1, 1, 0}, 2));
        // Cannot make all 1s
        printf("%d (Expected: 3)\n", minKBitFlips((int[]){0, 0, 0, 1, 0, 1, 1, 0}, 3));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

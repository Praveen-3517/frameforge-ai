/**
 * Problem: Contains Duplicate II (LeetCode 219)
 * Category: Fixed-Size Sliding Window | Easy
 * Asked in: Amazon, Bloomberg, Google
 * 
 * Given an integer array nums and an integer k, return true if there are two distinct
 * indices i and j in the array such that nums[i] == nums[j] and |i - j| <= k.
 * 
 * Approach - Sliding Window with HashMap:
 * Maintain a window of the last k elements using a HashMap (value -> index).
 * For each element, check if it already exists in the window.
 * If yes, indices differ by at most k: return true.
 * Update the map entry (index) for the current element.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(min(N, K)) for the map.
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

bool containsNearbyDuplicate(int* nums, int k) {
        Map<int, int> lastSeen = new HashMap<>();

        for (int i = 0; i < n; i++) {
            if (lastSeen.containsKey(nums[i]) && i - lastSeen.get(nums[i]) <= k) {
                return true;
            }
            lastSeen.put(nums[i], i);
        }

        return false;
    }

    int main(void) {
        printf("%d (Expected: true)\n", containsNearbyDuplicate((int[]){1, 2, 3, 1}, 3));
        printf("%d (Expected: true)\n", containsNearbyDuplicate((int[]){1, 0, 1, 1}, 1));
        printf("%d (Expected: false)\n", containsNearbyDuplicate((int[]){1, 2, 3, 1, 2, 3}, 2));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/*
 * Problem Statement:
 * Given an integer array nums and an integer k, return the length of the shortest
 * non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.
 * Note: nums can contain negative numbers, which precludes standard two-pointer sliding windows!
 * (LeetCode 862: Shortest Subarray with Sum at Least K)
 * 
 * Example:
 * Input: nums = [2,-1,2], k = 3
 * Output: 3
 * 
 * Asked in: Google, Goldman Sachs, Amazon
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
     * Approach:
     * Prefix Sums + Monotonic Deque:
     * 1. Compute prefix sums as long long* to prevent integer overflow.
     * 2. Maintain a monotonic increasing deque of indices:
     *    - While P[i] - P[deque.peekFirst()] >= k:
     *      A valid subarray found! Update minLen and pollFirst() because any later end index
     *      would produce a longer subarray with this start index.
     *    - While P[i] <= P[deque.peekLast()]:
     *      pollLast() because index i has a smaller prefix sum and is farther right,
     *      making previous larger prefix sum indices obsolete!
     */
    int shortestSubarray(int* nums, int k) {
        int n = n;
        long long* prefix = (long long*)malloc((n + 1) * sizeof(long long));
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        int minLen = INT_MAX;
        Deque<int> deque = new ArrayDeque<>();

        for (int i = 0; i <= n; i++) {
            // Check valid subarray satisfying sum >= k
            while (!deque.isEmpty() && prefix[i] - prefix[deque.peekFirst()] >= k) {
                minLen = MIN(minLen, i - deque.pollFirst());
            }

            // Maintain monotonic increasing prefix sums
            while (!deque.isEmpty() && prefix[i] <= prefix[deque.peekLast()]) {
                deque.pollLast();
            }

            deque.offerLast(i);
        }

        return minLen == INT_MAX ? -1 : minLen;
    }

    int main(void) {
        int* nums1 = {1};
        int k1 = 1;
        printf("nums: [1], k = 1 -> Shortest length: %d\n", shortestSubarray(nums1, k1));

        int* nums2 = {1, 2};
        int k2 = 4;
        printf("nums: [1, 2], k = 4 -> Shortest length: %d\n", shortestSubarray(nums2, k2));

        int* nums3 = {2, -1, 2};
        int k3 = 3;
        printf("nums: [2, -1, 2], k = 3 -> Shortest length: %d\n", shortestSubarray(nums3, k3));
        return 0;
}

/*
 * Time Complexity: O(N) - Each prefix index enters and leaves deque at most once.
 * Space Complexity: O(N) for prefix sums and monotonic deque.
 */

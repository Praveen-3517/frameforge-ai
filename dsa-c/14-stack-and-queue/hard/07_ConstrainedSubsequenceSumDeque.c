/**
 * Problem: Constrained Subsequence Sum (LeetCode 1425)
 * Asked in: Google, Uber, Amazon
 * 
 * Given an integer array nums and an integer k, return the maximum sum of a non-empty
 * subsequence such that for every two consecutive elements in the subsequence,
 * nums[i] and nums[j] (where i < j), the condition j - i <= k is satisfied.
 * 
 * Approach:
 * DP with Monotonic Decreasing Deque:
 * dp[i] = maximum subsequence sum ending at index i.
 * dp[i] = nums[i] + max(0, max_{i-k <= j < i} dp[j])
 * Using a monotonic double-ended queue, we maintain indices in sliding window [i-k, i-1]
 * with values dp[index] in decreasing order.
 * - If front index < i - k, poll front.
 * - dp[i] = nums[i] + max(0, dp[deque.peekFirst()])
 * - Pop elements from back while dp[deque.peekLast()] <= dp[i].
 * - Push i into deque.
 * 
 * Time Complexity: O(N) where N is array length (each index pushed and popped at most once).
 * Space Complexity: O(N) for DP array and deque.
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

int constrainedSubsetSum(int* nums, int k) {
        int n = n;
        int* dp = (int*)malloc((n) * sizeof(int));
        Deque<int> deque = new ArrayDeque<>();
        int maxSum = nums[0];

        for (int i = 0; i < n; i++) {
            // Remove indices out of range [i - k, i - 1]
            while (!deque.isEmpty() && deque.peekFirst() < i - k) {
                deque.pollFirst();
            }

            int prevMax = deque.isEmpty() ? 0 : MAX(0, dp[deque.peekFirst()]);
            dp[i] = nums[i] + prevMax;
            maxSum = MAX(maxSum, dp[i]);

            // Maintain monotonic decreasing order of dp values
            while (!deque.isEmpty() && dp[deque.peekLast()] <= dp[i]) {
                deque.pollLast();
            }
            deque.offerLast(i);
        }

        return maxSum;
    }

    int main(void) {
        int* nums1 = {10, 2, -10, 5, 20};
        int k1 = 2;
        printf("Test 1: " + constrainedSubsetSum(nums1, k1) + " (Expected: 37)\n");

        int* nums2 = {-1, -2, -3};
        int k2 = 1;
        printf("Test 2: " + constrainedSubsetSum(nums2, k2) + " (Expected: -1)\n");

        int* nums3 = {10, -2, -10, -5, 20};
        int k3 = 2;
        printf("Test 3: " + constrainedSubsetSum(nums3, k3) + " (Expected: 23)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

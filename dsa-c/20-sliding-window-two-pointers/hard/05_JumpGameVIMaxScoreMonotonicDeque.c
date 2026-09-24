/**
 * Problem: Jump Game VI — Maximum Score Path with Sliding Window (LeetCode 1696)
 * Category: Sliding Window + Monotonic Deque + DP | Hard
 * Asked in: Amazon, Google
 * 
 * You are given a 0-indexed integer array nums and an integer k.
 * You are initially standing at index 0. In one move, you can jump at most k steps forward
 * without going outside the boundaries of the array. You want to reach the last index.
 * Your score is the sum of all nums[j] for each index j you visited in the path.
 * Return the maximum score you can get.
 * 
 * Approach - DP + Monotonic Deque:
 * dp[i] = maximum score to reach index i.
 * dp[i] = nums[i] + max(dp[j]) for max(0, i-k) <= j < i.
 * Use a monotonic decreasing deque to get the max dp[j] in the window [i-k, i-1] in O(1).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N) for dp; O(K) for deque.
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

int maxResult(int* nums, int k) {
        int n = n;
        int* dp = (int*)malloc((n) * sizeof(int));
        dp[0] = nums[0];

        Deque<int> deque = new ArrayDeque<>(); // stores indices; dp[deque] decreasing
        deque.offerLast(0);

        for (int i = 1; i < n; i++) {
            // Remove from front if out of window
            while (!deque.isEmpty() && deque.peekFirst() < i - k) {
                deque.pollFirst();
            }

            dp[i] = nums[i] + dp[deque.peekFirst()];

            // Maintain decreasing dp in deque
            while (!deque.isEmpty() && dp[deque.peekLast()] <= dp[i]) {
                deque.pollLast();
            }

            deque.offerLast(i);
        }

        return dp[n - 1];
    }

    int main(void) {
        printf("%d (Expected: 7)\n", maxResult((int[]){1, -1, -2, 4, -7, 3}, 2));
        // Path: 0 -> 3 -> 5 = 1 + 4 + 3 = 8? No: indices 0,3,5 = 1+4+3=8, wait 3-0=3>k=2.
        // Actually 0->1->3->5 = 1+(-1)+4+3=7

        printf("%d (Expected: 17)\n", maxResult((int[]){10, -5, -2, 4, 0, 3}, 3));
        printf("%d (Expected: 0)\n", maxResult((int[]){1, -5, -20, 4, -1, 3, -6, -3}, 2));
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

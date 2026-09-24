/*
 * Problem Statement:
 * You are given an integer array nums and an integer target.
 * You want to build an expression out of nums by adding one of the symbols '+' and '-'
 * before each integer in nums and then concatenate all the integers.
 * Return the number of different expressions that you can build, which evaluates to target.
 * (LeetCode 494: Target Sum)
 * 
 * Example:
 * Input: nums = [1,1,1,1,1], target = 3
 * Output: 5
 * 
 * Asked in: Facebook/Meta, Amazon, Google
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

int findTargetSumWays(int* nums, int target) {
        Map<const char*, int> memo = new HashMap<>();
        return backtrack(nums, 0, 0, target, memo);
    }

    static int backtrack(int* nums, int index, int currentSum, int target, Map<const char*, int> memo) {
        if (index == n) {
            return currentSum == target ? 1 : 0;
        }

        const char* stateKey = index + "," + currentSum;
        if (memo.containsKey(stateKey)) {
            return memo.get(stateKey);
        }

        // Branch 1: Add nums[index]
        int add = backtrack(nums, index + 1, currentSum + nums[index], target, memo);
        // Branch 2: Subtract nums[index]
        int subtract = backtrack(nums, index + 1, currentSum - nums[index], target, memo);

        int totalWays = add + subtract;
        memo.put(stateKey, totalWays);
        return totalWays;
    }

    int main(void) {
        int* nums = {1, 1, 1, 1, 1};
        int target = 3;

        printf("Nums: [1, 1, 1, 1, 1], Target: 3\n");
        printf("Total expressions equaling target: " + findTargetSumWays(nums, target) + " (Expected: 5)\n");
        return 0;
}

/*
 * Time Complexity: O(N * S) where S is the sum range of nums.
 * Space Complexity: O(N * S) memoization table + O(N) call stack.
 */

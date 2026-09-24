/*
 * Problem Statement:
 * Given an array nums of distinct integers, return all the possible permutations.
 * You can return the answer in any order.
 * 
 * Example:
 * Input: nums = [1, 2, 3]
 * Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 * 
 * Asked in: Microsoft, Amazon, Google, Adobe, LinkedIn
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
     * Recursive In-Place Swapping:
     * At index 'start', swap nums[start] with every nums[i] where i ranges from start to end.
     * Recurse for start + 1.
     * Backtrack by swapping back to restore the original array state.
     */
    int*> permute(int* nums) {
        int*> result = new ArrayList<>();
        backtrack(nums, 0, result);
        return result;
    }

    static void backtrack(int* nums, int start, int*> result) {
        if (start == n) {
            int* current = new ArrayList<>();
            for (int num : nums) current.add(num);
            result.add(current);
            return;
        }

        for (int i = start; i < n; i++) {
            swap(nums, start, i);
            backtrack(nums, start + 1, result);
            swap(nums, start, i); // backtrack
        }
    }

    static void swap(int* arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    int main(void) {
        int* nums = {1, 2, 3};
        int*> perms = permute(nums);

        printf("Permutations of [1, 2, 3]: Total = %d\n", perms.size());
        for (int* p : perms) {
            printf("  %d\n", p);
        }
        return 0;
}

/*
 * Time Complexity: O(N * N!) - N! permutations, copying each takes O(N).
 * Space Complexity: O(N) - Recursion tree depth is N.
 */

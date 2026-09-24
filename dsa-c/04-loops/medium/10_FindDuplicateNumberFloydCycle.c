/**
 * Problem Statement:
 * Given an array of integers `nums` containing `n + 1` integers where each integer is
 * in the range `[1, n]` inclusive.
 * There is only one repeated number in `nums`, return this repeated number.
 * Requirements:
 *   - You must NOT modify the array `nums`.
 *   - You must use only constant O(1) extra space.
 *   - Runtime complexity must be less than O(N^2).
 * (LeetCode 287: Find the Duplicate Number).
 *
 * Asked in: Amazon, Google, Microsoft, Bloomberg, Apple
 *
 * Approach:
 * - Floyd's Tortoise and Hare Cycle Detection:
 *   Treat the array as a directed functional graph where an edge exists from index `i` to `nums[i]`.
 *   Since there are `n + 1` nodes with values pointing to `1..n`, a cycle is guaranteed by Dirichlet's Pigeonhole Principle!
 *   The duplicate number is precisely the entrance node to the cycle (where multiple nodes point to the same target).
 * - Phase 1 (Cycle Intersection):
 *   `slow = nums[slow]; fast = nums[nums[fast]];`
 *   Advance until `slow == fast`.
 * - Phase 2 (Cycle Entrance):
 *   Reset `slow = nums[0]`.
 *   Advance both `slow` and `fast` at speed 1: `slow = nums[slow]; fast = nums[fast];`
 *   They are mathematically guaranteed to meet at the cycle entrance, the duplicate number!
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

int findDuplicate(int* nums) {
        // Phase 1: Finding the intersection point in the cycle
        int slow = nums[0];
        int fast = nums[0];

        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Finding the entrance to the cycle
        slow = nums[0];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }

    int main(void) {
        printf("=== LeetCode 287: Find Duplicate Number (Floyd's Cycle Loop) ===\n");

        int** testArrays = {
            { 1, 3, 4, 2, 2 },
            { 3, 1, 3, 4, 2 },
            { 3, 3, 3, 3, 3 },
            { 2, 5, 9, 6, 9, 3, 8, 9, 7, 1 }
        };

        for (int* arr : testArrays) {
            int duplicate = findDuplicate(arr);
            printf("Array: %s ==> Duplicate: %d\n",
                    java.util."[array]", duplicate);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Traversing the cycle takes linear time.
 * Space Complexity: O(1) - Pointers `slow` and `fast` only. No array modification.
 */

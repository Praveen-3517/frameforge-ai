/**
 * Problem Statement:
 * Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.
 * You must write an algorithm that runs in O(N) time complexity.
 * (LeetCode 128: Longest Consecutive Sequence).
 *
 * Example:
 * nums = [100, 4, 200, 1, 3, 2]
 * The longest consecutive elements sequence is [1, 2, 3, 4]. Length = 4.
 *
 * Asked in: Google, Amazon, Microsoft, Facebook / Meta, Spotify
 *
 * Approach:
 * - Intelligent While Loop with Sequence-Start Detection:
 *   1. Insert all numbers into a `HashSet` for O(1) existence lookups.
 *   2. Iterate through each number in the set:
 *      - Condition: Check if `set.contains(num - 1)`.
 *      - If `num - 1` EXISTS, then `num` is NOT the start of a consecutive sequence!
 *        Skip it immediately without entering the while loop!
 *      - If `num - 1` DOES NOT EXIST, then `num` is the guaranteed beginning of a streak!
 *        Enter a while loop: while `set.contains(curr + 1)`, increment `curr` and `streak`.
 *   3. Why this is strictly O(N) rather than O(N^2):
 *      Numbers are only traversed inside the inner while loop when starting a sequence.
 *      Every element is visited at most twice across the entire algorithm.
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

int longestConsecutive(int* nums) {
        if (nums == NULL || n == 0) return 0;

        Set<int> numSet = new HashSet<>();
        for (size_t _idx = 0; _idx < sizeof(nums)/sizeof(nums[0]); _idx++) {
        int num = nums[_idx];
            numSet.add(num);
        }

        int longestStreak = 0;

        for (size_t _idx = 0; _idx < sizeof(numSet)/sizeof(numSet[0]); _idx++) {
        int num = numSet[_idx];
            // Only start counting if 'num' is the beginning of a sequence
            if (!numSet.contains(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (numSet.contains(currentNum + 1)) {
                    currentNum++;
                    currentStreak++;
                }

                longestStreak = MAX(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }

    int main(void) {
        printf("=== LeetCode 128: Longest Consecutive Sequence (O(N) Set + While Loop) ===\n");

        int** testCases = {
            { 100, 4, 200, 1, 3, 2 },
            { 0, 3, 7, 2, 5, 8, 4, 6, 0, 1 },
            { 1, 2, 0, 1 },
            { }
        };

        for (int* arr : testCases) {
            int longest = longestConsecutive(arr);
            printf("Array: %s ==> Longest Consecutive Length: %d\n",
                    java.util."[array]", longest);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Linear time since each element is part of at most one forward streak.
 * Space Complexity: O(N) - Storage for the HashSet.
 */

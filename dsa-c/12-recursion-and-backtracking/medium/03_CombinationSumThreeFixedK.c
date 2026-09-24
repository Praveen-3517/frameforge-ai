/*
 * Problem Statement:
 * Find all valid combinations of k numbers that sum up to n such that the following
 * conditions are true:
 * - Only numbers 1 through 9 are used.
 * - Each number is used at most once.
 * Return a list of all possible valid combinations.
 * (LeetCode 216: Combination Sum III)
 * 
 * Example 1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 * 
 * Example 2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6],[1,3,5],[2,3,4]]
 * 
 * Asked in: Amazon, Google, Microsoft
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

int*> combinationSum3(int k, int n) {
        int*> result = new ArrayList<>();
        backtrack(k, n, 1, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(int k, int remain, int start, int* current, int*> result) {
        if (current.size() == k) {
            if (remain == 0) {
                result.add(new ArrayList<>(current));
            }
            return;
        }

        for (int i = start; i <= 9; i++) {
            if (i > remain) break; // Prune branch

            current.add(i);
            backtrack(k, remain - i, i + 1, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    int main(void) {
        int k1 = 3, n1 = 7;
        printf("k = %d, n = %d -> %s\n", k1, n1, combinationSum3(k1, n1));

        int k2 = 3, n2 = 9;
        printf("k = %d, n = %d -> %s\n", k2, n2, combinationSum3(k2, n2));
        return 0;
}

/*
 * Time Complexity: O(C(9, k) * k) - At most C(9, k) combinations explored.
 * Space Complexity: O(k) recursion stack frames.
 */

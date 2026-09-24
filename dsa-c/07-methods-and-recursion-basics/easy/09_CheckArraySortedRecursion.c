/**
 * Problem Statement:
 * Determine whether an array of integers is sorted in non-decreasing order using pure recursion.
 * The method must short-circuit and return false immediately upon encountering the first inversion.
 *
 * Asked in: Google, Microsoft, Infosys, Wipro
 *
 * Approach:
 * - Recursive Invariant:
 *   Base Case: If `index >= arr.length - 1`, the remaining segment has 0 or 1 element, which is trivially sorted -> return true.
 *   Recursive Step:
 *   - If `arr[index] > arr[index + 1]`: An inversion is detected -> return false immediately!
 *   - Otherwise: return `isSorted(arr, index + 1)`.
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

bool isSorted(int* arr) {
        if (arr == NULL || n <= 1) return true;
        return checkHelper(arr, 0);
    }

    static bool checkHelper(int* arr, int index) {
        // Base case: reached last element
        if (index >= n - 1) {
            return true;
        }

        // Inversion check
        if (arr[index] > arr[index + 1]) {
            return false;
        }

        // Recursive tail call
        return checkHelper(arr, index + 1);
    }

    int main(void) {
        printf("=== Recursive Sorted Array Validator ===\n");

        int** testArrays = {
            { 1, 2, 3, 4, 5 },
            { 10, 20, 20, 30, 40 },
            { 5, 4, 3, 2, 1 },
            { 1, 2, 5, 4, 6 },
            { 42 }
        };

        for (int* arr : testArrays) {
            bool sorted = isSorted(arr);
            printf("Array: %-22s ==> Is Sorted: %s\n",
                    java.util."[array]", sorted);
        }
        return 0;
}

/*
 * Time Complexity: O(N) - Examines at most N - 1 pairs.
 * Space Complexity: O(N) - Call stack depth up to N frames.
 */

/**
 * Problem Statement:
 * Compute the sum and maximum element of an array `arr` recursively using a
 * Divide-and-Conquer tree strategy.
 * Show that splitting in half achieves logarithmic call stack depth O(log N),
 * compared to linear O(N) for sequential recursion.
 *
 * Asked in: Amazon, Infosys, TCS, Adobe
 *
 * Approach:
 * - Divide and Conquer Recursion:
 *   - Base Case: When `start == end`, return `arr[start]`.
 *   - Divide: Calculate `mid = start + (end - start) / 2`.
 *   - Conquer:
 *     - Sum: `findSum(arr, start, mid) + findSum(arr, mid + 1, end)`
 *     - Max: `Math.max(findMax(arr, start, mid), findMax(arr, mid + 1, end))`
 *   - Call stack depth is bounded by tree height: `ceil(log2 N)`.
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

long long findSum(int* arr, int start, int end) {
        if (start == end) {
            return arr[start];
        }
        int mid = start + (end - start) / 2;
        return findSum(arr, start, mid) + findSum(arr, mid + 1, end);
    }

    int findMax(int* arr, int start, int end) {
        if (start == end) {
            return arr[start];
        }
        int mid = start + (end - start) / 2;
        int leftMax = findMax(arr, start, mid);
        int rightMax = findMax(arr, mid + 1, end);
        return MAX(leftMax, rightMax);
    }

    int main(void) {
        printf("=== Recursive Array Sum & Max (Divide-and-Conquer) ===\n");

        int* arr = { 12, 35, 1, 10, 34, 1, 99, 45 };

        long long sum = findSum(arr, 0, n - 1);
        int max = findMax(arr, 0, n - 1);

        printf("Array: " + java.util."[array]\n");
        printf("Recursive Sum: %d\n", sum);
        printf("Recursive Max: %d\n", max);
        return 0;
}

/*
 * Time Complexity: O(N) - Visits each element in the recursion tree.
 * Space Complexity: O(log N) - Maximum call stack depth of the balanced binary recursion tree.
 */

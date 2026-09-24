/*
 * Problem Statement:
 * You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents
 * the width and the height of an envelope.
 * One envelope can fit into another if and only if both the width and height of one
 * envelope are strictly greater than the other envelope's width and height.
 * Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
 * (LeetCode 354: Russian Doll Envelopes)
 * 
 * Example:
 * Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
 * Output: 3 ([2,3] => [5,4] => [6,7])
 * 
 * Asked in: Google, Amazon, Microsoft, Uber
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
     * 2D Sort + Longest Increasing Subsequence (LIS) with Binary Search:
     * 1. Sort envelopes:
     *    - Ascending by width (w).
     *    - For matching widths, sort DESCENDING by height (h).
     *      (Descending height prevents two envelopes with the same width from being
     *       nested into each other!)
     * 2. Extract heights, and find LIS using Patience Sorting / Binary Search (O(N log N)).
     */
    int maxEnvelopes(int** envelopes) {
        if (envelopes == NULL || n == 0) return 0;

        // Sort width asc, height desc
        Arrays.sort(envelopes, (a, b) -> {
            if (a[0] == b[0]) {
                return int.compare(b[1], a[1]); // Descending
            }
            return int.compare(a[0], b[0]);     // Ascending
        });

        // Find LIS on heights array using binary search
        int* tails = (int*)malloc((n) * sizeof(int));
        int size = 0;

        for (int* env : envelopes) {
            int h = env[1];
            int low = 0, high = size;

            // Binary search for insertion point
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (tails[mid] < h) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }

            tails[low] = h;
            if (low == size) size++;
        }

        return size;
    }

    int main(void) {
        int** envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};

        printf("Envelopes: %d\n", Arrays.deepToString(envelopes));
        printf("Max Russian Doll nesting: " + maxEnvelopes(envelopes) + " (Expected: 3)\n");

        int** env2 = {{1, 1}, {1, 1}, {1, 1}};
        printf("\nIdentical envelopes nesting: " + maxEnvelopes(env2) + " (Expected: 1)\n");
        return 0;
}

/*
 * Time Complexity: O(N log N) - Sorting takes O(N log N), LIS takes O(N log N).
 * Space Complexity: O(N) tails array for patience sorting.
 */

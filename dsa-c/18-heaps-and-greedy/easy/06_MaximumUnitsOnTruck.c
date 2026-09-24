/**
 * Problem: Maximum Units on a Truck (LeetCode 1710)
 * Asked in: Amazon
 * 
 * You are assigned to put some amount of boxes onto one truck. You are given a 2D array
 * boxTypes, where boxTypes[i] = [numberOfBoxes_i, numberOfUnitsPerBox_i].
 * You are also given an integer truckSize, which is the maximum number of boxes that can be put on the truck.
 * Return the maximum total number of units that can be put on the truck.
 * 
 * Approach:
 * Greedy Fractional Knapsack Strategy:
 * 1. Sort boxTypes by units per box descending (b[1] - a[1]).
 * 2. Greedily pick the maximum boxes from the highest unit types until truck capacity is reached.
 * 
 * Time Complexity: O(N log N) for sorting.
 * Space Complexity: O(1) auxiliary space.
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

int maximumUnits(int** boxTypes, int truckSize) {
        // Sort by units per box descending
        Arrays.sort(boxTypes, (a, b) -> int.compare(b[1], a[1]));

        int totalUnits = 0;

        for (int* box : boxTypes) {
            int count = box[0];
            int units = box[1];

            int take = MIN(truckSize, count);
            totalUnits += take * units;
            truckSize -= take;

            if (truckSize == 0) break;
        }

        return totalUnits;
    }

    int main(void) {
        int** boxTypes1 = {{1, 3}, {2, 2}, {3, 1}};
        printf("Max units (truck=4): " + maximumUnits(boxTypes1, 4) + " (Expected: 8)\n");

        int** boxTypes2 = {{5, 10}, {2, 5}, {4, 7}, {3, 9}};
        printf("Max units (truck=10): " + maximumUnits(boxTypes2, 10) + " (Expected: 91)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

/**
 * Problem: Gas Station (LeetCode 134)
 * Asked in: Amazon, Google, Microsoft, Bloomberg
 * 
 * There are n gas stations along a circular route, where the amount of gas at the ith
 * station is gas[i]. Traveling from station i to i + 1 costs cost[i] gas.
 * Return the starting gas station's index if you can travel around the circuit once in the clockwise
 * direction, otherwise return -1.
 * 
 * Approach:
 * Greedy Single Pass:
 * 1. If sum(gas) < sum(cost), impossible to complete circuit -> return -1.
 * 2. Keep track of currentTank.
 *    If currentTank < 0 at station i, NO station from `start` to `i` can be the starting station!
 *    Reset currentTank = 0, and try starting at station i + 1.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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

int canCompleteCircuit(int* gas, int* cost) {
        int totalTank = 0;
        int currentTank = 0;
        int startStation = 0;

        for (int i = 0; i < n; i++) {
            int net = gas[i] - cost[i];
            totalTank += net;
            currentTank += net;

            if (currentTank < 0) {
                startStation = i + 1;
                currentTank = 0;
            }
        }

        return totalTank >= 0 ? startStation : -1;
    }

    int main(void) {
        int* gas1 = {1, 2, 3, 4, 5};
        int* cost1 = {3, 4, 5, 1, 2};
        printf("Start station 1: " + canCompleteCircuit(gas1, cost1) + " (Expected: 3)\n");

        int* gas2 = {2, 3, 4};
        int* cost2 = {3, 4, 3};
        printf("Start station 2: " + canCompleteCircuit(gas2, cost2) + " (Expected: -1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

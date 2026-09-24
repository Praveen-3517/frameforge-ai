/*
 * Problem Statement:
 * Given an array of integers temperatures represents the daily temperatures, return an array
 * answer such that answer[i] is the number of days you have to wait after the i-th day to get
 * a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0.
 * (LeetCode 739: Daily Temperatures)
 * 
 * Example:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 * 
 * Asked in: Facebook/Meta, Amazon, Google, Bloomberg
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
     * Monotonic Decreasing Stack of Indices:
     * - Iterate through temperatures:
     *   - While stack is not empty and temperatures[i] > temperatures[stack.peek()]:
     *     - warmer day found! idx = stack.pop(); result[idx] = i - idx;
     *   - Push index i onto stack.
     */
    int* dailyTemperatures(int* temperatures) {
        int n = n;
        int* result = (int*)malloc((n) * sizeof(int));
        Deque<int> stack = new ArrayDeque<>(); // Stores indices

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int prevDay = stack.pop();
                result[prevDay] = i - prevDay;
            }
            stack.push(i);
        }

        return result;
    }

    int main(void) {
        int* temps = {73, 74, 75, 71, 69, 72, 76, 73};

        printf("Temperatures: " + "[array]\n");
        printf("Wait days:    %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(N) - Each index pushed and popped at most once.
 * Space Complexity: O(N) monotonic index stack.
 */

/**
 * Problem: Task Scheduler (LeetCode 621)
 * Asked in: Facebook, Amazon, Google, Microsoft
 * 
 * Given a characters array tasks, representing CPU tasks (A through Z) and non-negative
 * integer n representing the cooling period between identical tasks.
 * Return the minimum number of units of times that the CPU will take to finish all the given tasks.
 * 
 * Approach:
 * Greedy Math / Formula:
 * 1. Find the task with maximum frequency `maxFreq`.
 * 2. Count how many tasks share this maximum frequency `maxCount`.
 * 3. The most frequent tasks define the framing structure:
 *    There are (maxFreq - 1) chunks of length (n + 1), plus the final trailing tasks `maxCount`.
 * 4. The minimum time needed is at least:
 *    (maxFreq - 1) * (n + 1) + maxCount
 * 5. If there are enough other tasks to fill all idle slots, time is simply tasks.length.
 *    Result = max(tasks.length, (maxFreq - 1) * (n + 1) + maxCount).
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1) for fixed alphabet frequencies (size 26).
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

int leastInterval(char* tasks, int n) {
        int* freq = (int*)malloc((26) * sizeof(int));
        int maxFreq = 0;

        for (size_t _idx = 0; _idx < sizeof(tasks)/sizeof(tasks[0]); _idx++) {
        char t = tasks[_idx];
            freq[t - 'A']++;
            maxFreq = MAX(maxFreq, freq[t - 'A']);
        }

        int maxCount = 0;
        for (size_t _idx = 0; _idx < sizeof(freq)/sizeof(freq[0]); _idx++) {
        int f = freq[_idx];
            if (f == maxFreq) {
                maxCount++;
            }
        }

        int time = (maxFreq - 1) * (n + 1) + maxCount;
        return MAX(n, time);
    }

    int main(void) {
        char* tasks1 = {'A', 'A', 'A', 'B', 'B', 'B'};
        printf("Least intervals (n=2): " + leastInterval(tasks1, 2) + " (Expected: 8)\n");
        // A -> B -> idle -> A -> B -> idle -> A -> B

        char* tasks2 = {'A', 'A', 'A', 'B', 'B', 'B'};
        printf("Least intervals (n=0): " + leastInterval(tasks2, 0) + " (Expected: 6)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

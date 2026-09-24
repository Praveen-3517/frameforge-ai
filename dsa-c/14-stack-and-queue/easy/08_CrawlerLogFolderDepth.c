/*
 * Problem Statement:
 * The Leetcode file system keeps a log each time, some user performs a change folder operation.
 * Operations:
 * - "../" : Move to parent folder (stay at main if already at main).
 * - "./"  : Remain in current folder.
 * - "x/"  : Move to child folder named x.
 * Return the minimum number of operations needed to go back to the main folder after all logs.
 * (LeetCode 1598: Crawler Log Folder)
 * 
 * Example:
 * Input: logs = ["d1/","d2/","../","d21/","./"]
 * Output: 2
 * 
 * Asked in: Amazon, Microsoft, Cisco
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

int minOperations(const char*[] logs) {
        int depth = 0;

        for (const char* log : logs) {
            if ((strcmp(log, "../") == 0)) {
                depth = MAX(0, depth - 1);
            } else if (!(strcmp(log, "./") == 0)) {
                depth++;
            }
        }

        return depth;
    }

    int main(void) {
        const char*[] logs1 = {"d1/", "d2/", "../", "d21/", "./"};
        printf("Logs: [\"d1/\",\"d2/\",\"../\",\"d21/\",\"./\"] -> Min steps: %d\n", minOperations(logs1));

        const char*[] logs2 = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
        printf("Logs: [\"d1/\",\"d2/\",\"./\",\"d3/\",\"../\",\"d31/\"] -> Min steps: %d\n", minOperations(logs2));
        return 0;
}

/*
 * Time Complexity: O(N) where N is the number of log entries.
 * Space Complexity: O(1) integer depth counter simulates stack height without heap allocation.
 */

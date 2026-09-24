/*
 * Problem Statement:
 * A binary watch has 4 LEDs on the top (representing hours 0-11) and 6 LEDs on the
 * bottom (representing minutes 0-59).
 * Given an integer turnedOn which represents the number of LEDs that are currently on,
 * return all possible times the watch could represent.
 * (LeetCode 401: Binary Watch)
 * 
 * Example:
 * Input: turnedOn = 1
 * Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
 * 
 * Asked in: Google, Amazon, Microsoft
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

int* readBinaryWatch(int turnedOn) {
        int* times = new ArrayList<>();
        if (turnedOn < 0 || turnedOn > 8) return times;

        for (int h = 0; h < 12; h++) {
            for (int m = 0; m < 60; m++) {
                if (int.bitCount(h) + int.bitCount(m) == turnedOn) {
                    times.add(const char*.format("%d:%02d", h, m));
                }
            }
        }

        return times;
    }

    int main(void) {
        int turnedOn = 1;
        int* result = readBinaryWatch(turnedOn);

        printf("Binary Watch times for turnedOn = " + turnedOn + " (Count: " + result.size() + "):\n");
        printf("%d\n", result);
        return 0;
}

/*
 * Time Complexity: O(1) - Constant search space: exactly 12 * 60 = 720 combinations checked.
 * Space Complexity: O(1) auxiliary space (excluding result list).
 */

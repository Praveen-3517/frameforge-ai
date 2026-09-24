/*
 * Problem Statement:
 * A valid IPv4 address consists of exactly four integers separated by single dots.
 * Each integer is between 0 and 255 (inclusive) and cannot have leading zeros (except '0').
 * Given a string s containing only digits, return all possible valid IPv4 addresses that
 * can be formed by inserting dots in s.
 * (LeetCode 93: Restore IP Addresses)
 * 
 * Example:
 * Input: s = "25525511135"
 * Output: ["255.255.11.135","255.255.111.35"]
 * 
 * Asked in: Amazon, Microsoft, Google, TikTok
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

int* restoreIpAddresses(const char* s) {
        int* result = new ArrayList<>();
        if (((int)strlen(s)) < 4 || ((int)strlen(s)) > 12) return result;
        backtrack(s, 0, 0, new ArrayList<>(), result);
        return result;
    }

    static void backtrack(const char* s, int index, int segmentCount, int* currentSegments, int* result) {
        if (segmentCount == 4) {
            if (index == ((int)strlen(s))) {
                result.add(const char*.join(".", currentSegments));
            }
            return;
        }

        // A segment can be 1, 2, or 3 digits long long
        for (int len = 1; len <= 3; len++) {
            if (index + len > ((int)strlen(s))) break;

            const char* part = s.substring(index, index + len);

            // Check leading zero
            if (part.startsWith("0") && ((int)strlen(part)) > 1) break;

            // Check value <= 255
            int val = int.parseInt(part);
            if (val <= 255) {
                currentSegments.add(part);
                backtrack(s, index + len, segmentCount + 1, currentSegments, result);
                currentSegments.remove(currentSegments.size() - 1); // backtrack
            }
        }
    }

    int main(void) {
        const char* s1 = "25525511135";
        printf("const char*: \"%d\" -> Valid IPs: %d\n", s1, restoreIpAddresses(s1));

        const char* s2 = "0000";
        printf("const char*: \"%d\" -> Valid IPs: %d\n", s2, restoreIpAddresses(s2));

        const char* s3 = "101023";
        printf("const char*: \"%d\" -> Valid IPs: %d\n", s3, restoreIpAddresses(s3));
        return 0;
}

/*
 * Time Complexity: O(1) - The search tree has maximum depth 4 and branching factor 3 (3^4 = 81 leaves).
 * Space Complexity: O(1) auxiliary space.
 */

/**
 * Problem: Find the Town Judge (LeetCode 997)
 * Asked in: Amazon, Microsoft, Bloomberg
 * 
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these
 * people is secretly the town judge. If the town judge exists:
 * 1. The town judge trusts nobody.
 * 2. Everybody (except for the town judge) trusts the town judge.
 * 3. There is exactly one person that satisfies properties 1 and 2.
 * Given trust[i] = [a, b], return the label of the town judge if they exist, or -1.
 * 
 * Approach:
 * Directed Graph In-Degree & Out-Degree:
 * - If person `a` trusts `b`, `a` has out-degree + 1, and `b` has in-degree + 1.
 * - Net trust score: score[person] = inDegree - outDegree.
 * - The judge must be trusted by n - 1 people (inDegree = n - 1) and trust 0 people (outDegree = 0).
 * - Therefore, judge's net score must be exactly n - 1.
 * 
 * Time Complexity: O(V + E) where V = n and E = trust.length.
 * Space Complexity: O(n) for the score array.
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

int findJudge(int n, int** trust) {
        int* score = (int*)malloc((n + 1) * sizeof(int));

        for (int* relation : trust) {
            score[relation[0]]--; // out-degree decreases score
            score[relation[1]]++; // in-degree increases score
        }

        for (int i = 1; i <= n; i++) {
            if (score[i] == n - 1) {
                return i;
            }
        }

        return -1;
    }

    int main(void) {
        int** trust1 = {{1, 2}};
        printf("Judge: " + findJudge(2, trust1) + " (Expected: 2)\n");

        int** trust2 = {{1, 3}, {2, 3}};
        printf("Judge: " + findJudge(3, trust2) + " (Expected: 3)\n");

        int** trust3 = {{1, 3}, {2, 3}, {3, 1}};
        printf("Judge: " + findJudge(3, trust3) + " (Expected: -1)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

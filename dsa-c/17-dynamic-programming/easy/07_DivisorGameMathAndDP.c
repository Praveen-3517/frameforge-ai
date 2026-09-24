/**
 * Problem: Divisor Game (LeetCode 1025)
 * Asked in: Google, Amazon
 * 
 * Alice and Bob take turns playing a game, with Alice starting first.
 * Initially, there is a number n on the chalkboard. On each player's turn, that player:
 * 1. Chooses any x with 0 < x < n and n % x == 0.
 * 2. Replaces the number n with n - x.
 * Also, if a player cannot make a move, they lose the game.
 * Return true if Alice wins assuming both play optimally.
 * 
 * Approach:
 * 1. Dynamic Programming:
 *    dp[i] = true if player whose turn it is wins with number i.
 *    For each divisor x of i: if !dp[i - x], then dp[i] = true.
 * 2. Mathematical Insight:
 *    If n is even, Alice chooses x = 1, giving Bob an odd number.
 *    Any divisor of an odd number is odd; odd - odd = even.
 *    Bob must always hand Alice back an even number.
 *    Eventually Alice hands Bob 1 (no moves left).
 *    Thus, Alice wins if and only if n is even!
 * 
 * Time Complexity: O(N * sqrt(N)) for DP, O(1) for math.
 * Space Complexity: O(N) for DP, O(1) for math.
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

bool divisorGameDP(int n) {
        bool[] dp = (bool*)malloc((n + 1) * sizeof(bool));
        // dp[1] is false (no move available)

        for (int i = 2; i <= n; i++) {
            for (int x = 1; x * x <= i; x++) {
                if (i % x == 0) {
                    if (!dp[i - x] || !dp[i - (i / x)]) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp[n];
    }

    bool divisorGameMath(int n) {
        return n % 2 == 0;
    }

    int main(void) {
        printf("n = 2: " + divisorGameDP(2) + " (Expected: true)\n");
        printf("n = 3: " + divisorGameDP(3) + " (Expected: false)\n");
        printf("n = 4: " + divisorGameMath(4) + " (Expected: true)\n");
        return 0;
}

/*
 * Time Complexity: O(N) or O(1) optimal.
 * Space Complexity: O(1) auxiliary.
 */

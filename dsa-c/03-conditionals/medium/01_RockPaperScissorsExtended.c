/**
 * Problem Statement:
 * Implement the extended "Rock, Paper, Scissors, Lizard, Spock" game (invented by Sam Kass
 * and popularized by The Big Bang Theory) for two players:
 * Rules:
 *   - Scissors cuts Paper
 *   - Paper covers Rock
 *   - Rock crushes Lizard
 *   - Lizard poisons Spock
 *   - Spock smashes Scissors
 *   - Scissors decapitates Lizard
 *   - Lizard eats Paper
 *   - Paper disproves Spock
 *   - Spock vaporizes Rock
 *   - Rock crushes Scissors
 * Determine whether Player 1 wins, Player 2 wins, or it is a Tie.
 *
 * Asked in: Amazon, Electronic Arts (EA), Gaming / Simulation Rounds
 *
 * Approach:
 * - Method 1: Nested Switch-Case conditional mapping.
 * - Method 2: Modular Arithmetic / Win Matrix:
 *   Assign IDs: Rock=0, Spock=1, Paper=2, Lizard=3, Scissors=4.
 *   Notice that in circular layout, each choice beats the next two counter-clockwise options!
 *   Difference: `(p1 - p2 + 5) % 5`:
 *   - 0: Tie
 *   - 1 or 3: Player 1 wins!
 *   - 2 or 4: Player 2 wins!
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

enum Move {
        ROCK, PAPER, SCISSORS, LIZARD, SPOCK
    }

    const char* determineWinner(Move p1, Move p2) {
        if (p1 == p2) {
            return "Tie! Both chose " + p1;
        }

        // Switch on player 1's move
        bool p1Wins = switch (p1) {
            case ROCK     -> (p2 == Move.SCISSORS || p2 == Move.LIZARD);
            case PAPER    -> (p2 == Move.ROCK     || p2 == Move.SPOCK);
            case SCISSORS -> (p2 == Move.PAPER    || p2 == Move.LIZARD);
            case LIZARD   -> (p2 == Move.SPOCK    || p2 == Move.PAPER);
            case SPOCK    -> (p2 == Move.SCISSORS || p2 == Move.ROCK);
        };

        return p1Wins ? ("Player 1 Wins (" + p1 + " beats " + p2 + ")")
                      : ("Player 2 Wins (" + p2 + " beats " + p1 + ")");
    }

    int main(void) {
        printf("=== Rock-Paper-Scissors-Lizard-Spock Outcome Engine ===\n");

        Move[][] matchUps = {
            { Move.ROCK, Move.SCISSORS },
            { Move.SPOCK, Move.ROCK },
            { Move.SCISSORS, Move.LIZARD },
            { Move.LIZARD, Move.SPOCK },
            { Move.PAPER, Move.SPOCK },
            { Move.ROCK, Move.ROCK }
        };

        for (Move[] match : matchUps) {
            printf("%d\n", determineWinner(match[0], match[1]));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Modern switch enum jump table.
 * Space Complexity: O(1) - Constant stack registers.
 */

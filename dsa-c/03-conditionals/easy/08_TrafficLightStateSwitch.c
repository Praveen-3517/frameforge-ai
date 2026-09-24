/**
 * Problem Statement:
 * Model a smart traffic light controller using a Java `enum` and modern `switch` expression.
 * The controller must support:
 * 1. State transitions: RED -> GREEN -> YELLOW -> RED.
 * 2. Duration lookup for each light state.
 * 3. Driver advisory action (e.g. "STOP", "PROCEED WITH CAUTION", "GO").
 * Demonstrate compile-time exhaustiveness checking (when switching over enums, modern Java
 * requires no default clause if all enum values are covered!).
 *
 * Asked in: Amazon, Oracle, Siemens, Bosch
 *
 * Approach:
 * - Define enum `TrafficLight { RED, YELLOW, GREEN }`.
 * - Transition method: `nextState(TrafficLight current)` returns the subsequent state.
 * - Modern switch expressions over enums enforce exhaustive matching. If a developer adds
 *   a new enum constant (e.g. FLASHING_RED), the compiler flags all unhandled switch expressions!
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

enum TrafficLight {
        RED,
        YELLOW,
        GREEN
    }

    // State Transition: Exhaustive enum switch without default
    TrafficLight getNextState(TrafficLight current) {
        return switch (current) {
            case RED    -> TrafficLight.GREEN;
            case GREEN  -> TrafficLight.YELLOW;
            case YELLOW -> TrafficLight.RED;
        };
    }

    // Duration lookup in seconds
    int getDurationSeconds(TrafficLight light) {
        return switch (light) {
            case RED    -> 60;
            case GREEN  -> 45;
            case YELLOW -> 5;
        };
    }

    // Advisory action
    const char* getAdvisory(TrafficLight light) {
        return switch (light) {
            case RED    -> "STOP: Complete vehicle halt behind line.";
            case YELLOW -> "CAUTION: Prepare to stop; clear intersection.";
            case GREEN  -> "GO: Proceed if intersection is clear.";
        };
    }

    int main(void) {
        printf("=== Finite State Machine: Traffic Light Controller (Enum Switch) ===\n");

        TrafficLight state = TrafficLight.RED;
        printf("Simulating 6 state transitions:\n");

        for (int cycle = 1; cycle <= 6; cycle++) {
            printf("Step %d: [%-6s] (Duration: %2ds) -> %s\n",
                    cycle, state, getDurationSeconds(state), getAdvisory(state));
            state = getNextState(state);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Enum ordinal index lookup in JVM tableswitch.
 * Space Complexity: O(1) - Static enum singletons.
 */

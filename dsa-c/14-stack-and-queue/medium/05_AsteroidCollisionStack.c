/*
 * Problem Statement:
 * We are given an array asteroids of integers representing asteroids in a row.
 * For each asteroid, the absolute value represents its size, and the sign represents its
 * direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
 * Find out the state of the asteroids after all collisions:
 * - Two asteroids moving in the same direction never meet.
 * - When two meet: smaller explodes; if same size, both explode.
 * (LeetCode 735: Asteroid Collision)
 * 
 * Example 1:
 * Input: asteroids = [5,10,-5]
 * Output: [5,10] (10 and -5 collide, -5 explodes)
 * 
 * Example 2:
 * Input: asteroids = [8,-8]
 * Output: [] (both explode)
 * 
 * Asked in: Google, Amazon, Microsoft, DoorDash
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
     * Simulation with Stack:
     * - A collision occurs ONLY when a right-moving asteroid (> 0) on stack meets
     *   a left-moving asteroid (< 0) incoming.
     * - Handle while-loop collision resolving:
     *   - stack.peek() < -incoming: stack asteroid explodes (pop and continue collision check).
     *   - stack.peek() == -incoming: both explode (pop and do not insert incoming).
     *   - stack.peek() > -incoming: incoming explodes (do not insert incoming).
     */
    int* asteroidCollision(int* asteroids) {
        Deque<int> stack = new ArrayDeque<>();

        for (size_t _idx = 0; _idx < sizeof(asteroids)/sizeof(asteroids[0]); _idx++) {
        int ast = asteroids[_idx];
            bool alive = true;

            while (alive && ast < 0 && !stack.isEmpty() && stack.peek() > 0) {
                if (stack.peek() < -ast) {
                    stack.pop(); // Asteroid on stack explodes
                } else if (stack.peek() == -ast) {
                    stack.pop(); // Both explode
                    alive = false;
                } else {
                    alive = false; // Incoming asteroid explodes
                }
            }

            if (alive) {
                stack.push(ast);
            }
        }

        int* result = (int*)malloc((stack.size()) * sizeof(int));
        for (int i = stack.size() - 1; i >= 0; i--) {
            result[i] = stack.pop();
        }
        return result;
    }

    int main(void) {
        int* a1 = {5, 10, -5};
        printf("Input: [5, 10, -5] -> Remaining: %d\n", "[array]"));

        int* a2 = {8, -8};
        printf("Input: [8, -8]     -> Remaining: %d\n", "[array]"));

        int* a3 = {10, 2, -5};
        printf("Input: [10, 2, -5] -> Remaining: %d\n", "[array]"));

        int* a4 = {-2, -1, 1, 2};
        printf("Input: [-2,-1,1,2] -> Remaining: %d\n", "[array]"));
        return 0;
}

/*
 * Time Complexity: O(N) - Each asteroid is pushed and popped at most once.
 * Space Complexity: O(N) stack storage.
 */

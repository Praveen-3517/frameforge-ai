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

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class AsteroidCollisionStack {

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
    public static int[] asteroidCollision(int[] asteroids) {
        Deque<Integer> stack = new ArrayDeque<>();

        for (int ast : asteroids) {
            boolean alive = true;

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

        int[] result = new int[stack.size()];
        for (int i = stack.size() - 1; i >= 0; i--) {
            result[i] = stack.pop();
        }
        return result;
    }

    public static void main(String[] args) {
        int[] a1 = {5, 10, -5};
        System.out.println("Input: [5, 10, -5] -> Remaining: " + Arrays.toString(asteroidCollision(a1)));

        int[] a2 = {8, -8};
        System.out.println("Input: [8, -8]     -> Remaining: " + Arrays.toString(asteroidCollision(a2)));

        int[] a3 = {10, 2, -5};
        System.out.println("Input: [10, 2, -5] -> Remaining: " + Arrays.toString(asteroidCollision(a3)));

        int[] a4 = {-2, -1, 1, 2};
        System.out.println("Input: [-2,-1,1,2] -> Remaining: " + Arrays.toString(asteroidCollision(a4)));
    }
}

/*
 * Time Complexity: O(N) - Each asteroid is pushed and popped at most once.
 * Space Complexity: O(N) stack storage.
 */

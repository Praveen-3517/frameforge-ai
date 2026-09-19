/*
 * Problem Statement:
 * The Tower of Hanoi is a mathematical puzzle with 3 rods (Source, Auxiliary, Destination)
 * and N disks of different sizes.
 * The objective is to move the entire stack from Source to Destination following rules:
 * 1. Only one disk can be moved at a time.
 * 2. Each move consists of taking the upper disk from one stack and placing it atop another.
 * 3. No disk may be placed on top of a smaller disk.
 * Print all steps and return the total number of moves (which is 2^N - 1).
 * 
 * Asked in: Amazon, Microsoft, Samsung, Goldman Sachs
 */

import java.util.ArrayList;
import java.util.List;

class TowerOfHanoiClassic {

    static class Step {
        int disk;
        char fromRod;
        char toRod;

        Step(int disk, char fromRod, char toRod) {
            this.disk = disk;
            this.fromRod = fromRod;
            this.toRod = toRod;
        }

        @Override
        public String toString() {
            return "Move disk " + disk + " from " + fromRod + " to " + toRod;
        }
    }

    /**
     * Approach:
     * Divide and Conquer Recursion:
     * To move N disks from Source 'A' to Destination 'C' using Auxiliary 'B':
     * 1. Move (N - 1) disks from 'A' to 'B' using 'C'.
     * 2. Move N-th disk directly from 'A' to 'C'.
     * 3. Move (N - 1) disks from 'B' to 'C' using 'A'.
     */
    public static long solveHanoi(int n, char fromRod, char toRod, char auxRod, List<Step> history) {
        if (n == 0) return 0;
        if (n == 1) {
            if (history != null) history.add(new Step(1, fromRod, toRod));
            return 1;
        }

        long moves = 0;
        // Step 1: Move top n-1 disks from source to aux
        moves += solveHanoi(n - 1, fromRod, auxRod, toRod, history);

        // Step 2: Move n-th disk from source to dest
        if (history != null) history.add(new Step(n, fromRod, toRod));
        moves += 1;

        // Step 3: Move n-1 disks from aux to dest
        moves += solveHanoi(n - 1, auxRod, toRod, fromRod, history);

        return moves;
    }

    public static void main(String[] args) {
        int n = 3;
        List<Step> history = new ArrayList<>();
        long totalMoves = solveHanoi(n, 'A', 'C', 'B', history);

        System.out.println("--- Tower of Hanoi with N = " + n + " disks ---");
        for (Step step : history) {
            System.out.println("  " + step);
        }
        System.out.println("Total moves executed: " + totalMoves);
        System.out.println("Theoretical minimum (2^n - 1): " + ((1L << n) - 1));

        // Test with n = 4
        long moves4 = solveHanoi(4, 'A', 'C', 'B', null);
        System.out.println("\nTotal moves for N = 4 disks: " + moves4 + " (Expected: 15)");
    }
}

/*
 * Time Complexity: O(2^N) - Recurrence relation T(N) = 2T(N - 1) + 1 yields 2^N - 1 calls.
 * Space Complexity: O(N) - Maximum recursion stack depth is N.
 */

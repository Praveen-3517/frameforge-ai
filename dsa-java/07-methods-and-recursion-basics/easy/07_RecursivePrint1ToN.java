/**
 * Problem Statement:
 * Print numbers from 1 to N and from N to 1 recursively without using any loops (`for`, `while`, `do-while`).
 * Demonstrate the fundamental difference between:
 * 1. Head Recursion (actions execute after the recursive call during stack unwinding).
 * 2. Tail Recursion (actions execute before the recursive call during descent).
 *
 * Asked in: TCS, Wipro, Infosys, Cognizant
 *
 * Approach:
 * - Print 1 to N (Head Recursion / Stack Unwinding):
 *   `if (n == 0) return;`
 *   `print1ToN(n - 1);` // Recurse first
 *   `System.out.print(n + " ");` // Print on stack unwinding
 * - Print N to 1 (Tail Recursion / Pre-order descent):
 *   `if (n == 0) return;`
 *   `System.out.print(n + " ");` // Print before recursing
 *   `printNTo1(n - 1);`
 */
class RecursivePrint1ToN {

    // Head Recursion: prints 1 to N
    public static void print1ToN(int n) {
        if (n == 0) return;
        print1ToN(n - 1);
        System.out.print(n + " ");
    }

    // Tail Recursion: prints N to 1
    public static void printNTo1(int n) {
        if (n == 0) return;
        System.out.print(n + " ");
        printNTo1(n - 1);
    }

    public static void main(String[] args) {
        System.out.println("=== Recursive Head vs Tail Printing (No Loops) ===");

        int n = 10;
        System.out.printf("Printing 1 to %d (Head Recursion) : ", n);
        print1ToN(n);
        System.out.println();

        System.out.printf("Printing %d to 1 (Tail Recursion) : ", n);
        printNTo1(n);
        System.out.println();
    }
}

/*
 * Time Complexity: O(N) - Exactly N recursive calls.
 * Space Complexity: O(N) - N frames on the JVM call stack.
 */

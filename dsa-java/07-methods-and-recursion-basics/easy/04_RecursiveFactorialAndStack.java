/**
 * Problem Statement:
 * Compute the factorial of an integer `n` recursively:
 *   n! = n * (n - 1)! with base case 0! = 1 and 1! = 1.
 * Instrument the recursion to visually print the JVM Call Stack frames
 * (demonstrating stack pushes on entry and stack pops on return).
 * Discuss the cause and prevention of `java.lang.StackOverflowError`.
 *
 * Asked in: TCS, Infosys, Accenture, Cognizant
 *
 * Approach:
 * - Base Case: `if (n <= 1) return 1L;`
 * - Recursive Step: `return n * factorial(n - 1);`
 * - Indentation: Use depth-based space indentation to visualize the Call Stack tree.
 */
class RecursiveFactorialAndStack {

    public static long factorialWithVisualization(int n, int depth) {
        String indent = "  ".repeat(depth);
        System.out.printf("%s-> [PUSH] Entering factorial(%d) | Stack Depth: %d%n", indent, n, depth);

        if (n <= 1) {
            System.out.printf("%s<- [BASE CASE REACHED] Returning 1 for factorial(%d)%n", indent, n);
            return 1L;
        }

        long result = n * factorialWithVisualization(n - 1, depth + 1);

        System.out.printf("%s<- [POP]  Exiting factorial(%d) = %d%n", indent, n, result);
        return result;
    }

    public static void main(String[] args) {
        System.out.println("=== Recursive Factorial with JVM Call Stack Visualization ===");

        int n = 5;
        long fact = factorialWithVisualization(n, 0);
        System.out.printf("%nFinal Calculated Factorial(%d): %d%n", n, fact);
    }
}

/*
 * Time Complexity: O(N) - Exactly N recursive invocations.
 * Space Complexity: O(N) - N stack frames on the Call Stack.
 */

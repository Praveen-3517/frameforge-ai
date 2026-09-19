/**
 * Problem: Fibonacci Number (LeetCode 509)
 * Asked in: Amazon, Microsoft, Apple
 * 
 * F(0) = 0, F(1) = 1
 * F(n) = F(n - 1) + F(n - 2), for n > 1.
 * Given n, calculate F(n).
 * 
 * Approach:
 * Iterative dynamic programming with O(1) space:
 * Maintain only the last two Fibonacci numbers.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class FibonacciNumberOptimized {

    public static int fib(int n) {
        if (n <= 1) return n;

        int a = 0;
        int b = 1;

        for (int i = 2; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }

        return b;
    }

    public static void main(String[] args) {
        System.out.println("F(2): " + fib(2) + " (Expected: 1)");
        System.out.println("F(3): " + fib(3) + " (Expected: 2)");
        System.out.println("F(4): " + fib(4) + " (Expected: 3)");
        System.out.println("F(10): " + fib(10) + " (Expected: 55)");
    }
}

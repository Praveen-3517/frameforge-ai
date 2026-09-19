/*
 * Problem Statement:
 * Compare Naive vs Memoized Recursion:
 * - Fibonacci Number (LeetCode 509):
 *   - Naive recursion: O(2^N) time due to overlapping redundant subtrees.
 *   - Top-down memoized recursion: O(N) time with array/HashMap cache.
 * - Factorial calculation with memoization table.
 * 
 * Asked in: TCS, Infosys, Capgemini, Amazon
 */

class FactorialAndFibonacciMemoized {

    // 1. Fibonacci with Memoization
    public static long fibMemo(int n) {
        long[] memo = new long[n + 1];
        return fibHelper(n, memo);
    }

    private static long fibHelper(int n, long[] memo) {
        if (n <= 1) return n;
        if (memo[n] != 0) return memo[n];
        return memo[n] = fibHelper(n - 1, memo) + fibHelper(n - 2, memo);
    }

    // 2. Naive Fibonacci (Exponential O(2^N))
    public static long fibNaive(int n) {
        if (n <= 1) return n;
        return fibNaive(n - 1) + fibNaive(n - 2);
    }

    public static void main(String[] args) {
        System.out.println("--- Fibonacci Comparison ---");
        int n = 40;

        long t1 = System.currentTimeMillis();
        long resMemo = fibMemo(n);
        long t2 = System.currentTimeMillis();
        System.out.printf("Memoized fib(%d) = %d in %dms%n", n, resMemo, (t2 - t1));

        long t3 = System.currentTimeMillis();
        long resNaive = fibNaive(n);
        long t4 = System.currentTimeMillis();
        System.out.printf("Naive    fib(%d) = %d in %dms%n", n, resNaive, (t4 - t3));
    }
}

/*
 * Time Complexity: Memoized: O(N), Naive: O(2^N).
 * Space Complexity: O(N) memoization array and call stack depth.
 */

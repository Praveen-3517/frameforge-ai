/**
 * Problem: N-th Tribonacci Number (LeetCode 1137)
 * Asked in: Amazon, Apple
 * 
 * T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
 * Given n, return the value of Tn.
 * 
 * Approach:
 * Iterative DP with 3 state variables:
 * Maintain only the previous 3 terms.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class TribonacciNumber {

    public static int tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        int t0 = 0, t1 = 1, t2 = 1;

        for (int i = 3; i <= n; i++) {
            int t3 = t0 + t1 + t2;
            t0 = t1;
            t1 = t2;
            t2 = t3;
        }

        return t2;
    }

    public static void main(String[] args) {
        System.out.println("T(4): " + tribonacci(4) + " (Expected: 4)");
        System.out.println("T(25): " + tribonacci(25) + " (Expected: 1389537)");
    }
}

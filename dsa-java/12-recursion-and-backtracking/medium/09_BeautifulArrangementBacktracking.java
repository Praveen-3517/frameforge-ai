/*
 * Problem Statement:
 * Suppose you have n integers labeled 1 through n. A permutation of these n integers
 * perm (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n):
 * 1. perm[i] is divisible by i, or
 * 2. i is divisible by perm[i].
 * Given an integer n, return the number of the beautiful arrangements you can construct.
 * (LeetCode 526: Beautiful Arrangement)
 * 
 * Example:
 * Input: n = 2
 * Output: 2 ([1,2] and [2,1])
 * 
 * Asked in: Google, Amazon, Microsoft
 */

class BeautifulArrangementBacktracking {

    private static int count = 0;

    public static int countArrangement(int n) {
        count = 0;
        boolean[] visited = new boolean[n + 1];
        backtrack(1, n, visited);
        return count;
    }

    private static void backtrack(int pos, int n, boolean[] visited) {
        if (pos > n) {
            count++;
            return;
        }

        for (int num = 1; num <= n; num++) {
            if (!visited[num] && (num % pos == 0 || pos % num == 0)) {
                visited[num] = true;
                backtrack(pos + 1, n, visited);
                visited[num] = false; // backtrack
            }
        }
    }

    public static void main(String[] args) {
        for (int n = 1; n <= 6; n++) {
            System.out.printf("n = %d -> Beautiful Arrangements: %d%n", n, countArrangement(n));
        }
    }
}

/*
 * Time Complexity: O(k) where k is the number of valid permutations satisfying divisibility.
 * Space Complexity: O(n) boolean visited array and recursion call stack.
 */

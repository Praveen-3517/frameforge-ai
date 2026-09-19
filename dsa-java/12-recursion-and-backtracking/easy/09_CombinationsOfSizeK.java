/*
 * Problem Statement:
 * Given two integers n and k, return all possible combinations of k numbers chosen
 * from the range [1, n]. You may return the answer in any order.
 * (LeetCode 77: Combinations)
 * 
 * Example:
 * Input: n = 4, k = 2
 * Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
 * 
 * Asked in: Google, Amazon, Microsoft, Apple
 */

import java.util.ArrayList;
import java.util.List;

class CombinationsOfSizeK {

    /**
     * Approach:
     * Backtracking with Pruning:
     * - Only pick numbers from `start` to `n`.
     * - Pruning optimization:
     *   We need `k - current.size()` more elements.
     *   If `n - i + 1 < k - current.size()`, there aren't enough elements left in the range,
     *   so we can safely stop iterating!
     */
    public static List<List<Integer>> combine(int n, int k) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(1, n, k, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(int start, int n, int k, List<Integer> current, List<List<Integer>> result) {
        if (current.size() == k) {
            result.add(new ArrayList<>(current));
            return;
        }

        // Pruned loop condition
        int needed = k - current.size();
        for (int i = start; i <= n - needed + 1; i++) {
            current.add(i);
            backtrack(i + 1, n, k, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        int n = 4, k = 2;
        List<List<Integer>> combos = combine(n, k);

        System.out.println("Combinations of " + k + " from [1.." + n + "] (Total: " + combos.size() + "):");
        System.out.println(combos);
    }
}

/*
 * Time Complexity: O(k * C(n, k)) where C(n, k) is the binomial coefficient n choose k.
 * Space Complexity: O(k) for the current combination buffer and recursion stack.
 */

/*
 * Problem Statement:
 * Find all valid combinations of k numbers that sum up to n such that the following
 * conditions are true:
 * - Only numbers 1 through 9 are used.
 * - Each number is used at most once.
 * Return a list of all possible valid combinations.
 * (LeetCode 216: Combination Sum III)
 * 
 * Example 1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 * 
 * Example 2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6],[1,3,5],[2,3,4]]
 * 
 * Asked in: Amazon, Google, Microsoft
 */

import java.util.ArrayList;
import java.util.List;

class CombinationSumThreeFixedK {

    public static List<List<Integer>> combinationSum3(int k, int n) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(k, n, 1, new ArrayList<>(), result);
        return result;
    }

    private static void backtrack(int k, int remain, int start, List<Integer> current, List<List<Integer>> result) {
        if (current.size() == k) {
            if (remain == 0) {
                result.add(new ArrayList<>(current));
            }
            return;
        }

        for (int i = start; i <= 9; i++) {
            if (i > remain) break; // Prune branch

            current.add(i);
            backtrack(k, remain - i, i + 1, current, result);
            current.remove(current.size() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        int k1 = 3, n1 = 7;
        System.out.printf("k = %d, n = %d -> %s%n", k1, n1, combinationSum3(k1, n1));

        int k2 = 3, n2 = 9;
        System.out.printf("k = %d, n = %d -> %s%n", k2, n2, combinationSum3(k2, n2));
    }
}

/*
 * Time Complexity: O(C(9, k) * k) - At most C(9, k) combinations explored.
 * Space Complexity: O(k) recursion stack frames.
 */

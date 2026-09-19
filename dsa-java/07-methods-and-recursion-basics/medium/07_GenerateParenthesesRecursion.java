/*
 * Problem Statement:
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 * 
 * Example 1:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 * 
 * Example 2:
 * Input: n = 1
 * Output: ["()"]
 * 
 * Asked in: Facebook/Meta, Amazon, Microsoft, Apple, Adobe
 */

import java.util.ArrayList;
import java.util.List;

class GenerateParenthesesRecursion {

    /**
     * Approach:
     * Backtracking with validity constraints:
     * Maintain count of open parentheses and close parentheses used so far.
     * Rules:
     * 1. Can add '(' if open < n.
     * 2. Can add ')' if close < open.
     * Base case: When string length reaches 2 * n, a valid combination is complete.
     */
    public static List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        backtrack(n, 0, 0, sb, result);
        return result;
    }

    private static void backtrack(int n, int open, int close, StringBuilder sb, List<String> result) {
        if (sb.length() == 2 * n) {
            result.add(sb.toString());
            return;
        }

        if (open < n) {
            sb.append('(');
            backtrack(n, open + 1, close, sb, result);
            sb.deleteCharAt(sb.length() - 1); // backtrack
        }

        if (close < open) {
            sb.append(')');
            backtrack(n, open, close + 1, sb, result);
            sb.deleteCharAt(sb.length() - 1); // backtrack
        }
    }

    public static void main(String[] args) {
        int n = 3;
        List<String> validCombos = generateParenthesis(n);

        System.out.println("--- Well-formed Parentheses for N = " + n + " ---");
        System.out.println("Total combinations (Catalan number C_3 = 5): " + validCombos.size());
        for (String s : validCombos) {
            System.out.println("  " + s);
        }

        System.out.println("\nTotal combinations for N = 4 (Catalan number C_4 = 14): " + generateParenthesis(4).size());
    }
}

/*
 * Time Complexity: O(4^N / sqrt(N)) - Proportional to N-th Catalan number C_N.
 * Space Complexity: O(N) - Maximum recursion depth is 2*N.
 */

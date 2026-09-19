/*
 * Problem Statement:
 * Given a string s that contains parentheses and letters, remove the minimum number
 * of invalid parentheses to make the input string valid.
 * Return a list of unique strings that are valid with the minimum number of removals.
 * You may return the answer in any order.
 * (LeetCode 301: Remove Invalid Parentheses)
 * 
 * Example 1:
 * Input: s = "()())()"
 * Output: ["(())()","()()()"]
 * 
 * Example 2:
 * Input: s = "(a)())()"
 * Output: ["(a())()","(a)()()"]
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
 */

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

class RemoveInvalidParenthesesBFSDFS {

    public static List<String> removeInvalidParentheses(String s) {
        // Step 1: Count minimum misplaced open and close parentheses
        int misOpen = 0;
        int misClose = 0;

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') {
                misOpen++;
            } else if (c == ')') {
                if (misOpen > 0) {
                    misOpen--;
                } else {
                    misClose++;
                }
            }
        }

        Set<String> result = new HashSet<>();
        StringBuilder sb = new StringBuilder();
        dfs(s, 0, 0, 0, misOpen, misClose, sb, result);
        return new ArrayList<>(result);
    }

    private static void dfs(String s, int index, int openCount, int closeCount,
                            int remOpen, int remClose,
                            StringBuilder current, Set<String> result) {
        if (index == s.length()) {
            if (remOpen == 0 && remClose == 0) {
                result.add(current.toString());
            }
            return;
        }

        char c = s.charAt(index);
        int len = current.length();

        // Option 1: Discard current parenthesis if it is eligible for removal
        if (c == '(' && remOpen > 0) {
            dfs(s, index + 1, openCount, closeCount, remOpen - 1, remClose, current, result);
        } else if (c == ')' && remClose > 0) {
            dfs(s, index + 1, openCount, closeCount, remOpen, remClose - 1, current, result);
        }

        // Option 2: Keep current character (must maintain valid prefix invariant closeCount <= openCount)
        current.append(c);
        if (c != '(' && c != ')') {
            dfs(s, index + 1, openCount, closeCount, remOpen, remClose, current, result);
        } else if (c == '(') {
            dfs(s, index + 1, openCount + 1, closeCount, remOpen, remClose, current, result);
        } else if (closeCount < openCount) {
            dfs(s, index + 1, openCount, closeCount + 1, remOpen, remClose, current, result);
        }
        current.setLength(len); // backtrack
    }

    public static void main(String[] args) {
        String s1 = "()())()";
        System.out.println("String: \"" + s1 + "\" -> Valid expressions: " + removeInvalidParentheses(s1));

        String s2 = "(a)())()";
        System.out.println("String: \"" + s2 + "\" -> Valid expressions: " + removeInvalidParentheses(s2));

        String s3 = ")(";
        System.out.println("String: \"" + s3 + "\" -> Valid expressions: " + removeInvalidParentheses(s3));
    }
}

/*
 * Time Complexity: O(2^N) bounded strictly by min invalid removals prune.
 * Space Complexity: O(N) recursion stack and StringBuilder buffer.
 */

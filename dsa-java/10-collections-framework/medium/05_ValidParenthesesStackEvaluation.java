/*
 * Problem Statement:
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 * 
 * Example 1:
 * Input: s = "()[]{}"
 * Output: true
 * 
 * Example 2:
 * Input: s = "(]"
 * Output: false
 * 
 * Asked in: Facebook/Meta, Amazon, Bloomberg, Microsoft, Google
 */

import java.util.ArrayDeque;
import java.util.Deque;

class ValidParenthesesStackEvaluation {

    /**
     * Approach:
     * Stack Matching:
     * When encountering an opening bracket, push the corresponding closing bracket onto stack.
     * When encountering a closing bracket, pop the stack and check if it matches.
     * If stack is empty when closing bracket arrives, or mismatch occurs -> invalid.
     * Final condition: Stack must be empty at the end.
     */
    public static boolean isValid(String s) {
        Deque<Character> stack = new ArrayDeque<>();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') {
                stack.push(')');
            } else if (c == '{') {
                stack.push('}');
            } else if (c == '[') {
                stack.push(']');
            } else {
                if (stack.isEmpty() || stack.pop() != c) {
                    return false;
                }
            }
        }

        return stack.isEmpty();
    }

    public static void main(String[] args) {
        String[] testCases = {"()", "()[]{}", "(]", "([)]", "{[]}", "(("};

        System.out.println("--- Valid Parentheses Evaluation ---");
        for (String test : testCases) {
            System.out.printf("Expression: %-8s -> Valid: %b%n", "\"" + test + "\"", isValid(test));
        }
    }
}

/*
 * Time Complexity: O(N) - Linear single pass over string.
 * Space Complexity: O(N) - Worst case stack depth for all opening brackets.
 */

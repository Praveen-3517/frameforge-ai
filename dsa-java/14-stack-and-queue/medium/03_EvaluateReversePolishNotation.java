/*
 * Problem Statement:
 * You are given an array of strings tokens that represents an arithmetic expression in a
 * Reverse Polish Notation (Postfix Notation).
 * Evaluate the expression. Return an integer that represents the value of the expression.
 * Supported operators: '+', '-', '*', and '/'. Division truncates toward zero.
 * (LeetCode 150: Evaluate Reverse Polish Notation)
 * 
 * Example:
 * Input: tokens = ["2","1","+","3","*"]
 * Output: 9 ((2 + 1) * 3 = 9)
 * 
 * Asked in: Amazon, Google, LinkedIn, Microsoft
 */

import java.util.ArrayDeque;
import java.util.Deque;

class EvaluateReversePolishNotation {

    public static int evalRPN(String[] tokens) {
        Deque<Integer> stack = new ArrayDeque<>();

        for (String token : tokens) {
            if (token.equals("+")) {
                stack.push(stack.pop() + stack.pop());
            } else if (token.equals("*")) {
                stack.push(stack.pop() * stack.pop());
            } else if (token.equals("-")) {
                int b = stack.pop();
                int a = stack.pop();
                stack.push(a - b);
            } else if (token.equals("/")) {
                int b = stack.pop();
                int a = stack.pop();
                stack.push(a / b);
            } else {
                stack.push(Integer.parseInt(token));
            }
        }

        return stack.pop();
    }

    public static void main(String[] args) {
        String[] expr1 = {"2", "1", "+", "3", "*"};
        System.out.println("[\"2\",\"1\",\"+\",\"3\",\"*\"] = " + evalRPN(expr1) + " (Expected: 9)");

        String[] expr2 = {"4", "13", "5", "/", "+"};
        System.out.println("[\"4\",\"13\",\"5\",\"/\",\"+\"] = " + evalRPN(expr2) + " (Expected: 6)");

        String[] expr3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
        System.out.println("Complex RPN expr = " + evalRPN(expr3) + " (Expected: 22)");
    }
}

/*
 * Time Complexity: O(N) linear pass over tokens.
 * Space Complexity: O(N) operand evaluation stack.
 */

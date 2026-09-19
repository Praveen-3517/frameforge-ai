import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem Statement:
 * You are given an array of strings `tokens` that represents an arithmetic expression
 * in a Reverse Polish Notation (Postfix notation).
 * Evaluate the expression. Return an integer that represents the value of the expression.
 * Operators: +, -, *, / (division truncates toward zero).
 * (LeetCode 150: Evaluate Reverse Polish Notation).
 *
 * Example:
 * ["2","1","+","3","*"] -> ((2 + 1) * 3) -> 9
 * ["4","13","5","/","+"] -> (4 + (13 / 5)) -> 6
 *
 * Asked in: Amazon, Google, Microsoft, LinkedIn
 *
 * Approach:
 * - Stack with String Switch Evaluation:
 *   Operands are pushed directly onto the stack.
 *   When an operator token is encountered:
 *   - Pop the right operand `b = stack.pop()`.
 *   - Pop the left operand `a = stack.pop()`.
 *   - Apply the switch expression:
 *       case "+" -> a + b
 *       case "-" -> a - b
 *       case "*" -> a * b
 *       case "/" -> a / b
 *   - Push the evaluated result back onto the stack.
 */
class EvaluateReversePolishNotation {

    public static int evalRPN(String[] tokens) {
        Deque<Integer> stack = new ArrayDeque<>();

        for (String token : tokens) {
            switch (token) {
                case "+" -> stack.push(stack.pop() + stack.pop());
                case "*" -> stack.push(stack.pop() * stack.pop());
                case "-" -> {
                    int b = stack.pop();
                    int a = stack.pop();
                    stack.push(a - b);
                }
                case "/" -> {
                    int b = stack.pop();
                    int a = stack.pop();
                    stack.push(a / b);
                }
                default -> stack.push(Integer.parseInt(token));
            }
        }

        return stack.pop();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 150: Evaluate Reverse Polish Notation ===");

        String[][] testExpressions = {
            { "2", "1", "+", "3", "*" },
            { "4", "13", "5", "/", "+" },
            { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" }
        };

        for (String[] expr : testExpressions) {
            int result = evalRPN(expr);
            System.out.printf("Tokens: %s%n ==> Evaluated Value: %d%n%n",
                    java.util.Arrays.toString(expr), result);
        }
    }
}

/*
 * Time Complexity: O(N) - Each token is processed once in constant time.
 * Space Complexity: O(N) - Stack storing operand values.
 */

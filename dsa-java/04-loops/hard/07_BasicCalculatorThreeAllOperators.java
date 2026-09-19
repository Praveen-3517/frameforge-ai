import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem Statement:
 * Implement a basic calculator to evaluate an expression string containing:
 *   - Non-negative integers
 *   - Basic operators: '+', '-', '*', '/'
 *   - Parentheses: '(' and ')'
 *   - Spaces: ' '
 * Integer division must truncate toward zero. Multiplication and division have higher precedence.
 * (LeetCode 772: Basic Calculator III - Hard).
 *
 * Asked in: Google, Amazon, Facebook / Meta, Uber
 *
 * Approach:
 * - Nested Scope Parsing Loop with Operator Stack:
 *   Use a helper method with a 1-element pointer array `int[] index` to parse sequentially:
 *   - `Deque<Integer> stack` stores operands at the current parenthesis level.
 *   - `char op = '+'` tracks the previous operator.
 *   - `int num = 0` accumulates digits.
 *   - When '(' is met: recursively evaluate the sub-expression until ')' is met.
 *   - When an operator (+, -, *, /) or ')' or end-of-string is met:
 *     - If `op == '+'`: `stack.push(num)`
 *     - If `op == '-'`: `stack.push(-num)`
 *     - If `op == '*'`: `stack.push(stack.pop() * num)` (immediate multiplication)
 *     - If `op == '/'`: `stack.push(stack.pop() / num)` (immediate division)
 *     Update `op = currentChar`, reset `num = 0`.
 *   - Sum all remaining items in the stack.
 */
class BasicCalculatorThreeAllOperators {

    public static int calculate(String s) {
        return parse(s, new int[] { 0 });
    }

    private static int parse(String s, int[] idx) {
        Deque<Integer> stack = new ArrayDeque<>();
        int num = 0;
        char op = '+';

        while (idx[0] < s.length()) {
            char ch = s.charAt(idx[0]++);

            if (Character.isDigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if (ch == '(') {
                // Recursively evaluate enclosed expression
                num = parse(s, idx);
            }

            // If an operator is reached, or closing ')', or end of string
            if ((!Character.isDigit(ch) && ch != ' ') || idx[0] == s.length()) {
                switch (op) {
                    case '+' -> stack.push(num);
                    case '-' -> stack.push(-num);
                    case '*' -> stack.push(stack.pop() * num);
                    case '/' -> stack.push(stack.pop() / num);
                }
                op = ch;
                num = 0;
            }

            if (ch == ')') {
                break; // Exit this parenthesis scope
            }
        }

        // Sum stack elements
        int total = 0;
        while (!stack.isEmpty()) {
            total += stack.pop();
        }
        return total;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 772: Basic Calculator III (+, -, *, /, Parentheses) ===");

        String[] testExpressions = {
            "1 + 1",
            " 6-4 / 2 ",
            "2*(5+5*2)/3+(6/2+8)",
            "(2+6* 3+5- (3*14/7+2)*5)+3",
            "0"
        };

        for (String expr : testExpressions) {
            int result = calculate(expr);
            System.out.printf("Expression: %-35s ==> Result: %d%n", "\"" + expr + "\"", result);
        }
    }
}

/*
 * Time Complexity: O(N) - Linear pass through characters.
 * Space Complexity: O(N) - Stack memory bounded by nesting depth and operators.
 */

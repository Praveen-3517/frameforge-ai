/*
 * Problem Statement:
 * You are given a string expression representing a Lisp-like expression to return the
 * integer value of it.
 * The syntax supports:
 * - let: `(let v1 e1 v2 e2 ... vn en expr)` binds variables in a new scope.
 * - add: `(add e1 e2)` returns sum of e1 and e2.
 * - mult: `(mult e1 e2)` returns product of e1 and e2.
 * 
 * Example:
 * Input: expression = "(let x 2 (mult x (let x 3 y 4 (add x y))))"
 * Output: 14  (outer x is 2; inner x is 3, y is 4 => 3 + 4 = 7 => 2 * 7 = 14)
 * 
 * Asked in: Google, Microsoft, Uber
 */

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class ParseLispExpressionRecursion {

    /**
     * Approach:
     * Recursive Descent Parsing with Scoped Symbol Tables:
     * - Pass a Map<String, Integer> representing the current variable scope.
     * - Split inner expression into tokens respecting nested parentheses.
     * - If token is "add": evaluate e1 + e2.
     * - If token is "mult": evaluate e1 * e2.
     * - If token is "let": create child scope clone, bind variables, evaluate final expr.
     */
    public static int evaluate(String expression) {
        return evalHelper(expression, new HashMap<>());
    }

    private static int evalHelper(String expr, Map<String, Integer> parentScope) {
        if (!expr.startsWith("(")) {
            // Either integer literal or variable identifier
            if (Character.isDigit(expr.charAt(0)) || expr.charAt(0) == '-') {
                return Integer.parseInt(expr);
            }
            return parentScope.get(expr);
        }

        // Strip outer '(' and ')'
        String inner = expr.substring(1, expr.length() - 1);
        List<String> tokens = parseTokens(inner);
        String command = tokens.get(0);

        if (command.equals("add")) {
            return evalHelper(tokens.get(1), parentScope) + evalHelper(tokens.get(2), parentScope);
        } else if (command.equals("mult")) {
            return evalHelper(tokens.get(1), parentScope) * evalHelper(tokens.get(2), parentScope);
        } else { // "let"
            Map<String, Integer> currentScope = new HashMap<>(parentScope);
            for (int i = 1; i < tokens.size() - 1; i += 2) {
                String var = tokens.get(i);
                int val = evalHelper(tokens.get(i + 1), currentScope);
                currentScope.put(var, val);
            }
            // Evaluate the trailing return expression in this scope
            return evalHelper(tokens.get(tokens.size() - 1), currentScope);
        }
    }

    private static List<String> parseTokens(String s) {
        List<String> tokens = new ArrayList<>();
        int bal = 0;
        StringBuilder current = new StringBuilder();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(') bal++;
            else if (c == ')') bal--;

            if (bal == 0 && c == ' ') {
                if (current.length() > 0) {
                    tokens.add(current.toString());
                    current.setLength(0);
                }
            } else {
                current.append(c);
            }
        }
        if (current.length() > 0) tokens.add(current.toString());
        return tokens;
    }

    public static void main(String[] args) {
        String[] exprs = {
            "(add 1 2)",
            "(mult 3 (add 2 3))",
            "(let x 2 (mult x 5))",
            "(let x 2 (mult x (let x 3 y 4 (add x y))))",
            "(let a1 3 b2 (add a1 1) b2)"
        };

        System.out.println("--- Lisp-Like Expression Evaluator ---");
        for (String exp : exprs) {
            System.out.printf("%-45s = %d%n", exp, evaluate(exp));
        }
    }
}

/*
 * Time Complexity: O(N^2) worst case due to string tokenization and scope cloning.
 * Space Complexity: O(N) for recursive evaluation stack and nested symbol tables.
 */

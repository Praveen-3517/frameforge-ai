import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Problem Statement:
 * Given a string `expression` representing a Lisp-like expression, evaluate and return its integer value.
 * Syntactic Forms:
 *   - Integer literal: e.g. "3", "-12"
 *   - Variable name: e.g. "x", "a"
 *   - `(let v1 e1 v2 e2 ... vn en expr)`: binds variables in a local lexical scope and returns `expr`.
 *   - `(add e1 e2)`: evaluates and returns `e1 + e2`.
 *   - `(mult e1 e2)`: evaluates and returns `e1 * e2`.
 * (LeetCode 736: Parse Lisp Expression - Hard).
 *
 * Asked in: Google, Airbnb, Bloomberg
 *
 * Approach:
 * - Recursive Descent Parser with Lexical Scoping:
 *   Use a helper `eval(String expr, Map<String, Integer> scope)`:
 *   1. Atomic Check:
 *      If `expr` doesn't start with '(', it is either an integer or variable:
 *      - If it starts with digit or '-', parse with `Integer.parseInt(expr)`.
 *      - Otherwise, look up variable name in current `scope`.
 *   2. Compound Expressions:
 *      Strip outer parentheses: `expr.substring(expr.startsWith("(add") ? 5 : ...)`
 *      Tokenize sub-expressions by respecting parenthesis depth.
 *   3. Command Switch:
 *      - "add" -> eval(token1) + eval(token2)
 *      - "mult" -> eval(token1) * eval(token2)
 *      - "let" -> clone scope for nested bindings, bind variables iteratively, evaluate trailing expression.
 */
class ParseLispExpression {

    public static int evaluate(String expression) {
        return eval(expression, new HashMap<>());
    }

    private static int eval(String expr, Map<String, Integer> parentScope) {
        // Base Case 1: Atomic expression (literal or variable)
        if (!expr.startsWith("(")) {
            char first = expr.charAt(0);
            if (Character.isDigit(first) || first == '-') {
                return Integer.parseInt(expr);
            }
            return parentScope.get(expr);
        }

        // Strip outer '(' and ')'
        String body = expr.substring(1, expr.length() - 1);

        if (body.startsWith("add ")) {
            List<String> tokens = parseTokens(body.substring(4));
            return eval(tokens.get(0), parentScope) + eval(tokens.get(1), parentScope);
        } else if (body.startsWith("mult ")) {
            List<String> tokens = parseTokens(body.substring(5));
            return eval(tokens.get(0), parentScope) * eval(tokens.get(1), parentScope);
        } else {
            // "let " command: create a new lexical scope inherited from parent
            Map<String, Integer> localScope = new HashMap<>(parentScope);
            List<String> tokens = parseTokens(body.substring(4));

            // Bind variable-value pairs (tokens.size() - 1 is the return expression)
            for (int i = 0; i < tokens.size() - 1; i += 2) {
                String var = tokens.get(i);
                int val = eval(tokens.get(i + 1), localScope);
                localScope.put(var, val);
            }

            // Evaluate trailing return expression
            return eval(tokens.get(tokens.size() - 1), localScope);
        }
    }

    // Tokenize space-separated tokens while keeping nested "(...)" together
    private static List<String> parseTokens(String s) {
        List<String> tokens = new ArrayList<>();
        int depth = 0;
        StringBuilder current = new StringBuilder();

        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            if (ch == '(') depth++;
            if (ch == ')') depth--;

            if (ch == ' ' && depth == 0) {
                tokens.add(current.toString());
                current.setLength(0);
            } else {
                current.append(ch);
            }
        }
        if (current.length() > 0) {
            tokens.add(current.toString());
        }

        return tokens;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 736: Parse Lisp Expression (Lexical Scoping & AST) ===");

        String[] testExpressions = {
            "(let x 2 (mult x 5))",
            "(let x 3 x 2 x)",
            "(let x 1 y 2 (add x y))",
            "(let x 2 (add (let x 3 (let x 4 x)) x))",
            "(let a1 3 b2 (add a1 1) b2)"
        };

        for (String expr : testExpressions) {
            int val = evaluate(expr);
            System.out.printf("Expression: %-42s ==> Result: %d%n", expr, val);
        }
    }
}

/*
 * Time Complexity: O(N^2) where N is expression length (due to substring slicing and tokenizing).
 * Space Complexity: O(N) - Recursion depth and scope environment maps.
 */

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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

/**
     * Approach:
     * Recursive Descent Parsing with Scoped Symbol Tables:
     * - Pass a Map<const char*, int> representing the current variable scope.
     * - Split inner expression into tokens respecting nested parentheses.
     * - If token is "add": evaluate e1 + e2.
     * - If token is "mult": evaluate e1 * e2.
     * - If token is "let": create child scope clone, bind variables, evaluate const expr.
     */
    int evaluate(const char* expression) {
        return evalHelper(expression, new HashMap<>());
    }

    static int evalHelper(const char* expr, Map<const char*, int> parentScope) {
        if (!expr.startsWith("(")) {
            // Either integer literal or variable identifier
            if (isdigit(expr[0]) || expr[0] == '-') {
                return int.parseInt(expr);
            }
            return parentScope.get(expr);
        }

        // Strip outer '(' and ')'
        const char* inner = expr.substring(1, ((int)strlen(expr)) - 1);
        int* tokens = parseTokens(inner);
        const char* command = tokens.get(0);

        if ((strcmp(command, "add") == 0)) {
            return evalHelper(tokens.get(1), parentScope) + evalHelper(tokens.get(2), parentScope);
        } else if ((strcmp(command, "mult") == 0)) {
            return evalHelper(tokens.get(1), parentScope) * evalHelper(tokens.get(2), parentScope);
        } else { // "let"
            Map<const char*, int> currentScope = new HashMap<>(parentScope);
            for (int i = 1; i < tokens.size() - 1; i += 2) {
                const char* var = tokens.get(i);
                int val = evalHelper(tokens.get(i + 1), currentScope);
                currentScope.put(var, val);
            }
            // Evaluate the trailing return expression in this scope
            return evalHelper(tokens.get(tokens.size() - 1), currentScope);
        }
    }

    static int* parseTokens(const char* s) {
        int* tokens = new ArrayList<>();
        int bal = 0;
        StringBuilder current = new StringBuilder();

        for (int i = 0; i < ((int)strlen(s)); i++) {
            char c = s[i];
            if (c == '(') bal++;
            else if (c == ')') bal--;

            if (bal == 0 && c == ' ') {
                if (((int)strlen(current)) > 0) {
                    tokens.add(current.toString());
                    current.setLength(0);
                }
            } else {
                current.append(c);
            }
        }
        if (((int)strlen(current)) > 0) tokens.add(current.toString());
        return tokens;
    }

    int main(void) {
        const char*[] exprs = {
            "(add 1 2)",
            "(mult 3 (add 2 3))",
            "(let x 2 (mult x 5))",
            "(let x 2 (mult x (let x 3 y 4 (add x y))))",
            "(let a1 3 b2 (add a1 1) b2)"
        };

        printf("--- Lisp-Like Expression Evaluator ---\n");
        for (const char* exp : exprs) {
            printf("%-45s = %d\n", exp, evaluate(exp));
        }
        return 0;
}

/*
 * Time Complexity: O(N^2) worst case due to string tokenization and scope cloning.
 * Space Complexity: O(N) for recursive evaluation stack and nested symbol tables.
 */

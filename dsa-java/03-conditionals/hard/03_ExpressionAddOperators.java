import java.util.ArrayList;
import java.util.List;

/**
 * Problem Statement:
 * Given a string `num` that contains only digits and an integer `target`, return all possibilities
 * to insert the binary operators '+', '-', and/or '*' between the digits of `num` so that the
 * resultant expression evaluates to `target`.
 * Operands cannot contain leading zeros (e.g. "1 + 05" is invalid).
 * (LeetCode 282: Expression Add Operators - Hard).
 *
 * Asked in: Facebook / Meta, Google, Amazon, Microsoft
 *
 * Approach:
 * - Backtracking with Operator Precedence Conditionals:
 *   Explore every possible substring `num[index..i]` as the next integer operand.
 *   - Guard against leading zeroes: if `num.charAt(index) == '0' && i > index`, stop expanding!
 *   At index == 0 (first operand):
 *     No operator is placed in front; path begins with the number.
 *   At index > 0:
 *     Branch into 3 operator choices:
 *     1. '+' Addition:
 *        `backtrack(i + 1, path + "+" + curr, eval + curr, curr)`
 *     2. '-' Subtraction:
 *        `backtrack(i + 1, path + "-" + curr, eval - curr, -curr)`
 *     3. '*' Multiplication (Precedence Trick):
 *        Multiplication takes precedence over prior additions/subtractions!
 *        Undo the effect of the previous operand:
 *        `eval - prevOperand + (prevOperand * curr)`
 *        The new `prevOperand` becomes `prevOperand * curr`!
 */
class ExpressionAddOperators {

    public static List<String> addOperators(String num, int target) {
        List<String> result = new ArrayList<>();
        if (num == null || num.isEmpty()) return result;
        backtrack(num, target, 0, 0, 0, new StringBuilder(), result);
        return result;
    }

    private static void backtrack(String num, long target, int index, long eval, long prevOperand,
                                  StringBuilder path, List<String> result) {
        if (index == num.length()) {
            if (eval == target) {
                result.add(path.toString());
            }
            return;
        }

        int len = path.length();

        for (int i = index; i < num.length(); i++) {
            // Conditional Guard: Disallow multi-digit numbers with leading zeros (e.g. "05")
            if (i != index && num.charAt(index) == '0') {
                break;
            }

            String part = num.substring(index, i + 1);
            long curr = Long.parseLong(part);

            if (index == 0) {
                // First operand has no operator prefix
                path.append(part);
                backtrack(num, target, i + 1, curr, curr, path, result);
                path.setLength(len);
            } else {
                // Choice 1: Addition '+'
                path.append('+').append(part);
                backtrack(num, target, i + 1, eval + curr, curr, path, result);
                path.setLength(len);

                // Choice 2: Subtraction '-'
                path.append('-').append(part);
                backtrack(num, target, i + 1, eval - curr, -curr, path, result);
                path.setLength(len);

                // Choice 3: Multiplication '*' (Precedence Correction)
                path.append('*').append(part);
                backtrack(num, target, i + 1, eval - prevOperand + (prevOperand * curr),
                          prevOperand * curr, path, result);
                path.setLength(len);
            }
        }
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 282: Expression Add Operators (Backtracking + Precedence) ===");

        String[][] testCases = {
            { "123", "6" },
            { "232", "8" },
            { "105", "5" },
            { "00", "0" }
        };

        for (String[] tc : testCases) {
            String num = tc[0];
            int target = Integer.parseInt(tc[1]);
            List<String> expressions = addOperators(num, target);
            System.out.printf("Num: %-5s | Target: %2d ==> Valid Expressions (%d): %s%n",
                    num, target, expressions.size(), expressions);
        }
    }
}

/*
 * Time Complexity: O(4^N) - In each position we can branch into 4 choices (no-op/concat, +, -, *).
 * Space Complexity: O(N) - Recursion stack depth and path StringBuilder.
 */

/*
 * Problem Statement:
 * Given a string num that contains only digits and an integer target,
 * return all possibilities to insert the binary operators '+', '-', and/or '*'
 * between the digits of num so that the resultant expression evaluates to the target value.
 * Operands must not contain leading zeros (e.g., "05" is invalid).
 * 
 * Example 1:
 * Input: num = "123", target = 6
 * Output: ["1*2*3","1+2+3"]
 * 
 * Example 2:
 * Input: num = "232", target = 8
 * Output: ["2*3+2","2+3*2"]
 * 
 * Asked in: Facebook/Meta, Google, Amazon, Microsoft
 */

import java.util.ArrayList;
import java.util.List;

class ExpressionAddOperatorsRecursion {

    /**
     * Approach:
     * Backtracking with Operator Precedence Management:
     * To handle multiplication precedence correctly:
     * Keep track of:
     * - current calculated value (calcVal)
     * - previous operand (prevOperand)
     * 
     * When multiplying:
     * newCalc = calcVal - prevOperand + (prevOperand * currNum)
     * newPrev = prevOperand * currNum
     */
    public static List<String> addOperators(String num, int target) {
        List<String> result = new ArrayList<>();
        if (num == null || num.isEmpty()) return result;
        backtrack(num, target, 0, 0, 0, new StringBuilder(), result);
        return result;
    }

    private static void backtrack(String num, int target, int index,
                                  long calcVal, long prevOperand,
                                  StringBuilder sb, List<String> result) {
        if (index == num.length()) {
            if (calcVal == target) {
                result.add(sb.toString());
            }
            return;
        }

        long currVal = 0;
        int lenBefore = sb.length();

        for (int i = index; i < num.length(); i++) {
            // Disallow leading zeros for multi-digit numbers
            if (i > index && num.charAt(index) == '0') break;

            currVal = currVal * 10 + (num.charAt(i) - '0');

            if (index == 0) {
                // First number, no operator prefix
                sb.append(currVal);
                backtrack(num, target, i + 1, currVal, currVal, sb, result);
                sb.setLength(lenBefore);
            } else {
                // Addition
                sb.append('+').append(currVal);
                backtrack(num, target, i + 1, calcVal + currVal, currVal, sb, result);
                sb.setLength(lenBefore);

                // Subtraction
                sb.append('-').append(currVal);
                backtrack(num, target, i + 1, calcVal - currVal, -currVal, sb, result);
                sb.setLength(lenBefore);

                // Multiplication (precedence adjustment)
                sb.append('*').append(currVal);
                backtrack(num, target, i + 1,
                        calcVal - prevOperand + (prevOperand * currVal),
                        prevOperand * currVal,
                        sb, result);
                sb.setLength(lenBefore);
            }
        }
    }

    public static void main(String[] args) {
        String num1 = "123";
        int target1 = 6;
        System.out.println("num: " + num1 + ", target: " + target1);
        System.out.println("Result: " + addOperators(num1, target1));

        String num2 = "232";
        int target2 = 8;
        System.out.println("\nnum: " + num2 + ", target: " + target2);
        System.out.println("Result: " + addOperators(num2, target2));

        String num3 = "105";
        int target3 = 5;
        System.out.println("\nnum: " + num3 + ", target: " + target3);
        System.out.println("Result: " + addOperators(num3, target3));
    }
}

/*
 * Time Complexity: O(4^N) where N is the length of digits string (at each gap: none, +, -, *).
 * Space Complexity: O(N) for StringBuilder and recursion stack.
 */

import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem Statement:
 * Given a string `s` containing just the characters '(', ')', '{', '}', '[' and ']',
 * determine if the input string is valid.
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 * (LeetCode 20: Valid Parentheses).
 *
 * Asked in: Amazon, Google, Facebook / Meta, Microsoft, TCS
 *
 * Approach:
 * - Stack with Character Matching Switch:
 *   Iterate through each character in the string:
 *   - When encountering an opening bracket '(', '{', or '[', push the EXPECTED closing bracket onto the stack.
 *   - When encountering a closing bracket, compare it directly with the popped character from the stack!
 *   - If stack is empty when closing bracket arrives, or popped char != current char, string is invalid.
 *   - At the end of the string, the stack must be completely empty.
 */
class ValidParenthesesSimpleSwitch {

    public static boolean isValid(String s) {
        if (s == null || (s.length() & 1) == 1) {
            return false; // Odd length strings can never be balanced
        }

        Deque<Character> stack = new ArrayDeque<>();

        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);

            switch (ch) {
                case '(' -> stack.push(')');
                case '{' -> stack.push('}');
                case '[' -> stack.push(']');
                case ')', '}', ']' -> {
                    if (stack.isEmpty() || stack.pop() != ch) {
                        return false;
                    }
                }
                default -> {
                    // Ignore non-bracket characters if present
                }
            }
        }

        return stack.isEmpty();
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 20: Valid Parentheses (Switch + Stack) ===");

        String[] testStrings = {
            "()",
            "()[]{}",
            "(]",
            "([)]",
            "{[]}",
            "((((((",
            "",
            "}{"
        };

        for (String str : testStrings) {
            System.out.printf("String: %-10s ==> Is Valid: %s%n", "\"" + str + "\"", isValid(str));
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through string of length N.
 * Space Complexity: O(N) - Stack storing up to N opening brackets.
 */

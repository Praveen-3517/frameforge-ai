/*
 * Problem Statement:
 * Given a string s of lower and upper case English letters.
 * A good string is a string which doesn't have two adjacent characters s[i] and s[i + 1]
 * where:
 * 0 <= i <= s.length() - 2
 * s[i] is a lower-case letter and s[i + 1] is the same letter but in upper-case or vice-versa.
 * To make the string good, you can choose two adjacent letters that make the string bad
 * and remove them. You can keep doing this until the string becomes good.
 * Return the string after making it good.
 * (LeetCode 1544: Make The String Great)
 * 
 * Example:
 * Input: s = "leEeetcode"
 * Output: "leetcode" (Removing 'eE' leaves "leetcode")
 * 
 * Asked in: Google, Amazon, Bloomberg
 */

import java.util.ArrayDeque;
import java.util.Deque;

class MakeStringGreatAdjacentRemoval {

    public static String makeGood(String s) {
        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (!stack.isEmpty() && Math.abs(stack.peek() - c) == 32) {
                // Difference between lowercase and uppercase in ASCII is exactly 32 ('a' - 'A' = 32)
                stack.pop();
            } else {
                stack.push(c);
            }
        }

        StringBuilder sb = new StringBuilder();
        while (!stack.isEmpty()) {
            sb.append(stack.pollLast()); // Poll from bottom to preserve forward order
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        String[] tests = {"leEeetcode", "abBAcC", "s"};

        System.out.println("--- Make String Great Adjacent Removals ---");
        for (String t : tests) {
            System.out.printf("Original: %-12s -> Made Good: \"%s\"%n", "\"" + t + "\"", makeGood(t));
        }
    }
}

/*
 * Time Complexity: O(N) single pass through the string.
 * Space Complexity: O(N) stack storage.
 */

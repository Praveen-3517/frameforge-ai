/*
 * Problem Statement:
 * Given two strings s and t, return true if they are equal when both are typed into empty
 * text editors. '#' means a backspace character.
 * Note that after backspacing an empty text, the text will continue empty.
 * (LeetCode 844: Backspace String Compare)
 * 
 * Example 1:
 * Input: s = "ab#c", t = "ad#c"
 * Output: true (Both become "ac")
 * 
 * Example 2:
 * Input: s = "ab##", t = "c#d#"
 * Output: true (Both become "")
 * 
 * Asked in: Google, Facebook/Meta, Amazon, Microsoft
 */

import java.util.ArrayDeque;
import java.util.Deque;

class BackspaceStringCompare {

    public static boolean backspaceCompare(String s, String t) {
        return build(s).equals(build(t));
    }

    private static String build(String str) {
        Deque<Character> stack = new ArrayDeque<>();
        for (char c : str.toCharArray()) {
            if (c != '#') {
                stack.push(c);
            } else if (!stack.isEmpty()) {
                stack.pop();
            }
        }
        return String.valueOf(stack);
    }

    public static void main(String[] args) {
        String s1 = "ab#c", t1 = "ad#c";
        System.out.printf("s = \"%s\", t = \"%s\" -> Equal? %b%n", s1, t1, backspaceCompare(s1, t1));

        String s2 = "ab##", t2 = "c#d#";
        System.out.printf("s = \"%s\", t = \"%s\" -> Equal? %b%n", s2, t2, backspaceCompare(s2, t2));

        String s3 = "a#c", t3 = "b";
        System.out.printf("s = \"%s\", t = \"%s\" -> Equal? %b%n", s3, t3, backspaceCompare(s3, t3));
    }
}

/*
 * Time Complexity: O(N + M) where N and M are string lengths.
 * Space Complexity: O(N + M) stack space.
 */

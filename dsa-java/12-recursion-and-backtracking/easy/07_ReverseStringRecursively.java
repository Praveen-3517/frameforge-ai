/*
 * Problem Statement:
 * Write a function that reverses a string. The input string is given as an array
 * of characters s. You must do this by modifying the input array in-place with
 * O(1) extra memory using recursion.
 * (LeetCode 344: Reverse String)
 * 
 * Example:
 * Input: s = ["h","e","l","l","o"]
 * Output: ["o","l","l","e","h"]
 * 
 * Asked in: Apple, Microsoft, Amazon, Adobe
 */

import java.util.Arrays;

class ReverseStringRecursively {

    public static void reverseString(char[] s) {
        helper(s, 0, s.length - 1);
    }

    private static void helper(char[] s, int left, int right) {
        if (left >= right) return;

        // Swap ends
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        // Recurse towards center
        helper(s, left + 1, right - 1);
    }

    public static void main(String[] args) {
        char[] s1 = {'h', 'e', 'l', 'l', 'o'};
        System.out.println("Original: " + Arrays.toString(s1));
        reverseString(s1);
        System.out.println("Reversed: " + Arrays.toString(s1));

        char[] s2 = {'H', 'a', 'n', 'n', 'a', 'h'};
        System.out.println("\nOriginal: " + Arrays.toString(s2));
        reverseString(s2);
        System.out.println("Reversed: " + Arrays.toString(s2));
    }
}

/*
 * Time Complexity: O(N) - N/2 recursive swap steps.
 * Space Complexity: O(N) recursion stack frames.
 */

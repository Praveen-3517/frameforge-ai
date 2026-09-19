import java.util.ArrayDeque;
import java.util.Deque;

/**
 * Problem Statement:
 * 1. Reverse a character array in-place without allocating extra space (LeetCode 344).
 * 2. Reverse words in a string: Given an input string `s`, reverse the order of the words.
 *    A word is defined as a sequence of non-space characters. The words in `s` will be
 *    separated by at least one space. Return a string with words in reverse order joined by a single space,
 *    stripping all leading, trailing, and duplicate spaces (LeetCode 151: Reverse Words in a String).
 *
 * Example:
 * "the sky is blue" -> "blue is sky the"
 * "  hello world  " -> "world hello"
 *
 * Asked in: Amazon, Microsoft, Apple, Cisco
 *
 * Approach:
 * - Part 1: In-Place Two Pointers:
 *   Swap `s[left]` and `s[right]` moving towards center.
 * - Part 2: Two-Pointer Word Scanning:
 *   Traverse backwards from end of string to beginning.
 *   Skip spaces. When a word is found, find its start, extract substring, append to `StringBuilder`.
 */
class ReverseStringAndWords {

    // LeetCode 344: Reverse String in-place
    public static void reverseString(char[] s) {
        int left = 0, right = s.length - 1;
        while (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }

    // LeetCode 151: Reverse Words in a String
    public static String reverseWords(String s) {
        StringBuilder result = new StringBuilder();
        int n = s.length();
        int i = n - 1;

        while (i >= 0) {
            // Skip trailing spaces
            while (i >= 0 && s.charAt(i) == ' ') {
                i--;
            }
            if (i < 0) break;

            // Find start of current word
            int j = i;
            while (i >= 0 && s.charAt(i) != ' ') {
                i--;
            }

            // Word is from index i + 1 to j
            if (result.length() > 0) {
                result.append(" ");
            }
            result.append(s, i + 1, j + 1);
        }

        return result.toString();
    }

    public static void main(String[] args) {
        System.out.println("=== Reverse String & Reverse Words in a String ===");

        char[] chars = "hello".toCharArray();
        reverseString(chars);
        System.out.println("Reverse String (\"hello\"): " + new String(chars));

        String[] testPhrases = {
            "the sky is blue",
            "  hello world  ",
            "a good   example"
        };

        for (String phrase : testPhrases) {
            System.out.printf("Original: \"%-18s\" ==> Reversed: \"%s\"%n",
                    phrase, reverseWords(phrase));
        }
    }
}

/*
 * Time Complexity: O(N) - Linear pass through string characters.
 * Space Complexity: O(N) - Output string builder.
 */

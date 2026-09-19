/**
 * Problem Statement:
 * Given a string `s` consisting of words and spaces, return the length of the last word in the string.
 * A word is a maximal substring consisting of non-space characters only.
 * (LeetCode 58: Length of Last Word).
 *
 * Example:
 * s = "Hello World"                 -> 5
 * s = "   fly me   to   the moon  " -> 4
 * s = "luffy is still joyboy"       -> 6
 *
 * Asked in: Apple, Adobe, Amazon, Cisco
 *
 * Approach:
 * - Backward Traversal (O(N) Worst Case, O(1) Space):
 *   1. Start from the end of the string `i = s.length() - 1`.
 *   2. Decrement `i` to skip any trailing whitespace: `while (i >= 0 && s.charAt(i) == ' ') i--;`
 *   3. Count non-whitespace characters until the next space or start of string is reached:
 *      `while (i >= 0 && s.charAt(i) != ' ') { length++; i--; }`
 *   4. Return `length`.
 */
class LengthOfLastWord {

    public static int lengthOfLastWord(String s) {
        if (s == null || s.isEmpty()) return 0;

        int i = s.length() - 1;
        int length = 0;

        // Skip trailing spaces
        while (i >= 0 && s.charAt(i) == ' ') {
            i--;
        }

        // Count characters of the last word
        while (i >= 0 && s.charAt(i) != ' ') {
            length++;
            i--;
        }

        return length;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 58: Length of Last Word (Backward Scan) ===");

        String[] testStrings = {
            "Hello World",
            "   fly me   to   the moon  ",
            "luffy is still joyboy",
            "a",
            "    day    "
        };

        for (String str : testStrings) {
            System.out.printf("String: %-30s ==> Last Word Length: %d%n",
                    "\"" + str + "\"", lengthOfLastWord(str));
        }
    }
}

/*
 * Time Complexity: O(N) - Backward scan stops as soon as the last word is counted.
 * Space Complexity: O(1) - Constant stack registers.
 */

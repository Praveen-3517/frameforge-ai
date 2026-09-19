/**
 * Problem Statement:
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
 * and removing all non-alphanumeric characters, it reads the same forward and backward.
 * Given a string `s`, return true if it is a palindrome, or false otherwise.
 * (LeetCode 125: Valid Palindrome).
 *
 * Example:
 * "A man, a plan, a canal: Panama" -> true ("amanaplanacanalpanama")
 * "race a car"                     -> false
 *
 * Asked in: Facebook / Meta, Microsoft, Amazon, Apple
 *
 * Approach:
 * - Two-Pointer In-Place Validation (O(N) Time, O(1) Space):
 *   Initialize `left = 0` and `right = s.length() - 1`.
 *   - While `left < right`:
 *     - If `s[left]` is not letter or digit: advance `left++`.
 *     - If `s[right]` is not letter or digit: decrement `right--`.
 *     - When both point to valid alphanumeric characters:
 *       Compare case-insensitively using `Character.toLowerCase()`.
 *       If they differ, return false immediately!
 *       Advance `left++`, decrement `right--`.
 *   - Return true if pointers cross without mismatch.
 */
class ValidPalindromeSimple {

    public static boolean isPalindrome(String s) {
        if (s == null) return false;

        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Skip non-alphanumeric characters from left
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }

            // Skip non-alphanumeric characters from right
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }

            // Compare case-insensitively
            char c1 = Character.toLowerCase(s.charAt(left));
            char c2 = Character.toLowerCase(s.charAt(right));

            if (c1 != c2) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 125: Valid Palindrome (Two-Pointer O(1) Space) ===");

        String[] testPhrases = {
            "A man, a plan, a canal: Panama",
            "race a car",
            " ",
            "0P",
            "No 'x' in Nixon"
        };

        for (String p : testPhrases) {
            System.out.printf("Phrase: %-35s ==> Is Palindrome: %s%n",
                    "\"" + p + "\"", isPalindrome(p));
        }
    }
}

/*
 * Time Complexity: O(N) - Linear pass through the string.
 * Space Complexity: O(1) - Constant stack registers; does not allocate filtered string.
 */

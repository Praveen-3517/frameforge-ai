/*
 * Problem Statement:
 * Given a string s, determine if it is a palindrome using recursion:
 * - A palindrome reads the same backwards as forwards.
 * - Ignore non-alphanumeric characters and case sensitivity.
 * (LeetCode 125: Valid Palindrome recursive formulation)
 * 
 * Example:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 * 
 * Asked in: Facebook/Meta, Microsoft, Amazon, Cisco
 */

class RecursivelyCheckPalindrome {

    public static boolean isPalindrome(String s) {
        if (s == null) return false;
        return check(s, 0, s.length() - 1);
    }

    private static boolean check(String s, int left, int right) {
        if (left >= right) return true;

        char c1 = s.charAt(left);
        char c2 = s.charAt(right);

        // Skip non-alphanumeric from left
        if (!Character.isLetterOrDigit(c1)) {
            return check(s, left + 1, right);
        }

        // Skip non-alphanumeric from right
        if (!Character.isLetterOrDigit(c2)) {
            return check(s, left, right - 1);
        }

        // Compare case-insensitively
        if (Character.toLowerCase(c1) != Character.toLowerCase(c2)) {
            return false;
        }

        return check(s, left + 1, right - 1);
    }

    public static void main(String[] args) {
        String[] tests = {
            "A man, a plan, a canal: Panama",
            "race a car",
            " ",
            "Madam, I'm Adam"
        };

        System.out.println("--- Recursive Palindrome Verification ---");
        for (String t : tests) {
            System.out.printf("String: %-32s -> Palindrome: %b%n", "\"" + t + "\"", isPalindrome(t));
        }
    }
}

/*
 * Time Complexity: O(N) where N is string length.
 * Space Complexity: O(N) recursion stack frames.
 */

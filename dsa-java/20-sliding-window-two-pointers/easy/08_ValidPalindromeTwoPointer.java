/**
 * Problem: Check If a String Is a Valid Palindrome (LeetCode 125)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Facebook, Amazon, Google, Microsoft, Apple
 * 
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase letters
 * and removing all non-alphanumeric characters, it reads the same forward and backward.
 * 
 * Approach - Opposite End Two Pointers:
 * Skip non-alphanumeric characters from both ends.
 * Compare lowercase versions of the characters pointed to by left and right.
 * If they differ, not a palindrome.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class ValidPalindromeTwoPointer {

    public static boolean isPalindrome(String s) {
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }

            if (Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    public static void main(String[] args) {
        System.out.println(isPalindrome("A man, a plan, a canal: Panama") + " (Expected: true)");
        System.out.println(isPalindrome("race a car") + " (Expected: false)");
        System.out.println(isPalindrome(" ") + " (Expected: true)");
    }
}

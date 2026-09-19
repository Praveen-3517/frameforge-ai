/**
 * Problem: Reverse String (LeetCode 344)
 * Category: Two Pointers (Opposite Ends) | Easy
 * Asked in: Google, Amazon, Facebook, Microsoft
 * 
 * Write a function that reverses a string. The input string is given as an array of characters.
 * Must do it in-place with O(1) extra memory.
 * 
 * Approach - Opposite-End Swap:
 * Place left and right pointers at each end.
 * Swap their characters and move pointers inward until they meet.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
class ReverseStringInPlaceTwoPointer {

    public static void reverseString(char[] s) {
        int left = 0;
        int right = s.length - 1;

        while (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }

    public static void main(String[] args) {
        char[] s1 = {'h', 'e', 'l', 'l', 'o'};
        reverseString(s1);
        System.out.println(new String(s1) + " (Expected: olleh)");

        char[] s2 = {'H', 'a', 'n', 'n', 'a', 'h'};
        reverseString(s2);
        System.out.println(new String(s2) + " (Expected: hannaH)");
    }
}

import java.util.HashSet;
import java.util.Set;

/**
 * Problem: Longest Substring Without Repeating Characters (LeetCode 3)
 * Category: Variable Sliding Window | Medium
 * Asked in: Amazon, Bloomberg, Google, Apple, Microsoft, Facebook
 * 
 * Given a string s, find the length of the longest substring without repeating characters.
 * 
 * Approach - Variable Window + HashSet:
 * Maintain a sliding window [left, right] with no duplicates using a HashSet.
 * Expand right. If s[right] already in set, shrink from left until it's gone.
 * Track max window size.
 * 
 * Time Complexity: O(N) - each character enters and leaves the window at most once.
 * Space Complexity: O(min(N, charset_size))
 */
class LongestSubstringWithoutRepeatingChars {

    public static int lengthOfLongestSubstring(String s) {
        Set<Character> window = new HashSet<>();
        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);

            while (window.contains(c)) {
                window.remove(s.charAt(left++));
            }

            window.add(c);
            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }

    public static void main(String[] args) {
        System.out.println(lengthOfLongestSubstring("abcabcbb") + " (Expected: 3)"); // "abc"
        System.out.println(lengthOfLongestSubstring("bbbbb") + " (Expected: 1)");    // "b"
        System.out.println(lengthOfLongestSubstring("pwwkew") + " (Expected: 3)");   // "wke"
        System.out.println(lengthOfLongestSubstring("") + " (Expected: 0)");
    }
}

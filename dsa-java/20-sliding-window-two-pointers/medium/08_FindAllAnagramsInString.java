import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Problem: Find All Anagrams in a String (LeetCode 438)
 * Category: Fixed Sliding Window | Medium
 * Asked in: Amazon, Facebook, Google, Bloomberg, Apple
 * 
 * Given two strings s and p, return an array of all the start indices of p's anagrams in s.
 * You may return the answer in any order.
 * 
 * Approach - Fixed Window Frequency Count:
 * Build freq array for p.
 * Slide window of size p.length() over s, maintaining freq array for current window.
 * When both freq arrays match, record left start index.
 * 
 * Time Complexity: O(N) where N = s.length()
 * Space Complexity: O(1) - fixed 26-size arrays
 */
class FindAllAnagramsInString {

    public static List<Integer> findAnagrams(String s, String p) {
        List<Integer> result = new ArrayList<>();
        if (s.length() < p.length()) return result;

        int[] pFreq = new int[26];
        int[] windowFreq = new int[26];

        for (char c : p.toCharArray()) pFreq[c - 'a']++;

        int k = p.length();

        for (int i = 0; i < s.length(); i++) {
            windowFreq[s.charAt(i) - 'a']++;

            if (i >= k) {
                windowFreq[s.charAt(i - k) - 'a']--;
            }

            if (i >= k - 1 && Arrays.equals(pFreq, windowFreq)) {
                result.add(i - k + 1);
            }
        }

        return result;
    }

    public static void main(String[] args) {
        System.out.println(findAnagrams("cbaebabacd", "abc") + " (Expected: [0, 6])");
        // "cba" at index 0, "bac" at index 6
        System.out.println(findAnagrams("abab", "ab") + " (Expected: [0, 1, 2])");
    }
}

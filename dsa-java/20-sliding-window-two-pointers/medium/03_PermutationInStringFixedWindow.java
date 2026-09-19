import java.util.Arrays;

/**
 * Problem: Permutation in String (LeetCode 567)
 * Category: Fixed Sliding Window | Medium
 * Asked in: Amazon, Google, Apple, Bloomberg, Microsoft
 * 
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1,
 * or false otherwise. In other words, return true if one of s1's permutations
 * is a substring of s2.
 * 
 * Approach - Fixed Window Frequency Matching:
 * Maintain a frequency map for s1 and a sliding window of size s1.length() over s2.
 * At each step, compare the two frequency arrays.
 * Arrays.equals() in O(26) = O(1) time.
 * 
 * Time Complexity: O(N) where N = s2.length()
 * Space Complexity: O(1) - fixed size of 26.
 */
class PermutationInStringFixedWindow {

    public static boolean checkInclusion(String s1, String s2) {
        if (s1.length() > s2.length()) return false;

        int[] s1Freq = new int[26];
        int[] windowFreq = new int[26];

        for (char c : s1.toCharArray()) s1Freq[c - 'a']++;

        int k = s1.length();

        for (int i = 0; i < s2.length(); i++) {
            windowFreq[s2.charAt(i) - 'a']++;

            if (i >= k) {
                windowFreq[s2.charAt(i - k) - 'a']--;
            }

            if (i >= k - 1 && Arrays.equals(s1Freq, windowFreq)) {
                return true;
            }
        }

        return false;
    }

    public static void main(String[] args) {
        System.out.println(checkInclusion("ab", "eidbaooo") + " (Expected: true)");  // "ba" is perm of "ab"
        System.out.println(checkInclusion("ab", "eidboaoo") + " (Expected: false)");
        System.out.println(checkInclusion("adc", "dcda") + " (Expected: true)");     // "dca" or "cda"
    }
}

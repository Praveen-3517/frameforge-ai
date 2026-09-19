import java.util.HashMap;
import java.util.Map;

/**
 * Problem: Minimum Window Substring (LeetCode 76)
 * Category: Variable Sliding Window | Medium/Hard
 * Asked in: Amazon, Facebook, Google, Apple, Bloomberg, Microsoft
 * 
 * Given two strings s and t of lengths m and n respectively, return the minimum window
 * substring of s such that every character in t (including duplicates) is included in the window.
 * If there is no such substring, return the empty string "".
 * 
 * Approach - Variable Window with Need/Have Counter:
 * `need`: number of distinct characters in t that still need to be satisfied.
 * `windowFreq`: frequency of characters in current window.
 * Expand: include s[right]. If windowFreq[c] == tFreq[c], one need satisfied.
 * Once need == 0: record window size; shrink from left.
 *   When shrinking removes a needed char (windowFreq[c] < tFreq[c]), increment need.
 * 
 * Time Complexity: O(N + M) where N = s.length, M = t.length
 * Space Complexity: O(M) for frequency maps.
 */
class MinimumWindowSubstringVariableWindow {

    public static String minWindow(String s, String t) {
        Map<Character, Integer> tFreq = new HashMap<>();
        for (char c : t.toCharArray()) {
            tFreq.merge(c, 1, Integer::sum);
        }

        int need = tFreq.size(); // number of unique chars in t yet to be satisfied
        int left = 0;
        int minStart = 0;
        int minLength = Integer.MAX_VALUE;
        Map<Character, Integer> windowFreq = new HashMap<>();

        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            windowFreq.merge(c, 1, Integer::sum);

            if (tFreq.containsKey(c) && windowFreq.get(c).equals(tFreq.get(c))) {
                need--;
            }

            while (need == 0) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minStart = left;
                }

                char leftChar = s.charAt(left++);
                windowFreq.merge(leftChar, -1, Integer::sum);

                if (tFreq.containsKey(leftChar) && windowFreq.get(leftChar) < tFreq.get(leftChar)) {
                    need++;
                }
            }
        }

        return minLength == Integer.MAX_VALUE ? "" : s.substring(minStart, minStart + minLength);
    }

    public static void main(String[] args) {
        System.out.println(minWindow("ADOBECODEBANC", "ABC") + " (Expected: BANC)");
        System.out.println(minWindow("a", "a") + " (Expected: a)");
        System.out.println(minWindow("a", "aa") + " (Expected: empty string)");
    }
}

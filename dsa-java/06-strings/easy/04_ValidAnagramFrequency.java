import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 * Given two strings `s` and `t`, return true if `t` is an anagram of `s`, and false otherwise.
 * An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
 * using all the original letters exactly once.
 * (LeetCode 242: Valid Anagram).
 *
 * Example:
 * s = "anagram", t = "nagaram" -> true
 * s = "rat", t = "car"         -> false
 *
 * Asked in: Google, Amazon, Bloomberg, Microsoft, Uber
 *
 * Approach:
 * - 26-Element Frequency Bucket (O(N) Time, O(1) Space):
 *   If strings differ in length, they cannot be anagrams.
 *   Maintain `int[] count = new int[26]`:
 *   Increment for each char in `s`: `count[s.charAt(i) - 'a']++`.
 *   Decrement for each char in `t`: `count[t.charAt(i) - 'a']--`.
 *   If all bucket counts return to 0, `s` and `t` are anagrams!
 * - Unicode Extension:
 *   For arbitrary Unicode characters beyond lowercase English 'a'-'z', use a `HashMap<Character, Integer>`.
 */
class ValidAnagramFrequency {

    // Fast O(1) space bucket for English lowercase letters
    public static boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) return false;

        int[] count = new int[26];

        for (int i = 0; i < s.length(); i++) {
            count[s.charAt(i) - 'a']++;
            count[t.charAt(i) - 'a']--;
        }

        for (int c : count) {
            if (c != 0) return false;
        }

        return true;
    }

    // Generalized solution for arbitrary Unicode characters
    public static boolean isAnagramUnicode(String s, String t) {
        if (s.length() != t.length()) return false;

        Map<Character, Integer> map = new HashMap<>();

        for (int i = 0; i < s.length(); i++) {
            char cs = s.charAt(i);
            char ct = t.charAt(i);
            map.put(cs, map.getOrDefault(cs, 0) + 1);
            map.put(ct, map.getOrDefault(ct, 0) - 1);
        }

        for (int val : map.values()) {
            if (val != 0) return false;
        }

        return true;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 242: Valid Anagram (Frequency Bucket & Unicode Map) ===");

        String[][] testPairs = {
            { "anagram", "nagaram" },
            { "rat", "car" },
            { "listen", "silent" },
            { "aacc", "ccac" }
        };

        for (String[] pair : testPairs) {
            boolean ans = isAnagram(pair[0], pair[1]);
            System.out.printf("'%s' vs '%s' ==> Anagram: %s%n", pair[0], pair[1], ans);
        }
    }
}

/*
 * Time Complexity: O(N) - Single pass through both strings of length N.
 * Space Complexity: O(1) - Fixed 26-integer bucket array (or O(U) for Unicode map).
 */

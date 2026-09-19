/**
 * Problem Statement:
 * Given a string `s`, find the first non-repeating character in it and return its index.
 * If it does not exist, return -1.
 * (LeetCode 387: First Unique Character in a String).
 *
 * Example:
 * s = "leetcode"     -> Output: 0 (character 'l')
 * s = "loveleetcode" -> Output: 2 (character 'v')
 * s = "aabb"         -> Output: -1
 *
 * Asked in: Amazon, Microsoft, Bloomberg, Apple, Google
 *
 * Approach:
 * - Two-Pass Frequency Array (O(N) Time, O(1) Space):
 *   1. Pass 1: Count frequency of each character in a 26-element array `freq[c - 'a']++`.
 *   2. Pass 2: Iterate through the string from left to right.
 *      Return the first index `i` where `freq[s.charAt(i) - 'a'] == 1`.
 *   3. If no character has frequency 1, return -1.
 */
class FirstUniqueCharacterInString {

    public static int firstUniqChar(String s) {
        if (s == null || s.isEmpty()) return -1;

        int[] freq = new int[26];

        // Pass 1: Build frequency map
        for (int i = 0; i < s.length(); i++) {
            freq[s.charAt(i) - 'a']++;
        }

        // Pass 2: Find first character with count 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s.charAt(i) - 'a'] == 1) {
                return i;
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 387: First Unique Character in a String ===");

        String[] testStrings = { "leetcode", "loveleetcode", "aabb", "z", "racecar" };

        for (String str : testStrings) {
            int idx = firstUniqChar(str);
            System.out.printf("String: %-15s ==> Index: %2d (Char: %s)%n",
                    "\"" + str + "\"", idx, (idx != -1 ? "'" + str.charAt(idx) + "'" : "None"));
        }
    }
}

/*
 * Time Complexity: O(N) - Two passes through the string.
 * Space Complexity: O(1) - Fixed 26-element frequency bucket.
 */

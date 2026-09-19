import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Problem Statement:
 * Given an array of strings `strs`, group the anagrams together. You can return the answer in any order.
 * (LeetCode 49: Group Anagrams).
 *
 * Example:
 * strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Asked in: Amazon, Facebook / Meta, Microsoft, Apple, Google
 *
 * Approach:
 * - Method 1: Canonical Sorted String as Hash Key (O(N * K log K)):
 *   Two strings are anagrams if and only if their sorted character representations are identical.
 *   - Sort chars of each string: `char[] ca = s.toCharArray(); Arrays.sort(ca);`
 *   - Use `new String(ca)` as the key in `Map<String, List<String>>`.
 * - Method 2: 26-Element Frequency Tuple Key (O(N * K)):
 *   Count frequencies of 26 letters and format as a key: `"#1#0#2#0..."`.
 *   Bypasses `K log K` character sorting.
 */
class GroupAnagramsCanonical {

    public static List<List<String>> groupAnagrams(String[] strs) {
        if (strs == null || strs.length == 0) return new ArrayList<>();

        Map<String, List<String>> map = new HashMap<>();

        for (String s : strs) {
            char[] ca = s.toCharArray();
            Arrays.sort(ca);
            String key = new String(ca);

            map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(map.values());
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 49: Group Anagrams (Canonical Keys) ===");

        String[] strs = { "eat", "tea", "tan", "ate", "nat", "bat" };
        List<List<String>> groups = groupAnagrams(strs);

        System.out.println("Input: " + Arrays.toString(strs));
        System.out.println("Grouped Anagrams:");
        for (List<String> group : groups) {
            System.out.println("  " + group);
        }
    }
}

/*
 * Time Complexity: O(N * K log K) where N is the number of strings and K is the maximum length of a string.
 * Space Complexity: O(N * K) - Storage for map entries and result list.
 */

/*
 * Problem Statement:
 * Given an array of strings strs, group the anagrams together.
 * You can return the answer in any order.
 * An Anagram is a word formed by rearranging the letters of a different word.
 * 
 * Example:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 * 
 * Asked in: Amazon, Facebook/Meta, Apple, Google, Microsoft
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class GroupAnagramsCategorization {

    /**
     * Approach:
     * Canonical Signature Hashing:
     * For each word, sort its characters to form a canonical key (e.g., "eat" -> "aet").
     * Words that are anagrams map to the exact same key.
     * Store words in Map<String, List<String>> keyed by this canonical signature.
     */
    public static List<List<String>> groupAnagrams(String[] strs) {
        if (strs == null || strs.length == 0) return new ArrayList<>();

        Map<String, List<String>> map = new HashMap<>();

        for (String s : strs) {
            char[] ca = s.toCharArray();
            Arrays.sort(ca);
            String key = String.valueOf(ca);

            map.computeIfAbsent(key, k -> new ArrayList<>()).add(s);
        }

        return new ArrayList<>(map.values());
    }

    public static void main(String[] args) {
        String[] words = {"eat", "tea", "tan", "ate", "nat", "bat"};
        List<List<String>> grouped = groupAnagrams(words);

        System.out.println("Original words: " + Arrays.toString(words));
        System.out.println("Grouped Anagrams (" + grouped.size() + " groups):");
        for (List<String> group : grouped) {
            System.out.println("  " + group);
        }
    }
}

/*
 * Time Complexity: O(N * K log K) where N is words count, K is max length of a string.
 * Space Complexity: O(N * K) to hold anagram groups in hash map.
 */

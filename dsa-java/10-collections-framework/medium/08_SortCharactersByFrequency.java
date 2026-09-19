/*
 * Problem Statement:
 * Given a string s, sort it in decreasing order based on the frequency of the characters.
 * The frequency of a character is the number of times it appears in the string.
 * Return the sorted string. If there are multiple answers, return any of them.
 * 
 * Example 1:
 * Input: s = "tree"
 * Output: "eert" (or "eetr")
 * 
 * Example 2:
 * Input: s = "cccaaa"
 * Output: "aaaccc" (or "cccaaa")
 * 
 * Asked in: Amazon, Bloomberg, Microsoft, Google
 */

import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

class SortCharactersByFrequency {

    /**
     * Approach:
     * 1. Count character frequencies into a HashMap.
     * 2. Populate a Max-Heap PriorityQueue comparing counts in descending order.
     * 3. Poll from Max-Heap and append character count times to StringBuilder.
     */
    public static String frequencySort(String s) {
        Map<Character, Integer> counts = new HashMap<>();
        for (char c : s.toCharArray()) {
            counts.merge(c, 1, Integer::sum);
        }

        PriorityQueue<Character> maxHeap = new PriorityQueue<>(
                (a, b) -> Integer.compare(counts.get(b), counts.get(a))
        );
        maxHeap.addAll(counts.keySet());

        StringBuilder sb = new StringBuilder();
        while (!maxHeap.isEmpty()) {
            char c = maxHeap.poll();
            int freq = counts.get(c);
            for (int i = 0; i < freq; i++) {
                sb.append(c);
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        String[] testStrings = {"tree", "cccaaa", "Aabb"};

        System.out.println("--- Sort Characters By Frequency ---");
        for (String s : testStrings) {
            System.out.printf("Original: %-8s -> Sorted: %s%n", "\"" + s + "\"", frequencySort(s));
        }
    }
}

/*
 * Time Complexity: O(N log U) where N is string length, U is unique character count (at most 128/256).
 * Space Complexity: O(N) for StringBuilder and frequency counts.
 */

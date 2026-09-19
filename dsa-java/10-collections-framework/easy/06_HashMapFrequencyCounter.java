/*
 * Problem Statement:
 * Demonstrate frequency counting and Map manipulation idioms with `java.util.HashMap`:
 * - Using `getOrDefault`, `putIfAbsent`, and `merge` to count word frequencies.
 * - Iterating using `entrySet()`, `keySet()`, and `values()`.
 * - Finding the most frequent element.
 * 
 * Asked in: Amazon, Microsoft, Google, TCS
 */

import java.util.HashMap;
import java.util.Map;

class HashMapFrequencyCounter {

    public static Map<String, Integer> countFrequencies(String[] words) {
        Map<String, Integer> freqMap = new HashMap<>();

        for (String word : words) {
            // Idiom 1: getOrDefault
            // freqMap.put(word, freqMap.getOrDefault(word, 0) + 1);

            // Idiom 2: merge (atomic and clean)
            freqMap.merge(word, 1, Integer::sum);
        }

        return freqMap;
    }

    public static void main(String[] args) {
        String sentence = "the quick brown fox jumps over the lazy dog and the quick fox";
        String[] tokens = sentence.split(" ");

        Map<String, Integer> counts = countFrequencies(tokens);

        System.out.println("--- Word Frequency Distribution ---");
        String maxWord = null;
        int maxCount = 0;

        for (Map.Entry<String, Integer> entry : counts.entrySet()) {
            System.out.printf("  %-8s : %d%n", entry.getKey(), entry.getValue());
            if (entry.getValue() > maxCount) {
                maxCount = entry.getValue();
                maxWord = entry.getKey();
            }
        }

        System.out.println("\nMost frequent word: '" + maxWord + "' with " + maxCount + " occurrences.");
    }
}

/*
 * Time Complexity: O(N) where N is number of tokens. O(1) average hash lookup.
 * Space Complexity: O(U) where U is unique word count.
 */

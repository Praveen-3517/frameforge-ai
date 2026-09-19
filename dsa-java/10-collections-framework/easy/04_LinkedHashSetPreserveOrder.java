/*
 * Problem Statement:
 * Demonstrate `java.util.LinkedHashSet` for preserving insertion order while maintaining
 * uniqueness:
 * - Contrast iteration order between standard `HashSet` (non-deterministic bucket order)
 *   and `LinkedHashSet` (guaranteed predictable FIFO insertion order).
 * - Remove duplicates from an input array while preserving the original sequence of first occurrences.
 * 
 * Asked in: Oracle, Cisco, Walmart, Morgan Stanley
 */

import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

class LinkedHashSetPreserveOrder {

    public static List<Integer> deduplicatePreserveOrder(int[] arr) {
        Set<Integer> orderedSet = new LinkedHashSet<>();
        for (int num : arr) {
            orderedSet.add(num);
        }
        return new ArrayList<>(orderedSet);
    }

    public static void main(String[] args) {
        int[] input = {9, 2, 5, 2, 8, 9, 1, 5, 3};

        System.out.println("--- Preserving Order while Deduplicating ---");
        System.out.println("Original array: [9, 2, 5, 2, 8, 9, 1, 5, 3]");

        Set<Integer> hashSet = new HashSet<>();
        for (int x : input) hashSet.add(x);
        System.out.println("Standard HashSet (arbitrary order):     " + hashSet);

        Set<Integer> linkedHashSet = new LinkedHashSet<>();
        for (int x : input) linkedHashSet.add(x);
        System.out.println("LinkedHashSet (exact insertion order):   " + linkedHashSet);

        List<Integer> deduplicated = deduplicatePreserveOrder(input);
        System.out.println("Preserved order list:                   " + deduplicated);
    }
}

/*
 * Time Complexity: O(N) to process N elements with O(1) hash lookups.
 * Space Complexity: O(U) where U is number of unique elements stored.
 */

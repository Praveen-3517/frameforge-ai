/*
 * Problem Statement:
 * Demonstrate `java.util.HashSet` for distinct element tracking and mathematical set algebra:
 * - Constant time O(1) membership testing (contains).
 * - Deduplicating a collection with duplicate entries.
 * - Set Operations:
 *   - Union: `setA.addAll(setB)`
 *   - Intersection: `setA.retainAll(setB)`
 *   - Difference: `setA.removeAll(setB)`
 * 
 * Asked in: Amazon, Microsoft, Infosys, Capgemini
 */

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class HashSetUniqueElements {

    public static void main(String[] args) {
        String[] fruitsWithDuplicates = {"Apple", "Banana", "Apple", "Orange", "Banana", "Mango"};
        Set<String> uniqueFruits = new HashSet<>(Arrays.asList(fruitsWithDuplicates));

        System.out.println("--- Deduplication with HashSet ---");
        System.out.println("Original array count: " + fruitsWithDuplicates.length);
        System.out.println("Unique fruits count:   " + uniqueFruits.size());
        System.out.println("Unique set: " + uniqueFruits);
        System.out.println("Contains 'Mango'? " + uniqueFruits.contains("Mango"));

        // Mathematical Set Operations
        Set<Integer> setA = new HashSet<>(Arrays.asList(1, 2, 3, 4, 5));
        Set<Integer> setB = new HashSet<>(Arrays.asList(4, 5, 6, 7, 8));

        // Union
        Set<Integer> union = new HashSet<>(setA);
        union.addAll(setB);
        System.out.println("\n--- Set Algebra ---");
        System.out.println("Set A: " + setA);
        System.out.println("Set B: " + setB);
        System.out.println("Union (A ∪ B):        " + union);

        // Intersection
        Set<Integer> intersection = new HashSet<>(setA);
        intersection.retainAll(setB);
        System.out.println("Intersection (A ∩ B): " + intersection);

        // Difference
        Set<Integer> difference = new HashSet<>(setA);
        difference.removeAll(setB);
        System.out.println("Difference (A - B):   " + difference);
    }
}

/*
 * Time Complexity: O(1) average for add, remove, contains; O(N + M) for union/intersection/difference.
 * Space Complexity: O(N) where N is number of unique elements.
 */

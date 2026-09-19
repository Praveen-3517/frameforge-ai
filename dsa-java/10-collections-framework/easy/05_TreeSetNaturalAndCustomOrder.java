/*
 * Problem Statement:
 * Demonstrate `java.util.TreeSet` (Red-Black Tree sorted set):
 * - Natural ascending sort vs custom Comparator (e.g. descending or by length).
 * - NavigableSet methods:
 *   - `first()`, `last()`
 *   - `ceiling(e)`: least element >= e
 *   - `floor(e)`: greatest element <= e
 *   - `subSet(from, to)`, `headSet(to)`, `tailSet(from)`
 * 
 * Asked in: Amazon, Goldman Sachs, Google, Adobe
 */

import java.util.Comparator;
import java.util.TreeSet;

class TreeSetNaturalAndCustomOrder {

    public static void main(String[] args) {
        // 1. Natural Sort Order
        TreeSet<Integer> scores = new TreeSet<>();
        scores.add(85);
        scores.add(42);
        scores.add(99);
        scores.add(73);
        scores.add(60);

        System.out.println("--- 1. TreeSet Natural Ordering (Red-Black Tree) ---");
        System.out.println("Sorted scores: " + scores);
        System.out.println("Lowest:  " + scores.first() + ", Highest: " + scores.last());
        System.out.println("Ceiling for 70 (>= 70): " + scores.ceiling(70));
        System.out.println("Floor for 70 (<= 70):   " + scores.floor(70));
        System.out.println("SubSet [50, 90):        " + scores.subSet(50, 90));

        // 2. Custom Comparator Ordering (Sort strings by length, then alphabetically)
        Comparator<String> lengthThenAlpha = Comparator
                .comparingInt(String::length)
                .thenComparing(Comparator.naturalOrder());

        TreeSet<String> words = new TreeSet<>(lengthThenAlpha);
        words.add("banana");
        words.add("fig");
        words.add("apple");
        words.add("kiwi");
        words.add("pear");

        System.out.println("\n--- 2. Custom Comparator (Length then Alphabetical) ---");
        System.out.println("Ordered words: " + words);
    }
}

/*
 * Time Complexity: O(log N) for add, remove, contains, ceiling, floor.
 * Space Complexity: O(N) red-black tree node allocation.
 */

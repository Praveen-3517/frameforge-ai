/*
 * Problem Statement:
 * Demonstrate all core operations and traversal idioms on `java.util.ArrayList`:
 * - Dynamic resizing, adding elements at specific indices.
 * - Element updates (set), lookups (get, indexOf, contains), and removal (by index vs object).
 * - Traversal methods: standard for-loop, enhanced for-each loop, Iterator with safe removal,
 *   and Java 8 `forEach` with lambda.
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
 */

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

class ArrayListOperationsAndTraversal {

    public static void main(String[] args) {
        List<String> languages = new ArrayList<>();

        // Adding elements
        languages.add("Java");
        languages.add("Python");
        languages.add("C++");
        languages.add(1, "Kotlin"); // Insert at index 1

        System.out.println("--- Initial List ---");
        System.out.println(languages + " (Size: " + languages.size() + ")");

        // Access and modification
        System.out.println("Element at index 2: " + languages.get(2));
        languages.set(2, "Rust"); // Replace element at index 2
        System.out.println("After set(2, 'Rust'): " + languages);

        // Safe removal during traversal using Iterator
        System.out.println("\n--- Safe Removal with Iterator ---");
        Iterator<String> it = languages.iterator();
        while (it.hasNext()) {
            String item = it.next();
            if (item.startsWith("C")) {
                it.remove(); // Safely removes "C++" without ConcurrentModificationException
            }
        }
        System.out.println("After removing elements starting with 'C': " + languages);

        // Functional forEach traversal
        System.out.println("\n--- Traversing via Java 8 forEach ---");
        languages.forEach(lang -> System.out.println("  Language: " + lang));
    }
}

/*
 * Time Complexity: get(i): O(1), set(i): O(1), add(e): O(1) amortized, remove/add(index): O(N).
 * Space Complexity: O(N) where N is number of stored elements.
 */

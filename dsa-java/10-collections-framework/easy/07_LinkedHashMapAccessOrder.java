/*
 * Problem Statement:
 * Demonstrate `java.util.LinkedHashMap` in Access-Order Mode:
 * - By default, LinkedHashMap maintains insertion order.
 * - By passing `true` for `accessOrder` in constructor:
 *   `new LinkedHashMap<>(capacity, loadFactor, true);`
 *   accessing an element via `get()` or `put()` moves it to the tail (most recently used).
 * - Show how this built-in capability forms the bedrock of an LRU Cache.
 * 
 * Asked in: Amazon, Oracle, Bloomberg, LinkedIn
 */

import java.util.LinkedHashMap;
import java.util.Map;

class LinkedHashMapAccessOrder {

    public static void main(String[] args) {
        // initialCapacity = 16, loadFactor = 0.75f, accessOrder = true
        LinkedHashMap<String, Integer> cache = new LinkedHashMap<>(16, 0.75f, true);

        cache.put("A", 1);
        cache.put("B", 2);
        cache.put("C", 3);
        cache.put("D", 4);

        System.out.println("--- Initial State (Insertion Order) ---");
        System.out.println("Order (Head -> Tail): " + cache.keySet());

        // Access 'B'
        System.out.println("\nAccessing key 'B' -> " + cache.get("B"));
        System.out.println("After accessing 'B':  " + cache.keySet() + " ('B' moved to end/MRU)");

        // Access 'A'
        System.out.println("\nAccessing key 'A' -> " + cache.get("A"));
        System.out.println("After accessing 'A':  " + cache.keySet() + " ('A' moved to end/MRU)");

        // Put updates an existing entry
        cache.put("C", 30);
        System.out.println("\nUpdated key 'C' -> 30");
        System.out.println("After updating 'C':   " + cache.keySet() + " ('C' moved to end/MRU)");

        System.out.println("\nNotice: Head of map is key 'D', which is now the LEAST recently used!");
    }
}

/*
 * Time Complexity: O(1) for put, get, and node repositioning in doubly linked list.
 * Space Complexity: O(N) map entries + doubly linked pointers.
 */

/*
 * Problem Statement:
 * Design a Least Recently Used (LRU) Cache by subclassing `java.util.LinkedHashMap`:
 * - Implement get(key) and put(key, value) in O(1) time.
 * - Override `protected boolean removeEldestEntry(Map.Entry<K, V> eldest)` to evict
 *   the oldest entry automatically when size exceeds capacity.
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Apple, Google
 */

import java.util.LinkedHashMap;
import java.util.Map;

class LRUCacheLinkedHashMap {

    static class LRUCache<K, V> extends LinkedHashMap<K, V> {
        private final int capacity;

        public LRUCache(int capacity) {
            // initialCapacity = capacity, loadFactor = 0.75f, accessOrder = true
            super(capacity, 0.75f, true);
            this.capacity = capacity;
        }

        @Override
        protected boolean removeEldestEntry(Map.Entry<K, V> eldest) {
            // Automatically invoked by put() and putAll()
            return size() > capacity;
        }

        public V getValue(K key) {
            return super.getOrDefault(key, null);
        }
    }

    public static void main(String[] args) {
        LRUCache<Integer, String> cache = new LRUCache<>(3);

        System.out.println("--- LRU Cache via LinkedHashMap Subclassing (Capacity = 3) ---");
        cache.put(1, "Data 1");
        cache.put(2, "Data 2");
        cache.put(3, "Data 3");
        System.out.println("Initial entries: " + cache);

        // Access key 1 -> marks 1 as most recently used
        cache.getValue(1);
        System.out.println("After accessing key 1: " + cache);

        // Put key 4 -> exceeds capacity 3, evicts key 2 (least recently used)!
        cache.put(4, "Data 4");
        System.out.println("After putting key 4 (evicts 2): " + cache);
        System.out.println("Key 2 present? " + cache.containsKey(2));
    }
}

/*
 * Time Complexity: O(1) for get, put, and automatic eviction.
 * Space Complexity: O(capacity) for hash entries and doubly linked list pointers.
 */

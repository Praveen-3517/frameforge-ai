/*
 * Problem Statement:
 * Design a Least Recently Used (LRU) Cache by subclassing `java.util.LinkedHashMap`:
 * - Implement get(key) and put(key, value) in O(1) time.
 * - Override `protected boolean removeEldestEntry(Map.Entry<K, V> eldest)` to evict
 *   the oldest entry automatically when size exceeds capacity.
 * 
 * Asked in: Amazon, Microsoft, Facebook/Meta, Apple, Google
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

static class LRUCache<K, V> extends LinkedHashMap<K, V> {
        static const int capacity;

        LRUCache(int capacity) {
            // initialCapacity = capacity, loadFactor = 0.75f, accessOrder = true
            super(capacity, 0.75f, true);
            this.capacity = capacity;
        }

        bool removeEldestEntry(Map.Entry<K, V> eldest) {
            // Automatically invoked by put() and putAll()
            return size() > capacity;
        }

        V getValue(K key) {
            return super.getOrDefault(key, NULL);
        }
    }

    int main(void) {
        LRUCache<int, const char*> cache = new LRUCache<>(3);

        printf("--- LRU Cache via LinkedHashMap Subclassing (Capacity = 3) ---\n");
        cache.put(1, "Data 1");
        cache.put(2, "Data 2");
        cache.put(3, "Data 3");
        printf("Initial entries: %d\n", cache);

        // Access key 1 -> marks 1 as most recently used
        cache.getValue(1);
        printf("After accessing key 1: %d\n", cache);

        // Put key 4 -> exceeds capacity 3, evicts key 2 (least recently used)!
        cache.put(4, "Data 4");
        printf("After putting key 4 (evicts 2): %d\n", cache);
        printf("Key 2 present? %d\n", cache.containsKey(2));
        return 0;
}

/*
 * Time Complexity: O(1) for get, put, and automatic eviction.
 * Space Complexity: O(capacity) for hash entries and doubly linked list pointers.
 */

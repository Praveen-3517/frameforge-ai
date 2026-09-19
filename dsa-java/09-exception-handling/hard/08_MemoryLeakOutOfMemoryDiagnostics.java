/*
 * Problem Statement:
 * Diagnose and Recover from Memory Exhaustion Patterns:
 * - Difference between OutOfMemoryError (fatal JVM error) and catchable memory exceptions.
 * - Demonstrate using WeakReference and SoftReference to implement memory-sensitive caches
 *   that allow the Garbage Collector to reclaim heap when under memory pressure.
 * - Prevent OutOfMemoryError before it crashes the application.
 * 
 * Asked in: Google, Oracle, LinkedIn, Amazon
 */

import java.lang.ref.SoftReference;
import java.util.HashMap;
import java.util.Map;

class MemoryLeakOutOfMemoryDiagnostics {

    // Memory-sensitive cache backed by SoftReference
    static class SoftMemoryCache<K, V> {
        private final Map<K, SoftReference<V>> cache = new HashMap<>();

        public void put(K key, V value) {
            cache.put(key, new SoftReference<>(value));
        }

        public V get(K key) {
            SoftReference<V> ref = cache.get(key);
            if (ref == null) return null;

            V val = ref.get();
            if (val == null) {
                // Object was reclaimed by GC during memory pressure!
                cache.remove(key);
                System.out.println("  [GC Reclamation] Key '" + key + "' was cleared by Garbage Collector.");
            }
            return val;
        }

        public int size() {
            return cache.size();
        }
    }

    public static void main(String[] args) {
        System.out.println("--- SoftReference Memory-Sensitive Cache Demonstration ---");

        SoftMemoryCache<String, byte[]> memoryCache = new SoftMemoryCache<>();

        // Add large binary arrays (1 MB each)
        for (int i = 1; i <= 5; i++) {
            byte[] largeBlock = new byte[1024 * 1024]; // 1 MB
            memoryCache.put("block_" + i, largeBlock);
            System.out.println("Cached block #" + i + " (1 MB)");
        }

        System.out.println("\nInitial cache entries count: " + memoryCache.size());

        // Probe entries
        for (int i = 1; i <= 5; i++) {
            byte[] block = memoryCache.get("block_" + i);
            System.out.printf("Block #%d present in memory: %b%n", i, (block != null));
        }

        // Trigger garbage collection request
        System.gc();
        System.out.println("\nSystem.gc() requested. SoftReferences protect against OOM while keeping heap flexible.");
    }
}

/*
 * Time Complexity: O(1) for put and get in soft cache.
 * Space Complexity: Dynamic heap sizing determined by GC pressure.
 */

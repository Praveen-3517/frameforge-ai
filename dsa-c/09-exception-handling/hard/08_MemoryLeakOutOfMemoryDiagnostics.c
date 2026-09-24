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

// Memory-sensitive cache backed by SoftReference
    static class SoftMemoryCache<K, V> {
        static const Map<K, SoftReference<V>> cache = new HashMap<>();

        void put(K key, V value) {
            cache.put(key, new SoftReference<>(value));
        }

        V get(K key) {
            SoftReference<V> ref = cache.get(key);
            if (ref == NULL) return NULL;

            V val = ref.get();
            if (val == NULL) {
                // Object was reclaimed by GC during memory pressure!
                cache.remove(key);
                printf("  [GC Reclamation] Key '" + key + "' was cleared by Garbage Collector.\n");
            }
            return val;
        }

        int size() {
            return cache.size();
        }
    }

    int main(void) {
        printf("--- SoftReference Memory-Sensitive Cache Demonstration ---\n");

        SoftMemoryCache<const char*, signed char[]> memoryCache = new SoftMemoryCache<>();

        // Add large binary arrays (1 MB each)
        for (int i = 1; i <= 5; i++) {
            signed char[] largeBlock = (signed char*)malloc((1024 * 1024) * sizeof(signed char)); // 1 MB
            memoryCache.put("block_" + i, largeBlock);
            printf("Cached block #" + i + " (1 MB)\n");
        }

        printf("\nInitial cache entries count: %d\n", memoryCache.size());

        // Probe entries
        for (int i = 1; i <= 5; i++) {
            signed char[] block = memoryCache.get("block_" + i);
            printf("Block #%d present in memory: %b\n", i, (block != NULL));
        }

        // Trigger garbage collection request
        System.gc();
        printf("\nSystem.gc() requested. SoftReferences protect against OOM while keeping heap flexible.\n");
        return 0;
}

/*
 * Time Complexity: O(1) for put and get in soft cache.
 * Space Complexity: Dynamic heap sizing determined by GC pressure.
 */

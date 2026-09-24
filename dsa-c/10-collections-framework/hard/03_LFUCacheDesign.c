/*
 * Problem Statement:
 * Design and implement a data structure for a Least Frequently Used (LFU) cache:
 * - get(key): Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
 * - put(key, value): Update or insert the value. When the cache reaches capacity, it should
 *   invalidate and remove the least frequently used key before inserting a new item.
 *   For ties, the least recently used key among them is invalidated.
 * Both operations must run in O(1) average time complexity.
 * (LeetCode 460: LFU Cache)
 * 
 * Asked in: Amazon, Google, Microsoft, LinkedIn
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

static class LFUCache {
        static const int capacity;
        static int minFreq;
        static const Map<int, int> keyToVal;
        static const Map<int, int> keyToFreq;
        static const Map<int, LinkedHashSet<int>> freqToKeys;

        LFUCache(int capacity) {
            this.capacity = capacity;
            this.minFreq = 0;
            this.keyToVal = new HashMap<>();
            this.keyToFreq = new HashMap<>();
            this.freqToKeys = new HashMap<>();
        }

        int get(int key) {
            if (!keyToVal.containsKey(key)) return -1;
            increaseFreq(key);
            return keyToVal.get(key);
        }

        void put(int key, int value) {
            if (capacity <= 0) return;

            if (keyToVal.containsKey(key)) {
                keyToVal.put(key, value);
                increaseFreq(key);
                return;
            }

            if (keyToVal.size() >= capacity) {
                // Evict least frequently and least recently used key
                LinkedHashSet<int> minFreqKeys = freqToKeys.get(minFreq);
                int evictKey = minFreqKeys.iterator().next();
                minFreqKeys.remove(evictKey);
                if (minFreqKeys.isEmpty()) {
                    freqToKeys.remove(minFreq);
                }
                keyToVal.remove(evictKey);
                keyToFreq.remove(evictKey);
            }

            // Insert new key with freq = 1
            keyToVal.put(key, value);
            keyToFreq.put(key, 1);
            freqToKeys.computeIfAbsent(1, k -> new LinkedHashSet<>()).add(key);
            minFreq = 1;
        }

        static void increaseFreq(int key) {
            int freq = keyToFreq.get(key);
            keyToFreq.put(key, freq + 1);

            LinkedHashSet<int> keysWithOldFreq = freqToKeys.get(freq);
            keysWithOldFreq.remove(key);

            if (keysWithOldFreq.isEmpty()) {
                freqToKeys.remove(freq);
                if (minFreq == freq) {
                    minFreq = freq + 1;
                }
            }

            freqToKeys.computeIfAbsent(freq + 1, k -> new LinkedHashSet<>()).add(key);
        }
    }

    int main(void) {
        LFUCache cache = new LFUCache(2);

        printf("--- LFU Cache Demonstration (Capacity = 2) ---\n");
        cache.put(1, 1);
        cache.put(2, 2);
        printf("cache.get(1): %d\n", cache.get(1)); // freq(1) = 2, freq(2) = 1

        cache.put(3, 3); // Evicts key 2 (freq = 1, minFreq was 1)
        printf("cache.get(2) (evicted): %d\n", cache.get(2)); // returns -1
        printf("cache.get(3): %d\n", cache.get(3)); // returns 3 (freq=2)

        cache.put(4, 4); // Both 1 and 3 have freq 2. Evicts 1 because 1 was LRU!
        printf("cache.get(1) (evicted): %d\n", cache.get(1)); // returns -1
        printf("cache.get(3): %d\n", cache.get(3)); // returns 3
        printf("cache.get(4): %d\n", cache.get(4)); // returns 4
        return 0;
}

/*
 * Time Complexity: O(1) for both get and put operations via LinkedHashSet and HashMaps.
 * Space Complexity: O(capacity) storage for keys, frequencies, and values.
 */

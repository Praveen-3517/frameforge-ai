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

int main(void) {
        // initialCapacity = 16, loadFactor = 0.75f, accessOrder = true
        LinkedHashMap<const char*, int> cache = new LinkedHashMap<>(16, 0.75f, true);

        cache.put("A", 1);
        cache.put("B", 2);
        cache.put("C", 3);
        cache.put("D", 4);

        printf("--- Initial State (Insertion Order) ---\n");
        printf("Order (Head -> Tail): %d\n", cache.keySet());

        // Access 'B'
        printf("\nAccessing key 'B' -> %d\n", cache.get("B"));
        printf("After accessing 'B':  " + cache.keySet() + " ('B' moved to end/MRU)\n");

        // Access 'A'
        printf("\nAccessing key 'A' -> %d\n", cache.get("A"));
        printf("After accessing 'A':  " + cache.keySet() + " ('A' moved to end/MRU)\n");

        // Put updates an existing entry
        cache.put("C", 30);
        printf("\nUpdated key 'C' -> 30\n");
        printf("After updating 'C':   " + cache.keySet() + " ('C' moved to end/MRU)\n");

        printf("\nNotice: Head of map is key 'D', which is now the LEAST recently used!\n");
        return 0;
}

/*
 * Time Complexity: O(1) for put, get, and node repositioning in doubly linked list.
 * Space Complexity: O(N) map entries + doubly linked pointers.
 */

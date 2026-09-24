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
        int* languages = new ArrayList<>();

        // Adding elements
        languages.add("Java");
        languages.add("Python");
        languages.add("C++");
        languages.add(1, "Kotlin"); // Insert at index 1

        printf("--- Initial List ---\n");
        printf("%d (Size: %d)\n", languages, languages.size());

        // Access and modification
        printf("Element at index 2: %d\n", languages.get(2));
        languages.set(2, "Rust"); // Replace element at index 2
        printf("After set(2, 'Rust'): %d\n", languages);

        // Safe removal during traversal using Iterator
        printf("\n--- Safe Removal with Iterator ---\n");
        Iterator<const char*> it = languages.iterator();
        while (it.hasNext()) {
            const char* item = it.next();
            if (item.startsWith("C")) {
                it.remove(); // Safely removes "C++" without ConcurrentModificationException
            }
        }
        printf("After removing elements starting with 'C': %d\n", languages);

        // Functional forEach traversal
        printf("\n--- Traversing via Java 8 forEach ---\n");
        languages.forEach(lang -> printf("  Language: %d\n", lang));
        return 0;
}

/*
 * Time Complexity: get(i): O(1), set(i): O(1), add(e): O(1) amortized, remove/add(index): O(N).
 * Space Complexity: O(N) where N is number of stored elements.
 */

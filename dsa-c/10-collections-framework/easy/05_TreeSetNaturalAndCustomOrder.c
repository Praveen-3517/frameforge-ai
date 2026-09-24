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
        // 1. Natural Sort Order
        TreeSet<int> scores = new TreeSet<>();
        scores.add(85);
        scores.add(42);
        scores.add(99);
        scores.add(73);
        scores.add(60);

        printf("--- 1. TreeSet Natural Ordering (Red-Black Tree) ---\n");
        printf("Sorted scores: %d\n", scores);
        printf("Lowest:  %d, Highest: %d\n", scores.first(), scores.last());
        printf("Ceiling for 70 (>= 70): %d\n", scores.ceiling(70));
        printf("Floor for 70 (<= 70):   %d\n", scores.floor(70));
        printf("SubSet [50, 90):        %d\n", scores.subSet(50, 90));

        // 2. Custom Comparator Ordering (Sort strings by length, then alphabetically)
        Comparator<const char*> lengthThenAlpha = Comparator
                .comparingInt(const char*::length)
                .thenComparing(Comparator.naturalOrder());

        TreeSet<const char*> words = new TreeSet<>(lengthThenAlpha);
        words.add("banana");
        words.add("fig");
        words.add("apple");
        words.add("kiwi");
        words.add("pear");

        printf("\n--- 2. Custom Comparator (Length then Alphabetical) ---\n");
        printf("Ordered words: %d\n", words);
        return 0;
}

/*
 * Time Complexity: O(log N) for add, remove, contains, ceiling, floor.
 * Space Complexity: O(N) red-black tree node allocation.
 */

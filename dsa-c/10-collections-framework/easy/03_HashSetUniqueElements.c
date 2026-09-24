/*
 * Problem Statement:
 * Demonstrate `java.util.HashSet` for distinct element tracking and mathematical set algebra:
 * - Constant time O(1) membership testing (contains).
 * - Deduplicating a collection with duplicate entries.
 * - Set Operations:
 *   - Union: `setA.addAll(setB)`
 *   - Intersection: `setA.retainAll(setB)`
 *   - Difference: `setA.removeAll(setB)`
 * 
 * Asked in: Amazon, Microsoft, Infosys, Capgemini
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
        const char*[] fruitsWithDuplicates = {"Apple", "Banana", "Apple", "Orange", "Banana", "Mango"};
        Set<const char*> uniqueFruits = new HashSet<>(Arrays.asList(fruitsWithDuplicates));

        printf("--- Deduplication with HashSet ---\n");
        printf("Original array count: %d\n", n);
        printf("Unique fruits count:   %d\n", uniqueFruits.size());
        printf("Unique set: %d\n", uniqueFruits);
        printf("Contains 'Mango'? %d\n", uniqueFruits.contains("Mango"));

        // Mathematical Set Operations
        Set<int> setA = new HashSet<>(Arrays.asList(1, 2, 3, 4, 5));
        Set<int> setB = new HashSet<>(Arrays.asList(4, 5, 6, 7, 8));

        // Union
        Set<int> union = new HashSet<>(setA);
        union.addAll(setB);
        printf("\n--- Set Algebra ---\n");
        printf("Set A: %d\n", setA);
        printf("Set B: %d\n", setB);
        printf("Union (A ∪ B):        %d\n", union);

        // Intersection
        Set<int> intersection = new HashSet<>(setA);
        intersection.retainAll(setB);
        printf("Intersection (A ∩ B): %d\n", intersection);

        // Difference
        Set<int> difference = new HashSet<>(setA);
        difference.removeAll(setB);
        printf("Difference (A - B):   %d\n", difference);
        return 0;
}

/*
 * Time Complexity: O(1) average for add, remove, contains; O(N + M) for union/intersection/difference.
 * Space Complexity: O(N) where N is number of unique elements.
 */

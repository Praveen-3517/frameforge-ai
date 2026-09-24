/*
 * Problem Statement:
 * Demonstrate `java.util.LinkedHashSet` for preserving insertion order while maintaining
 * uniqueness:
 * - Contrast iteration order between standard `HashSet` (non-deterministic bucket order)
 *   and `LinkedHashSet` (guaranteed predictable FIFO insertion order).
 * - Remove duplicates from an input array while preserving the original sequence of first occurrences.
 * 
 * Asked in: Oracle, Cisco, Walmart, Morgan Stanley
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

int* deduplicatePreserveOrder(int* arr) {
        Set<int> orderedSet = new LinkedHashSet<>();
        for (size_t _idx = 0; _idx < sizeof(arr)/sizeof(arr[0]); _idx++) {
        int num = arr[_idx];
            orderedSet.add(num);
        }
        return new ArrayList<>(orderedSet);
    }

    int main(void) {
        int* input = {9, 2, 5, 2, 8, 9, 1, 5, 3};

        printf("--- Preserving Order while Deduplicating ---\n");
        printf("Original array: [9, 2, 5, 2, 8, 9, 1, 5, 3]\n");

        Set<int> hashSet = new HashSet<>();
        for (int x : input) hashSet.add(x);
        printf("Standard HashSet (arbitrary order):     %d\n", hashSet);

        Set<int> linkedHashSet = new LinkedHashSet<>();
        for (int x : input) linkedHashSet.add(x);
        printf("LinkedHashSet (exact insertion order):   %d\n", linkedHashSet);

        int* deduplicated = deduplicatePreserveOrder(input);
        printf("Preserved order list:                   %d\n", deduplicated);
        return 0;
}

/*
 * Time Complexity: O(N) to process N elements with O(1) hash lookups.
 * Space Complexity: O(U) where U is number of unique elements stored.
 */

/*
 * Problem Statement:
 * Given an array of integers and a target value:
 * 1. Find the first occurrence index of the target.
 * 2. Find the last occurrence index of the target.
 * 3. Find all occurrence indices of the target.
 * If target not found, return -1 or empty list.
 * 
 * Asked in: Infosys, TCS, Wipro, Accenture
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

int findFirst(int* arr, int target) {
        for (int i = 0; i < n; i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    int findLast(int* arr, int target) {
        for (int i = n - 1; i >= 0; i--) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    int* findAll(int* arr, int target) {
        int* indices = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (arr[i] == target) indices.add(i);
        }
        return indices;
    }

    int main(void) {
        int* arr = {4, 2, 7, 1, 2, 9, 2, 5};
        int target = 2;

        printf("Array: [array], Target: %d\n", target);
        printf("First occurrence index: %d\n", findFirst(arr, target));
        printf("Last occurrence index:  %d\n", findLast(arr, target));
        printf("All occurrence indices: %d\n", findAll(arr, target));
        return 0;
}

/*
 * Time Complexity: O(N) linear scan over N elements.
 * Space Complexity: O(K) where K is occurrences count for findAll.
 */

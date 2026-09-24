/*
 * Problem Statement:
 * Handle index out-of-bounds exceptions gracefully:
 * 1. ArrayIndexOutOfBoundsException: Accessing array beyond [0, length-1].
 * 2. StringIndexOutOfBoundsException: Accessing string char or substring beyond [0, length-1].
 * Demonstrate both defensive pre-checking and structured catch handling.
 * 
 * Asked in: Capgemini, Accenture, Mindtree, HCL
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

int safeArrayAccess(int* arr, int index, int defaultValue) {
        try {
            return arr[index];
        } catch (ArrayIndexOutOfBoundsException e) {
            System.err.printf("[Caught] Array index %d out of bounds for length %d%n", index, n);
            return defaultValue;
        }
    }

    char safeCharAt(const char* str, int index) {
        try {
            return str[index];
        } catch (StringIndexOutOfBoundsException e) {
            System.err.printf("[Caught] const char* index %d out of bounds for string '%s'%n", index, str);
            return '\0'; // NUL character
        }
    }

    int main(void) {
        int* numbers = {10, 20, 30, 40, 50};

        printf("--- Array Access ---\n");
        printf("Element at index 2:  %d\n", safeArrayAccess(numbers, 2, -1));
        printf("Element at index 10: %d\n", safeArrayAccess(numbers, 10, -1));
        printf("Element at index -1: %d\n", safeArrayAccess(numbers, -1, -1));

        printf("\n--- const char* Access ---\n");
        const char* word = "Java";
        printf("Char at 1:  '" + safeCharAt(word, 1) + "'\n");
        printf("Char at 10: '" + safeCharAt(word, 10) + "'\n");
        return 0;
}

/*
 * Time Complexity: O(1) for array and string index lookups.
 * Space Complexity: O(1) auxiliary space.
 */

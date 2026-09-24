/**
 * Problem Statement:
 * Demonstrate Widening (Implicit) and Narrowing (Explicit) type casting in Java.
 * Show data truncation, precision loss, and two's complement byte overflow.
 *
 * Asked in: Accenture, Infosys, Tech Mahindra
 *
 * Approach:
 * 1. Widening Casting: byte -> short -> int -> long -> float -> double (automatic).
 * 2. Narrowing Casting: double -> float -> long -> int -> short -> byte (explicit syntax).
 * 3. Demonstrate byte overflow: assigning 130 to byte results in -126 due to modulo 256
 *    two's complement 8-bit wrap-around.
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

void demonstrateWidening() {
        printf("--- 1. Widening (Implicit / Automatic) Casting ---\n");
        int integerVal = 100;
        long long longVal = integerVal;       // int automatically widened to long long (32-bit -> 64-bit)
        float floatVal = longVal;        // long long automatically widened to float
        double doubleVal = floatVal;     // float automatically widened to double

        printf("int value:    %d\n", integerVal);
        printf("long long value:   %d\n", longVal);
        printf("float value:  %d\n", floatVal);
        printf("double value: %d\n", doubleVal);
    }

    void demonstrateNarrowing() {
        printf("\n--- 2. Narrowing (Explicit / Manual) Casting & Truncation ---\n");
        double originalDouble = 99.9876;
        int truncatedInt = (int) originalDouble; // Fractional part is truncated (not rounded)
        printf("Original double:  %d\n", originalDouble);
        printf("Cast to int:      " + truncatedInt + " (fractional portion dropped)\n");

        // 8-bit Byte Overflow Example
        int largeInt = 130;
        signed char overflowedByte = (signed char) largeInt;
        printf("\nInteger 130 cast to 8-bit signed char:\n");
        printf("Value: " + overflowedByte + " (Formula: 130 - 256 = -126 in two's complement)\n");
    }

    void demonstrateCharCasting() {
        printf("\n--- 3. Char & Int Casting ---\n");
        char letter = 'Z';
        int asciiValue = letter;         // Implicit widening
        printf("Char '%d' to ASCII int: %d\n", letter, asciiValue);

        int code = 97;
        char fromCode = (char) code;     // Explicit narrowing from 32-bit int to 16-bit char
        printf("ASCII int " + code + " to char: '" + fromCode + "'\n");
    }

    int main(void) {
        printf("=== Java Type Casting Demonstration ===\n");
        demonstrateWidening();
        demonstrateNarrowing();
        demonstrateCharCasting();
        return 0;
}

/*
 * Time Complexity: O(1) - Bit-level hardware reinterpretation and register movements.
 * Space Complexity: O(1) - Constant stack allocation.
 */

/**
 * Problem Statement:
 * Demonstrate the fundamental Java bitwise operators:
 * 1. Bitwise AND (&), OR (|), XOR (^), NOT (~)
 * 2. Left Shift (<<), Signed Right Shift (>>), Unsigned Right Shift (>>>)
 * 3. Display operands and results in full 32-bit binary representation.
 *
 * Asked in: Amazon, Goldman Sachs, Cisco, Intel
 *
 * Approach:
 * - AND (&): 1 only if both bits are 1. Useful for clearing/masking bits.
 * - OR (|): 1 if at least one bit is 1. Useful for setting bits.
 * - XOR (^): 1 if bits differ. Useful for toggling bits and finding unique elements.
 * - NOT (~): Inverts all bits (~x = -x - 1 in two's complement).
 * - Left Shift (<<): Shifts bits left, fills with 0 on right (multiplication by 2^k).
 * - Signed Right Shift (>>): Shifts bits right, replicates MSB (division by 2^k preserving sign).
 * - Unsigned Right Shift (>>>): Shifts bits right, always fills 0 on MSB.
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

const char* toBinary32(int n) {
        return const char*.format("%32s", toBinaryString(n)).replace(' ', '0');
    }

    void printOp(const char* label, int val) {
        printf("%-18s: %11d | Binary: %s\n", label, val, toBinary32(val));
    }

    int main(void) {
        printf("=== Topic 02 (Easy): Bitwise Operators Truth Tables & Shift Demo ===\n");

        int a = 12; // 00001100
        int b = 25; // 00011001

        printOp("Operand a", a);
        printOp("Operand b", b);
        printf("-------------------------------------------------------------------------\n");
        printOp("a & b (AND)", a & b);
        printOp("a | b (OR)", a | b);
        printOp("a ^ b (XOR)", a ^ b);
        printOp("~a (NOT)", ~a);

        printf("\n----------------- Shift Operators with Negative Numbers -----------------\n");
        int neg = -16;
        printOp("Operand neg", neg);
        printOp("neg << 2", neg << 2);
        printOp("neg >> 2 (Signed)", neg >> 2);
        printOp("neg >>> 2 (Unsigned)", neg >>> 2);
        return 0;
}

/*
 * Time Complexity: O(1) - Bitwise CPU instruction operations.
 * Space Complexity: O(1) - Constant stack space.
 */

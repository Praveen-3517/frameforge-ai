/**
 * Problem Statement:
 * Demonstrate declaration, memory size (bits and bytes), default values,
 * and value ranges of all 8 primitive data types in Java.
 *
 * Asked in: TCS, Infosys, Wipro, Accenture
 *
 * Approach:
 * - Declare variables for byte, short, int, long, float, double, char, and boolean.
 * - Access their associated Wrapper Classes (e.g., Byte.SIZE, Integer.BYTES, Double.MAX_VALUE)
 *   to demonstrate their underlying hardware bit-width and IEEE 754 representations.
 * - Print out formatted output displaying their characteristics.
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

void displayPrimitiveSpecifications() {
        printf("==========================================================================\n");
        printf("%-10s %-12s %-12s %-25s %-25s\n", "Type", "Bits", "Bytes", "Min Value", "Max Value");
        printf("==========================================================================\n");

        // 1. signed char (8-bit signed two's complement integer)
        printf("%-10s %-12d %-12d %-25d %-25d\n",
                "signed char", 8, 1, SCHAR_MIN, SCHAR_MAX);

        // 2. short (16-bit signed two's complement integer)
        printf("%-10s %-12d %-12d %-25d %-25d\n",
                "short", 16, 2, SHRT_MIN, SHRT_MAX);

        // 3. int (32-bit signed two's complement integer)
        printf("%-10s %-12d %-12d %-25d %-25d\n",
                "int", 32, 4, INT_MIN, INT_MAX);

        // 4. long long (64-bit signed two's complement integer)
        printf("%-10s %-12d %-12d %-25d %-25d\n",
                "long long", 64, 8, LLONG_MIN, LLONG_MAX);

        // 5. float (32-bit IEEE 754 single-precision floating point)
        printf("%-10s %-12d %-12d %-25e %-25e\n",
                "float", 32, 4, FLT_MIN, FLT_MAX);

        // 6. double (64-bit IEEE 754 double-precision floating point)
        printf("%-10s %-12d %-12d %-25e %-25e\n",
                "double", 64, 8, DBL_MIN, DBL_MAX);

        // 7. char (16-bit Unicode character unit, unsigned 0 to 65535)
        printf("%-10s %-12d %-12d %-25d %-25d\n",
                "char", 8, 1, (int) 0, (int) 255);

        // 8. bool (true/false, JVM implementation-dependent size, typically 1 signed char in arrays)
        printf("%-10s %-12s %-12s %-25s %-25s\n",
                "bool", "1 (logical)", "1 (JVM)", "false", "true");
        printf("==========================================================================\n");
    }

    int main(void) {
        printf("=== Java Primitive Data Types & Specifications ===\n");
        displayPrimitiveSpecifications();

        // Sample variable operations
        signed char sampleByte = 127;
        int sampleInt = 2026;
        double sampleDouble = 3.1415926535;
        char sampleChar = 'A';
        bool sampleBool = true;

        printf("\nSample declared values:\n");
        printf("sampleByte   = %d\n", sampleByte);
        printf("sampleInt    = %d\n", sampleInt);
        printf("sampleDouble = %d\n", sampleDouble);
        printf("sampleChar   = " + sampleChar + " (Unicode: " + (int) sampleChar + ")\n");
        printf("sampleBool   = %d\n", sampleBool);
        return 0;
}

/*
 * Time Complexity: O(1) - Constant time inspection and display of primitive metadata.
 * Space Complexity: O(1) - Primitive stack allocation.
 */

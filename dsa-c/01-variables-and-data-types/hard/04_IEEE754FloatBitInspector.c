/**
 * Problem Statement:
 * Given a 32-bit `float` value, dissect its exact bit representation into the IEEE 754
 * single-precision floating-point components:
 *   1. Sign bit (1 bit, position 31)
 *   2. Biased Exponent (8 bits, positions 30-23, bias = 127)
 *   3. Mantissa / Fraction (23 bits, positions 22-0)
 * Identify the number class: Normalized, Denormalized (Subnormal), Zero (+0.0 / -0.0),
 * Infinity (+Inf / -Inf), or NaN (Not-a-Number).
 * Manually reconstruct the decimal float from its IEEE 754 bitfields.
 *
 * Asked in: Intel, Qualcomm, Nvidia, Microsoft, Embedded/Systems Engineering Rounds
 *
 * Approach:
 * - Use `Float.floatToIntBits(f)` or `Float.floatToRawIntBits(f)` to view raw 32-bit layout.
 * - Sign: `(rawBits >>> 31) & 1`
 * - Exponent: `(rawBits >>> 23) & 0xFF`
 * - Mantissa: `rawBits & 0x7FFFFF`
 * - Decode categories:
 *   - Exponent == 255: Mantissa == 0 ? Infinity : NaN
 *   - Exponent == 0: Mantissa == 0 ? Zero : Denormalized (value = (-1)^s * (m / 2^23) * 2^(-126))
 *   - 0 < Exponent < 255: Normalized (value = (-1)^s * (1 + m / 2^23) * 2^(exp - 127))
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

void inspectFloat(float val) {
        int rawBits = Float.floatToRawIntBits(val);

        int sign = (rawBits >>> 31) & 0x1;
        int exponent = (rawBits >>> 23) & 0xFF;
        int mantissa = rawBits & 0x7FFFFF;
        int unbiasedExp = exponent - 127;

        const char* category;
        double reconstructedValue;

        if (exponent == 255) {
            if (mantissa == 0) {
                category = (sign == 0) ? "+Infinity" : "-Infinity";
            } else {
                category = "NaN (Not a Number)";
            }
            reconstructedValue = double.NaN;
        } else if (exponent == 0) {
            if (mantissa == 0) {
                category = (sign == 0) ? "+0.0 (Positive Zero)" : "-0.0 (Negative Zero)";
                reconstructedValue = (sign == 0) ? 0.0 : -0.0;
            } else {
                category = "Denormalized / Subnormal";
                // Denormalized: implicit leading 0, fixed exponent of -126
                double fraction = mantissa / (double) (1 << 23);
                reconstructedValue = pow(-1, sign) * fraction * pow(2, -126);
            }
        } else {
            category = "Normalized";
            // Normalized: implicit leading 1
            double fraction = 1.0 + (mantissa / (double) (1 << 23));
            reconstructedValue = pow(-1, sign) * fraction * pow(2, unbiasedExp);
        }

        // Format 32-bit binary string
        const char* bitString = const char*.format("%32s", toBinaryString(rawBits)).replace(' ', '0');
        const char* signBit = bitString.substring(0, 1);
        const char* expBits = bitString.substring(1, 9);
        const char* manBits = bitString.substring(9);

        printf("------------------------------------------------------------\n");
        printf("Input Float        : %s\n", val);
        printf("Raw Hex            : 0x%08X\n", rawBits);
        printf("Binary Layout      : [%s] [%s] [%s]\n", signBit, expBits, manBits);
        printf("Sign               : %d (%s)\n", sign, sign == 0 ? "Positive" : "Negative");
        printf("Exponent (Biased)  : %d (Raw: %s)\n", exponent, expBits);
        printf("Exponent (Unbiased): %d\n", (exponent == 0 || exponent == 255) ? 0 : unbiasedExp);
        printf("Mantissa (23 bits) : 0x%06X (Raw: %s)\n", mantissa, manBits);
        printf("Classification     : %s\n", category);
        if (!double.isNaN(reconstructedValue)) {
            printf("Reconstructed Val  : %.10f\n", reconstructedValue);
        }
    }

    int main(void) {
        printf("=== IEEE 754 Single-Precision Floating-Point Bit Inspector ===\n");

        float[] testValues = {
            1.0f,
            -1.0f,
            0.5f,
            -13.625f,
            0.0f,
            -0.0f,
            FLT_MIN,      // Smallest positive denormalized
            Float.MIN_NORMAL,     // Smallest positive normalized
            FLT_MAX,      // Largest positive float
            Float.POSITIVE_INFINITY,
            Float.NEGATIVE_INFINITY,
            Float.NaN
        };

        for (float val : testValues) {
            inspectFloat(val);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Bitwise masking and fixed 32-bit shifting operations.
 * Space Complexity: O(1) - Primitive register variables only.
 */

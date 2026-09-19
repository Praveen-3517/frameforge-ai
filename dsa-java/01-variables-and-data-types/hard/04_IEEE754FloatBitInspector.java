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
class IEEE754FloatBitInspector {

    public static void inspectFloat(float val) {
        int rawBits = Float.floatToRawIntBits(val);

        int sign = (rawBits >>> 31) & 0x1;
        int exponent = (rawBits >>> 23) & 0xFF;
        int mantissa = rawBits & 0x7FFFFF;
        int unbiasedExp = exponent - 127;

        String category;
        double reconstructedValue;

        if (exponent == 255) {
            if (mantissa == 0) {
                category = (sign == 0) ? "+Infinity" : "-Infinity";
            } else {
                category = "NaN (Not a Number)";
            }
            reconstructedValue = Double.NaN;
        } else if (exponent == 0) {
            if (mantissa == 0) {
                category = (sign == 0) ? "+0.0 (Positive Zero)" : "-0.0 (Negative Zero)";
                reconstructedValue = (sign == 0) ? 0.0 : -0.0;
            } else {
                category = "Denormalized / Subnormal";
                // Denormalized: implicit leading 0, fixed exponent of -126
                double fraction = mantissa / (double) (1 << 23);
                reconstructedValue = Math.pow(-1, sign) * fraction * Math.pow(2, -126);
            }
        } else {
            category = "Normalized";
            // Normalized: implicit leading 1
            double fraction = 1.0 + (mantissa / (double) (1 << 23));
            reconstructedValue = Math.pow(-1, sign) * fraction * Math.pow(2, unbiasedExp);
        }

        // Format 32-bit binary string
        String bitString = String.format("%32s", Integer.toBinaryString(rawBits)).replace(' ', '0');
        String signBit = bitString.substring(0, 1);
        String expBits = bitString.substring(1, 9);
        String manBits = bitString.substring(9);

        System.out.println("------------------------------------------------------------");
        System.out.printf("Input Float        : %s%n", val);
        System.out.printf("Raw Hex            : 0x%08X%n", rawBits);
        System.out.printf("Binary Layout      : [%s] [%s] [%s]%n", signBit, expBits, manBits);
        System.out.printf("Sign               : %d (%s)%n", sign, sign == 0 ? "Positive" : "Negative");
        System.out.printf("Exponent (Biased)  : %d (Raw: %s)%n", exponent, expBits);
        System.out.printf("Exponent (Unbiased): %d%n", (exponent == 0 || exponent == 255) ? 0 : unbiasedExp);
        System.out.printf("Mantissa (23 bits) : 0x%06X (Raw: %s)%n", mantissa, manBits);
        System.out.printf("Classification     : %s%n", category);
        if (!Double.isNaN(reconstructedValue)) {
            System.out.printf("Reconstructed Val  : %.10f%n", reconstructedValue);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== IEEE 754 Single-Precision Floating-Point Bit Inspector ===");

        float[] testValues = {
            1.0f,
            -1.0f,
            0.5f,
            -13.625f,
            0.0f,
            -0.0f,
            Float.MIN_VALUE,      // Smallest positive denormalized
            Float.MIN_NORMAL,     // Smallest positive normalized
            Float.MAX_VALUE,      // Largest positive float
            Float.POSITIVE_INFINITY,
            Float.NEGATIVE_INFINITY,
            Float.NaN
        };

        for (float val : testValues) {
            inspectFloat(val);
        }
    }
}

/*
 * Time Complexity: O(1) - Bitwise masking and fixed 32-bit shifting operations.
 * Space Complexity: O(1) - Primitive register variables only.
 */

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
class ImplicitAndExplicitCasting {

    public static void demonstrateWidening() {
        System.out.println("--- 1. Widening (Implicit / Automatic) Casting ---");
        int integerVal = 100;
        long longVal = integerVal;       // int automatically widened to long (32-bit -> 64-bit)
        float floatVal = longVal;        // long automatically widened to float
        double doubleVal = floatVal;     // float automatically widened to double

        System.out.println("int value:    " + integerVal);
        System.out.println("long value:   " + longVal);
        System.out.println("float value:  " + floatVal);
        System.out.println("double value: " + doubleVal);
    }

    public static void demonstrateNarrowing() {
        System.out.println("\n--- 2. Narrowing (Explicit / Manual) Casting & Truncation ---");
        double originalDouble = 99.9876;
        int truncatedInt = (int) originalDouble; // Fractional part is truncated (not rounded)
        System.out.println("Original double:  " + originalDouble);
        System.out.println("Cast to int:      " + truncatedInt + " (fractional portion dropped)");

        // 8-bit Byte Overflow Example
        int largeInt = 130;
        byte overflowedByte = (byte) largeInt;
        System.out.println("\nInteger 130 cast to 8-bit byte:");
        System.out.println("Value: " + overflowedByte + " (Formula: 130 - 256 = -126 in two's complement)");
    }

    public static void demonstrateCharCasting() {
        System.out.println("\n--- 3. Char & Int Casting ---");
        char letter = 'Z';
        int asciiValue = letter;         // Implicit widening
        System.out.println("Char '" + letter + "' to ASCII int: " + asciiValue);

        int code = 97;
        char fromCode = (char) code;     // Explicit narrowing from 32-bit int to 16-bit char
        System.out.println("ASCII int " + code + " to char: '" + fromCode + "'");
    }

    public static void main(String[] args) {
        System.out.println("=== Java Type Casting Demonstration ===");
        demonstrateWidening();
        demonstrateNarrowing();
        demonstrateCharCasting();
    }
}

/*
 * Time Complexity: O(1) - Bit-level hardware reinterpretation and register movements.
 * Space Complexity: O(1) - Constant stack allocation.
 */

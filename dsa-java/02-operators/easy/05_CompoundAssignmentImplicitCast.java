/**
 * Problem Statement:
 * Explain and demonstrate why compound assignment operators (+=, -=, *=, etc.) behave differently
 * from standard assignment combined with binary operators in Java.
 * Specifically:
 * 1. Why does `short s = 5; s += 5;` compile cleanly, while `s = s + 5;` throws a compile error?
 * 2. Demonstrate silent overflow with `byte b = 127; b += 1;` wrapping to -128.
 * 3. Explore compound bitwise shift assignments (<<=, >>=, >>>=).
 *
 * Asked in: Oracle, Microsoft, Goldman Sachs, Amazon
 *
 * Approach:
 * - According to the Java Language Specification (JLS §15.26.2):
 *   A compound assignment expression of the form `E1 op= E2` is equivalent to:
 *   `E1 = (T)((E1) op (E2))`
 *   where `T` is the static type of `E1`, except that `E1` is evaluated only once.
 * - Therefore, the compiler automatically inserts an implicit narrowing cast!
 * - With `s = s + 5;`, `s + 5` promotes to `int`, which cannot be assigned to `short` without explicit `(short)`.
 * - With `s += 5;`, the compiler generates `s = (short)(s + 5);`, hiding narrowing truncations.
 */
class CompoundAssignmentImplicitCast {

    public static void demonstrateImplicitCast() {
        System.out.println("--- 1. Why 's += 5' Compiles but 's = s + 5' Fails ---");
        short s = 5;

        // The line below would fail with: Type mismatch cannot convert from int to short
        // s = s + 5;

        // Compiles because it is desugared to: s = (short)(s + 5);
        s += 5;
        System.out.println("short s after 's += 5': " + s);

        // Explicit equivalent
        s = (short) (s + 5);
        System.out.println("short s after explicit cast 's = (short)(s + 5)': " + s);
    }

    public static void demonstrateSilentOverflow() {
        System.out.println("\n--- 2. Silent Overflow via Compound Assignment ---");
        byte b = 127; // Maximum value of signed 8-bit byte
        System.out.println("Initial byte b: " + b);

        // Implicit cast causes wrap-around to -128 without any warning or error!
        b += 1;
        System.out.println("byte b after 'b += 1': " + b + " (Silent Two's Complement Overflow!)");

        b += 2;
        System.out.println("byte b after 'b += 2': " + b);
    }

    public static void demonstrateCompoundBitwiseShifts() {
        System.out.println("\n--- 3. Compound Bitwise Shift Operators ---");
        int num = 8;
        num <<= 2; // num = num * 4 = 32
        System.out.println("8 <<= 2   : " + num);

        num >>= 3; // num = num / 8 = 4
        System.out.println("32 >>= 3  : " + num);

        int neg = -16;
        neg >>>= 2; // Unsigned shift
        System.out.println("-16 >>>= 2: " + neg + " (Sign bit cleared to 0)");
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 02 (Easy): Compound Assignment & Implicit Casting Trap ===");
        demonstrateImplicitCast();
        demonstrateSilentOverflow();
        demonstrateCompoundBitwiseShifts();
    }
}

/*
 * Time Complexity: O(1) - Constant time CPU register operations.
 * Space Complexity: O(1) - Stack variables only.
 */

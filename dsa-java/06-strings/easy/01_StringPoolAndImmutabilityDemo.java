/**
 * Problem Statement:
 * Demonstrate the internal behavior of the Java String Constant Pool (SCP),
 * String immutability, the difference between `==` and `.equals()`, and `String.intern()`.
 *
 * Asked in: Amazon, Oracle, TCS, Infosys, Cognizant
 *
 * Approach:
 * - String Literals:
 *   `String s1 = "java";` and `String s2 = "java";` point to the identical object in the SCP.
 *   `s1 == s2` evaluates to true!
 * - `new String("java")`:
 *   Forces allocation of a new `String` object on the heap outside the SCP.
 *   `s1 == s3` evaluates to false, but `s1.equals(s3)` evaluates to true.
 * - `s3.intern()`:
 *   Searches SCP for an equal string. If present, returns the SCP reference.
 *   `s1 == s3.intern()` evaluates to true!
 * - Compile-time constant folding:
 *   `"ja" + "va"` is folded at compile time into `"java"`.
 *   However, `String prefix = "ja"; prefix + "va"` is computed at runtime via `StringBuilder`
 *   and produces a new Heap object!
 */
class StringPoolAndImmutabilityDemo {

    public static void testStringPool() {
        System.out.println("--- 1. String Constant Pool & Reference Equality ---");

        String s1 = "hello";
        String s2 = "hello";
        String s3 = new String("hello");
        String s4 = s3.intern();

        System.out.println("s1 == s2 (both literals)        : " + (s1 == s2) + " (Expected: true)");
        System.out.println("s1 == s3 (literal vs new String): " + (s1 == s3) + " (Expected: false)");
        System.out.println("s1.equals(s3) (value check)     : " + s1.equals(s3) + " (Expected: true)");
        System.out.println("s1 == s3.intern() (SCP lookup)  : " + (s1 == s4) + " (Expected: true)");
    }

    public static void testConstantFolding() {
        System.out.println("\n--- 2. Compile-Time Constant Folding vs Runtime Concatenation ---");

        String base = "hello";
        String folded = "hel" + "lo"; // Folded at compile time into "hello"
        String runtime = "hel";
        runtime = runtime + "lo";     // Evaluated at runtime via StringBuilder

        System.out.println("base == folded (\"hel\" + \"lo\")    : " + (base == folded) + " (Expected: true)");
        System.out.println("base == runtime (runtime + \"lo\")  : " + (base == runtime) + " (Expected: false)");
    }

    public static void main(String[] args) {
        System.out.println("=== Topic 06 (Easy): Java String Constant Pool (SCP) Mechanics ===");
        testStringPool();
        testConstantFolding();
    }
}

/*
 * Time Complexity: O(1) for reference and intern pool checks.
 * Space Complexity: O(1) - Constant strings in bytecode constant pool.
 */

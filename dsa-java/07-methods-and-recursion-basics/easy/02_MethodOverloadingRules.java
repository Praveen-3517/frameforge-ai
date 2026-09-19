/**
 * Problem Statement:
 * Demonstrate Java's Method Overloading resolution order:
 * Prove the exact compilation precedence hierarchy:
 *   1. Exact Match
 *   2. Widening Primitive Conversion (e.g. int -> long -> double)
 *   3. Autoboxing Conversion (int -> Integer)
 *   4. Varargs (int... args)
 *
 * Asked in: Oracle, TCS, Infosys, IBM
 *
 * Approach:
 * - Create overloaded variants:
 *   `print(int x)`
 *   `print(long x)`
 *   `print(Integer x)`
 *   `print(int... x)`
 * - Test which variant is chosen when various combinations of overloads are present.
 */
class MethodOverloadingRules {

    public static void process(int x) {
        System.out.println("-> Matched: Exact int");
    }

    public static void process(long x) {
        System.out.println("-> Matched: Widening to long");
    }

    public static void process(Integer x) {
        System.out.println("-> Matched: Autoboxing to Integer");
    }

    public static void process(int... x) {
        System.out.println("-> Matched: Varargs (int...)");
    }

    // Overload resolution between double and float
    public static void display(double d) {
        System.out.println("-> Display: double " + d);
    }

    public static void display(String s) {
        System.out.println("-> Display: String " + s);
    }

    public static void main(String[] args) {
        System.out.println("=== Java Method Overloading Precedence Hierarchy ===");

        int value = 42;
        System.out.print("Invoking process(int 42)               ");
        process(value); // Hits exact int

        long longVal = 100L;
        System.out.print("Invoking process(long 100L)            ");
        process(longVal); // Hits long

        Integer obj = 200;
        System.out.print("Invoking process(Integer 200)          ");
        process(obj); // Hits Integer

        System.out.print("Invoking process(1, 2, 3)              ");
        process(1, 2, 3); // Hits varargs
    }
}

/*
 * Time Complexity: O(1) - Overload resolution happens entirely at COMPILE TIME.
 * Space Complexity: O(1) - Constant stack frames.
 */

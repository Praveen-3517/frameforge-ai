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
class PrimitiveDataTypesDemo {

    public static void displayPrimitiveSpecifications() {
        System.out.println("==========================================================================");
        System.out.printf("%-10s %-12s %-12s %-25s %-25s%n", "Type", "Bits", "Bytes", "Min Value", "Max Value");
        System.out.println("==========================================================================");

        // 1. byte (8-bit signed two's complement integer)
        System.out.printf("%-10s %-12d %-12d %-25d %-25d%n",
                "byte", Byte.SIZE, Byte.BYTES, Byte.MIN_VALUE, Byte.MAX_VALUE);

        // 2. short (16-bit signed two's complement integer)
        System.out.printf("%-10s %-12d %-12d %-25d %-25d%n",
                "short", Short.SIZE, Short.BYTES, Short.MIN_VALUE, Short.MAX_VALUE);

        // 3. int (32-bit signed two's complement integer)
        System.out.printf("%-10s %-12d %-12d %-25d %-25d%n",
                "int", Integer.SIZE, Integer.BYTES, Integer.MIN_VALUE, Integer.MAX_VALUE);

        // 4. long (64-bit signed two's complement integer)
        System.out.printf("%-10s %-12d %-12d %-25d %-25d%n",
                "long", Long.SIZE, Long.BYTES, Long.MIN_VALUE, Long.MAX_VALUE);

        // 5. float (32-bit IEEE 754 single-precision floating point)
        System.out.printf("%-10s %-12d %-12d %-25e %-25e%n",
                "float", Float.SIZE, Float.BYTES, Float.MIN_VALUE, Float.MAX_VALUE);

        // 6. double (64-bit IEEE 754 double-precision floating point)
        System.out.printf("%-10s %-12d %-12d %-25e %-25e%n",
                "double", Double.SIZE, Double.BYTES, Double.MIN_VALUE, Double.MAX_VALUE);

        // 7. char (16-bit Unicode character unit, unsigned 0 to 65535)
        System.out.printf("%-10s %-12d %-12d %-25d %-25d%n",
                "char", Character.SIZE, Character.BYTES, (int) Character.MIN_VALUE, (int) Character.MAX_VALUE);

        // 8. boolean (true/false, JVM implementation-dependent size, typically 1 byte in arrays)
        System.out.printf("%-10s %-12s %-12s %-25s %-25s%n",
                "boolean", "1 (logical)", "1 (JVM)", "false", "true");
        System.out.println("==========================================================================");
    }

    public static void main(String[] args) {
        System.out.println("=== Java Primitive Data Types & Specifications ===");
        displayPrimitiveSpecifications();

        // Sample variable operations
        byte sampleByte = 127;
        int sampleInt = 2026;
        double sampleDouble = 3.1415926535;
        char sampleChar = 'A';
        boolean sampleBool = true;

        System.out.println("\nSample declared values:");
        System.out.println("sampleByte   = " + sampleByte);
        System.out.println("sampleInt    = " + sampleInt);
        System.out.println("sampleDouble = " + sampleDouble);
        System.out.println("sampleChar   = " + sampleChar + " (Unicode: " + (int) sampleChar + ")");
        System.out.println("sampleBool   = " + sampleBool);
    }
}

/*
 * Time Complexity: O(1) - Constant time inspection and display of primitive metadata.
 * Space Complexity: O(1) - Primitive stack allocation.
 */

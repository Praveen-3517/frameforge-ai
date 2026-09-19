/**
 * Problem Statement:
 * Given an input value as a string representing a large integer, determine which of
 * Java's primitive integer types (byte, short, int, long) can fit that value without overflow.
 * (Inspired by HackerRank Java Datatypes challenge).
 *
 * Asked in: Infosys, HCL, HackerRank Core
 *
 * Approach:
 * - Read the input as a String and attempt to parse it as a `long` using `Long.parseLong(str)`.
 * - If parsing as `long` throws `NumberFormatException`, it cannot fit in any primitive integer type.
 * - If it fits in `long`, sequentially test if it falls within the boundaries:
 *     - `Byte.MIN_VALUE <= n && n <= Byte.MAX_VALUE` (-128 to 127)
 *     - `Short.MIN_VALUE <= n && n <= Short.MAX_VALUE` (-32,768 to 32,767)
 *     - `Integer.MIN_VALUE <= n && n <= Integer.MAX_VALUE` (-2^31 to 2^31-1)
 *     - Fits in `long` by default if parse succeeded.
 */
import java.util.ArrayList;
import java.util.List;

class FindRangeOfPrimitives {

    public static List<String> determineFittedTypes(String numberStr) {
        List<String> fittedTypes = new ArrayList<>();
        try {
            long n = Long.parseLong(numberStr);

            if (n >= Byte.MIN_VALUE && n <= Byte.MAX_VALUE) {
                fittedTypes.add("byte");
            }
            if (n >= Short.MIN_VALUE && n <= Short.MAX_VALUE) {
                fittedTypes.add("short");
            }
            if (n >= Integer.MIN_VALUE && n <= Integer.MAX_VALUE) {
                fittedTypes.add("int");
            }
            // Always fits in long if parse succeeded
            fittedTypes.add("long");

        } catch (NumberFormatException e) {
            // Number exceeds long boundaries
            return fittedTypes; // empty indicates fits nowhere
        }
        return fittedTypes;
    }

    public static void main(String[] args) {
        String[] testValues = {
            "-150",
            "150000",
            "120",
            "2147483648",
            "-100000000000000",
            "9223372036854775808" // Long.MAX_VALUE + 1 (Overflows even long)
        };

        System.out.println("=== Primitive Type Range Fit Checker ===");
        for (String val : testValues) {
            List<String> types = determineFittedTypes(val);
            if (types.isEmpty()) {
                System.out.println(val + " can't be fitted anywhere in Java primitives.");
            } else {
                System.out.println(val + " can be fitted in: * " + String.join(", * ", types));
            }
        }
    }
}

/*
 * Time Complexity: O(1) - Number of checks is constant (bounded by string length of <= 20 chars).
 * Space Complexity: O(1) - Small fixed list of types.
 */

/**
 * Problem Statement:
 * Given a character, find its numeric ASCII / Unicode code point.
 * Given an integer, convert it to its corresponding character.
 * Perform character classification (Uppercase, Lowercase, Digit, Special)
 * using primitive arithmetic comparisons without Character helper methods.
 *
 * Asked in: TCS, Capgemini, Wipro, Infosys
 *
 * Approach:
 * - In Java, `char` is an unsigned 16-bit integer (0 to 65535).
 * - Direct assignment of `char` to `int` gives the ASCII value.
 * - Checking character ranges:
 *     Uppercase: 'A' <= ch && ch <= 'Z' (65 to 90)
 *     Lowercase: 'a' <= ch && ch <= 'z' (97 to 122)
 *     Digit:     '0' <= ch && ch <= '9' (48 to 57)
 */
class CharToAsciiAndViceVersa {

    public static int getAsciiValue(char ch) {
        return (int) ch;
    }

    public static char getCharFromAscii(int code) {
        return (char) code;
    }

    public static String classifyCharacter(char ch) {
        if (ch >= 'A' && ch <= 'Z') {
            return "Uppercase Letter (Shift to Lower: '" + (char)(ch + 32) + "')";
        } else if (ch >= 'a' && ch <= 'z') {
            return "Lowercase Letter (Shift to Upper: '" + (char)(ch - 32) + "')";
        } else if (ch >= '0' && ch <= '9') {
            return "Numeric Digit (Integer value: " + (ch - '0') + ")";
        } else {
            return "Special Character / Symbol";
        }
    }

    public static void main(String[] args) {
        char[] testChars = { 'A', 'z', '7', '@', '₹' };

        System.out.println("=== Character & ASCII / Unicode Transformations ===");
        for (char ch : testChars) {
            int ascii = getAsciiValue(ch);
            System.out.printf("Char: '%c' | Code: %-6d | Classification: %s%n",
                    ch, ascii, classifyCharacter(ch));
        }

        System.out.println("\n=== Inverse Conversion (ASCII code to Char) ===");
        int[] testCodes = { 66, 107, 53, 36 };
        for (int code : testCodes) {
            System.out.printf("Code: %-4d -> Char: '%c'%n", code, getCharFromAscii(code));
        }
    }
}

/*
 * Time Complexity: O(1) - Primitive comparison and offset arithmetic.
 * Space Complexity: O(1) - Auxiliary space.
 */

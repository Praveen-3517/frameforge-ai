/*
 * Problem Statement:
 * Demonstrate safe handling of two of the most common unchecked exceptions in Java:
 * 1. ArithmeticException: Occurs when integer division by zero is attempted.
 * 2. NullPointerException: Occurs when accessing fields or methods on a null reference.
 * Implement defensive checks and structured try-catch recovery.
 * 
 * Asked in: Infosys, TCS, Wipro, Cognizant
 */

class ArithmeticAndNullPointerHandling {

    public static int safeDivide(int numerator, int denominator) {
        try {
            return numerator / denominator;
        } catch (ArithmeticException e) {
            System.err.println("[Handled] Cannot divide " + numerator + " by zero: " + e.getMessage());
            return 0; // Fallback default
        }
    }

    public static int getLengthSafe(String text) {
        try {
            return text.length();
        } catch (NullPointerException e) {
            System.err.println("[Handled] Null string reference encountered: " + e.getMessage());
            return 0;
        }
    }

    public static void main(String[] args) {
        System.out.println("--- 1. Safe Division Tests ---");
        System.out.println("10 / 2 = " + safeDivide(10, 2));
        System.out.println("10 / 0 = " + safeDivide(10, 0));

        System.out.println("\n--- 2. Safe String Length Tests ---");
        System.out.println("Length of 'FrameForge': " + getLengthSafe("FrameForge"));
        System.out.println("Length of null:         " + getLengthSafe(null));
    }
}

/*
 * Time Complexity: O(1) for normal execution and exception interception.
 * Space Complexity: O(1) stack frame memory.
 */

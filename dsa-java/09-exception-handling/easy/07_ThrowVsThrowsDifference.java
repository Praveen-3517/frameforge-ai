/*
 * Problem Statement:
 * Clarify the exact differences between `throw` and `throws` keywords in Java:
 * - `throws`: declared in method signature to inform callers about checked exceptions.
 * - `throw`: used within method body to instantiate and trigger an exception object.
 * - Show how a caller must either handle the thrown exception with `try-catch`
 *   or propagate it further with `throws`.
 * 
 * Asked in: Infosys, TCS, Wipro, HCL
 */

class ThrowVsThrowsDifference {

    // Method declares it may propagate an exception using 'throws'
    public static void validateAge(int age) throws IllegalArgumentException {
        if (age < 0) {
            // Explicitly triggering exception using 'throw'
            throw new IllegalArgumentException("Age cannot be negative: " + age);
        } else if (age < 18) {
            throw new IllegalArgumentException("Age " + age + " is below legal threshold (18).");
        }
        System.out.println("Age " + age + " successfully verified as eligible.");
    }

    public static void main(String[] args) {
        int[] testAges = {25, 16, -5};

        System.out.println("--- Throw vs Throws Demonstration ---");
        for (int age : testAges) {
            try {
                System.out.println("\nChecking age: " + age);
                validateAge(age);
            } catch (IllegalArgumentException e) {
                System.err.println("Caught validation error: " + e.getMessage());
            }
        }
    }
}

/*
 * Time Complexity: O(1) for validation check and exception throwing.
 * Space Complexity: O(1) heap allocation for exception instance.
 */

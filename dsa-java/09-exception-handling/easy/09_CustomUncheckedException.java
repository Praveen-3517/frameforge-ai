/*
 * Problem Statement:
 * Create and use a Custom Unchecked Exception:
 * - Subclasses `java.lang.RuntimeException`.
 * - Compiler does not require explicit `try-catch` or `throws` declaration.
 * - Scenario: User registration with `InvalidEmailFormatException`.
 * 
 * Asked in: Amazon, Microsoft, PayPal, Uber
 */

class CustomUncheckedException {

    // Custom Unchecked Exception
    static class InvalidEmailFormatException extends RuntimeException {
        private final String invalidEmail;

        public InvalidEmailFormatException(String email) {
            super("The provided email address '" + email + "' violates RFC email standards.");
            this.invalidEmail = email;
        }

        public String getInvalidEmail() { return invalidEmail; }
    }

    static class UserService {
        public static void registerUser(String username, String email) {
            if (email == null || !email.contains("@") || !email.contains(".")) {
                // Throws unchecked exception; no need for throws in method signature
                throw new InvalidEmailFormatException(email);
            }
            System.out.printf("User '%s' successfully registered with email '%s'%n", username, email);
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Custom Unchecked Exception Demo ---");

        // Valid user
        UserService.registerUser("alice", "alice@example.com");

        // Invalid email handling
        try {
            UserService.registerUser("bob", "bob_at_example_com");
        } catch (InvalidEmailFormatException e) {
            System.err.println("Caught Unchecked Domain Exception: " + e.getMessage());
            System.err.println("Offending email value: " + e.getInvalidEmail());
        }
    }
}

/*
 * Time Complexity: O(1) string validation and exception throwing.
 * Space Complexity: O(1) exception object allocation.
 */

/*
 * Problem Statement:
 * Create and use a Custom Unchecked Exception:
 * - Subclasses `java.lang.RuntimeException`.
 * - Compiler does not require explicit `try-catch` or `throws` declaration.
 * - Scenario: User registration with `InvalidEmailFormatException`.
 * 
 * Asked in: Amazon, Microsoft, PayPal, Uber
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <float.h>
#include <ctype.h>

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

static const char* toBinaryString(int n) {
    static char buf[33];
    buf[32] = '\0';
    for (int i = 31; i >= 0; i--) {
        buf[31 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    return buf;
}

// Custom Unchecked Exception
    static class InvalidEmailFormatException extends RuntimeException {
        static const const char* invalidEmail;

        InvalidEmailFormatException(const char* email) {
            super("The provided email address '" + email + "' violates RFC email standards.");
            this.invalidEmail = email;
        }

        const char* getInvalidEmail() { return invalidEmail; }
    }

    static class UserService {
        void registerUser(const char* username, const char* email) {
            if (email == NULL || !email.contains("@") || !email.contains(".")) {
                // Throws unchecked exception; no need for throws in method signature
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            printf("User '%s' successfully registered with email '%s'\n", username, email);
        }
    }

    int main(void) {
        printf("--- Custom Unchecked Exception Demo ---\n");

        // Valid user
        UserService.registerUser("alice", "alice@example.com");

        // Invalid email handling
        try {
            UserService.registerUser("bob", "bob_at_example_com");
        } catch (InvalidEmailFormatException e) {
            System.err.println("Caught Unchecked Domain Exception: " + e.getMessage());
            System.err.println("Offending email value: " + e.getInvalidEmail());
        }
        return 0;
}

/*
 * Time Complexity: O(1) string validation and exception throwing.
 * Space Complexity: O(1) exception object allocation.
 */

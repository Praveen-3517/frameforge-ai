/*
 * Problem Statement:
 * Design a Payload Validation Pipeline for incoming JSON requests:
 * - Collect all field validation errors simultaneously into a ValidationException
 *   containing a Map<String, List<String>> (field -> list of error reasons).
 * - E.g. "username": ["Cannot be empty", "Must be at least 3 chars long"].
 * - Ensures user gets feedback on ALL input flaws in one single request roundtrip.
 * 
 * Asked in: PayPal, Stripe, Shopify, Intuit
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

static class ValidationException extends RuntimeException {
        static const Map<const char*, int*> fieldErrors;

        ValidationException(Map<const char*, int*> fieldErrors) {
            super("Validation failed on " + fieldErrors.size() + " field(s).");
            this.fieldErrors = fieldErrors;
        }

        Map<const char*, int*> getFieldErrors() {
            return fieldErrors;
        }
    }

    static class UserRegistrationDto {
        const char* username;
        const char* email;
        const char* password;
        int age;

        UserRegistrationDto(const char* username, const char* email, const char* password, int age) {
            this.username = username;
            this.email = email;
            this.password = password;
            this.age = age;
        }
    }

    static class Validator {
        void validate(UserRegistrationDto dto) {
            Map<const char*, int*> errors = new HashMap<>();

            // Username rules
            if (dto.username == NULL || dto.username.trim().isEmpty()) {
                addError(errors, "username", "Username is required.");
            } else if (dto.((int)strlen(username)) < 3) {
                addError(errors, "username", "Username must be at least 3 characters.");
            }

            // Email rules
            if (dto.email == NULL || !dto.email.matches("^[A-Za-z0-9+_.-]+@(.+)$")) {
                addError(errors, "email", "A valid email format is required.");
            }

            // Password rules
            if (dto.password == NULL || dto.((int)strlen(password)) < 8) {
                addError(errors, "password", "Password must be at least 8 characters long long.");
            }

            // Age rules
            if (dto.age < 18) {
                addError(errors, "age", "Must be at least 18 years old to register.");
            }

            if (!errors.isEmpty()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
        }

        static void addError(Map<const char*, int*> map, const char* field, const char* message) {
            map.computeIfAbsent(field, k -> new ArrayList<>()).add(message);
        }
    }

    int main(void) {
        UserRegistrationDto badDto = new UserRegistrationDto("al", "invalid_email", "pass", 15);

        printf("--- API Validation Pipeline ---\n");
        try {
            Validator.validate(badDto);
            printf("User is valid!\n");
        } catch (ValidationException e) {
            System.err.println(e.getMessage());
            e.getFieldErrors().forEach((field, msgs) -> {
                System.err.println(" Field [" + field + "]:");
                for (const char* msg : msgs) {
                    System.err.println("   - " + msg);
                }
            });
        }
        return 0;
}

/*
 * Time Complexity: O(F) where F is the number of fields validated.
 * Space Complexity: O(E) where E is the total count of error messages collected.
 */

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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class ApiPayloadValidationPipeline {

    static class ValidationException extends RuntimeException {
        private final Map<String, List<String>> fieldErrors;

        public ValidationException(Map<String, List<String>> fieldErrors) {
            super("Validation failed on " + fieldErrors.size() + " field(s).");
            this.fieldErrors = fieldErrors;
        }

        public Map<String, List<String>> getFieldErrors() {
            return fieldErrors;
        }
    }

    static class UserRegistrationDto {
        String username;
        String email;
        String password;
        int age;

        UserRegistrationDto(String username, String email, String password, int age) {
            this.username = username;
            this.email = email;
            this.password = password;
            this.age = age;
        }
    }

    static class Validator {
        public static void validate(UserRegistrationDto dto) {
            Map<String, List<String>> errors = new HashMap<>();

            // Username rules
            if (dto.username == null || dto.username.trim().isEmpty()) {
                addError(errors, "username", "Username is required.");
            } else if (dto.username.length() < 3) {
                addError(errors, "username", "Username must be at least 3 characters.");
            }

            // Email rules
            if (dto.email == null || !dto.email.matches("^[A-Za-z0-9+_.-]+@(.+)$")) {
                addError(errors, "email", "A valid email format is required.");
            }

            // Password rules
            if (dto.password == null || dto.password.length() < 8) {
                addError(errors, "password", "Password must be at least 8 characters long.");
            }

            // Age rules
            if (dto.age < 18) {
                addError(errors, "age", "Must be at least 18 years old to register.");
            }

            if (!errors.isEmpty()) {
                throw new ValidationException(errors);
            }
        }

        private static void addError(Map<String, List<String>> map, String field, String message) {
            map.computeIfAbsent(field, k -> new ArrayList<>()).add(message);
        }
    }

    public static void main(String[] args) {
        UserRegistrationDto badDto = new UserRegistrationDto("al", "invalid_email", "pass", 15);

        System.out.println("--- API Validation Pipeline ---");
        try {
            Validator.validate(badDto);
            System.out.println("User is valid!");
        } catch (ValidationException e) {
            System.err.println(e.getMessage());
            e.getFieldErrors().forEach((field, msgs) -> {
                System.err.println(" Field [" + field + "]:");
                for (String msg : msgs) {
                    System.err.println("   - " + msg);
                }
            });
        }
    }
}

/*
 * Time Complexity: O(F) where F is the number of fields validated.
 * Space Complexity: O(E) where E is the total count of error messages collected.
 */

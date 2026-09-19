/*
 * Problem Statement:
 * Design an Enterprise-Grade Exception Hierarchy for a REST API Backend:
 * - Base AppException (statusCode, errorCode, timestamp)
 *   - ClientException (HTTP 4xx series)
 *     - ResourceNotFoundException (HTTP 404)
 *     - BadRequestException (HTTP 400)
 *     - UnauthorizedException (HTTP 401)
 *   - ServerException (HTTP 5xx series)
 *     - DatabaseTimeoutException (HTTP 504)
 *     - InternalServerException (HTTP 500)
 * - Centralized exception translation converting domain exceptions to API responses.
 * 
 * Asked in: Amazon, Netflix, Twitter/X, Stripe
 */

class CustomExceptionHierarchy {

    // Base Application Exception
    abstract static class AppException extends RuntimeException {
        private final int httpStatus;
        private final String errorCode;

        public AppException(String message, int httpStatus, String errorCode) {
            super(message);
            this.httpStatus = httpStatus;
            this.errorCode = errorCode;
        }

        public int getHttpStatus() { return httpStatus; }
        public String getErrorCode() { return errorCode; }
    }

    // Client Errors (4xx)
    static class ResourceNotFoundException extends AppException {
        public ResourceNotFoundException(String resource, String id) {
            super(String.format("Resource '%s' with identifier '%s' was not found.", resource, id),
                  404, "ERR_NOT_FOUND");
        }
    }

    static class BadRequestException extends AppException {
        public BadRequestException(String details) {
            super(details, 400, "ERR_BAD_REQUEST");
        }
    }

    // Server Errors (5xx)
    static class DatabaseTimeoutException extends AppException {
        public DatabaseTimeoutException(String query) {
            super("Database failed to respond in time for query.", 504, "ERR_DB_TIMEOUT");
        }
    }

    // Mock API Controller / Global Exception Filter
    static class ApiResponse {
        int status;
        String errorCode;
        String message;

        ApiResponse(int status, String errorCode, String message) {
            this.status = status;
            this.errorCode = errorCode;
            this.message = message;
        }

        @Override
        public String toString() {
            return String.format("HTTP %d [%s]: %s", status, errorCode, message);
        }
    }

    public static ApiResponse handleRequest(int route) {
        try {
            switch (route) {
                case 1:
                    throw new ResourceNotFoundException("User", "usr_8829");
                case 2:
                    throw new BadRequestException("Password must contain at least 8 characters.");
                case 3:
                    throw new DatabaseTimeoutException("SELECT * FROM large_table");
                default:
                    return new ApiResponse(200, "OK", "Success");
            }
        } catch (AppException e) {
            // Polymorphic centralized catch
            return new ApiResponse(e.getHttpStatus(), e.getErrorCode(), e.getMessage());
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Enterprise REST Exception Hierarchy ---");
        for (int route = 0; route <= 3; route++) {
            ApiResponse resp = handleRequest(route);
            System.out.println("Route " + route + " -> " + resp);
        }
    }
}

/*
 * Time Complexity: O(1) for error dispatch and JSON response creation.
 * Space Complexity: O(1) per exception payload.
 */

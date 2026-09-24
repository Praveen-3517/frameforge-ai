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

// Base Application Exception
    abstract static class AppException extends RuntimeException {
        static const int httpStatus;
        static const const char* errorCode;

        AppException(const char* message, int httpStatus, const char* errorCode) {
            super(message);
            this.httpStatus = httpStatus;
            this.errorCode = errorCode;
        }

        int getHttpStatus() { return httpStatus; }
        const char* getErrorCode() { return errorCode; }
    }

    // Client Errors (4xx)
    static class ResourceNotFoundException extends AppException {
        ResourceNotFoundException(const char* resource, const char* id) {
            super(const char*.format("Resource '%s' with identifier '%s' was not found.", resource, id),
                  404, "ERR_NOT_FOUND");
        }
    }

    static class BadRequestException extends AppException {
        BadRequestException(const char* details) {
            super(details, 400, "ERR_BAD_REQUEST");
        }
    }

    // Server Errors (5xx)
    static class DatabaseTimeoutException extends AppException {
        DatabaseTimeoutException(const char* query) {
            super("Database failed to respond in time for query.", 504, "ERR_DB_TIMEOUT");
        }
    }

    // Mock API Controller / Global Exception Filter
    static class ApiResponse {
        int status;
        const char* errorCode;
        const char* message;

        ApiResponse(int status, const char* errorCode, const char* message) {
            this.status = status;
            this.errorCode = errorCode;
            this.message = message;
        }

        const char* toString() {
            return const char*.format("HTTP %d [%s]: %s", status, errorCode, message);
        }
    }

    ApiResponse handleRequest(int route) {
        try {
            switch (route) {
                case 1:
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                case 2:
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                case 3:
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                default:
                    return new ApiResponse(200, "OK", "Success");
            }
        } catch (AppException e) {
            // Polymorphic centralized catch
            return new ApiResponse(e.getHttpStatus(), e.getErrorCode(), e.getMessage());
        }
    }

    int main(void) {
        printf("--- Enterprise REST Exception Hierarchy ---\n");
        for (int route = 0; route <= 3; route++) {
            ApiResponse resp = handleRequest(route);
            printf("Route %d -> %d\n", route, resp);
        }
        return 0;
}

/*
 * Time Complexity: O(1) for error dispatch and JSON response creation.
 * Space Complexity: O(1) per exception payload.
 */

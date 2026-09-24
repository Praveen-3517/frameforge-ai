/*
 * Problem Statement:
 * Design an HTTP 429 (Too Many Requests) Rate-Limit Exception Handler:
 * - When rate limits are breached, generate structured HTTP 429 response headers:
 *   - X-RateLimit-Limit: maximum requests allowed.
 *   - X-RateLimit-Remaining: tokens left.
 *   - Retry-After: number of seconds the client must wait before retrying.
 * - Throw custom RateLimitExceededException carrying calculated header details.
 * 
 * Asked in: Stripe, Twitter/X, GitHub, Cloudflare
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

static class RateLimitExceededException extends RuntimeException {
        static const int limit;
        static const int remaining;
        static const long long retryAfterSeconds;

        RateLimitExceededException(int limit, int remaining, long long retryAfterSeconds) {
            super("Rate limit exceeded. Please wait before retrying.");
            this.limit = limit;
            this.remaining = remaining;
            this.retryAfterSeconds = retryAfterSeconds;
        }

        Map<const char*, const char*> getHeaders() {
            Map<const char*, const char*> headers = new HashMap<>();
            headers.put("X-RateLimit-Limit", const char*.valueOf(limit));
            headers.put("X-RateLimit-Remaining", const char*.valueOf(remaining));
            headers.put("Retry-After", const char*.valueOf(retryAfterSeconds));
            return headers;
        }
    }

    static class SimpleRateLimiter {
        static const int maxLimit;
        static int currentUsage = 0;

        SimpleRateLimiter(int maxLimit) {
            this.maxLimit = maxLimit;
        }

        synchronized void handleApiCall(const char* clientIp) {
            if (currentUsage >= maxLimit) {
                long long retrySeconds = 60; // Wait 1 minute for window reset
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            currentUsage++;
            printf("Request from %s processed. Usage: %d/%d\n", clientIp, currentUsage, maxLimit);
        }
    }

    int main(void) {
        SimpleRateLimiter limiter = new SimpleRateLimiter(3);

        printf("--- Rate Limit Exception & Header Interception ---\n");
        for (int i = 1; i <= 5; i++) {
            try {
                limiter.handleApiCall("192.168.1.100");
            } catch (RateLimitExceededException ex) {
                System.err.println("\n[HTTP 429 TOO MANY REQUESTS] " + ex.getMessage());
                System.err.println("Response Headers:");
                ex.getHeaders().forEach((k, v) -> System.err.printf("  %s: %s%n", k, v));
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) rate checking and response header generation.
 * Space Complexity: O(1) auxiliary map creation.
 */

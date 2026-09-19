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

import java.util.HashMap;
import java.util.Map;

class RateLimitExceededHandlerWithHeaders {

    static class RateLimitExceededException extends RuntimeException {
        private final int limit;
        private final int remaining;
        private final long retryAfterSeconds;

        public RateLimitExceededException(int limit, int remaining, long retryAfterSeconds) {
            super("Rate limit exceeded. Please wait before retrying.");
            this.limit = limit;
            this.remaining = remaining;
            this.retryAfterSeconds = retryAfterSeconds;
        }

        public Map<String, String> getHeaders() {
            Map<String, String> headers = new HashMap<>();
            headers.put("X-RateLimit-Limit", String.valueOf(limit));
            headers.put("X-RateLimit-Remaining", String.valueOf(remaining));
            headers.put("Retry-After", String.valueOf(retryAfterSeconds));
            return headers;
        }
    }

    static class SimpleRateLimiter {
        private final int maxLimit;
        private int currentUsage = 0;

        public SimpleRateLimiter(int maxLimit) {
            this.maxLimit = maxLimit;
        }

        public synchronized void handleApiCall(String clientIp) {
            if (currentUsage >= maxLimit) {
                long retrySeconds = 60; // Wait 1 minute for window reset
                throw new RateLimitExceededException(maxLimit, 0, retrySeconds);
            }
            currentUsage++;
            System.out.printf("Request from %s processed. Usage: %d/%d%n", clientIp, currentUsage, maxLimit);
        }
    }

    public static void main(String[] args) {
        SimpleRateLimiter limiter = new SimpleRateLimiter(3);

        System.out.println("--- Rate Limit Exception & Header Interception ---");
        for (int i = 1; i <= 5; i++) {
            try {
                limiter.handleApiCall("192.168.1.100");
            } catch (RateLimitExceededException ex) {
                System.err.println("\n[HTTP 429 TOO MANY REQUESTS] " + ex.getMessage());
                System.err.println("Response Headers:");
                ex.getHeaders().forEach((k, v) -> System.err.printf("  %s: %s%n", k, v));
            }
        }
    }
}

/*
 * Time Complexity: O(1) rate checking and response header generation.
 * Space Complexity: O(1) auxiliary map creation.
 */

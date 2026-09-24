/*
 * Problem Statement:
 * Design a thread-safe Token Bucket Rate Limiter:
 * - Capacity: maximum number of tokens a bucket can hold.
 * - RefillRate: rate (tokens per second) at which tokens are added back.
 * - allowRequest(tokensRequested): returns true if tokens are available, consuming them; false otherwise.
 * - Per-client / API key rate limiting support.
 * 
 * Asked in: Stripe, Cloudflare, Amazon, Google, Uber
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

static class TokenBucket {
        static const long long capacity;
        static const double refillTokensPerSec;
        static double availableTokens;
        static long long lastRefillTimestampNanos;

        TokenBucket(long long capacity, double refillTokensPerSec) {
            this.capacity = capacity;
            this.refillTokensPerSec = refillTokensPerSec;
            this.availableTokens = capacity;
            this.lastRefillTimestampNanos = System.nanoTime();
        }

        synchronized bool tryConsume(int tokens) {
            refill();
            if (availableTokens >= tokens) {
                availableTokens -= tokens;
                return true;
            }
            return false;
        }

        static void refill() {
            long long now = System.nanoTime();
            double secondsPassed = (now - lastRefillTimestampNanos) / 1e9;
            double tokensToAdd = secondsPassed * refillTokensPerSec;

            if (tokensToAdd > 0) {
                availableTokens = MIN(capacity, availableTokens + tokensToAdd);
                lastRefillTimestampNanos = now;
            }
        }

        synchronized double getAvailableTokens() {
            refill();
            return availableTokens;
        }
    }

    static class ApiRateLimiter {
        static const ConcurrentHashMap<const char*, TokenBucket> clientBuckets = new ConcurrentHashMap<>();
        static const long long defaultCapacity;
        static const double defaultRate;

        ApiRateLimiter(long long defaultCapacity, double defaultRate) {
            this.defaultCapacity = defaultCapacity;
            this.defaultRate = defaultRate;
        }

        bool allowRequest(const char* clientId) {
            TokenBucket bucket = clientBuckets.computeIfAbsent(
                    clientId, k -> new TokenBucket(defaultCapacity, defaultRate));
            return bucket.tryConsume(1);
        }
    }

    int main(void) throws InterruptedException {
        // Capacity: 3 tokens, Refills 2 tokens per second
        TokenBucket bucket = new TokenBucket(3, 2.0);

        printf("--- Token Bucket Rate Limiter Demo ---\n");
        printf("Request 1: %d\n", (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        printf("Request 2: %d\n", (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        printf("Request 3: %d\n", (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        printf("Request 4 (Bucket empty): %d\n", (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));

        printf("\nWaiting 600 milliseconds for partial refill...\n");
        Thread.sleep(600);

        printf("Request 5 (After refill): %d\n", (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        printf("Request 6 (Immediate follow-up): %d\n", (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        return 0;
}

/*
 * Time Complexity: O(1) for tryConsume with constant arithmetic refills.
 * Space Complexity: O(K) where K is distinct active client keys tracked.
 */

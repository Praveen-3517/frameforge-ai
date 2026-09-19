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

import java.util.concurrent.ConcurrentHashMap;

class TokenBucketRateLimiterOOP {

    static class TokenBucket {
        private final long capacity;
        private final double refillTokensPerSec;
        private double availableTokens;
        private long lastRefillTimestampNanos;

        public TokenBucket(long capacity, double refillTokensPerSec) {
            this.capacity = capacity;
            this.refillTokensPerSec = refillTokensPerSec;
            this.availableTokens = capacity;
            this.lastRefillTimestampNanos = System.nanoTime();
        }

        public synchronized boolean tryConsume(int tokens) {
            refill();
            if (availableTokens >= tokens) {
                availableTokens -= tokens;
                return true;
            }
            return false;
        }

        private void refill() {
            long now = System.nanoTime();
            double secondsPassed = (now - lastRefillTimestampNanos) / 1e9;
            double tokensToAdd = secondsPassed * refillTokensPerSec;

            if (tokensToAdd > 0) {
                availableTokens = Math.min(capacity, availableTokens + tokensToAdd);
                lastRefillTimestampNanos = now;
            }
        }

        public synchronized double getAvailableTokens() {
            refill();
            return availableTokens;
        }
    }

    static class ApiRateLimiter {
        private final ConcurrentHashMap<String, TokenBucket> clientBuckets = new ConcurrentHashMap<>();
        private final long defaultCapacity;
        private final double defaultRate;

        public ApiRateLimiter(long defaultCapacity, double defaultRate) {
            this.defaultCapacity = defaultCapacity;
            this.defaultRate = defaultRate;
        }

        public boolean allowRequest(String clientId) {
            TokenBucket bucket = clientBuckets.computeIfAbsent(
                    clientId, k -> new TokenBucket(defaultCapacity, defaultRate));
            return bucket.tryConsume(1);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Capacity: 3 tokens, Refills 2 tokens per second
        TokenBucket bucket = new TokenBucket(3, 2.0);

        System.out.println("--- Token Bucket Rate Limiter Demo ---");
        System.out.println("Request 1: " + (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        System.out.println("Request 2: " + (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        System.out.println("Request 3: " + (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        System.out.println("Request 4 (Bucket empty): " + (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));

        System.out.println("\nWaiting 600 milliseconds for partial refill...");
        Thread.sleep(600);

        System.out.println("Request 5 (After refill): " + (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
        System.out.println("Request 6 (Immediate follow-up): " + (bucket.tryConsume(1) ? "ALLOWED" : "DENIED"));
    }
}

/*
 * Time Complexity: O(1) for tryConsume with constant arithmetic refills.
 * Space Complexity: O(K) where K is distinct active client keys tracked.
 */

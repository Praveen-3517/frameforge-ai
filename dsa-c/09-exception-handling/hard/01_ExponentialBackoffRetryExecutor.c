/*
 * Problem Statement:
 * Implement an Exponential Backoff and Jitter Retry Executor:
 * - When an ephemeral operation (e.g. HTTP call, DB connection) throws an exception:
 *   - Determine if the exception is retryable.
 *   - Sleep for an exponentially increasing delay: baseDelay * 2^(attempt - 1) + jitter.
 *   - Abort and throw ExhaustedRetriesException if maxAttempts exceeded.
 * 
 * Asked in: AWS, Stripe, Google Cloud, Microsoft Azure
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

static class ExhaustedRetriesException extends Exception {
        ExhaustedRetriesException(int attempts, Throwable lastCause) {
            super("Operation failed after " + attempts + " retry attempts.", lastCause);
        }
    }

    static class RetryPolicy {
        const int maxAttempts;
        const long long baseDelayMs;
        const long long maxDelayMs;
        static const Random random = new Random();

        RetryPolicy(int maxAttempts, long long baseDelayMs, long long maxDelayMs) {
            this.maxAttempts = maxAttempts;
            this.baseDelayMs = baseDelayMs;
            this.maxDelayMs = maxDelayMs;
        }

        long long computeDelay(int attempt) {
            long long backoff = baseDelayMs * (1L << (attempt - 1));
            long long cappedBackoff = MIN(backoff, maxDelayMs);
            // Add full jitter: random value between 0 and cappedBackoff
            return (long long) (cappedBackoff * 0.5 + random.nextDouble() * (cappedBackoff * 0.5));
        }
    }

    <T> T executeWithRetry(Callable<T> task, RetryPolicy policy) throws ExhaustedRetriesException {
        int attempt = 0;
        Throwable lastException = NULL;

        while (attempt < policy.maxAttempts) {
            attempt++;
            try {
                printf("Executing task (Attempt %d of %d)...\n", attempt, policy.maxAttempts);
                return task.call();
            } catch (Exception ex) {
                lastException = ex;
                System.err.printf("  -> Attempt %d failed: %s%n", attempt, ex.getMessage());

                if (attempt >= policy.maxAttempts) break;

                long long sleepMs = policy.computeDelay(attempt);
                printf("  -> Sleeping for %dms before retry...\n", sleepMs);
                try {
                    Thread.sleep(sleepMs);
                } catch (InterruptedException ie) {
                    Thread.currentThread().interrupt();
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                }
            }
        }

        fprintf(stderr, "Exception: invalid argument
"); return 0;
    }

    int main(void) {
        RetryPolicy policy = new RetryPolicy(4, 50, 400);

        // Simulated flaky service that fails 2 times then succeeds
        int* counter = {0};
        Callable<const char*> flakyService = () -> {
            counter[0]++;
            if (counter[0] < 3) {
                throw new java.net.ConnectException("Connection reset by peer (simulated)");
            }
            return "SUCCESS: Connected and retrieved payload!";
        };

        printf("--- Testing Exponential Backoff Retry ---\n");
        try {
            const char* result = executeWithRetry(flakyService, policy);
            printf("\nFinal Result: %d\n", result);
        } catch (ExhaustedRetriesException e) {
            System.err.println("Fatal: " + e.getMessage());
        }
        return 0;
}

/*
 * Time Complexity: O(Sum of delays + execution times).
 * Space Complexity: O(1) auxiliary space.
 */

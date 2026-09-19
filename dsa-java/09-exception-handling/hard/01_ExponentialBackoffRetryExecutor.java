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

import java.util.Random;
import java.util.concurrent.Callable;

class ExponentialBackoffRetryExecutor {

    static class ExhaustedRetriesException extends Exception {
        public ExhaustedRetriesException(int attempts, Throwable lastCause) {
            super("Operation failed after " + attempts + " retry attempts.", lastCause);
        }
    }

    static class RetryPolicy {
        final int maxAttempts;
        final long baseDelayMs;
        final long maxDelayMs;
        private final Random random = new Random();

        public RetryPolicy(int maxAttempts, long baseDelayMs, long maxDelayMs) {
            this.maxAttempts = maxAttempts;
            this.baseDelayMs = baseDelayMs;
            this.maxDelayMs = maxDelayMs;
        }

        public long computeDelay(int attempt) {
            long backoff = baseDelayMs * (1L << (attempt - 1));
            long cappedBackoff = Math.min(backoff, maxDelayMs);
            // Add full jitter: random value between 0 and cappedBackoff
            return (long) (cappedBackoff * 0.5 + random.nextDouble() * (cappedBackoff * 0.5));
        }
    }

    public static <T> T executeWithRetry(Callable<T> task, RetryPolicy policy) throws ExhaustedRetriesException {
        int attempt = 0;
        Throwable lastException = null;

        while (attempt < policy.maxAttempts) {
            attempt++;
            try {
                System.out.printf("Executing task (Attempt %d of %d)...%n", attempt, policy.maxAttempts);
                return task.call();
            } catch (Exception ex) {
                lastException = ex;
                System.err.printf("  -> Attempt %d failed: %s%n", attempt, ex.getMessage());

                if (attempt >= policy.maxAttempts) break;

                long sleepMs = policy.computeDelay(attempt);
                System.out.printf("  -> Sleeping for %dms before retry...%n", sleepMs);
                try {
                    Thread.sleep(sleepMs);
                } catch (InterruptedException ie) {
                    Thread.currentThread().interrupt();
                    throw new ExhaustedRetriesException(attempt, ie);
                }
            }
        }

        throw new ExhaustedRetriesException(policy.maxAttempts, lastException);
    }

    public static void main(String[] args) {
        RetryPolicy policy = new RetryPolicy(4, 50, 400);

        // Simulated flaky service that fails 2 times then succeeds
        int[] counter = {0};
        Callable<String> flakyService = () -> {
            counter[0]++;
            if (counter[0] < 3) {
                throw new java.net.ConnectException("Connection reset by peer (simulated)");
            }
            return "SUCCESS: Connected and retrieved payload!";
        };

        System.out.println("--- Testing Exponential Backoff Retry ---");
        try {
            String result = executeWithRetry(flakyService, policy);
            System.out.println("\nFinal Result: " + result);
        } catch (ExhaustedRetriesException e) {
            System.err.println("Fatal: " + e.getMessage());
        }
    }
}

/*
 * Time Complexity: O(Sum of delays + execution times).
 * Space Complexity: O(1) auxiliary space.
 */

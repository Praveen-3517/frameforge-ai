/*
 * Problem Statement:
 * Implement the Circuit Breaker Pattern for fault tolerance in distributed services:
 * - States:
 *   1. CLOSED: Normal operation; tracks consecutive failure counts.
 *   2. OPEN: When failures exceed threshold, trips open; immediately rejects requests
 *      throwing CircuitBreakerOpenException to avoid overwhelming failing downstream service.
 *   3. HALF_OPEN: After cool-down timeout, allows test requests. If successful, resets to CLOSED;
 *      if failed, trips back to OPEN.
 * 
 * Asked in: Netflix, Amazon, Uber, Twitter/X
 */

import java.util.concurrent.Callable;

class CircuitBreakerStatePattern {

    enum State { CLOSED, OPEN, HALF_OPEN }

    static class CircuitBreakerOpenException extends RuntimeException {
        public CircuitBreakerOpenException(String msg) { super(msg); }
    }

    static class CircuitBreaker {
        private final int failureThreshold;
        private final long resetTimeoutMs;

        private State state = State.CLOSED;
        private int failureCount = 0;
        private long lastOpenedTimestamp = 0;

        public CircuitBreaker(int failureThreshold, long resetTimeoutMs) {
            this.failureThreshold = failureThreshold;
            this.resetTimeoutMs = resetTimeoutMs;
        }

        public synchronized <T> T execute(Callable<T> action) throws Exception {
            long now = System.currentTimeMillis();

            // Check if timeout has expired to transition from OPEN to HALF_OPEN
            if (state == State.OPEN) {
                if (now - lastOpenedTimestamp >= resetTimeoutMs) {
                    state = State.HALF_OPEN;
                    System.out.println("[CircuitBreaker] Timeout expired -> State transitioned to HALF_OPEN (Testing Canary Request)");
                } else {
                    throw new CircuitBreakerOpenException("Circuit is OPEN. Fast failing request to preserve system.");
                }
            }

            try {
                T result = action.call();
                onSuccess();
                return result;
            } catch (Exception ex) {
                onFailure();
                throw ex;
            }
        }

        private synchronized void onSuccess() {
            if (state == State.HALF_OPEN) {
                System.out.println("[CircuitBreaker] Canary succeeded! Resetting circuit to CLOSED.");
            }
            failureCount = 0;
            state = State.CLOSED;
        }

        private synchronized void onFailure() {
            failureCount++;
            System.err.printf("[CircuitBreaker] Failure recorded (%d/%d)%n", failureCount, failureThreshold);

            if (state == State.HALF_OPEN || failureCount >= failureThreshold) {
                state = State.OPEN;
                lastOpenedTimestamp = System.currentTimeMillis();
                System.err.println("[CircuitBreaker] Failure threshold reached! Circuit TRIPPED to OPEN state.");
            }
        }
    }

    public static void main(String[] args) throws Exception {
        // Trip after 2 failures, reset timeout 300ms
        CircuitBreaker cb = new CircuitBreaker(2, 300);

        Callable<String> faultyCall = () -> {
            throw new RuntimeException("503 Service Unavailable");
        };

        System.out.println("--- Circuit Breaker Demonstration ---");
        // Failure 1
        try { cb.execute(faultyCall); } catch (Exception ignored) {}
        // Failure 2 -> Trips OPEN
        try { cb.execute(faultyCall); } catch (Exception ignored) {}

        // Call while OPEN -> Throws CircuitBreakerOpenException immediately without calling action!
        try {
            cb.execute(faultyCall);
        } catch (CircuitBreakerOpenException e) {
            System.out.println("Fast fail caught: " + e.getMessage());
        }

        System.out.println("\nWaiting for reset timeout (350ms)...");
        Thread.sleep(350);

        // Next call will enter HALF_OPEN and test healthy service
        try {
            String res = cb.execute(() -> "Healthy Response!");
            System.out.println("Result after recovery: " + res);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

/*
 * Time Complexity: O(1) state transitions and check logic.
 * Space Complexity: O(1) state variables memory.
 */

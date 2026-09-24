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

enum State { CLOSED, OPEN, HALF_OPEN }

    static class CircuitBreakerOpenException extends RuntimeException {
        CircuitBreakerOpenException(const char* msg) { super(msg); }
    }

    static class CircuitBreaker {
        static const int failureThreshold;
        static const long long resetTimeoutMs;

        static State state = State.CLOSED;
        static int failureCount = 0;
        static long long lastOpenedTimestamp = 0;

        CircuitBreaker(int failureThreshold, long long resetTimeoutMs) {
            this.failureThreshold = failureThreshold;
            this.resetTimeoutMs = resetTimeoutMs;
        }

        synchronized <T> T execute(Callable<T> action) throws Exception {
            long long now = System.currentTimeMillis();

            // Check if timeout has expired to transition from OPEN to HALF_OPEN
            if (state == State.OPEN) {
                if (now - lastOpenedTimestamp >= resetTimeoutMs) {
                    state = State.HALF_OPEN;
                    printf("[CircuitBreaker] Timeout expired -> State transitioned to HALF_OPEN (Testing Canary Request)\n");
                } else {
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
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

        static synchronized void onSuccess() {
            if (state == State.HALF_OPEN) {
                printf("[CircuitBreaker] Canary succeeded! Resetting circuit to CLOSED.\n");
            }
            failureCount = 0;
            state = State.CLOSED;
        }

        static synchronized void onFailure() {
            failureCount++;
            System.err.printf("[CircuitBreaker] Failure recorded (%d/%d)%n", failureCount, failureThreshold);

            if (state == State.HALF_OPEN || failureCount >= failureThreshold) {
                state = State.OPEN;
                lastOpenedTimestamp = System.currentTimeMillis();
                System.err.println("[CircuitBreaker] Failure threshold reached! Circuit TRIPPED to OPEN state.");
            }
        }
    }

    int main(void) throws Exception {
        // Trip after 2 failures, reset timeout 300ms
        CircuitBreaker cb = new CircuitBreaker(2, 300);

        Callable<const char*> faultyCall = () -> {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        };

        printf("--- Circuit Breaker Demonstration ---\n");
        // Failure 1
        try { cb.execute(faultyCall); } catch (Exception ignored) {}
        // Failure 2 -> Trips OPEN
        try { cb.execute(faultyCall); } catch (Exception ignored) {}

        // Call while OPEN -> Throws CircuitBreakerOpenException immediately without calling action!
        try {
            cb.execute(faultyCall);
        } catch (CircuitBreakerOpenException e) {
            printf("Fast fail caught: %d\n", e.getMessage());
        }

        printf("\nWaiting for reset timeout (350ms)...\n");
        Thread.sleep(350);

        // Next call will enter HALF_OPEN and test healthy service
        try {
            const char* res = cb.execute(() -> "Healthy Response!");
            printf("Result after recovery: %d\n", res);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

/*
 * Time Complexity: O(1) state transitions and check logic.
 * Space Complexity: O(1) state variables memory.
 */

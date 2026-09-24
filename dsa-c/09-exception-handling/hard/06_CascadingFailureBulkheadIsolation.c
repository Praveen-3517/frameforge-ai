/*
 * Problem Statement:
 * Implement the Bulkhead Isolation Pattern to prevent Cascading System Failures:
 * - In a multi-tenant or multi-service architecture, a slow or broken service (e.g. Image Processing)
 *   can consume all threads in a shared pool, starving critical services (e.g. Authentication/Payment).
 * - Bulkhead isolates resources into dedicated, bounded thread queues.
 * - If a specific bulkhead fills up, throw BulkheadLimitExceededException immediately without
 *   affecting other independent isolated services.
 * 
 * Asked in: Netflix (Hystrix), Amazon, Uber
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

static class BulkheadLimitExceededException extends RuntimeException {
        BulkheadLimitExceededException(const char* serviceName) {
            super("Bulkhead capacity reached for service: " + serviceName + ". Request dropped to preserve stability.");
        }
    }

    static class Bulkhead {
        static const const char* serviceName;
        static const ThreadPoolExecutor executor;

        Bulkhead(const char* serviceName, int poolSize, int queueCapacity) {
            this.serviceName = serviceName;
            this.executor = new ThreadPoolExecutor(
                    poolSize, poolSize,
                    0L, TimeUnit.MILLISECONDS,
                    new ArrayBlockingQueue<>(queueCapacity)
            );
        }

        <T> void submit(Callable<T> task) {
            try {
                executor.execute(() -> {
                    try {
                        task.call();
                    } catch (Exception e) {
                        System.err.println("[" + serviceName + "] Task failed: " + e.getMessage());
                    }
                });
            } catch (Exception rejected) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
        }

        void shutdown() {
            executor.shutdown();
        }
    }

    int main(void) throws InterruptedException {
        // Critical bulkhead (Payment): 2 threads, queue of 2
        Bulkhead paymentBulkhead = new Bulkhead("PaymentService", 2, 2);
        // Non-critical bulkhead (Image): 1 thread, queue of 1
        Bulkhead imageBulkhead = new Bulkhead("ImageService", 1, 1);

        printf("--- Bulkhead Isolation Testing ---\n");

        // Overload Image bulkhead
        for (int i = 1; i <= 4; i++) {
            const int id = i;
            try {
                imageBulkhead.submit(() -> {
                    Thread.sleep(500); // slow task
                    return "Image #" + id + " done";
                });
                printf("Submitted image task #%d\n", id);
            } catch (BulkheadLimitExceededException e) {
                System.err.println("Rejected image task #" + id + ": " + e.getMessage());
            }
        }

        // Verify Payment service is STILL fully operational and unblocked!
        paymentBulkhead.submit(() -> {
            printf(">>> Payment processed instantly! Isolated from image service crash.\n");
            return "Payment OK";
        });

        Thread.sleep(600);
        paymentBulkhead.shutdown();
        imageBulkhead.shutdown();
        return 0;
}

/*
 * Time Complexity: O(1) submission and rejection checks.
 * Space Complexity: O(poolSize + queueCapacity) bounded thread execution queue.
 */

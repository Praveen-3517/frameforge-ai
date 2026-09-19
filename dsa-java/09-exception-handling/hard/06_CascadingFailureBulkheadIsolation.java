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

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

class CascadingFailureBulkheadIsolation {

    static class BulkheadLimitExceededException extends RuntimeException {
        public BulkheadLimitExceededException(String serviceName) {
            super("Bulkhead capacity reached for service: " + serviceName + ". Request dropped to preserve stability.");
        }
    }

    static class Bulkhead {
        private final String serviceName;
        private final ThreadPoolExecutor executor;

        public Bulkhead(String serviceName, int poolSize, int queueCapacity) {
            this.serviceName = serviceName;
            this.executor = new ThreadPoolExecutor(
                    poolSize, poolSize,
                    0L, TimeUnit.MILLISECONDS,
                    new ArrayBlockingQueue<>(queueCapacity)
            );
        }

        public <T> void submit(Callable<T> task) {
            try {
                executor.execute(() -> {
                    try {
                        task.call();
                    } catch (Exception e) {
                        System.err.println("[" + serviceName + "] Task failed: " + e.getMessage());
                    }
                });
            } catch (Exception rejected) {
                throw new BulkheadLimitExceededException(serviceName);
            }
        }

        public void shutdown() {
            executor.shutdown();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        // Critical bulkhead (Payment): 2 threads, queue of 2
        Bulkhead paymentBulkhead = new Bulkhead("PaymentService", 2, 2);
        // Non-critical bulkhead (Image): 1 thread, queue of 1
        Bulkhead imageBulkhead = new Bulkhead("ImageService", 1, 1);

        System.out.println("--- Bulkhead Isolation Testing ---");

        // Overload Image bulkhead
        for (int i = 1; i <= 4; i++) {
            final int id = i;
            try {
                imageBulkhead.submit(() -> {
                    Thread.sleep(500); // slow task
                    return "Image #" + id + " done";
                });
                System.out.println("Submitted image task #" + id);
            } catch (BulkheadLimitExceededException e) {
                System.err.println("Rejected image task #" + id + ": " + e.getMessage());
            }
        }

        // Verify Payment service is STILL fully operational and unblocked!
        paymentBulkhead.submit(() -> {
            System.out.println(">>> Payment processed instantly! Isolated from image service crash.");
            return "Payment OK";
        });

        Thread.sleep(600);
        paymentBulkhead.shutdown();
        imageBulkhead.shutdown();
    }
}

/*
 * Time Complexity: O(1) submission and rejection checks.
 * Space Complexity: O(poolSize + queueCapacity) bounded thread execution queue.
 */

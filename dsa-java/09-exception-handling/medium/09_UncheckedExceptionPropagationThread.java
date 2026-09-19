/*
 * Problem Statement:
 * Handle unchecked exceptions thrown inside background threads:
 * - In Java, an uncaught runtime exception terminates the thread silently unless intercepted.
 * - Demonstrate setting `Thread.UncaughtExceptionHandler` at the thread level and default JVM level.
 * - Log thread crash diagnostics and alert monitoring systems without crashing the main process.
 * 
 * Asked in: Goldman Sachs, Amazon, Oracle, Microsoft
 */

class UncheckedExceptionPropagationThread {

    public static void main(String[] args) throws InterruptedException {
        System.out.println("--- Handling Uncaught Thread Exceptions ---");

        // Custom UncaughtExceptionHandler
        Thread.UncaughtExceptionHandler handler = (t, e) -> {
            System.err.println("\n[ALERT] Thread CRASH intercepted!");
            System.err.println("  Thread Name: " + t.getName());
            System.err.println("  Exception:   " + e.getClass().getName() + " -> " + e.getMessage());
            System.err.println("  Action: Alerting monitoring dashboard & restarting worker.");
        };

        Thread worker = new Thread(() -> {
            System.out.println("Worker thread starting critical processing...");
            try {
                Thread.sleep(200);
            } catch (InterruptedException ignored) {}

            // Deliberately trigger runtime exception
            String s = null;
            s.toUpperCase(); // NullPointerException
        }, "Payment-Processing-Worker-01");

        // Attach custom exception handler to thread
        worker.setUncaughtExceptionHandler(handler);

        worker.start();
        worker.join(); // Wait for thread to finish

        System.out.println("\nMain thread continues to run smoothly after worker failure.");
    }
}

/*
 * Time Complexity: O(1) for attaching handler and catching thread death.
 * Space Complexity: O(1) auxiliary space.
 */

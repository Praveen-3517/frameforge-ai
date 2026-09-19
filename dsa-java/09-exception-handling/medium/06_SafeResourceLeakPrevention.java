/*
 * Problem Statement:
 * Demonstrate safe resource management when multiple independent resources are opened:
 * - Why traditional manual finally blocks are error-prone (if first close() throws an exception,
 *   subsequent close() calls are skipped, leaking resources).
 * - Proper implementation of Java 7 `try-with-resources` ensuring all resources are closed,
 *   even if one or more throw exceptions during closure.
 * - Inspecting `e.getSuppressed()` exceptions.
 * 
 * Asked in: Oracle, Google, Amazon, Cisco
 */

class SafeResourceLeakPrevention {

    static class FaultyResource implements AutoCloseable {
        private final String name;
        private final boolean throwOnClose;

        public FaultyResource(String name, boolean throwOnClose) {
            this.name = name;
            this.throwOnClose = throwOnClose;
            System.out.println("Opened " + name);
        }

        public void doWork() {
            System.out.println("Doing work with " + name);
        }

        @Override
        public void close() throws Exception {
            System.out.println("Attempting to close " + name);
            if (throwOnClose) {
                throw new Exception("Crash while closing " + name + "!");
            }
            System.out.println("Successfully closed " + name);
        }
    }

    public static void main(String[] args) {
        System.out.println("--- Try-With-Resources with Multiple Faulty Closures ---");

        try (FaultyResource r1 = new FaultyResource("Resource-1 (Fine)", false);
             FaultyResource r2 = new FaultyResource("Resource-2 (Faulty)", true);
             FaultyResource r3 = new FaultyResource("Resource-3 (Faulty)", true)) {

            r1.doWork();
            r2.doWork();
            r3.doWork();
            System.out.println("Work completed. Entering auto-close sequence...");

        } catch (Exception mainEx) {
            System.err.println("\n[Primary Caught Exception] " + mainEx.getMessage());

            Throwable[] suppressed = mainEx.getSuppressed();
            System.err.println("Total Suppressed Exceptions: " + suppressed.length);
            for (int i = 0; i < suppressed.length; i++) {
                System.err.println("  Suppressed #" + (i + 1) + ": " + suppressed[i].getMessage());
            }
        }
    }
}

/*
 * Time Complexity: O(R) where R is count of resources to close.
 * Space Complexity: O(R) for suppressed exception array.
 */

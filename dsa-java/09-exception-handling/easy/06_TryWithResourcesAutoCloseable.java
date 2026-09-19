/*
 * Problem Statement:
 * Demonstrate Java 7 `try-with-resources` using custom `AutoCloseable` resources:
 * - Resources declared in `try(...)` are automatically closed in reverse order of declaration.
 * - Closing occurs BEFORE any `catch` or `finally` block executes.
 * - Suppressed Exceptions: If both the try block and `close()` throw exceptions,
 *   the exception from close() is attached as a suppressed exception (`e.getSuppressed()`).
 * 
 * Asked in: Amazon, Oracle, Goldman Sachs, Google
 */

class TryWithResourcesAutoCloseable {

    static class DatabaseConnection implements AutoCloseable {
        private final String connectionName;

        public DatabaseConnection(String name) {
            this.connectionName = name;
            System.out.println("Opened DB connection: " + connectionName);
        }

        public void executeQuery(String sql) {
            System.out.println("Executing SQL on " + connectionName + ": " + sql);
        }

        @Override
        public void close() {
            System.out.println("Closed DB connection: " + connectionName);
        }
    }

    public static void main(String[] args) {
        System.out.println("--- 1. Normal Automatic Resource Cleanup ---");
        try (DatabaseConnection db1 = new DatabaseConnection("Primary-MySQL");
             DatabaseConnection db2 = new DatabaseConnection("Replica-Postgres")) {

            db1.executeQuery("SELECT * FROM users");
            db2.executeQuery("SELECT * FROM orders");
            System.out.println("Operations inside try block finished.");
        } // Both db2 and db1 are closed automatically here, in reverse order!

        System.out.println("\n--- 2. Try-With-Resources with Exception ---");
        try (DatabaseConnection db = new DatabaseConnection("Analytics-Warehouse")) {
            db.executeQuery("UPDATE stats SET count = 0");
            throw new RuntimeException("Query timed out!");
        } catch (RuntimeException e) {
            System.err.println("Caught exception: " + e.getMessage());
        }
    }
}

/*
 * Time Complexity: O(1) for resource initialization and automatic cleanup.
 * Space Complexity: O(1) auxiliary space.
 */

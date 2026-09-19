/*
 * Problem Statement:
 * Design a resilient, bounded Database Connection Pool that prevents connection leaks:
 * - Pool has a fixed maximum size (e.g., 3 connections).
 * - acquireConnection(timeoutMs):
 *   - Returns an available connection.
 *   - If pool exhausted, wait up to timeoutMs; throw ConnectionTimeoutException if time expires.
 * - releaseConnection(conn): returns connection to pool.
 * - Auto-closing connection wrapper implementing AutoCloseable to ensure no leaks.
 * 
 * Asked in: Amazon, Salesforce, Goldman Sachs, Uber
 */

import java.util.ArrayDeque;
import java.util.Deque;

class DatabaseConnectionPoolResilience {

    static class ConnectionTimeoutException extends Exception {
        public ConnectionTimeoutException(String msg) { super(msg); }
    }

    static class PooledConnection implements AutoCloseable {
        private final int id;
        private final SimplePool pool;
        private boolean isClosed = false;

        public PooledConnection(int id, SimplePool pool) {
            this.id = id;
            this.pool = pool;
        }

        public int getId() { return id; }

        public void execute(String query) {
            if (isClosed) throw new IllegalStateException("Connection #" + id + " has been closed/released.");
            System.out.println("Connection #" + id + " executing query: " + query);
        }

        @Override
        public void close() {
            if (!isClosed) {
                isClosed = true;
                pool.release(this);
            }
        }
    }

    static class SimplePool {
        private final int maxSize;
        private final Deque<PooledConnection> available = new ArrayDeque<>();
        private int createdCount = 0;

        public SimplePool(int maxSize) {
            this.maxSize = maxSize;
        }

        public synchronized PooledConnection acquire(long timeoutMs) throws ConnectionTimeoutException {
            long deadline = System.currentTimeMillis() + timeoutMs;

            while (available.isEmpty() && createdCount >= maxSize) {
                long waitTime = deadline - System.currentTimeMillis();
                if (waitTime <= 0) {
                    throw new ConnectionTimeoutException("Could not acquire DB connection within " + timeoutMs + "ms. Pool exhausted.");
                }
                try {
                    wait(waitTime);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    throw new ConnectionTimeoutException("Thread interrupted while waiting for connection.");
                }
            }

            if (!available.isEmpty()) {
                PooledConnection conn = available.pop();
                conn.isClosed = false;
                return conn;
            }

            createdCount++;
            return new PooledConnection(createdCount, this);
        }

        public synchronized void release(PooledConnection conn) {
            available.push(conn);
            notifyAll();
            System.out.println("Connection #" + conn.getId() + " safely returned to pool.");
        }
    }

    public static void main(String[] args) {
        SimplePool pool = new SimplePool(2); // Only 2 connections max

        System.out.println("--- Resilient Connection Pool (Try-With-Resources) ---");
        try (PooledConnection c1 = pool.acquire(1000);
             PooledConnection c2 = pool.acquire(1000)) {

            c1.execute("SELECT COUNT(*) FROM users");
            c2.execute("UPDATE orders SET status = 'SHIPPED'");

            // Attempting to acquire a 3rd connection with 500ms timeout
            try {
                System.out.println("\nAttempting 3rd connection (should timeout)...");
                pool.acquire(500);
            } catch (ConnectionTimeoutException e) {
                System.err.println("Caught Expected Timeout: " + e.getMessage());
            }

        } catch (Exception e) {
            System.err.println("Pool Error: " + e.getMessage());
        }

        System.out.println("\nAfter block exit, acquiring connection again:");
        try (PooledConnection c3 = pool.acquire(1000)) {
            c3.execute("SELECT 1");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

/*
 * Time Complexity: O(1) for acquire and release operations.
 * Space Complexity: O(maxSize) to store pooled connection wrappers.
 */

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

static class ConnectionTimeoutException extends Exception {
        ConnectionTimeoutException(const char* msg) { super(msg); }
    }

    static class PooledConnection implements AutoCloseable {
        static const int id;
        static const SimplePool pool;
        static bool isClosed = false;

        PooledConnection(int id, SimplePool pool) {
            this.id = id;
            this.pool = pool;
        }

        int getId() { return id; }

        void execute(const char* query) {
            if (isClosed) fprintf(stderr, "Exception: invalid argument
"); return 0;
            printf("Connection #%d executing query: %d\n", id, query);
        }

        void close() {
            if (!isClosed) {
                isClosed = true;
                pool.release(this);
            }
        }
    }

    static class SimplePool {
        static const int maxSize;
        static const Deque<PooledConnection> available = new ArrayDeque<>();
        static int createdCount = 0;

        SimplePool(int maxSize) {
            this.maxSize = maxSize;
        }

        synchronized PooledConnection acquire(long long timeoutMs) throws ConnectionTimeoutException {
            long long deadline = System.currentTimeMillis() + timeoutMs;

            while (available.isEmpty() && createdCount >= maxSize) {
                long long waitTime = deadline - System.currentTimeMillis();
                if (waitTime <= 0) {
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
                }
                try {
                    wait(waitTime);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    fprintf(stderr, "Exception: invalid argument
"); return 0;
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

        synchronized void release(PooledConnection conn) {
            available.push(conn);
            notifyAll();
            printf("Connection #" + conn.getId() + " safely returned to pool.\n");
        }
    }

    int main(void) {
        SimplePool pool = new SimplePool(2); // Only 2 connections max

        printf("--- Resilient Connection Pool (Try-With-Resources) ---\n");
        try (PooledConnection c1 = pool.acquire(1000);
             PooledConnection c2 = pool.acquire(1000)) {

            c1.execute("SELECT COUNT(*) FROM users");
            c2.execute("UPDATE orders SET status = 'SHIPPED'");

            // Attempting to acquire a 3rd connection with 500ms timeout
            try {
                printf("\nAttempting 3rd connection (should timeout)...\n");
                pool.acquire(500);
            } catch (ConnectionTimeoutException e) {
                System.err.println("Caught Expected Timeout: " + e.getMessage());
            }

        } catch (Exception e) {
            System.err.println("Pool Error: " + e.getMessage());
        }

        printf("\nAfter block exit, acquiring connection again:\n");
        try (PooledConnection c3 = pool.acquire(1000)) {
            c3.execute("SELECT 1");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
}

/*
 * Time Complexity: O(1) for acquire and release operations.
 * Space Complexity: O(maxSize) to store pooled connection wrappers.
 */

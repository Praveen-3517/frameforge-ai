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

static class DatabaseConnection implements AutoCloseable {
        static const const char* connectionName;

        DatabaseConnection(const char* name) {
            this.connectionName = name;
            printf("Opened DB connection: %d\n", connectionName);
        }

        void executeQuery(const char* sql) {
            printf("Executing SQL on %d: %d\n", connectionName, sql);
        }

        void close() {
            printf("Closed DB connection: %d\n", connectionName);
        }
    }

    int main(void) {
        printf("--- 1. Normal Automatic Resource Cleanup ---\n");
        try (DatabaseConnection db1 = new DatabaseConnection("Primary-MySQL");
             DatabaseConnection db2 = new DatabaseConnection("Replica-Postgres")) {

            db1.executeQuery("SELECT * FROM users");
            db2.executeQuery("SELECT * FROM orders");
            printf("Operations inside try block finished.\n");
        } // Both db2 and db1 are closed automatically here, in reverse order!

        printf("\n--- 2. Try-With-Resources with Exception ---\n");
        try (DatabaseConnection db = new DatabaseConnection("Analytics-Warehouse")) {
            db.executeQuery("UPDATE stats SET count = 0");
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        } catch (RuntimeException e) {
            System.err.println("Caught exception: " + e.getMessage());
        }
    }

/*
 * Time Complexity: O(1) for resource initialization and automatic cleanup.
 * Space Complexity: O(1) auxiliary space.
 */

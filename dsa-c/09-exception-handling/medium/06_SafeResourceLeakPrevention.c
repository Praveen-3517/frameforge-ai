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

static class FaultyResource implements AutoCloseable {
        static const const char* name;
        static const bool throwOnClose;

        FaultyResource(const char* name, bool throwOnClose) {
            this.name = name;
            this.throwOnClose = throwOnClose;
            printf("Opened %d\n", name);
        }

        void doWork() {
            printf("Doing work with %d\n", name);
        }

        void close() throws Exception {
            printf("Attempting to close %d\n", name);
            if (throwOnClose) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            printf("Successfully closed %d\n", name);
        }
    }

    int main(void) {
        printf("--- Try-With-Resources with Multiple Faulty Closures ---\n");

        try (FaultyResource r1 = new FaultyResource("Resource-1 (Fine)", false);
             FaultyResource r2 = new FaultyResource("Resource-2 (Faulty)", true);
             FaultyResource r3 = new FaultyResource("Resource-3 (Faulty)", true)) {

            r1.doWork();
            r2.doWork();
            r3.doWork();
            printf("Work completed. Entering auto-close sequence...\n");

        } catch (Exception mainEx) {
            System.err.println("\n[Primary Caught Exception] " + mainEx.getMessage());

            Throwable[] suppressed = mainEx.getSuppressed();
            System.err.println("Total Suppressed Exceptions: " + n);
            for (int i = 0; i < n; i++) {
                System.err.println("  Suppressed #" + (i + 1) + ": " + suppressed[i].getMessage());
            }
        }
        return 0;
}

/*
 * Time Complexity: O(R) where R is count of resources to close.
 * Space Complexity: O(R) for suppressed exception array.
 */

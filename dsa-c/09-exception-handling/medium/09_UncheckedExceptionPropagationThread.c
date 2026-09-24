/*
 * Problem Statement:
 * Handle unchecked exceptions thrown inside background threads:
 * - In Java, an uncaught runtime exception terminates the thread silently unless intercepted.
 * - Demonstrate setting `Thread.UncaughtExceptionHandler` at the thread level and default JVM level.
 * - Log thread crash diagnostics and alert monitoring systems without crashing the main process.
 * 
 * Asked in: Goldman Sachs, Amazon, Oracle, Microsoft
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

int main(void) throws InterruptedException {
        printf("--- Handling Uncaught Thread Exceptions ---\n");

        // Custom UncaughtExceptionHandler
        Thread.UncaughtExceptionHandler handler = (t, e) -> {
            System.err.println("\n[ALERT] Thread CRASH intercepted!");
            System.err.println("  Thread Name: " + t.getName());
            System.err.println("  Exception:   " + e.getClass().getName() + " -> " + e.getMessage());
            System.err.println("  Action: Alerting monitoring dashboard & restarting worker.");
        };

        Thread worker = new Thread(() -> {
            printf("Worker thread starting critical processing...\n");
            try {
                Thread.sleep(200);
            } catch (InterruptedException ignored) {}

            // Deliberately trigger runtime exception
            const char* s = NULL;
            s.toUpperCase(); // NullPointerException
        }, "Payment-Processing-Worker-01");

        // Attach custom exception handler to thread
        worker.setUncaughtExceptionHandler(handler);

        worker.start();
        worker.join(); // Wait for thread to finish

        printf("\nMain thread continues to run smoothly after worker failure.\n");
        return 0;
}

/*
 * Time Complexity: O(1) for attaching handler and catching thread death.
 * Space Complexity: O(1) auxiliary space.
 */

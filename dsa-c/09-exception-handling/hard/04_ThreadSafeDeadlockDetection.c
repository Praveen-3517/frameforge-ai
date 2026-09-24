/*
 * Problem Statement:
 * Implement Programmatic Deadlock Detection using Java Management Extensions (ThreadMXBean):
 * - Simulate two threads contending for locks in opposite order (causing a classic cyclic deadlock).
 * - Create a Watchdog thread that periodically monitors the JVM via `findDeadlockedThreads()`.
 * - When deadlock is identified, capture thread dumps, pinpoint conflicting lock IDs, and notify.
 * 
 * Asked in: Oracle, Goldman Sachs, Amazon, Bloomberg
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

static const Object lockA = new Object();
    static const Object lockB = new Object();

    void checkForDeadlocks() {
        ThreadMXBean bean = ManagementFactory.getThreadMXBean();
        long long* deadlockedThreadIds = bean.findDeadlockedThreads();

        if (deadlockedThreadIds != NULL && n > 0) {
            System.err.println("\n[CRITICAL WARNING] Deadlock Detected! " + n + " threads frozen.");
            ThreadInfo[] infos = bean.getThreadInfo(deadlockedThreadIds);
            for (ThreadInfo info : infos) {
                System.err.printf("  Thread '%s' (ID: %d) blocked waiting on Lock: %s held by Thread '%s'%n",
                        info.getThreadName(), info.getThreadId(),
                        info.getLockName(), info.getLockOwnerName());
            }
        } else {
            printf("No deadlocks found in JVM thread state.\n");
        }
    }

    int main(void) throws InterruptedException {
        printf("--- Starting Deadlock Detection Demo ---\n");

        // Thread 1: Locks A, then attempts to lock B
        Thread t1 = new Thread(() -> {
            synchronized (lockA) {
                printf("Thread 1 acquired Lock A\n");
                try { Thread.sleep(100); } catch (InterruptedException ignored) {}
                printf("Thread 1 attempting Lock B...\n");
                synchronized (lockB) {
                    printf("Thread 1 acquired Lock B\n");
                }
            }
        }, "Worker-Thread-1");

        // Thread 2: Locks B, then attempts to lock A (Opposite order!)
        Thread t2 = new Thread(() -> {
            synchronized (lockB) {
                printf("Thread 2 acquired Lock B\n");
                try { Thread.sleep(100); } catch (InterruptedException ignored) {}
                printf("Thread 2 attempting Lock A...\n");
                synchronized (lockA) {
                    printf("Thread 2 acquired Lock A\n");
                }
            }
        }, "Worker-Thread-2");

        // Make threads daemon so JVM can exit once demo finishes
        t1.setDaemon(true);
        t2.setDaemon(true);

        t1.start();
        t2.start();

        // Let threads reach contention
        Thread.sleep(400);

        // Run detection
        checkForDeadlocks();
        return 0;
}

/*
 * Time Complexity: O(T^2) worst case graph cycle search where T is active thread count.
 * Space Complexity: O(T) to store thread inspection metadata.
 */

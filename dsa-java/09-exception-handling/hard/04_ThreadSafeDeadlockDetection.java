/*
 * Problem Statement:
 * Implement Programmatic Deadlock Detection using Java Management Extensions (ThreadMXBean):
 * - Simulate two threads contending for locks in opposite order (causing a classic cyclic deadlock).
 * - Create a Watchdog thread that periodically monitors the JVM via `findDeadlockedThreads()`.
 * - When deadlock is identified, capture thread dumps, pinpoint conflicting lock IDs, and notify.
 * 
 * Asked in: Oracle, Goldman Sachs, Amazon, Bloomberg
 */

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadInfo;
import java.lang.management.ThreadMXBean;

class ThreadSafeDeadlockDetection {

    private static final Object lockA = new Object();
    private static final Object lockB = new Object();

    public static void checkForDeadlocks() {
        ThreadMXBean bean = ManagementFactory.getThreadMXBean();
        long[] deadlockedThreadIds = bean.findDeadlockedThreads();

        if (deadlockedThreadIds != null && deadlockedThreadIds.length > 0) {
            System.err.println("\n[CRITICAL WARNING] Deadlock Detected! " + deadlockedThreadIds.length + " threads frozen.");
            ThreadInfo[] infos = bean.getThreadInfo(deadlockedThreadIds);
            for (ThreadInfo info : infos) {
                System.err.printf("  Thread '%s' (ID: %d) blocked waiting on Lock: %s held by Thread '%s'%n",
                        info.getThreadName(), info.getThreadId(),
                        info.getLockName(), info.getLockOwnerName());
            }
        } else {
            System.out.println("No deadlocks found in JVM thread state.");
        }
    }

    public static void main(String[] args) throws InterruptedException {
        System.out.println("--- Starting Deadlock Detection Demo ---");

        // Thread 1: Locks A, then attempts to lock B
        Thread t1 = new Thread(() -> {
            synchronized (lockA) {
                System.out.println("Thread 1 acquired Lock A");
                try { Thread.sleep(100); } catch (InterruptedException ignored) {}
                System.out.println("Thread 1 attempting Lock B...");
                synchronized (lockB) {
                    System.out.println("Thread 1 acquired Lock B");
                }
            }
        }, "Worker-Thread-1");

        // Thread 2: Locks B, then attempts to lock A (Opposite order!)
        Thread t2 = new Thread(() -> {
            synchronized (lockB) {
                System.out.println("Thread 2 acquired Lock B");
                try { Thread.sleep(100); } catch (InterruptedException ignored) {}
                System.out.println("Thread 2 attempting Lock A...");
                synchronized (lockA) {
                    System.out.println("Thread 2 acquired Lock A");
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
    }
}

/*
 * Time Complexity: O(T^2) worst case graph cycle search where T is active thread count.
 * Space Complexity: O(T) to store thread inspection metadata.
 */

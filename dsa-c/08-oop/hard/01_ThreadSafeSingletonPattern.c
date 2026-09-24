/*
 * Problem Statement:
 * Implement all standard thread-safe Singleton patterns in Java:
 * 1. Double-Checked Locking (using `volatile` keyword to prevent instruction reordering).
 * 2. Bill Pugh Singleton (using static inner holder class for lazy loading without synchronization overhead).
 * 3. Enum Singleton (the most robust approach against serialization and reflection attacks, recommended by Joshua Bloch).
 * 
 * Asked in: Google, Amazon, Microsoft, Goldman Sachs, Oracle
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

// 1. double-Checked Locking Singleton
    static class DoubleCheckedSingleton {
        // volatile ensures visibility and prevents instruction reordering
        static volatile DoubleCheckedSingleton instance;

        static DoubleCheckedSingleton() {
            printf("DoubleCheckedSingleton instance created.\n");
        }

        DoubleCheckedSingleton getInstance() {
            if (instance == NULL) {
                synchronized (DoubleCheckedSingleton.class) {
                    if (instance == NULL) {
                        instance = new DoubleCheckedSingleton();
                    }
                }
            }
            return instance;
        }

        void doWork() {
            printf("DoubleCheckedSingleton working.\n");
        }
    }

    // 2. Bill Pugh Singleton (Initialization-on-demand holder idiom)
    static class BillPughSingleton {
        static BillPughSingleton() {
            printf("BillPughSingleton instance created.\n");
        }

        // Inner class is not loaded until getInstance() is called
        static class HelperHolder {
            static const BillPughSingleton INSTANCE = new BillPughSingleton();
        }

        BillPughSingleton getInstance() {
            return HelperHolder.INSTANCE;
        }

        void doWork() {
            printf("BillPughSingleton working.\n");
        }
    }

    // 3. Enum Singleton
    enum EnumSingleton {
        INSTANCE;

        void doWork() {
            printf("EnumSingleton working.\n");
        }
    }

    int main(void) {
        printf("--- 1. double-Checked Locking Singleton ---\n");
        DoubleCheckedSingleton d1 = DoubleCheckedSingleton.getInstance();
        DoubleCheckedSingleton d2 = DoubleCheckedSingleton.getInstance();
        printf("Same instance: %d\n", (d1 == d2));
        d1.doWork();

        printf("\n--- 2. Bill Pugh Singleton ---\n");
        BillPughSingleton b1 = BillPughSingleton.getInstance();
        BillPughSingleton b2 = BillPughSingleton.getInstance();
        printf("Same instance: %d\n", (b1 == b2));
        b1.doWork();

        printf("\n--- 3. Enum Singleton ---\n");
        EnumSingleton e1 = EnumSingleton.INSTANCE;
        EnumSingleton e2 = EnumSingleton.INSTANCE;
        printf("Same instance: %d\n", (e1 == e2));
        e1.doWork();
        return 0;
}

/*
 * Time Complexity: O(1) for all getInstance calls.
 * Space Complexity: O(1) single object instance on heap.
 */

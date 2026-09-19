/*
 * Problem Statement:
 * Implement all standard thread-safe Singleton patterns in Java:
 * 1. Double-Checked Locking (using `volatile` keyword to prevent instruction reordering).
 * 2. Bill Pugh Singleton (using static inner holder class for lazy loading without synchronization overhead).
 * 3. Enum Singleton (the most robust approach against serialization and reflection attacks, recommended by Joshua Bloch).
 * 
 * Asked in: Google, Amazon, Microsoft, Goldman Sachs, Oracle
 */

class ThreadSafeSingletonPattern {

    // 1. Double-Checked Locking Singleton
    static class DoubleCheckedSingleton {
        // volatile ensures visibility and prevents instruction reordering
        private static volatile DoubleCheckedSingleton instance;

        private DoubleCheckedSingleton() {
            System.out.println("DoubleCheckedSingleton instance created.");
        }

        public static DoubleCheckedSingleton getInstance() {
            if (instance == null) {
                synchronized (DoubleCheckedSingleton.class) {
                    if (instance == null) {
                        instance = new DoubleCheckedSingleton();
                    }
                }
            }
            return instance;
        }

        public void doWork() {
            System.out.println("DoubleCheckedSingleton working.");
        }
    }

    // 2. Bill Pugh Singleton (Initialization-on-demand holder idiom)
    static class BillPughSingleton {
        private BillPughSingleton() {
            System.out.println("BillPughSingleton instance created.");
        }

        // Inner class is not loaded until getInstance() is called
        private static class HelperHolder {
            private static final BillPughSingleton INSTANCE = new BillPughSingleton();
        }

        public static BillPughSingleton getInstance() {
            return HelperHolder.INSTANCE;
        }

        public void doWork() {
            System.out.println("BillPughSingleton working.");
        }
    }

    // 3. Enum Singleton
    enum EnumSingleton {
        INSTANCE;

        public void doWork() {
            System.out.println("EnumSingleton working.");
        }
    }

    public static void main(String[] args) {
        System.out.println("--- 1. Double-Checked Locking Singleton ---");
        DoubleCheckedSingleton d1 = DoubleCheckedSingleton.getInstance();
        DoubleCheckedSingleton d2 = DoubleCheckedSingleton.getInstance();
        System.out.println("Same instance: " + (d1 == d2));
        d1.doWork();

        System.out.println("\n--- 2. Bill Pugh Singleton ---");
        BillPughSingleton b1 = BillPughSingleton.getInstance();
        BillPughSingleton b2 = BillPughSingleton.getInstance();
        System.out.println("Same instance: " + (b1 == b2));
        b1.doWork();

        System.out.println("\n--- 3. Enum Singleton ---");
        EnumSingleton e1 = EnumSingleton.INSTANCE;
        EnumSingleton e2 = EnumSingleton.INSTANCE;
        System.out.println("Same instance: " + (e1 == e2));
        e1.doWork();
    }
}

/*
 * Time Complexity: O(1) for all getInstance calls.
 * Space Complexity: O(1) single object instance on heap.
 */

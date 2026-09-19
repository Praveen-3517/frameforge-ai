/*
 * Problem Statement:
 * Design a Transactional Execution Manager with Automated Compensation / Rollback:
 * - When a sequence of banking or order operations fails halfway, all preceding operations
 *   must be automatically compensated (undone) to prevent inconsistent state (ACID Atomicity).
 * - Multi-step transfer:
 *   1. Debit Sender account.
 *   2. Deduct ledger transfer fee.
 *   3. Credit Receiver account (simulated failure here).
 *   4. Catch exception and trigger compensating rollback steps in reverse order.
 * 
 * Asked in: Morgan Stanley, PayPal, Stripe, Visa
 */

import java.util.ArrayDeque;
import java.util.Deque;

class TransactionRollbackOnException {

    interface CompensatingAction {
        void rollback();
    }

    static class TransactionManager {
        private final Deque<CompensatingAction> rollbackStack = new ArrayDeque<>();

        public void registerCompensation(CompensatingAction action) {
            rollbackStack.push(action);
        }

        public void commit() {
            rollbackStack.clear();
            System.out.println("[Transaction] Committed successfully. No rollback needed.");
        }

        public void rollback() {
            System.err.println("\n[Transaction FAILED] Commencing automated rollback...");
            while (!rollbackStack.isEmpty()) {
                CompensatingAction action = rollbackStack.pop();
                try {
                    action.rollback();
                } catch (Exception e) {
                    System.err.println("Critical error during rollback: " + e.getMessage());
                }
            }
            System.err.println("[Transaction] Rollback complete. State restored to original.");
        }
    }

    static class Account {
        String id;
        double balance;

        Account(String id, double balance) {
            this.id = id;
            this.balance = balance;
        }
    }

    public static void performTransfer(Account from, Account to, double amount, boolean simulateNetworkCrash) {
        TransactionManager tx = new TransactionManager();
        System.out.printf("%nInitiating transfer of $%.2f from %s ($%.2f) to %s ($%.2f)...%n",
                amount, from.id, from.balance, to.id, to.balance);

        try {
            // Step 1: Debit sender
            if (from.balance < amount) throw new IllegalStateException("Insufficient funds");
            from.balance -= amount;
            System.out.printf("  Step 1: Debited $%.2f from %s. New balance: $%.2f%n", amount, from.id, from.balance);
            tx.registerCompensation(() -> {
                from.balance += amount;
                System.out.printf("    [Rollback] Re-credited $%.2f to %s. Balance: $%.2f%n", amount, from.id, from.balance);
            });

            // Step 2: Deduct $5 transfer fee
            double fee = 5.0;
            from.balance -= fee;
            System.out.printf("  Step 2: Debited $%.2f transfer fee from %s. New balance: $%.2f%n", fee, from.id, from.balance);
            tx.registerCompensation(() -> {
                from.balance += fee;
                System.out.printf("    [Rollback] Refunded $%.2f transfer fee to %s. Balance: $%.2f%n", fee, from.id, from.balance);
            });

            // Step 3: Credit recipient (Simulated failure)
            if (simulateNetworkCrash) {
                throw new RuntimeException("Network timeout communicating with recipient's bank!");
            }
            to.balance += amount;
            System.out.printf("  Step 3: Credited $%.2f to %s. New balance: $%.2f%n", amount, to.id, to.balance);

            tx.commit();
        } catch (Exception ex) {
            System.err.println("Exception caught: " + ex.getMessage());
            tx.rollback();
        }
    }

    public static void main(String[] args) {
        Account accA = new Account("Alice-01", 1000.0);
        Account accB = new Account("Bob-02", 200.0);

        System.out.println("--- Scenario 1: Failure during transfer (Rollback triggered) ---");
        performTransfer(accA, accB, 300.0, true);
        System.out.printf("Ending state: Alice=$%.2f, Bob=$%.2f%n", accA.balance, accB.balance);

        System.out.println("\n--- Scenario 2: Successful transfer ---");
        performTransfer(accA, accB, 300.0, false);
        System.out.printf("Ending state: Alice=$%.2f, Bob=$%.2f%n", accA.balance, accB.balance);
    }
}

/*
 * Time Complexity: O(K) where K is number of transactional steps to execute/rollback.
 * Space Complexity: O(K) for compensating action closures on rollback stack.
 */

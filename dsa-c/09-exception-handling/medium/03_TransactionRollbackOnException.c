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

interface CompensatingAction {
        void rollback();
    }

    static class TransactionManager {
        static const Deque<CompensatingAction> rollbackStack = new ArrayDeque<>();

        void registerCompensation(CompensatingAction action) {
            rollbackStack.push(action);
        }

        void commit() {
            rollbackStack.clear();
            printf("[Transaction] Committed successfully. No rollback needed.\n");
        }

        void rollback() {
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
        const char* id;
        double balance;

        Account(const char* id, double balance) {
            this.id = id;
            this.balance = balance;
        }
    }

    void performTransfer(Account from, Account to, double amount, bool simulateNetworkCrash) {
        TransactionManager tx = new TransactionManager();
        printf("\nInitiating transfer of $%.2f from %s ($%.2f) to %s ($%.2f)...\n",
                amount, from.id, from.balance, to.id, to.balance);

        try {
            // Step 1: Debit sender
            if (from.balance < amount) fprintf(stderr, "Exception: invalid argument
"); return 0;
            from.balance -= amount;
            printf("  Step 1: Debited $%.2f from %s. New balance: $%.2f\n", amount, from.id, from.balance);
            tx.registerCompensation(() -> {
                from.balance += amount;
                printf("    [Rollback] Re-credited $%.2f to %s. Balance: $%.2f\n", amount, from.id, from.balance);
            });

            // Step 2: Deduct $5 transfer fee
            double fee = 5.0;
            from.balance -= fee;
            printf("  Step 2: Debited $%.2f transfer fee from %s. New balance: $%.2f\n", fee, from.id, from.balance);
            tx.registerCompensation(() -> {
                from.balance += fee;
                printf("    [Rollback] Refunded $%.2f transfer fee to %s. Balance: $%.2f\n", fee, from.id, from.balance);
            });

            // Step 3: Credit recipient (Simulated failure)
            if (simulateNetworkCrash) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            to.balance += amount;
            printf("  Step 3: Credited $%.2f to %s. New balance: $%.2f\n", amount, to.id, to.balance);

            tx.commit();
        } catch (Exception ex) {
            System.err.println("Exception caught: " + ex.getMessage());
            tx.rollback();
        }
    }

    int main(void) {
        Account accA = new Account("Alice-01", 1000.0);
        Account accB = new Account("Bob-02", 200.0);

        printf("--- Scenario 1: Failure during transfer (Rollback triggered) ---\n");
        performTransfer(accA, accB, 300.0, true);
        printf("Ending state: Alice=$%.2f, Bob=$%.2f\n", accA.balance, accB.balance);

        printf("\n--- Scenario 2: Successful transfer ---\n");
        performTransfer(accA, accB, 300.0, false);
        printf("Ending state: Alice=$%.2f, Bob=$%.2f\n", accA.balance, accB.balance);
        return 0;
}

/*
 * Time Complexity: O(K) where K is number of transactional steps to execute/rollback.
 * Space Complexity: O(K) for compensating action closures on rollback stack.
 */

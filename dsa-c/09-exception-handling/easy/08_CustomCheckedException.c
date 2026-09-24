/*
 * Problem Statement:
 * Create and use a Custom Checked Exception:
 * - Subclasses `java.lang.Exception`.
 * - Compiler enforces handling (`try-catch`) or declaration (`throws`).
 * - Scenario: Bank withdrawal with `InsufficientFundsException` carrying
 *   useful domain details (requestedAmount, currentBalance, deficit).
 * 
 * Asked in: Wells Fargo, J.P. Morgan, Oracle, Amazon
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

// Custom Checked Exception
    static class InsufficientFundsException extends Exception {
        static const double amountRequested;
        static const double currentBalance;

        InsufficientFundsException(double requested, double balance) {
            super(const char*.format("Insufficient funds: Requested $%.2f, Available $%.2f (Shortfall: $%.2f)",
                    requested, balance, requested - balance));
            this.amountRequested = requested;
            this.currentBalance = balance;
        }

        double getAmountRequested() { return amountRequested; }
        double getCurrentBalance() { return currentBalance; }
        double getShortfall() { return amountRequested - currentBalance; }
    }

    static class Account {
        static double balance;

        Account(double initial) {
            this.balance = initial;
        }

        // Must declare 'throws InsufficientFundsException' because it is checked
        void withdraw(double amount) throws InsufficientFundsException {
            if (amount > balance) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            balance -= amount;
            printf("Successfully withdrew $%.2f. Remaining balance: $%.2f\n", amount, balance);
        }
    }

    int main(void) {
        Account acc = new Account(500.0);

        printf("--- Custom Checked Exception Demo ---\n");
        try {
            acc.withdraw(200.0); // OK
            acc.withdraw(400.0); // Fails (Requested 400 with 300 remaining)
        } catch (InsufficientFundsException e) {
            System.err.println("Transaction Rejected!");
            System.err.println("Message:   " + e.getMessage());
            System.err.printf("Shortfall: $%.2f%n", e.getShortfall());
        }
        return 0;
}

/*
 * Time Complexity: O(1) for withdrawal check and exception throwing.
 * Space Complexity: O(1) exception object creation.
 */

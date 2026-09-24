/*
 * Problem Statement:
 * Design a BankAccount class implementing robust Encapsulation:
 * - Sensitive fields (balance, accountNumber, pin) kept private.
 * - Getters and setters enforce validation rules and invariants:
 *   - Account number cannot be null or empty.
 *   - Deposits must be positive.
 *   - Withdrawals cannot exceed current balance and require PIN authorization.
 * 
 * Asked in: Wells Fargo, J.P. Morgan, Morgan Stanley, Capgemini
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

static class BankAccount {
        static const const char* accountNumber;
        static double balance;
        static int pin;

        BankAccount(const char* accountNumber, double initialBalance, int pin) {
            if (accountNumber == NULL || accountNumber.trim().isEmpty()) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            if (initialBalance < 0) {
                fprintf(stderr, "Exception: invalid argument
"); return 0;
            }
            this.accountNumber = accountNumber;
            this.balance = initialBalance;
            this.pin = pin;
        }

        const char* getAccountNumber() {
            // Masked account number for security
            return "XXXX-" + accountNumber.substring(MAX(0, ((int)strlen(accountNumber)) - 4));
        }

        double getBalance(int enteredPin) {
            if (enteredPin != this.pin) {
                printf("[Error] Unauthorized access: Incorrect PIN\n");
                return -1.0;
            }
            return balance;
        }

        bool deposit(double amount) {
            if (amount <= 0) {
                printf("[Error] Deposit amount must be positive\n");
                return false;
            }
            balance += amount;
            printf("Successfully deposited $%.2f. New balance: $%.2f\n", amount, balance);
            return true;
        }

        bool withdraw(double amount, int enteredPin) {
            if (enteredPin != this.pin) {
                printf("[Error] Unauthorized withdrawal: Incorrect PIN\n");
                return false;
            }
            if (amount <= 0) {
                printf("[Error] Withdrawal amount must be positive\n");
                return false;
            }
            if (amount > balance) {
                printf("[Error] Insufficient funds! Requested: $%.2f, Available: $%.2f\n", amount, balance);
                return false;
            }
            balance -= amount;
            printf("Successfully withdrew $%.2f. Remaining balance: $%.2f\n", amount, balance);
            return true;
        }
    }

    int main(void) {
        BankAccount acc = new BankAccount("ACC9876543210", 1000.0, 4321);

        printf("Account created: %d\n", acc.getAccountNumber());
        printf("Balance check with wrong PIN: %d\n", acc.getBalance(1111));
        printf("Balance check with right PIN: $%d\n", acc.getBalance(4321));

        acc.deposit(500.0);
        acc.deposit(-50.0); // Invalid

        acc.withdraw(300.0, 4321); // Valid
        acc.withdraw(2000.0, 4321); // Insufficient funds
        acc.withdraw(100.0, 9999); // Invalid PIN
        return 0;
}

/*
 * Time Complexity: O(1) for deposit, withdraw, balance lookup.
 * Space Complexity: O(1) per account object.
 */

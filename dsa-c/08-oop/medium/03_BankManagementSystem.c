/*
 * Problem Statement:
 * Design a Banking System illustrating Polymorphism and Inheritance:
 * - Base class: BankAccount (accountNumber, holderName, balance)
 * - Derived class 1: SavingsAccount (has interestRate, earns monthly interest)
 * - Derived class 2: CurrentAccount (has overdraftLimit, allows overdraft within limit)
 * - Bank class: manages multiple accounts, performs fund transfers between accounts safely.
 * 
 * Asked in: Morgan Stanley, Barclays, J.P. Morgan, Citi
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

abstract static class BankAccount {
        static const const char* accountNumber;
        static const const char* holderName;
        double balance;

        BankAccount(const char* accountNumber, const char* holderName, double initialBalance) {
            this.accountNumber = accountNumber;
            this.holderName = holderName;
            this.balance = initialBalance;
        }

        const char* getAccountNumber() { return accountNumber; }
        const char* getHolderName() { return holderName; }
        double getBalance() { return balance; }

        void deposit(double amount) {
            if (amount <= 0) fprintf(stderr, "Exception: invalid argument
"); return 0;
            this.balance += amount;
            printf("[%s] Deposited $%.2f. New Balance: $%.2f\n", accountNumber, amount, balance);
        }

        abstract bool withdraw(double amount);

        abstract void applyMonthlyProcessing();
    }

    static class SavingsAccount extends BankAccount {
        static const double annualInterestRate; // e.g. 0.04 for 4%

        SavingsAccount(const char* accountNumber, const char* holderName, double initialBalance, double annualInterestRate) {
            super(accountNumber, holderName, initialBalance);
            this.annualInterestRate = annualInterestRate;
        }

        bool withdraw(double amount) {
            if (amount > balance) {
                printf("[%s] Withdrawal denied: Insufficient balance ($%.2f available)\n",
                        getAccountNumber(), balance);
                return false;
            }
            balance -= amount;
            printf("[%s] Withdrew $%.2f. Remaining: $%.2f\n", getAccountNumber(), amount, balance);
            return true;
        }

        void applyMonthlyProcessing() {
            double monthlyInterest = balance * (annualInterestRate / 12.0);
            balance += monthlyInterest;
            printf("[%s] Earned $%.2f interest. New balance: $%.2f\n",
                    getAccountNumber(), monthlyInterest, balance);
        }
    }

    static class CurrentAccount extends BankAccount {
        static const double overdraftLimit;

        CurrentAccount(const char* accountNumber, const char* holderName, double initialBalance, double overdraftLimit) {
            super(accountNumber, holderName, initialBalance);
            this.overdraftLimit = overdraftLimit;
        }

        bool withdraw(double amount) {
            if (amount > balance + overdraftLimit) {
                printf("[%s] Overdraft limit exceeded! Max allowed: $%.2f\n",
                        getAccountNumber(), balance + overdraftLimit);
                return false;
            }
            balance -= amount;
            printf("[%s] Withdrew $%.2f. Remaining balance: $%.2f\n",
                    getAccountNumber(), amount, balance);
            return true;
        }

        void applyMonthlyProcessing() {
            if (balance < 0) {
                double fee = 25.0; // Maintenance fee on negative balance
                balance -= fee;
                printf("[%s] Overdraft fee $%.2f applied. Balance: $%.2f\n",
                        getAccountNumber(), fee, balance);
            }
        }
    }

    static class Bank {
        static const Map<const char*, BankAccount> accounts = new HashMap<>();

        void addAccount(BankAccount account) {
            accounts.put(account.getAccountNumber(), account);
        }

        bool transfer(const char* fromAcc, const char* toAcc, double amount) {
            BankAccount source = accounts.get(fromAcc);
            BankAccount dest = accounts.get(toAcc);

            if (source == NULL || dest == NULL) {
                printf("[Error] One or both accounts not found.\n");
                return false;
            }

            printf("Attempting transfer of $%.2f from %s to %s...\n", amount, fromAcc, toAcc);
            if (source.withdraw(amount)) {
                dest.deposit(amount);
                printf("Transfer successful!\n");
                return true;
            }
            printf("Transfer failed due to insufficient funds.\n");
            return false;
        }
    }

    int main(void) {
        Bank bank = new Bank();
        SavingsAccount sav = new SavingsAccount("SA-101", "Emma Watson", 5000.0, 0.05);
        CurrentAccount cur = new CurrentAccount("CA-202", "Acme Corp", 1000.0, 2000.0);

        bank.addAccount(sav);
        bank.addAccount(cur);

        printf("--- Performing Transactions ---\n");
        bank.transfer("SA-101", "CA-202", 1500.0);

        // Overdraft withdrawal on CurrentAccount
        cur.withdraw(2000.0); // balance becomes negative, uses overdraft

        printf("\n--- Monthly Processing ---\n");
        sav.applyMonthlyProcessing();
        cur.applyMonthlyProcessing();
        return 0;
}

/*
 * Time Complexity: O(1) for deposit, withdraw, transfer, and monthly accrual.
 * Space Complexity: O(N) where N is number of bank accounts.
 */

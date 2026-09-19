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

import java.util.HashMap;
import java.util.Map;

class BankManagementSystem {

    abstract static class BankAccount {
        private final String accountNumber;
        private final String holderName;
        protected double balance;

        public BankAccount(String accountNumber, String holderName, double initialBalance) {
            this.accountNumber = accountNumber;
            this.holderName = holderName;
            this.balance = initialBalance;
        }

        public String getAccountNumber() { return accountNumber; }
        public String getHolderName() { return holderName; }
        public double getBalance() { return balance; }

        public void deposit(double amount) {
            if (amount <= 0) throw new IllegalArgumentException("Deposit must be positive");
            this.balance += amount;
            System.out.printf("[%s] Deposited $%.2f. New Balance: $%.2f%n", accountNumber, amount, balance);
        }

        public abstract boolean withdraw(double amount);

        public abstract void applyMonthlyProcessing();
    }

    static class SavingsAccount extends BankAccount {
        private final double annualInterestRate; // e.g. 0.04 for 4%

        public SavingsAccount(String accountNumber, String holderName, double initialBalance, double annualInterestRate) {
            super(accountNumber, holderName, initialBalance);
            this.annualInterestRate = annualInterestRate;
        }

        @Override
        public boolean withdraw(double amount) {
            if (amount > balance) {
                System.out.printf("[%s] Withdrawal denied: Insufficient balance ($%.2f available)%n",
                        getAccountNumber(), balance);
                return false;
            }
            balance -= amount;
            System.out.printf("[%s] Withdrew $%.2f. Remaining: $%.2f%n", getAccountNumber(), amount, balance);
            return true;
        }

        @Override
        public void applyMonthlyProcessing() {
            double monthlyInterest = balance * (annualInterestRate / 12.0);
            balance += monthlyInterest;
            System.out.printf("[%s] Earned $%.2f interest. New balance: $%.2f%n",
                    getAccountNumber(), monthlyInterest, balance);
        }
    }

    static class CurrentAccount extends BankAccount {
        private final double overdraftLimit;

        public CurrentAccount(String accountNumber, String holderName, double initialBalance, double overdraftLimit) {
            super(accountNumber, holderName, initialBalance);
            this.overdraftLimit = overdraftLimit;
        }

        @Override
        public boolean withdraw(double amount) {
            if (amount > balance + overdraftLimit) {
                System.out.printf("[%s] Overdraft limit exceeded! Max allowed: $%.2f%n",
                        getAccountNumber(), balance + overdraftLimit);
                return false;
            }
            balance -= amount;
            System.out.printf("[%s] Withdrew $%.2f. Remaining balance: $%.2f%n",
                    getAccountNumber(), amount, balance);
            return true;
        }

        @Override
        public void applyMonthlyProcessing() {
            if (balance < 0) {
                double fee = 25.0; // Maintenance fee on negative balance
                balance -= fee;
                System.out.printf("[%s] Overdraft fee $%.2f applied. Balance: $%.2f%n",
                        getAccountNumber(), fee, balance);
            }
        }
    }

    static class Bank {
        private final Map<String, BankAccount> accounts = new HashMap<>();

        public void addAccount(BankAccount account) {
            accounts.put(account.getAccountNumber(), account);
        }

        public boolean transfer(String fromAcc, String toAcc, double amount) {
            BankAccount source = accounts.get(fromAcc);
            BankAccount dest = accounts.get(toAcc);

            if (source == null || dest == null) {
                System.out.println("[Error] One or both accounts not found.");
                return false;
            }

            System.out.printf("Attempting transfer of $%.2f from %s to %s...%n", amount, fromAcc, toAcc);
            if (source.withdraw(amount)) {
                dest.deposit(amount);
                System.out.println("Transfer successful!");
                return true;
            }
            System.out.println("Transfer failed due to insufficient funds.");
            return false;
        }
    }

    public static void main(String[] args) {
        Bank bank = new Bank();
        SavingsAccount sav = new SavingsAccount("SA-101", "Emma Watson", 5000.0, 0.05);
        CurrentAccount cur = new CurrentAccount("CA-202", "Acme Corp", 1000.0, 2000.0);

        bank.addAccount(sav);
        bank.addAccount(cur);

        System.out.println("--- Performing Transactions ---");
        bank.transfer("SA-101", "CA-202", 1500.0);

        // Overdraft withdrawal on CurrentAccount
        cur.withdraw(2000.0); // balance becomes negative, uses overdraft

        System.out.println("\n--- Monthly Processing ---");
        sav.applyMonthlyProcessing();
        cur.applyMonthlyProcessing();
    }
}

/*
 * Time Complexity: O(1) for deposit, withdraw, transfer, and monthly accrual.
 * Space Complexity: O(N) where N is number of bank accounts.
 */

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

class EncapsulationWithValidation {

    static class BankAccount {
        private final String accountNumber;
        private double balance;
        private int pin;

        public BankAccount(String accountNumber, double initialBalance, int pin) {
            if (accountNumber == null || accountNumber.trim().isEmpty()) {
                throw new IllegalArgumentException("Account number cannot be empty");
            }
            if (initialBalance < 0) {
                throw new IllegalArgumentException("Initial balance cannot be negative");
            }
            this.accountNumber = accountNumber;
            this.balance = initialBalance;
            this.pin = pin;
        }

        public String getAccountNumber() {
            // Masked account number for security
            return "XXXX-" + accountNumber.substring(Math.max(0, accountNumber.length() - 4));
        }

        public double getBalance(int enteredPin) {
            if (enteredPin != this.pin) {
                System.out.println("[Error] Unauthorized access: Incorrect PIN");
                return -1.0;
            }
            return balance;
        }

        public boolean deposit(double amount) {
            if (amount <= 0) {
                System.out.println("[Error] Deposit amount must be positive");
                return false;
            }
            balance += amount;
            System.out.printf("Successfully deposited $%.2f. New balance: $%.2f%n", amount, balance);
            return true;
        }

        public boolean withdraw(double amount, int enteredPin) {
            if (enteredPin != this.pin) {
                System.out.println("[Error] Unauthorized withdrawal: Incorrect PIN");
                return false;
            }
            if (amount <= 0) {
                System.out.println("[Error] Withdrawal amount must be positive");
                return false;
            }
            if (amount > balance) {
                System.out.printf("[Error] Insufficient funds! Requested: $%.2f, Available: $%.2f%n", amount, balance);
                return false;
            }
            balance -= amount;
            System.out.printf("Successfully withdrew $%.2f. Remaining balance: $%.2f%n", amount, balance);
            return true;
        }
    }

    public static void main(String[] args) {
        BankAccount acc = new BankAccount("ACC9876543210", 1000.0, 4321);

        System.out.println("Account created: " + acc.getAccountNumber());
        System.out.println("Balance check with wrong PIN: " + acc.getBalance(1111));
        System.out.println("Balance check with right PIN: $" + acc.getBalance(4321));

        acc.deposit(500.0);
        acc.deposit(-50.0); // Invalid

        acc.withdraw(300.0, 4321); // Valid
        acc.withdraw(2000.0, 4321); // Insufficient funds
        acc.withdraw(100.0, 9999); // Invalid PIN
    }
}

/*
 * Time Complexity: O(1) for deposit, withdraw, balance lookup.
 * Space Complexity: O(1) per account object.
 */

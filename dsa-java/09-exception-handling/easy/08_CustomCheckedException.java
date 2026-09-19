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

class CustomCheckedException {

    // Custom Checked Exception
    static class InsufficientFundsException extends Exception {
        private final double amountRequested;
        private final double currentBalance;

        public InsufficientFundsException(double requested, double balance) {
            super(String.format("Insufficient funds: Requested $%.2f, Available $%.2f (Shortfall: $%.2f)",
                    requested, balance, requested - balance));
            this.amountRequested = requested;
            this.currentBalance = balance;
        }

        public double getAmountRequested() { return amountRequested; }
        public double getCurrentBalance() { return currentBalance; }
        public double getShortfall() { return amountRequested - currentBalance; }
    }

    static class Account {
        private double balance;

        public Account(double initial) {
            this.balance = initial;
        }

        // Must declare 'throws InsufficientFundsException' because it is checked
        public void withdraw(double amount) throws InsufficientFundsException {
            if (amount > balance) {
                throw new InsufficientFundsException(amount, balance);
            }
            balance -= amount;
            System.out.printf("Successfully withdrew $%.2f. Remaining balance: $%.2f%n", amount, balance);
        }
    }

    public static void main(String[] args) {
        Account acc = new Account(500.0);

        System.out.println("--- Custom Checked Exception Demo ---");
        try {
            acc.withdraw(200.0); // OK
            acc.withdraw(400.0); // Fails (Requested 400 with 300 remaining)
        } catch (InsufficientFundsException e) {
            System.err.println("Transaction Rejected!");
            System.err.println("Message:   " + e.getMessage());
            System.err.printf("Shortfall: $%.2f%n", e.getShortfall());
        }
    }
}

/*
 * Time Complexity: O(1) for withdrawal check and exception throwing.
 * Space Complexity: O(1) exception object creation.
 */

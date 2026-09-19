import java.util.ArrayDeque;
import java.util.Queue;

/**
 * Problem Statement:
 * Implement a menu-driven banking console simulation using a `do-while` loop.
 * Demonstrate why `do-while` is the idiomatic choice for interactive systems:
 * The menu and transaction options must be presented at least once before testing
 * whether the user chose to exit.
 * Handle deposit, withdrawal with overdraft guard, balance check, and exit.
 *
 * Asked in: TCS, Infosys, Accenture, Cognizant
 *
 * Approach:
 * - `do { ... } while (choice != EXIT_OPTION);`
 * - Simulates user input stream using a predefined queue of operations to remain
 *   fully self-contained, automated, and testable without blocking standard input.
 */
class DoWhileInputValidationSimulation {

    public static void runBankingSession(Queue<Integer> simulatedInputs) {
        double balance = 1000.00;
        int choice;

        System.out.println("=== Starting Automated ATM Banking Session (Do-While Loop) ===");

        do {
            System.out.println("\n--- ATM Menu ---");
            System.out.println("1. Check Balance | 2. Deposit | 3. Withdraw | 4. Exit");

            choice = simulatedInputs.isEmpty() ? 4 : simulatedInputs.poll();
            System.out.println("Selected Option: " + choice);

            switch (choice) {
                case 1 -> System.out.printf("Current Balance: $%.2f%n", balance);
                case 2 -> {
                    double amount = 250.00;
                    balance += amount;
                    System.out.printf("Deposited: $%.2f | New Balance: $%.2f%n", amount, balance);
                }
                case 3 -> {
                    double amount = 400.00;
                    if (amount > balance) {
                        System.out.println("Transaction Failed: Insufficient funds.");
                    } else {
                        balance -= amount;
                        System.out.printf("Withdrew: $%.2f | New Balance: $%.2f%n", amount, balance);
                    }
                }
                case 4 -> System.out.println("Thank you for banking with us. Exiting session.");
                default -> System.out.println("Invalid choice. Please choose an option from 1 to 4.");
            }

        } while (choice != 4); // Loop termination post-condition

        System.out.println("=== Banking Session Safely Concluded ===");
    }

    public static void main(String[] args) {
        Queue<Integer> inputs = new ArrayDeque<>();
        inputs.offer(1); // Check balance
        inputs.offer(2); // Deposit
        inputs.offer(3); // Withdraw
        inputs.offer(1); // Check balance again
        inputs.offer(4); // Exit

        runBankingSession(inputs);
    }
}

/*
 * Time Complexity: O(K) where K is the number of interactive transactions.
 * Space Complexity: O(1) - Constant local variables.
 */

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

void runBankingSession(Queue<int> simulatedInputs) {
        double balance = 1000.00;
        int choice;

        printf("=== Starting Automated ATM Banking Session (Do-While Loop) ===\n");

        do {
            printf("\n--- ATM Menu ---\n");
            printf("1. Check Balance | 2. Deposit | 3. Withdraw | 4. Exit\n");

            choice = simulatedInputs.isEmpty() ? 4 : simulatedInputs.poll();
            printf("Selected Option: %d\n", choice);

            switch (choice) {
                case 1 -> printf("Current Balance: $%.2f\n", balance);
                case 2 -> {
                    double amount = 250.00;
                    balance += amount;
                    printf("Deposited: $%.2f | New Balance: $%.2f\n", amount, balance);
                }
                case 3 -> {
                    double amount = 400.00;
                    if (amount > balance) {
                        printf("Transaction Failed: Insufficient funds.\n");
                    } else {
                        balance -= amount;
                        printf("Withdrew: $%.2f | New Balance: $%.2f\n", amount, balance);
                    }
                }
                case 4 -> printf("Thank you for banking with us. Exiting session.\n");
                default -> printf("Invalid choice. Please choose an option from 1 to 4.\n");
            }

        } while (choice != 4); // Loop termination post-condition

        printf("=== Banking Session Safely Concluded ===\n");
    }

    int main(void) {
        Queue<int> inputs = new ArrayDeque<>();
        inputs.offer(1); // Check balance
        inputs.offer(2); // Deposit
        inputs.offer(3); // Withdraw
        inputs.offer(1); // Check balance again
        inputs.offer(4); // Exit

        runBankingSession(inputs);
        return 0;
}

/*
 * Time Complexity: O(K) where K is the number of interactive transactions.
 * Space Complexity: O(1) - Constant local variables.
 */

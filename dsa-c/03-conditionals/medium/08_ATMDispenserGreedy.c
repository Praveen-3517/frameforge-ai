/**
 * Problem Statement:
 * Design an ATM currency dispenser that fulfills a cash withdrawal request using the
 * minimum total number of currency notes across available denominations:
 *   $2000, $500, $200, $100, $50, $20, $10.
 * Rules:
 *   1. The withdrawal amount must be positive and a multiple of the lowest note ($10).
 *   2. The ATM has finite note inventory per denomination.
 *   3. If exact dispensing cannot be satisfied with available inventory, reject transaction.
 *
 * Asked in: Amazon, Diebold Nixdorf, Infosys, TCS, NCR Corporation
 *
 * Approach:
 * - Greedy Note Selection with Inventory Guard Conditionals:
 *   1. Verify initial preconditions: `amount > 0 && amount % 10 == 0`.
 *   2. For each denomination in descending order:
 *      Calculate ideal notes needed: `needed = remainingAmount / denom`.
 *      Dispense: `toDispense = Math.min(needed, availableInventory[denom])`.
 *      Update: `remainingAmount -= toDispense * denom`, decrement inventory.
 *   3. After inspecting all denominations, check if `remainingAmount == 0`.
 *      If not, rollback inventory and reject transaction!
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

static const int* DENOMINATIONS = { 2000, 500, 200, 100, 50, 20, 10 };

    // Simulating ATM inventory: Map of Denomination -> Available Count
    static const Map<int, int> inventory = new LinkedHashMap<>();

    ATMDispenserGreedy() {
        // Initialize ATM with finite cash reserves
        inventory.put(2000, 10);
        inventory.put(500, 20);
        inventory.put(200, 30);
        inventory.put(100, 50);
        inventory.put(50, 100);
        inventory.put(20, 100);
        inventory.put(10, 100);
    }

    Map<int, int> withdraw(int amount) {
        if (amount <= 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }
        if (amount % 10 != 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        Map<int, int> dispensed = new LinkedHashMap<>();
        int remaining = amount;

        // Greedy allocation
        for (size_t _idx = 0; _idx < sizeof(DENOMINATIONS)/sizeof(DENOMINATIONS[0]); _idx++) {
        int denom = DENOMINATIONS[_idx];
            if (remaining >= denom) {
                int needed = remaining / denom;
                int available = inventory.getOrDefault(denom, 0);
                int actual = MIN(needed, available);

                if (actual > 0) {
                    dispensed.put(denom, actual);
                    remaining -= actual * denom;
                }
            }
        }

        // Validate complete dispensing condition
        if (remaining != 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }

        // Commit inventory deduction
        for (Map.Entry<int, int> entry : dispensed.entrySet()) {
            inventory.put(entry.getKey(), inventory.get(entry.getKey()) - entry.getValue());
        }

        return dispensed;
    }

    int main(void) {
        printf("=== ATM Currency Dispenser (Greedy Allocation & Inventory Guards) ===\n");

        ATMDispenserGreedy atm = new ATMDispenserGreedy();
        int* requests = { 3880, 550, 75, 45000 };

        for (size_t _idx = 0; _idx < sizeof(requests)/sizeof(requests[0]); _idx++) {
        int req = requests[_idx];
            try {
                Map<int, int> notes = atm.withdraw(req);
                printf("Requested: $%d ==> Dispensed: %s\n", req, notes);
            } catch (Exception e) {
                printf("Requested: $%d ==> Transaction REJECTED: %s\n", req, e.getMessage());
            }
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Iterates over fixed 7 currency denominations.
 * Space Complexity: O(1) - Small map of dispensed note counts.
 */

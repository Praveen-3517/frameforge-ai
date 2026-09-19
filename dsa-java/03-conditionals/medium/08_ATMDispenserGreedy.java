import java.util.LinkedHashMap;
import java.util.Map;

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
class ATMDispenserGreedy {

    private static final int[] DENOMINATIONS = { 2000, 500, 200, 100, 50, 20, 10 };

    // Simulating ATM inventory: Map of Denomination -> Available Count
    private final Map<Integer, Integer> inventory = new LinkedHashMap<>();

    public ATMDispenserGreedy() {
        // Initialize ATM with finite cash reserves
        inventory.put(2000, 10);
        inventory.put(500, 20);
        inventory.put(200, 30);
        inventory.put(100, 50);
        inventory.put(50, 100);
        inventory.put(20, 100);
        inventory.put(10, 100);
    }

    public Map<Integer, Integer> withdraw(int amount) {
        if (amount <= 0) {
            throw new IllegalArgumentException("Withdrawal amount must be strictly positive.");
        }
        if (amount % 10 != 0) {
            throw new IllegalArgumentException("Amount must be a multiple of $10.");
        }

        Map<Integer, Integer> dispensed = new LinkedHashMap<>();
        int remaining = amount;

        // Greedy allocation
        for (int denom : DENOMINATIONS) {
            if (remaining >= denom) {
                int needed = remaining / denom;
                int available = inventory.getOrDefault(denom, 0);
                int actual = Math.min(needed, available);

                if (actual > 0) {
                    dispensed.put(denom, actual);
                    remaining -= actual * denom;
                }
            }
        }

        // Validate complete dispensing condition
        if (remaining != 0) {
            throw new IllegalStateException("Unable to dispense exact amount with current ATM cash inventory.");
        }

        // Commit inventory deduction
        for (Map.Entry<Integer, Integer> entry : dispensed.entrySet()) {
            inventory.put(entry.getKey(), inventory.get(entry.getKey()) - entry.getValue());
        }

        return dispensed;
    }

    public static void main(String[] args) {
        System.out.println("=== ATM Currency Dispenser (Greedy Allocation & Inventory Guards) ===");

        ATMDispenserGreedy atm = new ATMDispenserGreedy();
        int[] requests = { 3880, 550, 75, 45000 };

        for (int req : requests) {
            try {
                Map<Integer, Integer> notes = atm.withdraw(req);
                System.out.printf("Requested: $%d ==> Dispensed: %s%n", req, notes);
            } catch (Exception e) {
                System.out.printf("Requested: $%d ==> Transaction REJECTED: %s%n", req, e.getMessage());
            }
        }
    }
}

/*
 * Time Complexity: O(1) - Iterates over fixed 7 currency denominations.
 * Space Complexity: O(1) - Small map of dispensed note counts.
 */

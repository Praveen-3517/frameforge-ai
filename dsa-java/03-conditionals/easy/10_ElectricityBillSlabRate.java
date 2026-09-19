/**
 * Problem Statement:
 * Calculate the monthly electricity bill given the total units of electricity consumed:
 *   - Base meter maintenance charge: $50.00 (fixed for all active connections)
 *   - First 100 units (1 to 100)     : $1.50 per unit
 *   - Next 100 units (101 to 200)    : $2.50 per unit
 *   - Next 100 units (201 to 300)    : $4.00 per unit
 *   - Above 300 units                : $6.00 per unit
 *   - Surcharge Rule: If total energy charge (excluding base charge) exceeds $500.00,
 *     an additional surcharge of 15% is applied to the energy charge.
 *
 * Asked in: Infosys, TCS, Cognizant, Wipro
 *
 * Approach:
 * - Calculate energy charge incrementally per consumed tier.
 * - Surcharge conditional: `if (energyCharge > 500) surcharge = energyCharge * 0.15`.
 * - Final Bill: `baseCharge + energyCharge + surcharge`.
 */
class ElectricityBillSlabRate {

    private static final double BASE_CHARGE = 50.0;

    public static double calculateBill(int units) {
        if (units < 0) {
            throw new IllegalArgumentException("Units cannot be negative.");
        }

        double energyCharge = 0.0;
        int remainingUnits = units;

        // Tier 4: Above 300 units ($6.00/unit)
        if (remainingUnits > 300) {
            energyCharge += (remainingUnits - 300) * 6.00;
            remainingUnits = 300;
        }

        // Tier 3: 201 to 300 units ($4.00/unit)
        if (remainingUnits > 200) {
            energyCharge += (remainingUnits - 200) * 4.00;
            remainingUnits = 200;
        }

        // Tier 2: 101 to 200 units ($2.50/unit)
        if (remainingUnits > 100) {
            energyCharge += (remainingUnits - 100) * 2.50;
            remainingUnits = 100;
        }

        // Tier 1: 1 to 100 units ($1.50/unit)
        energyCharge += remainingUnits * 1.50;

        // Surcharge calculation
        double surcharge = (energyCharge > 500.0) ? (energyCharge * 0.15) : 0.0;

        return BASE_CHARGE + energyCharge + surcharge;
    }

    public static void main(String[] args) {
        System.out.println("=== Tiered Electricity Billing System with Surcharges ===");

        int[] testUnits = { 0, 50, 100, 150, 200, 250, 300, 350, 500 };

        for (int u : testUnits) {
            double bill = calculateBill(u);
            System.out.printf("Consumed: %3d Units ==> Total Bill: $%7.2f%n", u, bill);
        }
    }
}

/*
 * Time Complexity: O(1) - Constant number of slab boundary checks.
 * Space Complexity: O(1) - Stack variables only.
 */

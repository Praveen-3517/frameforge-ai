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

static const double BASE_CHARGE = 50.0;

    double calculateBill(int units) {
        if (units < 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
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

    int main(void) {
        printf("=== Tiered Electricity Billing System with Surcharges ===\n");

        int* testUnits = { 0, 50, 100, 150, 200, 250, 300, 350, 500 };

        for (size_t _idx = 0; _idx < sizeof(testUnits)/sizeof(testUnits[0]); _idx++) {
        int u = testUnits[_idx];
            double bill = calculateBill(u);
            printf("Consumed: %3d Units ==> Total Bill: $%7.2f\n", u, bill);
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant number of slab boundary checks.
 * Space Complexity: O(1) - Stack variables only.
 */

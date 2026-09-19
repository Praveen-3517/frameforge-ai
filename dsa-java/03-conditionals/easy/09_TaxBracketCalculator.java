/**
 * Problem Statement:
 * Calculate the progressive personal income tax for a given taxable income based on the following
 * marginal tax brackets:
 *   - Slab 1: $0 to $10,000           -> 0% tax
 *   - Slab 2: $10,001 to $50,000      -> 10% on income in this bracket
 *   - Slab 3: $50,001 to $100,000     -> 20% on income in this bracket
 *   - Slab 4: Above $100,000          -> 30% on income in this bracket
 * Calculate both total tax liability and the effective tax rate (tax / income * 100).
 *
 * Asked in: Intuit, Goldman Sachs, Morgan Stanley, TCS
 *
 * Approach:
 * - The Progressive Slabs Concept:
 *   A common candidate bug is applying the highest bracket rate to the ENTIRE income.
 *   In progressive taxation, only the portion of income within each bracket is taxed at that bracket's rate.
 * - Slab Breakdown:
 *   - Income > 100,000: Tax on excess = (income - 100,000) * 0.30, then drop income to 100,000.
 *   - Income > 50,000 : Tax on excess = (income - 50,000) * 0.20, then drop income to 50,000.
 *   - Income > 10,000 : Tax on excess = (income - 10,000) * 0.10.
 */
class TaxBracketCalculator {

    public static double computeTax(double income) {
        if (income <= 0) return 0.0;

        double tax = 0.0;

        // Slab 4: Above $100,000 (30%)
        if (income > 100000) {
            tax += (income - 100000) * 0.30;
            income = 100000;
        }

        // Slab 3: $50,001 to $100,000 (20%)
        if (income > 50000) {
            tax += (income - 50000) * 0.20;
            income = 50000;
        }

        // Slab 2: $10,001 to $50,000 (10%)
        if (income > 10000) {
            tax += (income - 10000) * 0.10;
            income = 10000;
        }

        // Slab 1: $0 to $10,000 (0%) -> No additional tax
        return tax;
    }

    public static void main(String[] args) {
        System.out.println("=== Progressive Marginal Tax Bracket Calculator ===");

        double[] testIncomes = { 8000, 10000, 25000, 50000, 75000, 100000, 150000, 300000 };

        for (double inc : testIncomes) {
            double tax = computeTax(inc);
            double effectiveRate = (inc > 0) ? (tax / inc * 100.0) : 0.0;
            System.out.printf("Income: $%8.2f ==> Total Tax: $%8.2f | Effective Rate: %5.2f%%%n",
                    inc, tax, effectiveRate);
        }
    }
}

/*
 * Time Complexity: O(1) - Fixed number of tiered boundary conditional evaluations.
 * Space Complexity: O(1) - Constant stack registers.
 */

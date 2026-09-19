/**
 * Problem Statement:
 * Calculate Simple Interest and total maturity amount given:
 * Principal (P), Rate of interest per annum (R), and Time in years (T).
 * Formula: SI = (P * R * T) / 100
 * Handle input validation for non-negative values.
 *
 * Asked in: TCS, Cognizant, Tech Mahindra
 *
 * Approach:
 * - Use `double` for precision since currency, rate, and time frequently have fractional values.
 * - Compute `SI = (principal * rate * time) / 100.0`.
 * - Total Amount = Principal + SI.
 */
class SimpleInterestCalculator {

    public static class InterestResult {
        public final double simpleInterest;
        public final double totalAmount;

        public InterestResult(double simpleInterest, double totalAmount) {
            this.simpleInterest = simpleInterest;
            this.totalAmount = totalAmount;
        }
    }

    public static InterestResult calculate(double principal, double rateAnnual, double timeYears) {
        if (principal < 0 || rateAnnual < 0 || timeYears < 0) {
            throw new IllegalArgumentException("Principal, rate, and time must be non-negative.");
        }
        double si = (principal * rateAnnual * timeYears) / 100.0;
        double total = principal + si;
        return new InterestResult(si, total);
    }

    public static void main(String[] args) {
        double principal = 50000.0; // INR
        double rate = 7.5;          // 7.5% per annum
        double time = 3.5;          // 3.5 years

        InterestResult res = calculate(principal, rate, time);

        System.out.println("=== Simple Interest Calculation ===");
        System.out.printf("Principal Amount : ₹ %,.2f%n", principal);
        System.out.printf("Annual Rate      : %.2f %%%n", rate);
        System.out.printf("Tenure (Years)   : %.2f years%n", time);
        System.out.println("----------------------------------------");
        System.out.printf("Simple Interest  : ₹ %,.2f%n", res.simpleInterest);
        System.out.printf("Maturity Amount  : ₹ %,.2f%n", res.totalAmount);
    }
}

/*
 * Time Complexity: O(1) - Constant mathematical evaluation.
 * Space Complexity: O(1) - Primitive stack storage.
 */

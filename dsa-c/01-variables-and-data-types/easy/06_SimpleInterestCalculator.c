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

class InterestResult {
        const double simpleInterest;
        const double totalAmount;

        InterestResult(double simpleInterest, double totalAmount) {
            this.simpleInterest = simpleInterest;
            this.totalAmount = totalAmount;
        }
    }

    InterestResult calculate(double principal, double rateAnnual, double timeYears) {
        if (principal < 0 || rateAnnual < 0 || timeYears < 0) {
            fprintf(stderr, "Exception: invalid argument
"); return 0;
        }
        double si = (principal * rateAnnual * timeYears) / 100.0;
        double total = principal + si;
        return new InterestResult(si, total);
    }

    int main(void) {
        double principal = 50000.0; // INR
        double rate = 7.5;          // 7.5% per annum
        double time = 3.5;          // 3.5 years

        InterestResult res = calculate(principal, rate, time);

        printf("=== Simple Interest Calculation ===\n");
        printf("Principal Amount : ₹ %,.2f\n", principal);
        printf("Annual Rate      : %.2f %%\n", rate);
        printf("Tenure (Years)   : %.2f years\n", time);
        printf("----------------------------------------\n");
        printf("Simple Interest  : ₹ %,.2f\n", res.simpleInterest);
        printf("Maturity Amount  : ₹ %,.2f\n", res.totalAmount);
        return 0;
}

/*
 * Time Complexity: O(1) - Constant mathematical evaluation.
 * Space Complexity: O(1) - Primitive stack storage.
 */

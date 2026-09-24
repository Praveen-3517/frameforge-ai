/**
 * Problem Statement:
 * Given two integers `a` and `b`, compute:
 * 1. Their Greatest Common Divisor (GCD / HCF) using Euclid's algorithm with a `while` loop.
 * 2. Their Least Common Multiple (LCM) safely without integer overflow.
 *
 * Example:
 * a = 48, b = 18 -> GCD = 6, LCM = 144
 *
 * Asked in: Amazon, Google, TCS, Infosys, Wipro
 *
 * Approach:
 * - Euclidean Algorithm via `while` loop:
 *   Euclid's theorem states that `gcd(a, b) = gcd(b, a % b)`.
 *   Loop invariant:
 *     while (b != 0) {
 *         long temp = b;
 *         b = a % b;
 *         a = temp;
 *     }
 *     return a;
 * - LCM Calculation Formula:
 *   `lcm(a, b) = (|a * b|) / gcd(a, b)`.
 *   Critical Overflow Prevention Gotcha:
 *   Instead of `(a * b) / gcd`, evaluate as: `(a / gcd) * b`!
 *   Dividing first keeps intermediate products within 64-bit limits.
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

long long gcd(long long a, long long b) {
        a = abs(a);
        b = abs(b);

        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }

        return a;
    }

    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        long long commonGcd = gcd(a, b);
        // Divide before multiply to prevent intermediate 64-bit overflow
        return abs(a / commonGcd) * abs(b);
    }

    int main(void) {
        printf("=== Euclidean GCD & Overflow-Safe LCM (While Loop) ===\n");

        long long** testPairs = {
            { 48, 18 },
            { 101, 103 },         // Coprime primes -> GCD 1, LCM 10403
            { 1000, 250 },
            { 1000000007L, 998244353L },
            { 0, 50 },
            { -14, 21 }
        };

        for (long long* pair : testPairs) {
            long long a = pair[0], b = pair[1];
            long long g = gcd(a, b);
            long long l = lcm(a, b);
            printf("Pair (%11d, %11d) ==> GCD: %11d | LCM: %15d\n", a, b, g, l);
        }
        return 0;
}

/*
 * Time Complexity: O(log(min(a, b))) - Euclidean division step reduces operands exponentially.
 * Space Complexity: O(1) - Constant stack memory.
 */

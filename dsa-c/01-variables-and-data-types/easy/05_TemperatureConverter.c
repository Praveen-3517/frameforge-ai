/**
 * Problem Statement:
 * Implement a bidirectional temperature conversion utility:
 * 1. Celsius to Fahrenheit: F = (C * 9/5) + 32
 * 2. Fahrenheit to Celsius: C = (F - 32) * 5/9
 * Avoid the common beginner integer division bug `9 / 5 == 1`.
 *
 * Asked in: Wipro, Infosys, IBM
 *
 * Approach:
 * - If written as `9 / 5`, integer division truncates to `1`, causing incorrect calculations.
 * - Always use floating-point literals `9.0 / 5.0` or explicit double multiplication first.
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

double celsiusToFahrenheit(double celsius) {
        // Correct: 9.0 / 5.0 ensures double precision
        return (celsius * 9.0 / 5.0) + 32.0;
    }

    double fahrenheitToCelsius(double fahrenheit) {
        return (fahrenheit - 32.0) * 5.0 / 9.0;
    }

    int main(void) {
        double* testCelsius = { 0.0, 25.0, 37.0, 100.0, -40.0 };

        printf("=== Celsius to Fahrenheit Conversions ===\n");
        for (size_t _idx = 0; _idx < sizeof(testCelsius)/sizeof(testCelsius[0]); _idx++) {
        double c = testCelsius[_idx];
            double f = celsiusToFahrenheit(c);
            printf("%6.1f °C  ==>  %6.1f °F\n", c, f);
        }

        printf("\n=== Fahrenheit to Celsius Conversions ===\n");
        double* testFahrenheit = { 32.0, 77.0, 98.6, 212.0, -40.0 };
        for (size_t _idx = 0; _idx < sizeof(testFahrenheit)/sizeof(testFahrenheit[0]); _idx++) {
        double f = testFahrenheit[_idx];
            double c = fahrenheitToCelsius(f);
            printf("%6.1f °F  ==>  %6.1f °C\n", f, c);
        }

        printf("\nNote: At -40.0 degrees, both Celsius and Fahrenheit scales intersect (-40°C == -40°F).\n");
        return 0;
}

/*
 * Time Complexity: O(1) - Constant floating-point arithmetic.
 * Space Complexity: O(1) - Constant memory.
 */

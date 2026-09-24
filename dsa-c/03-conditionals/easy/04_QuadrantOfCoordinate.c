/**
 * Problem Statement:
 * Given Cartesian coordinates `(x, y)` of a point in a 2D plane, determine its exact location:
 *   - Origin: (0, 0)
 *   - X-Axis: (x != 0, y == 0)
 *   - Y-Axis: (x == 0, y != 0)
 *   - Quadrant I:   (x > 0, y > 0)
 *   - Quadrant II:  (x < 0, y > 0)
 *   - Quadrant III: (x < 0, y < 0)
 *   - Quadrant IV:  (x > 0, y < 0)
 *
 * Asked in: TCS, Infosys, Wipro, Capgemini
 *
 * Approach:
 * - Nested Conditionals / Boundary Checks:
 *   1. Check origin first: `x == 0 && y == 0`.
 *   2. Check axes: `x == 0` (Y-axis), `y == 0` (X-axis).
 *   3. Sign-based quadrant classification:
 *      x > 0: y > 0 ? Q1 : Q4
 *      x < 0: y > 0 ? Q2 : Q3
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

const char* findQuadrant(double x, double y) {
        if (x == 0 && y == 0) {
            return "Origin (0, 0)";
        } else if (y == 0) {
            return "On the X-Axis";
        } else if (x == 0) {
            return "On the Y-Axis";
        } else if (x > 0) {
            return (y > 0) ? "Quadrant I (+, +)" : "Quadrant IV (+, -)";
        } else {
            return (y > 0) ? "Quadrant II (-, +)" : "Quadrant III (-, -)";
        }
    }

    int main(void) {
        printf("=== 2D Cartesian Coordinate Plane Quadrant Classifier ===\n");

        double** testPoints = {
            { 0, 0 },
            { 5, 0 },
            { 0, -3 },
            { 4.5, 7.2 },
            { -3.0, 8.1 },
            { -6.2, -4.5 },
            { 9.0, -2.1 }
        };

        for (double* pt : testPoints) {
            double x = pt[0];
            double y = pt[1];
            printf("Point (%5.1f, %5.1f) ==> %s\n", x, y, findQuadrant(x, y));
        }
        return 0;
}

/*
 * Time Complexity: O(1) - Constant branch checks.
 * Space Complexity: O(1) - Stack variables only.
 */

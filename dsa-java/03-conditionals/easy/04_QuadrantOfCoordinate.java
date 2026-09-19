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
class QuadrantOfCoordinate {

    public static String findQuadrant(double x, double y) {
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

    public static void main(String[] args) {
        System.out.println("=== 2D Cartesian Coordinate Plane Quadrant Classifier ===");

        double[][] testPoints = {
            { 0, 0 },
            { 5, 0 },
            { 0, -3 },
            { 4.5, 7.2 },
            { -3.0, 8.1 },
            { -6.2, -4.5 },
            { 9.0, -2.1 }
        };

        for (double[] pt : testPoints) {
            double x = pt[0];
            double y = pt[1];
            System.out.printf("Point (%5.1f, %5.1f) ==> %s%n", x, y, findQuadrant(x, y));
        }
    }
}

/*
 * Time Complexity: O(1) - Constant branch checks.
 * Space Complexity: O(1) - Stack variables only.
 */

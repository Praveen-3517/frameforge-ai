import java.util.Arrays;

/**
 * Problem Statement:
 * Given three side lengths a, b, and c of a potential triangle:
 * 1. Determine if a valid non-degenerate triangle can be formed (Triangle Inequality Theorem).
 * 2. If valid, classify the triangle as Equilateral, Isosceles, or Scalene.
 * 3. Additionally check if it forms a Right-Angled Triangle (Pythagorean Theorem).
 *
 * Asked in: Infosys, Accenture, TCS, Cognizant
 *
 * Approach:
 * - Triangle Inequality Theorem:
 *   A triangle is valid if and only if the sum of any two sides is strictly greater than the third side:
 *   `a + b > c && a + c > b && b + c > a` (and all sides > 0).
 * - Sort the three sides so `s[0] <= s[1] <= s[2]`:
 *   Then condition simplifies to: `s[0] + s[1] > s[2]`.
 * - Classification:
 *   - Equilateral: `s[0] == s[2]` (since array is sorted, min == max implies all 3 equal).
 *   - Isosceles: `s[0] == s[1] || s[1] == s[2]`.
 *   - Scalene: all sides distinct.
 *   - Right-angled: `s[0]^2 + s[1]^2 == s[2]^2`.
 */
class TriangleValidityAndType {

    public static String analyzeTriangle(double a, double b, double c) {
        if (a <= 0 || b <= 0 || c <= 0) {
            return "Invalid: Sides must be strictly positive.";
        }

        double[] sides = { a, b, c };
        Arrays.sort(sides);

        // Triangle Inequality check
        if (sides[0] + sides[1] <= sides[2]) {
            return "Invalid: Sum of shorter two sides must be greater than the longest side.";
        }

        StringBuilder classification = new StringBuilder();

        // Check side equality
        if (sides[0] == sides[2]) {
            classification.append("Equilateral");
        } else if (sides[0] == sides[1] || sides[1] == sides[2]) {
            classification.append("Isosceles");
        } else {
            classification.append("Scalene");
        }

        // Check Pythagorean right-angle property with floating-point tolerance
        double pythDiff = Math.abs((sides[0] * sides[0] + sides[1] * sides[1]) - (sides[2] * sides[2]));
        if (pythDiff < 1e-9) {
            classification.append(" & Right-Angled");
        }

        return classification.toString();
    }

    public static void main(String[] args) {
        System.out.println("=== Triangle Inequality & Geometric Classification ===");

        double[][] testTriangles = {
            { 5, 5, 5 },      // Equilateral
            { 5, 5, 8 },      // Isosceles
            { 3, 4, 5 },      // Scalene & Right-Angled
            { 6, 8, 10 },     // Scalene & Right-Angled
            { 7, 10, 12 },    // Scalene
            { 1, 2, 3 },      // Degenerate / Invalid
            { 1, 5, 10 },     // Invalid
            { -2, 4, 4 }      // Negative side
        };

        for (double[] t : testTriangles) {
            System.out.printf("Sides (%.1f, %.1f, %.1f) ==> %s%n",
                    t[0], t[1], t[2], analyzeTriangle(t[0], t[1], t[2]));
        }
    }
}

/*
 * Time Complexity: O(1) - Sorting 3 elements and fixed arithmetic checks.
 * Space Complexity: O(1) - Constant stack array.
 */

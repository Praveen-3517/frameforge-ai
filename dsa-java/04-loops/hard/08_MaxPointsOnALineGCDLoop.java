import java.util.HashMap;
import java.util.Map;

/**
 * Problem Statement:
 * Given an array of points where `points[i] = [xi, yi]` represents a point on the X-Y plane,
 * return the maximum number of points that lie on the same straight line.
 * (LeetCode 149: Max Points on a Line - Hard).
 *
 * Example:
 * points = [[1,1],[2,2],[3,3]] -> 3
 * points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]] -> 4
 *
 * Asked in: Google, Amazon, LinkedIn, Apple, Microsoft
 *
 * Approach:
 * - Nested Point Anchor Loops with GCD-Normalized Coprime Slopes:
 *   - Outer loop fixes an anchor point `points[i]`.
 *   - Inner loop computes the slope with every other point `points[j]`.
 *   - Critical IEEE 754 Precision Trap:
 *     Using floating-point `double slope = (double) dy / dx` causes subtle rounding inaccuracies
 *     where collinear points receive slightly different float representations!
 *   - Exact Representation via Euclidean GCD Loop:
 *     Reduce `dy` and `dx` to their coprime irreducible fractional form:
 *     `int g = gcd(Math.abs(dx), Math.abs(dy));`
 *     `dx /= g; dy /= g;`
 *     Normalize sign: if `dx < 0 || (dx == 0 && dy < 0)`, flip both signs so equal slopes
 *     have identical representations.
 *   - Hash key `"dy/dx"` guarantees exact integer precision without floating-point errors.
 */
class MaxPointsOnALineGCDLoop {

    private static int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static int maxPoints(int[][] points) {
        if (points == null || points.length == 0) return 0;
        int n = points.length;
        if (n <= 2) return n;

        int globalMax = 0;

        for (int i = 0; i < n; i++) {
            Map<String, Integer> slopeCount = new HashMap<>();
            int duplicates = 1;
            int localMax = 0;

            for (int j = i + 1; j < n; j++) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                if (dx == 0 && dy == 0) {
                    duplicates++;
                    continue;
                }

                // Canonical GCD reduction
                int g = gcd(Math.abs(dx), Math.abs(dy));
                dx /= g;
                dy /= g;

                // Canonical sign normalization: keep dx >= 0
                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }

                String slopeKey = dy + "/" + dx;
                int count = slopeCount.getOrDefault(slopeKey, 0) + 1;
                slopeCount.put(slopeKey, count);
                localMax = Math.max(localMax, count);
            }

            globalMax = Math.max(globalMax, localMax + duplicates);
        }

        return globalMax;
    }

    public static void main(String[] args) {
        System.out.println("=== LeetCode 149: Max Points on a Line (GCD Slope Normalization) ===");

        int[][] points1 = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
        System.out.printf("Points: %s ==> Max Collinear: %d%n",
                java.util.Arrays.deepToString(points1), maxPoints(points1));

        int[][] points2 = {
            { 1, 1 }, { 3, 2 }, { 5, 3 }, { 4, 1 }, { 2, 3 }, { 1, 4 }
        };
        System.out.printf("Points: %s ==> Max Collinear: %d%n",
                java.util.Arrays.deepToString(points2), maxPoints(points2));
    }
}

/*
 * Time Complexity: O(N^2 * log(range)) - Pairwise loops with logarithmic GCD per pair.
 * Space Complexity: O(N) - Slope frequency map per anchor point.
 */

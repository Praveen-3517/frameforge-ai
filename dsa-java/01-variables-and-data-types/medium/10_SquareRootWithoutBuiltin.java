/**
 * Problem Statement:
 * Given a non-negative integer `x`, compute and return the square root of `x` rounded down
 * to the nearest integer (integer square root).
 * Do NOT use built-in exponent functions like `Math.sqrt(x)` or `Math.pow(x, 0.5)`.
 * Avoid integer overflow when squaring large numbers (`mid * mid`).
 * (LeetCode 69: Sqrt(x)).
 *
 * Asked in: Google, Amazon, Microsoft, Apple
 *
 * Approach:
 * - Binary Search in range `[1, x]`:
 *   - For `x = 0` or `x = 1`, return `x`.
 *   - Search space `left = 1, right = x / 2`.
 *   - Midpoint `mid = left + (right - left) / 2`.
 *   - Overflow Trap: Doing `if (mid * mid <= x)` will overflow 32-bit integer when `mid > 46340`.
 *   - Overflow-safe check: Use division `if (mid <= x / mid)` or promote `mid` to `long`.
 */
class SquareRootWithoutBuiltin {

    public static int mySqrt(int x) {
        if (x < 2) return x;

        int left = 1;
        int right = x / 2;
        int ans = 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // Overflow-safe check equivalent to: mid * mid <= x
            if (mid <= x / mid) {
                ans = mid;         // mid is a candidate floor answer
                left = mid + 1;    // Try to find a larger answer on the right
            } else {
                right = mid - 1;   // mid * mid > x, search left
            }
        }

        return ans;
    }

    public static void main(String[] args) {
        int[] testCases = { 0, 1, 4, 8, 9, 2147395599, Integer.MAX_VALUE };

        System.out.println("=== LeetCode 69: Integer Sqrt(x) via Overflow-Safe Binary Search ===");
        for (int x : testCases) {
            int sqrt = mySqrt(x);
            int expected = (int) Math.sqrt(x);
            System.out.printf("x = %-12d ==> mySqrt: %-8d | Math.sqrt: %-8d%n", x, sqrt, expected);
            assert sqrt == expected : "Mismatch detected!";
        }
        System.out.println("All test cases passed!");
    }
}

/*
 * Time Complexity: O(log X) - Binary search space is halved each step.
 * Space Complexity: O(1) - Constant variables with no extra allocation.
 */

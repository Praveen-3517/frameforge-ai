/*
 * Problem Statement:
 * Given a non-negative integer x, return the square root of x rounded down to the
 * nearest integer. The returned integer should be non-negative as well.
 * You must not use any built-in exponent function or operator (like pow(x, 0.5) or sqrt(x)).
 * (LeetCode 69: Sqrt(x))
 * 
 * Example 1:
 * Input: x = 4
 * Output: 2
 * 
 * Example 2:
 * Input: x = 8
 * Output: 2 (sqrt(8) = 2.8284..., floor is 2)
 * 
 * Asked in: Apple, Bloomberg, Amazon, Facebook/Meta
 */

class SquareRootBinarySearch {

    /**
     * Approach:
     * Binary Search on Integer Range [0, x]:
     * - Protect against integer multiplication overflow by using division: `mid <= x / mid`.
     * - If mid * mid <= x, mid is a viable candidate; search right half for a larger root.
     * - Else, search left half.
     */
    public static int mySqrt(int x) {
        if (x < 2) return x;

        int low = 1;
        int high = x / 2;
        int ans = 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Equivalent to mid * mid <= x without 32-bit overflow
            if (mid <= x / mid) {
                ans = mid;
                low = mid + 1; // Try finding larger square root
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }

    public static void main(String[] args) {
        int[] tests = {0, 1, 4, 8, 16, 26, 2147395599, 2147483647};

        System.out.println("--- Integer Square Root via Binary Search ---");
        for (int x : tests) {
            System.out.printf("sqrt(%10d) = %6d (Math.sqrt check: %6d)%n",
                    x, mySqrt(x), (int) Math.sqrt(x));
        }
    }
}

/*
 * Time Complexity: O(log x) binary search steps.
 * Space Complexity: O(1) auxiliary space.
 */

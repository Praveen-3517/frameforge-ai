import java.util.Arrays;

/**
 * Problem Statement:
 * Given an array containing `N - 2` distinct integers in the range `[1, N]`,
 * find the two missing numbers in O(N) runtime and O(1) auxiliary space.
 *
 * Example:
 * nums = [1, 2, 4, 6] (N = 6, missing 3 and 5)
 * Output: [3, 5]
 *
 * Asked in: Amazon, Google, Microsoft, Adobe
 *
 * Approach:
 * - Bitwise XOR Partitioning:
 *   1. Compute the XOR sum of all numbers in `nums` and all numbers from 1 to N:
 *      `xorTotal = (1 ^ 2 ^ ... ^ N) ^ (nums[0] ^ nums[1] ^ ...)`
 *      All present numbers cancel out in pairs, leaving: `xorTotal = missing1 ^ missing2`.
 *   2. Since `missing1 != missing2`, `xorTotal != 0`. There must be at least one bit where they differ.
 *   3. Isolate the lowest set bit using `diffBit = xorTotal & (-xorTotal)`.
 *      In one of the missing numbers, this bit is 1; in the other, it is 0.
 *   4. Partition both the array elements and the complete range `1..N` into two buckets:
 *      - Bucket 1: Elements where `(val & diffBit) != 0`
 *      - Bucket 2: Elements where `(val & diffBit) == 0`
 *   5. XORing each bucket separately cancels all present pairs and isolates `missing1` and `missing2`!
 */
class MissingTwoNumbersBitwise {

    public static int[] findTwoMissingNumbers(int[] nums) {
        int n = nums.length + 2;

        // Step 1: XOR all numbers from 1 to n with all numbers in array
        int xorTotal = 0;
        for (int i = 1; i <= n; i++) {
            xorTotal ^= i;
        }
        for (int num : nums) {
            xorTotal ^= num;
        }

        // Step 2: Find rightmost set bit
        int diffBit = xorTotal & (-xorTotal);

        // Step 3: Partition into two groups
        int missing1 = 0;
        int missing2 = 0;

        for (int i = 1; i <= n; i++) {
            if ((i & diffBit) != 0) {
                missing1 ^= i;
            } else {
                missing2 ^= i;
            }
        }

        for (int num : nums) {
            if ((num & diffBit) != 0) {
                missing1 ^= num;
            } else {
                missing2 ^= num;
            }
        }

        return new int[] { Math.min(missing1, missing2), Math.max(missing1, missing2) };
    }

    public static void main(String[] args) {
        System.out.println("=== Find Two Missing Numbers (O(N) Time, O(1) Space via XOR) ===");

        int[][] testArrays = {
            { 1, 2, 4, 6 },          // N = 6, missing: 3, 5
            { 2, 3 },                // N = 4, missing: 1, 4
            { 1, 3, 5, 6, 7 },       // N = 7, missing: 2, 4
            { 1 }                    // N = 3, missing: 2, 3
        };

        for (int[] arr : testArrays) {
            int[] missing = findTwoMissingNumbers(arr);
            System.out.printf("Array: %s (N = %d)%n ==> Missing Two: %s%n%n",
                    Arrays.toString(arr), arr.length + 2, Arrays.toString(missing));
        }
    }
}

/*
 * Time Complexity: O(N) - Two sequential passes over the array and range 1..N.
 * Space Complexity: O(1) - Constant auxiliary space (no hash sets or extra arrays).
 */

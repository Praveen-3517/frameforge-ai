/**
 * Problem Statement:
 * Compute the sum and maximum element of an array `arr` recursively using a
 * Divide-and-Conquer tree strategy.
 * Show that splitting in half achieves logarithmic call stack depth O(log N),
 * compared to linear O(N) for sequential recursion.
 *
 * Asked in: Amazon, Infosys, TCS, Adobe
 *
 * Approach:
 * - Divide and Conquer Recursion:
 *   - Base Case: When `start == end`, return `arr[start]`.
 *   - Divide: Calculate `mid = start + (end - start) / 2`.
 *   - Conquer:
 *     - Sum: `findSum(arr, start, mid) + findSum(arr, mid + 1, end)`
 *     - Max: `Math.max(findMax(arr, start, mid), findMax(arr, mid + 1, end))`
 *   - Call stack depth is bounded by tree height: `ceil(log2 N)`.
 */
class RecursiveArraySumAndMax {

    public static long findSum(int[] arr, int start, int end) {
        if (start == end) {
            return arr[start];
        }
        int mid = start + (end - start) / 2;
        return findSum(arr, start, mid) + findSum(arr, mid + 1, end);
    }

    public static int findMax(int[] arr, int start, int end) {
        if (start == end) {
            return arr[start];
        }
        int mid = start + (end - start) / 2;
        int leftMax = findMax(arr, start, mid);
        int rightMax = findMax(arr, mid + 1, end);
        return Math.max(leftMax, rightMax);
    }

    public static void main(String[] args) {
        System.out.println("=== Recursive Array Sum & Max (Divide-and-Conquer) ===");

        int[] arr = { 12, 35, 1, 10, 34, 1, 99, 45 };

        long sum = findSum(arr, 0, arr.length - 1);
        int max = findMax(arr, 0, arr.length - 1);

        System.out.println("Array: " + java.util.Arrays.toString(arr));
        System.out.println("Recursive Sum: " + sum);
        System.out.println("Recursive Max: " + max);
    }
}

/*
 * Time Complexity: O(N) - Visits each element in the recursion tree.
 * Space Complexity: O(log N) - Maximum call stack depth of the balanced binary recursion tree.
 */

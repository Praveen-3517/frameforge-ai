/**
 * Problem Statement:
 * Determine whether an array of integers is sorted in non-decreasing order using pure recursion.
 * The method must short-circuit and return false immediately upon encountering the first inversion.
 *
 * Asked in: Google, Microsoft, Infosys, Wipro
 *
 * Approach:
 * - Recursive Invariant:
 *   Base Case: If `index >= arr.length - 1`, the remaining segment has 0 or 1 element, which is trivially sorted -> return true.
 *   Recursive Step:
 *   - If `arr[index] > arr[index + 1]`: An inversion is detected -> return false immediately!
 *   - Otherwise: return `isSorted(arr, index + 1)`.
 */
class CheckArraySortedRecursion {

    public static boolean isSorted(int[] arr) {
        if (arr == null || arr.length <= 1) return true;
        return checkHelper(arr, 0);
    }

    private static boolean checkHelper(int[] arr, int index) {
        // Base case: reached last element
        if (index >= arr.length - 1) {
            return true;
        }

        // Inversion check
        if (arr[index] > arr[index + 1]) {
            return false;
        }

        // Recursive tail call
        return checkHelper(arr, index + 1);
    }

    public static void main(String[] args) {
        System.out.println("=== Recursive Sorted Array Validator ===");

        int[][] testArrays = {
            { 1, 2, 3, 4, 5 },
            { 10, 20, 20, 30, 40 },
            { 5, 4, 3, 2, 1 },
            { 1, 2, 5, 4, 6 },
            { 42 }
        };

        for (int[] arr : testArrays) {
            boolean sorted = isSorted(arr);
            System.out.printf("Array: %-22s ==> Is Sorted: %s%n",
                    java.util.Arrays.toString(arr), sorted);
        }
    }
}

/*
 * Time Complexity: O(N) - Examines at most N - 1 pairs.
 * Space Complexity: O(N) - Call stack depth up to N frames.
 */

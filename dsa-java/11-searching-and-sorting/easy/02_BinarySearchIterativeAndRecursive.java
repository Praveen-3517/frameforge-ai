/*
 * Problem Statement:
 * Implement Binary Search in a sorted array using both Iterative and Recursive techniques:
 * - Handle integer overflow safely in midpoint calculation: `low + (high - low) / 2`.
 * - Return index if found, else return -1.
 * 
 * Asked in: Google, Microsoft, Amazon, Facebook/Meta
 */

import java.util.Arrays;

class BinarySearchIterativeAndRecursive {

    // 1. Iterative Binary Search
    public static int searchIterative(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            // Safe midpoint to prevent (low + high) integer overflow
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return -1;
    }

    // 2. Recursive Binary Search
    public static int searchRecursive(int[] arr, int target) {
        return recursiveHelper(arr, target, 0, arr.length - 1);
    }

    private static int recursiveHelper(int[] arr, int target, int low, int high) {
        if (low > high) return -1;

        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return recursiveHelper(arr, target, mid + 1, high);
        } else {
            return recursiveHelper(arr, target, low, mid - 1);
        }
    }

    public static void main(String[] args) {
        int[] sorted = {3, 9, 14, 19, 25, 31, 42, 55, 68, 77, 89, 99};

        System.out.println("Array: " + Arrays.toString(sorted));
        int[] queries = {31, 3, 99, 50};

        System.out.println("--- Binary Search Queries ---");
        for (int q : queries) {
            int iterIdx = searchIterative(sorted, q);
            int recIdx = searchRecursive(sorted, q);
            System.out.printf("Target: %2d -> Iterative: %2d | Recursive: %2d%n", q, iterIdx, recIdx);
        }
    }
}

/*
 * Time Complexity: O(log N) - Search space halves at every step.
 * Space Complexity: Iterative: O(1) auxiliary space; Recursive: O(log N) stack frames.
 */

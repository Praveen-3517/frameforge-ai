/**
 * Problem Statement:
 * Given an integer array `arr` and a `target` element:
 * 1. Implement Linear Search (works on any unsorted/sorted array, O(N) time).
 * 2. Implement Binary Search (requires array to be sorted, O(log N) time).
 * 3. Safely calculate mid index: `mid = low + (high - low) / 2` to prevent 32-bit integer overflow.
 *
 * Asked in: TCS, Infosys, Wipro, Accenture, Cognizant
 *
 * Approach:
 * - Linear Search: Scan array element by element from index 0 to n - 1. Return index if found, else -1.
 * - Binary Search:
 *   Maintain `low = 0`, `high = n - 1`.
 *   Calculate `mid = low + (high - low) / 2`.
 *   If `arr[mid] == target`: return mid.
 *   If `arr[mid] < target`: `low = mid + 1`.
 *   If `arr[mid] > target`: `high = mid - 1`.
 */
class LinearAndBinarySearchArray {

    public static int linearSearch(int[] arr, int target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }

    public static int binarySearch(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            // Prevent 32-bit overflow bug: (low + high) >>> 1 or low + (high - low) / 2
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

    public static void main(String[] args) {
        System.out.println("=== Linear Search vs Binary Search Comparison ===");

        int[] sortedArr = { 2, 5, 8, 12, 16, 23, 38, 56, 72, 91 };
        int[] queries = { 23, 2, 91, 50 };

        for (int q : queries) {
            int linIdx = linearSearch(sortedArr, q);
            int binIdx = binarySearch(sortedArr, q);
            System.out.printf("Target %2d ==> Linear Index: %2d | Binary Index: %2d%n", q, linIdx, binIdx);
        }
    }
}

/*
 * Time Complexity:
 *   - Linear Search: O(N)
 *   - Binary Search: O(log N)
 * Space Complexity: O(1) - Constant stack space.
 */

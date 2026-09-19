/*
 * Problem Statement:
 * Implement Insertion Sort:
 * - Analogous to sorting a hand of playing cards.
 * - For each element at index i, shift elements in sorted sublist arr[0...i-1] that are
 *   greater than arr[i] one position to the right.
 * - Insert key into its correct sorted location.
 * - Highly efficient (O(N) time) for small or nearly-sorted datasets; adaptive and stable.
 * 
 * Asked in: Amazon, Oracle, TCS, IBM
 */

import java.util.Arrays;

class InsertionSortArray {

    public static void insertionSort(int[] arr) {
        int n = arr.length;

        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;

            // Shift elements of arr[0...i-1] that are greater than key to one position ahead
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }

            arr[j + 1] = key;
        }
    }

    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6};

        System.out.println("Original array: " + Arrays.toString(arr));
        insertionSort(arr);
        System.out.println("Sorted array:   " + Arrays.toString(arr));

        int[] nearlySorted = {1, 2, 4, 3, 5, 6};
        insertionSort(nearlySorted);
        System.out.println("Nearly sorted:  " + Arrays.toString(nearlySorted));
    }
}

/*
 * Time Complexity: Best: O(N) when nearly sorted; Worst & Average: O(N^2).
 * Space Complexity: O(1) in-place sorting.
 */

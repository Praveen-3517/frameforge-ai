/*
 * Problem Statement:
 * Implement Selection Sort with step-by-step state logging:
 * - Divide array into sorted prefix and unsorted suffix.
 * - In each pass, scan unsorted suffix to locate minimum element.
 * - Swap minimum element with the first element of unsorted suffix.
 * - Note: Selection sort makes at most N - 1 swaps (ideal when write operations are expensive).
 * 
 * Asked in: Accenture, Cognizant, Wipro
 */

import java.util.Arrays;

class SelectionSortStepByStep {

    public static void selectionSort(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;

            // Find index of minimum element in unsorted range [i, n-1]
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }

            // Swap if minIdx changed
            if (minIdx != i) {
                int temp = arr[i];
                arr[i] = arr[minIdx];
                arr[minIdx] = temp;
            }

            System.out.printf("Pass %d (min=%2d): %s%n", i + 1, arr[i], Arrays.toString(arr));
        }
    }

    public static void main(String[] args) {
        int[] arr = {29, 10, 14, 37, 13};

        System.out.println("Initial array: " + Arrays.toString(arr));
        System.out.println("--- Executing Selection Sort ---");
        selectionSort(arr);
        System.out.println("Final sorted:  " + Arrays.toString(arr));
    }
}

/*
 * Time Complexity: O(N^2) in best, average, and worst cases (always scans entire unsorted suffix).
 * Space Complexity: O(1) in-place sorting.
 */

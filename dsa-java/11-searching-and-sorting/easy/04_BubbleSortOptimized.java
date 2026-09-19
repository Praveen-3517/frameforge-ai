/*
 * Problem Statement:
 * Implement an Optimized Bubble Sort:
 * - Repeatedly step through list, compare adjacent elements, and swap if out of order.
 * - Optimization: Track a `swapped` boolean flag. If an entire pass completes without
 *   any swap, the array is already fully sorted. Break early!
 * - Achieves O(N) best case on already sorted inputs.
 * 
 * Asked in: TCS, Infosys, Capgemini, Wipro
 */

import java.util.Arrays;

class BubbleSortOptimized {

    public static void bubbleSort(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n - 1; i++) {
            boolean swapped = false;

            // In each pass, the largest remaining element bubbles up to index n - 1 - i
            for (int j = 0; j < n - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    swapped = true;
                }
            }

            // Early exit optimization
            if (!swapped) break;
        }
    }

    public static void main(String[] args) {
        int[] arr1 = {64, 34, 25, 12, 22, 11, 90};
        System.out.println("Original: " + Arrays.toString(arr1));
        bubbleSort(arr1);
        System.out.println("Sorted:   " + Arrays.toString(arr1));

        int[] alreadySorted = {1, 2, 3, 4, 5};
        bubbleSort(alreadySorted); // Exits after 1 pass
        System.out.println("\nAlready sorted test: " + Arrays.toString(alreadySorted));
    }
}

/*
 * Time Complexity: Best: O(N) when already sorted; Worst & Average: O(N^2).
 * Space Complexity: O(1) in-place sorting.
 */

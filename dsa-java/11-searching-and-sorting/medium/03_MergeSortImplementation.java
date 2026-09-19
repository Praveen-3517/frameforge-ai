/*
 * Problem Statement:
 * Implement the Merge Sort algorithm:
 * - Divide array into two halves recursively until base case (length <= 1).
 * - Merge the two sorted subarrays into a single sorted range.
 * - Guarantees O(N log N) time complexity in all cases (Best, Average, Worst).
 * - Stable sorting algorithm.
 * 
 * Asked in: Amazon, Microsoft, Goldman Sachs, Uber
 */

import java.util.Arrays;

class MergeSortImplementation {

    public static void mergeSort(int[] arr) {
        if (arr == null || arr.length <= 1) return;
        int[] temp = new int[arr.length];
        sort(arr, 0, arr.length - 1, temp);
    }

    private static void sort(int[] arr, int low, int high, int[] temp) {
        if (low >= high) return;

        int mid = low + (high - low) / 2;
        sort(arr, low, mid, temp);
        sort(arr, mid + 1, high, temp);
        merge(arr, low, mid, high, temp);
    }

    private static void merge(int[] arr, int low, int mid, int high, int[] temp) {
        // Copy segment to temp buffer
        for (int i = low; i <= high; i++) {
            temp[i] = arr[i];
        }

        int i = low;
        int j = mid + 1;
        int k = low;

        while (i <= mid && j <= high) {
            if (temp[i] <= temp[j]) { // <= ensures stability
                arr[k++] = temp[i++];
            } else {
                arr[k++] = temp[j++];
            }
        }

        while (i <= mid) {
            arr[k++] = temp[i++];
        }
        // Elements from right half (j..high) already in position
    }

    public static void main(String[] args) {
        int[] arr = {38, 27, 43, 3, 9, 82, 10};

        System.out.println("Original array: " + Arrays.toString(arr));
        mergeSort(arr);
        System.out.println("Sorted array:   " + Arrays.toString(arr));
    }
}

/*
 * Time Complexity: O(N log N) in all cases (Best, Average, Worst).
 * Space Complexity: O(N) for auxiliary merge buffer + O(log N) stack frames.
 */

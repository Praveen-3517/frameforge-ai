/*
 * Problem Statement:
 * Implement QuickSort with both partitioning schemes:
 * 1. Lomuto Partition Scheme (simpler to implement, pivot at end).
 * 2. Hoare Partition Scheme (original scheme by Tony Hoare, fewer swaps on average).
 * 
 * Asked in: Google, Microsoft, Amazon, Oracle, Apple
 */

import java.util.Arrays;

class QuickSortLomutoAndHoare {

    // 1. Lomuto Partition Scheme
    public static void quickSortLomuto(int[] arr, int low, int high) {
        if (low < high) {
            int pIndex = partitionLomuto(arr, low, high);
            quickSortLomuto(arr, low, pIndex - 1);
            quickSortLomuto(arr, pIndex + 1, high);
        }
    }

    private static int partitionLomuto(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);
        return i + 1;
    }

    // 2. Hoare Partition Scheme
    public static void quickSortHoare(int[] arr, int low, int high) {
        if (low < high) {
            int pIndex = partitionHoare(arr, low, high);
            quickSortHoare(arr, low, pIndex);
            quickSortHoare(arr, pIndex + 1, high);
        }
    }

    private static int partitionHoare(int[] arr, int low, int high) {
        int pivot = arr[low + (high - low) / 2];
        int i = low - 1;
        int j = high + 1;

        while (true) {
            do { i++; } while (arr[i] < pivot);
            do { j--; } while (arr[j] > pivot);

            if (i >= j) return j;
            swap(arr, i, j);
        }
    }

    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        int[] arr1 = {10, 80, 30, 90, 40, 50, 70};
        System.out.println("Original: " + Arrays.toString(arr1));
        quickSortLomuto(arr1, 0, arr1.length - 1);
        System.out.println("Sorted (Lomuto): " + Arrays.toString(arr1));

        int[] arr2 = {10, 80, 30, 90, 40, 50, 70};
        quickSortHoare(arr2, 0, arr2.length - 1);
        System.out.println("Sorted (Hoare):  " + Arrays.toString(arr2));
    }
}

/*
 * Time Complexity: Average & Best: O(N log N); Worst: O(N^2) when array is unbalanced.
 * Space Complexity: O(log N) recursion stack depth on average.
 */

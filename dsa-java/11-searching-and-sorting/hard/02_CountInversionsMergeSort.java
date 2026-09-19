/*
 * Problem Statement:
 * Given an array of integers, find the Inversion Count in the array.
 * Inversion Count indicates how far (or close) the array is from being sorted.
 * Two elements arr[i] and arr[j] form an inversion if arr[i] > arr[j] and i < j.
 * 
 * Example:
 * Input: arr = [8, 4, 2, 1]
 * Output: 6
 * Inversions: (8,4), (8,2), (8,1), (4,2), (4,1), (2,1)
 * 
 * Asked in: Amazon, Microsoft, Flipkart, Google
 */

import java.util.Arrays;

class CountInversionsMergeSort {

    /**
     * Approach:
     * Enhanced Merge Sort:
     * While merging two sorted halves arr[low..mid] and arr[mid+1..high]:
     * If arr[i] > arr[j], then since left half is sorted, EVERY element from
     * i to mid is strictly greater than arr[j]!
     * Count += (mid - i + 1).
     */
    public static long countInversions(int[] arr) {
        if (arr == null || arr.length <= 1) return 0;
        int[] temp = new int[arr.length];
        return mergeSortAndCount(arr, 0, arr.length - 1, temp);
    }

    private static long mergeSortAndCount(int[] arr, int low, int high, int[] temp) {
        long count = 0;
        if (low < high) {
            int mid = low + (high - low) / 2;
            count += mergeSortAndCount(arr, low, mid, temp);
            count += mergeSortAndCount(arr, mid + 1, high, temp);
            count += mergeAndCount(arr, low, mid, high, temp);
        }
        return count;
    }

    private static long mergeAndCount(int[] arr, int low, int mid, int high, int[] temp) {
        for (int i = low; i <= high; i++) temp[i] = arr[i];

        int i = low;
        int j = mid + 1;
        int k = low;
        long invCount = 0;

        while (i <= mid && j <= high) {
            if (temp[i] <= temp[j]) {
                arr[k++] = temp[i++];
            } else {
                arr[k++] = temp[j++];
                invCount += (mid - i + 1); // Key inversion logic
            }
        }

        while (i <= mid) arr[k++] = temp[i++];
        return invCount;
    }

    public static void main(String[] args) {
        int[] arr1 = {8, 4, 2, 1};
        System.out.println("Array: " + Arrays.toString(arr1));
        System.out.println("Inversion count: " + countInversions(arr1) + " (Expected: 6)");

        int[] arr2 = {1, 20, 6, 4, 5};
        System.out.println("\nArray: " + Arrays.toString(arr2));
        System.out.println("Inversion count: " + countInversions(arr2) + " (Expected: 5)");
    }
}

/*
 * Time Complexity: O(N log N) - Modified MergeSort.
 * Space Complexity: O(N) auxiliary space.
 */

/*
 * Problem Statement:
 * Given a sorted array where you do not know beforehand whether it is sorted in
 * ascending or descending order, implement an Order-Agnostic Binary Search to find target.
 * 
 * Asked in: Amazon, Goldman Sachs, Cognizant
 */

import java.util.Arrays;

class OrderAgnosticBinarySearch {

    /**
     * Approach:
     * Check first element vs last element:
     * If arr[0] <= arr[length - 1], the array is ascending.
     * Otherwise, it is descending.
     * Use the flag to adapt low/high updates.
     */
    public static int orderAgnosticSearch(int[] arr, int target) {
        if (arr == null || arr.length == 0) return -1;

        int low = 0;
        int high = arr.length - 1;
        boolean isAscending = arr[low] <= arr[high];

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            }

            if (isAscending) {
                if (arr[mid] < target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            } else { // Descending order
                if (arr[mid] > target) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }

    public static void main(String[] args) {
        int[] asc = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
        int[] desc = {91, 72, 56, 38, 23, 16, 12, 8, 5, 2};

        int target = 23;
        System.out.println("Ascending array:  " + Arrays.toString(asc));
        System.out.println("Search for " + target + ": Index " + orderAgnosticSearch(asc, target));

        System.out.println("\nDescending array: " + Arrays.toString(desc));
        System.out.println("Search for " + target + ": Index " + orderAgnosticSearch(desc, target));
    }
}

/*
 * Time Complexity: O(log N) binary search steps.
 * Space Complexity: O(1) auxiliary space.
 */

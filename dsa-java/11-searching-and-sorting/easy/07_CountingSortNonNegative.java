/*
 * Problem Statement:
 * Implement Counting Sort for non-negative integers:
 * - Non-comparison integer sorting algorithm.
 * - Counts frequency of each distinct value, builds prefix sums to determine
 *   stable output positions.
 * - Time complexity O(N + K) where K is the maximum value in the array.
 * 
 * Asked in: Amazon, Microsoft, Samsung, Uber
 */

import java.util.Arrays;

class CountingSortNonNegative {

    public static int[] countingSort(int[] arr) {
        if (arr == null || arr.length <= 1) return arr;

        // Find maximum value
        int max = arr[0];
        for (int val : arr) {
            if (val > max) max = val;
        }

        // 1. Build frequency array
        int[] count = new int[max + 1];
        for (int val : arr) {
            count[val]++;
        }

        // 2. Compute prefix sums (cumulative counts) for stable positioning
        for (int i = 1; i <= max; i++) {
            count[i] += count[i - 1];
        }

        // 3. Build output array in reverse to preserve stability
        int[] output = new int[arr.length];
        for (int i = arr.length - 1; i >= 0; i--) {
            int val = arr[i];
            output[count[val] - 1] = val;
            count[val]--;
        }

        return output;
    }

    public static void main(String[] args) {
        int[] arr = {4, 2, 2, 8, 3, 3, 1};

        System.out.println("Original array: " + Arrays.toString(arr));
        int[] sorted = countingSort(arr);
        System.out.println("Sorted array:   " + Arrays.toString(sorted));
    }
}

/*
 * Time Complexity: O(N + K) where N is array length and K is maximum element.
 * Space Complexity: O(N + K) for count and output arrays.
 */

import java.util.Arrays;

/**
 * Problem Statement:
 * Given an array `arr`, reverse the array elements in-place without using extra array memory.
 * Also implement a general range reversal helper: `reverseRange(arr, start, end)` which serves
 * as a crucial sub-routine in array rotation and permutation algorithms.
 *
 * Asked in: Infosys, Wipro, TCS, Cognizant
 *
 * Approach:
 * - Two-Pointer In-Place Reversal:
 *   Initialize `left = 0` and `right = arr.length - 1`.
 *   While `left < right`:
 *     Swap `arr[left]` and `arr[right]`.
 *     Advance `left++`, decrement `right--`.
 */
class ReverseArrayInPlace {

    public static void reverse(int[] arr) {
        if (arr == null || arr.length <= 1) return;
        reverseRange(arr, 0, arr.length - 1);
    }

    public static void reverseRange(int[] arr, int start, int end) {
        while (start < end) {
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }

    public static void main(String[] args) {
        System.out.println("=== In-Place Array Reversal (Two Pointers) ===");

        int[] arr1 = { 1, 2, 3, 4, 5, 6 };
        System.out.println("Original: " + Arrays.toString(arr1));
        reverse(arr1);
        System.out.println("Reversed: " + Arrays.toString(arr1));

        int[] arr2 = { 10, 20, 30, 40, 50, 60, 70 };
        System.out.println("\nOriginal: " + Arrays.toString(arr2));
        reverseRange(arr2, 2, 5); // Reverse sub-segment [30, 40, 50, 60]
        System.out.println("Range [2..5] Reversed: " + Arrays.toString(arr2));
    }
}

/*
 * Time Complexity: O(N) - N/2 swaps.
 * Space Complexity: O(1) - Constant auxiliary space.
 */

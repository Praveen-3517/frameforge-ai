/*
 * Problem Statement:
 * Given an array of integers and a target value:
 * 1. Find the first occurrence index of the target.
 * 2. Find the last occurrence index of the target.
 * 3. Find all occurrence indices of the target.
 * If target not found, return -1 or empty list.
 * 
 * Asked in: Infosys, TCS, Wipro, Accenture
 */

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class LinearSearchAllOccurrences {

    public static int findFirst(int[] arr, int target) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    public static int findLast(int[] arr, int target) {
        for (int i = arr.length - 1; i >= 0; i--) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    public static List<Integer> findAll(int[] arr, int target) {
        List<Integer> indices = new ArrayList<>();
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) indices.add(i);
        }
        return indices;
    }

    public static void main(String[] args) {
        int[] arr = {4, 2, 7, 1, 2, 9, 2, 5};
        int target = 2;

        System.out.println("Array: " + Arrays.toString(arr) + ", Target: " + target);
        System.out.println("First occurrence index: " + findFirst(arr, target));
        System.out.println("Last occurrence index:  " + findLast(arr, target));
        System.out.println("All occurrence indices: " + findAll(arr, target));
    }
}

/*
 * Time Complexity: O(N) linear scan over N elements.
 * Space Complexity: O(K) where K is occurrences count for findAll.
 */
